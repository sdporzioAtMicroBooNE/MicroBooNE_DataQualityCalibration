import ROOT, sys
import datetime
import numpy as np
import pandas as pd
from collections import OrderedDict as OD

### Progress message to make sure loop is running
class pbar:
    def __init__(self,size):
        self.ind = 0
        self.prevPerc = 0
        self.size = size
    def update(self):
        self.ind += 1
        perc = float(self.ind/float(self.size-1)*100.)
        if perc - self.prevPerc > 1:
            if perc < 100:
                self.prevPerc = perc
                sys.stdout.write('\r'+'Processing... %i%%' %perc)
                sys.stdout.flush()
            else:
                sys.stdout.write('\r'+'Complete')

### Save YZ corrections to file
def GetYZfile(name_in,dirOut):
    # Get timestamp
    path = name_in
    name_in = path.split('/')[-1]
    year = name_in.strip().split('_')[2]
    month = name_in.strip().split('_')[3]
    day = name_in.strip().split('_')[4]
    plane = int(name_in.strip().split('_')[-1].split('.')[0])

    epoch = datetime.datetime(1970,1,1)
    timestamp = (datetime.datetime(int(year),int(month),int(day)) - epoch).total_seconds()

    hType = 'error_dq_dx_z_vs_y_hist'
    tFile = ROOT.TFile(path,'READ')
    hist = tFile.Get(hType)
    nx = hist.GetNbinsX()
    ny = hist.GetNbinsY()
    zLow, zHigh, yLow, yHigh, corr, err = [], [], [], [], [], []

    for j in range(ny):
        for i in range(nx):
            zLow.append(hist.GetXaxis().GetBinLowEdge(i+1))
            zHigh.append(hist.GetXaxis().GetBinLowEdge(i+2))
            yLow.append(hist.GetYaxis().GetBinLowEdge(j+1))
            yHigh.append(hist.GetYaxis().GetBinLowEdge(j+2))
            corr.append(hist.GetBinContent(i+1,j+1))
            err.append(0.)
    for k in range(10001-len(zLow)):
            zLow.append(1000000.0)
            zHigh.append(1100000.0)
            yLow.append(1000000.0)
            yHigh.append(1100000.0)
            corr.append(0.)
            err.append(0.) 
    data = OD([('yLow',yLow),
               ('yHigh',yHigh),
               ('zLow',zLow),
               ('zHigh',zHigh),
               ('corr',corr),
               ('err',err)
              ])
    df = pd.DataFrame.from_dict(data)

    name_out = dirOut+'/dqdx_yz_plane%i_data/YZ_correction_factors_%i_plane_%i_v1r3.dat' %(plane,timestamp,plane)
    with open(name_out,'wb') as fileOut:
        fileOut.write('# time %i\n' %timestamp)
        fileOut.write('# channel y_bin_low_edge y_bin_high_edge z_bin_low_edge z_bin_high_edge correction correction_err\n')
        for i in range(len(df)):
            yLow = df.iloc[i]['yLow']
            yHigh = df.iloc[i]['yHigh']
            zLow = df.iloc[i]['zLow']
            zHigh = df.iloc[i]['zHigh']
            corr = df.iloc[i]['corr']
            err = df.iloc[i]['err']
            fileOut.write('%i %f %f %f %f %f %f\n' %(i,yLow,yHigh,zLow,zHigh,corr,err))

### Save X corrections to file
def GetXfile(name_in,dirOut):
    # Get timestamp
    path = name_in
    name_in = path.split('/')[-1]
    month = name_in.strip().split('_')[2]
    day = name_in.strip().split('_')[3]
    if month > 9: year = 2017
    if month < 5: year = 2018
    plane = int(name_in.strip().split('_')[5].split('.')[0])

    epoch = datetime.datetime(1970,1,1)
    timestamp = (datetime.datetime(int(year),int(month),int(day)) - epoch).total_seconds()

    hType = 'dq_dx_x_error_hist'
    tFile = ROOT.TFile(path,'READ')
    hist = tFile.Get(hType)
    nx = hist.GetNbinsX()
    xLow, xHigh, corr, err = [], [], [], [],

    for i in range(nx):
        xLow.append(hist.GetXaxis().GetBinLowEdge(i+1))
        xHigh.append(hist.GetXaxis().GetBinLowEdge(i+2))
        corr.append(hist.GetBinContent(i+1))
        err.append(0.)
    for k in range(131-len(xLow)):
            xLow.append(1000000.0)
            xHigh.append(1100000.0)
            corr.append(0.)
            err.append(0.) 
    data = OD([('xLow',xLow),
               ('xHigh',xHigh),
               ('corr',corr),
               ('err',err)
              ])
    df = pd.DataFrame.from_dict(data)
    
    name_out = dirOut+'/dqdx_x_plane%i_data/X_correction_factors_%i_plane_%i_v1r3.dat' %(plane,timestamp,plane)
    with open(name_out,'wb') as fileOut:
        fileOut.write('# time %i\n' %timestamp)
        fileOut.write('# channel x_bin_low_edge x_bin_high_edge correction correction_err\n')
        for i in range(len(df)):
            xLow = df.iloc[i]['xLow']
            xHigh = df.iloc[i]['xHigh']
            corr = df.iloc[i]['corr']
            err = df.iloc[i]['err']
            fileOut.write('%i %f %f %f %f\n' %(i,xLow,xHigh,corr,err))
from datetime import datetime as dt
import pandas as pd

df = pd.read_csv('second_global_dqdx_all_planes.txt',sep=' ')

dtCol = []
for i in range(len(df)):
    day = int(df['i'][i].split('/')[1])
    month = int(df['i'][i].split('/')[0])
    if month < 6: year = 2018
    else: year = 2017
    dtCol.append(dt(year,month,day,0,0,0))
df['date'] = dtCol

dfOut = df[['date','2']]
dfOut.to_csv('dqdx',sep=' ',header=False)
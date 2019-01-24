import os
import datetime
import time
from shutil import copyfile

directory = "/uboone/data/users/eberly/calibrations/dqdx/data/v1/X/"
new_dir = "/uboone/data/users/eberly/calibrations/dqdx/data/v1/Xrenamed/"

epoch = datetime.datetime(1970,1,1)

my_file_list = sorted(os.listdir(directory))
for line in list(my_file_list):
  if not line.startswith('X_correction'):
    my_file_list.remove(line)

old_stamp = 3
for filename in my_file_list:
  year = filename.strip().split('_')[3]
  month = filename.strip().split('_')[4]
  day = filename.strip().split('_')[5]
  
  epoch_time = (datetime.datetime(int(year),int(month),int(day)) - epoch).total_seconds()
  
  new_filename = filename.strip().split('factors')[0]+"factors_"+str(int(epoch_time))+"_plane_"+filename.strip().split('_')[-1]
  
  copyfile(directory+filename,new_dir+new_filename)


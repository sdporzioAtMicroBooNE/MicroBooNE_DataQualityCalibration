import os
import datetime

f1 = open("/uboone/data/users/eberly/calibrations/dqdx/data/v1r0/T/time_corrections.txt")
lines = f1.readlines()

year = 2016
epoch = datetime.datetime(1970,1,1)
for line in lines:
  line_elements = line.strip().split()
  month_day = line_elements[0]
  month = int(month_day.strip().split('/')[0])
  day = int(month_day.strip().split('/')[1])
  
  plane0 = line_elements[2]
  plane1 = line_elements[3]
  plane2 = line_elements[4]
  
  epoch_time = (datetime.datetime(year,month,day) - epoch).total_seconds()
  
  new_filename = "T_correction_factors_"+str(int(epoch_time))+"_v1r0.dat"
  
  f2 = open("/uboone/data/users/eberly/calibrations/dqdx/data/v1r0/Tdatabase/"+new_filename,'w')
  f2.write("# time "+str(int(epoch_time))+'\n')
  f2.write("# channel correction correction_err\n")
  f2.write("0 "+plane0+" 0.0\n")
  f2.write("1 "+plane1+" 0.0\n")
  f2.write("2 "+plane2+" 0.0\n")
  
  f2.close()
  
f1.close()
  
  

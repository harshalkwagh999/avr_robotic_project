import sys
import subprocess as sp

if (len(sys.argv)!=3):
    print "USAGE: python prog.py robot_prog.c input_file"
    exit(0)    
inputF=open(sys.argv[2],"r")
 
input_lst=inputF.readlines()
pattern=".*cmdArr\[\]={.*"
replace="unsigned char cmdArr[]="+"{"+input_lst[0].replace(' ',',')+"};"

if(sp.call("sed -i 's/"+pattern+"/"+replace+"/'"+" "+sys.argv[1],shell=True)==0):
    print "INPUT LOADED SUCCESSFULLY"
else:
    print "Error While Loading Input"
    

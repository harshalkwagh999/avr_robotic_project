import sys, os
import subprocess as sp

os.makedirs(sys.argv[2])
output_file_path= "{}/{}.c".format(sys.argv[2],sys.argv[2])
makefile_path="{}/Makefile".format(sys.argv[2])
configF=open(sys.argv[1],"r")
outputF=open(output_file_path,"w")

header_st="#ifndef F_CPU"+"\n"
header_end="#endif"+"\n"
ddr="DDR"
port="PORT"
pin="PIN"
include="#include "
define="#define "
zero="0x00"
ff="0xFF"
Timer0_flags="TIMSK |= (1<<TOIE0); TCNT0=0x00;"
Timer1_flags="TIMSK |= (1<<TOIE1); TCNT1=0x00;"
empty_while="while(true) {}"

Timer0_prescale_flags=[("0","(0<<CS02) | (0<<CS01) | (1<<CS00)"),
                       ("8","(0<<CS02) | (1<<CS01) | (0<<CS00)"),
                       ("64","(0<<CS02) | (1<<CS01) | (1<<CS00)"),
                       ("256","(1<<CS02) | (0<<CS01) | (0<<CS00)"),
                       ("1024","(1<<CS02) | (0<<CS01) | (1<<CS00)")]

Timer1_prescale_flags=[("0","(0<<CS12) | (0<<CS11) | (1<<CS10)"),
                       ("8","(0<<CS12) | (1<<CS11) | (0<<CS10)"),
                       ("64","(0<<CS12) | (1<<CS11) | (1<<CS10)"),
                       ("256","(1<<CS12) | (0<<CS11) | (0<<CS10)"),
                       ("1024","(1<<CS12) | (0<<CS11) | (1<<CS10)")]

input_lst=configF.readlines()

def find_prescale_flags(prescale,flags_lst):
    for tup in flags_lst:
        if tup[0]==prescale:
            return tup[1]

for line in input_lst:
    print line
    section=line.split(": ")[0]
    elems= line.split(": ")[1].split(",")
    
    if (section=="Title"):
        outputF.writelines("/*"+elems[0]+"*/")
        outputF.writelines("\n")

    elif (section=="F_CPU"):
        outputF.writelines(header_st)
        outputF.writelines(define+"F_CPU "+elems[0])
        outputF.writelines(header_end)

    elif (section=="Inclusions"):
        for elem in elems:
            if elem.endswith("\n"):
                elem=elem[:-1]
            outputF.writelines(include+"<"+elem+">"+"\n")
        outputF.writelines("\n")

    elif (section=="Definemacros"):
        for elem in elems:
            if elem.endswith("\n"):
                elem=elem[:-1]               
            outputF.writelines(define+" "+elem.split()[0]+" "+elem.split()[1]+"\n")
        outputF.writelines("\n")

    elif (section=="Start_fun"):
        if elems[0].endswith("\n"):
            elems[0]=elems[0][:-1]
        outputF.writelines(elems[0]+" {\n")

    elif (section=="End_fun"):
        outputF.writelines("\t"+"return 0; }\n")

    elif (section=="IO_ports"):
        for elem in elems:
            if elem.endswith("\n"):
                elem=elem[:-1]
            if (elem.split()[1]=="output"):
                outputF.writelines("\t"+ddr+elem.split()[0]+"="+ff+" ;\n")
            elif (elem.split()[1]=="input"):
                outputF.writelines("\t"+ddr+elem.split()[0]+"="+zero+" ;\n")

    elif (section=="Interrupts"):
        for elem in elems:
            if (elem.split()[0]=="Timer0"):
                outputF.writelines("\n\t"+Timer0_flags+"\n")
                outputF.writelines("\t"+"TCCR0"+"="+find_prescale_flags(elem.split()[1].strip(),Timer0_prescale_flags)+"\n")                
                
            if (elem.split()[0]=="Timer1"):
                outputF.writelines("\n\t"+Timer1_flags+"\n")
                outputF.writelines("\t"+"TCCR1B"+"="+find_prescale_flags(elem.split()[1].strip(),Timer1_prescale_flags)+"\n")

    elif (section=="Interrupt_enable"):
        outputF.writelines("\t"+"sei();"+"\n")

    elif (section=="Start_loop"):
        outputF.writelines("\t"+elems[0]+" {")

    elif (section=="End_loop"):
        outputF.writelines("\t"+"}\n")

    elif (section=="Add_helper"):            
        outputF.close()
        sp.Popen("cat"+" "+sys.argv[3]+" >>"+output_file_path,shell=True)

        for elem in elems:
            if elem.endswith("\n"):
                elem=elem[:-1]
            if (elem.split()[0]=="DATA_PORT"):
                tmp_port=port+elem.split()[1]
                sp.Popen("sed -i s/"+elem.split()[0]+"/"+tmp_port+"/g"+" "+output_file_path,shell=True)
            if (elem.split()[0]=="SENS_PORT"):
                tmp_port=pin+elem.split()[1]
                sp.Popen("sed -i s/"+elem.split()[0]+"/"+tmp_port+"/g"+" "+output_file_path,shell=True)

sp.Popen("cp "+sys.argv[4]+" "+makefile_path,shell=True)
sp.Popen("sed -i s/"+"progname"+"/"+sys.argv[2]+"/g"+" "+makefile_path,shell=True)

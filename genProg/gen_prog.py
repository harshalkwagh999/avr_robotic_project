# This program generates C-programs for Microcontroller according to the config file

import sys, os
import subprocess as sp

if (len(sys.argv)!=5):
    print "USAGE: python prog.py exmpl.conf new_prog_name helper_prog_file.c helper_Makefile"
    exit(0)

# defined paths:
output_file_path= "{}/{}.c".format(sys.argv[2],sys.argv[2])
makefile_path="{}/Makefile".format(sys.argv[2])
LCD_CONF_PATH="helper_files/LCDPORT_CONF"
KEYPAD_CONF_PATH="helper_files/KEYPAD_CONF"

# defined flags and register names for AVR:
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
INT0_flags="GICR |= 1 << INT0;"
INT1_flags="GICR |= 1 << INT1;"
Timer0_pre_reg="TCCR0"
Timer1_pre_reg="TCCR1B"
MCUCR="MCUCR"
INT_PORT="PORTD"
clr_global_INT="cli();"
INT_enable="sei();"
INT_ON=["0x04","0x08"]

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

INT0_interrupt_events=["0 << ISC01 | 0 <<ISC00",
                       "0 << ISC01 | 1 <<ISC00",
                       "1 << ISC01 | 0 <<ISC00",
                       "1 << ISC01 | 1 <<ISC00"]

INT1_interrupt_events=["0 << ISC11 | 0 <<ISC10",
                       "0 << ISC11 | 1 <<ISC10",
                       "1 << ISC11 | 0 <<ISC10",
                       "1 << ISC11 | 1 <<ISC10"]


def find_prescale_flags(prescale,flags_lst):
    for tup in flags_lst:
        if tup[0]==prescale:
            return tup[1]

def parser_and_generator(input_lst):
    for line in input_lst:
        print line
        section=line.split(": ")[0]
        params= line.split(": ")[1].split(",")
        
        if (section=="Title"):
            outputF.writelines("/*"+params[0]+"*/")
            outputF.writelines("\n")
    
        elif (section=="F_CPU"):
            outputF.writelines(header_st)
            outputF.writelines(define+"F_CPU "+params[0])
            outputF.writelines(header_end)
    
        elif (section=="Set_lcdport"):
            lcdconfF=open(LCD_CONF_PATH,"r")
            lcdport_lst=lcdconfF.readlines()
            for line in lcdport_lst:
                for prm in params:
                    if prm.endswith("\n"):
                        prm=prm[:-1]
                    prm=prm.split()
                    if (line != line.replace(prm[0],prm[1])):
                        outputF.writelines(line.replace(prm[0],prm[1]))
            outputF.writelines("\n")
            lcdconfF.close()
    
        elif (section=="Set_keyport"):
            keypad_conF=open(KEYPAD_CONF_PATH,"r")
            keypad_lst=keypad_conF.readlines()
            for line in keypad_lst:
                if params[0].endswith("\n"):
                    prm=params[0][:-1]
                prm=prm.split()
                outputF.writelines(line.replace(prm[0],prm[1]))
            outputF.writelines("\n")
            keypad_conF.close()
            
        elif (section=="Inclusions"):
            for prm in params:
                if prm.endswith("\n"):
                    prm=prm[:-1]
                outputF.writelines(include+"<"+prm+">"+"\n")
            outputF.writelines("\n")
    
        elif (section=="Definemacros"):
            for prm in params:
                if prm.endswith("\n"):
                    prm=prm[:-1]               
                outputF.writelines(define+" "+prm.split()[0]+" "+prm.split()[1]+"\n")
            outputF.writelines("\n")
    
        elif (section=="Start_fun"):
            if params[0].endswith("\n"):
                params[0]=params[0][:-1]
            outputF.writelines(params[0]+" {\n")
    
        elif (section=="End_fun"):
            outputF.writelines("\t"+"return 0; }\n")
            outputF.writelines("\n")
            
        elif (section=="Call_fun"):
            outputF.writelines("\t"+params[0][:-1]+";\n")
    
        elif (section=="IO_ports"):
            for prm in params:
                if prm.endswith("\n"):
                    prm=prm[:-1]
                if (prm.split()[1]=="output"):
                    outputF.writelines("\t"+ddr+prm.split()[0]+"="+ff+" ;\n")
                elif (prm.split()[1]=="input"):
                    outputF.writelines("\t"+ddr+prm.split()[0]+"="+zero+" ;\n")
    
        elif (section=="SW_interrupts"):
            for prm in params:
                if (prm.split()[0]=="Timer0"):
                    outputF.writelines("\n\t"+Timer0_flags+";\n")
                    outputF.writelines("\t"+Timer0_pre_reg+"="+find_prescale_flags(prm.split()[1].strip(),Timer0_prescale_flags)+";\n")                
                    
                if (prm.split()[0]=="Timer1"):
                    outputF.writelines("\n\t"+Timer1_flags+"\n")
                    outputF.writelines("\t"+Timer1_pre_reg+"="+find_prescale_flags(prm.split()[1].strip(),Timer1_prescale_flags)+";\n")
    
        elif (section=="EX_interrupts"):
            for prm in params:
                if prm.endswith("\n"):
                    prm=prm[:-1]
                print 
                if (prm.split()[0]=="INT0"):
                    outputF.writelines("\n\t"+INT0_flags+"\n")
                    outputF.writelines("\t"+MCUCR+"|="+INT0_interrupt_events[int(prm.split()[1])]+";\n")
                elif (prm.split()[0]=="INT1"):
                    outputF.writelines("\n\t"+INT1_flags+"\n")
                    outputF.writelines("\t"+MCUCR+"|="+INT1_interrupt_events[int(prm.split()[1])]+";\n")
        elif (section=="Interrupt_enable"):
            outputF.writelines("\t"+INT_enable+"\n")
            
        elif (section=="Interrupt_ON"):
            if params[0].endswith("\n"):
                    prm=params[0][:-1]
            outputF.writelines("\t"+INT_PORT+"="+INT_ON[int(prm[len(prm)-1])]+";\n")
    
        elif (section=="Interrupt_OFF"):
            if params[0].endswith("\n"):
                    prm=params[0][:-1]
            outputF.writelines("\t"+INT_PORT+"^="+INT_ON[int(prm[len(prm)-1])]+";\n")
            
        elif (section=="Clear_interrupt"):
            outputF.writelines("\t"+clr_global_INT+"\n")
            
        elif (section=="Start_loop"):
            outputF.writelines("\t"+params[0]+"\t{")
    
        elif (section=="End_loop"):
            outputF.writelines("\t"+"}\n")
    
        elif (section=="Add_helper"):            
            outputF.close()
            if(sp.call("cat"+" "+sys.argv[3]+" >>"+output_file_path,shell=True)==0):
                if (params != ['\n']):
                    for prm in params:
                        if prm.endswith("\n"):
                            prm=prm[:-1]
                        sp.call("sed -i s/"+prm.split()[0]+"/"+prm.split()[1]+"/g"+" "+output_file_path,shell=True)
            else:
                print "Error while adding helper"
                exit(0)
    if (sp.call("cp "+sys.argv[4]+" "+makefile_path,shell=True)==0):
        sp.call("sed -i s/"+"progname"+"/"+sys.argv[2]+"/g"+" "+makefile_path,shell=True)
    else:
        print "Error in copying Makefile"
        exit(0)

# Program execution starts from here:

os.makedirs(sys.argv[2])
configF=open(sys.argv[1],"r")
outputF=open(output_file_path,"w")
input_lst=configF.readlines()
parser_and_generator(input_lst)

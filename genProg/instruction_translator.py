# This program accept an .ri program which contains instructions for robot movement and
# generates an output file which contain translated instructions for robot

import sys

if (len(sys.argv)!=3):
    print "USAGE: python prog.py input.ri output_file"
    exit(0)
    
# defined key values
#   [0,1,2,3,4,5,6,7,8,9,A,B,C,D,*,#]
key=["0xeb","0x77","0x7b","0x7d","0xb7","0xbb","0xbd","0xd7",
     "0xdb","0xdd","0x7e","0xbe","0xde","0xee","0xe7","0xed"]

space=" "
key_END="0x00"


def convert_mov(motor,direction):
    if (direction=="F"):
        if(motor=="M1"):
            outputF.writelines(key[1]+space)
            return 0
        elif(motor=="M3"):
            outputF.writelines(key[2]+space)
            return 0
        elif(motor=="M4"):
            outputF.writelines(key[3]+space)
            return 0
        elif(motor=="M5"):
            outputF.writelines(key[10]+space)
            return 0
        else:
            return -1
    elif (direction=="B"):
        if(motor=="M1"):
            outputF.writelines(key[4]+space)
            return 0
        elif(motor=="M3"):
            outputF.writelines(key[5]+space)
            return 0
        elif(motor=="M4"):
            outputF.writelines(key[6]+space)
            return 0
        elif(motor=="M5"):
            outputF.writelines(key[11]+space)
            return 0
        else:
            return -1
    else:
        return -1
    
def convert_delay(delay):
    if(delay.isdigit()):
        outputF.writelines(key[12]+space)
        map(lambda x:outputF.writelines(key[int(x)]+space),delay)
        outputF.writelines(key[13]+space)
        return 0
    else:
        return -1
    
# parse input file and manage conversion of instructions
def parse_input(instr_lst,flag):
    repeat_lst=[]
    i=0
    rec_cnt=0
    while(i<len(instr_lst)):
        ins=instr_lst[i].split()
        if (ins[0]=="START" and len(ins)==1):
            flag=1
        elif (ins[0]=="END" and len(ins)==1):
            outputF.writelines(key_END)
            return(0)
            
        elif (ins[0]=="REPEAT" and len(ins)==2):
            cnt = int(ins[1])
            i=i+1
            while(True):
                ins=instr_lst[i].split()
                if (ins[0]=="REPEAT"):
                    rec_cnt=rec_cnt+1
                    repeat_lst.append(instr_lst[i])
                elif (ins[0]=="END_LOOP" and rec_cnt==0):
                    break
                elif (ins[0]=="END_LOOP" and rec_cnt!=0):
                    repeat_lst.append(instr_lst[i])
                    rec_cnt=rec_cnt-1
                else:
                    repeat_lst.append(instr_lst[i])
                i=i+1;

            for itr in range(cnt):
                parse_input(repeat_lst,flag)
                
        elif (flag==1):
            if (ins[0]=="MOV" and len(ins)==3):
                if(convert_mov(ins[1],ins[2])!=0):
                    print "Invalid Instruction: "+instr_lst[i]+"\n"
                    exit(0)
               
            elif (ins[0]=="DELAY" and len(ins)==2):
                if (convert_delay(ins[1])!=0):
                    print "Invalid Instruction: "+instr_lst[i]+"\n"
                    exit(0)
            else:
                print "Invalid Instruction: "+instr_lst[i]+"\n"
                exit(0)
        else:
            print "Invalid Instruction: "+instr_lst[i]+"\n"
            exit(0)
        i = i+1
        
    
def main():
    instr_lst=[]
    instr_lst=extract_instructions(input_lst,instr_lst)
    parse_input(instr_lst,flag)
            
# extract executable instructions from input file
def extract_instructions(input_lst,instructions):
    for line in input_lst:
        if (line.strip().split(";")[0]!=""):
            line=line.strip().split(";")[0]
            instructions.append(line)
    return instructions


if (sys.argv[1].split(".")[1]!="ri"):
    print "INVALID INPUT FILE FORMAT"
    exit(0)
else:
    inputF=open(sys.argv[1],"r")
    outputF=open(sys.argv[2],"w")

input_lst=inputF.readlines()
flag=0
main()

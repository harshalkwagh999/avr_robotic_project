import sys


inputF=open(sys.argv[1],"r")
outputF=open(sys.argv[2],"w")

key_0="0xeb"
key_1="0x77"
key_2="0x7b"
key_3="0x7d"
key_4="0xb7"
key_5="0xbb"
key_6="0xbd"
key_7="0xd7"
key_8="0xdb"
key_9="0xdd"
key_A="0x7e"
key_B="0xbe"
key_C="0xde"
key_D="0xee"
key_star="0xe7"
key_hash="0xed"
space=" "

def convert_mov(motor,direction):
    if (direction=="F"):
        if(motor=="M1"):
            outputF.writelines(key_1+space)
            return 0
        elif(motor=="M3"):
            outputF.writelines(key_2+space)
            return 0
        elif(motor=="M4"):
            outputF.writelines(key_3+space)
            return 0
        elif(motor=="M5"):
            outputF.writelines(key_A+space)
            return 0
        else:
            return -1
    elif (direction=="B"):
        if(motor=="M1"):
            outputF.writelines(key_4+space)
            return 0
        elif(motor=="M3"):
            outputF.writelines(key_5+space)
            return 0
        elif(motor=="M4"):
            outputF.writelines(key_6+space)
            return 0
        elif(motor=="M5"):
            outputF.writelines(key_B+space)
            return 0
        else:
            return -1
    else:
        return -1
    
def replace_key(key):
    if key=='0':
        return key_0
    elif key=='1':
        return key_1
    elif key=='2':
        return key_2
    elif key=='3':
        return key_3
    elif key=='4':
        return key_4
    elif key=='5':
        return key_5
    elif key=='6':
        return key_6
    elif key=='7':
        return key_7
    elif key=='8':
        return key_8
    elif key=='9':
        return key_9
    
    
def convert_delay(delay):
    if(delay.isdigit()):
        outputF.writelines(key_C+space)
        map(lambda x:outputF.writelines(replace_key(x)+space),delay)
        outputF.writelines(key_D+space)
        return 0
    else:
        return -1
    

def parse_input(instr_lst,flag):
    repeat_lst=[]
    i=0
    rec_cnt=0
    while(i<len(instr_lst)):
        ins=instr_lst[i].split()
        if (ins[0]=="START" and len(ins)==1):
            flag=1
        elif (ins[0]=="END" and len(ins)==1):
            flag=0
            
        elif (ins[0]=="REPEAT" and len(ins)==2):
            cnt = int(ins[1])
            i=i+1
            while(True):
                if (instr_lst[i].split()[0]=="REPEAT"):
                    rec_cnt=rec_cnt+1
                    repeat_lst.append(instr_lst[i])
                elif (instr_lst[i].split()[0]=="END_LOOP" and rec_cnt==0):
                    break
                elif (instr_lst[i].split()[0]=="END_LOOP" and rec_cnt!=0):
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
            
def extract_instructions(input_lst,instructions):
    for line in input_lst:
        if (line.strip().split(";")[0]!=""):
            line=line.strip().split(";")[0]
            instructions.append(line)
    return instructions


input_lst=inputF.readlines()
flag=0
main()

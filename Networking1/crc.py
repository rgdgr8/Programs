generator = '100101'
ZERO = '00000'

def crc_div(word,recv):
    z = word
    if(recv==False):
        for i in range(0,len(generator)-1):
            z += '0'
    
    cur = z[0:len(generator)]
    for j in range(len(cur),len(z)+1):
        if(j>=len(z)):
            y = ''
        else:
            y = z[j]

        if(cur[0]=='0'):
            cur = cur[1:]+y
            continue

        x = ''
        for i in range(1,len(cur)):
            if(cur[i]==generator[i]):
                x += '0'
            else:
                x += '1'
        cur = x+y

    return cur

def sender_check(word):
    return word+crc_div(word,False)

def recvr_check(word):
    rem = crc_div(word,True)
    if(rem==ZERO):
        return "No Error"

    return 'Error Detected'


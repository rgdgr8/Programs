def sender_check(words,frame):
    vert_bits = ['0']*frame
    for i in range(0,frame):
        vert_count = 0
        for word in words:
            if(word[i]=='1'):
                vert_count += 1
        
        if(vert_count%2!=0):
            vert_bits[i] = '1'

    hor_bits = ['0']*frame
    for i in range(0,len(words)):
        word = words[i]
        hor_count = 0
        for c in word:
            if(c=='1'):
                hor_count += 1
    
        if(hor_count%2!=0):
            hor_bits[i] = '1'

    words = "".join(words)
    vert_red = "".join(vert_bits)
    hor_red = "".join(hor_bits)
    #print('vert:',vert_red,'hor:',hor_red)
    return words+vert_red+hor_red #vertical redundant bits in the second last and horizontal redundant bits in the last

def recvr_check(word,frame):
    ERROR = "Error Detected"
    NOERR = "No Error"
    words = []
    j = 0
    for i in range(frame,len(word)+1,frame):
        words.append(word[j:i])
        j = i
    #print('recvr_ch:',words)
    for i in range(0,frame):
        vert_count = 0
        for j in range(0,len(words)-2):
            w = words[j]
            if(w[i]=='1'):
                vert_count += 1

        vert_count += int(words[len(words)-2][i])
        #print(f'after vert{i}',vert_count)
        if(vert_count%2!=0):
            return ERROR
    
    for i in range(0,len(words)-2):
        hor_count = 0
        for c in words[i]:
            if(c=='1'):
                hor_count += 1

        hor_count += int(words[len(words)-1][i])
        if(hor_count%2!=0):
            return ERROR

    return NOERR

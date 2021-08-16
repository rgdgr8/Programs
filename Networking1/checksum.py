def add_frames(words,frame):
    s = ''
    c = '0'
    for i in range(frame-1,-1,-1):
        if(c=='1'):
            count1 = 1
        else:
            count1 = 0

        for word in words:
            if(word[i]=='1'):
                count1 += 1
        
        if(count1==0):
            s = '0' + s
            continue
        
        if(count1%2==0):
            s = '0' + s
            c = '1'
        else:
            s = '1' + s
            if(count1==1):
                c = '0'
            else:
                c = '1'
    if(c=='1'):
        return c+s

    return s

def get_sum(words,frame):
    t = ['0' for _ in range(frame)]
    s = ''.join(t)
    for i in range(0,len(words)):
        extra_bits = len(s)-len(words[i])
        if(extra_bits>0):
            for _ in range(extra_bits):
                words[i] = '0'+words[i]

        s = add_frames([s,words[i]],(frame+extra_bits))

    extra_bits = len(s) - frame
    if(extra_bits>0):
        f = frame - extra_bits
        t = ''
        for i in range(f):
            t += '0'

        t += s[0:extra_bits]
        s = add_frames([t,s[extra_bits:]],frame)

    t = ''
    for c in s:
        if(c=='0'):
            t += '1'
        else:
            t += '0'

    return t

def sender_check(words,frame):
    codeword = ''
    for w in words:
        codeword += w

    t = get_sum(words,frame)
    codeword += t 
    return codeword

def recvr_check(word,frame):
    words = []
    j = 0
    for i in range(frame,len(word)+1,frame):
        words.append(word[j:i])
        j = i

    s = get_sum(words,frame)
    for c in s:
        if(c!='0'):
            return 'Error Detected'

    return 'No Error'

def sender_check(dw):
    count = 0
    for c in dw:
        if(c=='1'):
            count += 1

    dw += str(count%2)
    return dw

def recvr_check(cw):
    count = 0
    for c in cw:
        if(c=='1'):
            count += 1

    #print('recvr_check:',cw,count)
    if(count%2!=0):
        return "Error detected"

    return "No error"

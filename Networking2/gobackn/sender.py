import socket
import sys
import time


def createFrame(data):
    countOnes = 0
    for ch in data:
        if ch == '1':
            countOnes += 1
    data += str(countOnes % 2)
    return data

def Main(senderno):
    first = 0
    count = 0
    sentframes = []
    f = open('ws.txt','r')
    windowsize = int(f.read())
    f.close()

    print('Initiating Sender #', senderno)
    host = '127.0.0.1'
    f = open('sp.txt','r')
    port = int(f.read())
    f.close()

    mySocket = socket.socket()
    mySocket.connect((host, port))

    ui = -1
    re = 0
    while True:
        print()
        x = 'sending to channel :'
        if(ui>=len(sentframes)):
            ui = 0
        if(ui<0):
            re = 0
            data = input("Enter data: ")
            msg = createFrame(data) 
            data = msg + '/' + str(count)
            sentframes.append(data)
            count = (count+1)%windowsize
        else:
            re += 1
            if(re>len(sentframes)*3):
                ui =  -1
                continue
                
            data = sentframes[ui]
            ui += 1
            x = 're'+x
        
        print(x, data, 'ui= ', str(ui))
        mySocket.send(data.encode())
        starttime = time.time()

        if not msg:
            break
        if msg == 'q0':
            break

        resp = mySocket.recv(1024).decode()
        endtime = time.time()
        print('Received from channel:',resp)
        print('RTT=',endtime-starttime)
        try:
            if(resp=='-0'):
                resp = -1
            else:
                resp = int(resp)
        except:
            continue

        if(endtime-starttime>2):
            print('Timeout',str(resp),'ui=',str(ui))
            if(ui<0):
                ui += 1
        elif(resp>-1):#non-corrupt ack
            del sentframes[0:min((resp+1),len(sentframes))]
            first = (resp+1)%windowsize
            ui = -1
        else:
            if(ui<0):
                ui += 1

    mySocket.close()


if __name__ == '__main__':
    if len(sys.argv) > 1:
        senderno = int(sys.argv[1])
    else:
        senderno = 1
    Main(senderno)

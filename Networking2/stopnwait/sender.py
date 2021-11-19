import socket
import sys
import time

def createFrame(data):#even parity vrc
    countOnes = 0
    for ch in data:
        if ch == '1':
            countOnes += 1
    data += str(countOnes % 2)
    return data


def Main(senderno):
    print('Initiating Sender #', senderno)
    host = '127.0.0.1'
    f = open('sp.txt','r')
    port = int(f.read())
    f.close()

    mySocket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    print('sender port:',port)
    mySocket.connect((host, port))

    while True:
        print()
        data = input("Enter data: ")
        prevtime = time.time()
        data = createFrame(data)
        print('Sending to channel :', str(data))
        mySocket.send(data.encode())
        if not data or data=='q0':
            break

        rdata = mySocket.recv(1024).decode()
        print('Received from channel :', str(rdata))
        curtime = time.time()
        print('Round trip time: ', str(curtime-prevtime))
        if curtime-prevtime > 2:
            timeout = 1
        else:
            timeout = 0
        fileout = open('checktime.txt', "w")
        fileout.write(str(timeout))
        fileout.close()
        c = 0
        while timeout == 1:
            print()
            prevtime = time.time()
            if timeout == 1:
                print('TIMEOUT!')

            print('Again Sending to channel :', str(data))
            mySocket.send(data.encode())
            rdata = mySocket.recv(1024).decode()
            print('Again Received from channel :', str(rdata))
            curtime = time.time()
            print('Round trip time:', str(curtime-prevtime), 'seconds')
            #print('Bandwidth-delay product:',str((curtime-prevtime)*8),'bits/seconds')
            if curtime-prevtime > 2:
                timeout = 1
            else:
                timeout = 0
            fileout = open('checktime.txt', "w")
            fileout.write(str(timeout))
            fileout.close()
            c += 1
            if(c>=4):
                break

    mySocket.close()


if __name__ == '__main__':
    if len(sys.argv) > 1:
        senderno = int(sys.argv[1])
    else:
        senderno = 1
    Main(senderno)

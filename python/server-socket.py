import socket

PORT = 12345

with socket.socket(socket.AF_INET,socket.SOCK_STREAM) as s:
 s.bind((socket.gethostname(),PORT))
 s.listen()
 client,addr = s.accept()
 loop = 1
 try:
  while True:
   x = client.recv(1024)
   if(len(x)<=0):
    break
   print(x.decode(),end='')
   client.sendall("fuck you {}\r\n".format(loop).encode())
   loop = loop+1
 finally:
  client.close()

import socket

PORT = 12345

mysock = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
mysock.connect((socket.gethostname(),PORT))
try:
 for loop in range(31):
  cmd = 'anal? {}\r\n'.format(loop).encode()
  mysock.sendall(cmd)
  data = mysock.recv(512)
  if len(data) < 1:
   break
  print(data.decode(),end='')
finally:
 mysock.close()

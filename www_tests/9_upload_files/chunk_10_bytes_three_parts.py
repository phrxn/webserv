import socket
import time

# Configurações do servidor
host = 'localhost'
port = 9000

sleep_time = 10

#Create a socket and connect to the server
sock = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
sock.connect((host, port))

# !!!!! the request body is exactly 30 bytes in size 

# Create the HTTP Request with Chunked encoding
request = (
    "POST /file.txt HTTP/1.1\r\n"
    "Connection: keep-alive\r\n"
    "Host: aa\r\n"
    "Transfer-Encoding: chunked\r\n"
    "\r\n"
    "4\r\n"
    "abcd\r\n"
)

# Send the request
sock.sendall(request.encode())

time.sleep(sleep_time)

request_p2 = (
    "4\r\n"
    "1234\r\n"
)

sock.sendall(request_p2.encode())

time.sleep(sleep_time)

request_p3 = (
    "2\r\n"
    "\nZ\r\n"
    "0\r\n"
    "\r\n"
)

sock.sendall(request_p3.encode())

# Receive the response from the server (if any)
response = sock.recv(4096)
print("Server response: ", response.decode())

#close the socket
sock.close()


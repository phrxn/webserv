import socket
import time

# Configurações do servidor
host = 'localhost'
port = 9000

#Create a socket and connect to the server
sock = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
sock.connect((host, port))

# Create the HTTP Request with Chunked encoding
request = (
    "POST /file.txt HTTP/1.1\r\n"
    "Host: aa\r\n"
    "User-Agent: curl/7.74.\r\n"
    "Accept: */\r\n"
    "Content-Length: 12\r\n"
    "Content-Type: application/x-www-form-urlencode\r\n"
    "\r\n"
    "part1 "
)

# Send the request
sock.sendall(request.encode())

time.sleep(10)

request_p2 = (
    "part2\n"
)

sock.sendall(request_p2.encode())


# Receive the response from the server (if any)
response = sock.recv(4096)
print("Server response: ", response.decode())

#close the socket
sock.close()


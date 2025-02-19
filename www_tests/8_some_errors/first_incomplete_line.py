import socket

# Configurações do servidor
host = 'localhost'
port = 9000

#Create a socket and connect to the server
sock = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
sock.connect((host, port))

# Create the HTTP Request with Chunked encoding
request = (
    "GET HTTP/1.1\r\n"
    "Host: aa\r\n"
    "\r\n"
)

# Send the request
sock.sendall(request.encode())

# Receive the response from the server (if any)
response = sock.recv(1024)
print("Server response: ", response.decode())

#close the socket
sock.close()


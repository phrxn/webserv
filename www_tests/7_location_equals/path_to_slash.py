import socket

# Configurações do servidor
host = 'localhost'
port = 9000

#Create a socket and connect to the server
sock = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
sock.connect((host, port))

# Create the HTTP Request with Chunked encoding
request = (
    "GET /file.txt HTTP/1.1\r\n"
    "Host: aa\r\n"
    "\r\n"
)

print("===== the request =====")
print(request)
print("=======================\n")

# Send the request
sock.sendall(request.encode())

# Receive the response from the server (if any)
response = sock.recv(1024)
print("===== Server response =====\n")
print( response.decode())
print("===========================\n")

#close the socket
sock.close()


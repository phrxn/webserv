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
    "Connection: keep-alive\r\n"
    "User-Agent: FakeClientHTTP/1.0\r\n"
    "Accept: text/html, application/xhtml+xml, application/xml;q=0.9, image/webp, */*;q=0.8\r\n"
    "Accept-Encoding: gzip, deflate, br\r\n"
    "Accept-Language: pt-BR,pt;q=0.9,en-US;q=0.8,en;q=0.7\r\n"
    "\r\n"
)

# Send the request
sock.sendall(request.encode())

# Receive the response from the server (if any)
response = sock.recv(1024)
print("Server response: ", response.decode())

#close the socket
sock.close()


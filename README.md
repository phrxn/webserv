<p align="center">
  <img src="https://raw.githubusercontent.com/phrxn/webserv/refs/heads/main/images/webserv_logo.png?token=GHSAT0AAAAAACRRNVUCPUBX4LHVL65A7FPKZX4YV6A" />
</p>
<p align="center">
	<b><i>This is when you finally understand why a URL starts
with HTTP</i></b><br>
</p>

## About

This project is a simple HTTP server in C++98 with some restrictions and requires. They are:

- The server:
	- Must have a configuration file
	- Must be single thread
	- Must support multiple clients
	- Must be able to serve a fully static website
	- Must be able to listen to multiple ports
	- Must support HTTP 1.1 protocol and the methods: <code>GET</code>, <code>POST</code> e <code>DELETE</code>
	- Must stay available at all cost. For example, if an exception is thrown due to lack of memory, it must return an error page to the user and must not close out of nowhere.
	- Must provide support for CGI
	- Must have default error pages if none are provided in the configuration file
- The cliente:
	- Must be able to upload files
- A client request should never hang forever
- Sockets CANNOT be NON-BLOCKING
- Use only one I/O Multiplexer to manage sockets fds
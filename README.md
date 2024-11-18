<p align="center">
  <img src="https://raw.githubusercontent.com/phrxn/phrxn/refs/heads/master/webserv/webserv_logo.png" />
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

## Observation

1. Google tests version: v1.15.2

2. As the project MUST BE written in C++98, but Google tests require the C++14 version, compile this project always recompile everything.

3. The project is under development...

## Features

| Feature        | Status    |
|----------------|-----------|
| Handler signal (INTERRUPT, QUIT, etc...) | :heavy_check_mark:         |
| A Simple logger | :heavy_check_mark:         |
| Manage multiple connections (client sockets)  | :heavy_check_mark:         |
| Respond to TELNET | :heavy_check_mark:         |
| Implement a simple echo for testing | :heavy_check_mark:         |
| Timeout for connections not to hang forever| :heavy_check_mark:         |
| Handler the HTTP protocol | :bangbang: _in development_         |
| CGI | :bangbang: _in development_         |
| Configuration File | :bangbang: _in development_         |
| Virtual servers to handle many websites | :bangbang: _in development_         |
| Run on Linux | :heavy_check_mark:         |
| Run on Windows | :bangbang: _in development_         |

## Compile & Run

### Prerequisites

Before you begin, ensure you have met the following requirements:
- [ ] <code>make</code>
- [ ] <code>g++</code> (GNU Compiler Collection) or <code>clang</code>
- [ ] <code>valgrind</code> (It is not necessary for the program to work, but it is important to check for memory leaks in tests)
- [ ] You are in a Linux environment

### Compile

1. Download this repository: ``git clone --recurse-submodules https://github.com/phrxn/webserv.git``

2. After downloading, enter the project folder ``cd webserv``

3. Run ``make`` to compile the project

4. After running make, 2 executables will be created: ``webserv`` and ``cli`` (this one inside the tests_cli folder)

### Run

5. To run the webserv type: ``./webserv`` at this point the server will wait for clients.

**Important things**<br>
- By default the server will wait for clients on port 8080
- The Log is in DEBUG mode.
- To close the webserv just type CTRL+C.
- The server will echo every line sent to it. (The line must contain <code>\n</code> for the server to respond.)
- The timeout for inactivity is 10 seconds. (After 10 seconds of not sending anything to the server, it will close the connection)
- :bangbang:_These options will be configurable in the future. In the configuration file_

### How to connect?

To access the server you can, in a NEW terminal, use the command: ``telnet localhost 8080`` or use the executable (``cli``) inside the tests_cli folder.<br>
For now the server will echo everything that is sent to it after a <code>\n</code>
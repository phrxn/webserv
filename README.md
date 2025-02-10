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

2. As the project MUST BE written in C++98, but Google tests require at least the C++14 version two folder of objects are created

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
| CGI | :heavy_check_mark:         |
| Configuration File | :bangbang: _in development_         |
| Virtual servers to handle many websites | :heavy_check_mark:         |
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

3. Give execute permission to the build.sh script ``chmod 755 build.sh``

### The build script

The script build accept 3 options (parameters):

1. ``compile`` this command will compile the project (using c++98)<br>
	Example: ``./build compile``

2. ``tests`` this command will compile the tests and project (using c++17)<br>
	Example: ``./build tests``<br>
  This command also accepts one more parameter if you want to filter a Test Suite.<br>
	Example: ``./build tests MyTest``<br>

3. ``clean`` this command will remove things created during compilation (except the executable)<br>
	Example: ``./build clean``


4. After running ``./build compile``, one executable will be created: ``webserv``

### Run

5. To run the webserv type: ``./webserv`` at this point the server will wait for clients.

**Important things**<br>
- By default the server will wait for clients on port 8080
- The Log is in INFO mode.
- To close the webserv just type CTRL+C.
- The server will echo every line sent to it. (The line must contain <code>\n</code> for the server to respond.)
- The timeout for inactivity is 5 seconds. (After 5 seconds of not sending anything to the server, it will close the connection)
- :bangbang:_These options will be configurable in the future. In the configuration file_

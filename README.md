# Welcome to My Curl
***

## Task
The task was to create a `my_curl` command that is similar to UNIX command curl. This project is a tool to get data from a server, using HTTP. And it's designed to work without user interaction. This project demonstrates low-level network programming by implementing HTTP protocol handling using only basic socket operations.

## Description
`my_curl` fetches and displays HTML content from web servers using only basic socket operations and HTTP protocol handling. 

The URL parsing was implemented to extract the host, part, and path compomenets from HTTP URLs.

For network connection, I used `getaddrinfo()` for DNS resolution and to prepare the socket address. Then TCP connections were established using `socket()` adn `connect()` system calls.

The HTTP/1.1 requests were constructed with the proper headers. Parsing was implemented to separate the HTTP headers from the body.

Use with trusted servers only.

### Features
- Fetches HTML content from HTTP servers
- Supports both IP addresses and domain names (DNS resolution)
- Handles HTTP/1.1 protocol with proper headers
- Supports both Content-Length and chunked transfer encoding
- Memory-efficient buffer management
- Comprehensive error handling
- No external dependencies beyond standard C libraries

### Core Components
#### URL Parser
- Extracts protocol, host, port, and path from HTTP URLs
- Validates URL format and components
- Supports default HTTP port (80) and explicit port specifications

#### Network Layer
- Uses getaddrinfo() for DNS resolution
- Implements TCP socket connections with socket() and connect()
- Handles network byte order conversion
- Manages socket lifecycle and cleanup

#### HTTP Client
- Constructs HTTP/1.1 requests with required headers
- Parses HTTP responses, separating headers from body
- Supports Transfer-Encoding: chunked for streaming responses
- Implements Connection: close for proper session management

#### Response Handling
- State machine for chunked encoding decoding
- Buffer management for efficient data streaming
- Error detection and recovery mechanisms

## Installation
Clone the repo and move into the directory. From there, compile the code using `make`. 
```
git clone <repository-url>
cd my-curl
make
```
This will generate the my_curl executable in the project root directory.

## Usage
You can run the executable using the following command and format:
```
./my_curl <URL>
```
Example:
```
./my_curl http://example.com/
```

### The Core Team


<span><i>Made at <a href='https://qwasar.io'>Qwasar SV -- Software Engineering School</a></i></span>
<span><img alt='Qwasar SV -- Software Engineering School's Logo' src='https://storage.googleapis.com/qwasar-public/qwasar-logo_50x50.png' width='20px' /></span>

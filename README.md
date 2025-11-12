# Welcome to My Curl
***

## Task
The task was to create a `my_curl` command that is similar to UNIX command curl. This project is a tool to get data from a server, using HTTP. And it's designed to work without user interaction. It only supports HTTP.

## Description
`my_curl` fetches and displays HTML content from web servers using only basic socket operations and HTTP protocol handling. 

The URL parsing was implemented to extract the host, part, and path compomenets from HTTP URLs.

For network connection, I used `getaddrinfo()` for DNS resolution and to prepare the socket address. Then TCP connections were established using `socket()` adn `connect()` system calls.

The HTTP/1.1 requests were constructed with the proper headers. Parsing was implemented to separate the HTTP headers from the body.

## Installation
Clone the repo using `git clone` and move into the my_curl directory. From there, compile the code using `make`.

## Usage
You can run the code using the following command and format:
```
./my_curl <URL>
```

### The Core Team


<span><i>Made at <a href='https://qwasar.io'>Qwasar SV -- Software Engineering School</a></i></span>
<span><img alt='Qwasar SV -- Software Engineering School's Logo' src='https://storage.googleapis.com/qwasar-public/qwasar-logo_50x50.png' width='20px' /></span>

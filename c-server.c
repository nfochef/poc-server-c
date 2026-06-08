// Mini server with on C - PoC


// man socket - describes a socket address
// man sockaddr_in - describes an IPv4 In(in)ternet domain socket address 
// man bind - binding socket
// man sockaddr_in IPv4 address family, portnumber using hex number from python to reveal
// 0x1f90 = 0x901f
// man listen - for incoming connections
// man accept - accepting incoming string from client's
// man recv - receive mess form a socket  'buffer'
// man strchr - locating character in string
// man 2 open - to be able to open file with flag O_RDONLY (read only)
// man 2 sendfile - transfer data between file descriptors
// man 2 close - closes a file descriptor so it no longer refers to any file and may be reused. 


#include <sys/socket.h>
#include <netinet/in.h>
#include <string.h>
#include <fcntl.h>
#include <sys/sendfile.h>
#include <unistd.h>



void main(){
    int s = socket(AF_INET, SOCK_STREAM, 0);
    struct sockaddr_in addr = {
        AF_INET,
        0x901f,
        0
    };

    bind(s, &addr, sizeof(addr));

    listen(s, 5);

    int client_fd = accept(s, 0, 0);
    char buffer[512] = {0};
    recv(client_fd, buffer, 256, 0);

    //GET /file.html ...

    char* f = buffer + 5;
    *strchr(f, ' ') = 0;
    int opened_fd = open(f, O_RDONLY);
    sendfile(client_fd, opened_fd, 0, 512);
    close(opened_fd);
    close(client_fd);
    close(s);
}


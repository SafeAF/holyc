// nc like client
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <unistd.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <sys/select.h>


#define BUF_SIZE 4096

void die(const char *msg){
	perror(msg);
	exit(1);
}

int main(int argc, char *argv[]){

    char *host = argv[1];
    char *port = argv[2];   
    struct addrinfo hints, *res;
    int sock, err;

    memset(&hints, 0, sizeof hints);
    hints.ai_family = AF_INET;  // Force IPv4
    hints.ai_socktype = SOCK_STREAM;

    if ((err = getaddrinfo(host, port, &hints, &res)) != 0) {
        fprintf(stderr, "getaddrinfo: %s\n", gai_strerror(err));
        exit(1);
    }

    sock = socket(res->ai_family, res->ai_socktype, res->ai_protocol);
    if (sock < 0) die("socket");

    if (connect(sock, res->ai_addr, res->ai_addrlen) < 0) {
        die("connect");
    }

    freeaddrinfo(res);
    fprintf(stderr, "Connected to %s:%s\n", host, port);

    fd_set fds;
    char buf[BUF_SIZE];
    int maxfd = sock > STDIN_FILENO ? sock : STDIN_FILENO;

    while (1) {
        FD_ZERO(&fds);
        FD_SET(STDIN_FILENO, &fds);
        FD_SET(sock, &fds);

        if (select(maxfd + 1, &fds, NULL, NULL, NULL) < 0)
            die("select");

        if (FD_ISSET(STDIN_FILENO, &fds)) {
            ssize_t n = read(STDIN_FILENO, buf, sizeof buf);
            if (n <= 0) break;
            send(sock, buf, n, 0);
        }

        if (FD_ISSET(sock, &fds)) {
            ssize_t n = recv(sock, buf, sizeof buf, 0);
            if (n <= 0) break;
            write(STDOUT_FILENO, buf, n);
        }
    }

    close(sock);
}
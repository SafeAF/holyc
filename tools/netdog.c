// netdog.c - minimal netcat clone (TCP client and server)
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

void usage(const char *prog) {
    fprintf(stderr,
        "Usage:\n"
        "  %s host port         # connect to host:port\n"
        "  %s -l port           # listen on port\n", prog, prog);
    exit(1);
}

void die(const char *msg) {
    perror(msg);
    exit(1);
}

void client_mode(const char *host, const char *port) {
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

void server_mode(const char *port) {
    struct addrinfo hints, *res;
    int listenfd, connfd, err;
    struct sockaddr_storage their_addr;
    socklen_t sin_size;

    memset(&hints, 0, sizeof hints);
    hints.ai_family = AF_INET;  // Force IPv4
    hints.ai_socktype = SOCK_STREAM;
    hints.ai_flags = AI_PASSIVE;

    if ((err = getaddrinfo(NULL, port, &hints, &res)) != 0) {
        fprintf(stderr, "getaddrinfo: %s\n", gai_strerror(err));
        exit(1);
    }

    listenfd = socket(res->ai_family, res->ai_socktype, res->ai_protocol);
    if (listenfd < 0) die("socket");

    int yes = 1;
    if (setsockopt(listenfd, SOL_SOCKET, SO_REUSEADDR, &yes, sizeof yes) < 0)
        die("setsockopt");

    if (bind(listenfd, res->ai_addr, res->ai_addrlen) < 0)
        die("bind");

    if (listen(listenfd, 1) < 0)
        die("listen");

    fprintf(stderr, "Listening on port %s...\n", port);
    sin_size = sizeof their_addr;
    connfd = accept(listenfd, (struct sockaddr *)&their_addr, &sin_size);
    if (connfd < 0) die("accept");

    close(listenfd);
    fprintf(stderr, "Connection accepted.\n");

    fd_set fds;
    char buf[BUF_SIZE];
    int maxfd = connfd > STDIN_FILENO ? connfd : STDIN_FILENO;

    while (1) {
        FD_ZERO(&fds);
        FD_SET(STDIN_FILENO, &fds);
        FD_SET(connfd, &fds);

        if (select(maxfd + 1, &fds, NULL, NULL, NULL) < 0)
            die("select");

        if (FD_ISSET(STDIN_FILENO, &fds)) {
            ssize_t n = read(STDIN_FILENO, buf, sizeof buf);
            if (n <= 0) break;
            send(connfd, buf, n, 0);
        }

        if (FD_ISSET(connfd, &fds)) {
            ssize_t n = recv(connfd, buf, sizeof buf, 0);
            if (n <= 0) break;
            write(STDOUT_FILENO, buf, n);
        }
    }

    close(connfd);
}

int main(int argc, char *argv[]) {
    if (argc == 3 && strcmp(argv[1], "-l") == 0) {
        server_mode(argv[2]);
    } else if (argc == 3) {
        client_mode(argv[1], argv[2]);
    } else {
        usage(argv[0]);
    }
    return 0;
}

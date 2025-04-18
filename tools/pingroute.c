// Enhanced MTR-like tool in C with stats: min/avg/max/packet loss
// Compile: gcc -o minitraceroute_stats minitraceroute_stats.c
// Run with root or: sudo setcap cap_net_raw+ep ./minitraceroute_stats

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>
#include <sys/socket.h>
#include <sys/time.h>
#include <netinet/ip_icmp.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>

#define MAX_HOPS 30
#define TIMEOUT_SEC 2
#define PROBES_PER_HOP 5

uint16_t checksum(void *b, int len) {
    uint16_t *buf = b;
    uint32_t sum = 0;
    for (; len > 1; len -= 2)
        sum += *buf++;
    if (len == 1)
        sum += *(uint8_t *)buf;
    sum = (sum >> 16) + (sum & 0xFFFF);
    return ~sum;
}

double time_diff_ms(struct timeval start, struct timeval end) {
    return (end.tv_sec - start.tv_sec) * 1000.0 +
           (end.tv_usec - start.tv_usec) / 1000.0;
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <destination IP or hostname>\n", argv[0]);
        exit(1);
    }

    struct sockaddr_in dest;
    memset(&dest, 0, sizeof(dest));
    dest.sin_family = AF_INET;

    if (inet_aton(argv[1], &dest.sin_addr) == 0) {
        struct hostent *host = gethostbyname(argv[1]);
        if (!host) {
            perror("gethostbyname");
            exit(1);
        }
        memcpy(&dest.sin_addr, host->h_addr, host->h_length);
    }

    printf("Tracing route to %s\n\n", inet_ntoa(dest.sin_addr));
    printf("Hop IP Address        Loss %%  Min    Avg    Max\n");

    int sock = socket(AF_INET, SOCK_RAW, IPPROTO_ICMP);
    if (sock < 0) {
        perror("socket");
        exit(1);
    }

    struct timeval timeout = {TIMEOUT_SEC, 0};
    setsockopt(sock, SOL_SOCKET, SO_RCVTIMEO, &timeout, sizeof(timeout));

    for (int ttl = 1; ttl <= MAX_HOPS; ttl++) {
        setsockopt(sock, IPPROTO_IP, IP_TTL, &ttl, sizeof(ttl));

        int received = 0;
        double times[PROBES_PER_HOP];
        struct sockaddr_in reply_addr;
        memset(&reply_addr, 0, sizeof(reply_addr));

        for (int i = 0; i < PROBES_PER_HOP; i++) {
            struct icmphdr icmp;
            memset(&icmp, 0, sizeof(icmp));
            icmp.type = ICMP_ECHO;
            icmp.un.echo.id = getpid() & 0xFFFF;
            icmp.un.echo.sequence = (ttl << 8) + i;
            icmp.checksum = checksum(&icmp, sizeof(icmp));

            struct timeval send_time;
            gettimeofday(&send_time, NULL);

            sendto(sock, &icmp, sizeof(icmp), 0, (struct sockaddr *)&dest, sizeof(dest));

            char buf[512];
            socklen_t addr_len = sizeof(reply_addr);

            if (recvfrom(sock, buf, sizeof(buf), 0, (struct sockaddr *)&reply_addr, &addr_len) >= 0) {
                struct timeval recv_time;
                gettimeofday(&recv_time, NULL);
                times[received++] = time_diff_ms(send_time, recv_time);
            }
        }

        if (received == 0) {
            printf("%2d  *                  100%%   ---    ---    ---\n", ttl);
            continue;
        }

        double min = times[0], max = times[0], sum = 0;
        for (int i = 0; i < received; i++) {
            if (times[i] < min) min = times[i];
            if (times[i] > max) max = times[i];
            sum += times[i];
        }

        double avg = sum / received;
        double loss = ((PROBES_PER_HOP - received) * 100.0) / PROBES_PER_HOP;
        printf("%2d  %-16s %5.1f%%  %.1fms %.1fms %.1fms\n", ttl, inet_ntoa(reply_addr.sin_addr), loss, min, avg, max);

        if (reply_addr.sin_addr.s_addr == dest.sin_addr.s_addr) {
            printf("Reached destination.\n");
            break;
        }
    }

    close(sock);
    return 0;
}

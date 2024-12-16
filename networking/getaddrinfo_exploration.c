// getaddrinfo exploration

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include <netdb.h>
#include <arpa/inet.h>
#include <netinet/in.h>


int main(int argc, const char **argv){
	struct addrinfo *addr, *result;
	const char ** ptr;

	int rc;

	struct addrinfo hints;
	const char *serviceName = NULL;
	const char *hostName = "localhost";

	memset(&hints, 0, sizeof(hints));

	hints.ai_family = AF_INET;
	hints.ai_socktype = SOCK_STREAM;
	hints.ai_flags = AI_ADDRCONFIG;
	hints.ai_protocol = IPPROTO_TCP;

	rc = getaddrinfo(hostName, serviceName, &hints, &result);

	addr = result;

	while(addr){
		char ipstr[INET6_ADDRSTRLEN];
		void *addr_ptr = &((struct sockaddr_in *)addr->ai_addr)->sin_addr;
		inet_ntop(addr->ai_family, addr_ptr, ipstr, sizeof(ipstr));

		printf("IP Addr: %s\n", ipstr);
		addr = addr->ai_next;
	}

	freeaddrinfo(result);
	return 0;
}
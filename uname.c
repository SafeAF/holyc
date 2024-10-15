#include <stdio.h>
#include <sys/utsname.h>

int main(){
	struct utsname buffer;

	if(uname(&buffer) != 0){
		perror("uname");
		return 1;
	}

	printf("System name: %s\n", buffer.sysname);
	printf("Node name: %s\n", buffer.nodename);
}
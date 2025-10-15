// debugger.c 
// using ptrace
// usage: find an address to break on
// objdump -d /bin/ls | grep main
// run with ./debugger /bin/ls 0xADDRESS

// compile programs with no pie to prevent symbol stripping
//gcc -no-pie -g -o testprog testprog.c

// future features: 
// Attach to a running PID instead of spawning?
// Support symbol lookup?
// Dump memory regions?
// Add single-step mode?
// Load ELF symbols
// Auto-locate main or printf
// Disassemble bytes around breakpoints
// Or inject code!
// use dlysym() to get offsets dynamically

// things to look into for knowledge
// dif between PIE and non-PIE bins

#include <sys/ptrace.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/user.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

void run_debuggee(const char* program){
	ptrace(PTRACE_TRACEME, 0, NULL, NULL);
	execl(program, program, NULL);
}

void run_debugger(pid_t child_pid, unsigned long addr){
	int wait_status;
	waitpid(child_pid, &wait_status, 0);

	// lx to print lowercase hex, # adds 0x prefix
	printf("Inserting breakpoint at %#lx", addr);

	long orig_data = ptrace(PTRACE_PEEKTEXT, 
		child_pid, (void *)addr, NULL);

	// dig into this more. and with the opposite of 0xFF
	// and or the result with 0xCC should nuke the value
	// and populate the last byte with 0xCC the
	// INT3 cpu breakpoint instruction 
	long breakpoint = (orig_data & ~0xFF) | 0xCC;

	ptrace(PTRACE_POKETEXT, child_pid, (void*)addr,
			(void *)breakpoint);


	ptrace(PTRACE_CONT, child_pid, NULL, NULL);
	waitpid(child_pid, &wait_status, 0);

	printf("Breakpoint hit\n");
	// dump registers
	struct user_regs_struct regs;
	ptrace(PTRACE_GETREGS, child_pid, NULL, &regs);
	printf("RIP = %llx\n", regs.rip);
	printf("RAX:  0x%llx\n", regs.rax);
	printf("ORIG_RAX: 0x%llx\n", regs.orig_rax);
	printf("RCX:  0x%llx\n", regs.rcx);
	printf("RDX:  0x%llx\n", regs.rdx);
	printf("RSI:  0x%llx\n", regs.rsi);
	printf("RDI:  0x%llx\n", regs.rdi);
	printf("RBP:  0x%llx\n", regs.rbp);
	printf("RBX:  0x%llx\n", regs.rbx);
	// restore original instruction

	ptrace(PTRACE_POKETEXT, child_pid, (void *)addr,
		(void *)orig_data);

	regs.rip -= 1;
	ptrace(PTRACE_SETREGS, child_pid, )
}

// setup for auto resolution of addresses for functions like main
// get base address of libc from /proc/<pid>/maps
// also: objdump -d /lib/x86_64-linux-gnu/libc.so.6 | grep "<printf>"
unsigned long get_libc_base(pid_t pid){
	// open file
	char path[64];
	snprintf(path, sizeof(path), "/proc/%d/maps", pid);
	FILE *maps = fopen(path, "r");
	if(!maps){
		perror("fopen");
		exit(1);
	}
	// pull out 256 byte chunks looking for libc
	char line[256];
	while(fgets(line, sizeof(line), maps)){
		if(strstr(line, "libc") && strstr(line, "r-xp")){
			unsigned long addr;
			sscanf(line, "%lx", &addr);
			fclose(maps);
			return addr;
		}
	}
	fclose(maps);
	fprintf(stderr, "Could not find libc base in maps\n");
	exit(1);
}

int main(int argc, char *argv[]){
	if(argc < 3){
		fprintf(stderr, "Usage: %s <pid> <hex_addr>\n", argv[0]);
	}

	char *endptr; // used to validate conversion succeeded
	// base 16 for hex
	unsigned long addr = strtoul(argv[2], &endptr, 16);

	if (*endptr != '\0') {
    	fprintf(stderr, "Invalid address: %s\n", argv[2]);
    	exit(1);
	}

	pid_t child_pid = fork();
	if(child_pid == 0){
		run_debuggee(argv[1]);
	}
	else {
		run_debugger(child_pid, addr);
	}
	return 0;
}

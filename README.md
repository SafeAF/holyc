# C Mastery Roadmap: From Advanced to Chad-Level

## 🛠️ Phase 1: Mastery of Internals (Advanced Systems Foundations)

### Memory Management
- [x] Manual `malloc`/`free` basics
- [x] Write your own dynamic array
- [x] Use and abuse `memcpy`, `memset`, `memmove`
- [ ] Write your own malloc/free using a freelist
- [ ] Add `sbrk()`/`mmap()`-backed pages
- [ ] Implement slab allocator / buddy system
- [ ] Add malloc metadata corruption detection

### File & Process Primitives
- [ ] Learn `mmap`, `munmap`, `mprotect`, `fork`, `execve`, `pipe`, `dup2`
- [ ] Signal handling: `sigaction`, `sigsetjmp`, `siglongjmp`
- [ ] IPC: shared memory, message queues, UNIX sockets

---

## ⚙️ Phase 2: Operating System and Runtime Awareness

### Deep Dive Projects
- [ ] ELF Loader (parse and simulate ELF loading and symbol resolution)
- [ ] Write a toy libc with `puts`, `malloc`, `printf`
- [ ] Simulate system calls (via `ptrace` or `LD_PRELOAD`)

### Concepts to Internalize
- [ ] Calling conventions: x86-64 ABI
- [ ] Stack frames and prologue/epilogue mechanics
- [ ] Register calling vs stack calling
- [ ] Function pointer dispatch and vtable simulation
- [ ] GOT/PLT, relocations, and dynamic linking

---

## 🧨 Phase 3: Exploitation Awareness and Defense

### Exploit Simulations
- [x] Use-after-free
- [ ] Stack overflow → return address overwrite
- [ ] Heap overflow → fake chunk & tcache poisoning
- [ ] Format string → arbitrary write/read
- [ ] ROP chain with `setuid(0); execve("/bin/sh",...)`

### Hardened Defense:
- [ ] Compile with stack canaries (`-fstack-protector`)
- [ ] Enable PIE/ASLR (`-fPIE`, `-pie`)
- [ ] Enable RELRO (`-Wl,-z,relro,-z,now`)
- [ ] Use Valgrind, AddressSanitizer, GDB, `strace`, `ltrace`

---

## 🖥️ Phase 4: Bare Metal & Embedded

### Low-Level Hardware Work
- [ ] Write a bootloader in C (link with NASM)
- [ ] Blink an LED with C on a microcontroller (e.g., STM32 or AVR)
- [ ] Access hardware registers and I/O memory directly
- [ ] Use linker scripts to control memory layout

---

## 🧰 Phase 5: Build Real Stuff

### Projects
- [x] Write a memory allocator ✅
- [ ] Make a game engine or emulator (CHIP-8, NES, etc.)
- [ ] Implement a minimal TCP/IP stack (raw sockets or userland)
- [ ] Write a Forth or Lisp interpreter in C
- [ ] Build a kernel module or bootable OS with multitasking

---

## 📚 Resources

| Topic | Resource |
|-------|----------|
| Linux Internals | *The Linux Programming Interface* by Michael Kerrisk |
| Linkers/Loaders | *Linkers and Loaders* by John R. Levine |
| Exploitation | *Hacking: The Art of Exploitation* by Jon Erickson |
| Embedded | *Embedded C* by Michael Pont |
| C Idioms | *21st Century C* by Ben Klemens |
| Tooling | `readelf`, `objdump`, `gdb`, `valgrind`, `ltrace`, `strace` |

---

## 🧙 Phase 6: Final Boss Level – Craft and Combat

- [ ] Build a language that compiles to C
- [ ] Write a JIT compiler (e.g., for a stack-based VM)
- [ ] Write a debugger using `ptrace()`
- [ ] Implement cooperative multitasking/scheduler
- [ ] Write a file system in userspace with FUSE

---

> "If it ain't got pointers, it's just scripting."


Phase 3: Advanced Topics

1. Advanced Pointers
  -Pointer to pointer (double pointers)
  -Function pointers and their use cases
  -Pointers and dynamic data structures (linked lists, trees)
  -Pointer-related issues (dangling, wild, and null pointers)

2. Data Structures in C
  -Linked lists (singly, doubly, circular)
  -Stacks and queues (implementation using arrays and linked lists)
  -Trees (binary trees, binary search trees)
  -Graphs (basic introduction, adjacency matrix, and list)
  -Hashing (hash tables, collision resolution techniques)

3. Advanced Memory Management
  -Memory allocation strategies (stack vs. heap)
  -Custom memory allocators
  -Garbage collection basics
  -Implementing memory pools

4. Preprocessor Directives
  -Macros and macro functions
  -Conditional compilation
  -Include guards and the use of #define (it is not a hashtag 😅)
  -Creating and using header files

Phase 4: Expert-Level Topics

1. Advanced C Concepts
  -Bitwise manipulation and operations
  -Working with hardware and low-level programming (registers, ports)
  -Writing and using inline assembly within C
  -Creating and using libraries (static and dynamic)
  -Interfacing with other languages (e.g., using C in Python with ctypes)

2. Concurrency in C
  -Introduction to concurrency and parallelism
  -Multithreading with pthreads (POSIX threads)
  -Synchronization (mutexes, semaphores, condition variables)
  -Thread safety and race conditions

3. Network Programming in C
  -Sockets and socket programming
  -Client-server architecture
  -TCP/IP and UDP protocols
  -Handling multiple clients (select, poll, epoll)

4. Real-Time Operating Systems (RTOS)
  -Basics of RTOS and their use cases
  -Writing programs for RTOS
  -Inter-task communication
  -Task scheduling and real-time constraints

Phase 5: Mastery and Specialization

1. Algorithms and Data Structures in C
  -Sorting and searching algorithms
  -Dynamic programming and greedy algorithms
  -Graph algorithms (Dijkstra, A*, DFS, BFS)
  -Advanced data structures (trie, AVL trees, red-black trees)

2. System Programming 
  -Understanding OS-level concepts (processes, threads, memory management)
  -Writing system-level programs (creating and managing processes, IPC)
  -Unix/Linux system calls (fork, exec, pipe, signals)
  -Working with the Linux kernel

3. Embedded Systems Programming
  -Basics of embedded systems and microcontrollers
  -Programming microcontrollers in C
  -Interfacing with peripherals (GPIO, UART, SPI, I2C)
  -Writing device drivers

4. Optimization and Debugging
  -Code profiling and optimization techniques
  -Using debugging tools (gdb, valgrind)
  -Writing and running test cases
  -Optimizing for memory and performance

Phase 6: Project-Based Learning

1. Small Projects
  -Implementing a basic shell
  -Creating a simple text editor
  -Building a basic HTTP server

2. Medium Projects
  -Developing a database management system (miniature)
  -Writing a networked chat application
  -Implementing a simple operating system kernel

3. Large Projects
  -Contributing to open-source C projects (e.g., the Linux kernel)
  -Writing your own C compiler or interpreter
  -Creating a fully-featured real-time operating system
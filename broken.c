#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Broken.c
// Exploring memory leaks, overflows, and underflows.


int broken(){
	char *dyn;
	char local[5];

	// overwrite buffer a scosche
	// dyn = malloc(5);
	// strcpy(dyn, "12345");

	// Result

	// broken.c: In function ‘broken’:
	// broken.c:14:9: warning: ‘__builtin_memcpy’ writing 6 bytes into a region of size 5 overflows the destination [-Wstringop-overflow=]
	//    14 |         strcpy(dyn, "12345");
	//       |         ^~~~~~~~~~~~~~~~~~~~
	// broken.c:13:15: note: destination object of size 5 allocated by ‘malloc’
	//    13 |         dyn = malloc(5);
	//       |               ^~~~~~~~~

	// Improvements in the compiler since Linux Application Development
	// was published in 2004? Book says it compiles and runs.

	// walk past the beginning of a malloced buffer (underflow)

	// *(dyn - 1) = '\0';

	// Result
	// Seg fault

	// overflow local var (stack variable)

	// strcpy(local, "12345");

	// Result
	// 	broken.c: In function ‘broken’:
	// broken.c:40:9: warning: ‘__builtin_memcpy’ writing 6 bytes into a region of size 5 overflows the destination [-Wstringop-overflow=]
	//    40 |         strcpy(local, "12345");
	//       |         ^~~~~~~~~~~~~~~~~~~~~~
	// broken.c:12:14: note: destination object ‘local’ of size 5
	//    12 |         char local[5];
	//       |              ^~~~~

	// underflow of stack var is not caught
	strcpy(local, "1234");
	local[-1] = '\0';
	printf("%s\n", local);

	return 0;
}



int main(){
	return broken();
}


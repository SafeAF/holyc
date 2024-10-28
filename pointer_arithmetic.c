// pointer arithmetic

#include <stdio.h>



typedef struct {
	int size;
	char data[64];
} Datum;

int main(){
	Datum dat[100];

	Datum *p_dat = &dat[0];

	for(int i=0; i<100; i++){
		p_dat->size = 5;
		p_dat += 1;
		p_dat->data = "foo " x i

		printf("Struct member[%d]: Struct data->[%s]\n", i, p_dat[i].data);
	}
}
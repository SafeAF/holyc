// 2 d array

#include <stdio.h>
#include <stdlib.h>


int main(){
  int rows = 3;
  int cols = 4;

  int **table;

  table = malloc(sizeof(int) * rows);

  for(int i=0; i<rows; i++){
  	table[i] = malloc(sizeof(int) * cols);
  }

  for(int i=0; i<rows; i++){
  	for(int j=0; j<cols; j++){
  		table[i][j] = i + 3 * j;
  	}
  }

  printf("%d", table[2][3]);
}



































// int main(){
// 	int rows = 3;
// 	int cols = 4;
	
// 	int ** table;

// 	table = malloc(rows * sizeof(int));

// 	for(int i = 0; i < rows; i++){
// 		table[i] = malloc(cols * sizeof(int));
// 	}	

// 	for(int i=0; i<rows; i++){
// 		for(int j = 0; j < rows; j++){
// 			table[i][j] = i * cols + j;
// 		}
// 	}

// 	printf("%d\n", table[1][2]);
// }
// compound literals


#include <stdio.h>

typedef struct {
	int x;
	int y;
} Point;

void print_point(Point p) {
    printf("x = %d, y = %d\n", p.x, p.y);
}


int main(){
	int *ptr = (int[]) { 1, 2, 3, 4};

	printf("%d\n", ptr[1]);


	// example with structs

	Point p = (Point) { .x = 10, .y = 20};

	printf("x=%d y=%d\n", p.x, p.y);


	print_point((Point) { .x = 5, .y = 10 });
}
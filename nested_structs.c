#include <stdio.h>


typedef struct Point {
	int x;
	int y;
} Point;


typedef struct Rectangle {
	struct Point top_left;
	struct Point bottom_right;
} Rectangle;


int main(){
Rectangle rect = {{0,0}, {200,200}};

printf("Rectangle: (%d, %d) to (%d, %d)\n",
		rect.top_left.x, rect.top_left.y,
		rect.bottom_right.x, rect.bottom_right.y);
}


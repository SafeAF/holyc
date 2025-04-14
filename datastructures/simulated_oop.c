// simulated oop with structs and function pointers

#include <stdio.h>

typedef struct Point {
	int dx;
	int dy;
	void (*move)(struct Point *self, int dx, int dy); 
} Point;

void point_move(Point *self, int dx, int dy){
	self->x += dx;
	self->y += dy;
}

Point new_point(int x, int y) {
	Point p = { x, y, point_move};
	return p;
}


int main(){
	Point p = new_point(10, 20);
	p.move(&p, 5, -1);
	printf("Point at (%d, %d)\n", p.x, p.y);
}
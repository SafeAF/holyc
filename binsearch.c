// binsearch


// determine if an element is in a sorted array by
// slicing the array into to parts and checking the midpoint
// if target element is greater than midpoint discard left
// side, if lesser discard right side. Repeat the process 
// until it is found or run out of elements.

#include <stdio.h>


int binsearch(int * ary, int left, int right, int target){
	while(left <= right){
	int mid = left + (right - left) / 2;

	if(ary[mid] == target){
		return mid;
	}

	if(ary[mid] < target){
		left = mid + 1;
	}
	else{
		right = mid - 1; 
	}
}
	return -1; // not found

}


int main(){
	int sorted[] = {1, 4, 6, 13, 22, 51, 71};

	int target = 22;
	int n = sizeof(sorted) / sizeof(sorted[0]);
	int result = binsearch(sorted, 0, n - 1, target);
	if(result == -1 ){
		printf("target %d not found", target);
	}
	else {
		printf("target %d found", target);
	}
}
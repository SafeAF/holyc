#include <stdio.h>


#define foreach(item, array) \
    for (int keep = 1, count = 0, size = sizeof(array)/sizeof(*(array)); keep && count != size; keep = !keep, count++) \
        for (item = (array)[count]; keep; keep = !keep)

int main() {
    int arr[] = {1, 2, 3, 4};
    int x;
    foreach(x, arr) {
        printf("%d\n", x);
    }
}
#include <stdio.h>
//#include <stdlib.h>
#include <string.h>

// Define a simple map structure
typedef struct {
    const char *key;
    void (*function)();
} FunctionMapEntry;

void process_start() {
    printf("Process started.\n");
}

void process_data() {
    printf("Processing data.\n");
}

void process_finish() {
    printf("Process finished.\n");
}

// Define a function map (hash map)
FunctionMapEntry function_map[] = {
    {"start", process_start},
    {"data", process_data},
    {"finish", process_finish}
};

// Helper function to find the function in the map
void call_function_by_key(const char *key) {
    for (size_t i = 0; i < sizeof(function_map) / sizeof(FunctionMapEntry); i++) {
        if (strcmp(function_map[i].key, key) == 0) {
            function_map[i].function();
            return;
        }
    }
    printf("Invalid key: %s\n", key);
}

int main() {
    char key[] = "data";
    call_function_by_key(key);  // Dynamically dispatch function based on string key

    return 0;
}



// // void pointers
// #include <stddef.h>
// #include <stdint.h>
// #include <stdio.h>


// int main(){
// 	int a = 3;
// 	void *p = &a;

// 	char b[1] = {'z'};

// 	printf("%p\n", b);
// 	printf("%d\n", sizeof(b));
// }


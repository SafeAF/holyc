#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char name[32];
    void (*print_func)();
} User;

// Original print function
void safe_print() {
    printf("This is a safe print.\n");
}

// Attacker's malicious function
void malicious_code() {
    printf("🔥 Attacker's code executed! 🔥\n");
}

int main() {
    User *user = malloc(sizeof(User));
    if (!user) {
        perror("malloc failed");
        exit(1);
    }

    strcpy(user->name, "Alice");
    user->print_func = safe_print;

    printf("Before free: %s\n", user->name);
    user->print_func();

    // Free the user (UAF vulnerability begins here)
    free(user);

    // Attacker now forces an allocation of the same size
    char *attacker_buf = malloc(sizeof(User));
    if (!attacker_buf) {
        perror("malloc failed");
        exit(1);
    }

    // Attacker overwrites the freed memory with malicious data
    memset(attacker_buf, 0, sizeof(User));
    void (**fake_func_ptr)() = (void (**)())(attacker_buf + 32);
    *fake_func_ptr = malicious_code;

    // Use-after-free: using the stale pointer `user`
    printf("After free (UAF): %s\n", user->name);
    user->print_func();  // ❌ Now calls attacker's code

    // Cleanup
    free(attacker_buf);

    return 0;
}

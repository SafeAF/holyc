// simple cuda element-wise addition
// requires nvcc to compile and run

#include <stdio.h>


__global__ void add(int *a, int *b, int *c, int n) {
    int index = threadIdx.x;
    if (index < n) {
        c[index] = a[index] + b[index];
    }
}

int main() {
    const int n = 5;
    int h_a[n] = {1, 2, 3, 4, 5};   // Host input array a
    int h_b[n] = {10, 20, 30, 40, 50}; // Host input array b
    int h_c[n]; // Host output array c

    int *d_a, *d_b, *d_c; // Device pointers

    // Allocate device memory
    cudaMalloc((void**)&d_a, n * sizeof(int));
    cudaMalloc((void**)&d_b, n * sizeof(int));
    cudaMalloc((void**)&d_c, n * sizeof(int));

    // Copy inputs to device
    cudaMemcpy(d_a, h_a, n * sizeof(int), cudaMemcpyHostToDevice);
    cudaMemcpy(d_b, h_b, n * sizeof(int), cudaMemcpyHostToDevice);

    // Launch the kernel on the GPU
    add<<<1, n>>>(d_a, d_b, d_c, n);

    // Copy result back to host
    cudaMemcpy(h_c, d_c, n * sizeof(int), cudaMemcpyDeviceToHost);

    // Print the result
    printf("Result:\n");
    for (int i = 0; i < n; i++) {
        printf("%d + %d = %d\n", h_a[i], h_b[i], h_c[i]);
    }

    // Free device memory
    cudaFree(d_a);
    cudaFree(d_b);
    cudaFree(d_c);

    return 0;
}
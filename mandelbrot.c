#include <stdio.h>
#include <stdlib.h>
#include <SDL2/SDL.h>

#define WIDTH 800
#define HEIGHT 600
#define MAX_ITER 1000

// Function to compute whether a point belongs to the Mandelbrot set
int mandelbrot(double x0, double y0) {
    double x = 0.0;
    double y = 0.0;
    int iter = 0;
    
    while (x*x + y*y <= 4.0 && iter < MAX_ITER) {
        double xtemp = x*x - y*y + x0;
        y = 2*x*y + y0;
        x = xtemp;
        iter++;
    }
    return iter;
}

// Function to map pixel coordinates to the complex plane
double map(double value, double start1, double stop1, double start2, double stop2) {
    return start2 + (stop2 - start2) * ((value - start1) / (stop1 - start1));
}

// Function to set pixel in SDL texture
void set_pixel(SDL_Renderer *renderer, int x, int y, int r, int g, int b) {
    SDL_SetRenderDrawColor(renderer, r, g, b, 255);
    SDL_RenderDrawPoint(renderer, x, y);
}

int main(int argc, char* argv[]) {
    // Initialize SDL
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        fprintf(stderr, "Could not initialize SDL: %s\n", SDL_GetError());
        return 1;
    }

    // Create SDL window and renderer
    SDL_Window *window = SDL_CreateWindow("Mandelbrot Fractal", 
                                          SDL_WINDOWPOS_CENTERED, 
                                          SDL_WINDOWPOS_CENTERED, 
                                          WIDTH, HEIGHT, 
                                          SDL_WINDOW_SHOWN);
    if (!window) {
        fprintf(stderr, "Could not create window: %s\n", SDL_GetError());
        SDL_Quit();
        return 1;
    }

    SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (!renderer) {
        fprintf(stderr, "Could not create renderer: %s\n", SDL_GetError());
        SDL_DestroyWindow(window);
        SDL_Quit();
        return 1;
    }

    // Variables for the complex plane
    double minRe = -2.0, maxRe = 1.0;
    double minIm = -1.2, maxIm = minIm + (maxRe - minRe) * HEIGHT / WIDTH;

    // Generate the Mandelbrot fractal
    for (int y = 0; y < HEIGHT; y++) {
        for (int x = 0; x < WIDTH; x++) {
            // Map the pixel coordinates to the complex plane
            double a = map(x, 0, WIDTH, minRe, maxRe);
            double b = map(y, 0, HEIGHT, minIm, maxIm);
            
            // Compute the Mandelbrot value
            int iter = mandelbrot(a, b);
            
            // Choose color based on iteration count
            int color = map(iter, 0, MAX_ITER, 0, 255);
            set_pixel(renderer, x, y, color % 8 * 32, color % 16 * 16, color % 32 * 8);
        }
    }

    // Show the rendered fractal
    SDL_RenderPresent(renderer);

    // Wait for user to close the window
    int quit = 0;
    SDL_Event event;
    while (!quit) {
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                quit = 1;
            }
        }
    }

    // Clean up
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}

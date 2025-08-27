#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <SDL2/SDL.h>

#include "ball.h"
#include "bar.h"

int width = 640;
int height = 480;

int running = 0;
Uint32 ticks = 0;
Uint32 fps = 60;
float delta_time = 0;

SDL_Window* window;



Ball ball;
Bar bar;


void* poll_events(void* arg) {
    printf("Starting event polling thread.\n");

    SDL_Renderer* renderer;

    while (running == 1) {
        SDL_Event ev;
        SDL_PollEvent(&ev);

        if (ev.type == SDL_QUIT) running = 0;
        if (ev.type == SDL_WINDOWEVENT) {
            if (ev.window.event == SDL_WINDOWEVENT_RESIZED) SDL_GetWindowSize(window, &width, &height);
        }
        if (ev.type == SDL_KEYDOWN) {
            if (ev.key.keysym.sym == SDLK_w) move_bar(&bar, -1);
            if (ev.key.keysym.sym == SDLK_s) move_bar(&bar,  1);
        }
        if (ev.type == SDL_KEYUP) bar.vy = 0;
    }
}


void* render_graphics(void* arg) {
    printf("Starting rendering thread.\n");

    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

    if (renderer == NULL) {
        printf("Error: Could not create the renderer.");
    }

    while (running == 1) {
        SDL_SetRenderDrawColor(renderer, 60, 100, 255, 255);
        SDL_RenderClear(renderer);

        SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
        SDL_Rect rect = {ball.x, ball.y, ball.w, ball.h};
        SDL_RenderFillRect(renderer, &rect);

        SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
        SDL_Rect rect2 = {bar.x, bar.y, bar.w, bar.h};
        SDL_RenderFillRect(renderer, &rect2);

        SDL_RenderPresent(renderer);
    }

    SDL_DestroyRenderer(renderer);
}


int main(int argc, char *argv[]) {
    printf("Classic Pong.\n");

    SDL_Init(SDL_INIT_VIDEO);

    window = SDL_CreateWindow(
        "Pong",
        SDL_WINDOWPOS_CENTERED,
        SDL_WINDOWPOS_CENTERED,
        width, height,
        SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE
    );

    if (window == NULL) {
        printf("Error: Could not create a window.");
        return -1;
    }

    ball = create_ball(width / 2, height / 2);
    
    ball.ay = 100;
    ball.vx = 250;
    ball.vy = 100;

    bar = create_bar(5, height / 2);

    running = 1;

    pthread_t poll_events_t;
    pthread_create(&poll_events_t, NULL, poll_events, NULL);
    pthread_detach(poll_events_t);

    pthread_t render_graphics_t;
    pthread_create(&render_graphics_t, NULL, render_graphics, NULL);
    pthread_detach(render_graphics_t);

    while (running == 1) {
        delta_time = (SDL_GetTicks() - ticks) / 1000.;
        ticks = SDL_GetTicks();

        // Physics logic.
        update_ball(&ball, delta_time);
        keep_ball_inbounds(&ball, width, height);

        update_bar(&bar, delta_time);
        keep_bar_inbounds(&bar, height);
    }

   
    SDL_DestroyWindow(window);

    SDL_Quit();

    return 0;
}
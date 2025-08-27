#include "bar.h"

Bar create_bar(float x, float y) {
    Bar bar;

    bar.x = x;
    bar.y = y - 50;
    bar.w = 15;
    bar.h = 100;
    bar.vy = 0;
    bar.speed = 1000;

    return bar;
}

void update_bar(Bar* bar, float delta_time) {
    bar->y += bar->vy * delta_time;
}

void move_bar(Bar* bar, int direction) {
    bar->vy = bar->speed * direction;
}

void keep_bar_inbounds(Bar* bar, int height) {
    if (bar->y <= 5 && bar->vy < 0) {
        bar->y = 5;
        bar->vy = 0;
    }
    
    if (bar->y + bar->h >= height - 5 && bar->vy > 0) {
        bar->y = height - bar->h - 5;
        bar->vy = 0;
    }
}
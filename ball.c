#include "ball.h"


Ball create_ball(float x, float y) {
    Ball ball;

    ball.x = x;
    ball.y = y;
    ball.w = 30;
    ball.h = 30;
    ball.vx = 0;
    ball.vy = 0;
    ball.ax = 0;
    ball.ay = 0;

    return ball;
}

void keep_ball_inbounds(Ball* ball, int width, int height) {
    if (ball->x + ball->w >= width  && ball->vx > 0) ball->vx *= -1;
    if (ball->y + ball->h >= height && ball->vy > 0) ball->vy *= -1;
    if (ball->x <= 0 && ball->vx < 0) ball->vx *= -1;
    if (ball->y <= 0 && ball->vy < 0) ball->vy *= -1;
}

void update_ball(Ball* ball, float delta_time) {
    ball->vx += ball->ax * delta_time;
    ball->vy += ball->ay * delta_time;

    ball->x += ((ball->ax * delta_time) + ball->vx) * delta_time;
    ball->y += ((ball->ay * delta_time) + ball->vy) * delta_time;
}
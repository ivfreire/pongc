#ifndef BALL_H
#define BALL_H

typedef struct Ball {
    float x, y, w, h;
    float vx, vy;
    float ax, ay;
} Ball;

Ball create_ball(float x, float y);

void update_ball(Ball* ball, float delta_time);

void keep_ball_inbounds(Ball* ball, int width, int height);

#endif
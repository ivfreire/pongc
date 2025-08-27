#ifndef BAR_H
#define BAR_H

typedef struct Bar {
    float x, y, w, h;
    float vy;
    float speed;
} Bar;

Bar create_bar(float x, float y);

void update_bar(Bar* bar, float delta_time);

void move_bar(Bar* bar, int direction);

void keep_bar_inbounds(Bar* bar, int height);

#endif
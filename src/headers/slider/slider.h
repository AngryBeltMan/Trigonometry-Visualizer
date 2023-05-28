#include <stdbool.h>
#ifndef  SLIDER
#define SLIDER
typedef struct Slider {
    float progress;
    float x;
    float y;
    bool moving;
} Slider;
#endif
Slider create_slider(int x,int y);
void draw_slider(Slider *slider);
void update_slider(Slider*slider);

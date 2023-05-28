#include "slider.h"
#include "raylib.h"
#include <stdio.h>
#define SLIDERWIDTH 300
#define SLIDERHEIGHT 20
void draw_slider(Slider *slider) {
    DrawRectangleV((Vector2){slider->x,slider->y}, (Vector2){300,20}, LIGHTGRAY);
    DrawCircleV((Vector2){slider->x + (slider->progress*300),slider->y + 10}, 10, BLUE);
}
Slider create_slider(int x, int y) {
    Slider slider;
    slider.progress = 0.;
    slider.x = x;
    slider.y = y;
    slider.moving = false;
    return slider;
}

void update_slider(Slider *slider) {
    Vector2 mouse_cursor = {GetMouseX(),GetMouseY()};

    if (!IsMouseButtonDown(MOUSE_BUTTON_LEFT)) {
        slider->moving = false;
    } else if (
            (mouse_cursor.x < slider->x + SLIDERWIDTH ) && (mouse_cursor.x > slider->x) &&
            (mouse_cursor.y < slider->y + SLIDERHEIGHT ) && (mouse_cursor.y > slider->y)
            ) {
        slider->moving = true;
    }
    if (slider->moving) {
        slider->progress = (mouse_cursor.x - slider->x)/SLIDERWIDTH;
        if (slider->progress < 0) { slider->progress = 0; }
        if (slider->progress > 1) {slider->progress = 1; }
    }
}

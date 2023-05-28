#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "raylib.h"
#include "headers/slider/slider.h"
#include "headers/slider/slider.c"
#define WIDTH 800
#define HEIGHT 450
#define DISTANCE(dot1,dot2) sqrtf(powf(dot1->x - dot2->x, 2) + powf(dot1->y - dot2->y,2))
static int dot_x = 200;
static int dot_y = 200;
void draw_trig_fn(char*name,float progress,float x,float y,const Vector2*dot_loc,const Vector2*sine_start);
int main(void) {
    Slider circle_slider = create_slider(30, 340);
    InitWindow(WIDTH,HEIGHT,"Trignometry Visualizer");
    SetTargetFPS(60);
     while (!WindowShouldClose()) {
         Vector2 dot_loc = {150 + (cosf(circle_slider.progress * (2 * PI)) * 100),(HEIGHT/2.) + (sinf((1 - circle_slider.progress) * (2 * PI)) * 100)};
         Vector2 sine_start = {dot_loc.x,HEIGHT/2.};
         Vector2 cosine_start = {150,dot_loc.y};
         BeginDrawing();
            ClearBackground(RAYWHITE);
            DrawLineEx((Vector2){50,HEIGHT/2.}, (Vector2){250,HEIGHT/2.}, 5., BLACK);
            DrawLineEx((Vector2){150,(HEIGHT/2.) - 100}, (Vector2){150,(HEIGHT/2.) + 100}, 5., BLACK);
            for (int thickness = 0;thickness < 10;++thickness) { DrawCircleLines(150, HEIGHT/2, 100 - (thickness/2.),RED); } // draws a thick circle line
            // the sine line
            DrawLineEx(sine_start,dot_loc,5.,BLUE);
            // the cosine line
            DrawLineEx(cosine_start,dot_loc,5.,GREEN);
            DrawCircleV(dot_loc, 5, BLUE);
            draw_trig_fn("sin",circle_slider.progress,WIDTH * 0.25,HEIGHT/40.,&dot_loc,&sine_start);
            draw_trig_fn("cos",circle_slider.progress,WIDTH * 0.25,HEIGHT/10.,&dot_loc,&cosine_start);
            draw_slider(&circle_slider);
            update_slider(&circle_slider);
        EndDrawing();
    }
    CloseWindow();
    return 0;
}
void draw_trig_fn(char*name,float progress,float x,float y,const Vector2*dot_loc,const Vector2*sine_start) {
    char trig_res[35];
    float trig_in = roundf((progress*(2*PI))*100)/100;
    float trig_out = (roundf(DISTANCE(dot_loc,sine_start) * 100))/10000;
    snprintf(trig_res, sizeof(trig_res), "%s(%g) = %g",name,trig_in,trig_out);
    DrawText(trig_res,x,y, 30., BLACK);

}

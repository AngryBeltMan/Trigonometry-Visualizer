#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "raylib.h"
#include "headers/slider/slider.h"
#include "headers/slider/slider.c"
#include "headers/tangent/tangent.h"
#define WIDTH 800
#define HEIGHT 450
#define RADIANS (2 * PI)
#define CIRCLEWIDTH 150
#define CIRCLEHEIGHT HEIGHT/2.
#define DISTANCE(dot1,dot2) sqrtf(powf(dot1->x - dot2->x, 2) + powf(dot1->y - dot2->y,2))
static int dot_x = 200;
static int dot_y = 200;
void draw_trig_fn(char*name,float progress,float x,float y,bool negative,const Vector2*dot_loc,const Vector2*sine_start);
int main(void) {
    Slider circle_slider = create_slider(30, 340);
    InitWindow(WIDTH,HEIGHT,"Trignometry Visualizer");
    SetTargetFPS(60);
     Vector2 origin  = {CIRCLEWIDTH,CIRCLEHEIGHT};
     while (!WindowShouldClose()) {
         float dot_x = (cosf(circle_slider.progress * RADIANS) * 100);
         float dot_y = (sinf((circle_slider.progress) * RADIANS) * 100);
         Vector2 dot_loc = {150 + dot_x,(HEIGHT/2.) + (1-dot_y)};
         Vector2 sine_start = {dot_loc.x,HEIGHT/2.};
         Vector2 cosine_start = {150,dot_loc.y};
         float tan = CALCTAN(dot_y,dot_x);
         float sec = -FINDSECANT(tan);
         Vector2 tangent_start = {
             (CIRCLEWIDTH + 100 * (1/cosf(circle_slider.progress * RADIANS))),
             CIRCLEHEIGHT
         };
         BeginDrawing();
            ClearBackground(RAYWHITE);
            DrawLineEx((Vector2){50,CIRCLEHEIGHT}, (Vector2){250,CIRCLEHEIGHT}, 5., BLACK);
            DrawLineEx((Vector2){150,(HEIGHT/2.) - 100}, (Vector2){150,CIRCLEHEIGHT + 100}, 5., BLACK);
            for (int thickness = 0;thickness < 10;++thickness) { DrawCircleLines(150, CIRCLEHEIGHT, 100 - (thickness/2.),RED); } // draws a thick circle line
            // the origin line
            DrawLineEx(origin,dot_loc,5.,YELLOW);
            // the sine line
            DrawLineEx(sine_start,dot_loc,5.,BLUE);
            // the cosine line
            DrawLineEx(cosine_start,dot_loc,5.,GREEN);
            // the tangent line
            DrawLineEx(tangent_start,dot_loc,5.,PURPLE);
            // draws the secant line
            DrawCircleV(dot_loc, 5, BLUE);

            draw_trig_fn("sin",circle_slider.progress,WIDTH * 0.25,HEIGHT/40.,false,&dot_loc,&sine_start);
            draw_trig_fn("cos",circle_slider.progress,WIDTH * 0.25,HEIGHT/10.,false,&dot_loc,&cosine_start);
            bool negative = (((int)floorf((circle_slider.progress*100)/25) + 2) % 2) == 1;
            draw_trig_fn("tan",circle_slider.progress,WIDTH * 0.25,HEIGHT/6.,negative,&dot_loc,&tangent_start);
            draw_trig_fn("rad",circle_slider.progress,WIDTH * 0.25,HEIGHT/3.,false,&dot_loc,&origin);
            draw_slider(&circle_slider);
            update_slider(&circle_slider);

        EndDrawing();
    }
    CloseWindow();
    return 0;
}
void draw_trig_fn(char*name,float progress,float x,float y,bool negative,const Vector2*dot_loc,const Vector2*sine_start) {
    char trig_res[36];
    float trig_in = roundf((progress*RADIANS)*100)/100;
    float trig_out = (roundf(DISTANCE(dot_loc,sine_start) * 100))/10000;
    if (negative) {
        snprintf(trig_res, sizeof(trig_res), "%s(%g) = -%g",name,trig_in,trig_out);
    } else {
        snprintf(trig_res, sizeof(trig_res), "%s(%g) = %g",name,trig_in,trig_out);
    }
    DrawText(trig_res,x,y, 30., BLACK);

}

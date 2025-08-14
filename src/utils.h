
#pragma once

#include "SDL3/SDL_render.h"
namespace utils {
    
struct HotRect{
float x,y,w,h;
}; 


const int logical_x = 1920;
const int logical_y = 1080;

extern void get_mpos(SDL_Renderer * rnd, float *u, float *v);
bool hit_rect_norm(float u, float v, HotRect r);
void norm_to_logical(SDL_Renderer* rnd, float x, float y, float* screen_x, float* screen_y);


}

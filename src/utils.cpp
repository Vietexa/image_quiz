
#include "utils.h"
#include "SDL3/SDL_mouse.h"
#include "SDL3/SDL_render.h"
#include <string>
#include <SDL3/SDL_log.h>

namespace utils {

void get_mpos(SDL_Renderer* rnd, float *u, float *v){


    float mouse_x,mouse_y;
    float outw,outh;
    
    std::string x_str, y_str;

    SDL_GetMouseState(&mouse_x, &mouse_y);
    SDL_RenderCoordinatesFromWindow(rnd, mouse_x,mouse_y,&outw, &outh);

    *u =  outw / logical_x;
    *v =  outh / logical_y;

    x_str = std::to_string(*u);
    y_str = std::to_string(*v);

    SDL_Log("%s", (x_str + " " + y_str).c_str());

}


 bool hit_rect_norm(float u, float v, utils::HotRect r) {
    return (u >= r.x && u <= r.x + r.w &&
            v >= r.y && v <= r.y + r.h);
}


void norm_to_logical(SDL_Renderer* rnd, float x, float y, float* lpos_x, float* lpos_y){

    *lpos_x = x * logical_x;
    *lpos_y = y * logical_y;
}


 }
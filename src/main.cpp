

#include "SDL3/SDL_mouse.h"
#define SDL_MAIN_USE_CALLBACKS 1 

#include <cstdlib>
#include "SDL3/SDL_init.h"
#include "SDL3/SDL_keycode.h"
#include <SDL3/SDL_log.h>
#include <SDL3/SDL_video.h>
#include "SDL3/SDL_events.h"
#include "SDL3/SDL_render.h"
#include <SDL3/SDL.h>
#include <SDL3_image/SDL_image.h>
#include <SDL3/SDL_main.h>
#include "utils.h"

static SDL_Window *window = NULL;
static SDL_Renderer* renderer = NULL;
static SDL_Texture* bckg = NULL;
static SDL_Texture* selected_area = NULL;

static float u, v;

inline void render_marker(){

    float x_pos, y_pos;
    float rect_x, rect_y;
    float rect_w, rect_h ;
    rect_w = rect_h = 50;
    utils::norm_to_logical(renderer,u,v,&x_pos,&y_pos);

    if (x_pos < 0 || y_pos < 0 || x_pos > utils::logical_x || y_pos > utils::logical_y){  
        u = 0;
        v = 0;
        SDL_Log("The area selected exceeds the rendering space. Please select a position within the rendering space.\n");
        return;
    }

    rect_x = x_pos -  rect_w / 2;
    rect_y = y_pos - rect_h / 2;

    SDL_FRect rect = {rect_x ,rect_y ,rect_w,rect_h};

    SDL_RenderTexture(renderer,selected_area, NULL, &rect);

}


SDL_AppResult SDL_AppInit(void **appstate, int argc, char *argv[]){

    #ifdef unix
    setenv("SDL_VIDEODRIVER", "x11", 1);
    #endif

    if (!SDL_Init(SDL_INIT_VIDEO)) {
        SDL_Log("Couldn't initialize SDL: %s", SDL_GetError());
        return SDL_APP_FAILURE;
    }

    window = SDL_CreateWindow("SDL App",800, 620, SDL_WINDOW_RESIZABLE);
    renderer = SDL_CreateRenderer(window, "opengl");

    if (!window || !renderer) {
        SDL_Log("Couldn't create the window or the renderer: %s", SDL_GetError());
        return SDL_APP_FAILURE;
    }

    SDL_SetRenderLogicalPresentation(renderer,1920, 1080, SDL_LOGICAL_PRESENTATION_LETTERBOX);

    bckg = IMG_LoadTexture(renderer, "./assets/png_files/image.png");
    selected_area = IMG_LoadTexture(renderer, "./assets/png_files/s_marker.png");

    if (!bckg)
    {
          SDL_Log("Couldn't create the texture: %s", SDL_GetError());
          return SDL_APP_FAILURE;
    }



    return SDL_APP_CONTINUE; 
}


SDL_AppResult SDL_AppEvent(void *appstate, SDL_Event *event){

    SDL_Keycode key = event->key.key;

    switch (event->type){

        case SDL_EVENT_QUIT:
        return SDL_APP_SUCCESS;
        break;

        case SDL_EVENT_KEY_DOWN:
        if (key == SDLK_ESCAPE) return SDL_APP_SUCCESS;
        break;

        case SDL_EVENT_MOUSE_BUTTON_DOWN:

        if (event->button.button == SDL_BUTTON_LEFT){
    
            utils::get_mpos(renderer, &u, &v);
    
            utils::HotRect answer = { 0.20f, 0.30f, 0.15f, 0.10f };

            if (utils::hit_rect_norm(u,v, answer) == true) SDL_Log("You hit the hotspot!");
            else SDL_Log("You didn't hit the hotspot! Please try again!");
         }

        break;
   }
    return SDL_APP_CONTINUE; 
 }


SDL_AppResult SDL_AppIterate(void *appstate){  
    
SDL_SetRenderDrawColor(renderer,255,255,225, 1);
SDL_RenderTexture(renderer,bckg, NULL, NULL);
   
if (u != 0 && v != 0) render_marker();
    
    SDL_RenderPresent(renderer);
    SDL_RenderClear(renderer);
   
    SDL_Delay(10);

    return SDL_APP_CONTINUE;
}


void SDL_AppQuit(void *appstate, SDL_AppResult result){
    
SDL_DestroyRenderer(renderer);
SDL_DestroyWindow(window);

}

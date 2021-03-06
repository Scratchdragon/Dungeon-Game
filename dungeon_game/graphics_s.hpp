#include <stdlib.h>

#include <SDL2/SDL.h>

void draw_model(float model[16][16],float alpha[16][16],int x, int y, SDL_Renderer *renderer,float background[16][16] = floor1){
    for (int xi = 0; xi < 32; ++xi) {
        for (int yi = 0; yi < 32; ++yi) {
            float brightness = model[(int)(yi / 2)][(int)(xi / 2)] * 255;
            SDL_SetRenderDrawColor(renderer, brightness, brightness, brightness, alpha[(int)(yi / 2)][(int)(xi / 2)] * 255);
            if(alpha[(int)(yi / 2)][(int)(xi / 2)] != 0){
                SDL_RenderDrawPoint(renderer, x + xi, y + yi);
            }
            else{
                float brightness = background[(int)(yi / 2)][(int)(xi / 2)] * 255;
                SDL_SetRenderDrawColor(renderer, brightness, brightness, brightness, alpha[(int)(yi / 2)][(int)(xi / 2)] * 255);
                SDL_RenderDrawPoint(renderer, x + xi, y + yi);
            }
        }
    }
}

#include <Controls.h>

void processInput(SDL_Event* e,  bool* done, Camera* camera, Time* time){

            if(e->type == SDL_QUIT) {
                *done = true;
            }
            if(e->type == SDL_MOUSEMOTION){
                panCamera(camera,e->motion.xrel,e->motion.yrel);
            } 
            if (e->type == SDL_KEYDOWN){

				switch(e->key.keysym.sym) {
					case SDLK_z:
						ProcessKeyboard(camera, FORWARD, time->deltaTime);
						break;
					case SDLK_s:
						ProcessKeyboard(camera, BACKWARD, time->deltaTime);
						break;
					case SDLK_q:
						ProcessKeyboard(camera, LEFT, time->deltaTime);
						break;
					case SDLK_d:
						ProcessKeyboard(camera, RIGHT, time->deltaTime);
						break;
				}

            }
			if (e->type == SDL_KEYUP)
				switch(e->key.keysym.sym) {
					case SDLK_w:
						break;
					case SDLK_s:
						break;
					case SDLK_a:
						break;
					case SDLK_d:
						break;
				}
	}

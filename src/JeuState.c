#include "SDL/SDL.h"
#include "SDL/SDL_image.h"
#include "include/JeuState.h"
#include "include/Mario.h"
#include "include/config.h"
#include "include/Enemy.h"

typedef struct {
	SDL_Surface * fond;
	SDL_Rect pos;
	int ymax;
	Mario * mario;
	Mario ** enemies;
    int countOfEnemies;
} JS_t;

void JS_init(state_t * s);
void JS_update(state_t * s, Uint32 elapsedTime);
void JS_handleEvent(state_t * s);
void JS_draw(state_t * s, SDL_Surface * surface);
void JS_clean(state_t * s);
const int H = 15;
const int W = 150;


state_t * JS_get()
{
	state_t * state = malloc(sizeof(*state));
	state->init = JS_init;
	state->update = JS_update;
	state->handleEvent = JS_handleEvent;
	state->draw = JS_draw;
	state->clean = JS_clean;
	state->data = NULL;
	return state;
}
int HasIntersection(SDL_Rect a,SDL_Rect b){
    if((a.x==b.x)||(a.w+a.x<b.w+b.x&&a.x+a.w>b.x)||(b.w+b.x<a.w+a.x&&b.x+b.w>a.x)){
        if((a.y==b.y)||(a.h+a.y>b.y&&a.h+a.y<b.y+b.h)||(b.h+b.y>a.y&&b.h+b.y<a.y+a.h)){
            return 1;
        }
    }
    return 0;
}
void JS_update(state_t * s, Uint32 elapsedTime)
{
	JS_t * m = s->data;
    if(HasIntersection(m->enemies[0]->position,m->mario->position)){
        if(m->mario->acceleration>0&&m->mario->position.y-183<0)
            m->enemies[0]->died = 1;
        else if(m->enemies[0]->died ==0){
            m->mario->died=1;
        }
    }
	Enemy_update(m->enemies[0], elapsedTime);
	Mario_update(m->mario, elapsedTime);
}

void JS_init(state_t * s)
{
	JS_t * data = malloc(sizeof(*data));
    data->fond = IMG_Load("/home/vladlensky/Загрузки/Mario/levels/1-1/view.png");
    SDL_Rect r = {(0), (0), (3584), (480)};\
    SDL_Rect position;
    SDL_FillRect(data->fond, &r, 1);
    SDL_Surface *surface = IMG_Load("/home/vladlensky/Загрузки/Mario/images/Mario_tileset.png");
    int i=0;
    int j=0;
    for (; i<H; i++) {
        for (j = 0; j < W; j++) {
            position.x = (j * 16);
            position.y = (i * 16);
            if (FirstLevelMap[i][j] == 'P') {
                SDL_Rect element = {(96), (112), (16), (16)};
                position.w = 16;
                position.h = 16;
                SDL_BlitSurface(surface, &element, data->fond, &position);
            }/*Земля*/

            if (FirstLevelMap[i][j]=='k') {
                SDL_Rect element = {(143), (112), (16), (16)};
                position.w = 16;
                position.h = 16;
                SDL_BlitSurface(surface, &element, data->fond, &position);
            }/*Кирпич*/

             if (FirstLevelMap[i][j]=='c'){
                 SDL_Rect element = {(127), (112), (16), (16)};
                 position.w = 16;
                 position.h = 16;
                 SDL_BlitSurface(surface, &element, data->fond, &position);
             }/*Секретный блок*/

             if (FirstLevelMap[i][j]=='t'){
                 SDL_Rect element = {(0), (47), (32), (48)};
                 position.w = 32;
                 position.h = 48;
                 SDL_BlitSurface(surface, &element, data->fond, &position);
             }/*труба*/

             if (FirstLevelMap[i][j]=='g'){
                 SDL_Rect element = {(0), (16*9-5), (48), (37)};
                 position.w = 48;
                 position.h = 37;
                 SDL_BlitSurface(surface, &element, data->fond, &position);
             }/*Маленькая травка*/

             if (FirstLevelMap[i][j]=='G'){
                 SDL_Rect element = {(145), (222), (77), (33)};
                 position.w = 77;
                 position.h = 33;
                 SDL_BlitSurface(surface, &element, data->fond, &position);
             }/*Большая травка*/

             if (FirstLevelMap[i][j]=='d'){
                 SDL_Rect element = {(0), (106), (74), (21)};
                 position.w = 74;
                 position.h = 21;
                 SDL_BlitSurface(surface, &element, data->fond, &position);
             }/*Кустик*/

             if (FirstLevelMap[i][j]=='w'){
                 SDL_Rect element = {(99), (224), (41), (31)};
                 position.w = 41;
                 position.h = 31;
                 SDL_BlitSurface(surface, &element, data->fond, &position);
             }/*Маленькое облако*/

            if (FirstLevelMap[i][j]=='r') {
                SDL_Rect element = {(111), (112), (16), (16)};
                position.w = 16;
                position.h = 16;
                SDL_BlitSurface(surface, &element, data->fond, &position);
            }/*Неразрушаемые блоки(лесенки)*/
        }
    }
	data->pos.x = 0;
	data->pos.y = 80;
	data->pos.h = SCREEN_H;
	data->pos.w = SCREEN_W;
	data->mario = malloc(sizeof(*(data->mario)));
	data->ymax = 240;
	Mario_init(data->mario);
	Mario** enemies =  malloc(sizeof(*(data->mario))*1);
	enemies[0] = malloc(sizeof(*(data->mario)));
	position.x = (750);
	position.y = (0);
    Enemy_init(enemies[0],position);
	Mario_draw(enemies[0],surface,position);
	data->enemies = enemies;
	s->data = data;
}

void JS_handleEvent(state_t * s)
{
	SDL_Event event;
	int continuer = 1;
	JS_t * m = s->data;
	
	while(continuer && SDL_PollEvent(&event))
	{
		switch(event.type)
		{
			case SDL_QUIT:
				GS_PopState();
				continuer = 0;
				break;
			case SDL_KEYDOWN:
				switch(event.key.keysym.sym)
				{
					case SDLK_ESCAPE:
					case SDLK_RETURN:
						GS_PopState();
						continuer = 0;
						break;
					case SDLK_LEFT:
						Mario_move_left(m->mario, 1);
						break;
					case SDLK_RIGHT:
						Mario_move_right(m->mario, 1);
						break;
                    case SDLK_UP:
                        Mario_jump(m->mario);
                        break;
                    case SDLK_DOWN:
                        Mario_down(m->mario,1);
                        break;
					default:
						;
				}
				break;
			case SDL_KEYUP:
				switch(event.key.keysym.sym)
				{
					case SDLK_LEFT:
						Mario_move_left(m->mario, 0);
						break;
					case SDLK_RIGHT:
						Mario_move_right(m->mario, 0);
						break;
					default:
						;
				}
				break;
			default:
				;
		}
	}
	
	{
		SDL_Rect frame_rect = m->mario->animation[m->mario->currentAnimation].frames[m->mario->currentFrame];
		int px = (SCREEN_W - frame_rect.w) / 2;
		int py = (SCREEN_H - frame_rect.h) / 2;
		int pymax = m->ymax - SCREEN_H;
		
		if(m->mario->position.x < px)
		{
			m->pos.x = 0;
		}
		else
		{
			m->pos.x = m->mario->position.x - px;
		}
        m->pos.y = pymax;
	}
}

void JS_draw(state_t * s, SDL_Surface * surface)
{
	JS_t * m = s->data;
	SDL_BlitSurface(m->fond, &(m->pos), surface, NULL);
	Mario_draw(m->mario, surface, m->pos);
	Mario_draw(m->enemies[0], surface, m->pos);
}

void JS_clean(state_t * s)
{
	JS_t * m = s->data;
	SDL_FreeSurface(m->fond);
	Mario_clean(m->mario);
}

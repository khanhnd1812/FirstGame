#include "GameButton.h"

Button::Button()
{
	inside = false;
    des = { 0,0,0,0 };
    btn_image = NULL;
    isTouch = false;
}

Button::~Button()
{
    if (btn_image != NULL) {
        SDL_DestroyTexture(btn_image);
        btn_image = NULL;
    }
}

void Button::Init(SDL_Renderer* screen,std::string name,int tag)
{
	btn_image = IMG_LoadTexture(screen, m_mapTexture[name].c_str());
	SDL_QueryTexture(btn_image, NULL, NULL, &des.w, &des.h);
    des.w /= 2;
    src[0] = { 0,0,des.w,des.h };
    src[1] = { des.w,0,des.w,des.h };
    m_tag = tag;
    if (m_tag == PLAY) {des.h *= 2; des.w *= 2;}
}

void Button::Update(SDL_Event* e)
{
    isTouch = false;
    HandleTouchEvent(e);
}

void Button::RenderButton(SDL_Renderer* screen)
{
	SDL_RenderCopy(screen, btn_image, &src[inside], &des);
}

void Button::HandleTouchEvent(SDL_Event* e)
{
    if (e->type == SDL_MOUSEMOTION || e->type == SDL_MOUSEBUTTONDOWN || e->type == SDL_MOUSEBUTTONUP)
    {
        int x, y;
        SDL_GetMouseState(&x, &y);
        inside = true;

        if (x < des.x)
        {
            inside = false;
        }
        else if (x > des.x + des.w)
        {
            inside = false;
        }
        else if (y < des.y)
        {
            inside = false;
        }
        else if (y > des.y + des.h)
        {
            inside = false;
        }
        if (inside && e->type == SDL_MOUSEBUTTONUP) {
            isTouch = true;
        }
    }
}

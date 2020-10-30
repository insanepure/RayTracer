#include "include/window.h"

#include <SDL.h>


CWindow::CWindow(const unsigned int a_Width,const unsigned int a_Height) : m_Width(a_Width),m_Height(a_Height)
{
    SDL_Init(SDL_INIT_VIDEO | SDL_INIT_TIMER | SDL_INIT_EVENTS);
    this->m_pWindow = SDL_CreateWindow("Raytracer",SDL_WINDOWPOS_CENTERED,SDL_WINDOWPOS_CENTERED,a_Width,a_Height,0);
    this->m_pRenderer = SDL_CreateRenderer(this->m_pWindow,-1,SDL_RENDERER_ACCELERATED);
}

//*********************************************************************//
//*********************************************************************//

CWindow::~CWindow()
{
    SDL_DestroyRenderer(this->m_pRenderer);
    SDL_DestroyWindow(this->m_pWindow);
    SDL_Quit();
}

//*********************************************************************//
//*********************************************************************//

unsigned int CWindow::GetWidth() const
{
    return this->m_Width;
}

//*********************************************************************//
//*********************************************************************//

unsigned int CWindow::GetHeight() const
{
    return this->m_Height;
}

//*********************************************************************//
//*********************************************************************//

SDL_Renderer* CWindow::GetRenderer() const
{
	return this->m_pRenderer;
}
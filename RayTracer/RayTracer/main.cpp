#include <SDL.h>
#undef main //sdl defines main as SDL_MAIN using arg and argv, we don't need arg and argv

#include "include/window.h"
#include "include/scene.h"
#include "include/sphere.h"
#include "include/plane.h"
#include "include/blinnmaterial.h"
#include "include/color.h"
#include "include/pointlight.h"

CScene* g_pScene; //Global Scene to use within ProcessInput and main

/// @brief Processes Input
///
/// @returns true if still running, false if end
///
bool ProcessInput()
{
    SDL_Event event;
    memset(&event, 0, sizeof(event)); //NULL event so we don't have garbage
    SDL_PollEvent(&event); //Fill event with the events from SDL

    //go through events
    switch (event.type)
    {
    case SDL_QUIT: //SDL calls Quit
        return false;

    case SDL_KEYDOWN:
        switch (event.key.keysym.sym) //get keyboard input
        {
        case SDLK_ESCAPE: //ESC Pressed
            return false;
        }
        break;

    default:
        break;
    }

    return true;
}

int main()
{
    //Additional Scope to remove leaks from main() objects
    {
        //Create Window on the Stack, no need to delete
        CWindow window = CWindow(600,480);
        //Set Render Color
        SDL_SetRenderDrawColor(window.GetRenderer(), 0, 102, 255, 255);
    
        //Initialize Scene
        g_pScene = new CScene(window,600,480);


        //Changeable Data
        bool shadow = true; //false for performance
        float reflection = 0.4f; //0.4f looks good, 0.0f for no reflection
        bool antiAliasing = false;//false for performance


        //Spheres
        CSphere sphere1(Vector3<float>(-2.0f,-1.0f,7.0f),1.5f,new CBlinnMaterial(CColor(1.0f,0.0f,0.0f),64,reflection,shadow));
        g_pScene->AddObject(&sphere1);
        CSphere sphere2(Vector3<float>(0.0f,2.0f,7.0f),1.5f,new CBlinnMaterial(CColor(1.0f,1.0f,1.0f),64,reflection,shadow));
        g_pScene->AddObject(&sphere2);
        CSphere sphere3(Vector3<float>(2.0f,-1.0f,7.0f),1.5f,new CBlinnMaterial(CColor(0.0f,0.0f,1.0f),64,reflection,shadow));
        g_pScene->AddObject(&sphere3);
        //Planes
        CPlane plane1(Vector3<float>(0.0f,1.0f,0.0f),3.0f,new CBlinnMaterial(CColor(0.0f,0.75,0.0f),64,reflection,shadow));
        g_pScene->AddObject(&plane1);
        CPlane plane2(Vector3<float>(0.0f,0.0f,-1.0f),8.5f,new CBlinnMaterial(CColor(0.0f,0.0f,0.75f),64,reflection,shadow));
        g_pScene->AddObject(&plane2);
    
        ////add Lights
        CPointLight light1( Vector3<float>(0.0f,1.0f,0.0f), CColor(1.0f,1.0f,1.0f),10.0f);
        g_pScene->AddLight(&light1);
    
        CPointLight light2( Vector3<float>(-5,2.5,4), CColor(0.7f,0.0f,0.0f),10.0f);
        g_pScene->AddLight(&light2);
    
        CPointLight light3( Vector3<float>(0.0f,6.0f,4.0f), CColor(0.0f,0.7f,0.0f),10.0f);
        g_pScene->AddLight(&light3);
    
        CPointLight light4( Vector3<float>(5.0f,-2.5f,4.0f), CColor(0.0f,0.0f,0.7f),10.0f);
        g_pScene->AddLight(&light4);
        //Main Loop


        while(ProcessInput())
        {
            //Start Profiling
            unsigned int start = SDL_GetTicks();
            //Clear Renderer
            SDL_RenderClear(window.GetRenderer());
        
            //Do rendering
            g_pScene->Render(antiAliasing);

            //Update Renderer
            SDL_RenderPresent(window.GetRenderer());
            //End Profiling
            unsigned int end = SDL_GetTicks();
            float fps = 1000.0f/(end-start);
            printf("%d MS - %f FPS\n", end-start, fps);
        }

        //Delete Scene
        delete g_pScene;
    }

    //Fucnction to display Memory Leaks
    //
    //std::thread has a memory leak -> but it's fixed in vs 2013!
 /*   int leaks = _CrtDumpMemoryLeaks();
    if(leaks != 0)
        printf("Memory Leaks detected!\n");*/

    return 0;
}


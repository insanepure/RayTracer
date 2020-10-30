#include "include/scene.h"
#include "include/color.h"
#include "include/ray.h"
#include "include/hit.h"

#include <SDL.h>

CScene::CScene(const CWindow& a_rWindow,const unsigned int a_Width,const unsigned int a_Height) : m_pWindow(&a_rWindow),m_Width(a_Width),m_Height(a_Height)
{
    this->m_End = false;
    //Create BackBuffer
    this->m_pTexture = SDL_CreateTexture(a_rWindow.GetRenderer(),SDL_PIXELFORMAT_RGBA8888,SDL_TEXTUREACCESS_STREAMING,a_Width,a_Height);

    //width and height in pixel of the Area a Job has to do
    unsigned int jobWidth = a_Width/JobsHorizontal;
    unsigned int jobHeight = a_Height/JobsVertical;

    for(unsigned int y=0;y<JobsVertical;++y)
    {
        for(unsigned int x=0;x<JobsHorizontal;++x, ++this->m_NextJob)
        {
            SJob& job = this->m_Jobs[this->m_NextJob];
            job.minX = x * jobWidth;
            job.minY = y * jobHeight;
            job.maxX = job.minX + jobWidth;
            job.maxY = job.minY + jobHeight;
        }
    }

    // Start threadpool
    for (int i=0; i<Threads-1; ++i)
        this->m_pThreads[i] = new std::thread(&CScene::DoWork, this);
}

//*********************************************************************//
//*********************************************************************//

CScene::~CScene()
{
    this->m_End = true;
    for (int i=0; i<Threads-1; ++i)
    {
        this->m_pThreads[i]->join();
        delete this->m_pThreads[i];
    }
    SDL_DestroyTexture(this->m_pTexture);
}

// ----------------------------------------------------------------------------

void CScene::DoWork(CScene* a_pSelf)
{
    //Thread's "Loop".
    while (!a_pSelf->m_End)
    {
        if (!a_pSelf->GetJob())
            std::this_thread::yield(); //we have nothing to do, wait until there is work to do
    }
}

// ----------------------------------------------------------------------------

bool CScene::GetJob()
{
    //if there are still jobs to do
    if (this->m_NextJob < JobCount)
    {
        //get a new job
        int jobIdx = this->m_NextJob++;
        if (jobIdx < JobCount) //if there are still job left
        {
            //do job
            ProcessJob(jobIdx);
            //finished
            ++this->m_DoneJobs; //increase already done jobs
            return true;
        }
    }

    return false;
}

// ----------------------------------------------------------------------------

void CScene::ProcessJob(int a_Index)
{
    //Get the data
    Vector3<float> maxTopLeft = this->m_Camera.GetTopLeft(); //Top Left Corner
    Vector3<float> maxRight = this->m_Camera.GetScaledRight(); //get the scaled right vector
    Vector3<float> maxDown = this->m_Camera.GetScaledDown(); //get the scaled doen vector

    CRay viewRay(this->m_Camera.GetPosition(),this->m_Camera.GetNormal());

    SHit hit;
    //define all values before so they are not initialized and destroyed N times
    Vector3<float> right,down,direction; 
    unsigned int index = 0;
    //get our job Data
    SJob& job = this->m_Jobs[a_Index];

    int color;
    //do job
    for(unsigned int y=job.minY;y<job.maxY;y++)
    {
        down = maxDown * (float)y;
        for(unsigned int x=job.minX;x<job.maxX;x++)
        {
            right = maxRight * (float)x;
            direction = maxTopLeft + right + down;
            index = (x +y*m_TexturePitch);
            //set the new direction
            viewRay.SetDirection(direction);

            //Now trace
            if ((Trace(viewRay, &hit,99999999999.0f)) != nullptr)
            {
                //only calculate AntiAliasing if an object has been hit
                if(this->m_AntiAliasing)
                {
                    CColor aliasedColor( 0, 0, 0,0 );
                    for ( int xAdd = -1; xAdd < 1; xAdd++ ) 
                    {
                        for ( int yAdd = -1; yAdd < 1; yAdd++ )
                        {
                            down = maxDown * (float)(y+yAdd);
                            right = maxRight * (float)(x+xAdd);
                            direction = maxTopLeft + right + down;
                            viewRay.SetDirection(direction);
                            if (Trace(viewRay, &hit,99999999999.0f) != nullptr)
                                aliasedColor += hit.pMaterial->Shade(hit,*this);
                        }
                    }
                    aliasedColor.R /= 4.0f;
                    aliasedColor.G /= 4.0f;
                    aliasedColor.B /= 4.0f;
                    aliasedColor.A /= 4.0f;
                    color = CColor::ToRGBA(aliasedColor);
                }
                else
                    color = CColor::ToRGBA(hit.pMaterial->Shade(hit,*this));
                this->m_pPixelBuffer[index] = color;
            }
            else
                color = 0x101010FF;
            this->m_pPixelBuffer[index] = color;

        }
    }
}

//*********************************************************************//
//*********************************************************************//

IObject*  CScene::Trace(const CRay& a_rViewRay, SHit* a_pHit,float a_Distance) const
{
    IObject* hitObject = nullptr;

    for (auto object : this->m_Objects)
    {
        if(object->Intersects(a_rViewRay, a_pHit, a_Distance))
            hitObject = object;
    }

    return hitObject;
}

//*********************************************************************//
//*********************************************************************//

void CScene::AddObject(IObject* a_pObject)
{
    this->m_Objects.push_back(a_pObject);
}

//*********************************************************************//
//*********************************************************************//

void CScene::AddLight(ILight* a_pLight)
{
    this->m_Lights.push_back(a_pLight);
}

//*********************************************************************//
//*********************************************************************//

const CCamera& CScene::GetCamera() const
{
    return this->m_Camera;
}

//*********************************************************************//
//*********************************************************************//

const std::vector<ILight*>& CScene::GetLights() const
{
    return this->m_Lights;
}
//*********************************************************************//
//*********************************************************************//

void CScene::Render(bool a_AntiAliasing)
{
    this->m_AntiAliasing = a_AntiAliasing;
    // Prepare texture, get PixelBuffer and fill TexturePitch
    SDL_LockTexture(this->m_pTexture, NULL, (void**)&this->m_pPixelBuffer, &this->m_TexturePitch);
    m_TexturePitch /= sizeof(int); //texturePitch is defines in bytes, but we use int

    //only update the Data if the Camera moved or the Aspect changed
    this->m_Camera.Update(this->m_Width,this->m_Height);

    //atomics because they are changed by threads
    this->m_DoneJobs = 0;
    this->m_NextJob = 0;

    //wait for workers to finish, also do something ourself
    while (this->m_DoneJobs < JobCount)
    {
        if (!GetJob())
            std::this_thread::yield();
    }

    //unlock texture
    SDL_UnlockTexture(this->m_pTexture);
    //copy the texture to the renderer and display it
    SDL_RenderCopy(this->m_pWindow->GetRenderer(), this->m_pTexture, NULL, NULL);
}
#include "include/camera.h"

CCamera::CCamera(Vector3<float> a_Position,
                 Vector3<float> a_Normal,
                 Vector3<float> a_Up,
                 float a_Distance,
                 float a_FOV) : 
m_Position(a_Position),
    m_Normal(a_Normal),
    m_Up(a_Up),
    m_Distance(a_Distance),
    m_FOV(a_FOV),
    m_Update(true)
{
}

//*********************************************************************//
//*********************************************************************//

CCamera::~CCamera()
{
}

//*********************************************************************//
//*********************************************************************//

const Vector3<float>& CCamera::GetPosition() const
{
    return this->m_Position;
}

//*********************************************************************//
//*********************************************************************//

const Vector3<float>& CCamera::GetNormal() const
{
    return this->m_Normal;
}

//*********************************************************************//
//*********************************************************************//

const Vector3<float>& CCamera::GetUp() const
{
    return this->m_Up;
}

//*********************************************************************//
//*********************************************************************//

const Vector3<float>& CCamera::GetLeft() const
{
    return this->m_Left;
}

//*********************************************************************//
//*********************************************************************//

const Vector3<float>& CCamera::GetTopLeft() const
{
    return this->m_TopLeft;
}

//*********************************************************************//
//*********************************************************************//

const Vector3<float>& CCamera::GetScaledDown() const
{
    return this->m_Down;
}

//*********************************************************************//
//*********************************************************************//

const Vector3<float>& CCamera::GetScaledRight() const
{
    return this->m_Right;
}

//*********************************************************************//
//*********************************************************************//

float CCamera::GetDistance()
{
    return this->m_Distance;
}

//*********************************************************************//
//*********************************************************************//

float CCamera::GetFOV()
{
    return this->m_FOV;
}

//*********************************************************************//
//*********************************************************************//

void CCamera::Update(unsigned int a_Width, unsigned int a_Height)
{
    //We save the camera's data and change them only when the camera changed
    if(this->m_Update||this->m_Width != a_Width||this->m_Height != a_Height)
    {
        //Camera moved or Width changed, so we update our Data
        this->m_Width = a_Width;
        this->m_Height = a_Height;
        this->m_Left = Vector3<float>::Cross(this->m_Normal,this->m_Up);

        //aspect ratio
        float aspect = this->m_Width / (float)this->m_Height;
        //move half in X axis
        float halfX = this->m_Distance * 0.5f * ((aspect > 1) ? aspect : 1);
        //move half in Y axis
        float halfY = this->m_Distance * 0.5f * ((aspect < 1) ? aspect : 1);
        //add all
        this->m_TopLeft = this->m_Normal + (m_Left * halfX) + (m_Up * halfY);

        //we use the smallest side so we downsample instead of oversampling if needed
        float minSize = (float)((this->m_Width < this->m_Height) ? this->m_Width : this->m_Height);
        float stride = this->m_Distance / minSize;
        //now save our scaled Right and Down Vector
        this->m_Right = -this->m_Left * stride;
        this->m_Down = -this->m_Up * stride;

        this->m_Update = false;
    }
}
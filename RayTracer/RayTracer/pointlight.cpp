#include "include/pointlight.h"
#include "include/hit.h"

CPointLight::CPointLight(const Vector3<float>& a_rPosition, CColor a_Color,float a_Radius) : m_Position(a_rPosition),m_Color(a_Color),m_Radius(a_Radius)
{

}


//*********************************************************************//
//*********************************************************************//

CPointLight::~CPointLight()
{
}


//*********************************************************************//
//*********************************************************************//

const  Vector3<float>& CPointLight::GetPosition() const
{
    return this->m_Position;
}


//*********************************************************************//
//*********************************************************************//

const CColor CPointLight::GetColor(const SHit& a_rHit) const
{
    float len = (this->m_Position-a_rHit.Position).Length();
    float attenuation = 1.0f-(len/this->m_Radius);

    if(attenuation > 1.0f) attenuation = 1.0f;
    else if(attenuation < 0.0f) attenuation = 0.0f;

    return this->m_Color;
}
#include "include/sphere.h"
#include "include/ray.h"
#include "include/hit.h"

#include <cmath>


CSphere::CSphere(Vector3<float> a_Position, float a_Radius, IMaterial* a_pMaterial) : m_Position(a_Position), m_Radius(a_Radius*a_Radius),m_pMaterial(a_pMaterial)
{

}



//*********************************************************************//
//*********************************************************************//

CSphere::~CSphere()
{
    delete this->m_pMaterial;
}



//*********************************************************************//
//*********************************************************************//

bool CSphere::Intersects(const CRay& a_rRay, SHit* a_pHit, float& a_rMaxDistance) const
{
    //check if the distance between the center and the ray is smaller than or equal to the sphere's radius
    
    Vector3<float> rayToCenter = this->m_Position - a_rRay.GetStart();
    float RTCLength = Vector3<float>::Dot(rayToCenter,rayToCenter);
    float ViewDirLength = Vector3<float>::Dot(rayToCenter,a_rRay.GetDirection());
    
    if ((ViewDirLength < 0) && (RTCLength > this->m_Radius))
        return false;  //MISS
    
    float CTVLength = RTCLength - ViewDirLength * ViewDirLength;
    if (CTVLength > this->m_Radius)
        return false; //MISS
    
    float innerDist = sqrt(this->m_Radius - CTVLength);
    float distance = (RTCLength > this->m_Radius) ? ViewDirLength - innerDist : ViewDirLength + innerDist;
        
    if (distance >= a_rMaxDistance)
        return false; // ### return, rejected #

    if (a_pHit != nullptr)
    {
        a_pHit->Distance = distance;
        a_pHit->Position  = a_rRay.GetPoint(distance);
        a_pHit->Normal = Vector3<float>::Normalize(a_pHit->Position - this->m_Position);
        a_pHit->pMaterial = this->m_pMaterial;
    }
    
    a_rMaxDistance = distance;
    return true;
}
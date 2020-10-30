#include "include/plane.h"
#include "include/ray.h"
#include "include/hit.h"
#include "include/imaterial.h"

#include <cmath>


CPlane::CPlane(Vector3<float> a_Normal, float a_Distance, IMaterial* a_pMaterial) : m_Normal(a_Normal), m_Distance(a_Distance),m_pMaterial(a_pMaterial)
{

}



//*********************************************************************//
//*********************************************************************//

CPlane::~CPlane()
{
    delete this->m_pMaterial;
}



//*********************************************************************//
//*********************************************************************//

bool CPlane::Intersects(const CRay& a_rRay, SHit* a_pHit, float& a_rMaxDistance) const
{
    //hesse normal form, point on ray = point on plane
    float directionDotNormal = Vector3<float>::Dot(a_rRay.GetDirection(),m_Normal);
    float distance = -(Vector3<float>::Dot(a_rRay.GetStart(),m_Normal) + this->m_Distance) / directionDotNormal;
    
    if (distance < 0)
        return false; // ### return, missed ###

    if (distance >= a_rMaxDistance)
        return false; // ### return, rejected ###
    
    if (a_pHit != nullptr)
    {
        a_pHit->Distance  = distance;
        a_pHit->Position  = a_rRay.GetPoint(distance);
        a_pHit->Normal    = this->m_Normal;
        a_pHit->pMaterial = this->m_pMaterial;
    }
    
    a_rMaxDistance = distance;
    return true;
}
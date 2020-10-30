#include "include/ray.h"


CRay::CRay(const Vector3<float>& a_rStart,const Vector3<float>& a_rDirection) : m_Start(a_rStart),m_Direction(a_rDirection)
{
    this->SetDirection(this->m_Direction);
}

//*********************************************************************//
//*********************************************************************//

CRay::~CRay()
{
}

//*********************************************************************//
//*********************************************************************//

void CRay::SetDirection(Vector3<float>& a_Direction)
{
    this->m_Direction = Vector3<float>::Normalize(a_Direction);
}

//*********************************************************************//
//*********************************************************************//

Vector3<float> CRay::GetPoint(float a_Distance) const
{
    return this->m_Start + this->m_Direction * a_Distance;
}

//*********************************************************************//
//*********************************************************************//

Vector3<float> CRay::GetStart() const
{
    return this->m_Start;
}

//*********************************************************************//
//*********************************************************************//

Vector3<float> CRay::GetDirection() const
{
    return this->m_Direction;
}
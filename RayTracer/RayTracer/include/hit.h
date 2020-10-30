#ifndef _HIT_H_
#define _HIT_H_

#include "vector3.h"
#include "imaterial.h"

/// @brief Data if a Ray hit an Object
///
struct SHit
{
    ///@brief Distance from the Ray to the Hitpoint
    ///
    float Distance;  
    ///@brief World Position of the Hit Point
    ///       
    Vector3<float> Position;
    ///@brief Normal at the Hit Point
    ///
    Vector3<float> Normal;
    ///@brief Material which has been hit
    ///
    IMaterial* pMaterial;
};

#endif /* _HIT_H_ */
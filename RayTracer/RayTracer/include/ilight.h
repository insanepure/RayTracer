#ifndef _ILIGHT_H_
#define _ILIGHT_H_

#include "vector3.h"
#include "color.h"

struct SHit;

/// @brief Interface for Light Objects, like Point Light or Directional Light
///
class ILight
{
public:
    
    /// @brief Define Destructor so it can be overloaded
    ///
    virtual ~ILight() {}
    
    /// @brief Return the Position of the Light
    ///
    /// @returns Position as Reference
    ///
    virtual const Vector3<float>& GetPosition() const = 0;
    
    /// @brief Return the Color of the Light
    ///
    /// @param World Position of the pixel defined in here
    ///
    /// @returns Color as Reference
    ///
    virtual const CColor GetColor(const SHit& a_Hit) const = 0;
};

#endif
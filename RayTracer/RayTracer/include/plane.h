#ifndef _PLANE_H_
#define _PLANE_H_

#include "iobject.h"
#include "vector3.h"

class IMaterial;

/// @brief Plane object that inherits from IObject
///
class CPlane : public IObject
{
private:
    /// @brief Normal of the Plane
    ///
    Vector3<float> m_Normal;
    /// @brief Distance from Origin
    ///
    float m_Distance;
    /// @brief Material of the Plane
    ///
    IMaterial* m_pMaterial;
public:
    /// @brief Constructor to initialize a new Plane
    ///
    /// @param Normal of the Plane
    /// @param Radius of the Plane
    /// @param Material for the Plane
    ///
    CPlane(Vector3<float> a_Normal, float a_Distance, IMaterial* a_pMaterial);
    /// @brief Destructor to destroy a new Plane
    ///
    ~CPlane();
public:
    /// @brief Test if an object intersects with a ray
    ///
    /// @param Ray to test the object
    /// @param Resulted Data
    /// @param Ray Length
    ///
    /// @returns true if hit, false if not
    ///
    virtual bool Intersects(const CRay& a_rRay, SHit* a_pHit, float& a_rMaxDistance) const;
};

#endif /* _PLANE_H_ */
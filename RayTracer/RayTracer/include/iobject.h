#ifndef _IOBJECT_H_
#define _IOBJECT_H_

class CRay;
class IMaterial;
struct SHit;

/// @brief Interface for all Objects
///
class IObject
{
public:

    /// @brief Define Destructor so it can be overloaded
    ///
    virtual ~IObject() {}
    /// @brief Test if an object intersects with a ray
    ///
    /// @param Ray to test the object
    /// @param Resulted Data
    /// @param Ray Length
    ///
    /// @returns true if hit, false if not
    ///
    virtual bool Intersects(const CRay& a_rRay,SHit* a_pHit,float& a_rMaxDistance) const = 0;
};

#endif /* _IOBJECT_H_ */
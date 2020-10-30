#ifndef _SPHERE_H_
#define _SPHERE_H_

#include "iobject.h"
#include "vector3.h"

class IMaterial;

/// @brief Sphere object that inherits from IObject
///
class CSphere : public IObject
{
    private:
        /// @brief Position of the Sphere
        ///
        Vector3<float> m_Position;
        /// @brief Radius of the Sphere
        ///
        float m_Radius;
        /// @brief Material of the Sphere
        ///
        IMaterial* m_pMaterial;
    public:
        /// @brief Constructor to initialize a new Sphere
        ///
        /// @param Position of the Sphere
        /// @param Radius of the Sphere
        /// @param Material for the Sphere
        ///
        CSphere(Vector3<float> a_Position, float a_Radius, IMaterial* a_pMaterial);
        /// @brief Destructor to destroy a new Sphere
        ///
        ~CSphere();
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


#endif /* _SPHERE_H_ */
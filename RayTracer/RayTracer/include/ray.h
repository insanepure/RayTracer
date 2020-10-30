#ifndef _RAY_H_
#define _RAY_H_

#include "vector3.h"


/// @brief Ray that is casted from the Camera to the Scene
///
class CRay
{
private:
    /// @brief Start Vector
    ///
    Vector3<float> m_Start;
    /// @brief Direction Vector
    ///
    Vector3<float> m_Direction;
public:
    /// @brief Constructor to initialize a Ray
    ///
    /// @param Start Vector
    /// @param Direction Vector
    ///
    CRay(const Vector3<float>& a_rStart=Vector3<float>(),const Vector3<float>& a_rDirection=Vector3<float>());
    /// @brief Destructor to destroy a Ray
    ///
    ~CRay();
public:
    /// @brief Set the Direction
    ///
    /// @param New Direction Vector
    ///
    void SetDirection(Vector3<float>& a_Direction);
    
    /// @brief Return the Start of the Ray
    ///
    /// @returns Start as Vector3<float>
    ///
    Vector3<float> GetStart() const;
    
    /// @brief Return the Direction of the Ray
    ///
    /// @returns Direction as Vector3<float>
    ///
    Vector3<float> GetDirection() const;
    
    /// @brief Return the World Position of a point along the Ray
    ///
    /// @returns Point as Vector3<float>
    ///
    Vector3<float> GetPoint(float a_Distance) const;

    
};

#endif /* _RAY_H_ */
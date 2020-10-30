#ifndef _POINTLIGHT_H_
#define _POINTLIGHT_H_

#include "ilight.h"

class CPointLight : public ILight
{
private:
    /// @brief Color of the Light
    ///
    CColor m_Color;
    /// @brief Position of the Light
    ///
    Vector3<float> m_Position;
    /// @brief Attenuation of the Light
    ///
    float m_Radius;
public:
    /// @brief Constructor to initialize a PointLight
    ///
    /// @param Position of the PointLight
    /// @param Color of the PointLight
    /// @param Radius of the PointLight
    ///
    CPointLight(const Vector3<float>& a_rPosition, CColor a_Color,float a_Radius);
    /// @brief Destructor to destroy a Light
    ///
    ~CPointLight();
public:
    
    /// @brief Return the Position of the Light
    ///
    /// @returns Position as Reference
    ///
    virtual const Vector3<float>& GetPosition() const;
    
    /// @brief Return the Color of the Light
    ///
    /// @param World Position of the pixel defined in here
    ///
    /// @returns Color as Reference
    ///
    virtual const CColor GetColor(const SHit& a_Hit) const;
};


#endif /* _POINTLIGHT_H_ */
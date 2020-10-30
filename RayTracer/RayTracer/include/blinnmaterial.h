#ifndef _BLINNMATERIAL_H_
#define _BLINNMATERIAL_H_

#include "IMaterial.h"
#include "color.h"

/// @brief Material based on Blinn's Formula
///
class CBlinnMaterial : public IMaterial
{
    /// @brief Amount of the Max Reflections
    ///
    enum { MaxReflections = 1000 };

private:
    /// @brief Surface Color
    ///
    CColor m_Diffuse;
    /// @brief Specular Exponent
    ///
    float m_Specular;
    /// @brief Reflection Value
    ///
    float m_Reflection;
    /// @brief Whether or not he should cast a shadow
    ///
    bool m_Shadow;
public:
    /// @brief Constructor to initialize a BlinnMaterial
    ///
    /// @param Color of the Surface
    /// @param Specular Value
    /// @param Reflection Value
    /// @param Whether or not he should cast a shadow
    ///
    CBlinnMaterial(CColor a_Diffuse,float a_Specular,float a_Reflection,bool a_Shadow);

    /// @brief Destructor to destroy a BlinnMaterial
    ///
    ~CBlinnMaterial();
public:

    /// @brief Function to call when a ray hits the Object
    ///
    /// @param Where it has been hit
    /// @param Scene needed for Lights
    /// @param Times the Ray has been reflected
    ///
    /// @returns Color at this point
    ///
    virtual CColor Shade(const SHit& a_rHit, const CScene& a_rScene, int a_Reflected = 0) const;

};

#endif /* _BLINNMATERIAL_H_ */
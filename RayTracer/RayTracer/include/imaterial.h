#ifndef _IMATERIAL_H_
#define _IMATERIAL_H_


///Forward declarations
struct SHit;
class CScene;
class CColor;
class IObject;

/// @brief Interface for different Material types
///
class IMaterial
{
public:

    /// @brief Define Destructor so it can be overloaded
    ///
    virtual ~IMaterial() {}

    /// @brief Function to call when a ray hits the Object
    ///
    /// @param Where it has been hit
    /// @param Scene needed for Lights
    /// @param Times the Ray has been reflected
    ///
    /// @returns Color at this point
    ///
    virtual CColor Shade(const SHit& a_rHit, const CScene& a_rScene, int a_Reflected = 0) const = 0;
};

#endif /* _IMATERIAL_H_ */
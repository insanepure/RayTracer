#ifndef _CAMERA_H_
#define _CAMERA_H_

#include "vector3.h"

/// @brief Camera where the Rays come from
///
class CCamera
{
private:
    /// @brief Position of the Camera
    ///
    Vector3<float> m_Position;
    /// @brief View Plane Normal / Forward Vector
    ///
    Vector3<float> m_Normal;
    /// @brief Up Vector
    ///
    Vector3<float> m_Up;
    /// @brief Left Vector
    ///
    Vector3<float> m_Left;
    /// @brief Top Left Corner
    ///
    Vector3<float> m_TopLeft;
    /// @brief Scaled Right
    ///
    Vector3<float> m_Right;
    /// @brief Scaled Down
    ///
    Vector3<float> m_Down;
    /// @brief View Plane Distance / Near Plane Distance
    ///
    float m_Distance;
    /// @brief Field of View
    ///
    float m_FOV;
    /// @brief Width of the Scene
    ///
    unsigned int m_Width;
    /// @brief Height of the Scene
    ///
    unsigned int m_Height;
    /// @brief Whether the Data need's to be updated or not
    ///
    bool m_Update;
public:
    /// @brief Constructor to initialize a Camera
    ///
    /// @param Position of the Camera
    /// @param View Plane Normal
    /// @param Up Vector
    /// @param View Plane Distance
    /// @param Field of View
    ///
    CCamera(Vector3<float> a_Position=Vector3<float>(0.0f,0.0f,0.0f),
            Vector3<float> a_Normal=Vector3<float>(0.0f,0.0f,1.0f),
            Vector3<float> a_Up=Vector3<float>(0.0f,1.0f,0.0f),
            float a_Distance=1.0f,
            float a_FOV = 3.141592654f*0.5f);
    /// @brief Destructor to destroy a Camera
    ///
    ~CCamera();
public:
    /// @brief Return the Position of the Camera
    ///
    /// @returns Position as Vector3<float>
    ///
    const Vector3<float>& GetPosition() const;
    /// @brief Return the Up Vector of the Camera
    ///
    /// @returns Up Vector as Vector3<float>
    ///
    const Vector3<float>& GetUp() const;
    /// @brief Return the Top Left Vector of the Camera
    ///
    /// @returns TopLeft Vector as Vector3<float>
    ///
    const Vector3<float>& GetTopLeft() const;
    /// @brief Return the scaled Down Vector of the Camera
    ///
    /// @returns Down Vector as Vector3<float>
    ///
    const Vector3<float>& GetScaledDown() const;
    /// @brief Return the scaled Right Vector of the Camera
    ///
    /// @returns Right Vector as Vector3<float>
    ///
    const Vector3<float>& GetScaledRight() const;
    /// @brief Return the View Plane Normal of the Camera
    ///
    /// @returns ViewPlaneNormal as Vector3<float>
    ///
    const Vector3<float>& GetNormal() const;
    /// @brief Return the Left Vector of the Camera
    ///
    /// @returns Left Vector as Vector3<float>
    ///
    const Vector3<float>& GetLeft() const;
    /// @brief Return the ViewPlaneDistance of the Camera
    ///
    /// @returns ViewPlaneDistance as float
    ///
    float GetDistance();
    /// @brief Return the Field of View of the Camera
    ///
    /// @returns Field of View as float
    ///
    float GetFOV();
    /// @brief Update the Camera
    ///
    /// @param Width of the Scene
    /// @param Height of the Scene
    ///
    void Update(unsigned int a_Width, unsigned int a_Height);
};

#endif /* _CAMERA_H_ */
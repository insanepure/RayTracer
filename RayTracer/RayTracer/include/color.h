#ifndef _Color_H_
#define _Color_H_

#include <math.h>

/// @brief Class for CColors
///
class CColor
{
    // ************************************************************************
    // PUBLIC MEMBERS
    // ************************************************************************

public:

    /// @brief Red Value
    ///
    float R;
    /// @brief Green Value
    ///
    float G;
    /// @brief Blue Value
    ///
    float B;
    /// @brief Alpha Value
    ///
    float A;
    /*!
    * @brief Returns a pointer to the internal vector array.
    *
    * @returns A pointer to the internal vector array.
    */
    inline operator float*() const
    {
        return const_cast<float*>(&this->R);
    }

    /*!
    * @brief Indicates whether this instance equals to the specified Vector4<T> instance.
    *
    * @param A Vector4<T> instance.
    *
    * @returns boolean whether the param is the same as this.
    */
    inline bool operator==(const CColor& c) const
    {
        if (this->R != c.R)
            return false;

        if (this->G != c.G)
            return false;

        if (this->B != c.B)
            return false;

        return this->A == c.A;
    }

    /*!
    * @brief Calculates the sum of this instance components' and the
    * specified color components' and returns the result as a new color instance.
    *
    * @param A color instance.
    *
    * @returns A color containing the result of the sum operation.
    */
    inline CColor operator+(const CColor &rhs) const
    {
        return CColor(this->R + rhs.R, this->G + rhs.G, this->B + rhs.B, this->A + rhs.A);
    }

    /*!
    * @brief Adds the specified Color instance to this instance.
    *
    * @param A Color instance.
    *
    * @returns This Color instance.
    */
    inline CColor operator+=(const CColor &rhs)
    {
        this->R += rhs.R; this->G += rhs.G; this->B += rhs.B; this->A += rhs.A;

        return *this;
    }

    /*!
    * @brief Calculates the multiplication of this instance components' and the
    * specified float component and returns the result as a new Color instance.
    *
    * @param A float value.
    *
    * @returns A Color containing the result of the multiplication operation.
    */
    inline CColor operator*(const float &rhs) const
    {
        return CColor(rhs * this->R, rhs * this->G, rhs * this->B,rhs * this->A);
    }

    /*!
    * @brief Calculates the multiplication of this instance components' and the
    * specified vec components' and returns the result as a new Color instance.
    *
    * @param A Color instance.
    *
    * @returns A Color containing the result of the multiplication operation.
    */
    inline CColor operator*(const CColor &rhs) const
    {
        return CColor(rhs.R * this->R, rhs.G * this->G, rhs.B * this->B,rhs.A * this->A);
    }

    /// @brief Creates an instance of CColor
    ///
    CColor()
    {
        this->R = 0;
        this->G = 0;
        this->B = 0;
        this->A = 1.0f;
    }
    /// @brief Creates an instance of CColor
    ///
    /// @param Red Amount
    /// @param Green Amount
    /// @param Blue Amount
    /// @param Alpha Amount
    ///
    CColor(float r, float g, float b, float a = 1.0f)
    {
        this->R = r;
        this->G = g;
        this->B = b;
        this->A = a;
    }
    /// @brief Creates an instance of CColor
    ///
    /// @param RGBA as Integer
    ///
    CColor(int rgba)
    {
        this->R = (rgba >> 24 & 0xff) / 255.0f;
        this->G = (rgba >> 16 & 0xff) / 255.0f;
        this->B = (rgba >> 8 & 0xff) / 255.0f ;
        this->A = (rgba & 0xff) / 255.0f;
    }
    /// @brief Duplicates an instance of CColor
    ///
    /// @returns a RGBA CColor
    ///
    CColor(const CColor& CColor)
    {
        this->R = CColor.R;
        this->G = CColor.G;
        this->B = CColor.B;
        this->A = CColor.A;
    }
    /// @brief Converts ARGB to RGBA
    ///
    /// @param ARGB Value
    ///
    /// @returns a RGBA CColor
    ///
    static CColor FromARGB(int argb)
    {
        return CColor(((argb >> 16) & 0xff) / 255.0f,
            ((argb >> 8) & 0xff) / 255.0f,
            ((argb)& 0xff) / 255.0f,
            ((argb >> 24) & 0xff)/ 255.0f);
    }
    /// @brief Converts RGBA to RGBA
    ///
    /// @param RGBA Value
    ///
    /// @returns a RGBA CColor
    ///
    static CColor FromRGBA(int rgba)
    {
        return CColor(((rgba >> 24) & 0xff) / 255.0f,
            ((rgba >> 16) & 0xff) / 255.0f,
            ((rgba >> 8) & 0xff) / 255.0f,
            (rgba & 0xff)/ 255.0f);
    }
    /// @brief Converts ARGB to RGBA
    ///
    /// @param ARGB Value
    ///
    /// @returns a RGBA CColor
    ///
    static CColor FromABGR(int abgr)
    {
        return CColor((abgr & 0xff) / 255.0f,
            ((abgr >> 8) & 0xff) / 255.0f,
            ((abgr >> 16) & 0xff) / 255.0f,
            ((abgr >> 24) & 0xff)/ 255.0f);
    }
    /// @brief Converts BGRA to RGBA
    ///
    /// @param BGRA Value
    ///
    /// @returns a RGBA CColor
    ///
    static CColor FromBGRA(int bgra)
    {
        return CColor(((bgra >> 8) & 0xff) / 255.0f,
            ((bgra >> 16) & 0xff) / 255.0f,
            ((bgra >> 24) & 0xff) / 255.0f,
            (bgra & 0xff)/ 255.0f);
    }
    /// @brief Converts a CColor to ARGB Integer
    ///
    /// @param a CColor Object
    ///
    /// @returns ARGB as integer
    ///
    static unsigned int ToARGB(const CColor& CColor)
    {
        return (unsigned int)(255 * CColor.A) << 24 |
            (unsigned int)( 255 * CColor.R) << 16 |
            (unsigned int)( 255 * CColor.G) << 8 |
            (unsigned int)( 255 * CColor.B);
    }
    /// @brief Converts a CColor to RGBA Integer
    ///
    /// @param a CColor Object
    ///
    /// @returns RGBA as integer
    ///
    static unsigned int ToRGBA(const CColor& CColor)
    {
        unsigned int value;

        value = (unsigned int)(255 * CColor.A) |
            (unsigned int)(255 * CColor.R) << 24 |
            (unsigned int)(255 * CColor.G) << 16 |
            (unsigned int)(255 * CColor.B) << 8;

        return value;
    }
    /// @brief Converts a CColor to ABGR Integer
    ///
    /// @param a CColor Object
    ///
    /// @returns ABGR as integer
    ///
    static unsigned int ToABGR(const CColor& CColor)
    {
        return (unsigned int)(255 * CColor.A) << 24 |
            (unsigned int)(255 * CColor.B) << 16 |
            (unsigned int)(255 * CColor.G) << 8 |
            (unsigned int)(255 * CColor.R);
    }
    /// @brief Converts a CColor to BGRA Integer
    ///
    /// @param a CColor Object
    ///
    /// @returns BGRA as integer
    ///
    static unsigned int ToBGRA(const CColor& CColor)
    {
        return (unsigned int)(255 * CColor.A) |
            (unsigned int)(255 * CColor.R) << 8 |
            (unsigned int)(255 * CColor.G) << 16 |
            (unsigned int)(255 * CColor.B) << 24;
    }

};

#endif /* _COLOR_H_ */
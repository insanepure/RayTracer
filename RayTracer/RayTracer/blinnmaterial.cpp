#include "include/blinnmaterial.h"
#include "include/scene.h"
#include "include/hit.h"
#include "include/Ray.h"
#include "include/iobject.h"

CBlinnMaterial::CBlinnMaterial(CColor a_Diffuse,float a_Specular,float a_Reflection,bool a_Shadow) : 
    m_Diffuse(a_Diffuse),m_Specular(a_Specular), m_Reflection(a_Reflection), m_Shadow(a_Shadow)
{

}

//*********************************************************************//
//*********************************************************************//

CBlinnMaterial::~CBlinnMaterial()
{

}
//*********************************************************************//
//*********************************************************************//

CColor CBlinnMaterial::Shade(const SHit& a_rHit, const CScene& a_rScene, int a_Reflected) const
{
    CColor color;

    //calculate a vector from the Camera's Position to the Hit Location
    Vector3<float> hitToCamera = Vector3<float>::Normalize(a_rScene.GetCamera().GetPosition()  - a_rHit.Position);

    //Calculate Color from all Lights
    for (auto light : a_rScene.GetLights())
    {
        //Calculate a Vector from the light to the hit position
        Vector3<float> hitToLight = (light->GetPosition() - a_rHit.Position);
        float hitToLightDistance = hitToLight.Length();
        hitToLight = Vector3<float>::Normalize(hitToLight);
        //Add them and normalize, to ge the halfway vector between the viewer and the light source
        Vector3<float> halfVector = Vector3<float>::Normalize(hitToLight + hitToCamera);
        CRay shadowRay(a_rHit.Position+hitToLight, hitToLight);
        
        if (!this->m_Shadow||!a_rScene.Trace(shadowRay, nullptr,hitToLightDistance))
        {

            //Calculate Diffuse Factor
            float diffuseFactor = Vector3<float>::Dot(hitToLight,a_rHit.Normal);
            diffuseFactor = (diffuseFactor > 1.0f) ? 1.0f : diffuseFactor;
            diffuseFactor = (diffuseFactor < 0.0f) ? 0.0f : diffuseFactor;

            //Calculate Specular Factor
            float specularFactor = pow(Vector3<float>::Dot(halfVector,a_rHit.Normal),this->m_Specular);
            specularFactor = (specularFactor > 1.0f) ? 1.0f : specularFactor;
            specularFactor = (specularFactor < 0.0f) ? 0.0f : specularFactor;

            //Add calculated Data
            CColor lightColor = light->GetColor(a_rHit);
            CColor diffuse = this->m_Diffuse * lightColor * diffuseFactor;
            CColor specular = lightColor * specularFactor;

            color += diffuse + specular;
        }
    }
    // Calculate the reflection ray
    // Add normal to position to avoid "reflection acne"


    // Reflection pass - independent from light sources
    float reflectionValue = this->m_Reflection/(a_Reflected+1);
    if(reflectionValue > 0.1f)
    {
        if (a_Reflected < CBlinnMaterial::MaxReflections)
        {
            SHit reflectionHit;

            Vector3<float> hitToCameraReflected = Vector3<float>::Reflection(-hitToCamera,a_rHit.Normal);
            CRay reflectionRay(a_rHit.Position + Vector3<float>::Normalize(hitToCameraReflected), hitToCameraReflected);

            if (a_rScene.Trace(reflectionRay, &reflectionHit,999999999999.0f))
            {
                // Call the shader of the target material if we hit something
                color += reflectionHit.pMaterial->Shade(reflectionHit, a_rScene, a_Reflected+1) * reflectionValue;
            }
        }
    }

    color.A = this->m_Diffuse.A;

    color.R = (color.R > 1.0f) ? 1.0f : color.R;
    color.R = (color.R < 0) ? 0 : color.R;
    color.G = (color.G > 1.0f) ? 1.0f : color.G;
    color.G = (color.G < 0) ? 0 : color.G;
    color.B = (color.B > 1.0f) ? 1.0f : color.B;
    color.B = (color.B < 0) ? 0 : color.B;

    return color;
}
#pragma once
#include "le3_object.h"

#include <cereal/cereal.hpp>

class LE3AmbientLight : public LE3Object
{
public:
    LE3AmbientLight(glm::vec3 color = glm::vec3(1.f), float intensity=0.1f);

    virtual void Update(double deltaTime);
    virtual void Draw();

    template <typename Archive>
    void serialize( Archive & ar )
    {
        LE3Object::serialize(ar);
        // ar(CEREAL_NVP(color), CEREAL_NVP(intensity));
    }

    glm::vec3 GetColor() const;
    void SetColor(glm::vec3 color);
    
    float GetIntensity() const;
    void SetIntensity(float intensity);

protected:
    glm::vec3 color;
    float intensity;
};

CEREAL_REGISTER_TYPE(LE3AmbientLight);
CEREAL_REGISTER_POLYMORPHIC_RELATION(LE3Object, LE3AmbientLight);

#pragma once
#include "pch.h"
#include "elems/element.h"

namespace nelems
{
    class Texture : public Element
    {
    public:
        Texture() = default;
        unsigned int textureId;
        Texture(std::string path);
        void UseTex();
        void update(nshaders::Shader* shader, std::string uniform) override
        {
            shader->set_i1(0, uniform);
        }
        virtual ~Texture();
    };
}

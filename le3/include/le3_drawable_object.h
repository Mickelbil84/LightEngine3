#pragma once

#include "le3_object.h"
#include "le3_material.h"

namespace le3 {
    // The lower priority == the sooner the object is drawn on screen
    enum LE3DrawPriority {
        DRAW_PRIORITY_LOW = 0,
        DRAW_PRIORITY_MEDIUM = 1,
        DRAW_PRIORITY_HIGH = 2,
        DRAW_PRIORITY_UI = 3,
        DRAW_PRIORITY_END // Used for enum iteration, not an actual priority
    };

    class LE3DrawableObject : public LE3Object {
    public:
        LE3DrawableObject(LE3MaterialPtr pMaterial) : 
            m_pMaterial(pMaterial), 
            m_drawPriority(LE3DrawPriority::DRAW_PRIORITY_LOW),
            m_bHidden(false), m_bCastShadow(true)
        {}

        virtual void draw(LE3ShaderPtr shaderOverride) = 0;

        inline LE3DrawPriority getDrawPriority() const { return m_drawPriority; }
        inline void setDrawPriority(LE3DrawPriority drawPriority) { m_drawPriority = drawPriority; }

        inline LE3MaterialPtr& getMaterial() { return m_pMaterial; }
        inline void setMaterial(LE3MaterialPtr pMaterial) { m_pMaterial = pMaterial; }

        inline bool isHidden() const { return m_bHidden; }
        inline void setHidden(bool hidden) { m_bHidden = hidden; }

        inline bool getCastShadow() const { return m_bCastShadow; }
        inline void setCastShadow(bool castShadow) { m_bCastShadow = castShadow; }

        inline void setDrawID(uint32_t drawID) { m_drawID = drawID; } 
        inline uint32_t getDrawID() const { return m_drawID; }

    protected:
        LE3MaterialPtr m_pMaterial;
        LE3DrawPriority m_drawPriority;
        bool m_bHidden, m_bCastShadow;
        uint32_t m_drawID;
    };
    using LE3DrawableObjectPtr = std::shared_ptr<LE3DrawableObject>;
}
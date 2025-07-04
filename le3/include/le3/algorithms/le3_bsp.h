#pragma once

#include <map>
#include <set>
#include <vector>
#include <memory>

#include "graphics/le3_geometry.h"
#include "graphics/le3_drawable_object.h"


namespace le3 {

    const std::string LE3_BSP_MESH_NAME = "__#BSP#";

    enum LE3BSPBrushType {
        LE3_BRUSH_ADDITIVE = 0, LE3_BRUSH_SUBTRACTIVE = 1
    };

    class LE3BSPBrush : public LE3DrawableObject {
    public:
        LE3BSPBrush() : LE3DrawableObject(LE3MaterialPtr()), m_brushType(LE3_BRUSH_ADDITIVE) {}
        LE3_TYPE_RETURN(LE3BSPBrush)

        LE3BSPBrushType getBrushType() const { return m_brushType; }
        void setBrushType(LE3BSPBrushType brushType) { m_brushType = brushType; }

        virtual void draw(LE3ShaderPtr shaderOverride);

    protected:
        LE3BSPBrushType m_brushType;
    };
    using LE3BSPBrushPtr = std::shared_ptr<LE3BSPBrush>;

    struct LE3BSPManager {
    public:
        LE3BSPManager();

        void build();
        void setShowBrushes(bool showBrushes);
        void addBrush(std::weak_ptr<LE3BSPBrush> brush);

        inline std::vector<LE3Vertex> getGeometry() const { return m_geometry; }
        inline std::shared_ptr<LE3Mesh<LE3Vertex>> getGeometryMesh() const { return m_pGeometryMesh; }

    private:
        std::vector<std::weak_ptr<LE3BSPBrush>> m_brushes;   
        std::vector<LE3Vertex> m_geometry; 
        std::shared_ptr<LE3Mesh<LE3Vertex>> m_pGeometryMesh;
    };
}
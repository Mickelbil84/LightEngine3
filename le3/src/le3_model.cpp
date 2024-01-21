#include "le3_model.h"
using namespace le3;

template<typename LE3VertexType>
LE3Model<LE3VertexType>::LE3Model(LE3MeshPtr<LE3VertexType> pMesh, LE3MaterialPtr pMaterial) :
    LE3DrawableObject(pMaterial), m_pMesh(pMesh) {
}

template<typename LE3VertexType>
void LE3Model<LE3VertexType>::draw() {
    if (m_pMaterial) m_pMaterial->apply();
    if (m_pMesh) m_pMesh->draw();
}

namespace le3 {
    template class LE3Model<LE3Vertex3p>;
    template class LE3Model<LE3Vertex3p3c>;
    template class LE3Model<LE3Vertex3p2t3n>;
    template class LE3Model<LE3Vertex3p2t3n3c>;
    template class LE3Model<LE3Vertex3p2t3n3tn3b>;
    template class LE3Model<LE3Vertex3p2t3n3tn3b4b4w>;
}
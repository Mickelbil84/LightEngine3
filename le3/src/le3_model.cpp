#include "le3_model.h"
using namespace le3;

template<typename LE3VertexType>
LE3Model<LE3VertexType>::LE3Model(LE3MeshPtr<LE3VertexType> pMesh, LE3MaterialPtr pMaterial) :
    m_pMesh(pMesh), m_pMaterial(pMaterial) {
}
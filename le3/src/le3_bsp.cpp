#include "le3_bsp.h"
#include "le3_engine_systems.h"
using namespace le3;

#include <fmt/core.h>

namespace le3 {
    constexpr double LE3_BSP_EPS = 1e-5;
    enum LE3BSP_Side {
        IN = -1, ON = 0, OUT = 1
    };

    using LE3BSP_Triangle = std::vector<glm::dvec3>;

    struct LE3BSP_SplitResult {
        std::vector<LE3BSP_Triangle> F_in, F_out, F_on;
    };

    struct LE3BSP_Hyperplane {
    public:
        glm::dvec3 normal;
        double offset;

        LE3BSP_Hyperplane(glm::dvec3 normal, double offset);

        static LE3BSP_Hyperplane fromTriangle(LE3BSP_Triangle triangle);
        static glm::dvec3 getTriangleNormal(LE3BSP_Triangle triangle);

        LE3BSP_Side determinePoint(glm::dvec3 point);
        LE3BSP_SplitResult splitTriangle(LE3BSP_Triangle triangle);
        LE3BSP_SplitResult splitTriangles(std::vector<LE3BSP_Triangle> triangles);
    
    private:
        static LE3BSP_SplitResult _trianglePlaneIsect(LE3BSP_Hyperplane plane, LE3BSP_Triangle triangle);
    };

    class LE3BSP_Node {
    public:
        LE3BSP_Hyperplane plane;
        std::vector<LE3BSP_Triangle> faces;
        std::shared_ptr<LE3BSP_Node> left, right;
        LE3BSP_Side leftVal, rightVal; // "Pointers" to leaves
        
        LE3BSP_Node(LE3BSP_Hyperplane plane, std::vector<LE3BSP_Triangle> faces);

        void getChildHyperplanes(std::vector<LE3BSP_Hyperplane>& res);
        void toTriangleSoup(std::vector<LE3BSP_Triangle>& res);

        static std::vector<LE3BSP_Triangle> toMesh(std::shared_ptr<LE3BSP_Node> root);
    };

    // Note: face normals should point *inwards*
    std::shared_ptr<LE3BSP_Node> buildBSPT(std::vector<LE3BSP_Triangle> faces);

    LE3BSP_Side classifyPoint(std::shared_ptr<LE3BSP_Node> root, glm::dvec3 point, LE3BSP_Side val = IN);
    LE3BSP_Side classifyTriangle(std::shared_ptr<LE3BSP_Node> root, LE3BSP_Triangle triangle, double epsilon = 0.01);

    enum LE3BSP_CSG_Op {
        UNION, ISECT, DIFF
    };

    std::vector<LE3BSP_Triangle> negateFaces(std::vector<LE3BSP_Triangle> faces);
    std::shared_ptr<LE3BSP_Node> CSGOP(LE3BSP_CSG_Op op, std::shared_ptr<LE3BSP_Node> root, std::vector<LE3BSP_Triangle> faces, LE3BSP_Side val = IN);

    std::vector<LE3BSP_Triangle> getCubeFaces(glm::dvec3 offset, glm::dvec3 extent);
    std::string toSTL(std::vector<LE3BSP_Triangle> soup);
}

LE3BSP_Hyperplane::LE3BSP_Hyperplane(glm::dvec3 normal, double offset) :
    normal(normal), offset(offset) {
}

LE3BSP_Hyperplane LE3BSP_Hyperplane::fromTriangle(LE3BSP_Triangle triangle) {
    glm::dvec3 normal = LE3BSP_Hyperplane::getTriangleNormal(triangle);
    double offset = -glm::dot(normal, triangle[0]);
    return LE3BSP_Hyperplane(normal, offset);
}
glm::dvec3 LE3BSP_Hyperplane::getTriangleNormal(LE3BSP_Triangle triangle) {
    glm::dvec3 v1 = triangle[1] - triangle[0];
    glm::dvec3 v2 = triangle[2] - triangle[0];
    return glm::cross(v1, v2);
}

LE3BSP_Side LE3BSP_Hyperplane::determinePoint(glm::dvec3 point) {
    double val = glm::dot(point, this->normal) + this->offset;
    if (abs(val) < LE3_BSP_EPS) return ON;
    if (val > 0) return IN;
    return OUT;
}

LE3BSP_SplitResult LE3BSP_Hyperplane::splitTriangle(LE3BSP_Triangle triangle) {
    LE3BSP_SplitResult res;
    std::set<LE3BSP_Side> sides;
    for (auto vertex : triangle) sides.insert(determinePoint(vertex));

    if (sides.contains(IN) && !sides.contains(OUT)) res.F_in.push_back(triangle);
    else if (!sides.contains(IN) && sides.contains(OUT)) res.F_out.push_back(triangle);
    else if (!sides.contains(IN) && !sides.contains(OUT)) res.F_on.push_back(triangle);
    else {
        res = LE3BSP_Hyperplane::_trianglePlaneIsect(*this, triangle);
    }
    return res;
}

LE3BSP_SplitResult LE3BSP_Hyperplane::splitTriangles(std::vector<LE3BSP_Triangle> triangles) {
    LE3BSP_SplitResult res;
    for (auto triangle : triangles) {
        LE3BSP_SplitResult tmp = splitTriangle(triangle);
        std::copy(tmp.F_in.begin(), tmp.F_in.end(), std::back_inserter(res.F_in));
        std::copy(tmp.F_out.begin(), tmp.F_out.end(), std::back_inserter(res.F_out));
        std::copy(tmp.F_on.begin(), tmp.F_on.end(), std::back_inserter(res.F_on));
    }
    return res;
}

LE3BSP_SplitResult LE3BSP_Hyperplane::_trianglePlaneIsect(LE3BSP_Hyperplane plane, LE3BSP_Triangle triangle) {
    LE3BSP_SplitResult res;

    // Assumpe WLOG that only one vertex is inside plane
    std::map<LE3BSP_Side, int> counts;
    counts[IN] = 0; counts[OUT] = 0; counts[ON] = 0;
    std::vector<LE3BSP_Side> sides;
    for (auto vertex : triangle) sides.push_back(plane.determinePoint(vertex));
    for (auto side : sides) counts[side]++;

    if (counts[IN] > counts[OUT]) {
        plane = LE3BSP_Hyperplane(-plane.normal, -plane.offset);
        LE3BSP_SplitResult tmp = LE3BSP_Hyperplane::_trianglePlaneIsect(plane, triangle);
        res.F_in = tmp.F_out; res.F_out = tmp.F_in;
        return res;
    }

    // WLOG: Make sure that v1 is the one vertex inside
    if (sides[1] == IN) {
        LE3BSP_Triangle tmpTri; 
        tmpTri.push_back(triangle[1]); tmpTri.push_back(triangle[2]); tmpTri.push_back(triangle[0]);
        triangle = tmpTri;
    }
    else if (sides[2] == IN) {
        LE3BSP_Triangle tmpTri; 
        tmpTri.push_back(triangle[2]); tmpTri.push_back(triangle[0]); tmpTri.push_back(triangle[1]);
        triangle = tmpTri;
    }

    // V4: intersection of V1-V2 with plane
    // V5: intersection of V1-V3 with plane
    // line:  l(s) = v1 + s * (vj - v1)
    //   dot(l(s), n) + d = 0
    //   dot(v1, n) + s * dot(vj - v1, n) + d = 0
    //   s = (-d - dot(v1, n)) / dot(vj - v1, n)
    double tmp = -plane.offset - glm::dot(triangle[0], plane.normal);
    double s4 = tmp / glm::dot(triangle[1] - triangle[0], plane.normal);
    double s5 = tmp / glm::dot(triangle[2] - triangle[0], plane.normal);

    glm::dvec3 v4 = triangle[0] + s4 * (triangle[1] - triangle[0]);
    glm::dvec3 v5 = triangle[0] + s5 * (triangle[2] - triangle[0]);

    LE3BSP_Triangle t1, t2, t3;
    t1.push_back(triangle[0]); t1.push_back(v4); t1.push_back(v5);
    t2.push_back(triangle[2]); t2.push_back(v5); t2.push_back(v4);
    t3.push_back(triangle[2]); t3.push_back(v4); t3.push_back(triangle[1]);

    res.F_in.push_back(t1);
    res.F_out.push_back(t2); res.F_out.push_back(t3);
    return res;
}

LE3BSP_Node::LE3BSP_Node(LE3BSP_Hyperplane plane, std::vector<LE3BSP_Triangle> faces) :
    plane(plane), faces(faces), left(nullptr), right(nullptr) {
}

void LE3BSP_Node::getChildHyperplanes(std::vector<LE3BSP_Hyperplane>& res) {
    res.push_back(this->plane);
    if (this->left) this->left->getChildHyperplanes(res);
    if (this->right) this->right->getChildHyperplanes(res);
}

void LE3BSP_Node::toTriangleSoup(std::vector<LE3BSP_Triangle>& res) {
    std::vector<LE3BSP_Hyperplane> planes;
    this->getChildHyperplanes(planes);
    std::vector<LE3BSP_Triangle> curr = this->faces;
    for (auto plane : planes) {
        LE3BSP_SplitResult splitRes = plane.splitTriangles(curr);
        curr.clear();
        std::copy(splitRes.F_in.begin(), splitRes.F_in.end(), std::back_inserter(curr));
        std::copy(splitRes.F_out.begin(), splitRes.F_out.end(), std::back_inserter(curr));
        std::copy(splitRes.F_on.begin(), splitRes.F_on.end(), std::back_inserter(curr));
    }
    std::copy(curr.begin(), curr.end(), std::back_inserter(res));
    if (this->left) this->left->toTriangleSoup(res);
    if (this->right) this->right->toTriangleSoup(res);
}

std::shared_ptr<LE3BSP_Node> le3::buildBSPT(std::vector<LE3BSP_Triangle> faces) {
    LE3BSP_Hyperplane H = LE3BSP_Hyperplane::fromTriangle(faces[0]);
    LE3BSP_SplitResult res = H.splitTriangles(faces);

    std::shared_ptr<LE3BSP_Node> node = std::make_shared<LE3BSP_Node>(H, res.F_on);

    if (res.F_out.size() == 0)
        node->leftVal = glm::dot(H.normal, LE3BSP_Hyperplane::getTriangleNormal(res.F_on[0])) > 0 ? OUT : IN;
    else
        node->left = buildBSPT(res.F_out);
    
    if (res.F_in.size() == 0)
        node->rightVal = glm::dot(H.normal, LE3BSP_Hyperplane::getTriangleNormal(res.F_on[0])) > 0 ? IN : OUT;
    else
        node->right = buildBSPT(res.F_in);
    
    return node;
}

LE3BSP_Side le3::classifyPoint(std::shared_ptr<LE3BSP_Node> root, glm::dvec3 point, LE3BSP_Side val) {
    if (!root) return val;
    LE3BSP_Side s = root->plane.determinePoint(point);
    if (s == OUT) return classifyPoint(root->left, point, root->leftVal);
    if (s == IN) return classifyPoint(root->right, point, root->rightVal);
    LE3BSP_Side l = classifyPoint(root->left, point, root->leftVal);
    LE3BSP_Side r = classifyPoint(root->right, point, root->rightVal);
    if (l == r) return r;
    return ON;
}
LE3BSP_Side le3::classifyTriangle(std::shared_ptr<LE3BSP_Node> root, LE3BSP_Triangle triangle, double epsilon) {
    glm::dvec3 midpoint = (triangle[0] + triangle[1] + triangle[2]) / 3.0;
    glm::dvec3 normal = LE3BSP_Hyperplane::getTriangleNormal(triangle);
    if (classifyPoint(root, midpoint + epsilon * normal) == OUT &&
        classifyPoint(root, midpoint - epsilon * normal) == OUT)
        return OUT;
    return ON;
}

std::vector<LE3BSP_Triangle> le3::negateFaces(std::vector<LE3BSP_Triangle> faces) {
    std::vector<LE3BSP_Triangle> res;
    for (auto face : faces) {
        LE3BSP_Triangle tri;
        tri.push_back(face[2]); tri.push_back(face[1]); tri.push_back(face[0]);
        res.push_back(tri);
    }
    return res;
}
std::shared_ptr<LE3BSP_Node> le3::CSGOP(LE3BSP_CSG_Op op, std::shared_ptr<LE3BSP_Node> root, std::vector<LE3BSP_Triangle> faces, LE3BSP_Side val) {
    if (op == DIFF) return CSGOP(ISECT, root, negateFaces(faces));

    if (!root) {
        if (
            ((op == UNION) && (val == IN)) ||
            ((op == ISECT) && (val == OUT))
        ) return nullptr;

        return buildBSPT(faces);
    }

    LE3BSP_SplitResult res = root->plane.splitTriangles(faces);
    if (res.F_out.size() > 0) root->left = CSGOP(op, root->left, res.F_out, root->leftVal);
    if (res.F_in.size() > 0) root->right = CSGOP(op, root->right, res.F_in, root->rightVal);

    return root;
}

std::vector<LE3BSP_Triangle> le3::getCubeFaces(glm::dvec3 offset, glm::dvec3 extent) {
    std::vector<glm::dvec3> vertices{
        glm::dvec3(-1, -1, -1), glm::dvec3(-1,  1, -1), glm::dvec3( 1,  1, -1), glm::dvec3( 1, -1, -1),
        glm::dvec3(-1, -1,  1), glm::dvec3(-1,  1,  1), glm::dvec3( 1,  1,  1), glm::dvec3( 1, -1,  1),
    };
    for (auto& vertex : vertices) vertex = 0.5 * vertex * extent + offset;
    int faces[] = {
        4, 5, 6, 7,
        0, 3, 2, 1,
        0, 1, 5, 4,
        3, 7, 6, 2, 
        0, 4, 7, 3, 
        1, 2, 6, 5,
    };
    std::vector<LE3BSP_Triangle> triangles;
    for (int i = 0; i < 6; ++i) {
        LE3BSP_Triangle t1, t2;
        t1.push_back(vertices[faces[4*i + 0]]); t1.push_back(vertices[faces[4*i + 1]]); t1.push_back(vertices[faces[4*i + 2]]);
        t2.push_back(vertices[faces[4*i + 0]]); t2.push_back(vertices[faces[4*i + 2]]); t2.push_back(vertices[faces[4*i + 3]]);
        triangles.push_back(t1);
        triangles.push_back(t2);
    }
    return triangles;
}

std::vector<LE3BSP_Triangle> LE3BSP_Node::toMesh(std::shared_ptr<LE3BSP_Node> root) {
    std::vector<LE3BSP_Triangle> clean, raw;
    root->toTriangleSoup(raw);
    for (auto face : raw)
        if (classifyTriangle(root, face) != OUT) 
            clean.push_back(face);
    return clean;
}

std::string le3::toSTL(std::vector<LE3BSP_Triangle> soup) {
    std::string res = "solid le3bsp\n";

    for (auto tri : soup) {
        glm::dvec3 normal = -LE3BSP_Hyperplane::getTriangleNormal(tri);
        res += fmt::format("facet normal {} {} {}\n", normal.x, normal.y, normal.z);
        res += "\touter loop\n";
        for (int i = 0; i < tri.size(); ++i)
            res += fmt::format("\t\tvertex {} {} {}\n", tri[i].x, tri[i].y, tri[i].z);
        res += "\tendloop\n";
        res += "endfacet\n";
    }
    res += "endsolid le3bsp\n";
    return res;
}

// ---------------------------------------------------------------------------------
// ---------------------------------------------------------------------------------
// ---------------------------------------------------------------------------------
// ---------------------------------------------------------------------------------
// ---------------------------------------------------------------------------------
// ---------------------------------------------------------------------------------


void LE3BSPBrush::draw(LE3ShaderPtr shaderOverride) {
    if (shaderOverride) return;
    LE3GetVisualDebug().drawDebugBox(this->getWorldMatrix(), glm::vec3(0.5f, 0.f, 0.125f));
}

LE3BSPManager::LE3BSPManager() {
}

void LE3BSPManager::build() {

    std::shared_ptr<LE3BSP_Node> root = nullptr;

    for (int phase = LE3_BRUSH_ADDITIVE; phase <= LE3_BRUSH_SUBTRACTIVE; ++phase) {
        for (auto brush : m_brushes) {
            LE3BSPBrushPtr brushPtr = brush.lock(); if (!brushPtr) continue;
            if (brushPtr->getBrushType() != phase) continue;

            std::vector<LE3BSP_Triangle> triangles = getCubeFaces(glm::dvec3(0.f), glm::dvec3(1.f));
            for (int i = 0; i < triangles.size(); ++i) {
                for (int j = 0; j < 3; j++) {
                    glm::vec4 tmp = brushPtr->getWorldMatrix() * glm::vec4(triangles[i][j], 1.0);
                    triangles[i][j] = glm::dvec3(tmp);
                }
            }

            if (!root) {
                if (phase == LE3_BRUSH_SUBTRACTIVE) triangles = negateFaces(triangles);
                root = buildBSPT(triangles);
            } else {
                LE3BSP_CSG_Op op = phase == LE3_BRUSH_ADDITIVE ? UNION : DIFF;
                root = CSGOP(op, root, triangles);
            }
        }
    }

    std::vector<LE3BSP_Triangle> soup = LE3BSP_Node::toMesh(root);
    m_geometry.clear();

    for (auto face : soup) {
        glm::vec3 normal = -LE3BSP_Hyperplane::getTriangleNormal(face);
        for (int i = 0; i < 3; i++)
            m_geometry.push_back(vertexFromGLM(
                face[i], glm::vec2(0.f), normal
            ));
    }


}
void LE3BSPManager::setShowBrushes(bool showBrushes) {
    for (auto& brush : m_brushes) {
        std::shared_ptr<LE3BSPBrush> brushPtr = brush.lock();
        if (brushPtr) brushPtr->setHidden(!showBrushes);
    }
}
void LE3BSPManager::addBrush(std::weak_ptr<LE3BSPBrush> brush) {
    m_brushes.push_back(brush);
}
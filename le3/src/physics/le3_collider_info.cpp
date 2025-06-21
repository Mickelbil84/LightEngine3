#include "physics/le3_collider_info.h"
using namespace le3;

std::string le3::LE3ColliderType_toString(LE3ColliderType type) {
    switch(type) {
        case LE3ColliderType::LE3ColliderType_Box: return "Box";
        case LE3ColliderType::LE3ColliderType_Sphere: return "Sphere";
        case LE3ColliderType::LE3ColliderType_Cone: return "Cone";
        case LE3ColliderType::LE3ColliderType_Cylinder: return "Cylinder";
        case LE3ColliderType::LE3ColliderType_Capsule: return "Capsule";
        case LE3ColliderType::LE3ColliderType_ConvexHull: return "ConvexHull";
    }
    return "";
}
LE3ColliderType le3::LE3ColliderType_fromString(const std::string& str) {
    if (str == "Box") return LE3ColliderType::LE3ColliderType_Box;
    if (str == "Sphere") return LE3ColliderType::LE3ColliderType_Sphere;
    if (str == "Cone") return LE3ColliderType::LE3ColliderType_Cone;
    if (str == "Cylinder") return LE3ColliderType::LE3ColliderType_Cylinder;
    if (str == "Capsule") return LE3ColliderType::LE3ColliderType_Capsule;
    if (str == "ConvexHull") return LE3ColliderType::LE3ColliderType_ConvexHull;
    return LE3ColliderType::LE3ColliderType_Box;
}
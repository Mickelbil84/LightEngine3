#include "physics/le3_collider_info.h"
using namespace le3;

std::string le3::LE3ColliderType_toString(LE3ColliderType type) {
    switch(type) {
        case LE3ColliderType::LE3ColliderType_Box: return "Box";
        case LE3ColliderType::LE3ColliderType_Sphere: return "Sphere";
        case LE3ColliderType::LE3ColliderType_Ellipsoid: return "Ellipsoid";
        case LE3ColliderType::LE3ColliderType_ConvexHull: return "ConvexHull";
    }
    return "";
}
LE3ColliderType le3::LE3ColliderType_fromString(const std::string& str) {
    if (str == "Box") return LE3ColliderType::LE3ColliderType_Box;
    if (str == "Sphere") return LE3ColliderType::LE3ColliderType_Sphere;
    if (str == "Ellipsoid") return LE3ColliderType::LE3ColliderType_Ellipsoid;
    if (str == "ConvexHull") return LE3ColliderType::LE3ColliderType_ConvexHull;
    return LE3ColliderType::LE3ColliderType_Box;
}
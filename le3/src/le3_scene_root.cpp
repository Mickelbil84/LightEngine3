#include "le3_scene_root.h"
using namespace le3;

void LE3SceneRoot::updateRecurse(float deltaTime, LE3ObjectPtr object) {
    for (auto child : object->getChildren()) {
        if (!child) continue;
        child->update(deltaTime);
        updateRecurse(deltaTime, child);
    }
}
void LE3SceneRoot::drawRecurse(LE3ObjectPtr object) {
    for (auto child : object->getChildren()) {
        if (!child) continue;
        child->draw();
        drawRecurse(child);
    }
}
#include "graphics/le3_draw_queue.h"
using namespace le3;

#include <fmt/core.h>

#ifdef __linux__
#include <GL/glew.h>
#else
#include <gl/glew.h>
#endif

LE3DrawQueue::LE3DrawQueue() {
    clear();
}

void LE3DrawQueue::clear() {
    for (
        int priority = LE3DrawPriority::DRAW_PRIORITY_LOW; 
        priority <= LE3DrawPriority::DRAW_PRIORITY_END; ++priority) {
        m_drawQueue[(LE3DrawPriority)priority] = std::map<int, std::vector<std::weak_ptr<LE3DrawableObject>>>();
    }
}

void LE3DrawQueue::draw(LE3ShaderPtr shaderOverrideWeak, bool shadowPhase, bool uiPhase) {
    auto shaderOverride = shaderOverrideWeak.lock();
    if (shaderOverride != nullptr) shaderOverride->use();
    for (
        int priority = LE3DrawPriority::DRAW_PRIORITY_LOW; 
        priority <= LE3DrawPriority::DRAW_PRIORITY_END; ++priority) {

        // The last priority has unique treatment as UI should be drawn in a different phase
        if (uiPhase && priority != LE3DrawPriority::DRAW_PRIORITY_UI) continue;
        if (!uiPhase && priority == LE3DrawPriority::DRAW_PRIORITY_UI) continue;
        
        if (priority == LE3DrawPriority::DRAW_PRIORITY_END) glDepthMask(GL_FALSE);
        for (auto kv : m_drawQueue[(LE3DrawPriority)priority]) {

            LE3ShaderPtr shaderWeak = shaderOverride;
            auto shader = shaderWeak.lock();
            for (auto object : kv.second) {
                if (object.expired()) continue;
                auto objectPtr = object.lock();
                if (objectPtr->isHidden() || (!objectPtr->getCastShadow() && shadowPhase)) continue;
                if (!shader && objectPtr->getMaterial().lock()) {
                    shader = objectPtr->getMaterial().lock()->shader.lock();
                }
                if (shader) {
                    shader->use();
                    shader->uniform("model", objectPtr->getWorldMatrix());
                    shader->uniform("objectID", objectPtr->getDrawID());
                    objectPtr->draw(shaderOverride);
                }
            }
        }
        if (priority == LE3DrawPriority::DRAW_PRIORITY_END) glDepthMask(GL_TRUE);
    }
}

void LE3DrawQueue::addObject(std::weak_ptr<LE3DrawableObject> object) {
    auto objectPtr = object.lock();
    if (!objectPtr) return;

    LE3DrawPriority priority = objectPtr->getDrawPriority();
    int key = -1;
    if (objectPtr->getMaterial().lock()) key = objectPtr->getMaterial().lock()->shader.lock()->key();
    if (!m_drawQueue[priority].contains(key)) m_drawQueue[priority][key] = std::vector<std::weak_ptr<LE3DrawableObject>>();
    m_drawQueue[priority][key].push_back(object);
}
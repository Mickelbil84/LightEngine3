#include "le3_draw_queue.h"
using namespace le3;

#include <fmt/core.h>

#ifdef __linux__
#include <GL/glew.h>
#else
#include <gl/glew.h>
#endif

LE3DrawQueue::LE3DrawQueue() {
    for (
        int priority = LE3DrawPriority::DRAW_PRIORITY_LOW; 
        priority <= LE3DrawPriority::DRAW_PRIORITY_END; ++priority) {
        m_drawQueue[(LE3DrawPriority)priority] = std::map<int, std::vector<std::weak_ptr<LE3DrawableObject>>>();
    }
}

void LE3DrawQueue::draw(LE3ShaderPtr shaderOverride, bool shadowPhase) {
    if (shaderOverride != nullptr) shaderOverride->use();
    for (
        int priority = LE3DrawPriority::DRAW_PRIORITY_LOW; 
        priority <= LE3DrawPriority::DRAW_PRIORITY_END; ++priority) {
        
        if (priority == LE3DrawPriority::DRAW_PRIORITY_END) glDepthMask(GL_FALSE);
        for (auto kv : m_drawQueue[(LE3DrawPriority)priority]) {

            LE3ShaderPtr shader = shaderOverride;
            for (auto object : kv.second) {
                if (object.expired()) continue;
                auto objectPtr = object.lock();
                if (objectPtr->isHidden() || (!objectPtr->getCastShadow() && shadowPhase)) continue;
                if (shader == nullptr && objectPtr->getMaterial()) {
                    shader = objectPtr->getMaterial()->shader;
                }
                if (shader) {
                    shader->use();
                    shader->uniform("model", objectPtr->getWorldMatrix());
                    shader->uniform("objectID", objectPtr->getDrawID());
                }
                objectPtr->draw(shaderOverride);
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
    if (objectPtr->getMaterial()) key = objectPtr->getMaterial()->shader->key();
    if (!m_drawQueue[priority].contains(key)) m_drawQueue[priority][key] = std::vector<std::weak_ptr<LE3DrawableObject>>();
    m_drawQueue[priority][key].push_back(object);
}
#include "components/le3ed_wintitle.h"
#include "le3_engine_systems.h"
#include "le3ed_events.h"
#include "le3ed_project.h"
using namespace le3;

#include <algorithm>
#include <fmt/core.h>

void LE3EditorWindowTitle::init() {
    m_pDummyObject = std::make_shared<LE3Object>();
    LE3GetEventManager().subscribe(LE3ED_EVENT_ON_SCENE_LOAD, m_pDummyObject, [this](void* data) { this->OnTitleUpdate(false); });
    LE3GetEventManager().subscribe(LE3ED_EVENT_ON_SCENE_CHANGE, m_pDummyObject, [this](void* data) { this->OnTitleUpdate(true); });
    LE3GetEventManager().subscribe(LE3ED_EVENT_ON_SCENE_SAVE, m_pDummyObject, [this](void* data) { this->OnTitleUpdate(false); });

    m_originalTitle = m_engineState.getWindowTitle();
}

void LE3EditorWindowTitle::OnTitleUpdate(bool pendingSave) {
    m_bPendingSave = pendingSave;

    // std::string title = m_originalTitle + " - ";
    // LE3GetConfig<std::string>("LE3EditorCache.MostRecent")

    std::string shortProjectName = LE3GetConfig<std::string>("LE3EditorCache.MostRecent");
    shortProjectName = shortProjectName.substr(shortProjectName.find_last_of('/') + 1);

    std::string shortSceneName = LE3GetConfig<std::string>("LE3ProjectConfig.LastOpenedScene", "");
    if (shortSceneName.size() > 0)
        shortSceneName = shortSceneName.substr(LE3ED_PROJECT_SCENES_ROOT.size());
    else
        shortSceneName = "[untitled]";

    std::string title = fmt::format("{} - {} | {}",
        m_originalTitle, shortProjectName, shortSceneName
    );
    if (m_bPendingSave) title += " *";

    fmt::print("{}\n", title);

    m_engineState.requestRenameTitle(title);
}
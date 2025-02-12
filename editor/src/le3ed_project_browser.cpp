#include "le3ed_project_browser.h"
using namespace le3;

#include <fmt/core.h>

void LE3EditorProjectBrowser::render() {
    ImGui::Begin("Project Browser", nullptr, 0);
    ImGui::Text("Hello, world!");
    ImGui::End();
}
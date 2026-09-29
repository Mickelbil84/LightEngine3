#pragma once

#include <string>
#include <utility>
#include <vector>

#include "core/le3_game_logic.h"
#include "ui/le3_ui_text_object.h"

namespace le3 {
    ////////////////////////////////////////////////////////////////////////////////////////
    // Game logic with the standard project startup built in:
    // run the bootstrap config (a *.lua file next to the executable), mount the project
    // archives and run their scripts, load the initial scene (adding a default player start
    // when the scene has none), and optionally show an FPS counter.
    // Configure it from the constructor of the derived class via the protected setters.
    ////////////////////////////////////////////////////////////////////////////////////////
    class LE3GameBase : public LE3GameLogic {
    public:
        virtual void init() override;
        virtual void update(float deltaTime) override;
        virtual void render() override;

    protected:
        // Settings; call these from the constructor, before init() runs
        inline void setDisplayFPS(bool displayFPS) { m_bDisplayFPS = displayFPS; }
        inline void setBootstrapFile(std::string filename) { m_bootstrapFile = filename; }
        // Mount an extra archive from the engine data directory (e.g. "demos", "demos.dat") along with the project archives
        inline void addDataArchive(std::string name, std::string filename) { m_dataArchives.push_back({name, filename}); }

        // Register extra Lua bindings here; runs after the bootstrap config and before any project script
        virtual void registerBindings() {}

        // The individual startup steps, in the order init() runs them, for games that need a custom sequence
        void loadBootstrapConfig();
        void loadProjectArchives();
        void loadInitialScene();
        void initFPSDisplay();
        // Call this from update() when overriding it, to keep the FPS counter refreshing
        void updateFPSDisplay(float deltaTime);

    private:
        bool m_bDisplayFPS = false;
        std::string m_bootstrapFile = "bootstrap.lua";
        std::vector<std::pair<std::string, std::string>> m_dataArchives; // (archive name, filename)

        float m_fpsPrintTimer = 0.f;
        LE3UITextObjectPtr m_fpsTextObject;
    };
}

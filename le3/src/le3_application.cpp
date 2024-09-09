#include "le3_application.h"
using namespace le3;

#include <stdexcept>

#include <fmt/core.h>

#ifdef __linux__
#include <GL/glew.h>
#else
#include <gl/glew.h>
#endif
#include <SDL2/SDL.h>

#include <imgui.h>
#include <misc/cpp/imgui_stdlib.h>
#include <backends/imgui_impl_sdl2.h>
#include <backends/imgui_impl_opengl3.h>

#include "le3_engine_systems.h"


struct LE3Application::_Internal {
    _Internal() {}
    std::shared_ptr<SDL_Window> m_pWindow;
    SDL_GLContext m_glContext;
};

LE3Application::LE3Application(std::unique_ptr<LE3GameLogic> pGameLogic) :
    m_pGameLogic(std::move(pGameLogic)),
    m_pInternal(std::make_shared<LE3Application::_Internal>()),
    m_bShouldRun(true) {
    if (m_pGameLogic == nullptr)
        throw std::runtime_error("Cannot start game application with nullptr logic.");
    createSDLKeyMapping();
}

LE3Application::LE3Application() {
    m_pGameLogic = nullptr;
    m_bHeadless = true;
}

void LE3Application::run() {
    init();
    while(m_bShouldRun) {
        _handleNotifys();
        handleInput();
        update();
        render();

        // Update delta time computation
        m_prevTime = m_currTime;
        m_currTime = SDL_GetPerformanceCounter();
        m_deltaTime = (double)((m_currTime - m_prevTime) * 1000 / (double)SDL_GetPerformanceFrequency());
        m_deltaTime *= 0.001;
        m_pGameLogic->m_engineState.m_elapsedTime += m_deltaTime;
        if (m_deltaTime < 1.0 / (double)120) // TODO: move into settings file!
            SDL_Delay(Uint32((1.0 / (double)120 - m_deltaTime) * 1000));
    }
    shutdown();
}

void LE3Application::init() {
    LE3EngineSystems::instance().preload(m_bHeadless);
    if (m_bHeadless) return;
    _initSDL();
    _initOpenGL();
    _initImGui();
    LE3EngineSystems::instance().init();
    m_pGameLogic->init();
}

void LE3Application::handleInput() {
    SDL_Event e;
    LE3Input input;
    input.xrel = 0; input.yrel = 0;
    input.bLeftMouseDown = m_lastInput.bLeftMouseDown; input.bRightMouseDown = m_lastInput.bRightMouseDown;
    input.keyDownEvt.clear(); input.keyUpEvt.clear();
    while (SDL_PollEvent(&e)) {
        if (e.type == SDL_QUIT) m_bShouldRun = false;
        if (e.type == SDL_MOUSEBUTTONDOWN)
        {
            if (e.button.button == SDL_BUTTON_LEFT)
                input.bLeftMouseDown = true;
            if (e.button.button == SDL_BUTTON_RIGHT)
                input.bRightMouseDown = true;
        }
        if (e.type == SDL_MOUSEBUTTONUP)
        {
            if (e.button.button == SDL_BUTTON_LEFT)
                input.bLeftMouseDown = false;
            if (e.button.button == SDL_BUTTON_RIGHT)
                input.bRightMouseDown = false;
        }

        if (e.type == SDL_KEYDOWN) {
            input.keyDownEvt.push_back(m_sdlKeyMapping[e.key.keysym.scancode]);
        }
        if (e.type == SDL_KEYUP) {
            input.keyUpEvt.push_back(m_sdlKeyMapping[e.key.keysym.scancode]);
        }

        if (e.type == SDL_WINDOWEVENT) {
            if (e.window.event == SDL_WINDOWEVENT_RESIZED) {
                SDL_GetWindowSize(m_pInternal->m_pWindow.get(),
                    &m_pGameLogic->m_engineState.m_windowWidth,
                    &m_pGameLogic->m_engineState.m_windowHeight);
            
                for (auto scene : LE3GetSceneManager().getScenes()) {
                    if (scene.second->isRenderDirectly())
                        scene.second->resize(m_pGameLogic->m_engineState.m_windowWidth, m_pGameLogic->m_engineState.m_windowHeight);
                }
            }
        }

        ImGui_ImplSDL2_ProcessEvent(&e);
    }
    SDL_GetRelativeMouseState(&input.xrel, &input.yrel);
    SDL_GetMouseState(&input.mouseX, &input.mouseY);
    getKeyboardInput(input);
    // Editor manager should know about mouse state
    LE3GetEditorManager().setMouseDown(input.bLeftMouseDown);
    LE3GetEditorManager().setMouseRel(input.xrel, input.yrel);

    if (m_pGameLogic->m_engineState.isFocused() || m_pGameLogic->m_engineState.getFocusedOverride())
        m_pGameLogic->handleInput(input);

    m_lastInput = input;
}

void LE3Application::update() {
    // Update ImGui frame
    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplSDL2_NewFrame();
    ImGui::NewFrame();

    m_pGameLogic->m_engineState.m_bFocused = !ImGui::GetIO().WantCaptureMouse;

    m_pGameLogic->update(m_deltaTime);
}

void LE3Application::render() {
    
    glClearColor(0.8f, 0.8f, 0.8f, 1.f); // TODO: Propagate to game config
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    m_pGameLogic->render();

    ImGui::Render();
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

    // Update platform windows
    SDL_Window* backup_current_window = SDL_GL_GetCurrentWindow();
    SDL_GLContext backup_current_context = SDL_GL_GetCurrentContext();
    ImGui::UpdatePlatformWindows();
    ImGui::RenderPlatformWindowsDefault();
    SDL_GL_MakeCurrent(backup_current_window, backup_current_context);

    SDL_GL_SwapWindow(m_pInternal->m_pWindow.get());
}

void LE3Application::shutdown() {
    m_pGameLogic->shutdown();

    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplSDL2_Shutdown();
    ImGui::DestroyContext();

    SDL_GL_DeleteContext(m_pInternal->m_glContext);
    if (m_pInternal->m_pWindow) {
        SDL_DestroyWindow(m_pInternal->m_pWindow.get());
        m_pInternal->m_pWindow = nullptr;
    }
    SDL_Quit();
}

void LE3Application::_initSDL() {
    if (SDL_Init(SDL_INIT_EVERYTHING) < 0)
        throw std::runtime_error(fmt::format("Could not initialize SDL: {}\n", SDL_GetError()));
    
    // TODO: Enumerate largest version of OpenGL and GLSL on device
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
    SDL_GL_SetAttribute(SDL_GL_MULTISAMPLEBUFFERS, 1);
    SDL_GL_SetAttribute(SDL_GL_MULTISAMPLESAMPLES, 16); // TODO: Propagate multisamples into engine config

    Uint32 flags = 0;
    flags |= SDL_WINDOW_OPENGL;
    flags |= SDL_WINDOW_RESIZABLE; // TODO: Propagate resizability (and fullscreen) into engine config
    flags |= SDL_WINDOW_MAXIMIZED;

    // TODO: Propagate window title and size into game config
    m_pInternal->m_pWindow = std::shared_ptr<SDL_Window>(SDL_CreateWindow(
        "LightEngine3 v0.2", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 1200, 800, flags
    ), SDL_DestroyWindow);
    SDL_SetRelativeMouseMode((SDL_bool)m_pGameLogic->m_engineState.m_bReltaiveMouse);

    if (!m_pInternal->m_pWindow)
        throw std::runtime_error(fmt::format("Could not create SDL window: {}\n", SDL_GetError()));
    m_pInternal->m_glContext = SDL_GL_CreateContext(m_pInternal->m_pWindow.get());
    SDL_GetWindowSize(m_pInternal->m_pWindow.get(),
        &m_pGameLogic->m_engineState.m_windowWidth,
        &m_pGameLogic->m_engineState.m_windowHeight);

    m_prevTime = m_currTime = SDL_GetPerformanceCounter();

    // if (false) // TODO: Allow fullscreen on init
        // setFullscreen(true);
}
void LE3Application::_initOpenGL() {
    if (glewInit() != GLEW_OK)
        throw std::runtime_error(fmt::format("Could not init GLEW: {}", (char *)glewGetErrorString(glewInit())));
    
    glEnable(GL_DEPTH_TEST);
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

    glEnable(GL_MULTISAMPLE);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
}
void LE3Application::_initImGui() {
    // Setup Dear ImGui
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO();
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;
    io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;
    // io.ConfigFlags |= ImGuiConfigFlags_ViewportsEnable;

    // When viewports are enabled we tweak WindowRounding/WindowBg so platform windows can look identical to regular ones.
    ImGuiStyle& style = ImGui::GetStyle();
    if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
    {
        style.WindowRounding = 0.0f;
        style.Colors[ImGuiCol_WindowBg].w = 1.0f;
    }

    ImGui_ImplSDL2_InitForOpenGL(m_pInternal->m_pWindow.get(), m_pInternal->m_glContext);
    ImGui_ImplOpenGL3_Init();
    
    style.Alpha = 1.0;
    style.DisabledAlpha = 0.6000000238418579;
    style.WindowPadding = ImVec2(8.0, 8.0);
    style.WindowRounding = 0.0;
    style.WindowBorderSize = 1.0;
    style.WindowMinSize = ImVec2(32.0, 32.0);
    style.WindowTitleAlign = ImVec2(0.0, 0.5);
    style.WindowMenuButtonPosition = ImGuiDir_Left;
    style.ChildRounding = 0.0;
    style.ChildBorderSize = 1.0;
    style.PopupRounding = 0.0;
    style.PopupBorderSize = 1.0;
    style.FramePadding = ImVec2(4.0, 3.0);
    style.FrameRounding = 0.0;
    style.FrameBorderSize = 0.0;
    style.ItemSpacing = ImVec2(8.0, 4.0);
    style.ItemInnerSpacing = ImVec2(4.0, 4.0);
    style.CellPadding = ImVec2(4.0, 2.0);
    style.IndentSpacing = 21.0;
    style.ColumnsMinSpacing = 6.0;
    style.ScrollbarSize = 14.0;
    style.ScrollbarRounding = 9.0;
    style.GrabMinSize = 10.0;
    style.GrabRounding = 0.0;
    style.TabRounding = 4.0;
    style.TabBorderSize = 0.0;
    style.TabMinWidthForCloseButton = 0.0;
    style.ColorButtonPosition = ImGuiDir_Right;
    style.ButtonTextAlign = ImVec2(0.5, 0.5);
    style.SelectableTextAlign = ImVec2(0.0, 0.0);
}

void LE3Application::_handleNotifys() {
    if (m_pGameLogic->m_engineState.m_bWantsQuit) m_bShouldRun = false;
    
    if (m_pGameLogic->m_engineState.m_bWantsRelativeMouse != m_pGameLogic->m_engineState.m_bReltaiveMouse) {
        m_pGameLogic->m_engineState.m_bReltaiveMouse = m_pGameLogic->m_engineState.m_bWantsRelativeMouse;
        SDL_SetRelativeMouseMode((SDL_bool)m_pGameLogic->m_engineState.m_bReltaiveMouse);
    }
}

void LE3Application::getKeyboardInput(LE3Input& input) {
    const Uint8* keyboard = SDL_GetKeyboardState(NULL);
    for (auto kv : m_sdlKeyMapping) input.keys[kv.second] = keyboard[kv.first];
}

void LE3Application::createSDLKeyMapping() {
    m_sdlKeyMapping[SDL_SCANCODE_0] = "KEY_0";
    m_sdlKeyMapping[SDL_SCANCODE_1] = "KEY_1";
    m_sdlKeyMapping[SDL_SCANCODE_2] = "KEY_2";
    m_sdlKeyMapping[SDL_SCANCODE_3] = "KEY_3";
    m_sdlKeyMapping[SDL_SCANCODE_4] = "KEY_4";
    m_sdlKeyMapping[SDL_SCANCODE_5] = "KEY_5";
    m_sdlKeyMapping[SDL_SCANCODE_6] = "KEY_6";
    m_sdlKeyMapping[SDL_SCANCODE_7] = "KEY_7";
    m_sdlKeyMapping[SDL_SCANCODE_8] = "KEY_8";
    m_sdlKeyMapping[SDL_SCANCODE_9] = "KEY_9";
    m_sdlKeyMapping[SDL_SCANCODE_A] = "KEY_A";
    m_sdlKeyMapping[SDL_SCANCODE_AC_BACK] = "KEY_AC_BACK";
    m_sdlKeyMapping[SDL_SCANCODE_AC_BOOKMARKS] = "KEY_AC_BOOKMARKS";
    m_sdlKeyMapping[SDL_SCANCODE_AC_FORWARD] = "KEY_AC_FORWARD";
    m_sdlKeyMapping[SDL_SCANCODE_AC_HOME] = "KEY_AC_HOME";
    m_sdlKeyMapping[SDL_SCANCODE_AC_REFRESH] = "KEY_AC_REFRESH";
    m_sdlKeyMapping[SDL_SCANCODE_AC_SEARCH] = "KEY_AC_SEARCH";
    m_sdlKeyMapping[SDL_SCANCODE_AC_STOP] = "KEY_AC_STOP";
    m_sdlKeyMapping[SDL_SCANCODE_AGAIN] = "KEY_AGAIN";
    m_sdlKeyMapping[SDL_SCANCODE_ALTERASE] = "KEY_ALTERASE";
    m_sdlKeyMapping[SDL_SCANCODE_APOSTROPHE] = "KEY_APOSTROPHE";
    m_sdlKeyMapping[SDL_SCANCODE_APPLICATION] = "KEY_APPLICATION";
    m_sdlKeyMapping[SDL_SCANCODE_AUDIOMUTE] = "KEY_AUDIOMUTE";
    m_sdlKeyMapping[SDL_SCANCODE_AUDIONEXT] = "KEY_AUDIONEXT";
    m_sdlKeyMapping[SDL_SCANCODE_AUDIOPLAY] = "KEY_AUDIOPLAY";
    m_sdlKeyMapping[SDL_SCANCODE_AUDIOPREV] = "KEY_AUDIOPREV";
    m_sdlKeyMapping[SDL_SCANCODE_AUDIOSTOP] = "KEY_AUDIOSTOP";
    m_sdlKeyMapping[SDL_SCANCODE_B] = "KEY_B";
    m_sdlKeyMapping[SDL_SCANCODE_BACKSLASH] = "KEY_BACKSLASH";
    m_sdlKeyMapping[SDL_SCANCODE_BACKSPACE] = "KEY_BACKSPACE";
    m_sdlKeyMapping[SDL_SCANCODE_BRIGHTNESSDOWN] = "KEY_BRIGHTNESSDOWN";
    m_sdlKeyMapping[SDL_SCANCODE_BRIGHTNESSUP] = "KEY_BRIGHTNESSUP";
    m_sdlKeyMapping[SDL_SCANCODE_C] = "KEY_C";
    m_sdlKeyMapping[SDL_SCANCODE_CALCULATOR] = "KEY_CALCULATOR";
    m_sdlKeyMapping[SDL_SCANCODE_CANCEL] = "KEY_CANCEL";
    m_sdlKeyMapping[SDL_SCANCODE_CAPSLOCK] = "KEY_CAPSLOCK";
    m_sdlKeyMapping[SDL_SCANCODE_CLEAR] = "KEY_CLEAR";
    m_sdlKeyMapping[SDL_SCANCODE_CLEARAGAIN] = "KEY_CLEARAGAIN";
    m_sdlKeyMapping[SDL_SCANCODE_COMMA] = "KEY_COMMA";
    m_sdlKeyMapping[SDL_SCANCODE_COMPUTER] = "KEY_COMPUTER";
    m_sdlKeyMapping[SDL_SCANCODE_COPY] = "KEY_COPY";
    m_sdlKeyMapping[SDL_SCANCODE_CRSEL] = "KEY_CRSEL";
    m_sdlKeyMapping[SDL_SCANCODE_CURRENCYSUBUNIT] = "KEY_CURRENCYSUBUNIT";
    m_sdlKeyMapping[SDL_SCANCODE_CURRENCYUNIT] = "KEY_CURRENCYUNIT";
    m_sdlKeyMapping[SDL_SCANCODE_CUT] = "KEY_CUT";
    m_sdlKeyMapping[SDL_SCANCODE_D] = "KEY_D";
    m_sdlKeyMapping[SDL_SCANCODE_DECIMALSEPARATOR] = "KEY_DECIMALSEPARATOR";
    m_sdlKeyMapping[SDL_SCANCODE_DELETE] = "KEY_DELETE";
    m_sdlKeyMapping[SDL_SCANCODE_DISPLAYSWITCH] = "KEY_DISPLAYSWITCH";
    m_sdlKeyMapping[SDL_SCANCODE_DOWN] = "KEY_DOWN";
    m_sdlKeyMapping[SDL_SCANCODE_E] = "KEY_E";
    m_sdlKeyMapping[SDL_SCANCODE_EJECT] = "KEY_EJECT";
    m_sdlKeyMapping[SDL_SCANCODE_END] = "KEY_END";
    m_sdlKeyMapping[SDL_SCANCODE_EQUALS] = "KEY_EQUALS";
    m_sdlKeyMapping[SDL_SCANCODE_ESCAPE] = "KEY_ESCAPE";
    m_sdlKeyMapping[SDL_SCANCODE_EXECUTE] = "KEY_EXECUTE";
    m_sdlKeyMapping[SDL_SCANCODE_EXSEL] = "KEY_EXSEL";
    m_sdlKeyMapping[SDL_SCANCODE_F] = "KEY_F";
    m_sdlKeyMapping[SDL_SCANCODE_F1] = "KEY_F1";
    m_sdlKeyMapping[SDL_SCANCODE_F10] = "KEY_F10";
    m_sdlKeyMapping[SDL_SCANCODE_F11] = "KEY_F11";
    m_sdlKeyMapping[SDL_SCANCODE_F12] = "KEY_F12";
    m_sdlKeyMapping[SDL_SCANCODE_F13] = "KEY_F13";
    m_sdlKeyMapping[SDL_SCANCODE_F14] = "KEY_F14";
    m_sdlKeyMapping[SDL_SCANCODE_F15] = "KEY_F15";
    m_sdlKeyMapping[SDL_SCANCODE_F16] = "KEY_F16";
    m_sdlKeyMapping[SDL_SCANCODE_F17] = "KEY_F17";
    m_sdlKeyMapping[SDL_SCANCODE_F18] = "KEY_F18";
    m_sdlKeyMapping[SDL_SCANCODE_F19] = "KEY_F19";
    m_sdlKeyMapping[SDL_SCANCODE_F2] = "KEY_F2";
    m_sdlKeyMapping[SDL_SCANCODE_F20] = "KEY_F20";
    m_sdlKeyMapping[SDL_SCANCODE_F21] = "KEY_F21";
    m_sdlKeyMapping[SDL_SCANCODE_F22] = "KEY_F22";
    m_sdlKeyMapping[SDL_SCANCODE_F23] = "KEY_F23";
    m_sdlKeyMapping[SDL_SCANCODE_F24] = "KEY_F24";
    m_sdlKeyMapping[SDL_SCANCODE_F3] = "KEY_F3";
    m_sdlKeyMapping[SDL_SCANCODE_F4] = "KEY_F4";
    m_sdlKeyMapping[SDL_SCANCODE_F5] = "KEY_F5";
    m_sdlKeyMapping[SDL_SCANCODE_F6] = "KEY_F6";
    m_sdlKeyMapping[SDL_SCANCODE_F7] = "KEY_F7";
    m_sdlKeyMapping[SDL_SCANCODE_F8] = "KEY_F8";
    m_sdlKeyMapping[SDL_SCANCODE_F9] = "KEY_F9";
    m_sdlKeyMapping[SDL_SCANCODE_FIND] = "KEY_FIND";
    m_sdlKeyMapping[SDL_SCANCODE_G] = "KEY_G";
    m_sdlKeyMapping[SDL_SCANCODE_GRAVE] = "KEY_GRAVE";
    m_sdlKeyMapping[SDL_SCANCODE_H] = "KEY_H";
    m_sdlKeyMapping[SDL_SCANCODE_HELP] = "KEY_HELP";
    m_sdlKeyMapping[SDL_SCANCODE_HOME] = "KEY_HOME";
    m_sdlKeyMapping[SDL_SCANCODE_I] = "KEY_I";
    m_sdlKeyMapping[SDL_SCANCODE_INSERT] = "KEY_INSERT";
    m_sdlKeyMapping[SDL_SCANCODE_J] = "KEY_J";
    m_sdlKeyMapping[SDL_SCANCODE_K] = "KEY_K";
    m_sdlKeyMapping[SDL_SCANCODE_KBDILLUMDOWN] = "KEY_KBDILLUMDOWN";
    m_sdlKeyMapping[SDL_SCANCODE_KBDILLUMTOGGLE] = "KEY_KBDILLUMTOGGLE";
    m_sdlKeyMapping[SDL_SCANCODE_KBDILLUMUP] = "KEY_KBDILLUMUP";
    m_sdlKeyMapping[SDL_SCANCODE_KP_0] = "KEY_KP_0";
    m_sdlKeyMapping[SDL_SCANCODE_KP_00] = "KEY_KP_00";
    m_sdlKeyMapping[SDL_SCANCODE_KP_000] = "KEY_KP_000";
    m_sdlKeyMapping[SDL_SCANCODE_KP_1] = "KEY_KP_1";
    m_sdlKeyMapping[SDL_SCANCODE_KP_2] = "KEY_KP_2";
    m_sdlKeyMapping[SDL_SCANCODE_KP_3] = "KEY_KP_3";
    m_sdlKeyMapping[SDL_SCANCODE_KP_4] = "KEY_KP_4";
    m_sdlKeyMapping[SDL_SCANCODE_KP_5] = "KEY_KP_5";
    m_sdlKeyMapping[SDL_SCANCODE_KP_6] = "KEY_KP_6";
    m_sdlKeyMapping[SDL_SCANCODE_KP_7] = "KEY_KP_7";
    m_sdlKeyMapping[SDL_SCANCODE_KP_8] = "KEY_KP_8";
    m_sdlKeyMapping[SDL_SCANCODE_KP_9] = "KEY_KP_9";
    m_sdlKeyMapping[SDL_SCANCODE_KP_A] = "KEY_KP_A";
    m_sdlKeyMapping[SDL_SCANCODE_KP_AMPERSAND] = "KEY_KP_AMPERSAND";
    m_sdlKeyMapping[SDL_SCANCODE_KP_AT] = "KEY_KP_AT";
    m_sdlKeyMapping[SDL_SCANCODE_KP_B] = "KEY_KP_B";
    m_sdlKeyMapping[SDL_SCANCODE_KP_BACKSPACE] = "KEY_KP_BACKSPACE";
    m_sdlKeyMapping[SDL_SCANCODE_KP_BINARY] = "KEY_KP_BINARY";
    m_sdlKeyMapping[SDL_SCANCODE_KP_C] = "KEY_KP_C";
    m_sdlKeyMapping[SDL_SCANCODE_KP_CLEAR] = "KEY_KP_CLEAR";
    m_sdlKeyMapping[SDL_SCANCODE_KP_CLEARENTRY] = "KEY_KP_CLEARENTRY";
    m_sdlKeyMapping[SDL_SCANCODE_KP_COLON] = "KEY_KP_COLON";
    m_sdlKeyMapping[SDL_SCANCODE_KP_COMMA] = "KEY_KP_COMMA";
    m_sdlKeyMapping[SDL_SCANCODE_KP_D] = "KEY_KP_D";
    m_sdlKeyMapping[SDL_SCANCODE_KP_DBLAMPERSAND] = "KEY_KP_DBLAMPERSAND";
    m_sdlKeyMapping[SDL_SCANCODE_KP_DBLVERTICALBAR] = "KEY_KP_DBLVERTICALBAR";
    m_sdlKeyMapping[SDL_SCANCODE_KP_DECIMAL] = "KEY_KP_DECIMAL";
    m_sdlKeyMapping[SDL_SCANCODE_KP_DIVIDE] = "KEY_KP_DIVIDE";
    m_sdlKeyMapping[SDL_SCANCODE_KP_E] = "KEY_KP_E";
    m_sdlKeyMapping[SDL_SCANCODE_KP_ENTER] = "KEY_KP_ENTER";
    m_sdlKeyMapping[SDL_SCANCODE_KP_EQUALS] = "KEY_KP_EQUALS";
    m_sdlKeyMapping[SDL_SCANCODE_KP_EQUALSAS400] = "KEY_KP_EQUALSAS400";
    m_sdlKeyMapping[SDL_SCANCODE_KP_EXCLAM] = "KEY_KP_EXCLAM";
    m_sdlKeyMapping[SDL_SCANCODE_KP_F] = "KEY_KP_F";
    m_sdlKeyMapping[SDL_SCANCODE_KP_GREATER] = "KEY_KP_GREATER";
    m_sdlKeyMapping[SDL_SCANCODE_KP_HASH] = "KEY_KP_HASH";
    m_sdlKeyMapping[SDL_SCANCODE_KP_HEXADECIMAL] = "KEY_KP_HEXADECIMAL";
    m_sdlKeyMapping[SDL_SCANCODE_KP_LEFTBRACE] = "KEY_KP_LEFTBRACE";
    m_sdlKeyMapping[SDL_SCANCODE_KP_LEFTPAREN] = "KEY_KP_LEFTPAREN";
    m_sdlKeyMapping[SDL_SCANCODE_KP_LESS] = "KEY_KP_LESS";
    m_sdlKeyMapping[SDL_SCANCODE_KP_MEMADD] = "KEY_KP_MEMADD";
    m_sdlKeyMapping[SDL_SCANCODE_KP_MEMCLEAR] = "KEY_KP_MEMCLEAR";
    m_sdlKeyMapping[SDL_SCANCODE_KP_MEMDIVIDE] = "KEY_KP_MEMDIVIDE";
    m_sdlKeyMapping[SDL_SCANCODE_KP_MEMMULTIPLY] = "KEY_KP_MEMMULTIPLY";
    m_sdlKeyMapping[SDL_SCANCODE_KP_MEMRECALL] = "KEY_KP_MEMRECALL";
    m_sdlKeyMapping[SDL_SCANCODE_KP_MEMSTORE] = "KEY_KP_MEMSTORE";
    m_sdlKeyMapping[SDL_SCANCODE_KP_MEMSUBTRACT] = "KEY_KP_MEMSUBTRACT";
    m_sdlKeyMapping[SDL_SCANCODE_KP_MINUS] = "KEY_KP_MINUS";
    m_sdlKeyMapping[SDL_SCANCODE_KP_MULTIPLY] = "KEY_KP_MULTIPLY";
    m_sdlKeyMapping[SDL_SCANCODE_KP_OCTAL] = "KEY_KP_OCTAL";
    m_sdlKeyMapping[SDL_SCANCODE_KP_PERCENT] = "KEY_KP_PERCENT";
    m_sdlKeyMapping[SDL_SCANCODE_KP_PERIOD] = "KEY_KP_PERIOD";
    m_sdlKeyMapping[SDL_SCANCODE_KP_PLUS] = "KEY_KP_PLUS";
    m_sdlKeyMapping[SDL_SCANCODE_KP_PLUSMINUS] = "KEY_KP_PLUSMINUS";
    m_sdlKeyMapping[SDL_SCANCODE_KP_POWER] = "KEY_KP_POWER";
    m_sdlKeyMapping[SDL_SCANCODE_KP_RIGHTBRACE] = "KEY_KP_RIGHTBRACE";
    m_sdlKeyMapping[SDL_SCANCODE_KP_RIGHTPAREN] = "KEY_KP_RIGHTPAREN";
    m_sdlKeyMapping[SDL_SCANCODE_KP_SPACE] = "KEY_KP_SPACE";
    m_sdlKeyMapping[SDL_SCANCODE_KP_TAB] = "KEY_KP_TAB";
    m_sdlKeyMapping[SDL_SCANCODE_KP_VERTICALBAR] = "KEY_KP_VERTICALBAR";
    m_sdlKeyMapping[SDL_SCANCODE_KP_XOR] = "KEY_KP_XOR";
    m_sdlKeyMapping[SDL_SCANCODE_L] = "KEY_L";
    m_sdlKeyMapping[SDL_SCANCODE_LALT] = "KEY_LALT";
    m_sdlKeyMapping[SDL_SCANCODE_LCTRL] = "KEY_LCTRL";
    m_sdlKeyMapping[SDL_SCANCODE_LEFT] = "KEY_LEFT";
    m_sdlKeyMapping[SDL_SCANCODE_LEFTBRACKET] = "KEY_LEFTBRACKET";
    m_sdlKeyMapping[SDL_SCANCODE_LGUI] = "KEY_LGUI";
    m_sdlKeyMapping[SDL_SCANCODE_LSHIFT] = "KEY_LSHIFT";
    m_sdlKeyMapping[SDL_SCANCODE_M] = "KEY_M";
    m_sdlKeyMapping[SDL_SCANCODE_MAIL] = "KEY_MAIL";
    m_sdlKeyMapping[SDL_SCANCODE_MEDIASELECT] = "KEY_MEDIASELECT";
    m_sdlKeyMapping[SDL_SCANCODE_MENU] = "KEY_MENU";
    m_sdlKeyMapping[SDL_SCANCODE_MINUS] = "KEY_MINUS";
    m_sdlKeyMapping[SDL_SCANCODE_MODE] = "KEY_MODE";
    m_sdlKeyMapping[SDL_SCANCODE_MUTE] = "KEY_MUTE";
    m_sdlKeyMapping[SDL_SCANCODE_N] = "KEY_N";
    m_sdlKeyMapping[SDL_SCANCODE_NUMLOCKCLEAR] = "KEY_NUMLOCKCLEAR";
    m_sdlKeyMapping[SDL_SCANCODE_O] = "KEY_O";
    m_sdlKeyMapping[SDL_SCANCODE_OPER] = "KEY_OPER";
    m_sdlKeyMapping[SDL_SCANCODE_OUT] = "KEY_OUT";
    m_sdlKeyMapping[SDL_SCANCODE_P] = "KEY_P";
    m_sdlKeyMapping[SDL_SCANCODE_PAGEDOWN] = "KEY_PAGEDOWN";
    m_sdlKeyMapping[SDL_SCANCODE_PAGEUP] = "KEY_PAGEUP";
    m_sdlKeyMapping[SDL_SCANCODE_PASTE] = "KEY_PASTE";
    m_sdlKeyMapping[SDL_SCANCODE_PAUSE] = "KEY_PAUSE";
    m_sdlKeyMapping[SDL_SCANCODE_PERIOD] = "KEY_PERIOD";
    m_sdlKeyMapping[SDL_SCANCODE_POWER] = "KEY_POWER";
    m_sdlKeyMapping[SDL_SCANCODE_PRINTSCREEN] = "KEY_PRINTSCREEN";
    m_sdlKeyMapping[SDL_SCANCODE_PRIOR] = "KEY_PRIOR";
    m_sdlKeyMapping[SDL_SCANCODE_Q] = "KEY_Q";
    m_sdlKeyMapping[SDL_SCANCODE_R] = "KEY_R";
    m_sdlKeyMapping[SDL_SCANCODE_RALT] = "KEY_RALT";
    m_sdlKeyMapping[SDL_SCANCODE_RCTRL] = "KEY_RCTRL";
    m_sdlKeyMapping[SDL_SCANCODE_RETURN] = "KEY_RETURN";
    m_sdlKeyMapping[SDL_SCANCODE_RETURN2] = "KEY_RETURN2";
    m_sdlKeyMapping[SDL_SCANCODE_RGUI] = "KEY_RGUI";
    m_sdlKeyMapping[SDL_SCANCODE_RIGHT] = "KEY_RIGHT";
    m_sdlKeyMapping[SDL_SCANCODE_RIGHTBRACKET] = "KEY_RIGHTBRACKET";
    m_sdlKeyMapping[SDL_SCANCODE_RSHIFT] = "KEY_RSHIFT";
    m_sdlKeyMapping[SDL_SCANCODE_S] = "KEY_S";
    m_sdlKeyMapping[SDL_SCANCODE_SCROLLLOCK] = "KEY_SCROLLLOCK";
    m_sdlKeyMapping[SDL_SCANCODE_SELECT] = "KEY_SELECT";
    m_sdlKeyMapping[SDL_SCANCODE_SEMICOLON] = "KEY_SEMICOLON";
    m_sdlKeyMapping[SDL_SCANCODE_SEPARATOR] = "KEY_SEPARATOR";
    m_sdlKeyMapping[SDL_SCANCODE_SLASH] = "KEY_SLASH";
    m_sdlKeyMapping[SDL_SCANCODE_SLEEP] = "KEY_SLEEP";
    m_sdlKeyMapping[SDL_SCANCODE_SPACE] = "KEY_SPACE";
    m_sdlKeyMapping[SDL_SCANCODE_STOP] = "KEY_STOP";
    m_sdlKeyMapping[SDL_SCANCODE_SYSREQ] = "KEY_SYSREQ";
    m_sdlKeyMapping[SDL_SCANCODE_T] = "KEY_T";
    m_sdlKeyMapping[SDL_SCANCODE_TAB] = "KEY_TAB";
    m_sdlKeyMapping[SDL_SCANCODE_THOUSANDSSEPARATOR] = "KEY_THOUSANDSSEPARATOR";
    m_sdlKeyMapping[SDL_SCANCODE_U] = "KEY_U";
    m_sdlKeyMapping[SDL_SCANCODE_UNDO] = "KEY_UNDO";
    m_sdlKeyMapping[SDL_SCANCODE_UNKNOWN] = "KEY_UNKNOWN";
    m_sdlKeyMapping[SDL_SCANCODE_UP] = "KEY_UP";
    m_sdlKeyMapping[SDL_SCANCODE_V] = "KEY_V";
    m_sdlKeyMapping[SDL_SCANCODE_VOLUMEDOWN] = "KEY_VOLUMEDOWN";
    m_sdlKeyMapping[SDL_SCANCODE_VOLUMEUP] = "KEY_VOLUMEUP";
    m_sdlKeyMapping[SDL_SCANCODE_W] = "KEY_W";
    m_sdlKeyMapping[SDL_SCANCODE_WWW] = "KEY_WWW";
    m_sdlKeyMapping[SDL_SCANCODE_X] = "KEY_X";
    m_sdlKeyMapping[SDL_SCANCODE_Y] = "KEY_Y";
    m_sdlKeyMapping[SDL_SCANCODE_Z] = "KEY_Z";
    m_sdlKeyMapping[SDL_SCANCODE_INTERNATIONAL1] = "KEY_INTERNATIONAL1";
    m_sdlKeyMapping[SDL_SCANCODE_INTERNATIONAL2] = "KEY_INTERNATIONAL2";
    m_sdlKeyMapping[SDL_SCANCODE_INTERNATIONAL3] = "KEY_INTERNATIONAL3";
    m_sdlKeyMapping[SDL_SCANCODE_INTERNATIONAL4] = "KEY_INTERNATIONAL4";
    m_sdlKeyMapping[SDL_SCANCODE_INTERNATIONAL5] = "KEY_INTERNATIONAL5";
    m_sdlKeyMapping[SDL_SCANCODE_INTERNATIONAL6] = "KEY_INTERNATIONAL6";
    m_sdlKeyMapping[SDL_SCANCODE_INTERNATIONAL7] = "KEY_INTERNATIONAL7";
    m_sdlKeyMapping[SDL_SCANCODE_INTERNATIONAL8] = "KEY_INTERNATIONAL8";
    m_sdlKeyMapping[SDL_SCANCODE_INTERNATIONAL9] = "KEY_INTERNATIONAL9";
    m_sdlKeyMapping[SDL_SCANCODE_LANG1] = "KEY_LANG1";
    m_sdlKeyMapping[SDL_SCANCODE_LANG2] = "KEY_LANG2";
    m_sdlKeyMapping[SDL_SCANCODE_LANG3] = "KEY_LANG3";
    m_sdlKeyMapping[SDL_SCANCODE_LANG4] = "KEY_LANG4";
    m_sdlKeyMapping[SDL_SCANCODE_LANG5] = "KEY_LANG5";
    m_sdlKeyMapping[SDL_SCANCODE_LANG6] = "KEY_LANG6";
    m_sdlKeyMapping[SDL_SCANCODE_LANG7] = "KEY_LANG7";
    m_sdlKeyMapping[SDL_SCANCODE_LANG8] = "KEY_LANG8";
    m_sdlKeyMapping[SDL_SCANCODE_LANG9] = "KEY_LANG9";
}
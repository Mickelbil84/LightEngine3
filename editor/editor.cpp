#define GL_SILENCE_DEPRECATION

#include <le3_application.h>
#include <le3_shader.h>
#include <le3_mesh.h>
#include <le3_primitives.h>
#include <le3_camera.h>
#include <le3_texture.h>
#include <le3_material.h>
#include <le3_scene_root.h>
#include <le3_static_mesh.h>
#include <le3_asset_manager.h>

#include <map>
#include <vector>
#include <glm/gtx/transform.hpp>

#include "noname.h"
#include "editor_glpanel.h"

#include <wx/wxprec.h>
 
#ifndef WX_PRECOMP
    #include <wx/wx.h>
#endif
 
class LE3Editor : public wxApp
{
public:
    virtual bool OnInit();
};

wxIMPLEMENT_APP(LE3Editor);

bool LE3Editor::OnInit()
{
    LE3EditorWindow* window = new LE3EditorWindow(nullptr);
    
    wxBoxSizer* sizer = new wxBoxSizer(wxHORIZONTAL);
    int args[] = {WX_GL_RGBA, WX_GL_DOUBLEBUFFER, WX_GL_DEPTH_SIZE, 16, 0};

    LE3wxOpenGLPanel* glPane = new LE3wxOpenGLPanel((wxFrame*) window->m_OpenGLContainer, args);
    sizer->Add(glPane, 1, wxEXPAND);
    
    window->m_OpenGLContainer->SetSizer(sizer);
    window->m_OpenGLContainer->SetAutoLayout(true);
    
    
    window->Show(true);

    // window->m_treeCtrl6->AddRoot(wxT("Root node test"));

    return true;
}
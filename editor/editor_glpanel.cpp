#include "editor_glpanel.h"

BEGIN_EVENT_TABLE(LE3wxOpenGLPanel, wxGLCanvas)
EVT_MOTION(LE3wxOpenGLPanel::mouseMoved)
EVT_LEFT_DOWN(LE3wxOpenGLPanel::mouseDown)
EVT_LEFT_UP(LE3wxOpenGLPanel::mouseReleased)
EVT_RIGHT_DOWN(LE3wxOpenGLPanel::rightClick)
EVT_LEAVE_WINDOW(LE3wxOpenGLPanel::mouseLeftWindow)
EVT_SIZE(LE3wxOpenGLPanel::resized)
EVT_KEY_DOWN(LE3wxOpenGLPanel::keyPressed)
EVT_KEY_UP(LE3wxOpenGLPanel::keyReleased)
EVT_MOUSEWHEEL(LE3wxOpenGLPanel::mouseWheelMoved)
EVT_PAINT(LE3wxOpenGLPanel::render)
END_EVENT_TABLE()

void LE3wxOpenGLPanel::mouseMoved(wxMouseEvent& event) {}
void LE3wxOpenGLPanel::mouseDown(wxMouseEvent& event) {}
void LE3wxOpenGLPanel::mouseWheelMoved(wxMouseEvent& event) {}
void LE3wxOpenGLPanel::mouseReleased(wxMouseEvent& event) {}
void LE3wxOpenGLPanel::rightClick(wxMouseEvent& event) {}
void LE3wxOpenGLPanel::mouseLeftWindow(wxMouseEvent& event) {}
void LE3wxOpenGLPanel::keyPressed(wxKeyEvent& event) {}
void LE3wxOpenGLPanel::keyReleased(wxKeyEvent& event) {}

#ifndef __APPLE__
const std::string resource_prefix = std::string("../../");
#else
const std::string resource_prefix = std::string("../");
#endif

 
LE3wxOpenGLPanel::LE3wxOpenGLPanel(wxFrame* parent, int* args) :
    wxGLCanvas(parent, wxID_ANY, args, wxDefaultPosition, wxDefaultSize, wxFULL_REPAINT_ON_RESIZE)
{
    m_contextAttribs.CoreProfile().OGLVersion(4, 1).Robust().ResetIsolation().EndList();
	m_context = new wxGLContext(this, nullptr, &m_contextAttribs);
    wxGLCanvas::SetCurrent(*m_context);

    // To avoid flashing on MSW
    SetBackgroundStyle(wxBG_STYLE_CUSTOM);

    glewExperimental = true;
    glewInit();

    glEnable(GL_DEPTH_TEST);

    // ---------------------------
    //   Load Assets
    // ---------------------------
    assets.LoadShader("basic", 
        resource_prefix + "resources/shaders/basic/basic.vs", 
        resource_prefix + "resources/shaders/basic/basic.fs");
    assets.LoadMesh("car", resource_prefix + "resources/models/cars/Audi R8.fbx");
    assets.CreateMaterial("car", "basic");

    // ---------------------------
    //   Create game objects
    // ---------------------------
    camera.SetPosition(glm::vec3(0.f, 0.5f, 5.f));
    root.AppendChild(&camera);

    car.SetPosition(glm::vec3(0.f, 0.f, 2.f));
    car.SetMesh(assets.GetMesh("car"));
    car.SetMaterial(assets.GetMaterial("car"));
    car.SetScale(0.3f);
    car.SetRotation(glm::vec3(-3.14159265f / 2.f, 0.f, -3.14159265f / 2.f));
    root.AppendChild(&car);

}
 
LE3wxOpenGLPanel::~LE3wxOpenGLPanel()
{
	delete m_context;
}

void LE3wxOpenGLPanel::resized(wxSizeEvent& evt)
{
//	wxGLCanvas::OnSize(evt);
	
    Refresh();
}
 
int LE3wxOpenGLPanel::getWidth()
{
    return GetSize().x;
}
 
int LE3wxOpenGLPanel::getHeight()
{
    return GetSize().y;
}
 
 
void LE3wxOpenGLPanel::render( wxPaintEvent& evt )
{
    if(!IsShown()) return;
    
    wxGLCanvas::SetCurrent(*m_context);
    wxPaintDC(this); // only to be used in paint events. use wxClientDC to paint outside the paint event
	
    glClearColor(
            100.f/255.f, 
            149.f/255.f, 
            237.f/255.f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    root.Update(0);

    assets.GetShader("basic")->Use();
    assets.GetShader("basic")->Uniform("view", camera.GetViewMatrix());
    assets.GetShader("basic")->Uniform("projection", camera.GetProjectionMatrix((float)getWidth() / (float)getHeight()));
    root.Draw();
    
    SwapBuffers();
}
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

void LE3wxOpenGLPanel::mouseMoved(wxMouseEvent& event) 
{
    event.Skip();
}
void LE3wxOpenGLPanel::mouseDown(wxMouseEvent& event) 
{
    // m_input.bLeftMouse = true;
    event.Skip();
}
void LE3wxOpenGLPanel::mouseWheelMoved(wxMouseEvent& event) {event.Skip();}
void LE3wxOpenGLPanel::mouseReleased(wxMouseEvent& event)
{
    //  m_input.bLeftMouse = false;
    event.Skip();
}
void LE3wxOpenGLPanel::rightClick(wxMouseEvent& event) {event.Skip();}
void LE3wxOpenGLPanel::mouseLeftWindow(wxMouseEvent& event) {event.Skip();}
void LE3wxOpenGLPanel::keyPressed(wxKeyEvent& event) 
{
    m_input.keyboard[event.GetKeyCode()] = true;
}
void LE3wxOpenGLPanel::keyReleased(wxKeyEvent& event) 
{
    m_input.keyboard[event.GetKeyCode()] = false;
}

 
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
    //   Initialize keys
    // ---------------------------
    m_input.keyboard['W'] = false;
    m_input.keyboard['S'] = false;
    m_input.keyboard['A'] = false;
    m_input.keyboard['D'] = false;

    // ---------------------------
    //   Setup timer
    // ---------------------------
    m_timer.Bind(wxEVT_TIMER, &LE3wxOpenGLPanel::update, this);
    m_timer.Start(5);

    m_prevTime = m_currTime = wxGetLocalTimeMillis();
    m_lastMouse = wxGetMousePosition();

    // ---------------------------
    //   Create framebuffer
    // ---------------------------
    glGenFramebuffers(1, &m_outFramebuffer);
    glBindFramebuffer(GL_FRAMEBUFFER, m_outFramebuffer);

    GLuint bufferTexture, depthTexture;
    glGenTextures(1, &bufferTexture);
    glBindTexture(GL_TEXTURE_2D, bufferTexture);

    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, PS1_RESOLUTION_WIDTH, PS1_RESOLUTION_HEIGHT, 0, GL_RGB, GL_UNSIGNED_BYTE, NULL);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);  

    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, bufferTexture, 0);  

    glGenTextures(1, &depthTexture);
    glBindTexture(GL_TEXTURE_2D, depthTexture);

    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, PS1_RESOLUTION_WIDTH, PS1_RESOLUTION_HEIGHT, 0, GL_RGB, GL_UNSIGNED_BYTE, NULL);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST); 
    glTexImage2D(
        GL_TEXTURE_2D, 0, GL_DEPTH24_STENCIL8, PS1_RESOLUTION_WIDTH, PS1_RESOLUTION_HEIGHT, 0, 
        GL_DEPTH_STENCIL, GL_UNSIGNED_INT_24_8, NULL
    );

    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_TEXTURE_2D, depthTexture, 0);  

    if(glCheckFramebufferStatus(GL_FRAMEBUFFER) == GL_FRAMEBUFFER_COMPLETE)
        std::cout << "FB Complete@!!" << std::endl;
    else
        std::cout << glCheckFramebufferStatus(GL_FRAMEBUFFER) << m_outFramebuffer << std::endl;

    glBindFramebuffer(GL_FRAMEBUFFER, 0);

    #ifdef PS1GRAPHICS
    LE3Texture::g_bPS1TextureMode = true;
    #endif

}
 
void LE3wxOpenGLPanel::update(wxTimerEvent& evt)
{
    wxPoint newPos = wxGetMousePosition();
    wxPoint relPos = ScreenToClient(newPos);
    m_input.mouseX = relPos.x;
    m_input.mouseY = relPos.y;
    m_input.screenWidth = getWidth();
    m_input.screenHeight = getHeight();
    m_input.relativeMouseX = ((float) m_input.mouseX  / (float) m_input.screenWidth - 0.5f) * 2.f;
    m_input.relativeMouseY = -((float) m_input.mouseY  / (float) m_input.screenHeight - 0.5f) * 2.f;
    m_input.xrel = newPos.x - m_lastMouse.x;
    m_input.yrel = newPos.y - m_lastMouse.y;
    m_lastMouse = newPos;

    if (GetRect().Contains(ScreenToClient(newPos)))
    {
        // Register mouse click events only inside the viewport
        wxMouseState mouseState = wxGetMouseState();
        m_input.bLeftMouse = mouseState.LeftIsDown();
        m_input.bRightMouse = mouseState.RightIsDown();
    }
    else
    {
        m_input.bLeftMouse = false;
        m_input.bRightMouse = false;
    }

    m_currTime = wxGetLocalTimeMillis();
    wxLongLong delta = m_currTime - m_prevTime;
    m_deltaTime = (float)delta.ToDouble() / 1000.0;
    m_prevTime = m_currTime;

    m_editor->HandleInput(m_input);
    m_editor->Update(m_deltaTime);
    Refresh();
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

    #ifndef PS1GRAPHICS
    
        glViewport(0, 0, getWidth() * GetContentScaleFactor(), getHeight() * GetContentScaleFactor());
        glClearColor(0.1f, 0.1f, 0.1f, 1.f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        m_editor->Render(getWidth() * GetContentScaleFactor(), getHeight() * GetContentScaleFactor());

    #else
        glBindFramebuffer(GL_FRAMEBUFFER, m_outFramebuffer);
        glViewport(0, 0, PS1_RESOLUTION_WIDTH, PS1_RESOLUTION_HEIGHT);
        glClearColor(0.1f, 0.1f, 0.1f, 1.f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

            m_editor->Render(getWidth(), getHeight());

        glBindFramebuffer(GL_DRAW_FRAMEBUFFER, 0);
        glViewport(0, 0, getWidth() * GetContentScaleFactor(), getHeight() * GetContentScaleFactor());
        glClearColor(0.7f, 0.7f, 0.7f, 1.f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        glBlitFramebuffer(0, 0, PS1_RESOLUTION_WIDTH, PS1_RESOLUTION_HEIGHT, 0, 0, getWidth() * GetContentScaleFactor(), getHeight() * GetContentScaleFactor(), 
            GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT, GL_NEAREST);


    #endif
    
    SwapBuffers();
}
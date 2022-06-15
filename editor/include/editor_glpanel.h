#pragma once
#include <gl/glew.h>

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

#include "editor.h"

#include "wx/wx.h"
#include "wx/time.h"
#include "wx/glcanvas.h"


class LE3wxOpenGLPanel : public wxGLCanvas
{
public:
	LE3Editor* m_editor;
	LE3EditorInput m_input;

private:
    wxGLContext* m_context;
    wxGLContextAttrs m_contextAttribs;
	wxTimer m_timer;
	wxLongLong m_prevTime;
	wxLongLong m_currTime;
	float m_deltaTime;
	wxPoint m_lastMouse;

public:
    LE3wxOpenGLPanel(wxFrame* parent, int* args);
    virtual ~LE3wxOpenGLPanel();

    void resized(wxSizeEvent& evt);

    int getWidth();
    int getHeight();

	void update(wxTimerEvent& evt);
    void render(wxPaintEvent& evt);
    
	// events
	void mouseMoved(wxMouseEvent& event);
	void mouseDown(wxMouseEvent& event);
	void mouseWheelMoved(wxMouseEvent& event);
	void mouseReleased(wxMouseEvent& event);
	void rightClick(wxMouseEvent& event);
	void mouseLeftWindow(wxMouseEvent& event);
	void keyPressed(wxKeyEvent& event);
	void keyReleased(wxKeyEvent& event);
    
	DECLARE_EVENT_TABLE()
};
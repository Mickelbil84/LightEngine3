#pragma once

#include "wx/wx.h"

const int gEditorLookAroundKey = wxKeyCode::WXK_SHIFT;

//-----------------
// Gizmo settings
//-----------------
const float gGizmoAxisThickness = 0.005f;
const float gGizmoAxisLength = 0.3f;
const float gGizmoConeThicnkess = 1.5f * gGizmoAxisThickness;
const float gGizmoConeLength = 3.f * gGizmoAxisThickness;
const float gGizmoScaleFactor = 0.5f;
const float gGizmoSelectionDist = 0.05f;
const float gGizmoDragSpeed = 20.f;

/* ------------------------------------------------------

   OpenGL Render - Std3D

--------------------------------------------------------*/

#ifndef _RENDER_
#define _RENDER_

#include "FrustumG.h"

void drawPoints(const FrustumG& frustum);

void drawEdges(const FrustumG& frustum);

void drawPlanes(const FrustumG& frustum);

void drawNormals(const FrustumG& frustum);

void drawFrustum(const FrustumG& frustum, bool draw_axes);

void drawAxes();

void drawAABox(const AABox& box, float r, float g, float b);

#endif


/* ------------------------------------------------------

   OpenGL Render - Std3D

--------------------------------------------------------*/

#ifndef _RENDER_
#define _RENDER_

#include "FrustumG.h"

void drawPoints(const FrustumG& frustum);

void drawLines(const FrustumG& frustum);

void drawPlanes(const FrustumG& frustum);

void drawNormals(const FrustumG& frustum);

void drawFrustum(const FrustumG& frustum);

void drawAxes();

void drawAABox(const AABox& box, float r, float g, float b);

//void drawRenderArray(const CRenderArray& array);

//void drawRenderObject(const CRenderObject& renderElement);

//void drawCircle(CCircle& circle);

#endif


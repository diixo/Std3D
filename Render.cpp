
/* ------------------------------------------------------

   OpenGL Render - Std3D

--------------------------------------------------------*/

#include <windows.h>
#include <GL/gl.h>

#include "Render.h"
#include "View.hpp"


void drawAABox(const AABox& box, float r, float g, float b)
{
   glDisable(GL_CULL_FACE);
   glBegin(GL_LINE_LOOP);

   glColor4f(r, g, b, 1.f);

   glVertex3f( box.position().x,             0.f,  box.position().z);
   glVertex3f((box.position()+box.size()).x, 0.f,  box.position().z);
   glVertex3f((box.position()+box.size()).x, 0.f, (box.position()+box.size()).z);
   glVertex3f( box.position().x,             0.f, (box.position()+box.size()).z);

   glEnd();
   glEnable(GL_CULL_FACE);
};


void drawPoints(const FrustumG& frustum)
{
   glBegin(GL_POINTS);

   glColor4f(1.f, 1.f, 1.f, 1.f);

   glVertex3f(frustum.mNTL.x, frustum.mNTL.y, frustum.mNTL.z);
   glVertex3f(frustum.mNTR.x, frustum.mNTR.y, frustum.mNTR.z);
   glVertex3f(frustum.mNBL.x, frustum.mNBL.y, frustum.mNBL.z);
   glVertex3f(frustum.mNBR.x, frustum.mNBR.y, frustum.mNBR.z);

   glVertex3f(frustum.mFTL.x, frustum.mFTL.y, frustum.mFTL.z);
   glVertex3f(frustum.mFTR.x, frustum.mFTR.y, frustum.mFTR.z);
   glVertex3f(frustum.mFBL.x, frustum.mFBL.y, frustum.mFBL.z);
   glVertex3f(frustum.mFBR.x, frustum.mFBR.y, frustum.mFBR.z);

   glEnd();
}


void drawEdges(const FrustumG& frustum)
{
   glEnable(GL_CULL_FACE);
   glBegin(GL_LINE_LOOP);

   glColor4f(0.f, 1.f, 0.f, 1.f);

   //near mClipPlanesane
   glVertex3f(frustum.mNTL.x, frustum.mNTL.y, frustum.mNTL.z);
   glVertex3f(frustum.mNTR.x, frustum.mNTR.y, frustum.mNTR.z);
   glVertex3f(frustum.mNBR.x, frustum.mNBR.y, frustum.mNBR.z);
   glVertex3f(frustum.mNBL.x, frustum.mNBL.y, frustum.mNBL.z);
   glEnd();

   glBegin(GL_LINE_LOOP);
   glColor4f(0.f, 1.f, 0.f, 1.f);
   //far mClipPlanesane
   glVertex3f(frustum.mFTR.x, frustum.mFTR.y, frustum.mFTR.z);
   glVertex3f(frustum.mFTL.x, frustum.mFTL.y, frustum.mFTL.z);
   glVertex3f(frustum.mFBL.x, frustum.mFBL.y, frustum.mFBL.z);
   glVertex3f(frustum.mFBR.x, frustum.mFBR.y, frustum.mFBR.z);
   glEnd();

   glBegin(GL_LINE_LOOP);
   glColor4f(0.f, 1.f, 0.f, 1.f);
   //bottom mClipPlanesane
   glVertex3f(frustum.mNBL.x, frustum.mNBL.y, frustum.mNBL.z);
   glVertex3f(frustum.mNBR.x, frustum.mNBR.y, frustum.mNBR.z);
   glVertex3f(frustum.mFBR.x, frustum.mFBR.y, frustum.mFBR.z);
   glVertex3f(frustum.mFBL.x, frustum.mFBL.y, frustum.mFBL.z);
   glEnd();

   glBegin(GL_LINE_LOOP);
   glColor4f(0.f, 1.f, 0.f, 1.f);
   //top mClipPlanesane
   glVertex3f(frustum.mNTR.x, frustum.mNTR.y, frustum.mNTR.z);
   glVertex3f(frustum.mNTL.x, frustum.mNTL.y, frustum.mNTL.z);
   glVertex3f(frustum.mFTL.x, frustum.mFTL.y, frustum.mFTL.z);
   glVertex3f(frustum.mFTR.x, frustum.mFTR.y, frustum.mFTR.z);
   glEnd();

   glBegin(GL_LINE_LOOP);
   glColor4f(0.f, 1.f, 0.f, 1.f);
   //left mClipPlanesane
   glVertex3f(frustum.mNTL.x, frustum.mNTL.y, frustum.mNTL.z);
   glVertex3f(frustum.mNBL.x, frustum.mNBL.y, frustum.mNBL.z);
   glVertex3f(frustum.mFBL.x, frustum.mFBL.y, frustum.mFBL.z);
   glVertex3f(frustum.mFTL.x, frustum.mFTL.y, frustum.mFTL.z);
   glEnd();

   glBegin(GL_LINE_LOOP);
   glColor4f(0.f, 1.f, 0.f, 1.f);
   // right mClipPlanesane
   glVertex3f(frustum.mNBR.x, frustum.mNBR.y, frustum.mNBR.z);
   glVertex3f(frustum.mNTR.x, frustum.mNTR.y, frustum.mNTR.z);
   glVertex3f(frustum.mFTR.x, frustum.mFTR.y, frustum.mFTR.z);
   glVertex3f(frustum.mFBR.x, frustum.mFBR.y, frustum.mFBR.z);

   glEnd();
   glEnable(GL_CULL_FACE);
}


void drawPlanes(const FrustumG& frustum)
{
   glDisable(GL_CULL_FACE);

   glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

   glColor4f(0.5f, 0.5f, 0.5f, 0.4f);

   glBegin(GL_QUADS);

   //near mClipPlanesane
   glVertex3f(frustum.mNTL.x, frustum.mNTL.y, frustum.mNTL.z);
   glVertex3f(frustum.mNTR.x, frustum.mNTR.y, frustum.mNTR.z);
   glVertex3f(frustum.mNBR.x, frustum.mNBR.y, frustum.mNBR.z);
   glVertex3f(frustum.mNBL.x, frustum.mNBL.y, frustum.mNBL.z);

   //far mClipPlanesane
   glVertex3f(frustum.mFTR.x, frustum.mFTR.y, frustum.mFTR.z);
   glVertex3f(frustum.mFTL.x, frustum.mFTL.y, frustum.mFTL.z);
   glVertex3f(frustum.mFBL.x, frustum.mFBL.y, frustum.mFBL.z);
   glVertex3f(frustum.mFBR.x, frustum.mFBR.y, frustum.mFBR.z);

   //bottom mClipPlanesane
   glVertex3f(frustum.mNBL.x, frustum.mNBL.y, frustum.mNBL.z);
   glVertex3f(frustum.mNBR.x, frustum.mNBR.y, frustum.mNBR.z);
   glVertex3f(frustum.mFBR.x, frustum.mFBR.y, frustum.mFBR.z);
   glVertex3f(frustum.mFBL.x, frustum.mFBL.y, frustum.mFBL.z);

   //top mClipPlanesane
   glVertex3f(frustum.mNTR.x, frustum.mNTR.y, frustum.mNTR.z);
   glVertex3f(frustum.mNTL.x, frustum.mNTL.y, frustum.mNTL.z);
   glVertex3f(frustum.mFTL.x, frustum.mFTL.y, frustum.mFTL.z);
   glVertex3f(frustum.mFTR.x, frustum.mFTR.y, frustum.mFTR.z);

   //left mClipPlanesane
   glVertex3f(frustum.mNTL.x, frustum.mNTL.y, frustum.mNTL.z);
   glVertex3f(frustum.mNBL.x, frustum.mNBL.y, frustum.mNBL.z);
   glVertex3f(frustum.mFBL.x, frustum.mFBL.y, frustum.mFBL.z);
   glVertex3f(frustum.mFTL.x, frustum.mFTL.y, frustum.mFTL.z);

   // right mClipPlanesane
   glVertex3f(frustum.mNBR.x, frustum.mNBR.y, frustum.mNBR.z);
   glVertex3f(frustum.mNTR.x, frustum.mNTR.y, frustum.mNTR.z);
   glVertex3f(frustum.mFTR.x, frustum.mFTR.y, frustum.mFTR.z);
   glVertex3f(frustum.mFBR.x, frustum.mFBR.y, frustum.mFBR.z);

   glEnd();
   glEnable(GL_CULL_FACE);
}


void drawNormals(const FrustumG& frustum)
{
   Vec3 a, b;

   glDisable(GL_CULL_FACE);
   glBegin(GL_LINES);

   glColor4f(1.f, 1.f, 1.f, 1.f);

   // near
   a = (frustum.mNTR + frustum.mNTL + frustum.mNBR + frustum.mNBL) * 0.25f;
   b = a + frustum.mClipPlanes[FrustumG::P_NEAR].normal;
   glVertex3f(a.x, a.y, a.z);
   glVertex3f(b.x, b.y, b.z);

   // far
   a = (frustum.mFTR + frustum.mFTL + frustum.mFBR + frustum.mFBL) * 0.25f;
   b = a + frustum.mClipPlanes[FrustumG::P_FAR].normal;
   glVertex3f(a.x, a.y, a.z);
   glVertex3f(b.x, b.y, b.z);

   // left
   a = (frustum.mFTL + frustum.mFBL + frustum.mNBL + frustum.mNTL) * 0.25f;
   b = a + frustum.mClipPlanes[FrustumG::P_LEFT].normal;
   glVertex3f(a.x, a.y, a.z);
   glVertex3f(b.x, b.y, b.z);

   // right
   a = (frustum.mFTR + frustum.mNBR + frustum.mFBR + frustum.mNTR) * 0.25f;
   b = a + frustum.mClipPlanes[FrustumG::P_RIGHT].normal;
   glVertex3f(a.x, a.y, a.z);
   glVertex3f(b.x, b.y, b.z);

   // top
   a = (frustum.mFTR + frustum.mFTL + frustum.mNTR + frustum.mNTL) * 0.25f;
   b = a + frustum.mClipPlanes[FrustumG::P_TOP].normal;
   glVertex3f(a.x, a.y, a.z);
   glVertex3f(b.x, b.y, b.z);

   // bottom
   a = (frustum.mFBR + frustum.mFBL + frustum.mNBR + frustum.mNBL) * 0.25f;
   b = a + frustum.mClipPlanes[FrustumG::P_BOTTOM].normal;
   glVertex3f(a.x, a.y, a.z);
   glVertex3f(b.x, b.y, b.z);

   glEnd();
   glEnable(GL_CULL_FACE);
}


void drawAxes()
{
   float offset = 1.5;

   glEnable(GL_CULL_FACE);
   glBegin(GL_LINES);

   glColor4f(1.f, 0.3f, 0.f, 1.f);   // X-axis
   glVertex3f(0, 0, 0);
   glVertex3f(offset, 0, 0);

   glColor4f(0.5f, 1.f, 0.f, 1.f);  // Y-axis
   glVertex3f(0, 0, 0);
   glVertex3f(0, offset, 0);

   glColor4f(0.f, 0.f, 1.f, 1.f);   // Z-axis
   glVertex3f(0, 0, 0);
   glVertex3f(0, 0, offset);

   glEnd();
   glDisable(GL_CULL_FACE);
}


void drawFrustum(const FrustumG& frustum)
{
   //drawPoints(frustum);
   drawEdges(frustum);
   drawNormals(frustum);
   drawPlanes(frustum);
}


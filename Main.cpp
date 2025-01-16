/* ------------------------------------------------------

   View Frustum Culling - Std3D

--------------------------------------------------------*/


#include <stdlib.h>
#include <GL/glut.h>

#include <stdio.h>

#include "FrustumG.h"
#include "Render.h"
#include "Matrix.hpp"
#include "View.hpp"

#include <time.h>


float nearP = 1.0f, farP = 100.0f, Radius = 60.f;
float angle = 45.f, farF = 15.f;

int frame = 0, timebase = 0;

int frustumOn = 1;
int spheresDrawn = 0;
int spheresTotal = 0;


SPosition position(10.f, 60.f, Radius, Vec3());
CView view(position);

Vec3 p(0,0,-5), l(0,0,0), u(0,1,0); // pos,lookAt,up

FrustumG frustum;


void changeSize(int w, int h) 
{
   // Prevent a divide by zero, when window is too short
   // (you cant make a window of zero width).
   if(h == 0)
      h = 1;

   const float ratio = float(w) / float(h);

   // Reset the coordinate system before modifying
   glMatrixMode(GL_PROJECTION);
   glLoadIdentity();

   // Set the viewport to be the entire window
   glViewport(0, 0, w, h);

   // Set the correct perspective.
   gluPerspective(30.f, ratio, nearP, farP);

   //frustum.setCamInternals(angle, w, h, nearP, farF);
}


void render()
{
   spheresTotal=0;
   spheresDrawn=0;

   int cntr = 0;
   float r = 0.2f;

   for (int i = -40; i < 40; i +=4)
   {
      for (int k = -40; k < 40; k+=4)
      {
         spheresTotal++;
         Vec3 a(i, 0, k);
         if (!frustumOn || (frustum.sphereInFrustum(a, r) == FrustumG::INSIDE))
         {
            ++cntr;

            glPushMatrix();
            glTranslatef(i,0,k);
            glColor3f(0,1,0);
            glutSolidSphere(r, 5, 5);
            glPopMatrix();
            spheresDrawn++;
         }
         else if (!frustumOn || (frustum.sphereInFrustum(a, r) == FrustumG::INTERSECT))
         {
            ++cntr;

            glPushMatrix();
            glTranslatef(i,0,k);
            glColor3f(1,1,0);
            glutSolidSphere(r, 5, 5);
            glPopMatrix();
            spheresDrawn++;
         }
         else
         {
            ++cntr;

            glPushMatrix();
            glTranslatef(i,0,k);
            glColor3f(1,0,0);
            glutSolidSphere(r, 5, 5);
            glPopMatrix();
         }
      }
   }
   drawAxes();
   drawFrustum(frustum);
}


void renderScene()
{
   char title[150];
   float fps;

   glClearColor(0.f, 0.f, 0.f, 0.f);
   glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

   glMatrixMode(GL_MODELVIEW);

   view.update(position);

   glLoadMatrixf(view.getView());

   frustum.update(p, l, u);

   render();

   frame++;

   int t_ms = glutGet(GLUT_ELAPSED_TIME);

   if (t_ms - timebase > 1000)
   {
      fps = float(frame*1000)/float(t_ms - timebase);
      timebase = t_ms;
      frame = 0;
      sprintf_s(title, "Frustum_Spheres( Drawn=%d, Total=%d ) FPS=%.1f, R=%.1f, pitch=%.1f, yaw=%.1f (w-s, a-d, q-e, z-x, t-g, y-h, u-j, r)",
         spheresDrawn, spheresTotal, fps, position.mRadius, position.mPitch, position.mYaw);
      glutSetWindowTitle(title);
   }

   glutSwapBuffers();
}


void keyboard(unsigned char a, int x, int y)
{
   const float speed = 1.f;

   switch (a)
   {
      case 'w':   // move view forward
      case 'W':
         position.mLookAt -= view.dir() * speed;
         break;

      case 's':   // move view backward
      case 'S':
         position.mLookAt += view.dir() * speed;
         break;

      case 'd':   // move view right
      case 'D':
         position.mLookAt += view.right() * 0.5f;
         break;

      case 'a':   // move view left
      case 'A':
         position.mLookAt -= view.right() * 0.5f;
         break;

      case 'q':   // yaw back rotate
      case 'Q':
         position.setYaw(-speed);
         break;

      case 'e':   // yaw rotate
      case 'E':
         position.setYaw(speed);
         break;

      case 't':   // pitch-up
      case 'T':
         position.setPitch(speed);
         break;

      case 'g':   // pitch-down
      case 'G':
         position.setPitch(-speed);
         break;

      case '+':   // zoom-in
         position.setRadius(-speed);
         break;

      case '-':   // zoom-out
         position.setRadius(speed);
         break;

      case 'u':   // view-up
      case 'U':
         position = SPosition(90.f, position.mYaw, position.mRadius, position.mLookAt);
         break;

      case 'j':   // jump view-down
      case 'J':
         position = SPosition(10.f, position.mYaw, position.mRadius, position.mLookAt);
         break;

      case 'r':   // reset to default params
      case 'R':
         p = Vec3(0.f, 0.f, -5.f);
         l = Vec3(0.f, 0.f, 0.f);
         u = Vec3(0.f, 1.f, 0.f);
         position = SPosition(10.f, 60.f, Radius, Vec3());
         break;

      case 'x':   // scroll frustum right
      case 'X':
         p += view.scroll_right() * 0.5f;
         l += view.scroll_right() * 0.5f;
         break;

      case 'z':   // scroll frustum left
      case 'Z':
         p -= view.scroll_right() * 0.5f;
         l -= view.scroll_right() * 0.5f;
         break;

      case 'y':   // scroll frustum forward
      case 'Y':
         p -= view.scroll_dir() * 0.5f;
         l -= view.scroll_dir() * 0.5f;
         break;

      case 'h':   // scroll frustum backward
      case 'H':
         p += view.scroll_dir() * 0.5f;
         l += view.scroll_dir() * 0.5f;
         break;
      
      case 'f':
      case 'F':
         frustumOn = !frustumOn;
         break;

      case 'p':
      case 'P':
         frustum.print();
         break;

      case 27: 
         exit(0);
         break;
   }
}


void viewer(int argc, char **argv)
{
   glutInit(&argc, argv);
   glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
   glutInitWindowPosition(100, 50);
   glutInitWindowSize(800, 600);
   glutCreateWindow("Camera View");

   glutDisplayFunc(renderScene);
   glutIdleFunc(renderScene);
   glutReshapeFunc(changeSize);
   glutKeyboardFunc(keyboard);

   //glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);

   glBlendFunc(GL_SRC_ALPHA,GL_ONE);			
   glClearColor(0.f, 0.f, 0.f, 0.f);		
   glClearDepth(1.0);							
   glDepthFunc(GL_LESS);								
   glEnable(GL_DEPTH_TEST);							
   glShadeModel(GL_SMOOTH);
   glEnable(GL_BLEND);
   glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);	

   frustum.setCamInternals(angle, 640, 640, nearP, farF);

   frustum.update(p, l, u);

   glutMainLoop();
}


int main(int argc, char **argv)
{
   viewer(argc, argv);
   return 0;
}


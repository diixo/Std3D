/* ------------------------------------------------------

   View Frustum Culling - Std3D

--------------------------------------------------------*/


#include <stdlib.h>
#include <GL/glut.h>

#include <stdio.h>

#include "FrustumG.h"
#include "Render.h"
#include "Matrix.hpp"

#include <time.h>


float nearP = 1.0f, farP = 100.0f, Radius = 60.f;
float angle = 45.f, ratio= 1.f, farF = 15.f;

int frame = 0, timebase = 0;

int frustumOn = 1;
int spheresDrawn = 0;
int spheresTotal = 0;


CPosition position(10.f, 60.f, Radius);
CMovement movement(Vec3(0.f, 10.f, Radius), Vec3(), Vec3(0.f, 1.f, 0.f));

bool mode = true;
Vec3 p(0,0,-5), l(0,0,0), u(0,1,0); // pos,lookAt,up

FrustumG frustum;


void changeSize(int w, int h) 
{
   // Prevent a divide by zero, when window is too short
   // (you cant make a window of zero width).
   if(h == 0)
      h = 1;

   ratio = float(w) / float(h);

   // Reset the coordinate system before modifying
   glMatrixMode(GL_PROJECTION);
   glLoadIdentity();

   // Set the viewport to be the entire window
   glViewport(0, 0, w, h);

   // Set the correct perspective.
   gluPerspective(30.f, ratio, nearP, farP);

   frustum.setCamInternals(angle, w, h, nearP, farF);
}


void render()
{
   spheresTotal=0;
   spheresDrawn=0;

   int cntr = 0;

   for (int i = -40; i < 40; i +=4)
   {
      for(int k = -40; k < 40; k+=4)
      {
         spheresTotal++;
         Vec3 a(i, 0, k);
         if (!frustumOn || (frustum.sphereInFrustum(a, 0.5) == FrustumG::INSIDE))
         {
            ++cntr;

            glPushMatrix();
            glTranslatef(i,0,k);
            glColor3f(0,1,0);
            glutSolidSphere(0.2, 5, 5);
            glPopMatrix();
            spheresDrawn++;
         }
         else if(!frustumOn || (frustum.sphereInFrustum(a, 0.5) == FrustumG::INTERSECT))
         {
            ++cntr;

            glPushMatrix();
            glTranslatef(i,0,k);
            glColor3f(1,1,0);
            glutSolidSphere(0.2, 5, 5);
            glPopMatrix();
            spheresDrawn++;
         }
         else
         {
            ++cntr;

            glPushMatrix();
            glTranslatef(i,0,k);
            glColor3f(1,0,0);
            glutSolidSphere(0.2, 5, 5);
            glPopMatrix();
            spheresDrawn++;
         }
      }
   }
   drawAxes();
   drawFrustum(frustum);
}


void renderScene(void)
{
   char title[100];
   float fps,time;

   glClearColor(0.f, 0.f, 0.f, 0.f);
   glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

   glMatrixMode(GL_MODELVIEW);

   if (mode)
   {
      Matrix4x4 viewMtx = position.calculateLookAt();
      glLoadMatrixf(viewMtx.m);
   }
   else
   {
      Matrix4x4 viewMtx = movement.calculateLookAt();
      glLoadMatrixf(viewMtx.m);
   }

   frustum.update(p, l, u);

   render();

   frame++;

   time = glutGet(GLUT_ELAPSED_TIME);
   if (time - timebase > 1000)
   {
      fps = frame*1000.0/(time-timebase);
      timebase = time;
      frame = 0;
      sprintf_s(title, "Spheres( Drawn=%d, Total=%d ) FPS=%.1f, Mode=%d, R=%.1f, pitch=%.2f, yaw=%.2f",
         spheresDrawn, spheresTotal, fps, int(mode), position.mRadius, position.mPitch, position.mYaw);
      glutSetWindowTitle(title);
   }

   glutSwapBuffers();
}


void keyboard(unsigned char a, int x, int y)
{
   const float speed = 1.f;

   Vec3 v;

   switch(a)
   {
      case 'w':
      case 'W':
         position.mPitch = normalize360(position.mPitch + speed);
         movement.pitch += speed;
         break;

      case 's':
      case 'S':
         position.mPitch = normalize360(position.mPitch - speed);
         movement.pitch -= speed;
         break;

      case 'q':
      case 'Q':
         if (mode) position.mLookAt.x -= speed;
         else movement.yaw -= speed;
         break;

      case 'e':
      case 'E':
         if (mode) position.mLookAt.x += speed;
         else movement.yaw += speed;
         break;

      case 'a':
      case 'A':
         position.mYaw = normalize360(position.mYaw - speed);
         break;

      case 'd':
      case 'D':
         position.mYaw = normalize360(position.mYaw + speed);
         break;

      case 't':
      case 'T':
         if (mode) position.mLookAt.z += speed;
         else movement.side += speed;
         break;

      case 'g':
      case 'G':
         if (mode) position.mLookAt.z -= speed;
         else movement.side -= speed;
         break;

      case '+':
         position += speed;
         movement.forward += speed;
         //view.movement -= 2.f*speed;
         break;

      case '-':
         position -= speed;
         movement.forward -= speed;
         //view.movement += 2.f*speed;
         break;

      case 'u':   // up-view
      case 'U':
         position = CPosition(90.f, 0.f, Radius);
         break;

      case 'r':
      case 'R':
         p.set(0, 0, -5);
         l.set(0, 0, 0);
         u.set(0, 1, 0);
         break;

      case 'm':
      case 'M':
         {
            mode = !mode;
            position = CPosition(10.f, 60.f, Radius);
            movement = CMovement(Vec3(0.f, 10.f, Radius), Vec3(), Vec3(0.f, 1.f, 0.f));
         }
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
   glutInitWindowSize(640, 640);
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


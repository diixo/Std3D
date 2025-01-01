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


float nearP = 1.0f, farP = 100.0f;
float angle = 45.f, ratio= 1.f;

int frame = 0, timebase = 0;

int frustumOn = 1;
int spheresDrawn = 0;
int spheresTotal = 0;


CPosition position(10.f, 0.f, 75.f);
CMovement movement(Vec3(0.f, 10.f, -75.f), Vec3(), Vec3(0.f, 1.f, 0.f));

bool mode = true;
Vec3 p(0,0,-5), l(0,0,0), u(0,1,0);

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

   frustum.setCamInternals(angle, w, h, nearP, 15);
}


void render()
{
   spheresTotal=0;
   spheresDrawn=0;

   int cntr = 0;

   for (int i = -40; i < 40; i+=4)
   {
      for(int k =  -40; k < 40; k+=4) 
      {
         spheresTotal++;
         Vec3 a(i,0,k);
         if (!frustumOn || (frustum.sphereInFrustum(a,0.5) == FrustumG::INSIDE)) 
         {
            ++cntr;

            glPushMatrix();
            glTranslatef(i,0,k);
            glColor3f(0,1,0);
            glutSolidSphere(0.2,5,5);
            glPopMatrix();
            spheresDrawn++;
         }
         else if(!frustumOn || (frustum.sphereInFrustum(a,0.5) == FrustumG::INTERSECT))
         {
            ++cntr;

            glPushMatrix();
            glTranslatef(i,0,k);
            glColor3f(1,1,0);
            glutSolidSphere(0.2,5,5);
            glPopMatrix();
            spheresDrawn++;
         }
         else
         {
            ++cntr;

            glPushMatrix();
            glTranslatef(i,0,k);
            glColor3f(1,0,0);
            glutSolidSphere(0.2,5,5);
            glPopMatrix();
            spheresDrawn++;
         }
      }
   }

   drawFrustum(frustum);
   drawAxes();
}


void renderScene(void)
{
   char title[80];
   float fps,time;

   glClearColor(0.f, 0.f, 0.f, 0.f);
   glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

   glMatrixMode(GL_MODELVIEW);

   // CView::makeWorldToCamTest(eye, lookAt, up);

   Matrix4x4 viewMtx0 = movement.calculateView();
   Matrix4x4 viewMtx1 = position.calculateView();

   if (mode)
   {
      glLoadMatrixf( viewMtx1.m );
   }
   else
   {
      glLoadMatrixf( viewMtx0.m );
   }

   frustum.setPosition(p, l, u);

   render();

   frame++;

   time = glutGet(GLUT_ELAPSED_TIME);
   if (time - timebase > 1000)
   {
      fps = frame*1000.0/(time-timebase);
      timebase = time;
      frame = 0;
      sprintf(title, "CamView v0.1   Spheres Drawn= %d, Total Spheres= %d, FPS= %8.2f",
         spheresDrawn, spheresTotal, fps);
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
      case '+': 
         position.movement -= 2.f*speed;
         movement.forward  += speed;
         //view.movement     -= 2.f*speed;
         break;

      case '-': 
         position.movement += 2.f*speed;
         movement.forward  -= speed;
         //view.movement     += 2.f*speed;
         break;

      case 'w': 
      case 'W': 
         position.camPitch += speed;
         movement.pitch    += speed;
         //view.camPitch     += speed;
         break;

      case 's': 
      case 'S': 
         position.camPitch -= speed;
         movement.pitch    -= speed;
         //view.camPitch     -= speed;
         break;

      case 'q': 
      case 'Q': 
         movement.yaw -= speed;
         //view.camYaw -= speed;
         break;

      case 'e': 
      case 'E': 
         movement.yaw += speed;
         //view.camYaw += speed;
         break;

      case 'a': 
      case 'A':
         position.worldYaw -= speed;
         //view.worldYaw     -= speed;
         break;

      case 'd': 
      case 'D': 
         position.worldYaw += speed;
         //view.worldYaw     += speed;
         break;

      case 't':
      case 'T':
         movement.side += speed;
         break;

      case 'g':
      case 'G':
         movement.side -= speed;
         break;

      case 'r':
      case 'R':
         p.set(0,0,-5);
         l.set(0,0,0);
         u.set(0,1,0);
         break;

      case 'm':
      case 'M':
         {
            mode = !mode;
            position = CPosition(10.f, 0.f, 75.f);
            movement = CMovement(Vec3(0.f, 10.f, -75.f), Vec3(), Vec3(0.f, 1.f, 0.f));
         }
         break;

      case 'f':
      case 'F':
         frustumOn = !frustumOn;

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


   glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);

   glBlendFunc(GL_SRC_ALPHA,GL_ONE);			
   glClearColor(0.f, 0.f, 0.f, 0.f);		
   glClearDepth(1.0);							
   glDepthFunc(GL_LESS);								
   glEnable(GL_DEPTH_TEST);							
   glShadeModel(GL_SMOOTH);
   glEnable(GL_BLEND);
   glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);	

   //glEnable(GL_CULL_FACE);

   frustum.setCamInternals(angle, 640, 640, nearP, 20.f);

   frustum.setPosition(p,l,u);

   glutMainLoop();
}


int main(int argc, char **argv)
{
   viewer(argc, argv);

   return 0;
}


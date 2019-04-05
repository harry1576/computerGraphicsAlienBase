//  ========================================================================
//  COSC363: Computer Graphics (2019); CSSE  University of Canterbury.
//
//  FILE NAME: Skybox.cpp
//  See Lab03.pdf for details
//  ========================================================================

#include <iostream>
#include <GL/freeglut.h>
#include <cmath>
#include "loadTGA.h"
#include "castle.cpp"
#include "rocket.cpp"
using namespace std;

#define GL_CLAMP_TO_EDGE 0x812F   //To get rid of seams between textures
float lookAngle = 0.0;      //Camera rotation
float eye_z, eye_x;
double distance_from_origin = 0;
double angle = 0;  //Rotation angle for viewing
double player_x = -15;
double player_z = 166;
float cam_hgt = 500; //Camera height

GLuint texId[7];

void stars(GLfloat x, GLfloat y, GLfloat z){
   glBegin(GL_POINTS);
   glColor3f(1.0, 0.0, 0.0);
   glVertex3f(x, y, z);
   glEnd();
}


void loadGLTextures()               // Load bitmaps And Convert To Textures
{
    glGenTextures(7, texId);        // Create texture ids
    // *** left ***
    glBindTexture(GL_TEXTURE_2D, texId[0]);
    loadTGA("left.tga");
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

    // *** front ***
    glBindTexture(GL_TEXTURE_2D, texId[1]);
    loadTGA("front.tga");
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

    // *** right ***
    glBindTexture(GL_TEXTURE_2D, texId[2]);
    loadTGA("right.tga");
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

    // *** back***
    glBindTexture(GL_TEXTURE_2D, texId[3]);
    loadTGA("back.tga");
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

    // *** top ***
    glBindTexture(GL_TEXTURE_2D, texId[4]);
    loadTGA("top.tga");
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

    // *** down ***
    glBindTexture(GL_TEXTURE_2D, texId[5]);
    loadTGA("down4.tga");
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);


    glBindTexture(GL_TEXTURE_2D, texId[6]);
    loadTGA("wall2.tga");
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);


    glTexEnvi(GL_TEXTURE_ENV,GL_TEXTURE_ENV_MODE,GL_REPLACE);
}

void drawRocket()
{	
	int N = 9;
	
	float vy[N] = {-18,-15, -10, -6, 0.0};
	float vx[N] = {0,26.25,45,56.25,60,56.25};
	float vz[N] = {0};

	float wx[N], wy[N], wz[N];
	
    
    for(int j = 0; j < 36; j++)
    {
    for(int i = 0; i < N; i++)
    {
        wx[i]= vx[i] * cos(10*(M_PI/180)) + vz[i] * sin(10*(M_PI/180));
        wy[i] = vy[i];
        wz[i] = -vx[i] * sin(10*(M_PI/180)) + vz[i] * cos(10*(M_PI/180));

    }

    glBegin(GL_TRIANGLE_STRIP);


        for(int i = 0; i < N; i++)
        {

            if(i > 0)
            {
            normal( wx[i-1], wy[i-1], wz[i-1],vx[i-1], vy[i-1], vz[i-1],vx[i], vy[i], vz[i]);
            }

            glVertex3f(vx[i], vy[i], vz[i]);
            if(i > 0)
            {
                normal( wx[i-1], wy[i-1], wz[i-1],vx[i], vy[i], vz[i],wx[i], wy[i], wz[i]);
            }

            glVertex3f(wx[i], wy[i], wz[i]);
        }
        for(int i = 0; i < N; i++)
        {
            vx[i] = wx[i];
            vy[i] = wy[i];
            vz[i] = wz[i];
        }
    }

	
     glEnd();
     
     for( int x = 0; x < 360; x+= 60)
     {
     glPushMatrix();
     	glRotatef(x,  0,  1,  0);

		 glTranslatef(30, 0, 0);
		 glPushMatrix();
			 
			 glTranslatef(0, -20, 0);
			 glColor3f(1.00f, 0.00f, 1.0f);
			 glRotatef(30,  0,  0,  1);
			 glScalef (3,40,3);
			 glutSolidCube(1);
		glPopMatrix();
		glPushMatrix();
			glTranslatef(9.5, -38, 0);
			glRotatef(90,  1,  0,  0);
			glutSolidTorus(3,3,10, 10);
		glPopMatrix();
	glPopMatrix();
	}
	



    
	 
	 glPushMatrix();
	     
	     glTranslatef(0, 3, 0);
	     glColor3f(1.00f, 0.00f, 1.0f);
	     glutSolidSphere(20,50,50);
	     
	glPopMatrix();

    
    glFlush();
}

//========================================================================================

void skybox(){

  glEnable(GL_TEXTURE_2D);
  ////////////////////// LEFT WALL ///////////////////////
  glBindTexture(GL_TEXTURE_2D, texId[0]);
  //glColor3f(1, 0, 0);    //<<<<<<<<<<<< Remove the statements that assign color to the sides of the cube

  glBegin(GL_QUADS);
  glTexCoord2f(0.0, 0.0);
  glVertex3f(-1000,  0, 1000);
  glTexCoord2f(1.0, 0.0);
  glVertex3f(-1000, 0., -1000);
  glTexCoord2f(1.0, 1.0);
  glVertex3f(-1000, 1000., -1000);
  glTexCoord2f(0.0, 1.0);
  glVertex3f(-1000, 1000, 1000);
  glEnd();

  ////////////////////// FRONT WALL ///////////////////////
  glBindTexture(GL_TEXTURE_2D, texId[1]);
  //glColor3f(0, 1, 0);
  glBegin(GL_QUADS);
  glTexCoord2f(0.0, 0.0);
  glVertex3f(-1000,  0, -1000);
  glTexCoord2f(1.0, 0.0);
  glVertex3f(1000, 0., -1000);
  glTexCoord2f(1.0, 1.0);
  glVertex3f(1000, 1000, -1000);
  glTexCoord2f(0.0, 1.0);
  glVertex3f(-1000,  1000, -1000);
  glEnd();

 //////////////////////// RIGHT WALL ///////////////////////
  glBindTexture(GL_TEXTURE_2D, texId[2]);
  glColor3f(0, 0, 1);
  glBegin(GL_QUADS);
  glTexCoord2f(0.0, 0.0);
  glVertex3f(1000,  0, -1000);
  glTexCoord2f(1.0, 0.0);
  glVertex3f(1000, 0, 1000);
  glTexCoord2f(1.0, 1.0);
  glVertex3f(1000, 1000,  1000);
  glTexCoord2f(0.0, 1.0);
  glVertex3f(1000,  1000,  -1000);
  glEnd();


  //////////////////////// REAR WALL ////////////////////////
  glBindTexture(GL_TEXTURE_2D, texId[3]);
  glColor3f(1, 1, 0);
  glBegin(GL_QUADS);
  glTexCoord2f(0.0, 0.0);
  glVertex3f( 1000, 0, 1000);
  glTexCoord2f(1.0, 0.0);
  glVertex3f(-1000, 0,  1000);
  glTexCoord2f(1.0, 1.0);
  glVertex3f(-1000, 1000,  1000);
  glTexCoord2f(0.0, 1.0);
  glVertex3f( 1000, 1000, 1000);
  glEnd();

  ///////////////////////// TOP //////////////////////////
  glBindTexture(GL_TEXTURE_2D, texId[4]);
  glColor3f(1, 0, 1);
  glBegin(GL_QUADS);
  glTexCoord2f(1.0, 0.0);
  glVertex3f(-1000, 1000, -1000);
  glTexCoord2f(1.0, 1.0);
  glVertex3f(1000, 1000,  -1000);
  glTexCoord2f(0.0, 1.0);
  glVertex3f(1000, 1000,  1000);
  glTexCoord2f(0.0, 0.0);
  glVertex3f(-1000, 1000, 1000);
  glEnd();

  /////////////////////// FLOOR //////////////////////////
  glBindTexture(GL_TEXTURE_2D, texId[5]);
  glColor3f(0, 1, 1);
  glBegin(GL_QUADS);
  glTexCoord2f(1.0, 1.0);
  glVertex3f(-1000, 0., 1000);
  glTexCoord2f(1.0, 0.0);
  glVertex3f(1000, 0.,  1000);
  glTexCoord2f(0.0, 0.0);
  glVertex3f(1000, 0., -1000);
  glTexCoord2f(0.0, 1.0);
  glVertex3f(-1000, 0., -1000);
  glEnd();


  glDisable(GL_TEXTURE_2D);


}

//---------------------------------------------------------------------
void initialise(void)
{
    loadGLTextures();

    glEnable(GL_DEPTH_TEST);
    glEnable(GL_TEXTURE_2D);
    glEnable(GL_NORMALIZE);
    glClearColor (0.0, 0.0, 0.0, 0.0);

    glMatrixMode (GL_PROJECTION);
    glLoadIdentity ();
    //gluPerspective(50.0, 1, 100.0, 2000.0);   //Perspective projection
    glFrustum(-4, 4, -4, 4, 6, 2000);  //The camera view volume

}

//---------------------------------------------------------------------
void display(void)
{
    glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();


    gluLookAt(player_x, cam_hgt, player_z, player_x + cos(-angle * (M_PI/180)), cam_hgt, player_z + sin(-angle * (M_PI/180)), 0, 1, 0);

    //gluLookAt (eye_x, 500, eye_z, xlook, 500, zlook, 0, 1, 0);  //camera rotation

    glColor3f(1, 0, 1);


    glPushMatrix();
        glTranslatef(0, 50, 0);
        glScalef (1,1,1);
        drawCastle2();
    glPopMatrix();

    glPushMatrix();
        glTranslatef(0, 490, 0);
        glScalef (2,2,2);
        drawCastle();
    glPopMatrix();

    skybox();

    glPushMatrix();

        glTranslatef(0, 530, -40);
        glScalef (1,1,1);
        drawRocket();
		glColor3f(1.00f, 1.00f, 0.00f);

    glPopMatrix();
    // no marks for code?


    //
    //glPointSize(500.0);
    //glBegin(GL_POINTS);
      //glVertex3f(0, 500,0);
    //glEnd();




    //glEnable(GL_TEXTURE_2D);
    //glBindTexture(GL_TEXTURE_2D, texId[6]);


    glutSwapBuffers();
}

//--------------------------------------------------------------
 void special(int key, int x, int y)
 {
    if(key == GLUT_KEY_LEFT)
    {
        angle+= 5;
        glTranslatef(-(cos(angle*(3.14/180))* distance_from_origin),0,-(sin(angle*(3.14/180))* distance_from_origin));
        glRotatef(angle, 0.0, 1.0, 0.0);        //rotate the whole scene
        glTranslatef((cos(angle*(3.14/180))* distance_from_origin),0,-(sin(angle*(3.14/180))* distance_from_origin));

    }
    else if(key == GLUT_KEY_RIGHT)
    {
        angle-= 5;
        glTranslatef(-(cos(angle*(3.14/180))* distance_from_origin),0,-(sin(angle*(3.14/180))* distance_from_origin));
        glRotatef(angle, 0.0, 1.0, 0.0);        //rotate the whole scene
        glTranslatef((cos(angle*(3.14/180))* distance_from_origin),0,-(sin(angle*(3.14/180))* distance_from_origin));

    }
    else if(key == GLUT_KEY_UP)
    {
        player_x += cos(-angle * (M_PI/180));glMatrixMode(GL_MODELVIEW);
        player_z += sin(-angle * (M_PI/180));
        distance_from_origin = pow(pow(player_x,2) + pow(player_z,2),0.5) ;
    }
    else if(key == GLUT_KEY_DOWN)
    {
        player_x += cos(-(angle-180) * (M_PI/180));
        player_z += sin(-(angle-180) * (M_PI/180));
        distance_from_origin = pow(pow(player_x,2) + pow(player_z,2),0.5) ;
    }


    glTranslatef((cos(angle*(3.14/180))* distance_from_origin),0,-(sin(angle*(3.14/180))* distance_from_origin));


    cout << "X " << player_x  << "Z " << player_z << "Angle " << angle << endl;
    glutPostRedisplay();

}
//-------------------------------------------------------------------

int main(int argc, char** argv)
{
   glutInit(&argc, argv);
   glutInitDisplayMode (GLUT_SINGLE | GLUT_DEPTH );
   glutInitWindowSize (900, 720);
   glutInitWindowPosition (50, 50);

   glutCreateWindow ("Sky Box");
   initialise();
   glutDisplayFunc(display);
   glutSpecialFunc(special);

   glutMainLoop();
   return 0;
}


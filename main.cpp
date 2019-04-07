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

#include <fstream>
#include <climits>
#include <math.h>



using namespace std;

#define GL_CLAMP_TO_EDGE 0x812F   //To get rid of seams between textures
float lookAngle = 0.0;      //Camera rotation
float eye_z, eye_x;
double distance_from_origin = 0;
double angle = 0;  //Rotation angle for viewing
double player_x = -15;
double player_z = 166;
float cam_hgt = 500; //Camera height
int rocketRotation = 0;

double cannonBallY	= 4;
double cannonBallZ  = 68;
int cannonFiring = 0;
int rocketFeetAngle = 0;
int rocketThrust = 0;
float rocketHeight = 530;

float *x, *y, *z;  //vertex coordinate arrays
int *t1, *t2, *t3; //triangles
int nvrt, ntri;    //total number of vertices and triangles
GLUquadricObj*  q;




GLuint texId[8];


//-- Loads mesh data in OFF format    -------------------------------------
void loadMeshFile(const char* fname)
{
    ifstream fp_in;
    int num, ne;

    fp_in.open(fname, ios::in);
    if(!fp_in.is_open())
    {
        cout << "Error opening mesh file" << endl;
        exit(1);
    }

    fp_in.ignore(INT_MAX, '\n');                //ignore first line
    fp_in >> nvrt >> ntri >> ne;                // read number of vertices, polygons, edges

    x = new float[nvrt];                        //create arrays
    y = new float[nvrt];
    z = new float[nvrt];

    t1 = new int[ntri];
    t2 = new int[ntri];
    t3 = new int[ntri];

    for(int i=0; i < nvrt; i++)                         //read vertex list
        fp_in >> x[i] >> y[i] >> z[i];

    for(int i=0; i < ntri; i++)                         //read polygon list
    {
        fp_in >> num >> t1[i] >> t2[i] >> t3[i];
        if(num != 3)
        {
            cout << "ERROR: Polygon with index " << i  << " is not a triangle." << endl;  //not a triangle!!
            exit(1);
        }
    }

    fp_in.close();
    cout << " File successfully read." << endl;
}

void loadGLTextures()               // Load bitmaps And Convert To Textures
{
    glGenTextures(8, texId);        // Create texture ids
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
    loadTGA("down4.tga");// was wall2.tga
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	
	
	glBindTexture(GL_TEXTURE_2D, texId[7]);
    loadTGA("alien3.tga");
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    
    glBindTexture(GL_TEXTURE_2D, texId[8]);  //Use this texture name for the following OpenGL texture
    loadTGA("rust.tga");
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    
    


}

//--Function to compute the normal vector of a triangle with index tindx ----------
void normal(int tindx)
{
    float x1 = x[t1[tindx]], x2 = x[t2[tindx]], x3 = x[t3[tindx]];
    float y1 = y[t1[tindx]], y2 = y[t2[tindx]], y3 = y[t3[tindx]];
    float z1 = z[t1[tindx]], z2 = z[t2[tindx]], z3 = z[t3[tindx]];
    float nx, ny, nz;
    nx = y1*(z2-z3) + y2*(z3-z1) + y3*(z1-z2);
    ny = z1*(x2-x3) + z2*(x3-x1) + z3*(x1-x2);
    nz = x1*(y2-y3) + x2*(y3-y1) + x3*(y1-y2);
    glNormal3f(nx, ny, nz);
}



//-- Draws Cannon Mesh Model
void drawCannonMesh()
{
    glColor3f(0.4, 0.5, 0.4);

    //Construct the object model here using triangles read from OFF file
    glBegin(GL_TRIANGLES);
        for(int tindx = 0; tindx < ntri; tindx++)
        {
           normal(tindx);
           glVertex3d(x[t1[tindx]], y[t1[tindx]], z[t1[tindx]]);
           glVertex3d(x[t2[tindx]], y[t2[tindx]], z[t2[tindx]]);
           glVertex3d(x[t3[tindx]], y[t3[tindx]], z[t3[tindx]]);
        }
    glEnd();
}


void drawRocket()
{	
	int N = 9;
	
	float vy[N] = {-18,-15, -10, -6, 0.0};
	float vx[N] = {0,26.25,45,56.25,60,56.25};
	float vz[N] = {0};

	float wx[N], wy[N], wz[N];
	
	glRotatef(rocketRotation+45,  0,  1,  0);

    
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
            normal2( wx[i-1], wy[i-1], wz[i-1],vx[i-1], vy[i-1], vz[i-1],vx[i], vy[i], vz[i]);
            }

            glVertex3f(vx[i], vy[i], vz[i]);
            if(i > 0)
            {
                normal2( wx[i-1], wy[i-1], wz[i-1],vx[i], vy[i], vz[i],wx[i], wy[i], wz[i]);
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
     for( int x = 0; x < 360; x+= 90)
     {
     glPushMatrix();
     	glRotatef(x,  0,  1,  0);
		 glTranslatef(30, 0, 0);
		 
		 glTranslatef(0, -rocketFeetAngle*0.03, 0);

		 glRotatef(rocketFeetAngle,  0,  0,  1);

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

	glPushMatrix();
		 
		 glTranslatef(0, -17, 0);
		 glRotatef(90,  1,  0,  0);
	     glColor3f(1.00f, 0.00f, 0.00f);
		 glutSolidTorus(5,8,10, 10);
		 
	glPopMatrix();

    
}


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
  glVertex3f(-1000, 486, 1000);
  glTexCoord2f(1.0, 0.0);
  glVertex3f(1000, 486,  1000);
  glTexCoord2f(0.0, 0.0);
  glVertex3f(1000, 486, -1000);
  glTexCoord2f(0.0, 1.0);
  glVertex3f(-1000, 486, -1000);
  glEnd();


  glDisable(GL_TEXTURE_2D);


}


void drawCannon()
{

   glPushMatrix();
		glTranslatef(-10.0,cannonBallY, cannonBallZ);
        glutSolidSphere(0.5, 10, 10);
   glPopMatrix();
	
    glPushMatrix();

        glTranslatef(-10, 0.2, 67);
        glScalef(.1, .1, .1);
        glRotatef(-30, 1, 0 ,0);
        glRotatef(270, 0, 1, 0);
        //glRotatef(180, 0, 0, 1);
        drawCannonMesh();
    glPopMatrix();

    //--start here
    glPushMatrix();
    glTranslatef(-10.0, 0, 65);
    glRotatef(90, 0, 1, 0);
    glPushMatrix();
        glColor3f(1.0,0, 0);
        glTranslatef(-1.0, .5, 1.7);
        glScalef(8.0, 1.0, .6);
        glutSolidCube(1);
    glPopMatrix();

    glPushMatrix();
        glTranslatef(-2.0, 2.5, 1.7);
        glScalef (4.0, 3.0, .6);
        glutSolidCube(1);

    glPopMatrix();

    glPushMatrix();
        glTranslatef (-1.0, .5,-1.7) ;
        glScalef(8.0, 1.0, .6);
        glutSolidCube(1);
    glPopMatrix();

    glPushMatrix();
        glTranslatef(-2.0, 2.5, -1.7);
        glScalef (4.0, 3.0, .6);
        glutSolidCube(1);
    glPopMatrix();

    glPushMatrix();
        glTranslatef(3.88, 6.4, 0);
        glutSolidSphere(.5, 3.6, 1.8);
    glPopMatrix();
    glPopMatrix();


}

void drawCastle()
{
	
    GLfloat lightpos[] = {800,800 ,800,0 };

    
    glLightfv(GL_LIGHT0, GL_POSITION, lightpos);
 
    
    int cubeSize = 2;
        
    glBindTexture(GL_TEXTURE_2D, texId[6]);

    glEnable(GL_TEXTURE_2D);
    
    glBegin(GL_QUADS);
    glDisable(GL_TEXTURE_2D);
    glColor3f(0.00f, 1.00f, 1.0f);

	glTexCoord2f(0., 3.); 
    glVertex3f(-51,35, -54);
    glTexCoord2f(3., 3.); 
    glVertex3f(51, 35, -54);
    glTexCoord2f(3., 0.); 
    glVertex3f(51, 0, -54);
    glTexCoord2f(0., 0.); 
    glVertex3f(-51,0, -54);
	
	glTexCoord2f(0., 3.); 
    glVertex3f(-51,35, -56);
    glTexCoord2f(3., 3.); 
    glVertex3f(51, 35, -56);
    glTexCoord2f(3., 0.); 
    glVertex3f(51, 0, -56);
    glTexCoord2f(0., 0.);
    glVertex3f(-51,0, -56);

    glVertex3f(-51, 35, -54);
    glVertex3f(-51, 35, -56);
    glVertex3f(51, 35,  -56);
    glVertex3f( 51, 35,  -54);

    //glColor3f(0.f, 1.0f, 0.0f);
	glTexCoord2f(0., 3.); 
    glVertex3f(-54,0, -51);
    glTexCoord2f(3.0, 3.0); 
    glVertex3f(-54, 0, 51);
    glTexCoord2f(3., .0); 
    glVertex3f(-54, 35, 51);
    glTexCoord2f(0., 0.); 
    glVertex3f(-54,35, -51);

	glTexCoord2f(0., 3.); 
    glVertex3f(-56,0, -51);
    glTexCoord2f(3.0, 3.0); 
    glVertex3f(-56, 0, 51);
    glTexCoord2f(3., .0);
    glVertex3f(-56, 35, 51);
    glTexCoord2f(0., 0.); 
    glVertex3f(-56,35, -51);

    glVertex3f(-56,35, -51);
    glVertex3f(-54, 35, -51);
    glVertex3f(-54, 35, 51);
    glVertex3f(-56,35, 51);


    //glColor3f(0.f, 0.0f, 1.0f);
	glTexCoord2f(0., 3.); 
    glVertex3f(54,0, -51);
    glTexCoord2f(3.0, 3.0);
    glVertex3f(54, 0, 51);
    glTexCoord2f(3., .0);
    glVertex3f(54, 35, 51);
    glTexCoord2f(0., 0.);  
    glVertex3f(54,35, -51);


	glTexCoord2f(0., 3.); 
    glVertex3f(56,0, -51);
    glTexCoord2f(3.0, 3.0);
    glVertex3f(56, 0, 51);
    glTexCoord2f(3., .0);
    glVertex3f(56, 35, 51);
    glTexCoord2f(0., 0.);  
    glVertex3f(56,35, -51);

    glVertex3f(56,35, -51);
    glVertex3f(54, 35, -51);
    glVertex3f(54, 35, 51);
    glVertex3f(56,35, 51);

    //glColor3f(1.0f, 0.0f, 1.0f);
	
	glTexCoord2f(0., 3.); 
    glVertex3f(-51,0, 54);
    glTexCoord2f(1.55, 3.0);
    glVertex3f(-5, 0, 54);
    glTexCoord2f(1.55, .0);
    glVertex3f(-5, 35, 54);
    glTexCoord2f(0., 0.);  
    glVertex3f(-51,35, 54);
	
	
	glTexCoord2f(0., 3.); 
    glVertex3f(5,0, 54);
    glTexCoord2f(1.55, 3.0);
    glVertex3f(51, 0, 54);
    glTexCoord2f(1.55, .0);
    glVertex3f(51, 35, 54);
    glTexCoord2f(0., 0.);  
    glVertex3f(5,35, 54);
	
	glTexCoord2f(0., 2.); 
    glVertex3f(-5,8, 54);
    glTexCoord2f(.3, 2.0);
    glVertex3f(5, 8, 54);
    glTexCoord2f(.3, .0);
    glVertex3f(5, 35, 54);
    glTexCoord2f(.0, 0.);  
    glVertex3f(-5,35, 54);

	glTexCoord2f(0., 3.); 
    glVertex3f(-51,0, 56);
    glTexCoord2f(1.55, 3.0);
    glVertex3f(-5, 0, 56);
    glTexCoord2f(1.55, .0);
    glVertex3f(-5, 35, 56);
    glTexCoord2f(0., 0.);  
    glVertex3f(-51,35, 56);

	glTexCoord2f(0., 3.); 
    glVertex3f(5,0, 56);
    glTexCoord2f(1.55, 3.0);
    glVertex3f(51, 0, 56);
    glTexCoord2f(1.55, .0);
    glVertex3f(51, 35, 56);
    glTexCoord2f(0., 0.);  
    glVertex3f(5,35, 56);

	glTexCoord2f(0., 2.67); 
    glVertex3f(-5,8, 56);
    glTexCoord2f(.3, 2.67);
    glVertex3f(5, 8, 56);
    glTexCoord2f(0.3, .22);
    glVertex3f(5, 35, 56);
    glTexCoord2f(0., 0.22);  
    glVertex3f(-5,35, 56);

    //glColor3f(0.0f, 0.0f, 0.2f);

    glVertex3f(-5,0, 56);
    glVertex3f(-5,0, 54);
    glVertex3f(-5,8, 54);
    glVertex3f(-5,8, 56);

    glVertex3f(-5,8, 56);
    glVertex3f(-5,8, 54);
    glVertex3f(5,8, 54);
    glVertex3f(5,8, 56);

    glVertex3f(5,0, 56);
    glVertex3f(5,0, 54);
    glVertex3f(5,8, 54);
    glVertex3f(5,8, 56);
	
    glDisable(GL_TEXTURE_2D);

	glEnd();

	 glDisable(GL_TEXTURE_2D);

	glDisable(GL_LIGHTING);                

	glPushMatrix();
	   
		glColor3f(0.9f, 0.00f, 0.0f);

		glBegin(GL_QUADS);
		glVertex3f(-5,12, 56.01);
		glVertex3f(5,12, 56.01);
		glVertex3f(5,35, 56.01);
		glVertex3f(-5,35, 56.01);
		glEnd();
	glPopMatrix();
	
	glPushMatrix();
	
		glBegin(GL_TRIANGLES);
		glVertex3f(-5,12, 56.01);
		glVertex3f(0,8, 56.01);
		glVertex3f(5,12, 56.01);
		glEnd();
	glPopMatrix();
	    glDisable(GL_TEXTURE_2D);

	
		
	//glPushMatrix();
		//glBegin(GL_QUADS);
		//glVertex3f(-5,12, 53.99);
		//glVertex3f(5,12,  53.99);
		//glVertex3f(5,35,  53.99);
		//glVertex3f(-5,35,  53.99);
		//glEnd();
	//glPopMatrix();
	
	//glPushMatrix();
		//glBegin(GL_TRIANGLES);
		//glVertex3f(-5,12,  53.99);
		//glVertex3f(0,8,  53.99);
		//glVertex3f(5,12,  53.99);
		//glEnd();
	//glPopMatrix();
	
		glDisable(GL_LIGHTING);                

	glEnable(GL_LIGHTING);                

	glPushMatrix();
	glBindTexture(GL_TEXTURE_2D, texId[7]);
		glEnable(GL_TEXTURE_2D);
		glBegin(GL_QUADS);
		
		glTexCoord2f(1, 1); 
		glVertex3f(-3,17.5, 56.02);
		glTexCoord2f(0., 1.0); 
		glVertex3f(3,17.5, 56.02);
		glTexCoord2f(0., 0.); 
		glVertex3f(3,30, 56.02);
		glTexCoord2f(1, 0.0); 
		glVertex3f(-3,30, 56.02);
		
		glEnd();
	glPopMatrix();
	
	
	//glPushMatrix();
	//glBindTexture(GL_TEXTURE_2D, texId[7]);
		//glEnable(GL_TEXTURE_2D);
		//glBegin(GL_QUADS);
		
		//glTexCoord2f(1, 1); 
		//glVertex3f(-3,17.5, 53.98);
		//glTexCoord2f(0., 1.0); 
		//glVertex3f(3,17.5, 53.98);
		//glTexCoord2f(0., 0.); 
		//glVertex3f(3,30, 53.98);
		//glTexCoord2f(1, 0.0); 
		//glVertex3f(-3,30, 53.98);
		
		//glEnd();
	//glPopMatrix();

	
	glDisable(GL_TEXTURE_2D);



    int blockRadius = 3;
    for(int amountOfTowers = 0 , towerX = 0, towerZ = 0; amountOfTowers < 4; amountOfTowers++)
    {
        blockRadius = 3;
        cubeSize = 2;
        if (amountOfTowers == 0)
        {
            towerX = -55;
            towerZ = -55;
        }

        else if (amountOfTowers == 1){
            towerX = 55;
            towerZ = -55;

        }
        else if (amountOfTowers == 2){
            towerX = -55;
            towerZ = 55;

        }
        else if (amountOfTowers == 3){
            towerX = 55;
            towerZ = 55;

        }


        for(int q = 1, rotation = 0; q < 40; q+=2)
        {

        rotation += 20.5;


        glPushMatrix();/*
        if (q >= 38)
        {
            cubeSize = 1.9;
            glTranslatef(towerX,q-0.5,towerZ);
            blockRadius = 3;

        }
        else {
            glTranslatef(towerX,q,towerZ);
        }*/
        glTranslatef(towerX,q,towerZ);
        glPushMatrix();
            glRotatef(rotation, 0, 1, 0);
            glTranslatef(0, 0, blockRadius);
            glutSolidCube(cubeSize);
        glPopMatrix();

        glPushMatrix();
            glRotatef(rotation, 0, 1, 0);
            glTranslatef(0, 0, -blockRadius);
            glutSolidCube(cubeSize);
        glPopMatrix();

        glPushMatrix();
            glRotatef(rotation, 0, 1, 0);
            glTranslatef(-blockRadius, 0, 0);
            glutSolidCube(cubeSize);
        glPopMatrix();

        glPushMatrix();
            glRotatef(rotation, 0, 1, 0);
            glTranslatef(blockRadius, 0, 0);
            glutSolidCube(cubeSize);
        glPopMatrix();

        glPushMatrix();
            glRotatef(rotation+45, 0, 1, 0);
            glTranslatef(blockRadius, 0, 0);
            glutSolidCube(cubeSize);
        glPopMatrix();

        glPushMatrix();
            glRotatef(rotation+45, 0, 1, 0);
            glTranslatef(-blockRadius, 0, 0);
            glutSolidCube(cubeSize);
        glPopMatrix();

        glPushMatrix();
            glRotatef(rotation+45, 0, 1, 0);
            glTranslatef(0, 0, -blockRadius);
            glutSolidCube(cubeSize);
        glPopMatrix();

        glPushMatrix();
            glRotatef(rotation+45, 0, 1, 0);
            glTranslatef(0, 0, blockRadius);
            glutSolidCube(cubeSize);
        glPopMatrix();

        glPopMatrix();
        }
    }
 
    glDisable(GL_TEXTURE_2D);

}

void drawScorpion()
{
	
	// draw body
	
	glColor3f(1.00f, 0.00f, 1.0f);
	
	//body
	glPushMatrix();
		glScalef (10,3,5);
		glRotatef(0,  0,  0,  1);
		glutSolidCube(1);
	glPopMatrix();
	
	glColor3f(1.00f, 0.00f, 0.0f);
	
	// upper leg
	glPushMatrix();
		glTranslatef(4, 0, 1);
		//glRotatef(-20,  1,  0,  0);
		glScalef (1,1,3);
		glutSolidCube(1);
	glPopMatrix();
	
	glPushMatrix();
		glTranslatef(4, 0, -1);
		//glRotatef(-20,  1,  0,  0);
		glScalef (1,1,3);
		glutSolidCube(1);
	glPopMatrix();

	glPushMatrix();
		glTranslatef(-4, 0, -1);
		//glRotatef(-20,  1,  0,  0);
		glScalef (1,1,3);
		glutSolidCube(1);
	glPopMatrix();

	glPushMatrix();
		glTranslatef(-4, 0, 1);
		//glRotatef(-20,  1,  0,  0);
		glScalef (1,1,3);
		glutSolidCube(1);
	glPopMatrix();
		
	// lower leg
	glPushMatrix();
		glTranslatef(4, -0.8, 5.3);
		glRotatef(50,  1,  0,  0);
		glScalef (1,1,3);

		glutSolidCube(1);
	glPopMatrix();

}


void drawRobot1()
{
	
	
	glEnable(GL_LIGHTING);

    glPushMatrix();
		glTranslatef(0.6, 5.5, 1.4);
		glutSolidSphere(0.3, 50, 50 );
	glPopMatrix();
	
	glPushMatrix();
		glTranslatef(-0.6, 5.5, 1.4);
		glutSolidSphere(0.3, 50, 50 );
	glPopMatrix();
	
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, texId[8]);
    glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);
	glPushMatrix();
		gluSphere ( q, 4.0, 50, 50 );
		glTranslatef(0, 5.4, 0);
		glutSolidCube(3);

	glPopMatrix();
    glDisable(GL_TEXTURE_2D);

	
}

void cannonAnimation(int time)
{
    glutPostRedisplay();
    cannonFiring = 1;
    cannonBallZ += cos(30*(3.1415/180)) * 1.5 -  (  cos(30*(3.1415/180)) * 1.5 * 0.1) ;
    cannonBallY += (sin(30*(3.1415/180)) * 1.5) - (9.81 * 0.5 * pow(time*0.001,2));
    time += 10;
    if (cannonBallY > -1)
    {
    glutTimerFunc(10,cannonAnimation,time);
	}
	else
	{
	    cannonFiring = 0;
	}
}

void RocketFeetAnimation(int time)
{
	glutPostRedisplay();

	//cout << "Thrust :  " << rocketThrust << endl;
	if (rocketThrust < 100)
	{
		rocketThrust ++;
		glutTimerFunc(30,RocketFeetAnimation,0);

	}
    else
    {
	if (rocketThrust < 400)
    {rocketThrust ++;
		rocketHeight += 0.2;}
	if (rocketThrust >= 400 && rocketHeight < 980)
    {rocketThrust ++;
		rocketHeight += 1;}
	
    
	if (rocketFeetAngle < 70)
	{
			rocketFeetAngle += 3;
			glutTimerFunc(30,RocketFeetAnimation,0);
	}
	else
	{
		rocketRotation += 1;
		glutTimerFunc(15,RocketFeetAnimation,0);
	
	}
	}

}

//---------------------------------------------------------------------
void initialise(void)
{
    loadGLTextures();
	loadMeshFile("Cannon.off");             //Specify mesh file name here
	
    float white[4]  = {1.0, 1.0, 1.0, 1.0};
	
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_TEXTURE_2D);
    glEnable(GL_NORMALIZE);
    glClearColor (0.0, 0.0, 0.0, 0.0);
    
    glEnable(GL_LIGHTING);                  //Enable OpenGL states
    glEnable(GL_LIGHT0);
    glColorMaterial(GL_FRONT, GL_AMBIENT_AND_DIFFUSE);
    glEnable(GL_COLOR_MATERIAL);
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_NORMALIZE);
    

    glColorMaterial(GL_FRONT, GL_AMBIENT_AND_DIFFUSE);
    
    
    glMaterialfv(GL_FRONT, GL_SPECULAR, white);
    glMaterialf(GL_FRONT, GL_SHININESS, 50);
    
    q =  gluNewQuadric ( );
    gluQuadricDrawStyle (q, GLU_FILL );
    gluQuadricNormals   (q, GLU_SMOOTH );
    

    gluQuadricTexture (q, GL_TRUE);


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
        glTranslatef(0, 490, 0);
        glScalef (2,2.5,2);
        drawCastle();
    glPopMatrix();

    skybox();

    glPushMatrix();

        glTranslatef(0, rocketHeight, -40);
        glScalef (1,1,1);
        drawRocket();
		glColor3f(1.00f, 1.00f, 0.00f);

    glPopMatrix();
    // no marks for code?
    
    glPushMatrix();
        glTranslatef(00, 490, 200);
		//drawScorpion();
    glPopMatrix();
    
    glPushMatrix();
        glTranslatef(-5, 490, 40);
        glScalef (1.5,1.5,1.5);
		drawCannon();
    glPopMatrix();
    
    glPushMatrix();
        glTranslatef(0, 494.5, 150);
		drawRobot1();
	glPopMatrix();

	
    
	if (rocketThrust > 0)
	{
	glDisable(GL_LIGHTING);                  
    glPointSize(6.6);
    
    for(int x = 0; x < rocketThrust; x++)
    {	
		
		
		//int xpoint = rand() % 5;
		
		//int ypoint = 0.5 * (xpoint * xpoint);
		
		double ypoint = (rand() % 250) * 0.1; //* (rand() % 100000)/100000;
		
		
		double length = sqrt(ypoint) * (rand() % 1000 + 1) * 0.001;
		
		
		//cout << "y " << ypoint << endl;

		
		int theta = rand() % 360;
		
	
		double xpoint = (length * sin(theta * (M_PI/180)));
		double zpoint = (length * cos(theta * (M_PI/180)));
		
		
		
		int colourPicker = rand() % 5;

		
		glBegin(GL_POINTS);

		if (colourPicker == 0){glColor3f(0.95f, 1.00f, 0.06f);}
		else if (colourPicker ==1){glColor3f(0.95f, 0.69f, 0.25f);}
		else if (colourPicker ==2){glColor3f(0.89, 0.72, 0.13);}
		else if (colourPicker ==3){glColor3f(0.89f, 0.47f, 0.13);}
		else if (colourPicker ==4){glColor3f(0.89f, 0.13f, 0.17f);}
		

		
		
	    glVertex3d(xpoint, (rocketHeight - 35) + ypoint,zpoint-40);
	    
	    

		glEnd();
	}	
	glEnable(GL_LIGHTING);                

	}
    //glEnable(GL_TEXTURE_2D);
    //glBindTexture(GL_TEXTURE_2D, texId[6]);
    glutSwapBuffers();
}

void keyBoard (unsigned char key, int x, int y)
{
	if (key == 'c' && cannonFiring == 0)
	{
		cannonBallY	= 4;
		cannonBallZ  = 68;
		glutTimerFunc(1,cannonAnimation,0);
	}
	if (key == 's' && rocketThrust == 0)
	{
		glutTimerFunc(1,RocketFeetAnimation,0);	   
	}
}  


//--------------------------------------------------------------
 void special(int key, int x, int y)
 {
    if(key == GLUT_KEY_LEFT)
    {
        angle+= 5;
        glTranslatef(-(cos(angle*(3.14/180))* distance_from_origin),0,-(sin(angle*(M_PI/180))* distance_from_origin));
        glRotatef(angle, 0.0, 1.0, 0.0);        //rotate the whole scene
        glTranslatef((cos(angle*(3.14/180))* distance_from_origin),0,-(sin(angle*(M_PI/180))* distance_from_origin));

    }
    else if(key == GLUT_KEY_RIGHT)
    {
        angle-= 5;
        glTranslatef(-(cos(angle*(3.14/180))* distance_from_origin),0,-(sin(angle*(M_PI/180))* distance_from_origin));
        glRotatef(angle, 0.0, 1.0, 0.0);        //rotate the whole scene
        glTranslatef((cos(angle*(3.14/180))* distance_from_origin),0,-(sin(angle*(M_PI/180))* distance_from_origin));

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
   glutKeyboardFunc(keyBoard);
   glutMainLoop();
   return 0;
}


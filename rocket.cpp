
#include <iostream>
#include <GL/freeglut.h>
#include <cmath>
void normal(float x1, float y1, float z1,
            float x2, float y2, float z2,
            float x3, float y3, float z3 )
{
    float nx, ny, nz;
    nx = y1*(z2-z3)+ y2*(z3-z1)+ y3*(z1-z2);
    ny = z1*(x2-x3)+ z2*(x3-x1)+ z3*(x1-x2);
    nz = x1*(y2-y3)+ x2*(y3-y1)+ x3*(y1-y2);
    glNormal3f(nx, ny, nz);
}

void drawRocket()
{	
	int N = 15;
	
	
	float vx[N] = {0,1, 2, 3, 4, 5, 6, 7, 8, 9,8,7,5,4,3};
	float vy[N] = {0,-0.5,-2,-3.5,-8,-12.5,-18,-24.5,-32,-40.5,-49,-56.5,-63,-68.5,-73};
	float vz[N] = {0};
	
	// y = -0.5q^2
	// x = -q
	
	


	float wx[N], wy[N], wz[N];
	
	
	//for(int q = 1; q < N - 1; q++)
	//{
	
		//vx[q] = -q;
		//vy[q] = -0.5*(q*q) ;
	//}
	
	//vx[9] = vx[8];
	//vy[9] = 100;
	
	

    
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
    glFlush();
}

void drawRocket()
{	
	
	
	
	float vx[N], vy[N], vz[N];
	float wx[N], wy[N], wz[N];
	
	
	for(int q = 0; q < N; q++)
	{
	
		vx[q] = q;
		vy[q] = -q * q + 25;
	}
	

    
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

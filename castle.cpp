

// ---------- draw the castle -------------------
void drawCastle()
{
	
    GLfloat lightpos[] = {.5, 1., 1., 0.};
    glLightfv(GL_LIGHT0, GL_POSITION, lightpos);
    int cubeSize = 2;
    

	glEnable(GL_TEXTURE_2D);

    glBegin(GL_QUADS);
    glDisable(GL_TEXTURE_2D);
    glColor3f(0.00f, 0.00f, 1.0f);
	
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
	
	glTexCoord2f(0., 3.); 
    glVertex3f(-5,8, 54);
    glTexCoord2f(.3, 3.0);
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

	glEnd();

	glDisable(GL_TEXTURE_2D);
	
	glColor3f(0.90f, 0.00f, 0.0f);

	
	glPushMatrix();
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
  
   
   

}


void squareTower()
{
	
}


void drawCastle2()
{
	
    GLfloat lightpos[] = {.5, 1., 1., 0.};
    glLightfv(GL_LIGHT0, GL_POSITION, lightpos);
   

	glEnable(GL_TEXTURE_2D);


    glDisable(GL_TEXTURE_2D);
    glColor3f(0.00f, 0.00f, 1.0f);
    	for(int i = 0; i < 50; i ++)
	{	
		glPushMatrix();

		glTranslatef(0, i, 0);
        glScalef(2, 1, 1);
        glutSolidCube(1);
        glPopMatrix();
     }	
	

}




// ---------- draw the castle -------------------

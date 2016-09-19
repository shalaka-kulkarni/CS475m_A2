#include <GL/glut.h>
#include <iostream>
#include <math.h>

#define PI 3.14159265

using namespace std;

float x_angle=0.0;
float y_angle=0.0;
float z_angle=0.0;
float offset=5.0;

float top_circle[32][3];
float bottom_circle[32][3];

void populateVertices()
{
	for(int i=0; i<32; i++)
	 {
	 	top_circle[i][0] = cos(2*PI*i/32);
	 	top_circle[i][1] = sin(2*PI*i/32);
	 	top_circle[i][2] = 1.0;
	 }
	 
	for(int i=0; i<32; i++)
	 {
	 	bottom_circle[i][0] = cos(2*PI*i/32);
	 	bottom_circle[i][1] = sin(2*PI*i/32);
	 	bottom_circle[i][2] = -1.0;
	 }
}

//Our function for processing ASCII keys
void processNormalKeys(unsigned char key, int x, int y) {
  if (key == 27)
  exit(0);
}

//Our function for processing Non-ASCII keys
void processSpecialKeys(int key, int x, int y) {
  switch(key) {
    case GLUT_KEY_LEFT :
    y_angle-=offset;
    break;
    case GLUT_KEY_RIGHT :
    y_angle+=offset;
    break;
    case GLUT_KEY_UP :
    x_angle-=offset;
    break;
    case GLUT_KEY_DOWN :
    x_angle+=offset;
    break;
    case GLUT_KEY_PAGE_UP :
    z_angle-=offset;
    break;
    case GLUT_KEY_PAGE_DOWN :
    z_angle+=offset;
    break;
  }

  //Reset angles in range 0 to 360
  if(x_angle<0) {
    x_angle=x_angle+360;
  } else if(x_angle>360) {
    x_angle=x_angle-360;
  }

  if(y_angle<0){
    y_angle=y_angle+360;
  } else if(y_angle>360) {
    y_angle=y_angle-360;
  }

  if(z_angle<0){
    z_angle=z_angle+360;
  } else if(z_angle>360){
    z_angle=z_angle-360;
  }

  //Redraw
  glutPostRedisplay();
}


void drawCylinder(void)
{
  glPushMatrix();
  glRotatef(x_angle, 1.0, 0.0, 0.0);
  glRotatef(y_angle, 0.0, 1.0, 0.0);
  glRotatef(z_angle, 0.0, 0.0, 1.0);
  
  float color[3] = {1.0,0.0,0.0};
  
  //drawing top circle
  float center[3] = {0.0,0.0,1.0};
  
  for (int i=0;i<31;i++){
    
    glBegin(GL_TRIANGLES);
    glColor3fv(color);
    glVertex3fv(top_circle[i]);
    glVertex3fv(top_circle[i+1]);
    glVertex3fv(center);
       
    glEnd();
  }
  
  glBegin(GL_TRIANGLES);
    glColor3fv(color);
    glVertex3fv(top_circle[31]);
    glVertex3fv(top_circle[0]);
    glVertex3fv(center);
  glEnd();
  
  //drawing bottom circle
  center[2] = -1.0;
  
  for (int i=0;i<31;i++){
    
    glBegin(GL_TRIANGLES);
    glColor3fv(color);
    glVertex3fv(bottom_circle[i]);
    glVertex3fv(bottom_circle[i+1]);
    glVertex3fv(center);
       
    glEnd();
  }
  
  glBegin(GL_TRIANGLES);
    glColor3fv(color);
    glVertex3fv(bottom_circle[31]);
    glVertex3fv(bottom_circle[0]);
    glVertex3fv(center);
  glEnd();
  
  //drawing lateral surface
  for (int i=0;i<31;i++){
    
    glBegin(GL_TRIANGLES);
    glColor3fv(color);
    
    glVertex3fv(top_circle[i]);
    glVertex3fv(top_circle[i+1]);
    glVertex3fv(bottom_circle[i]);
    
    glVertex3fv(bottom_circle[i]);
    glVertex3fv(bottom_circle[i+1]);
    glVertex3fv(top_circle[i+1]);
       
    glEnd();
  }
  
  glBegin(GL_TRIANGLES);
    glColor3fv(color);
    
    glVertex3fv(top_circle[31]);
    glVertex3fv(top_circle[0]);
    glVertex3fv(bottom_circle[31]);
    
    glVertex3fv(bottom_circle[31]);
    glVertex3fv(bottom_circle[0]);
    glVertex3fv(top_circle[0]);
  glEnd();
  
  glPopMatrix();
}


void display(void)
{
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  drawCylinder();
  //Swaps front buffer with back buffer
  glutSwapBuffers();
}

void init(void)
{
  // Use depth buffering for hidden surface elimination.
  glEnable(GL_DEPTH_TEST);

  // Setup the view of the cube.
  glMatrixMode(GL_PROJECTION);

  //gluPerspective(field of view in degree, aspect ratio, Z near, Z far);
  gluPerspective(40.0, 1.0, 1.0, 10.0);

  glMatrixMode(GL_MODELVIEW);
  gluLookAt(0.0, 0.0, 8.0,  // eye is at (0,0,8)
  0.0, 0.0, 0.0,      // center is at (0,0,0)
  0.0, 1.0, 0.0);      // up is in positive Y direction
}

int main(int argc, char **argv)
{
  populateVertices();
  glutInit(&argc, argv);
  glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
  glutCreateWindow("Color Cube Rotate");
  glutDisplayFunc(display);

  glutKeyboardFunc(processNormalKeys);
  glutSpecialFunc(processSpecialKeys);

  init();
  glutMainLoop();
  return 0;
}

/*
//For individual object rotation you will need glPushMatrix() & glPopMatrix();
glPushMatrix();
glTranslate(-originalX, -originalY, -originalZ);  //translate to origin
glRotate(angle, 0, 1, 0);
glTranslate(originalX, originalY, originalZ);     //translate back
...
glPopMatrix();
*/

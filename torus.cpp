/*
#include <GL/glut.h>

GLfloat xRotated, yRotated, zRotated;
// Torus
GLdouble innerRaidus=0.5;
GLdouble outterRaidus=1;
GLint sides =50;
GLint rings =50;


void displayTorus(void)
{

    glMatrixMode(GL_MODELVIEW);
    // clear the drawing buffer.
    glClear(GL_COLOR_BUFFER_BIT);
    // clear the identity matrix.
    glLoadIdentity();
    // traslate the draw by z = -4.0
    // Note this when you decrease z like -8.0 the drawing will looks far , or smaller.
    glTranslatef(0.0,0.0,-4.5);
    // Red color used to draw.
    glColor3f(0.8, 0.2, 0.1); 
    // changing in transformation matrix.
    // rotation about X axis
    glRotatef(xRotated,1.0,0.0,0.0);
    // rotation about Y axis
    glRotatef(yRotated,0.0,1.0,0.0);
    // rotation about Z axis
    glRotatef(zRotated,0.0,0.0,1.0);
    // scaling transfomation 
    glScalef(1.0,1.0,1.0);
    // built-in (glut library) function , draw you a Torus.
 

    glutSolidTorus(innerRaidus,outterRaidus,sides,rings);
    // Flush buffers to screen
     
    glFlush();        
    // sawp buffers called because we are using double buffering 
   // glutSwapBuffers();
}

void reshapeTorus(int x, int y)
{
    if (y == 0 || x == 0) return;  //Nothing is visible then, so return
    //Set a new projection matrix
    glMatrixMode(GL_PROJECTION);  
    glLoadIdentity();
    //Angle of view:40 degrees
    //Near clipping plane distance: 0.5
    //Far clipping plane distance: 20.0
     
    gluPerspective(40.0,(GLdouble)x/(GLdouble)y,0.5,20.0);
 
    glViewport(0,0,x,y);  //Use the whole window for rendering
}

void idleTorus(void)
{
 
     yRotated += 0.01;
     
    displayTorus();
}


int main (int argc, char **argv)
{
    //Initialize GLUT
    glutInit(&argc, argv);
    //double buffering used to avoid flickering problem in animation
     glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);  
    // window size
    glutInitWindowSize(400,350);
    // create the window 
    glutCreateWindow("Torus Rotating Animation");
    glPolygonMode(GL_FRONT_AND_BACK,GL_LINE);
    xRotated = yRotated = zRotated = 30.0;
     xRotated=33;
     yRotated=40;
    glClearColor(0.0,0.0,0.0,0.0);
    //Assign  the function used in events
    glutDisplayFunc(displayTorus);
   glutReshapeFunc(reshapeTorus);
    glutIdleFunc(idleTorus);
    //Let start glut loop
    glutMainLoop();
    return 0;
} */



#include <GL/glut.h>
#include <iostream>
#include <vector>
#include <math.h>
#include "HNode.cpp"
#include "cylinder.cpp"

using namespace std;

float r_out = 5, r_in = 4;
float r_tube = (r_out - r_in)/2; 
int theta = 5; 		//angle subtended by every elemental cylinder
int num_cyl = (int)(360/theta); 	
float xa = 0, ya = 0, za = 0; 

HNode* torusNode[73];   //360/theta + 1

int curr=0; //Index of current operational torusNode

float v_cyl_pos[32*4][3][3];		//32 triangles per circular face of cylinder; 3 vertices per triangle; 3 coordinates per vertex
float v_cyl_col[32*4][3][3];

void createCylinderList()
{
	r = r_tube; h = (2*PI*r_out/num_cyl)/2 ;
	populateVertices();

for(int i=0; i<128; i++)
{
	for(int j=0; j<3; j++)
	{
		v_cyl_col[i][j][0] = 0.0;
		v_cyl_col[i][j][1] = 1.0;
		v_cyl_col[i][j][2] = 1.0;
	}
}


float center[3] = {0.0,0.0,1.0};

//drawing top circle
center[2] = h;
for (int i=0;i<31;i++)
{    
    vertexcopy(v_cyl_pos[i][0], top_circle[i]);
    vertexcopy(v_cyl_pos[i][1], top_circle[i+1]);
    vertexcopy(v_cyl_pos[i][2], center);
}
	vertexcopy(v_cyl_pos[31][0], top_circle[31]);
    vertexcopy(v_cyl_pos[31][1], top_circle[0]);
    vertexcopy(v_cyl_pos[31][2], center);
  
//drawing bottom circle
  center[2] = -h;
  
  for (int i=32;i<63;i++)
  { 
    vertexcopy(v_cyl_pos[i][0], bottom_circle[i]);
    vertexcopy(v_cyl_pos[i][1], bottom_circle[i+1]);
    vertexcopy(v_cyl_pos[i][2], center);
  }
 	vertexcopy(v_cyl_pos[63][0], bottom_circle[31]);
    vertexcopy(v_cyl_pos[63][1], bottom_circle[0]);
    vertexcopy(v_cyl_pos[63][2], center);
  
  
  //drawing lateral surface
  for (int i=64;i<126;i+=2)
  {       
    vertexcopy(v_cyl_pos[i][0], top_circle[i]);
    vertexcopy(v_cyl_pos[i][1], top_circle[i+1]);
    vertexcopy(v_cyl_pos[i][2], bottom_circle[i]);
    i++;
    vertexcopy(v_cyl_pos[i][0], bottom_circle[i]);
    vertexcopy(v_cyl_pos[i][1], bottom_circle[i+1]);
    vertexcopy(v_cyl_pos[i][2], top_circle[i+1]);
  }
  	vertexcopy(v_cyl_pos[126][0], top_circle[31]);
    vertexcopy(v_cyl_pos[126][1], top_circle[0]);
    vertexcopy(v_cyl_pos[126][2], bottom_circle[31]);
    
    vertexcopy(v_cyl_pos[127][0], bottom_circle[31]);
    vertexcopy(v_cyl_pos[127][1], bottom_circle[0]);
    vertexcopy(v_cyl_pos[127][2], top_circle[0]);
}


void processNormalKeys(unsigned char key, int x, int y) {
  switch(key) {
    case '1':
      curr=0;
      break;
    case '2':
      curr=1;
      break;
    case '3':
      curr=2;
      break;
  }
  if (key == 27)
  exit(0);
}

//Our function for processing Non-ASCII keys
void processSpecialKeys(int key, int x, int y) {
  switch(key) {
    case GLUT_KEY_LEFT :
    torusNode[curr]->dec_ry();
    //xa -= 5;
    break; 
    case GLUT_KEY_RIGHT :
    torusNode[curr]->inc_ry();
    //xa += 5;
    break;
    case GLUT_KEY_UP :
    torusNode[curr]->dec_rx();
    //ya -= 5;
    break;
    case GLUT_KEY_DOWN :
    torusNode[curr]->inc_rx();
    //ya += 5;
    break;
    case GLUT_KEY_PAGE_UP :
    torusNode[curr]->dec_rz();
    //za -= 5;
    break;
    case GLUT_KEY_PAGE_DOWN :
    torusNode[curr]->inc_rz();
    //za += 5;
    break;
  }
  //Redraw
  glutPostRedisplay();
}

void display(void)
{
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  torusNode[0]->render_tree();
  glutSwapBuffers();
  /*glMatrixMode(GL_MODELVIEW);
    // clear the drawing buffer.
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    // clear the identity matrix.
    glLoadIdentity();
    // traslate the draw by z = -4.0
    // Note this when you decrease z like -8.0 the drawing will looks far , or smaller.
    glTranslatef(0.0,0.0,-4.5);
    // Red color used to draw.
    glColor3f(0.8, 0.2, 0.1); 
    // changing in transformation matrix.
    // rotation about X axis
    glRotatef(xa,1.0,0.0,0.0);
    // rotation about Y axis
    glRotatef(ya,0.0,1.0,0.0);
    // rotation about Z axis
    glRotatef(za,0.0,0.0,1.0);
    // scaling transfomation 
    glScalef(0.2,0.2,0.2);
    // built-in (glut library) function , draw you a Torus.
 

    glutSolidTorus(r_out-r_in,r_out, 50, 50);

    // Flush buffers to screen
     
    //glFlush();        
    // sawp buffers called because we are using double buffering 
   glutSwapBuffers();*/
}

void init(void)
{
  // Use depth buffering for hidden surface elimination.
  glEnable(GL_DEPTH_TEST);
  // Setup the view of the cube.
  glMatrixMode(GL_PROJECTION);
  //gluPerspective(field of view in degree, aspect ratio, Z near, Z far);
  gluPerspective(80.0, 1.0, 1.0, 20.0);

  glMatrixMode(GL_MODELVIEW);
  gluLookAt(0.0, 0.0, 9.0,  // eye is at (0,0,9)
  0.0, 0.0, 0.0,      // center is at (0,0,0)
  0.0, 1.0, 0.0);      // up is in positive Y direction
}

int main(int argc, char **argv)
{
	createCylinderList();
  //Parent is a single point at the centre of the torus
    float par_pos[1][3] = {{0.0, 0.0, 0.0}};
    float par_col[1][3] = {{0.0, 0.0, 0.0}};
	torusNode[0] = new HNode(NULL, 1, par_pos, par_col);

  //Children are the elemental cylinders
	float globalVertexList[128*3][3];
	float globalColorList[128*3][3];
	for(int i=0, index=0; i<128*3; i+=3, index++)
	{
		vertexcopy(globalVertexList[i], v_cyl_pos[index][0]);
		vertexcopy(globalVertexList[i+1], v_cyl_pos[index][1]);
		vertexcopy(globalVertexList[i+2], v_cyl_pos[index][2]);

		vertexcopy(globalColorList[i], v_cyl_col[index][0]);
		vertexcopy(globalColorList[i+1], v_cyl_col[index][1]);
		vertexcopy(globalColorList[i+2], v_cyl_col[index][2]);
	}
	float r_mean = (r_out+r_in)/2;
	for(int i=1; i<=num_cyl; i++)
	{
		torusNode[i] = new HNode(torusNode[0], 128*3, globalVertexList, globalColorList);
		int phi = (i-1)*theta;
		torusNode[i]->change_parameters(r_mean*cos(phi), 0.0, r_mean*sin(phi), 0.0, phi, 0.0);
	}

  glutInit(&argc, argv);
  glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
  glutInitWindowSize(500,500);
  glutCreateWindow("Torus");
  glutDisplayFunc(display);
  glutKeyboardFunc(processNormalKeys);
  glutSpecialFunc(processSpecialKeys);
  init();
  glutMainLoop();
  return 0;
}






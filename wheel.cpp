#include <GL/glut.h>
#include <iostream>
#include <vector>
#include "HNode.cpp"
#include "cylinder.cpp"

using namespace std;

HNode* wheelNode[7];	//12 spokes and a rim

float v_cyl_pos[32*4*3][3];		//32 triangles per circular face of cylinder; 3 vertices per triangle; 3 coordinates per vertex
float v_cyl_col[32*4*3][3];

void createCylinderList()
{
	r = 0.1; h = 2 ;
	populateVertices();

for(int i=0; i<384; i++)
{
	v_cyl_col[i][0] = 0.0;
	v_cyl_col[i][1] = 1.0;
	v_cyl_col[i][2] = 1.0;
	
}


float center[3] = {0.0,0.0,1.0};

//drawing top circle
center[2] = h;
int i=0;
for (int ind=0;ind<31;i+=3,ind++)
{    
    vertexcopy(v_cyl_pos[i], top_circle[ind]);
    vertexcopy(v_cyl_pos[i+1], top_circle[ind+1]);
    vertexcopy(v_cyl_pos[i+2], center);
}
	vertexcopy(v_cyl_pos[i], top_circle[31]);
    vertexcopy(v_cyl_pos[i+1], top_circle[0]);
    vertexcopy(v_cyl_pos[i+2], center);
  
//drawing bottom circle
  center[2] = -h;
  
  for (int ind=0;ind<31;i+=3,ind++)
  { 
    vertexcopy(v_cyl_pos[i], bottom_circle[ind]);
    vertexcopy(v_cyl_pos[i+1], bottom_circle[ind+1]);
    vertexcopy(v_cyl_pos[i+2], center);
  }
 	vertexcopy(v_cyl_pos[i], bottom_circle[31]);
    vertexcopy(v_cyl_pos[i+1], bottom_circle[0]);
    vertexcopy(v_cyl_pos[i+2], center);
  
  
  //drawing lateral surface
  for (int ind=0;ind<31;i+=6,ind++)
  {       
    vertexcopy(v_cyl_pos[i], top_circle[i]);
    vertexcopy(v_cyl_pos[i+1], top_circle[i+1]);
    vertexcopy(v_cyl_pos[i+2], bottom_circle[i]);
    i++;
    vertexcopy(v_cyl_pos[i], bottom_circle[i]);
    vertexcopy(v_cyl_pos[i+1], bottom_circle[i+1]);
    vertexcopy(v_cyl_pos[i+2], top_circle[i+1]);
  }
  	vertexcopy(v_cyl_pos[i], top_circle[31]);
    vertexcopy(v_cyl_pos[i+1], top_circle[0]);
    vertexcopy(v_cyl_pos[i+2], bottom_circle[31]);
    i++;
    vertexcopy(v_cyl_pos[i], bottom_circle[31]);
    vertexcopy(v_cyl_pos[i+1], bottom_circle[0]);
    vertexcopy(v_cyl_pos[i+2], top_circle[0]);
}

void createNodes()
{
  //Parent Node
  float v_tor_pos[1][3] = {2.4, 2, -999};
  float v_tor_col[1][3] = {1.0, 0.0, 1.0};
  wheelNode[0] = new HNode(NULL,1,v_tor_pos,v_tor_col);
  //Child Nodes
  for(int i=1;i<7;i++)
  {
  	wheelNode[i] = new HNode(wheelNode[0],384,v_cyl_pos,v_cyl_col);
  	wheelNode[i]->change_parameters(0,0,0, 0,(i-1)*30,0);
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
    wheelNode[0]->dec_ry();
    break;
    case GLUT_KEY_RIGHT :
    wheelNode[0]->inc_ry();
    break;
    case GLUT_KEY_UP :
    wheelNode[0]->dec_rx();
    break;
    case GLUT_KEY_DOWN :
    wheelNode[0]->inc_rx();
    break;
    case GLUT_KEY_PAGE_UP :
    wheelNode[0]->dec_rz();
    break;
    case GLUT_KEY_PAGE_DOWN :
    wheelNode[0]->inc_rz();
    break;
  }
  //Redraw
  glutPostRedisplay();
}

void display(void)
{
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  wheelNode[0]->render_tree();
  glutSwapBuffers();
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
  gluLookAt(0.0, 0.0, 9.0,  // eye is at (0,0,8)
  0.0, 0.0, 0.0,      // center is at (0,0,0)
  0.0, 1.0, 0.0);      // up is in positive Y direction
}

int main(int argc, char **argv)
{
  createNodes();

  glutInit(&argc, argv);
  glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
  glutInitWindowSize(400,400);
  glutCreateWindow("My Wheel");
  glutDisplayFunc(display);
  glutKeyboardFunc(processNormalKeys);
  glutSpecialFunc(processSpecialKeys);
  init();
  glutMainLoop();
  return 0;
}

#include <GL/glut.h>
#include <iostream>
#include <math.h>
#include "HNode.cpp"

#define PI 3.14159265

using namespace std;

HNode *node[6];

float x_angle=0.0;
float y_angle=0.0;
float z_angle=0.0;
float offset=5.0;

float seat_vertices[24][3] = {
  {-2.0,0.0,0.0},{1.0,1.5,0.0},{1.0,-1.5,0.0},
  {-2.0,0.0,-0.4},{1.0,1.5,-0.4},{1.0,-1.5,-0.4},
  {-2.0,0.0,0.0},{1.0,1.5,0.0},{-2.0,0.0,-0.4},
  {-2.0,0.0,-0.4},{1.0,1.5,-0.4},{1.0,1.5,0.0},
  {1.0,1.5,0.0},{1.0,-1.5,0.0},{1.0,1.5,-0.4},
  {1.0,1.5,-0.4},{1.0,-1.5,-0.4},{1.0,-1.5,0.0},
  {-2.0,0.0,0.0},{1.0,-1.5,0.0},{-2.0,0.0,-0.4},
  {-2.0,0.0,-0.4},{1.0,-1.5,-0.4},{1.0,-1.5,0.0}
};

float seat_color[24][3] = {
  {0.5,0.5,0.5}, {0.5,0.5,0.5}, {0.5,0.5,0.5},
  {0.5,0.5,0.5}, {0.5,0.5,0.5}, {0.5,0.5,0.5},
  {0.5,0.5,0.5}, {0.5,0.5,0.5}, {0.5,0.5,0.5},
  {0.5,0.5,0.5}, {0.5,0.5,0.5}, {0.5,0.5,0.5},
  {0.5,0.5,0.5}, {0.5,0.5,0.5}, {0.5,0.5,0.5},
  {0.5,0.5,0.5}, {0.5,0.5,0.5}, {0.5,0.5,0.5},
  {0.5,0.5,0.5}, {0.5,0.5,0.5}, {0.5,0.5,0.5},
  {0.5,0.5,0.5}, {0.5,0.5,0.5}, {0.5,0.5,0.5}
};

float l=0.75, b=0.5, h=0.2; // cuboid is 2l along x, 2b along y, 2h along z 

float cuboid_positions[36][3] = {
  {-l,b,h},  {-l,-b,h},  {l,-b,h},
  {-l,b,h},  {l,-b,h},  {l,b,h},
  {l,b,h},  {l,-b,h},  {l,-b,-h},
  {l,b,h},  {l,-b,-h},  {l,b,-h},
  {l,-b,h},  {-l,-b,h},  {-l,-b,-h},
  {l,-b,h},  {-l,-b,-h},  {l,-b,-h},
  {l,b,-h},  {-l,b,-h},  {-l,b,h},
  {l,b,-h},  {-l,b,h},  {l,b,h},
  {-l,-b,-h},  {-l,b,-h},  {l,b,-h},
  {-l,-b,-h},  {l,b,-h},  {l,-b,-h},
  {-l,b,-h},  {-l,-b,-h},  {-l,-b,h},
  {-l,b,-h},  {-l,-b,h},  {-l,b,h}
};

float cuboid_colors[36][3] = {
  {0.3,0.3,0.3}, {0.3,0.3,0.3}, {0.3,0.3,0.3},
   {0.3,0.3,0.3}, {0.3,0.3,0.3}, {0.3,0.3,0.3},
   {0.3,0.3,0.3}, {0.3,0.3,0.3}, {0.3,0.3,0.3},
   {0.3,0.3,0.3}, {0.3,0.3,0.3}, {0.3,0.3,0.3},
   {0.3,0.3,0.3}, {0.3,0.3,0.3}, {0.3,0.3,0.3},
   {0.3,0.3,0.3}, {0.3,0.3,0.3}, {0.3,0.3,0.3},
   {0.3,0.3,0.3}, {0.3,0.3,0.3}, {0.3,0.3,0.3},
   {0.3,0.3,0.3}, {0.3,0.3,0.3}, {0.3,0.3,0.3},
   {0.3,0.3,0.3}, {0.3,0.3,0.3}, {0.3,0.3,0.3},
   {0.3,0.3,0.3}, {0.3,0.3,0.3}, {0.3,0.3,0.3},
   {0.3,0.3,0.3}, {0.3,0.3,0.3}, {0.3,0.3,0.3},
   {0.3,0.3,0.3}, {0.3,0.3,0.3}, {0.3,0.3,0.3}
};

float cylinder_vertices[384][3];
float cylinder_colors[384][3];

float top_circle[32][3];
float bottom_circle[32][3];

void populateCylinderVertices(float radius, float height, float _r, float _g, float _b)
{
  for(int i=0; i<384; i++)
  {
    cylinder_colors[i][0] = _r;
    cylinder_colors[i][1] = _g;
    cylinder_colors[i][2] = _b;
  }

  for(int i=0; i<32; i++)
   {
    top_circle[i][0] = radius*cos(2*PI*i/32);
    top_circle[i][1] = radius*sin(2*PI*i/32);
    top_circle[i][2] = height/2;
   }
   
  for(int i=0; i<32; i++)
   {
    bottom_circle[i][0] = radius*cos(2*PI*i/32);
    bottom_circle[i][1] = radius*sin(2*PI*i/32);
    bottom_circle[i][2] = -1*height/2;
   }

  int index =0;
  for(int i=0; i<31; i++)
  {
    vertexcopy(bottom_circle[i], cylinder_vertices[index]);
    vertexcopy(bottom_circle[i+1],cylinder_vertices[index+1]);
    cylinder_vertices[index+2][0] = 0.0;
    cylinder_vertices[index+2][1] = 0.0;
    cylinder_vertices[index+2][2] = -1*height/2;
    index+=3;
  }
  
  vertexcopy(bottom_circle[31], cylinder_vertices[index]);
  vertexcopy(bottom_circle[0],cylinder_vertices[index+1]);
  cylinder_vertices[index+2][0] = 0.0;
  cylinder_vertices[index+2][1] = 0.0;
  cylinder_vertices[index+2][2] = -1*height/2;
  index+=3;

  for(int i=0; i<31; i++)
  {
    vertexcopy(top_circle[i],cylinder_vertices[index]);
    vertexcopy(top_circle[i+1],cylinder_vertices[index+1]);
    cylinder_vertices[index+2][0] = 0.0;
    cylinder_vertices[index+2][1] = 0.0;
    cylinder_vertices[index+2][2] = height/2;
    index+=3;
  }

  vertexcopy(top_circle[31],cylinder_vertices[index]);
  vertexcopy(top_circle[0],cylinder_vertices[index+1]);
  cylinder_vertices[index+2][0] = 0.0;
  cylinder_vertices[index+2][1] = 0.0;
  cylinder_vertices[index+2][2] = height/2;
  index+=3;

  for (int i=0;i<31;i++)
  {
    vertexcopy(top_circle[i],cylinder_vertices[index]);
    vertexcopy(top_circle[i+1],cylinder_vertices[index+1]);
    vertexcopy(bottom_circle[i],cylinder_vertices[index+2]);
    index+=3;

    vertexcopy(top_circle[i+1],cylinder_vertices[index+2]);
    vertexcopy(bottom_circle[i],cylinder_vertices[index]);
    vertexcopy(bottom_circle[i+1],cylinder_vertices[index+1]);
    index+=3;    
  }

  vertexcopy(top_circle[31],cylinder_vertices[index]);
  vertexcopy(top_circle[0],cylinder_vertices[index+1]);
  vertexcopy(bottom_circle[31],cylinder_vertices[index+2]);
  index+=3;

  vertexcopy(top_circle[0],cylinder_vertices[index+2]);
  vertexcopy(bottom_circle[0],cylinder_vertices[index+1]);
  vertexcopy(bottom_circle[31],cylinder_vertices[index]);
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
    node[0]->dec_ry();
    break;
    case GLUT_KEY_RIGHT :
    node[0]->inc_ry();
    break;
    case GLUT_KEY_UP :
    node[0]->dec_rx();
    break;
    case GLUT_KEY_DOWN :
    node[0]->inc_rx();
    break;
    case GLUT_KEY_PAGE_UP :
    node[0]->dec_rz();
    break;
    case GLUT_KEY_PAGE_DOWN :
    node[0]->inc_rz();
    break;
  }
  //Redraw
  glutPostRedisplay();
}


void display(void)
{
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  node[0]->render_tree();
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
  gluPerspective(80.0, 1.0, 1.0, 20.0);

  glMatrixMode(GL_MODELVIEW);
  gluLookAt(0.0, 0.0, 9.0,  // eye is at (0,0,8)
  0.0, 0.0, 0.0,      // center is at (0,0,0)
  0.0, 1.0, 0.0);      // up is in positive Y direction
}

int main(int argc, char **argv)
{
  populateCylinderVertices(0.25,4.0,1.0,0.0,0.0);
  node[0] = new HNode(NULL,384,cylinder_vertices,cylinder_colors);
  node[0]->change_parameters(0.0,0.0,0.0,90.0,-5.0,0.0);

  populateCylinderVertices(0.25,0.8,0.3,0.3,0.3);
  node[1] = new HNode(node[0],384,cylinder_vertices,cylinder_colors);
  node[1]->change_parameters(0.0,0.0,-2.4,0.0,0.0,0.0);

  populateCylinderVertices(0.25,5.0,1.0,0.0,0.0);
  node[2] = new HNode(node[0],384,cylinder_vertices,cylinder_colors);
  node[2]->change_parameters(-2.3,0.0,-1.0,0.0,90.0,0.0);

  populateCylinderVertices(0.25,5.3,1.0,0.0,0.0);
  node[3] = new HNode(node[0],384,cylinder_vertices,cylinder_colors);
  node[3]->change_parameters(-2.4,0.0,0.8,0.0,68.0,0.0);

  populateCylinderVertices(0.25,5.3,1.0,0.0,0.0);
  node[4] = new HNode(node[0],384,cylinder_vertices,cylinder_colors);
  node[4]->change_parameters(2.4,0.0,-0.4,0.0,60.0,0.0);

  populateCylinderVertices(0.25,5.0,1.0,0.0,0.0);
  node[5] = new HNode(node[0],384,cylinder_vertices,cylinder_colors);
  node[5]->change_parameters(2.4,0.0,1.4,0.0,100.0,0.0);

  node[6] = new HNode(node[0],24,seat_vertices, seat_color);
  node[6]->change_parameters(0.0,0.0,-2.8,0.0,0.0,0.0);

/*
  populateCylinderVertices(0.25,2.5,0.5,0.5,0.5);
  node[2] = new HNode(node[0],384,cylinder_vertices,cylinder_colors);
  node[2]->change_parameters(-1.0,0.0,1.0,90.0,90.0,0.0);  

  node[3] = new HNode(node[1],36,cuboid_positions,cuboid_colors);
  node[3]->change_parameters(0.0,0.0,1.25+(b/2),0.0,90.0,90.0);

  node[4] = new HNode(node[2],36,cuboid_positions,cuboid_colors);
  node[4]->change_parameters(0.0,0.0,-1.25-(b/2),0.0,90.0,90.0);*/

  glutInit(&argc, argv);
  glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
  glutInitWindowSize(600,600);
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

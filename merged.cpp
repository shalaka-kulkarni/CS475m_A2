#include <GL/glut.h>
#include <iostream>
#include <math.h>
#include "HNode.cpp"

#define PI 3.14159265

using namespace std;

HNode *node[21];

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
  {0.3,0.3,0.3}, {0.3,0.3,0.3}, {0.3,0.3,0.3},
  {0.3,0.3,0.3}, {0.3,0.3,0.3}, {0.3,0.3,0.3},
  {0.3,0.3,0.3}, {0.3,0.3,0.3}, {0.3,0.3,0.3},
  {0.3,0.3,0.3}, {0.3,0.3,0.3}, {0.3,0.3,0.3},
  {0.3,0.3,0.3}, {0.3,0.3,0.3}, {0.3,0.3,0.3},
  {0.3,0.3,0.3}, {0.3,0.3,0.3}, {0.3,0.3,0.3},
  {0.3,0.3,0.3}, {0.3,0.3,0.3}, {0.3,0.3,0.3},
  {0.3,0.3,0.3}, {0.3,0.3,0.3}, {0.3,0.3,0.3}
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
    node[12]->dec_rz();
    break;
    case GLUT_KEY_RIGHT :
    node[12]->inc_rz();
    break;
    case GLUT_KEY_UP :
    node[7]->dec_rz();
    break;
    case GLUT_KEY_DOWN :
    node[7]->inc_rz();
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
  //Frame vertical rod
  populateCylinderVertices(0.25,4.0,1.0,0.0,0.0);
  node[0] = new HNode(NULL,384,cylinder_vertices,cylinder_colors);
  node[0]->change_parameters(0.0,0.0,0.0,90.0,-5.0,0.0);

  populateCylinderVertices(0.25,0.8,0.5,0.5,0.5);
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

  //Axle for pedal shaft - 7
  populateCylinderVertices(0.25,0.75,0.5,0.5,0.5);
  node[7] = new HNode(node[0],384,cylinder_vertices,cylinder_colors);
  node[7]->change_parameters(0.0,0.0,2.0,90.0,0.0,0.0);

  //Pedal shafts
  populateCylinderVertices(0.25,1.8,0.5,0.5,0.5);
  node[8] = new HNode(node[7],384,cylinder_vertices,cylinder_colors);
  node[8]->change_parameters(1.0,0.0,-0.4,90.0,90.0,0.0);

  populateCylinderVertices(0.25,1.8,0.5,0.5,0.5);
  node[9] = new HNode(node[7],384,cylinder_vertices,cylinder_colors);
  node[9]->change_parameters(-1.0,0.0,0.4,90.0,90.0,0.0); 

  //Pedals
  node[10] = new HNode(node[8],36,cuboid_positions,cuboid_colors);
  node[10]->change_parameters(0.0,0.0,0.9+(b/2),0.0,90.0,90.0);

  node[11] = new HNode(node[9],36,cuboid_positions,cuboid_colors);
  node[11]->change_parameters(0.0,0.0,-0.9-(b/2),0.0,90.0,90.0);

  //Front Handlebar 
  //Axle for front handlebar movement - 12
  populateCylinderVertices(0.25,2.2,1.0,0.0,0.0);
  node[12] = new HNode(node[0],384,cylinder_vertices,cylinder_colors);
  node[12]->change_parameters(-5.0,0.0,-0.5,0.0,0.0,0.0);

  populateCylinderVertices(0.2,0.8,0.5,0.5,0.5);
  node[13] = new HNode(node[12],384,cylinder_vertices,cylinder_colors);
  node[13]->change_parameters(0.0,0.0,-1.5,0.0,0.0,0.0);

  populateCylinderVertices(0.2,0.7,0.5,0.5,0.5);
  node[14] = new HNode(node[13],384,cylinder_vertices,cylinder_colors);
  node[14]->change_parameters(-0.3,0.0,-0.35,0.0,50.0,90.0);

  populateCylinderVertices(0.15,3.0,0.5,0.5,0.5);
  node[15] = new HNode(node[12],384,cylinder_vertices,cylinder_colors);
  node[15]->change_parameters(-0.5,0.0,-2.1,90.0,0.0,0.0);

  populateCylinderVertices(0.2,0.5,0.3,0.3,0.3);
  node[16] = new HNode(node[15],384,cylinder_vertices,cylinder_colors);
  node[16]->change_parameters(0.0,0.0,-1.5,0.0,0.0,0.0);

  populateCylinderVertices(0.2,0.5,0.3,0.3,0.3);
  node[17] = new HNode(node[15],384,cylinder_vertices,cylinder_colors);
  node[17]->change_parameters(0.0,0.0,1.5,0.0,0.0,0.0);

  populateCylinderVertices(0.25,0.75,1.0,0.0,0.0);
  node[18] = new HNode(node[12],384,cylinder_vertices,cylinder_colors);
  node[18]->change_parameters(0.0,0.0,1.1,90.0,0.0,0.0);

  populateCylinderVertices(0.2,1.8,1.0,0.0,0.0);
  node[19] = new HNode(node[18],384,cylinder_vertices,cylinder_colors);
  node[19]->change_parameters(0.0,(-0.2+0.9),0.37,90.0,0.0,0.0);

  populateCylinderVertices(0.2,1.8,1.0,0.0,0.0);
  node[20] = new HNode(node[18],384,cylinder_vertices,cylinder_colors);
  node[20]->change_parameters(0.0,(-0.2+0.9),-0.37,90.0,0.0,0.0);  

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
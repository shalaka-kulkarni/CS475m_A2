#include <GL/glut.h>
#include <iostream>
#include <vector>
#include <math.h>
#include "HNode.cpp"
#define PI 3.14159265
using namespace std;

HNode* wheelNode[7];	//12 spokes and a rim
HNode* rim[1];

float v_cyl_pos[32*4*3][3];		//32 triangles per circular face of cylinder; 3 vertices per triangle; 3 coordinates per vertex
float v_cyl_col[32*4*3][3];

float top_circle[32][3];
float bottom_circle[32][3];

void vertexcopy1(float *src,float *dest)
{
  dest[0]=src[0];
  dest[1]=src[1];
  dest[2]=src[2];
}

void populateCylinderVertices(float radius, float height, float _r, float _g, float _b)
{
  for(int i=0; i<192; i++)
  {
    v_cyl_col[i][0] = _r;
    v_cyl_col[i][1] = _g;
    v_cyl_col[i][2] = _b;
  }
  for(int i=192; i<384; i++)
  {
    v_cyl_col[i][0] = _b;
    v_cyl_col[i][1] = _r;
    v_cyl_col[i][2] = _g;
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
    vertexcopy1(bottom_circle[i], v_cyl_pos[index]);
    vertexcopy1(bottom_circle[i+1],v_cyl_pos[index+1]);
    v_cyl_pos[index+2][0] = 0.0;
    v_cyl_pos[index+2][1] = 0.0;
    v_cyl_pos[index+2][2] = -1*height/2;
    index+=3;
  }
  
  vertexcopy1(bottom_circle[31], v_cyl_pos[index]);
  vertexcopy1(bottom_circle[0],v_cyl_pos[index+1]);
  v_cyl_pos[index+2][0] = 0.0;
  v_cyl_pos[index+2][1] = 0.0;
  v_cyl_pos[index+2][2] = -1*height/2;
  index+=3;

  for(int i=0; i<31; i++)
  {
    vertexcopy1(top_circle[i],v_cyl_pos[index]);
    vertexcopy1(top_circle[i+1],v_cyl_pos[index+1]);
    v_cyl_pos[index+2][0] = 0.0;
    v_cyl_pos[index+2][1] = 0.0;
    v_cyl_pos[index+2][2] = height/2;
    index+=3;
  }

  vertexcopy1(top_circle[31],v_cyl_pos[index]);
  vertexcopy1(top_circle[0],v_cyl_pos[index+1]);
  v_cyl_pos[index+2][0] = 0.0;
  v_cyl_pos[index+2][1] = 0.0;
  v_cyl_pos[index+2][2] = height/2;
  index+=3;

  for (int i=0;i<31;i++)
  {
    vertexcopy1(top_circle[i],v_cyl_pos[index]);
    vertexcopy1(top_circle[i+1],v_cyl_pos[index+1]);
    vertexcopy1(bottom_circle[i],v_cyl_pos[index+2]);
    index+=3;

    vertexcopy1(top_circle[i+1],v_cyl_pos[index+2]);
    vertexcopy1(bottom_circle[i],v_cyl_pos[index]);
    vertexcopy1(bottom_circle[i+1],v_cyl_pos[index+1]);
    index+=3;    
  }

  vertexcopy1(top_circle[31],v_cyl_pos[index]);
  vertexcopy1(top_circle[0],v_cyl_pos[index+1]);
  vertexcopy1(bottom_circle[31],v_cyl_pos[index+2]);
  index+=3;

  vertexcopy1(top_circle[0],v_cyl_pos[index+2]);
  vertexcopy1(bottom_circle[0],v_cyl_pos[index+1]);
  vertexcopy1(bottom_circle[31],v_cyl_pos[index]);

  /*for(int i=0;i<384;i++)
  {
  	for(int j=0;j<3;j++)
  	{
  		cout<<v_cyl_pos[i][j]<<" ";
  	}
  	cout<<"\n";
  }*/
}

void createNodes()
{
  //Parent Node
  float v_par_pos[1][3] = {{0,0,0}};
  float v_par_col[1][3] = {{0,0,0}};
  wheelNode[0] = new HNode(NULL,1,v_par_pos,v_par_col);
  //Child Nodes
  for(int i=1;i<7;i++)
  {
  	wheelNode[i] = new HNode(wheelNode[0],384,v_cyl_pos,v_cyl_col);//cylinder_vertices, cylinder_colors);//
  	wheelNode[i]->change_parameters(0,0,0,90,30*(i-1),0);
  }
  float v_tor_pos[1][3] = {2.2, 2, -999};
  float v_tor_col[1][3] = {1.0, 0.0, 1.0};
  rim[0] = new HNode(wheelNode[0],1,v_tor_pos,v_tor_col);
  //wheelNode[7] = rim[0];

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
    rim[0]->dec_ry();
    break;
    case GLUT_KEY_RIGHT :
    wheelNode[0]->inc_ry();
    rim[0]->inc_ry();
    break;
    case GLUT_KEY_UP :
    wheelNode[0]->dec_rx();
    rim[0]->dec_rx();
    break;
    case GLUT_KEY_DOWN :
    wheelNode[0]->inc_rx();
    rim[0]->inc_rx();
    break;
    case GLUT_KEY_PAGE_UP :
    wheelNode[0]->dec_rz();
    rim[0]->dec_rz();
    break;
    case GLUT_KEY_PAGE_DOWN :
    wheelNode[0]->inc_rz();
    rim[0]->inc_rz();
    break;
  }
  //Redraw
  glutPostRedisplay();
}

void display(void)
{
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  wheelNode[0]->render_tree();
  rim[0]->renderTorus();
  //cout<<"Rendered"<<endl;
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
  populateCylinderVertices(0.1,4,1,0,1);
  createNodes();
  /*for(int i=0;i<1;i++)
  {
  	for(int j=0;j<3;j++)
  	{
  		cout<<wheelNode[0]->vertex_pos[i][j]<<" ";
  	}
  	cout<<"\n";
  }
  for(int i=0;i<384;i++)
  {
  	for(int j=0;j<3;j++)
  	{
  		cout<<wheelNode[1]->vertex_pos[i][j]<<" ";
  	}
  	cout<<"\n";
  }*/
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

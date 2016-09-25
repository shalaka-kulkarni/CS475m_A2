#include <GL/glut.h>
#include <iostream>
#include <math.h>
#include "HNode.cpp"

#define PI 3.14159265

using namespace std;

HNode *node[5];

float x_angle=0.0;
float y_angle=0.0;
float z_angle=0.0;
float offset=5.0;

float l=0.3, b=0.2, h=0.05; // cuboid is 2l along x, 2b along y, 2h along z 

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

/*
void drawCyclePart1(void)
{
  float color[3]={0.5,0.5,0.5};
  float center[3] = {0.0,0.0,0.0};

  node[0]->render();

  //-----------Shaft1
  populateVertices(1.0);
  glPushMatrix();
  
  glTranslatef(0.0,0.0,0.0);
  glRotatef(90, 0.0, 1.0, 0.0);
  glRotatef(0.0, 1.0, 0.0, 0.0);
  //glRotatef(z_angle, 0.0, 0.0, 1.0);
  
  //drawing top circle
  center[2] = 1.0;
  
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
  center[2] = 0.0;
  
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

  //-----------Axle
  populateVertices(1.2);
  glPushMatrix();
  
  glTranslatef(0.0,0.0,0.0);
  glRotatef(0, 0.0, 1.0, 0.0);
  glRotatef(0, 1.0, 0.0, 0.0);
  //glRotatef(z_angle, 0.0, 0.0, 1.0);
  
  //drawing top circle
  center[2] = 1.2;
  
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
  center[2] = 0.0;
  
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

  //-----------Shaft2
  populateVertices(-1.0);
  glPushMatrix();
  
  glTranslatef(0.0,0.0,1.2);
  glRotatef(90, 0.0, 1.0, 0.0);
  glRotatef(0.0, 1.0, 0.0, 0.0);
  //glRotatef(z_angle, 0.0, 0.0, 1.0);
  
  //drawing top circle
  center[2] = -1.0;
  
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
  center[2] = 0.0;
  
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

  //-----------Pedal2
  /*glPushMatrix();
  glTranslatef(-1.0,0.0,1.2);

  glRotatef(90.0, 0.0, 0.0, 1.0);
  glRotatef(90.0, 0.0, 1.0, 0.0);
  glRotatef(0.0, 1.0, 0.0, 0.0);
  
  for (int i=0;i<12;i++){
    glBegin(GL_TRIANGLES);
    //glColor3fv(v_colors[i]);
    glColor3f(0.3, 0.3, 0.3);
    glVertex3fv(cuboid_positions[3*i]);
    glVertex3fv(cuboid_positions[3*i+1]);
    glVertex3fv(cuboid_positions[3*i+2]);
    glEnd();
  }

  glPopMatrix();*/
  //node[1]->render();
//}*/


void display(void)
{
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  node[0]->render();
  //drawCyclePart1();
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
  //node[0] = new HNode(NULL,36,cuboid_positions,cuboid_colors);
  //node[0]->change_parameters(0.0,0.0,0.0,90.0,0.0,0.0);

  populateCylinderVertices(1.0,2.0,0.5,0.5,0.5);
  node[0] = new HNode(NULL,384,cylinder_vertices,cylinder_colors);
  node[0]->change_parameters(0.0,0.0,0.0,90.0,90.0,0.0);  

 // node[1] = new HNode(NULL,36,cuboid_positions,cuboid_colors);
  //node[1]->change_parameters(-1.0,0.0,0.0,0.0,90.0,90.0);

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

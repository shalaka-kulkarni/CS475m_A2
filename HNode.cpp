#include "HNode.hpp"

float shift = 0.5;

void vertexcopy(float *src,float *dest){
  dest[0]=src[0];
  dest[1]=src[1];
  dest[2]=src[2];
}

HNode::HNode(HNode* par, int num_v, float pos_v4[][3],  float col_v4[][3]){
  flag = false;
  if(par!=NULL){
    parent=par;
    parent->add_child(this);
  }
  num_vertices=num_v;
  vertex_pos = new float*[num_vertices];
  vertex_col = new float*[num_vertices];
  for(int i=0;i<num_v;i++){
    vertex_pos[i]=new(float[3]);
    vertexcopy(pos_v4[i],vertex_pos[i]);

    vertex_col[i]=new(float[3]);
    vertexcopy(col_v4[i],vertex_col[i]);
  }
  tx=ty=tz=rx=ry=rz=0;
}

void HNode::add_child(HNode *child){
  children.push_back(child);
}

void HNode::renderTorus()
{
  glTranslatef(tx,ty,tz);
  //Rotate at translated origin
  glRotatef(rx, 1.0, 0.0, 0.0);
  glRotatef(ry, 0.0, 1.0, 0.0);
  glRotatef(rz, 0.0, 0.0, 1.0);
  glColor3fv(vertex_col[0]);
  glutSolidTorus(vertex_pos[0][0]-vertex_pos[0][1], vertex_pos[0][0],50,50);
}

void HNode::render(){
  if(flag==true)
  {
    this->renderTorus();
  }
  else
  {
  //Translate the origin
  glTranslatef(tx,ty,tz);
  //Rotate at translated origin
  glRotatef(rx, 1.0, 0.0, 0.0);
  glRotatef(ry, 0.0, 1.0, 0.0);
  glRotatef(rz, 0.0, 0.0, 1.0);
  
    glBegin(GL_TRIANGLES);
    for (int i=0;i<num_vertices;i++){
      glColor3fv(vertex_col[i]);
      glVertex3fv(vertex_pos[i]);
    }
    glEnd();
  }
}

void HNode::change_parameters(float tx,float ty,float tz,float rx,float ry,float rz){
  this->tx=tx;
  this->ty=ty;
  this->tz=tz;
  this->rx=rx;
  this->ry=ry;
  this->rz=rz;
}

void HNode::render_tree(){
  glPushMatrix();
  
    render();

  for(int i=0;i<children.size();i++){
    children[i]->render_tree();
  }
  glPopMatrix();
}


void HNode::inc_rx(){
  rx+=shift;
  if(rx>360)
  rx-=360;
}
void HNode::inc_ry(){
  ry+=shift;
  if(ry>360)
  ry-=360;
}
void HNode::inc_rz(){
  rz+=shift;
  if(rz>360)
  rz-=360;
}
void HNode::dec_rx(){
  rx-=shift;
  if(rx<0)
  rx+=360;
}
void HNode::dec_ry(){
  ry-=shift;
  if(ry<0)
  ry+=360;
}
void HNode::dec_rz(){
  rz-=shift;
  if(rz<0)
  rz+=360;
}
#include "glcommon.h"
    // int deltax=(x-xpos)*xscale;
    // int deltay=(y-ypos)*yscale;


Object::Object(){
  xpos=0;
  ypos=0;
  width=20;
  height=20;
  xscale=1.0f;
  yscale=1.0f;
  down=0;
  up=0;
}

Object::~Object(){
}
bool
Object::chk_hit(int x,int y){
  return
    xpos<=x && x<xpos+width*xscale &&
    ypos<=y && y<ypos+height*yscale ;
}

void
Object::keydown(unsigned char key, int x, int y){
}

void
Object::mouse(int button , int state , int x , int y){
  // printf("mouse hit %d %d\n",x,y);
  tmp_xpos=xpos;
  tmp_ypos=ypos;
  tmp_x=x;
  tmp_y=y;
}
void
Object::motion(int x , int y){
  // printf("motion hit %d %d\n",x,y);
  xpos=tmp_xpos+x-tmp_x;
  ypos=tmp_ypos+y-tmp_y;
}
void
Object::passive_motion(int x , int y){
}
void
Object::display(){
    glColor3ub(255,0,0);
    glBegin(GL_TRIANGLES);

    glVertex2f( 0.0, 20.0);
    glVertex2f(20.0, 20.0);
    glVertex2f( 20.0,0.0);
 
    glEnd(); 
}

void
Object::sys_keydown(unsigned char key, int x, int y){
  if(chk_hit(x,y)){
    keydown(key,x,y);
  }
}

void
Object::sys_motion(int x , int y){
  if(down){
    //chk_hit(x,y)){
    motion(x,y);
  }
}
void
Object::sys_passive_motion(int x , int y){
  if(chk_hit(x,y)){
    passive_motion(x,y);
  }
}
void
Object::sys_mouse(int button , int state , int x , int y){
  if(chk_hit(x,y)){
    down=
      ( (button == GLUT_LEFT_BUTTON   &&  state==GLUT_DOWN)  ? 1	: 0)|
      ( (button == GLUT_MIDDLE_BUTTON &&  state==GLUT_DOWN)  ? 2	: 0)|
      ( (button == GLUT_RIGHT_BUTTON  &&  state==GLUT_DOWN)  ? 4	: 0)|
      ( (button == GLUT_UP_BUTTON     &&  state==GLUT_DOWN)  ? 8	: 0)|
      ( (button == GLUT_DOWN_BUTTON   &&  state==GLUT_DOWN)  ? 16	: 0);
    up=
      ( (button == GLUT_LEFT_BUTTON   &&  state==GLUT_UP)  ? 1	: 0)|
      ( (button == GLUT_MIDDLE_BUTTON &&  state==GLUT_UP)  ? 2	: 0)|
      ( (button == GLUT_RIGHT_BUTTON  &&  state==GLUT_UP)  ? 4	: 0)|
      ( (button == GLUT_UP_BUTTON     &&  state==GLUT_UP)  ? 8	: 0)|
      ( (button == GLUT_DOWN_BUTTON   &&  state==GLUT_UP)  ? 16	: 0);
    mouse(button,state,x,y);
  }
}
void
Object::sys_display(){
    glPushMatrix();
    glTranslatef(xpos,ypos,0.0f);
    glScalef(xscale,yscale,1.0f);
    glColor3ub(255,255,255);
    display();
    glPopMatrix();
}



Button::Button(const string& str,int x,int y,void (*f)(void*,void*),void* arg){
  this->str=str;
  xpos=x;
  ypos=y;
  width=100;
  height=20;
  this->f=f;
  this->arg=arg;
}
Button::~Button(){
}
void
Button::motion(int x , int y){
}
void
Button::display(){
  glColor3ub(128,128,128);
  Square(0,0,width,height);
  glColor3ub(0,0,0);
  Printf(5,15,str.c_str());
}
void
Button::mouse(int button , int state , int x , int y){
  if(this->down){
    f(this,j);
  }
}

void
pushed_listbox(void* self,void* arg){
  Button*  b =(Button*)self;
  ListBox* lb=(ListBox*)arg;
  lb->str=b->str;
}

ListBox::ListBox(int x,int y){
  xpos=x;
  ypos=y;
  width=100;
  height=100;
  vec.push_back(new Button("label1",0,3, pushed_listbox,this));
  vec.push_back(new Button("label2",30,3,pushed_listbox,this));
  vec.push_back(new Button("label3",60,3,pushed_listbox,this));

}
ListBox::~ListBox(){
}
void,
ListBox::motion(int x , int y){
}
void
ListBox::display(){
  glColor3ub(128,128,128);
  Square(0,0,width,height);
  glColor3ub(0,0,0);

  for(int i=0;i<vec.size();i++)
    vec[i]->sys_display();
  
  //  Printf(5,15,str.c_str());
}

void
ListBox::mouse(int button , int state , int x , int y){
  if(this->down){
    //    f();
  }
}


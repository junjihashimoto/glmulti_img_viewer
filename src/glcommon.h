#ifndef TEXTURE_H
#define TEXTURE_H

#include <cstdlib>
#include <cstring>
#include <cstdio>
#include <string>
extern "C"{
#include <GL/gl.h>
#include <GL/glut.h>
#include <GL/freeglut_ext.h>
}


#include <bmp.h>
#include <string>
#include <vector>
using namespace std;

#define LEFT_3D  0
#define RIGHT_3D 1


//GL_TEXTURE_2D
//GL_TEXTURE_RECTANGLE_ARB
#ifndef GL_TEXTURE_RECTANGLE_ARB
#define GL_TEXTURE_RECTANGLE_ARB 0x84F5
#endif


struct Texture{
public:
  unsigned int sizeX;  //横
  unsigned int sizeY; //縦
  GLuint texture;
  int    texturep;
  Texture();
  Texture(const Texture& tex);
  ~Texture();
  void set(const BMPb& bmp);
  Texture(const BMPb& bmp);
  Texture& operator = (const Texture& tex);
  void display();
};

struct Object{
  float xscale;
  float yscale;
  float xpos;
  float ypos;
  float width;
  float height;
  int   down;
  int   up;
  
private:
  float tmp_xpos;
  float tmp_ypos;
  float tmp_x;
  float tmp_y;
public:
  Object();
  virtual ~Object();
  virtual bool chk_hit(int x,int y);
  virtual void keydown(unsigned char key, int x, int y);
  virtual void mouse(int button , int state , int x , int y);
  virtual void motion(int x , int y);
  virtual void passive_motion(int x , int y);
  virtual void display();
  virtual void sys_keydown(unsigned char key, int x, int y);
  virtual void sys_motion(int x , int y);
  virtual void sys_passive_motion(int x , int y);
  virtual void sys_mouse(int button , int state , int x , int y);
  virtual void sys_display();
};

struct Button : public Object{
  void (*f)();
  string str;
  Button(const string& str,int x,int y,void (*f)());
  ~Button();
  void motion(int x , int y);
  void display();
  void mouse(int button , int state , int x , int y);
};

struct ListBox : public Object{
  int id;
  vector<string> vec;
  ListBox(int x,int y);
  ~ListBox();
  void motion(int x , int y);
  void display();
  void mouse(int button , int state , int x , int y);
};


extern void set_vsync(int interval);
extern void fps_timer(int value=0);

void Printf(int x,int y,const char* format, ...);
void Square(int x1,int y1,int x2, int y2);


inline int
lmt16(int x){
  if(x<0)
    return 0;
  else if(x>16)
    return 16;
  else
    return x;
}





#endif

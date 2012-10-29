#include "glcommon.h"
#include "utils.h"

#include <vector>

using namespace std;


#define INIT_WIDTH  640
#define INIT_HEIGHT 480
#define WIDTH  glutGet(GLUT_WINDOW_WIDTH)
#define HEIGHT glutGet(GLUT_WINDOW_HEIGHT)

int vsync = 1;
int fullscreen=0;
int g_LeaveGameMode=0;


vector<Object*> obj_vec;

void timer(int value) {
  glutTimerFunc(100 , timer , 0);
  //  glutPostRedisplay();
}


void
print_push(void*,void*){
  printf("pushed\n");
}


void
display(void){
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  glViewport(0, 0, WIDTH, HEIGHT);
  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();
  glOrtho(0.0, WIDTH, HEIGHT, 0.0, -1.0, 1.0);


  for(int i=0;i<obj_vec.size();i++)
    obj_vec[i]->sys_display();

  glutSwapBuffers();

  if( g_LeaveGameMode == 1 ){
    glutLeaveMainLoop();
    g_LeaveGameMode = 0;
  }

}

void
idle(){
  glutPostRedisplay();
}


void
keydown(unsigned char key, int x, int y){
  for(int i=0;i<obj_vec.size();i++)
    obj_vec[i]->sys_keydown(key,x,y);

  switch(key){
  case 'f':
    fullscreen = !fullscreen;
    if (fullscreen){
      glutFullScreen();                /* Go to full screen */
    }else{
      glutReshapeWindow(INIT_WIDTH,INIT_HEIGHT);
      glutPositionWindow(0,0);
    }
    break;
  case 'q':
  case 27://ESC key
    g_LeaveGameMode = 1;
    break;
  case ' ':
    vsync = vsync==0 ? 1:0;
    set_vsync(vsync);
    break;
  }
  
}


void
mouse(int button , int state , int x , int y) {
  for(int i=0;i<obj_vec.size();i++)
    obj_vec[i]->sys_mouse(button,state,x,y);
}

void
motion(int x , int y) {
  for(int i=0;i<obj_vec.size();i++)
    obj_vec[i]->sys_motion(x,y);
}

void
passive_motion(int x , int y) {
  for(int i=0;i<obj_vec.size();i++)
    obj_vec[i]->sys_passive_motion(x,y);
}


void
dropfile(const char* file){
  printf("dropfile:'%s'\n",file);
}

void
Init(){
  glClearColor(0.3f, 0.3f, 0.3f, 1.0f);
  glEnable(GL_DEPTH_TEST);
}

void
reshape(int w,int h){
}


int
main(int argc, char *argv[]){

  char *temp[2]={"img viewer",NULL};
  int num=1;
  glutInit(&num,temp);
  glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB );
  glutInitWindowSize(INIT_WIDTH, INIT_HEIGHT);
  glutCreateWindow("img viewer");
  glutKeyboardFunc(keydown);
  // glutKeyboardUpFunc(keyup);
  // glutSpecialFunc(skeydown);
  // glutSpecialUpFunc(skeyup);

  glutMouseFunc(mouse);
  glutMotionFunc(motion);
  glutPassiveMotionFunc(passive_motion);

  glutDisplayFunc(display);
  Init();
  //  set_vsync(1);
  //glutTimerFunc(100 , timer , 0);
  glutIdleFunc(idle);
  glutDropFileFunc(dropfile);

  obj_vec.push_back(new Object());
  obj_vec.push_back(new Object());
  obj_vec.push_back(new Button("Rec",0,30,print_push));
  obj_vec.push_back(new Button("Play",0,60,print_push));
  obj_vec.push_back(new Button("Stop",0,90,print_push));
  obj_vec.push_back(new ListBox(0,120));

  obj_vec[1]->xpos=100;
  
  glutMainLoop();
  return 0;
}

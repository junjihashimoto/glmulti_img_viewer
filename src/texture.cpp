#include "glcommon.h"

//GL_TEXTURE_2D
//GL_TEXTURE_RECTANGLE_ARB
#ifndef GL_TEXTURE_RECTANGLE_ARB
#define GL_TEXTURE_RECTANGLE_ARB 0x84F5
#endif

#define aligned_base(w) ((w)*3)%4==0? 0 : 4-(((w)*3)%4)
#define aligned_size(w,h) (sizeof(unsigned char)*((w)+aligned_base(w))*(h)*3  )
#define aligned_pos(w,x,y,z) ((x)*3+(y)*(3*(w)+aligned_base(w))+(z))



Texture::Texture(){
  texturep=0;
}
Texture::Texture(const Texture& tex){
  sizeX=tex.sizeX;
  sizeY=tex.sizeY;
  if(tex.texturep){
    glGenTextures( 1, &texture );
    texturep=1;
    
    glBindTexture( GL_TEXTURE_RECTANGLE_ARB, tex.texture );
    unsigned char* data=(unsigned char*)malloc(aligned_size(sizeX,sizeY));
    glGetTexImage(GL_TEXTURE_2D,0,GL_RGB,GL_UNSIGNED_BYTE,data);
    
    glBindTexture( GL_TEXTURE_RECTANGLE_ARB, texture );
    glTexParameterf( GL_TEXTURE_RECTANGLE_ARB, GL_TEXTURE_MIN_FILTER, GL_LINEAR );
    glTexParameterf( GL_TEXTURE_RECTANGLE_ARB, GL_TEXTURE_MAG_FILTER, GL_LINEAR );
    glTexImage2D( GL_TEXTURE_RECTANGLE_ARB, 0, GL_RGBA, sizeX, sizeY, 0, GL_RGB, GL_UNSIGNED_BYTE, data );

      
    free(data);
  }else{
    texturep=0;
  }
}
Texture::~Texture(){
  if(texturep)
    glDeleteTextures(1,&texture);
}
void Texture::set(const BMPb& bmp){
  unsigned char* data=NULL;
  sizeX=bmp.w;
  sizeY=bmp.h;
  if(sizeX==0||sizeY==0)
    return;
  int align=aligned_base(sizeX);

  if(align==0&&(sizeof(bmp.rgb[0])==3)){
  }else{
    data=(unsigned char*)malloc(aligned_size(sizeX,sizeY));
    bmp_for3(bmp)
      data[aligned_pos(sizeX,x,y,z)]=bmp(x,y,z);
  }
  if(!texturep){
    glGenTextures( 1, &texture );
    texturep=1;
  }
  glBindTexture( GL_TEXTURE_RECTANGLE_ARB, texture );
  glTexParameterf( GL_TEXTURE_RECTANGLE_ARB, GL_TEXTURE_MIN_FILTER, GL_LINEAR );
  glTexParameterf( GL_TEXTURE_RECTANGLE_ARB, GL_TEXTURE_MAG_FILTER, GL_LINEAR );
       
  if(align==0&&(sizeof(bmp.rgb[0])==3)){
    glTexImage2D( GL_TEXTURE_RECTANGLE_ARB, 0, GL_RGBA, sizeX, sizeY, 0, GL_RGB, GL_UNSIGNED_BYTE, bmp.rgb );
  }else{
    glTexImage2D( GL_TEXTURE_RECTANGLE_ARB, 0, GL_RGBA, sizeX, sizeY, 0, GL_RGB, GL_UNSIGNED_BYTE, data );
    free(data);
  }
}
Texture::Texture(const BMPb& bmp){
  set(bmp);
}

Texture&
Texture::operator = (const Texture& tex){
  sizeX=tex.sizeX;
  sizeY=tex.sizeY;

  if(!texturep){
    texturep=1;
    glGenTextures( 1, &texture );
  }
  glBindTexture( GL_TEXTURE_RECTANGLE_ARB, tex.texture );
  unsigned char* data=(unsigned char*)malloc(aligned_size(sizeX,sizeY));
  glGetTexImage(GL_TEXTURE_2D,0,GL_RGB,GL_UNSIGNED_BYTE,data);
    
  glBindTexture( GL_TEXTURE_RECTANGLE_ARB, texture );
  glTexParameterf( GL_TEXTURE_RECTANGLE_ARB, GL_TEXTURE_MIN_FILTER, GL_LINEAR );
  glTexParameterf( GL_TEXTURE_RECTANGLE_ARB, GL_TEXTURE_MAG_FILTER, GL_LINEAR );
  glTexImage2D( GL_TEXTURE_RECTANGLE_ARB, 0, GL_RGBA, sizeX, sizeY, 0, GL_RGB, GL_UNSIGNED_BYTE, data );

  free(data);
  
  return *this;
}
  
void
Texture::display(){
  if(sizeX==0||sizeY==0)
    return;
  glEnable(GL_TEXTURE_RECTANGLE_ARB);
  glBindTexture( GL_TEXTURE_RECTANGLE_ARB, texture );

  glBegin(GL_QUADS);
  {
    glTexCoord2f(0.0f, 0.0f);
    glVertex2f(0,0);
    glTexCoord2f(sizeX,0);
    glVertex2f(sizeX,0);
    glTexCoord2f(sizeX,sizeY);
    glVertex2f(sizeX,sizeY);
    glTexCoord2f(0,sizeY);
    glVertex2f(0,sizeY);
  }
  glEnd();
  
  glDisable(GL_TEXTURE_RECTANGLE_ARB);
}



//
//  main.cpp
//  sdl_ogl_poc
//
//  Created by Osman H. Romero on 11/24/16.
//  Copyright © 2016 Osman H. All rights reserved.
//


#include <stdio.h>
#include <stdlib.h>

#include <SDL/SDL.h>

#ifdef __APPLE__
#include <OpenGL/gl.h>
#include <OpenGL/glu.h>
#else
#include <GL/gl.h>
#include <GL/glu.h>
#endif



// float variable to rotate the 3D shape
float rot = 0.0f;
// GL unsigned int to store the GL texture
GLuint texture[1];

void initiateOpenGL(int w,int h)
{
    glViewport(0,0,w,h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    
    gluPerspective(45.0f, (GLfloat)w/(GLfloat)h, 0.1f, 100.0f);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    
    glClearColor(0.0f,0.0f,0.0f,0.0f);
    glClearDepth(1.0f);
    
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_TEXTURE_2D);
    
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glTranslatef(0.0f,0.0f,-15.0f);
}

int initiateSDL(int w, int h, char *caption){
    if (SDL_Init(SDL_INIT_VIDEO)<0){
        printf("Error starting SDL: %s",SDL_GetError());
        return 0;
    }
    
    SDL_Surface *screen = SDL_SetVideoMode(w,h,0,SDL_HWSURFACE|SDL_OPENGL|SDL_RESIZABLE);
    
    if (!screen){
        printf("Error creating the SDL window: %s",SDL_GetError());
        return 0;
    }
    
    SDL_WM_SetCaption(caption,NULL);
    
    return 1;
}

int createTexture(char *img){
    SDL_Surface *image = SDL_LoadBMP(img);
    
    if (!image) {
        printf("Could not find the image: %s\n", img);
        return 0;
    }
    
    glGenTextures(1,&texture[0]);
    glBindTexture(GL_TEXTURE_2D,texture[0]);
    glPixelStorei(GL_UNPACK_ALIGNMENT,1);
    
    printf("BytesPerPixel: %d \n",image->format->BytesPerPixel);
    printf("Pixels: %d \n",image->pixels);
    
    gluBuild2DMipmaps(GL_TEXTURE_2D,image->format->BytesPerPixel,image->w,image->h,GL_RGB,GL_UNSIGNED_BYTE,image->pixels);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
    return 1;
}

void renderScene(){
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    
    glLoadIdentity();
    glEnable(GL_TEXTURE_2D);
    
    glTranslatef( 0.0f, 0.0f, -6.0f );
    glRotatef(rot,1.0f,1.0f,1.0f);
    
    glBegin(GL_QUADS);
    glTexCoord2f(0.0f, 0.0f); glVertex3f(-2.0f, 1.0f,  0.0f);
    glTexCoord2f(1.0f, 0.0f); glVertex3f( 2.0f, 1.0f,  0.0f);
    glTexCoord2f(1.0f, 1.0f); glVertex3f( 2.0f,  -1.0f,  0.0f);
    glTexCoord2f(0.0f, 1.0f); glVertex3f(-2.0f,  -1.0f,  0.0f);
    glEnd();
    
    rot +=0.3f;
    SDL_GL_SwapBuffers();
}

void printHelp(char *argv[]){
    printf("Program should be ran as follows:\n\n");
    printf("%s image_to_be_loaded\n\n",argv[0]);
}




int main(int argc, char *argv[]) {
    if (argc < 2){
        printHelp(argv);
        return -1;
    }
    
    int w=640;
    int h=480;
    
    int ok = initiateSDL(w,h,"sdl-ogl-test");
    if (!ok) return -1;
    
    initiateOpenGL(w,h);
    
    ok = createTexture(argv[1]);
    if (!ok) return -1;
    
    SDL_Event event;
    while (ok) {
        while(SDL_PollEvent(&event)) {
            if (event.type==SDL_QUIT) {
                ok = 0;
                break;
            }
        }
        renderScene();
    }
    
    SDL_Quit();
    return 0;
    
}


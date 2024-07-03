#include <alloca.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include <OpenGL/gl3.h>
#include <GLFW/glfw3.h>

#include "util.h"
#include "shader.h"
#include "object.h"

const int WIDTH = 600;
const int HEIGHT = 600;
const int FPS = 60;

// sleep wrapper function
void sleep_us(unsigned long microseconds){
  struct timespec ts;
  ts.tv_sec = microseconds / 1000000ul;
  ts.tv_nsec = (microseconds % 1000000ul) * 1000;
  nanosleep(&ts, NULL);
}

// global variable for render modes (fill/wireframe)
int G_fill = 1;

// error reporting code for glfw
void errorCallback(int error, const char* desc){
  fprintf(stderr, "Error: %s\n", desc);
}

// a function to process all key inputs 
static void keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods){
  if(key == GLFW_KEY_ESCAPE && action == GLFW_PRESS){
    glfwSetWindowShouldClose(window, GLFW_TRUE);
  }

  if(key == GLFW_KEY_TAB && action == GLFW_PRESS){
    if(G_fill){ G_fill = 0; glPolygonMode(GL_FRONT_AND_BACK, GL_LINE); }
    else{ G_fill = 1; glPolygonMode(GL_FRONT_AND_BACK, GL_FILL); }
  }
}

// a function to run when a resize happens
void resizeCallback(GLFWwindow* window, int width, int height){
  glViewport(0, 0, width, height);
}

int main(){
  // initialization of glfw
  glfwSetErrorCallback(errorCallback);
  if(!glfwInit()){ errorCallback(0, "glfw didn't initialize"); return -1; }

  // sets the minimum opengl versions 
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
  glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
  
  // makes the window and init all important things
  GLFWwindow* window = glfwCreateWindow(WIDTH, HEIGHT, "Snake", NULL, NULL);
  if(!window){ glfwTerminate(); errorCallback(0, "couldn't make window"); return -1;}
  glfwMakeContextCurrent(window);
  glfwSetKeyCallback(window, keyCallback);
  glfwSetFramebufferSizeCallback(window, resizeCallback);
  glViewport(0, 0, WIDTH, HEIGHT);
  glfwSetWindowAspectRatio(window, WIDTH, HEIGHT);

  // window is scaled so have to adjust frame buffer to be the same as window
  int frameBufferSizeX, frameBufferSizeY;
  glfwGetFramebufferSize(window, &frameBufferSizeX, &frameBufferSizeY);
  glViewport(0, 0, frameBufferSizeX, frameBufferSizeY);

  // data points 
  float vert[] = {
    0.1f, 0.1f, 0.0f,
    0.1f, -0.1f, 0.0f,
    -0.1f, 0.1f, 0.0f,
    -0.1f, -0.1f, 0.0f
  };

  unsigned int ind[] = {
    0, 1, 2,
    1, 2, 3
  };

  // creates the shader program
  struct shader* s = createShaderProgram(
      "./shaders/vertexShader.glsl", 
      "./shaders/fragmentShader.glsl"
    );

  struct object* o = createObject(vert, 12, ind, 6);

  float vert2[] = {
    0.2f, 0.2f, 0.0f,
    0.2f, -0.3f, 0.0f,
    -0.3f, 0.3f, 0.0f,
    -0.3f, -0.3f, 0.0f
  };

  // main game loop
  while(!glfwWindowShouldClose(window)){
    // start of frame 
    clock_t start = clock();
    
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);
    
    setActiveShader(s);
    bindObject(o);
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
    unbindObject();

    updateVertObject(o, vert2, 12);
    
    glfwSwapBuffers(window);
    glfwPollEvents();

    // end of frame 
    clock_t end = clock();
    int msec = ((end - start) * 1000) / CLOCKS_PER_SEC;
    // wait to keep framerate 
    if(!(msec > (1000/FPS)))
      sleep_us(((1000/FPS)-msec) * 1000);

  }
  
  deleteShader(s);
  deleteObject(o);
  
  glfwDestroyWindow(window);
  glfwTerminate();
  return 0;
}



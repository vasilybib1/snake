#include <stdio.h>
#include "lib/GLFW/include/GLFW//glfw3.h"

// error reporting code for glfw
void errorCallback(int error, const char* desc){
  fprintf(stderr, "Error: %s\n", desc);
}

// a function to process all key inputs 
static void keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods){
  if(key == GLFW_KEY_ESCAPE && action == GLFW_PRESS){
    glfwSetWindowShouldClose(window, GLFW_TRUE);
  }
}

int main(){
  // initialization of glfw
  glfwSetErrorCallback(errorCallback);
  if(!glfwInit()){ errorCallback(0, "glfw didn't initialize"); }
  
  //makes the window 
  GLFWwindow* window = glfwCreateWindow(600, 600, "Snake", NULL, NULL);
  if(!window){ errorCallback(0, "couldn't make window"); }
  glfwMakeContextCurrent(window);
  glfwSetKeyCallback(window, keyCallback);
  
  // main game loop
  while(!glfwWindowShouldClose(window)){
    // game logic / rendering 
    glfwSwapBuffers(window);
    glfwPollEvents();
  }
  
  // cleans up the memory
  glfwDestroyWindow(window);
  glfwTerminate();
  return 0;
}

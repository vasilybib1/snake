#include <stdio.h>
#include <stdlib.h>

#include <OpenGL/gl3.h>
#include <GLFW/glfw3.h>

#include "util.h"

const int WIDTH = 600;
const int HEIGHT = 600;

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

// a function to run when a resize happens
void resizeCallback(GLFWwindow* window, int width, int height){
  glViewport(0, 0, width, height);
}

// a function to check that shaders were compiled correctly
void shaderCompilerCheck(unsigned int shader){
  int success;
  char log[512];
  glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
  if(!success){
    glGetShaderInfoLog(shader, 512, NULL, log);
    fprintf(stderr, "Shader Error: %s\n", log);
  }
}

// a function to check that the shader program was compiled correctly
void shaderProgramCompilerCheck(unsigned int program){
  int success;
  char log[512];
  glGetProgramiv(program, GL_COMPILE_STATUS, &success);
  if(!success){
    glGetProgramInfoLog(program, 512, NULL, log);
    fprintf(stderr, "Program Error: %s\n", log);
  }
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

  // data loading 
  float vert[] = {
    -1.0f, -1.0f, 0.0f, 
    0.0f, -1.0f, 0.0f, 
    -1.0f, 0.0f, 0.0f
  };

  // makes the VAO and binds it 
  unsigned int VAO;
  glGenVertexArrays(1, &VAO);
  glBindVertexArray(VAO);

  // makes the VBO (unique id -> bind -> init)
  unsigned int VBO;
  glGenBuffers(1, &VBO); 
  glBindBuffer(GL_ARRAY_BUFFER, VBO); 
  glBufferData(GL_ARRAY_BUFFER, sizeof(vert), vert, GL_STATIC_DRAW);
  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*) 0);
  glEnableVertexAttribArray(0);
  
  // unbinds both after finishing asigning data
  glBindBuffer(GL_ARRAY_BUFFER, 0);
  glBindVertexArray(0);

  // creates the vertex shader
  const char* vertexShaderString = readFile("shaders/vertexShader.glsl");
  unsigned int vertexShader;
  vertexShader = glCreateShader(GL_VERTEX_SHADER);
  glShaderSource(vertexShader, 1, &vertexShaderString, NULL);
  glCompileShader(vertexShader);
  shaderCompilerCheck(vertexShader);

  // creates the fragment shader
  const char* fragmentShaderString = readFile("shaders/fragmentShader.glsl");
  unsigned int fragmentShader;
  fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
  glShaderSource(fragmentShader, 1, &fragmentShaderString, NULL);
  glCompileShader(fragmentShader);
  shaderCompilerCheck(fragmentShader);
  
  // creates the shader program
  unsigned int shaderProgram;
  shaderProgram = glCreateProgram();
  glAttachShader(shaderProgram, vertexShader);
  glAttachShader(shaderProgram, fragmentShader);
  glLinkProgram(shaderProgram);

  // main game loop
  while(!glfwWindowShouldClose(window)){
    // game logic / rendering 
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);
    
    glUseProgram(shaderProgram);
    glBindVertexArray(VAO);
    glDrawArrays(GL_TRIANGLES, 0, 3);
    
    glfwSwapBuffers(window);
    glfwPollEvents();
  }
  
  // cleans up the memory
  free((char*)vertexShaderString);
  free((char*)fragmentShaderString);

  glDeleteShader(vertexShader);
  glDeleteShader(fragmentShader);

  glDeleteVertexArrays(1, &VAO);
  glDeleteBuffers(1, &VBO);
  
  glfwDestroyWindow(window);
  glfwTerminate();
  return 0;
}

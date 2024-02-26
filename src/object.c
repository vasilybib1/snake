#include "object.h"

#include <OpenGL/gl3.h>
#include <GLFW/glfw3.h>

#include <stdlib.h>

struct object* createObject(float* ver, unsigned int verSize, unsigned int* ind, unsigned int indSize){
  struct object* o = malloc(sizeof(struct object));
  o->vertexArray = ver;
  o->indexArray = ind;

  glGenVertexArrays(1, &(o->VAO));
  glGenBuffers(1, &(o->EBO));
  glGenBuffers(1, &(o->VBO)); 

  glBindVertexArray(o->VAO);

  glBindBuffer(GL_ARRAY_BUFFER, o->VBO); 
  glBufferData(GL_ARRAY_BUFFER, sizeof(float)*verSize, o->vertexArray, GL_STATIC_DRAW);

  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, o->EBO);
  glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(unsigned int)*indSize, o->indexArray, GL_STATIC_DRAW);

  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*) 0);
  glEnableVertexAttribArray(0);
  
  unbindObject();
  return o;
}

void bindObject(struct object* o){
  glBindVertexArray(o->VAO);
}

void unbindObject(){
  glBindBuffer(GL_ARRAY_BUFFER, 0);
  glBindVertexArray(0);
}

void deleteObject(struct object *o){
  glDeleteVertexArrays(1, &(o->VAO));
  glDeleteBuffers(1, &(o->VBO));
  glDeleteBuffers(1, &(o->EBO));
  free(o);
}

#ifndef OBJECT_H
#define OBJECT_H

struct object {
  unsigned int VAO;
  unsigned int VBO;
  unsigned int EBO;

  unsigned int* indexArray;
  float* vertexArray;
};

struct object* createObject(float* ver, unsigned int verSize, unsigned int* ind, unsigned int indSize);
void bindObject(struct object* o);
void unbindObject();
void deleteObject(struct object* o);

#endif

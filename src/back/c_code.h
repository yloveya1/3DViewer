#ifndef FUNC_C_CODE_H_
#define FUNC_C_CODE_H_

#ifdef __cplusplus
extern "C" {
#endif

#include <locale.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

typedef struct {
  float* xyz;
  int* index_triangles;
  unsigned int index_v;
  unsigned int index_p;
  float max_size;
} obj;

typedef struct {
  int move_x;
  int move_y;
  int move_z;
  int rotate_x;
  int rotate_y;
  int rotate_z;
  float scale;
  float* xyz;
} obj_current;

#define XI i * 3
#define YI i * 3 + 1
#define ZI i * 3 + 2

float readNumberFl(char** begin);
unsigned int readNumberInt(char** begin);

int numberOfVertices(FILE* fp);
int numberOfPolygons(FILE* fp);

void formingVerticesData(FILE* fp, obj* obj_data);
void formingPolygonsData(FILE* fp, obj* obj_data);

void rotateSimple(unsigned int a, unsigned int b, float* xyz, float turn);
void rotateX(float* xyz, unsigned int index_v, float turn);
void rotateY(float* xyz, unsigned int index_v, float turn);
void rotateZ(float* xyz, unsigned int index_v, float turn);

void moveX(float* xyz, int step_move, unsigned int index_v);
void moveY(float* xyz, int step_move, unsigned int index_v);
void moveZ(float* xyz, int step_move, unsigned int index_v);

void scaleModel(float* xyz, unsigned int index_v, float scale);
void projectionModel(obj obj_data, obj_current* obj_cur);

#ifdef __cplusplus
}
#endif
#endif  //  FUNC_C_CODE_H_

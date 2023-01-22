#include "./c_code.h"

// MOVE

void moveX(float* xyz, int step_move, unsigned int index_v) {
  for (unsigned int i = 0; i < index_v; i++) {
    xyz[XI] += step_move;
  }
}

void moveY(float* xyz, int step_move, unsigned int index_v) {
  for (unsigned int i = 0; i < index_v; i++) {
    xyz[YI] += step_move;
  }
}

void moveZ(float* xyz, int step_move, unsigned int index_v) {
  for (unsigned int i = 0; i < index_v; i++) {
    xyz[ZI] += step_move;
  }
}

// ROTATE
void rotateSimple(unsigned int a, unsigned int b, float* xyz, float turn) {
  float tmp = xyz[a];
  turn *= M_PI / 180;
  xyz[a] *= cos(turn);
  xyz[a] += xyz[b] * sin(turn);
  xyz[b] *= cos(turn);
  xyz[b] -= tmp * sin(turn);
}

void rotateX(float* xyz, unsigned int index_v, float turn) {
  for (unsigned int i = 0; i < index_v; i++) {
    rotateSimple(YI, ZI, xyz, turn);
  }
}

void rotateY(float* xyz, unsigned int index_v, float turn) {
  for (unsigned int i = 0; i < index_v; i++) {
    rotateSimple(XI, ZI, xyz, turn);
  }
}

void rotateZ(float* xyz, unsigned int index_v, float turn) {
  for (unsigned int i = 0; i < index_v; i++) {
    rotateSimple(XI, YI, xyz, turn);
  }
}

// SCALE

void scaleModel(float* xyz, unsigned int index_v, float scale) {
  for (unsigned int i = 0; i < index_v; i++) {
    xyz[XI] *= scale;
    xyz[YI] *= scale;
    xyz[ZI] *= scale;
  }
}

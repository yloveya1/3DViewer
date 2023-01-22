#include "widget.h"

#include <QDir>

Widget::Widget(QWidget *parent) : QOpenGLWidget(parent) {}

Widget::~Widget() { deleteData(); }

void Widget::initializeGL() {
  //    backgroundColor.setRgb(0, 0, 0);  // Реализовать установку цвета из
  //    файла
}

void Widget::paintGL() {
  int w = this->width();
  int h = this->height();
  float aspect = w / (h ? (float)h : 1);
  recalculation();
  // Back color
  glClearColor(backgroundColor.redF(), backgroundColor.greenF(),
               backgroundColor.blueF(), 1.0f);
  glClear(GL_COLOR_BUFFER_BIT);
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();

  float tmp = obj_data.max_size * 1.05;
  glOrtho(-(tmp * aspect), (tmp * aspect), -(tmp), (tmp), -(tmp * 12),
          (tmp * 12));

  if (obj_data.index_p) {
    glEnableClientState(GL_VERTEX_ARRAY);
    // Triangles
    printTriangles();
    // Points
    if (display_method != 0) {  // Not none
      printPoints();
    }
    glDisableClientState(GL_VERTEX_ARRAY);
  }
}

void Widget::recalculation() {
  for (unsigned int i = 0; i < obj_data.index_v * 3; i++)
    obj_cur.xyz[i] = obj_data.xyz[i];

  if (obj_cur.move_x) moveX(obj_cur.xyz, obj_cur.move_x, obj_data.index_v);
  if (obj_cur.move_y) moveY(obj_cur.xyz, obj_cur.move_y, obj_data.index_v);
  if (obj_cur.move_z) moveZ(obj_cur.xyz, obj_cur.move_z, obj_data.index_v);

  if (obj_cur.rotate_x)
    rotateX(obj_cur.xyz, obj_data.index_v, obj_cur.rotate_x);
  if (obj_cur.rotate_y)
    rotateY(obj_cur.xyz, obj_data.index_v, obj_cur.rotate_y);
  if (obj_cur.rotate_z)
    rotateZ(obj_cur.xyz, obj_data.index_v, obj_cur.rotate_z);

  if (obj_cur.scale != 1)
    scaleModel(obj_cur.xyz, obj_data.index_v, obj_cur.scale);
  if (projection) projectionModel(obj_data, &obj_cur);
}

void Widget::printTriangles() {
  glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);  // Полигоны без заливки
  glColor3f(ribsColor.redF(), ribsColor.greenF(), ribsColor.blueF());
  glLineWidth(thicknessRibs);

  if (type_ribs == 1) {
    glEnable(GL_LINE_STIPPLE);
    glLineStipple(2, 0X00FF);
  } else {
    glDisable(GL_LINE_STIPPLE);
  }
  glVertexPointer(3, GL_FLOAT, 0, obj_cur.xyz);
  glDrawElements(GL_TRIANGLES, obj_data.index_p * 3, GL_UNSIGNED_INT,
                 obj_data.index_triangles);
  glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);  // Возвращение заливки полигонам
}

void Widget::printPoints() {
  glColor3f(verticesColor.redF(), verticesColor.greenF(),
            verticesColor.blueF());
  glPointSize(sizeVertices);

  if (display_method == 1) {  //  Circle
    glEnable(GL_POINT_SMOOTH);
  } else if (display_method == 2) {  //  Square
    glDisable(GL_POINT_SMOOTH);
  }
  glDrawArrays(GL_POINTS, 0, obj_data.index_v);
}

void Widget::deleteData() {
  if (obj_cur.xyz) delete[] obj_cur.xyz;

  if (obj_data.xyz) delete[] obj_data.xyz;
  if (obj_data.index_triangles) delete[] obj_data.index_triangles;
  obj_data.index_v = 0;
  obj_data.index_p = 0;
  obj_data.max_size = 0;
}

void Widget::CreateObj(QString file) {
  std::string filename = file.toStdString();
  const char *p = filename.c_str();

  FILE *fp = fopen(p, "r");
  if (fp == NULL) return;

  deleteData();

  // Nunber of Vertices and Polygons
  obj_data.index_v = numberOfVertices(fp);
  obj_data.index_p = numberOfPolygons(fp);

  // Read Vertices
  obj_data.xyz = new float[obj_data.index_v * 3];
  formingVerticesData(fp, &obj_data);

  // Read Polygons
  obj_data.index_triangles = new int[obj_data.index_p * 3];
  formingPolygonsData(fp, &obj_data);
  fclose(fp);

  obj_cur.scale = 1;
  obj_cur.xyz = new float[obj_data.index_v * 3];
}

#ifndef WIDGET_H
#define WIDGET_H

#include <QOpenGLWidget>

#include "../back/c_code.h"

class Widget : public QOpenGLWidget {
  Q_OBJECT
 public:
  obj obj_data = {0};
  obj_current obj_cur = {0};

  QColor backgroundColor = QColor::fromRgb(0, 0, 0);
  QColor ribsColor = QColor::fromRgb(245, 121, 0);
  QColor verticesColor = QColor::fromRgb(245, 121, 0);
  int thicknessRibs = 1;
  int sizeVertices = 1;
  int type_ribs = 0;
  int display_method = 0;
  int projection = 0;

  void CreateObj(QString file);
  void deleteData();

  Widget(QWidget *parent = nullptr);
  ~Widget();

 protected:
  void initializeGL() override;
  void paintGL() override;
  void recalculation();
  void printTriangles();
  void printPoints();
};

#endif  // WIDGET_H

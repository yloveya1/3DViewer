#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QFileDialog>
#include <QMainWindow>
#include <QOpenGLWidget>
#include <QTime>
#include <QTimer>

#include "../QtGifImage-master/src/gifimage/qgifimage.h"
#include "widget.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow {
  Q_OBJECT

 public:
  Widget *OGLWidget;
  QTimer *timer;
  int start_timer, step_timer_temp, step_timer = 1000 / 10;
  int width = 640;
  int height = 480;
  QGifImage *gif;
  std::vector<QImage> images;

  MainWindow(QWidget *parent = nullptr);
  ~MainWindow();

 private slots:
  void on_pushButton_clicked();

  void on_move_x_editingFinished();
  void on_move_y_editingFinished();
  void on_move_z_editingFinished();

  void on_slider_rotate_x_valueChanged(int value);
  void on_slider_rotate_y_valueChanged(int value);
  void on_slider_rotate_z_valueChanged(int value);

  void on_rotate_x_textChanged(const QString &arg1);
  void on_rotate_y_textChanged(const QString &arg1);
  void on_rotate_z_textChanged(const QString &arg1);

  void on_slider_scale_valueChanged(int value);
  void on_scale_textChanged(const QString &arg1);

  void formColor(int value, int *r, int *g, int *b);
  void on_background_color_valueChanged(int value);
  void on_color_ribs_valueChanged(int value);
  void on_color_vertices_valueChanged(int value);

  void on_type_ribs_currentIndexChanged(int index);
  void on_thickness_ribs_valueChanged(int value);
  void on_size_vertices_valueChanged(int value);

  void on_display_method_currentIndexChanged(int index);

  void on_save_file_clicked();
  void on_create_gif_clicked();
  void take_screnn();
  void create_gif();

  void on_projection_currentIndexChanged(int index);
  void save_settings();
  void import_settings();

 private:
  Ui::MainWindow *ui;
};
#endif  // MAINWINDOW_H

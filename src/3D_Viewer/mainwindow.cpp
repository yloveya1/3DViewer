#include "mainwindow.h"

#include <QStandardPaths>

#include "./ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow) {
  ui->setupUi(this);
  OGLWidget = new Widget;
  ui->gridLayout_16->addWidget(OGLWidget, 0, 0);
  import_settings();
  ui->scale->setValidator(new QRegularExpressionValidator(
      QRegularExpression("([0-9]*)(\\.?)([0-9]*)"), this));
  ui->rotate_x->setValidator(new QRegularExpressionValidator(
      QRegularExpression("([0-9]*)(\\.?)([0-9]*)"), this));
  ui->rotate_y->setValidator(new QRegularExpressionValidator(
      QRegularExpression("([0-9]*)(\\.?)([0-9]*)"), this));
  ui->rotate_z->setValidator(new QRegularExpressionValidator(
      QRegularExpression("([0-9]*)(\\.?)([0-9]*)"), this));
  ui->move_x->setValidator(new QRegularExpressionValidator(
      QRegularExpression("(^[-0-9])([0-9]*)(\\.?)([0-9]*)"), this));
  ui->move_y->setValidator(new QRegularExpressionValidator(
      QRegularExpression("(^[-0-9])([0-9]*)(\\.?)([0-9]*)"), this));
  ui->move_z->setValidator(new QRegularExpressionValidator(
      QRegularExpression("(^[-0-9])([0-9]*)(\\.?)([0-9]*)"), this));
}

void MainWindow::import_settings() {
  int ribs_c = 0, vertices_c = 0, background_c = 0;

  QString name = QString("%1/config.cfg")
                     .arg(QStandardPaths::writableLocation(
                         QStandardPaths::DesktopLocation));
  QByteArray ba = name.toLocal8Bit();
  char *path_setting = ba.data();
  FILE *file = fopen(path_setting, "r");
  if (file) {
    int a = fscanf(file, "%d %d %d %d %d %d %d %d", &OGLWidget->projection,
                   &OGLWidget->type_ribs, &ribs_c, &OGLWidget->thicknessRibs,
                   &OGLWidget->display_method, &vertices_c,
                   &OGLWidget->sizeVertices, &background_c);
    ui->projection->setCurrentIndex(OGLWidget->projection);
    ui->type_ribs->setCurrentIndex(OGLWidget->type_ribs);
    ui->color_ribs->setValue(ribs_c);
    ui->thickness_ribs->setValue(OGLWidget->thicknessRibs);
    ui->display_method->setCurrentIndex(OGLWidget->display_method);
    ui->color_vertices->setValue(vertices_c);
    ui->size_vertices->setValue(OGLWidget->sizeVertices);
    ui->background_color->setValue(background_c);
    std::fclose(file);
  }
}

void MainWindow::save_settings() {
  QString name = QString("%1/config.cfg")
                     .arg(QStandardPaths::writableLocation(
                         QStandardPaths::DesktopLocation));
  QByteArray ba = name.toLocal8Bit();
  char *path_setting = ba.data();
  FILE *file = fopen(path_setting, "w");
  if (file) {
    fprintf(file, "%d %d %d %d %d %d %d %d", OGLWidget->projection,
            OGLWidget->type_ribs, ui->color_ribs->value(),
            OGLWidget->thicknessRibs, OGLWidget->display_method,
            ui->color_vertices->value(), OGLWidget->sizeVertices,
            ui->background_color->value());
    fclose(file);
  }
}

MainWindow::~MainWindow() {
  save_settings();
  delete ui;
  delete OGLWidget;
}

void MainWindow::on_pushButton_clicked() {
  QString filename =
      QFileDialog::getOpenFileName(this, "Choose a file", "/", "*.obj");
  if (QString(filename).isNull()) return;
  QString file =
      filename.right(filename.length() - filename.lastIndexOf('/') - 1);

  ui->filename->setText(file);
  ui->about_model->setText("");
  ui->about_model->setText(ui->about_model->text() + "\nName: " + file +
                           "\nNumber of vertices: ");

  OGLWidget->CreateObj(filename);
  ui->about_model->setMinimumWidth(1000);
  ui->about_model->setText(
      ui->about_model->text() + QString::number(OGLWidget->obj_data.index_v) +
      "\nNumber of ribs: " + QString::number(OGLWidget->obj_data.index_p * 3));
  OGLWidget->update();
}

//  move
void MainWindow::on_move_x_editingFinished() {
  OGLWidget->obj_cur.move_x = ui->move_x->text().toInt();
  OGLWidget->update();
}

void MainWindow::on_move_y_editingFinished() {
  OGLWidget->obj_cur.move_y = ui->move_y->text().toInt();
  OGLWidget->update();
}

void MainWindow::on_move_z_editingFinished() {
  OGLWidget->obj_cur.move_z = ui->move_z->text().toInt();
  OGLWidget->update();
}

//  rotate
void MainWindow::on_rotate_x_textChanged(const QString &arg1) {
  OGLWidget->obj_cur.rotate_x = ui->rotate_x->text().toInt();
  OGLWidget->update();

  if (OGLWidget->obj_cur.rotate_x != 360) {
    ui->slider_rotate_x->setValue(OGLWidget->obj_cur.rotate_x % 360);
  } else {
    ui->slider_rotate_x->setValue(OGLWidget->obj_cur.rotate_x);
  }
}

void MainWindow::on_rotate_y_textChanged(const QString &arg1) {
  OGLWidget->obj_cur.rotate_y = ui->rotate_y->text().toInt();
  OGLWidget->update();

  if (OGLWidget->obj_cur.rotate_y != 360) {
    ui->slider_rotate_y->setValue(OGLWidget->obj_cur.rotate_y % 360);
  } else {
    ui->slider_rotate_y->setValue(OGLWidget->obj_cur.rotate_y);
  }
}

void MainWindow::on_rotate_z_textChanged(const QString &arg1) {
  OGLWidget->obj_cur.rotate_z = ui->rotate_z->text().toInt();
  OGLWidget->update();

  if (OGLWidget->obj_cur.rotate_z != 360) {
    ui->slider_rotate_z->setValue(OGLWidget->obj_cur.rotate_z % 360);
  } else {
    ui->slider_rotate_z->setValue(OGLWidget->obj_cur.rotate_z);
  }
}

//  rotate slider
void MainWindow::on_slider_rotate_x_valueChanged(int value) {
  ui->rotate_x->setText(QString::number(value));
}

void MainWindow::on_slider_rotate_y_valueChanged(int value) {
  ui->rotate_y->setText(QString::number(value));
}

void MainWindow::on_slider_rotate_z_valueChanged(int value) {
  ui->rotate_z->setText(QString::number(value));
}

//  scale
void MainWindow::on_slider_scale_valueChanged(int value) {
  if (value >= 0) {
    ui->scale->setText(QString::number(1. + value));
  } else {
    ui->scale->setText(QString::number(1. + value / 10.));
  }
}

void MainWindow::on_scale_textChanged(const QString &arg1) {
  OGLWidget->obj_cur.scale = ui->scale->text().toFloat();
  OGLWidget->update();
}

//  color

// 1. 0-255  0      0        0 -15
// 2. 255    0-255  0        16-31
// 3. 255-0  255    0        32-47
// 4. 0      255    0-255    48-63
// 5. 0      255-0  255      64-79
// 6. 0-255  0      255      80-95
// 7. 255    0-255  255      96-111

void MainWindow::formColor(int value, int *r, int *g, int *b) {
  if (value < 32) {
    *r = value * 8;
  } else if (value < 64) {
    *r = 255;
    *g = (value - 32) * 8;
  } else if (value < 96) {
    *r = 255 - (value - 64) * 8;
    *g = 255;
  } else if (value < 128) {
    *g = 255;
    *b = (value - 96) * 8;
  } else if (value < 160) {
    *g = 255 - (value - 128) * 8;
    *b = 255;
  } else if (value < 192) {
    *r = (value - 160) * 8;
    *b = 255;
  } else if (value < 224) {
    *r = 255;
    *g = (value - 192) * 8;
    *b = 255;
  } else {
    *r = 255;
    *g = 255;
    *b = 255;
  }
}

void MainWindow::on_background_color_valueChanged(int value) {
  int r = 0, g = 0, b = 0;
  formColor(value, &r, &g, &b);
  OGLWidget->backgroundColor.setRgb(r, g, b);
  OGLWidget->update();
}

void MainWindow::on_color_ribs_valueChanged(int value) {
  int r = 0, g = 0, b = 0;
  formColor(value, &r, &g, &b);
  OGLWidget->ribsColor.setRgb(r, g, b);
  OGLWidget->update();
}

void MainWindow::on_color_vertices_valueChanged(int value) {
  int r = 0, g = 0, b = 0;
  formColor(value, &r, &g, &b);
  OGLWidget->verticesColor.setRgb(r, g, b);
  OGLWidget->update();
}

void MainWindow::on_type_ribs_currentIndexChanged(int index) {
  OGLWidget->type_ribs = ui->type_ribs->currentIndex();
  OGLWidget->update();
}

void MainWindow::on_projection_currentIndexChanged(int index) {
  OGLWidget->projection = ui->projection->currentIndex();
  OGLWidget->update();
}

void MainWindow::on_thickness_ribs_valueChanged(int value) {
  OGLWidget->thicknessRibs = value;
  OGLWidget->update();
}

void MainWindow::on_size_vertices_valueChanged(int value) {
  OGLWidget->sizeVertices = value;
  OGLWidget->update();
}

void MainWindow::on_display_method_currentIndexChanged(int index) {
  OGLWidget->display_method = ui->display_method->currentIndex();
  OGLWidget->update();
}

void MainWindow::on_save_file_clicked() {
  QString file = QFileDialog::getSaveFileName(
      this, "Save as...",
      "Screenshot " +
          QDateTime::currentDateTime().toString("dd.MM.yyyy hh-mm-ss"),
      "BMP (*.bmp);; JPEG (*.jpg *.jpeg)");
  if (file.length()) {
    OGLWidget->grabFramebuffer().save(file);
  }
}

void MainWindow::take_screnn() {
  static QTime time(0, 0, 5, 0);

  if (start_timer == step_timer_temp) {
    images.push_back(OGLWidget->grabFramebuffer());
    step_timer_temp += step_timer;
    time = time.addMSecs(-step_timer);
  }

  ui->timer->setText("Time left: " + time.toString("ss.zzz"));
  if (start_timer == 5000) {
    create_gif();
    timer->stop();
    time = time.addSecs(5);
  }
  start_timer += step_timer;
}

void MainWindow::create_gif() {
  gif = new QGifImage;
  gif->setDefaultDelay(step_timer);

  for (QImage img : images) {
    img = img.scaled(width, height, Qt::KeepAspectRatio);
    gif->addFrame(img, step_timer);
  }
  QString file = QFileDialog::getSaveFileName(
      this, "Save as...",
      "Gif " + QDateTime::currentDateTime().toString("dd.MM.yyyy hh-mm-ss"),
      "GIF (*.gif)");
  if (file.length()) {
    gif->save(file);
  }

  images.clear();
  delete gif;
  ui->timer->setText("");
  ui->create_gif->setText("Create GIF");
  ui->create_gif->setStyleSheet(
      "QPushButton {color: white; background-color: rgb(245, 121, 0); "
      "border-radius: 2px;}\n"
      "QPushButton:pressed {background-color: rgb(51, 7, 38);}\n");
}

void MainWindow::on_create_gif_clicked() {
  ui->create_gif->setText("Recorging");

  ui->create_gif->setStyleSheet(
      "QPushButton {color: white; background-color: rgb(108, 97, 103); "
      "border-radius: 2px;}\n"
      "QPushButton:pressed {background-color: rgb(51, 7, 38);}\n");
  timer = new QTimer(this);
  start_timer = 0;

  step_timer_temp = step_timer;
  timer->start(step_timer);
  QObject::connect(timer, SIGNAL(timeout()), this, SLOT(take_screnn()));
}

void projectionModel(obj obj_data, obj_current *obj_cur) {
  for (unsigned int i = 0; i < obj_data.index_v; i++) {
    float tmp = (obj_data.max_size * 5) /
                (obj_data.max_size * 5 +
                 (-obj_cur->xyz[ZI] + obj_data.max_size * obj_cur->scale));
    obj_cur->xyz[XI] = obj_cur->xyz[XI] * tmp;
    obj_cur->xyz[YI] = obj_cur->xyz[YI] * tmp;
  }
}

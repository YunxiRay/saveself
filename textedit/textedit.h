#pragma once

#include <QtWidgets/QMainWindow>
#include <QFileInfo>
#include <QFileSystemModel>

#include "ui_textedit.h"

// forward declaration
class QAction;

class Textedit : public QMainWindow {
  Q_OBJECT

 public:
  Textedit(QWidget *parent = Q_NULLPTR);
  ~Textedit();

  // File operations
  void openFile();
  void openFile(const QModelIndex &index);
  void openFile(QString path);
  void openDir();
  void saveFile();
  void newFile();

 private:
  Ui::TexteditClass ui;
  QString path;
  QFileInfo info;
  QFileSystemModel modelDir;

  // check if file path is default
  bool isFileDefault;
};

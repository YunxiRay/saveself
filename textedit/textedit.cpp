#include <QAction>
#include <QtGui/QKeySequence>
#include <QMessageBox>
#include <QFileDialog>
#include <QTextStream>
#include "textedit.h"

Textedit::Textedit(QWidget *parent) : QMainWindow(parent) {
  ui.setupUi(this);

  // connect signal and slot
  connect(ui.actionOpenFile, &QAction::triggered, this,
          static_cast<void (Textedit::*)()>(&Textedit::openFile));
  connect(ui.actionSaveFile, &QAction::triggered, this, &Textedit::saveFile);
  connect(ui.actionNewFile, &QAction::triggered, this, &Textedit::newFile);
  connect(ui.actionOpenDir, &QAction::triggered, this, &Textedit::openDir);
  connect(ui.treeViewDir, &QTreeView::doubleClicked, this,
          static_cast<void (Textedit::*)(const QModelIndex &)>(&Textedit::openFile));

  // var init
  this->path = "Untitled.txt";
  this->info = QFileInfo(path);
  this->isFileDefault = true;
  // Dir tree
  modelDir.setRootPath(QDir::homePath());
  ui.treeViewDir->setModel(&modelDir);
  ui.treeViewDir->setRootIndex(modelDir.index(QDir::homePath()));
  ui.treeViewDir->setColumnHidden(1, true);
  ui.treeViewDir->setColumnHidden(2, true);
  ui.treeViewDir->setColumnHidden(3, true);
  

  // set window
  this->setWindowTitle(this->info.fileName());
 }

Textedit::~Textedit() {}

void Textedit::openFile() { 
	QString path =
      QFileDialog::getOpenFileName(this, tr("Open file"), ".", tr("Text files(*.txt)"));

	if (!path.isEmpty()) {
          QFile file(path);
          if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
              // Warning: cannot open file
            QMessageBox::warning(this, tr("Read file"),
                                 tr("Cannot open file: \n%1").arg(path));
            return;
          }

          this->path = path;
          this->info = QFileInfo(path);
          this->setWindowTitle(this->info.fileName());
          // Dir tree
          modelDir.setRootPath(info.dir().absolutePath());
          ui.treeViewDir->setRootIndex(
              modelDir.index(info.dir().absolutePath()));

          this->isFileDefault = false;
          QTextStream in(&file);
          ui.textEdit->setText(in.readAll());
          file.close();
    } else {
          QMessageBox::warning(this, tr("Path"),
                               tr("You didn't select any file. "));
    }
}

void Textedit::openFile(const QModelIndex &index) {
  if (!index.isValid()) {
    QMessageBox::warning(this, tr("Open file"), tr("Error: invalid path. "));
    return;
  }
  if (modelDir.fileInfo(index).isFile()) {
    this->openFile(modelDir.fileInfo(index).absoluteFilePath());
  }
}

void Textedit::openFile(QString path) {
  if (!path.isEmpty()) {
    QFile file(path);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
      // Warning: cannot open file
      QMessageBox::warning(this, tr("Read file"),
                           tr("Cannot open file: \n%1").arg(path));
      return;
    }

    this->path = path;
    this->info = QFileInfo(path);
    this->setWindowTitle(this->info.fileName());
    // Dir tree
    modelDir.setRootPath(info.dir().absolutePath());
    ui.treeViewDir->setRootIndex(modelDir.index(info.dir().absolutePath()));

    this->isFileDefault = false;
    QTextStream in(&file);
    ui.textEdit->setText(in.readAll());
    file.close();
  } else {
    QMessageBox::warning(this, tr("Path"), tr("You didn't select any file. "));
  }
}

void Textedit::saveFile() {
  if (this->isFileDefault) {
    QString path = QFileDialog::getSaveFileName(this, tr("Select file"), ".",
                                                tr("Text files(*.txt)"));

    if (!path.isEmpty()) {
      QFile file(path);
      file.open(QIODevice::WriteOnly | QIODevice::Text);
      QTextStream out(&file);
      out << ui.textEdit->toPlainText();
      file.close();
    } else {
      QMessageBox::warning(this, tr("Path"),
                           tr("You didn't select any file. "));
    }
  } else {
    QFile file(this->path);
    file.open(QIODevice::WriteOnly | QIODevice::Text);
    QTextStream out(&file);
    out << ui.textEdit->toPlainText();
    file.close();
  }
}
  

void Textedit::newFile() {
  QString path = QFileDialog::getSaveFileName(this, tr("Create new file"), ".",
                                              tr("Text files(*.txt)"));
  if (!path.isEmpty()) {
    this->path = path;
    this->info = QFileInfo(path);
    this->setWindowTitle(this->info.fileName());
    this->isFileDefault = false;

    // empty textEdit
    ui.textEdit->setText(NULL);
  }
}

void Textedit::openDir() {
  QString dir =
      QFileDialog::getExistingDirectory(this, tr("Open Directory"), ".");
  if (!dir.isEmpty()) {
    modelDir.setRootPath(dir);
    ui.treeViewDir->setRootIndex(modelDir.index(dir));
  } else {
    QMessageBox::warning(this, tr("Open directory"),
                         tr("Can not open this directory: \n%1").arg(dir));
  }
}

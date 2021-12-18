#include "textedit.h"
#include <QtWidgets/QApplication>
#include <QTranslator>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    QTranslator translator;
    translator.load("textedit_zh.qm");
    a.installTranslator(&translator);
    Textedit w;
    w.show();
    return a.exec();
}

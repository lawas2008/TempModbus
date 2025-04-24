#include "tempwdiget.h"

#include <QApplication>
#include <QLocale>
#include <QTranslator>
#include <QVector>
#include <QMetaType>


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    QTranslator translator;
    const QStringList uiLanguages = QLocale::system().uiLanguages();
    for (const QString &locale : uiLanguages) {
        const QString baseName = "TempModbus_" + QLocale(locale).name();
        if (translator.load(":/i18n/" + baseName)) {
            a.installTranslator(&translator);
            break;
        }
    }
    qRegisterMetaType<QVector<uint16_t>>("QVector<uint16_t>");

    TempWdiget widget;
    widget.resize(1024,580);
    widget.setWindowTitle("温湿度工具");
    widget.show();
    return a.exec();
}

#include "TrinityIDE.h"
#include <QtWidgets/QApplication>
#include "qfile.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QFile file("c:/trinity/themes/spybot.qss");
    file.open(QFile::ReadOnly);
    QString styleSheet = QLatin1String(file.readAll());
    
    qApp->setStyleSheet(styleSheet);
   
    TrinityIDE w;

    //w.setStyleSheet(styleSheet);
   // qApp->setStyleSheet(styleSheet);

    w.show();
    //w.setStyleSheet(styleSheet);
 
    return a.exec();
}

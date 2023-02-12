#include "TrinityIDE.h"
#include <QtWidgets/QApplication>
#include "qfile.h"
#include "qdrag.h"
#include <mono/jit/jit.h>
#include <mono/metadata/assembly.h>

int main(int argc, char *argv[])
{
    printf("Mono Test\n");
    qDebug("Mono Test\n");

    MonoDomain* domain = mono_jit_init("MyDomain");
    if (!domain) {
        // Error handling
        qDebug("Failed to create domain.\n");
        return 2;
    }
    qDebug("Created domain.\n");


    while (true);
    return 1;
    QApplication a(argc, argv);
    QFile file("c:/trinity/themes/spybot.qss");
    file.open(QFile::ReadOnly);
    QString styleSheet = QLatin1String(file.readAll());
    
    qApp->setStyleSheet(styleSheet);
   
    TrinityIDE w;

    //DragSourceWidget* dragSourceWidget = new DragSourceWidget(&window);
    //DropTargetWidget* dropTargetWidget = new DropTargetWidget(&window);


    //w.setStyleSheet(styleSheet);
   // qApp->setStyleSheet(styleSheet);

    w.show();
    //w.setStyleSheet(styleSheet);
 
    return a.exec();
}

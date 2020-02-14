#include "mainwindow.h"
#include <QApplication>
#include"meter.h"
#include <speedplot.h>
#include <wheelplot.h>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;

    QPalette pal = w.palette();
    pal.setColor(QPalette::Window, Qt::black);
    w.setPalette(pal);

    SpeedPlot s(&w);
    WheelPlot wh(&w);

    Meter m(&w);
    Meter m2(&w);
    QVector<int> vector;
    for(int i =0;i<16;i++)
    {
        vector.append(10+i*10);
    }
    for(int i =14;i>=0;i--)
    {
        vector.append(10+i*10);
    }
    m.setPostion(0,500);
    m.setVector(vector);
    m.setType("Speed");

    m2.setPostion(400,500);
    m2.setVector(vector);
    m2.setType("RPM");

    QQuickWidget *view = new QQuickWidget(&w);
    view->setSource(QUrl::fromLocalFile(":/main.qml"));
    view->setGeometry(1000, 200, view->width(), view->height());

    Pressure p1(&w);
    p1.setGeometry(1600, 100, 250, 230);
    Temperature t1(&w);
    t1.setGeometry(1700, 500, 60, 280);
    w.showMaximized();

    return a.exec();
}

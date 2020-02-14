#ifndef SPEEDPLOT_H
#define SPEEDPLOT_H

#include <QObject>
#include <QWidget>
#include <qcustomplot.h>
#include <QTimer>

class SpeedPlot : public QWidget
{
    Q_OBJECT
public:
    explicit SpeedPlot(QWidget *parent = nullptr);

    void setupRealtimeDataDemo(QCustomPlot *customPlot);
    void customizePlot(QCustomPlot *customPlot);

private slots:
    void realtimeDataSlot();

private:
    QCustomPlot *customPlot;
    QString demoName;
    QTimer dataTimer;
};

#endif // SPEEDPLOT_H

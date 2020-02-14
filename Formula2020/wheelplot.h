#ifndef WHEELPLOT_H
#define WHEELPLOT_H

#include <QObject>
#include <QWidget>
#include <QTimer>
#include <qcustomplot.h>

class WheelPlot : public QWidget
{
    Q_OBJECT
public:
    explicit WheelPlot(QWidget *parent = nullptr);

    void setupRealtimeBarGraph(QCustomPlot *customPlot);

private slots:
    void realtimeBarSlot();

private:
    QCustomPlot *barPlot;
    QString demoName;
    QTimer barTimer;
    QCPBars *fossil;
};

#endif // WHEELPLOT_H

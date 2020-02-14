#include "wheelplot.h"

WheelPlot::WheelPlot(QWidget *parent) : QWidget(parent)
{
    barPlot = new QCustomPlot(this);
    setGeometry(600, 20, 400, 300);
    barPlot->setGeometry(0, 0, 400, 300);
    setupRealtimeBarGraph(barPlot);
}

void WheelPlot::setupRealtimeBarGraph(QCustomPlot *customPlot)
{
    // set dark background gradient:
    QLinearGradient gradient(0, 0, 0, 400);
    gradient.setColorAt(0, QColor(90, 90, 90));
    gradient.setColorAt(0.38, QColor(105, 105, 105));
    gradient.setColorAt(1, QColor(70, 70, 70));
    customPlot->setBackground(QBrush(gradient));

    // create empty bar chart objects:
    fossil = new QCPBars(customPlot->xAxis, customPlot->yAxis);

    fossil->setAntialiased(false);

    fossil->setStackingGap(1);
    // set names and colors:
    fossil->setName("Steering Angles");
    fossil->setPen(QPen(QColor(111, 9, 176).lighter(170)));
    fossil->setBrush(QColor(111, 9, 176));



    // prepare x axis with country labels:
    QVector<double> ticks;
    QVector<QString> labels;
    ticks << 1 << 2 << 3 << 4;
    labels << "Wheel 1" << "Wheel 2" << "Wheel 3" << "Wheel 4";
    QSharedPointer<QCPAxisTickerText> textTicker(new QCPAxisTickerText);
    textTicker->addTicks(ticks, labels);
    customPlot->xAxis->setTicker(textTicker);
    customPlot->xAxis->setTickLabelRotation(60);
    customPlot->xAxis->setSubTicks(false);
    customPlot->xAxis->setTickLength(0, 4);
    customPlot->xAxis->setRange(0, 8);
    customPlot->xAxis->setBasePen(QPen(Qt::white));
    customPlot->xAxis->setTickPen(QPen(Qt::white));
    customPlot->xAxis->grid()->setVisible(true);
    customPlot->xAxis->grid()->setPen(QPen(QColor(130, 130, 130), 0, Qt::DotLine));
    customPlot->xAxis->setTickLabelColor(Qt::white);
    customPlot->xAxis->setLabelColor(Qt::white);

    // prepare y axis:
    customPlot->yAxis->setRange(0, 90);
    customPlot->yAxis->setPadding(5); // a bit more space to the left border
    customPlot->yAxis->setLabel("Steering Angle");
    customPlot->yAxis->setBasePen(QPen(Qt::white));
    customPlot->yAxis->setTickPen(QPen(Qt::white));
    customPlot->yAxis->setSubTickPen(QPen(Qt::white));
    customPlot->yAxis->grid()->setSubGridVisible(true);
    customPlot->yAxis->setTickLabelColor(Qt::white);
    customPlot->yAxis->setLabelColor(Qt::white);
    customPlot->yAxis->grid()->setPen(QPen(QColor(130, 130, 130), 0, Qt::SolidLine));
    customPlot->yAxis->grid()->setSubGridPen(QPen(QColor(130, 130, 130), 0, Qt::DotLine));

    // Add data:
    QVector<double> fossilData;
    fossilData  << qrand()%80 << qrand()%80 << qrand()%80 << qrand()%80;
    //fossilData  << 0.86*10.5 << 0.83*5.5 << 0.84*5.5 << 0.52*5.8;
    fossil->setData(ticks, fossilData);

    // setup legend:
    customPlot->legend->setVisible(true);
    customPlot->axisRect()->insetLayout()->setInsetAlignment(0, Qt::AlignTop|Qt::AlignHCenter);
    customPlot->legend->setBrush(QColor(255, 255, 255, 100));
    customPlot->legend->setBorderPen(Qt::NoPen);
    QFont legendFont = font();
    legendFont.setPointSize(10);
    customPlot->legend->setFont(legendFont);
    customPlot->setInteractions(QCP::iRangeDrag | QCP::iRangeZoom);

    // setup a timer that repeatedly calls MainWindow::realtimeDataSlot:
    connect(&barTimer, SIGNAL(timeout()), this, SLOT(realtimeBarSlot()));
    barTimer.start(500); // Interval 0 means to refresh as fast as possible
}

void WheelPlot::realtimeBarSlot()
{
    QVector<double> ticks;
    QVector<QString> labels;
    ticks << 1 << 2 << 3 << 4;

    // Add data:
    QVector<double> fossilData;
    fossilData  << qrand()%80 << qrand()%80 << qrand()%80 << qrand()%80;
    //fossilData  << 0.86*10.5 << 0.83*5.5 << 0.84*5.5 << 0.52*5.8;
    fossil->setData(ticks, fossilData);

    barPlot->replot();
}

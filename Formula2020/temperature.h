#ifndef TEMPERATURE_H
#define TEMPERATURE_H

#include <QObject>
#include <QWidget>
#include <QLabel>
#include <QTimer>
#include <QPainter>
#include <QPaintEvent>
#include <QDebug>
#include <QPropertyAnimation>

class Temperature : public QWidget
{
    Q_OBJECT
    Q_PROPERTY(qreal temperature READ temperature WRITE setTemperature NOTIFY temperatureChanged)
    Q_PROPERTY(qreal height READ height WRITE setHeight NOTIFY heightChanged)
public:
    explicit Temperature(QWidget *parent = nullptr);
    void paintEvent(QPaintEvent *);
    void timerEvent(QTimerEvent *);

    qreal temperature() const;
    void setTemperature(qreal temperature);
    qreal height() const;
    void setHeight(qreal height);

private:
    QLabel *temp;
    QLabel *lblTemp;
    QTimer *t;
    int timer_id;
    QPropertyAnimation temp_animation;
    QPropertyAnimation height_animation;
    qreal t_temp = 980;
    qreal maxValue = 60;
    qreal h_height = 10;
    qreal currentTemp = 0;
    qreal newTemp = 0;
    qreal maxTemp = 100;
    qreal currentHeight = 10;
    qreal newHeight = 0;
    qreal maxHeight = 920;

signals:
    void temperatureChanged();
    void heightChanged();

private slots:
    void updateTemperature();
};

#endif // TEMPERATURE_H

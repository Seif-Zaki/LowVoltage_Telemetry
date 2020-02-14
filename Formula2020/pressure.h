#ifndef PRESSURE_H
#define PRESSURE_H

#include <QObject>
#include <QWidget>
#include <QLabel>
#include <QTimer>
#include <QPainter>
#include <QPaintEvent>
#include <QPropertyAnimation>
#include <QTimerEvent>
#include <QDebug>

class Pressure : public QWidget
{
    Q_OBJECT
    Q_PROPERTY(qreal rotation READ rotation WRITE setRotation NOTIFY rotationChanged)
public:
    explicit Pressure(QWidget *parent = nullptr);
    void paintEvent(QPaintEvent *);
    void timerEvent(QTimerEvent *);

    qreal rotation() const;
    void setRotation(qreal rotation);

private:
    QLabel *pressure;
    QLabel *lblPress;
    QTimer *t;
    int timer_id;
    QPropertyAnimation rot_animation;
    qreal r_rotation = -135;
    qreal maxValue = 135;
    qreal currentPressure = 0;
    qreal newPressure = 0;
    qreal maxPressure = 160;

signals:
    void rotationChanged();
private slots:
    void updateValue();
};

#endif // PRESSURE_H

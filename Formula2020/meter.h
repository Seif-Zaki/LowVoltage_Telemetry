#ifndef METER_H
#define METER_H

#include <QObject>
#include<QPainter>
#include<QBrush>
#include<QPropertyAnimation>
#include<QPen>
#include<QTimerEvent>
#include<QVector>
#include<QDebug>
#include<QPaintEvent>
#include<QWidget>
class Meter : public QWidget
{
    Q_OBJECT
    Q_PROPERTY(qreal value READ value WRITE setValue NOTIFY valueChanged)
    Q_PROPERTY(QColor color READ getColor WRITE setColor NOTIFY colorChanged)
public:
    explicit Meter(QWidget *parent = nullptr);
    qreal value() const;
    void setValue(qreal value);

    QColor getColor() const ;
    void setColor(QColor color);

    void setVector(QVector<int>speedVector);
    void setType(QString type);
    void setPostion(qreal x,qreal y);


signals:
    void valueChanged();
    void colorChanged();

protected:
    void timerEvent(QTimerEvent *) Q_DECL_OVERRIDE;
    void paintEvent(QPaintEvent *) Q_DECL_OVERRIDE;

private:
    int m_valueTimerId;

    qreal m_value;
    QPropertyAnimation m_animation;

    QColor arcColor;
    QPropertyAnimation c_animation;


    int i;
    QVector<int> vector;
    QString meterUnit;
    QString meterTitle;
    qreal spanfactor;
    qreal maxValue;
    QString meter_type;


};

#endif // METER_H

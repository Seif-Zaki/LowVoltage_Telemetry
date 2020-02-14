#include "meter.h"
Meter::Meter(QWidget *parent) : QWidget(parent)
{
    m_valueTimerId = startTimer(1000);
    m_value = 0;
    arcColor = QString("#008710");
    i = 0;
    m_animation.setTargetObject(this);
    m_animation.setPropertyName("value");
    c_animation.setTargetObject(this);
    c_animation.setPropertyName("color");
}

qreal Meter::value() const
{
     return m_value;
}

void Meter::setValue(qreal value)
{
    if (qFuzzyCompare(value, m_value))
        return;

    m_value = value;
    update();
    emit valueChanged();

}
QColor Meter::getColor() const
{
    return arcColor;
}

void Meter::setColor(QColor color)
{
    if (color == arcColor)
        return;

    arcColor = color;
    update();
    emit colorChanged();

}

void Meter::setVector(QVector<int> speedVector)
{
    vector.append(speedVector);
}

void Meter::setType(QString type)
{
    if(type == "RPM")
    {
        meterUnit = "rpm";
        meterTitle = "RPM (*1000)";
        spanfactor = 1.5;
        maxValue = 160;
        meter_type = type;
    }
    else if(type == "Speed")
    {
        meterUnit = "km/h";
        meterTitle = "Speed meter";
        spanfactor = 1.72;
        maxValue = 140;
        meter_type =type;
    }
}

void Meter::setPostion(qreal x, qreal y)
{
    this->setGeometry(x,y,500,300);
}



void Meter::timerEvent(QTimerEvent *event)
{
        if (event->timerId() == m_valueTimerId) {

            qreal newValue;
            if(i>(vector.length()-1))
            {
               //i=0;
              return;
            }
            else{
                if(vector[i]>m_value){
                    newValue = m_value + (vector[i] - m_value);
                }
                else{
                    newValue = m_value -(m_value - vector[i]);
                }

            }
            if (newValue > maxValue) newValue = maxValue;
            if (newValue < 0) newValue = 0;
            if (m_animation.state() == QPropertyAnimation::Running)
                m_animation.stop();
            if (c_animation.state() == QPropertyAnimation::Running)
                c_animation.stop();
            m_animation.setStartValue(m_value);
            m_animation.setEndValue(newValue);
            m_animation.start();

            if(meter_type == "Speed")
            {
                if(newValue >= 120)
                {
                    c_animation.setStartValue(arcColor);
                    c_animation.setEndValue(QColor(QString("#F82019")));
                    c_animation.start();

                }
                else if(newValue >= 90)
                {
                    c_animation.setStartValue(arcColor);
                    c_animation.setEndValue(QColor(QString("#E27930")));
                    c_animation.start();
                }
                else
                {
                    arcColor = QString("#008710");
                }

            }
            else if(meter_type == "RPM")
            {
                if(newValue >= 140)
                {
                    c_animation.setStartValue(arcColor);
                    c_animation.setEndValue(QColor(QString("#F82019")));
                    c_animation.start();

                }
                else if(newValue >= 100)
                {
                    c_animation.setStartValue(arcColor);
                    c_animation.setEndValue(QColor(QString("#E27930")));
                    c_animation.start();
                }
                else
                {
                    c_animation.setStartValue(arcColor);
                    c_animation.setEndValue(QColor(QString("#008710")));
                    c_animation.start();
                }
            }
            i++;
        }
}

void Meter::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);
    QPen pen;
    QBrush brush (QColor(QString("#252424")),Qt::SolidPattern);

    QRect rect (0,0,500,300);
    painter.drawRect(rect);
    painter.fillRect(rect,brush);


    pen.setColor(QColor(QString("#008710")));
    pen.setWidth(5);
    painter.setPen(pen);
    painter.drawArc(QRect(150,80,200,200),30*16,190*16);

    pen.setColor(QColor(QString("#E27930")));
    painter.setPen(pen);
    painter.drawArc(QRect(150,80,200,200),-10*16,60*16);

    pen.setColor(QColor(QString("#F82019")));
    painter.setPen(pen);
    painter.drawArc(QRect(150,80,200,200),-40*16,30*16);

    pen.setColor(QColor(QString("#2C2B2B")));
    pen.setWidth(45);
    painter.setPen(pen);
    painter.drawArc(QRect(175,105,150,150),-30*16,240*16);

    pen.setColor(arcColor);
    pen.setWidth(40);
    painter.setPen(pen);
    painter.drawArc(QRect(176,106,147,147),-150*16,-(m_value*spanfactor)*16);


    QFont font = painter.font();
    font.setPixelSize(20);
    painter.setFont(font);
    pen.setColor(QColor(QString("white")));
    painter.setPen(pen);
    painter.drawText(QRect(195,30,150,150),QString(meterTitle));
    painter.drawText(QRect(205,240,40,40),QString::number(m_value));
    painter.drawText(QRect(245,240,100,100),QString(meterUnit));

}

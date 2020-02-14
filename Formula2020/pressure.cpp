#include "pressure.h"

Pressure::Pressure(QWidget *parent) : QWidget(parent)
{
    pressure = new QLabel(this);
    lblPress = new QLabel(this);
    lblPress->setText("0 PSI");
    lblPress->setGeometry(100, 200, 80, 30);
    lblPress->setStyleSheet("QLabel { color : red; }");
    QFont font = lblPress->font();
    font.setPointSize(10);
    font.setBold(true);
    lblPress->setFont(font);
    rot_animation.setTargetObject(this);
    rot_animation.setPropertyName("rotation");
    t = new QTimer;
    t->start(2000);
    timer_id = startTimer(1000);
    connect(t, SIGNAL(timeout()), this, SLOT(updateValue()));
}

qreal Pressure::rotation() const
{
     return r_rotation;
}

void Pressure::setRotation(qreal rotation)
{
    if (qFuzzyCompare(r_rotation, rotation))
        return;

    r_rotation = rotation;
    update();
    emit rotationChanged();

}

void Pressure::paintEvent(QPaintEvent *)
{
    QPixmap pm(":/pressure.png");
    QPainter p(&pm);
    p.setRenderHint(QPainter::Antialiasing);
    QPen pen(Qt::red, 1, Qt::SolidLine, Qt::SquareCap, Qt::MiterJoin);
    p.setPen(pen);
    p.setBrush(Qt::red);
    QPolygon poly;
    poly << QPoint(126, 60)
         << QPoint(131, 130)
         << QPoint(126, 140) //rotation point
         << QPoint(121, 130)\
         << QPoint(126, 60);
//    p.translate(126, 130);
//    p.rotate(r_rotation);
//    p.translate(-126, -130);
    poly = QTransform().translate(126, 130).rotate(r_rotation).translate(-126, -130).map(poly);
    p.drawPolygon(poly);
    pressure->setPixmap(pm);
    QSize s = pm.size();
    pressure->setGeometry(0, 0, s.width(), s.height());
    pressure->setScaledContents(true);
    update();
}

void Pressure::timerEvent(QTimerEvent *event)
{
        if (event->timerId() == timer_id) {
            qreal newValue = 0;
            newValue = (newPressure * 1.7) - 135;

            if (newPressure > maxPressure)
            {
                r_rotation = maxValue;
            }

            if (rot_animation.state() == QPropertyAnimation::Running)
                rot_animation.stop();
            rot_animation.setStartValue(r_rotation);
            rot_animation.setEndValue(newValue);
            rot_animation.start();
            lblPress->setText(QString::number(newPressure) + " PSI");
        }
}

void Pressure::updateValue()
{
    newPressure = qrand() % 160;
}

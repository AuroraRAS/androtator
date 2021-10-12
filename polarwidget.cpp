#include "polarwidget.h"

PolarWidget::PolarWidget(QWidget *parent) : QChartView(parent)
{
    chart = new QPolarChart();

    angularAxis = new QValueAxis();
    angularAxis->setTickCount(9); // First and last ticks are co-located on 0/360 angle.
    angularAxis->setLabelFormat("%.1f");
    angularAxis->setShadesVisible(true);
    angularAxis->setShadesBrush(QBrush(QColor(249, 249, 255)));
    angularAxis->setRange(angularMin, angularMax);
    chart->addAxis(angularAxis, QPolarChart::PolarOrientationAngular);

    radialAxis = new QValueAxis();
    radialAxis->setTickCount(4);
    radialAxis->setLabelsVisible(false);
    radialAxis->setRange(radialMin, radialMax);
    chart->addAxis(radialAxis, QPolarChart::PolarOrientationRadial);

    crosshair = new QScatterSeries();
    chart->addSeries(crosshair);
    crosshair->setName("ANT");
    crosshair->attachAxis(radialAxis);
    crosshair->attachAxis(angularAxis);

    circle = new QScatterSeries();
    chart->addSeries(circle);
    circle->setName("SATE");
    circle->attachAxis(radialAxis);
    circle->attachAxis(angularAxis);

    chart->legend()->hide();
    this->setChart(chart);
    this->setRenderHint(QPainter::Antialiasing);
}

void PolarWidget::setCrosshairPoint(float yaw, float pitch)
{
    crosshair->clear();    

    if(yaw < angularMin)
        yaw += angularMax - angularMin;
    if(yaw > angularMax)
        yaw -= angularMax - angularMin;
    if(pitch<radialMin)
    {
        pitch = radialMin;
        crosshair->setColor(QColor("red"));
    }
    else
        crosshair->setColor(QColor("blue"));

    if(rotationLock)
    {
        chart->setTransformOriginPoint(this->width()/2, this->height()/2);
        chart->setRotation(yaw * -1);
    }
    crosshair->append(yaw, pitch * -1 + radialMax);
}

void PolarWidget::setCirclePoint(float yaw, float pitch)
{
    circle->clear();

    if(yaw < angularMin)
        yaw += angularMax - angularMin;
    if(yaw > angularMax)
        yaw -= angularMax - angularMin;
    pitch = pitch<radialMin ? radialMin : pitch;

    circle->append(yaw, pitch * -1 + radialMax);
}

void PolarWidget::setRotationUnlock(bool rotationUnlock)
{
    this->rotationLock = !rotationUnlock;

    if(rotationUnlock)
        chart->legend()->show();
    else
        chart->legend()->hide();
}

void PolarWidget::resetRotationAngle()
{
    chart->setTransformOriginPoint(this->width()/2, this->height()/2);
    chart->setRotation(0);
}

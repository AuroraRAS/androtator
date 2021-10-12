#ifndef POLARWIDGET_H
#define POLARWIDGET_H

#include <QWidget>
#include <QtCharts/QChartView>
#include <QtCharts/QPolarChart>
#include <QtCharts/QValueAxis>
#include <QtCharts/QScatterSeries>

class PolarWidget : public QChartView
{
    Q_OBJECT
public:
    explicit PolarWidget(QWidget *parent = nullptr);

private:
    const qreal angularMin = 0;
    const qreal angularMax = 360;
    const qreal radialMin = 0;
    const qreal radialMax = 90;
    bool rotationLock = true;

    QPolarChart *chart;
    QValueAxis *angularAxis;
    QValueAxis *radialAxis;

    QScatterSeries *crosshair;
    QScatterSeries *circle;

signals:

public slots:
    void setCrosshairPoint(float yaw, float pitch);
    void setCirclePoint(float yaw, float pitch);
    void setRotationUnlock(bool rotationUnlock);
    void resetRotationAngle();
};

#endif // POLARWIDGET_H

#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QTimer>
#include <QtNetwork/QTcpServer>
#include <QtNetwork/QTcpSocket>

#include <hamlib/rotator.h>

QT_BEGIN_NAMESPACE
namespace Ui { class Widget; }
QT_END_NAMESPACE

class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = nullptr);
    ~Widget();

private slots:
    void serverNewConnection();
    void clientReadyRead();
    void timeout();

    void on_pushButton_clicked();

private:
    Ui::Widget *ui;
    QTimer *timer;
    QTcpServer *server;
    QTcpSocket *client;
    ROT *rot;        /* handle to rot (instance) */
    int rot_in[2], rot_out[2];
};
#endif // WIDGET_H

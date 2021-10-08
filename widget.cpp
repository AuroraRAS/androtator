#include "widget.h"
#include "./ui_widget.h"

#include <unistd.h>

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);

    pipe(rot_in);
    pipe(rot_out);

    rot_model_t rotModel = ROT_MODEL_ANDROIDSENSOR;
    rot = rot_init(rotModel);

    timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, &Widget::timeout);
    timer->start(20);

    server = new QTcpServer(this);
    connect(server, &QTcpServer::newConnection, this, &Widget::serverNewConnection);
    server->listen(QHostAddress::Any, 4533);

    client = NULL;
}

Widget::~Widget()
{
    delete ui;
}

void Widget::serverNewConnection()
{
    while (server->hasPendingConnections()) {
        if(client != NULL) {
            disconnect(client, &QTcpSocket::readyRead, this, &Widget::clientReadyRead);
            client->close();
            client->deleteLater();
        }

        client = server->nextPendingConnection();
        connect(client, &QTcpSocket::readyRead, this, &Widget::clientReadyRead);
    }
}

void Widget::clientReadyRead()
{
    float az, el;

    QTextStream readText(client->readAll());

    char head = readText.read(1).toLatin1().at(0);
    switch (head) {
    case 'P':{
        readText >> az >> el;
        rot->caps->set_position(rot, az, el);
        client->write("RPRT 0\n");
        break;
    }
    case 'p':
    {
        rot->caps->get_position(rot, &az, &el);
        QString writeText = QString::number(az,'f',2) + "\n" + QString::number(el,'f',2) + "\n";
        client->write(writeText.toLatin1());
        break;
    }
    default:
    {
        client->write("RPRT -1\n");
        break;
    }
    }
}


void Widget::timeout()
{
    struct androidsensor_rot_priv_data
    {
        void *imu;
        azimuth_t target_az;
        elevation_t target_el;
    };

    struct androidsensor_rot_priv_data *priv = (struct androidsensor_rot_priv_data*)rot->state.priv;

    float az, el;
    rot->caps->get_position(rot, &az, &el);

    ui->polarWidget->setCrosshairPoint(az, el);
    ui->polarWidget->setCirclePoint(priv->target_az, priv->target_el);
}

void Widget::on_pushButton_clicked()
{
    server->close();
    server->listen(QHostAddress::Any, ui->lineEdit->text().toUInt());
}

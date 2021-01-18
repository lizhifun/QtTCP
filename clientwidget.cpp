#include "clientwidget.h"
#include "ui_clientwidget.h"


ClientWidget::ClientWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ClientWidget)
{
    ui->setupUi(this);

    tcpSocket = NULL;
    //分配空间 指定父对象
    tcpSocket = new QTcpSocket(this);

    setWindowTitle(QStringLiteral("客户端"));

    connect(tcpSocket,&QTcpSocket::connected,
        [=]()
        {
            ui->tb_read->setText(QStringLiteral("成功与服务端建立连接"));
        }
        );

    connect(tcpSocket,&QTcpSocket::readyRead,
        [=]()
        {
            //获取对方发送的内容
            QByteArray array=tcpSocket->readAll();
            ui->tb_read->append(array);
        }
        );

}

ClientWidget::~ClientWidget()
{
    delete ui;
}

void ClientWidget::on_btn_connect_clicked()
{
    //获取服务器IP和端口
    QString ip = ui->tb_ip->text();
    qint16 port = ui->tb_port->text().toInt();

    tcpSocket->connectToHost(QHostAddress(ip),port);
}

void ClientWidget::on_btn_send_clicked()
{
    //获取编辑框内容
    QString str=ui->tb_write->toPlainText();
    //发射数据
    tcpSocket->write(str.toUtf8().data());
}

void ClientWidget::on_btn_close_clicked()
{
    //主动和对方断开连接
    tcpSocket->disconnectFromHost();
}

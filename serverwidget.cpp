#include "serverwidget.h"
#include "ui_serverwidget.h"


ServerWidget::ServerWidget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::ServerWidget)
{
    ui->setupUi(this);

    tcpServer=NULL;
    tcpSocket=NULL;

    //监听套接字 指定父对象 让其自动回收空间
    tcpServer = new QTcpServer(this);

    tcpServer->listen(QHostAddress::Any,8888);

    setWindowTitle(QStringLiteral("服务端,端口:8888"));

    connect(tcpServer, &QTcpServer::newConnection,
        [=]()
        {
            //取出建立好连接的套接字
            tcpSocket = tcpServer->nextPendingConnection();
            //获取对方的IP和端口
            QString ip = tcpSocket->peerAddress().toString();
            qint16 port = tcpSocket->peerPort();
            QString temp=QStringLiteral("[%1,:%2]:成功连接").arg(ip).arg(port);
            ui->tb_read->setText(temp);

            //收到客户端数据
            connect(tcpSocket,&QTcpSocket::readyRead,
                [=]()
                {
                    QByteArray array=tcpSocket->readAll();
                    ui->tb_read->append(array);
                }
                );
        }
        );


}

ServerWidget::~ServerWidget()
{
    delete ui;
}


void ServerWidget::on_btn_send_clicked()
{
    if(tcpSocket == NULL)
    {
        return;
    }
    //获取编辑区内容
    QString str = ui->tb_write->toPlainText();
    tcpSocket->write(str.toUtf8().data());
}

void ServerWidget::on_btn_close_clicked()
{
    if(tcpSocket ==NULL)
    {
        return;
    }
    //主动和客户端断开连接
    tcpSocket->disconnectFromHost();
    tcpSocket->close();
}

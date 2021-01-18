#ifndef CLIENTWIDGET_H
#define CLIENTWIDGET_H

#include <QWidget>
#include <QTcpSocket>//通信套接字
#include <QHostAddress>

namespace Ui {
class ClientWidget;
}

class ClientWidget : public QWidget
{
    Q_OBJECT

public:
    explicit ClientWidget(QWidget *parent = nullptr);
    ~ClientWidget();

private slots:
    void on_btn_connect_clicked();

    void on_btn_send_clicked();

    void on_btn_close_clicked();

private:
    Ui::ClientWidget *ui;
    QTcpSocket *tcpSocket;
};

#endif // CLIENTWIDGET_H

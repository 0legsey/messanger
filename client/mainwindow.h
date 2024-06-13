#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTcpSocket>
#include "..\privateChatWidget\privatechatwidget.h"
#include <QFile>
#include <QTextStream>

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    enum MsgType{
        Text,
        SetName,
        PrvMsg
    };
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_pushButtonConnect_clicked();

    void on_pushButtonSend_clicked();

    void on_lineEdit_returnPressed();

    void on_pushButtonName_clicked();

    void on_lineEdit_2_returnPressed();

    void on_userBox_currentTextChanged(const QString &arg1);

    void on_pushButtonPrv_clicked();

    void on_prvText_returnPressed();

private:
    Ui::MainWindow *ui;
    QTcpSocket *socket;
    QByteArray Data;
    QString name;
    QList<QString> userList;
    MsgType _type;
    void SendToServer(MsgType type, QString str);
    void SendPrivateMsg(MsgType type, QString sender, QString reciever, QString str);
    void LogToFile(QString filename, QString msg);

public slots:
    void slotReadyRead();

};
#endif // MAINWINDOW_H

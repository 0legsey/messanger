#ifndef SERVER_H
#define SERVER_H
#include <QTcpServer>
#include <QTcpSocket>
#include <QFile>
#include <QTextStream>
#include <QTime>

class Server : public QTcpServer{
    Q_OBJECT

public:
    Server();
    QTcpSocket *socket;
    enum MsgType{
        Text,
        SetName,
        PrvMsg
    };
    QMap <QTcpSocket*, QString> userMap;

private:
    QVector <QTcpSocket*> Sockets;
    QByteArray Data;
    QList<QString> userList;
    MsgType _type;
    int numOfUsers;
    void SendToClient(MsgType type, QString str);
    void SendPrvMsg(MsgType type, QString sender, QString reciever, QString str);
    void logToFile(QString fileName, QString msg);

public slots:
    void incomingConnection(qintptr socketDescriptor);
    void slotReadyRead();
};

#endif // SERVER_H

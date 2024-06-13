#include "server.h"

Server::Server(){
    if (this->listen(QHostAddress::Any, 2323)){
        qDebug() << "start";
        logToFile("server_logs.txt", "start");
        numOfUsers = 0;
    }
    else{
        qDebug() << "failed to start";
    }
    QFile file("client_list.txt");
    file.open(QIODevice::WriteOnly);
    file.close();
}

void Server::incomingConnection(qintptr socketDescriptor){
    socket = new QTcpSocket;
    socket->setSocketDescriptor(socketDescriptor);
    connect(socket, &QTcpSocket::readyRead, this, &Server::slotReadyRead);
    connect(socket, &QTcpSocket::disconnected, socket, QTcpSocket::deleteLater);

    Sockets.push_back(socket);
    qDebug() << "client connected" << socketDescriptor;
    QString logs = QString("%1 - %2").arg("client connected", QString::number(socketDescriptor));
    logToFile("server_logs.txt", logs);
    userMap.insert(socket, "New client");
    _type = SetName;
}

void Server::slotReadyRead(){
    socket = (QTcpSocket*)sender();
    QDataStream in(socket);
    in.setVersion(QDataStream::Qt_6_7);
    if(in.status() == QDataStream::Ok){
        QString str;
        in >> _type;
        switch(_type){
        case Text:{
            qDebug() << "read...";
            in >> str;
            qDebug() << str;
            QString logs = QDateTime::currentDateTime().toString("yyyy-MM-dd HH:mm:ss") + " - " + str;
            logToFile("server_logs.txt", logs);
            SendToClient(_type, str);
            break;
        }
        case SetName:{
            qDebug() << "reading name...";
            in >> str;
            userList.append(str);
            qDebug() << userList.last();
            userMap.insert(this->socket, str);

            logToFile("client_list.txt", str);

            for (auto i = userMap.begin(); i != userMap.end(); i++){
                qDebug() << i.key()->socketDescriptor() << ":" << i.value();
            }
            SendToClient(_type, userList.last());
            break;
        }
        case PrvMsg:{
            qDebug() << "reading private message...";
            QString l_sender, l_reciever;
            in >> l_sender;
            in >> l_reciever;
            in >> str;
            qDebug() << "message from" << l_sender << "to" << l_reciever << "contains:" << str;
            SendPrvMsg(_type, l_sender, l_reciever, str);
        }
        default:{
            break;
        }
        }
    }
    else{
        qDebug() << "failed to read";
    }
}

void Server::SendToClient(MsgType type, QString str){
    Data.clear();
    QDataStream out(&Data, QIODevice::WriteOnly);
    out.setVersion(QDataStream::Qt_6_7);
    out << type << str;
    for (int i = 0; i < Sockets.size(); i++){
        Sockets[i]->write(Data);
    }

}

void Server::SendPrvMsg(MsgType type, QString sender, QString reciever, QString str)
{
    Data.clear();
    QDataStream out(&Data, QIODevice::WriteOnly);
    out.setVersion((QDataStream::Qt_6_7));
    QString fullmsg = QString("%1: %2").arg(sender, str);
    out << type << sender << str;
    QString filename_1 = QString("%1_%2.txt").arg(sender, reciever);
    QString filename_2 = QString("%1_%2.txt").arg(reciever, sender);
    QFile file_1(filename_1);
    QFile file_2(filename_2);
    if (file_1.open(QIODevice::WriteOnly | QIODevice::Append | QIODevice::ExistingOnly | QIODevice::Text) ||
        file_2.open(QIODevice::WriteOnly | QIODevice::Append | QIODevice::ExistingOnly | QIODevice::Text)){
        if (file_1.isOpen()){
            QTextStream stream(&file_1);
            stream << fullmsg << "\n";
            file_1.close();
        }
        else if (file_2.isOpen()){
            QTextStream stream(&file_2);
            stream << fullmsg << "\n";
            file_2.close();
        }
    }
    else{
        if (file_1.open(QIODevice::WriteOnly | QIODevice::Append | QIODevice::Text)){
            QTextStream stream(&file_1);
            stream << fullmsg << "\n";
            file_1.close();
        }
    }
    for (auto cl = userMap.begin(); cl != userMap.end(); cl++){
        if (reciever == cl.value())
            cl.key()->write(Data);
    }
}

void Server::logToFile(QString fileName, QString msg)
{
    QFile file(fileName);
    if (file.open(QIODevice::WriteOnly | QIODevice::Append | QIODevice::Text)){
        QTextStream stream(&file);
        stream << msg << "\n";
        qDebug() << QString("text \"%1\" has been written to file %2").arg(msg, fileName);
        file.close();
    }
}

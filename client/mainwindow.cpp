#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    socket = new QTcpSocket(this);
    connect(socket, &QTcpSocket::readyRead, this, &MainWindow::slotReadyRead);
    connect(socket, &QTcpSocket::disconnected, socket, &QTcpSocket::deleteLater);
    ui->error_label->setVisible(false);

}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_pushButtonConnect_clicked()
{
    socket->connectToHost("127.0.0.1", 2323);
    ui->lineEdit_2->setEnabled(true);
    ui->pushButtonName->setEnabled(true);
    ui->label->setEnabled(true);
    ui->pushButtonConnect->setEnabled(false);
}


void MainWindow::SendToServer(MsgType type, QString str){
    Data.clear();
    QDataStream out(&Data, QIODevice::WriteOnly);
    out.setVersion(QDataStream::Qt_6_7);
    QString fullmsg = QString("%1: %2").arg(this->name, str);
    switch(type){
    case Text:{
        out << type << fullmsg;
        socket->write(Data);
        ui->lineEdit->clear();
        break;
    }
    case SetName:{
        out << type << name;
        socket->write(Data);
        break;
    }
    default:
        break;
    }
}

void MainWindow::SendPrivateMsg(MsgType type, QString sender, QString reciever, QString str)
{
    Data.clear();
    QDataStream out(&Data, QIODevice::WriteOnly);
    out.setVersion(QDataStream::Qt_6_7);
    out << type << sender << reciever << str;
    ui->privateBrowser->append(QString("%1: %2").arg(sender, str));
    socket->write(Data);
}

void MainWindow::LogToFile(QString fileName, QString msg)
{
    QFile file(fileName);
    if (file.open(QIODevice::WriteOnly | QIODevice::Text)){
        QTextStream stream(&file);
        stream << msg << "\n";
        file.close();
    }
}

void MainWindow::slotReadyRead()
{
    QDataStream in(socket);
    in.setVersion(QDataStream::Qt_6_7);
    if(in.status() == QDataStream::Ok){
        in >> _type;
        QString str;
        switch(_type){
        case Text:{
            in >> str;
            qDebug() << str;
            ui->textBrowser->append(str);
            break;
        }
        case SetName:{
            in >> str;
            QFile file("C:\\Users\\Никита\\Documents\\kr2\\build\\Desktop_Qt_6_7_1_MinGW_64_bit-Debug\\client_list.txt");
            if (file.open(QIODevice::ReadOnly | QIODevice::Text)){
                while (!file.atEnd()){
                    QByteArray line = file.readLine();
                    QString l = QString(line);
                    qsizetype to_remove = l.indexOf("\n");
                    l = l.first(to_remove);
                    int flag = 0;
                    for (int i = 0; i < userList.count(); i++){
                        if (l == userList[i] || l == this->name){
                            flag = 1;
                        }
                    }
                    if (flag == 0 && l != this->name){
                        ui->userBox->addItem(l);
                        userList.append(l);
                    }
                }
            }
            file.close();
            break;
        }
        case PrvMsg:{
            QString l_sender;
            in >> l_sender;
            in >> str;
            if (ui->userBox->currentText() == l_sender){
                ui->privateBrowser->append(QString("%1: %2").arg(l_sender, str));
            }
            break;
        }
        default:{
            break;
        }
        }

    }
    else{
        ui->textBrowser->append("failed to read");
    }
}


void MainWindow::on_pushButtonSend_clicked()
{
    _type = Text;
    SendToServer(_type, ui->lineEdit->text());
}


void MainWindow::on_lineEdit_returnPressed()
{
    _type = Text;
    SendToServer(_type, ui->lineEdit->text());
}


void MainWindow::on_pushButtonName_clicked()
{
    QFile file("C:\\Users\\Никита\\Documents\\kr2\\build\\Desktop_Qt_6_7_1_MinGW_64_bit-Debug\\client_list.txt");
    int flag = 0;
    if (file.open(QIODevice::ReadOnly | QIODevice::Text)){
        while (!file.atEnd()){
            QByteArray line = file.readLine();
            if (line == ui->lineEdit_2->text() + "\n"){
                flag = 1;
            }
        }
    }
    file.close();
    if (flag){
        ui->error_label->setVisible(true);
    }
    else{
        name = ui->lineEdit_2->text();
        LogToFile("client_list.txt", name);
        ui->lineEdit_2->setEnabled(false);
        ui->textBrowser->setEnabled(true);
        ui->lineEdit->setEnabled(true);
        ui->pushButtonSend->setEnabled(true);
        ui->pushButtonName->setEnabled(false);
        ui->privateBrowser->setEnabled(true);
        ui->userBox->setEnabled(true);
        ui->error_label->setVisible(false);
        _type = SetName;
        SendToServer(_type, name);
    }
}


void MainWindow::on_lineEdit_2_returnPressed()
{
    QFile file("C:\\Users\\Никита\\Documents\\kr2\\build\\Desktop_Qt_6_7_1_MinGW_64_bit-Debug\\client_list.txt");
    int flag = 0;
    if (file.open(QIODevice::ReadOnly | QIODevice::Text)){
        while (!file.atEnd()){
            QByteArray line = file.readLine();
            if (line == ui->lineEdit_2->text() + "\n"){
                flag = 1;
            }
        }
    }
    file.close();
    if (flag){
        ui->error_label->setVisible(true);
    }
    else{
        name = ui->lineEdit_2->text();
        LogToFile("client_list.txt", name);
        ui->lineEdit_2->setEnabled(false);
        ui->textBrowser->setEnabled(true);
        ui->lineEdit->setEnabled(true);
        ui->pushButtonSend->setEnabled(true);
        ui->pushButtonName->setEnabled(false);
        ui->privateBrowser->setEnabled(true);
        ui->userBox->setEnabled(true);
        ui->error_label->setVisible(false);
        _type = SetName;
        SendToServer(_type, name);
    }
}


void MainWindow::on_userBox_currentTextChanged(const QString &arg1)
{
    ui->privateBrowser->clear();

    if (ui->userBox->currentText() == "None")
        ui->prvText->setEnabled(false);
    else{
        ui->prvText->setEnabled(true);
        ui->pushButtonPrv->setEnabled(true);
        QString filename_1 = QString("C:\\Users\\Никита\\Documents\\kr2\\build\\Desktop_Qt_6_7_1_MinGW_64_bit-Debug\\%1_%2.txt").arg(this->name, ui->userBox->currentText());
        QString filename_2 = QString("C:\\Users\\Никита\\Documents\\kr2\\build\\Desktop_Qt_6_7_1_MinGW_64_bit-Debug\\%1_%2.txt").arg(ui->userBox->currentText(), this->name);
        QFile file_1(filename_1);
        QFile file_2(filename_2);
        if (file_1.open(QIODevice::ReadOnly | QIODevice::Text) ||
            file_2.open(QIODevice::ReadOnly | QIODevice::Text)){
            if (file_1.isOpen()){
                while (!file_1.atEnd()){
                    QByteArray line = file_1.readLine();
                    QString l = QString(line);
                    qsizetype to_remove = l.indexOf("\n");
                    l = l.first(to_remove);
                    ui->privateBrowser->append(l);
                }
            }
            else if (file_2.isOpen()){
                while (!file_2.atEnd()){
                    QByteArray line = file_2.readLine();
                    QString l = QString(line);
                    qsizetype to_remove = l.indexOf("\n");
                    l = l.first(to_remove);
                    ui->privateBrowser->append(l);
                }
            }
        }
    }
}


void MainWindow::on_pushButtonPrv_clicked()
{
    _type = PrvMsg;
    SendPrivateMsg(_type, this->name, ui->userBox->currentText(), ui->prvText->text());
    ui->prvText->clear();
}



void MainWindow::on_prvText_returnPressed()
{
    _type = PrvMsg;
    SendPrivateMsg(_type, this->name, ui->userBox->currentText(), ui->prvText->text());
    ui->prvText->clear();
}


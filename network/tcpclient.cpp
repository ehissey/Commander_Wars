#include <QTcpSocket>

#include "network/rxtask.h"
#include "network/txtask.h"
#include "coreengine/mainapp.h"
#include "network/tcpclient.h"


TCPClient::TCPClient()
    : pRXTask(nullptr),
      pTXTask(nullptr),
      pSocket(nullptr)
{
    this->moveToThread(Mainapp::getInstance()->getNetworkThread());
    isServer = false;
}

TCPClient::~TCPClient()
{
    disconnect();
    disconnectTCP();
    Console::print(tr("Client is closed"), Console::eDEBUG);
}

void TCPClient::connectTCP(QString adress, quint16 port)
{
    // Launch Socket
    pSocket = std::shared_ptr<QTcpSocket>(new QTcpSocket(this));
    pSocket->moveToThread(Mainapp::getInstance()->getNetworkThread());
    QObject::connect(pSocket.get(), &QTcpSocket::disconnected, this, &TCPClient::disconnectTCP, Qt::QueuedConnection);
    QObject::connect(pSocket.get(), QOverload<QAbstractSocket::SocketError>::of(&QAbstractSocket::error), this, &TCPClient::displayError);
    pSocket->connectToHost(adress, port);

    // Start RX-Task
    pRXTask = new RxTask(pSocket.get(), 0, this);
    pRXTask->moveToThread(Mainapp::getInstance()->getNetworkThread());
    QObject::connect(pSocket.get(), &QTcpSocket::readyRead, pRXTask.get(), &RxTask::recieveData);

    // start TX-Task
    pTXTask = new TxTask(pSocket.get(), 0, this);
    pTXTask->moveToThread(Mainapp::getInstance()->getNetworkThread());
    QObject::connect(this, &TCPClient::sig_sendData, pTXTask.get(), &TxTask::send);

    isConnected = true;
    Console::print(tr("Client is running"), Console::eDEBUG);
    emit sigConnected(0);
}

void TCPClient::disconnectTCP()
{
    if (pSocket != nullptr)
    {
        pRXTask = nullptr;
        pTXTask = nullptr;
        pSocket->disconnect();
        pSocket->close();
        pSocket = nullptr;
    }
    emit sigDisconnected(0);
}

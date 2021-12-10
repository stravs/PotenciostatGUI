#include <QFile>
#include <QSerialPortInfo>
#include <qdebug.h>

#include "potenciostat.h"

Potenciostat::Potenciostat(QObject *parent) : QObject(parent)
{
    m_serial = new QSerialPort(this);
    getAvaliablePorts();
    connect(m_serial, &QSerialPort::readyRead, this, &Potenciostat::readData);
    setStatusText("Not connected to serial");
}

Potenciostat::~Potenciostat()
{
    closeSerialPort();
    delete m_serial;
}

void Potenciostat::openSerialPort()
{
    m_serial->setPortName(selectedPort());
    m_serial->setBaudRate(QSerialPort::Baud115200);
    m_serial->setDataBits(QSerialPort::Data8);
    m_serial->setParity(QSerialPort::NoParity);
    m_serial->setStopBits(QSerialPort::OneStop);
    m_serial->setFlowControl(QSerialPort::NoFlowControl);
    if (m_serial->open(QIODevice::ReadWrite)) {
        qDebug() << "Connected";
        setStatusText("Connected to serial");
        setIsConnected(true);
    } else {
        qDebug() << m_serial->errorString();

        setStatusText("Failed to connect to serial: " + m_serial->errorString());
    }
}

void Potenciostat::closeSerialPort()
{
    if (m_serial->isOpen()){
        m_serial->close();
        setIsConnected(false);
        setStatusText("Not connected to serial");
    }
}

void Potenciostat::getAvaliablePorts()
{
    const auto infos = QSerialPortInfo::availablePorts();

    QStringList portNames;
    for (const QSerialPortInfo &info : infos) {
        portNames << info.portName();
    }

    setAvaliblePorts(portNames);
}

void Potenciostat::sendInit()
{
    m_serial->write("I()\n");
}

void Potenciostat::sendStart()
{
    if (!QFile::exists(QString{"%1/%2.csv"}.arg(fileLocation()).arg(fileName()))){
        m_file = new QFile(QString{"%1/%2.csv"}.arg(fileLocation()).arg(fileName()));
        if (!m_file->open(QIODevice::WriteOnly | QIODevice::Append)){
            setStatusText(m_file->errorString());
            return;
        }
        m_serial->write("S()\n");
    } else {
        setStatusText("Datoteka obstaja, izberi drugo ime");
    }

}

void Potenciostat::sendReset()
{
    m_serial->write("R()\n");


}


QString Potenciostat::selectedPort() const
{
    return m_selectedPort;
}

QStringList Potenciostat::avaliblePorts() const
{
    return m_avaliblePorts;
}

void Potenciostat::readData()
{
    const QByteArray data = m_serial->readAll();
    qDebug() << data;



    if (data.contains("s:Done")){
        m_isWritingData = false;
        setIsRunning(false);
        m_file->close();
    }


    if (m_isWritingData) {
        QTextStream out(m_file);
        out << data;
    }

    if (data.contains("r:DONE"))
        m_isWritingData = true;

    if (data.contains("i:DONE")){
        setIsRunning(true);
        setStatusText("Connected to serial");
    }
}

bool Potenciostat::isConnected() const
{
    return m_isConnected;
}

QString Potenciostat::fileName() const
{
    return m_fileName;
}

QString Potenciostat::fileLocation() const
{
    return m_fileLocation;
}

bool Potenciostat::isRunning() const
{
    return m_isRunning;
}

QString Potenciostat::statusText() const
{
    return m_statusText;
}


void Potenciostat::setSelectedPort(QString selectedPort)
{
    if (m_selectedPort == selectedPort)
        return;

    m_selectedPort = selectedPort;
    emit selectedPortChanged(m_selectedPort);
}

void Potenciostat::setAvaliblePorts(QStringList avaliblePorts)
{
    if (m_avaliblePorts == avaliblePorts)
        return;

    m_avaliblePorts = avaliblePorts;
    emit avaliblePortsChanged(m_avaliblePorts);
}

void Potenciostat::setIsConnected(bool isConnected)
{
    if (m_isConnected == isConnected)
        return;

    m_isConnected = isConnected;
    emit isConnectedChanged(m_isConnected);
}

void Potenciostat::setFileName(QString fileName)
{
    if (m_fileName == fileName)
        return;

    m_fileName = fileName;
    emit fileNameChanged(m_fileName);
}

void Potenciostat::setFileLocation(QString fileLocation)
{
    if (m_fileLocation == fileLocation)
        return;

    m_fileLocation = fileLocation;
    emit fileLocationChanged(m_fileLocation);
}

void Potenciostat::setIsRunning(bool isRunning)
{
    if (m_isRunning == isRunning)
        return;

    m_isRunning = isRunning;
    emit isRunningChanged(m_isRunning);
}

void Potenciostat::setStatusText(QString statusText)
{
    if (m_statusText == statusText)
        return;

    m_statusText = statusText;
    emit statusTextChanged(m_statusText);
}

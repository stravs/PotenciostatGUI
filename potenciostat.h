#ifndef POTENCIOSTAT_H
#define POTENCIOSTAT_H

#include <QFile>
#include <QObject>
#include <QSerialPort>
#include <QTextStream>

class Potenciostat : public QObject
{
    Q_OBJECT

    Q_PROPERTY(QString selectedPort READ selectedPort WRITE setSelectedPort NOTIFY selectedPortChanged)
    Q_PROPERTY(QStringList avaliblePorts READ avaliblePorts WRITE setAvaliblePorts NOTIFY avaliblePortsChanged)
    Q_PROPERTY(bool isConnected READ isConnected WRITE setIsConnected NOTIFY isConnectedChanged)
    Q_PROPERTY(bool isRunning READ isRunning WRITE setIsRunning NOTIFY isRunningChanged)
    Q_PROPERTY(QString fileLocation READ fileLocation WRITE setFileLocation NOTIFY fileLocationChanged)
    Q_PROPERTY(QString fileName READ fileName WRITE setFileName NOTIFY fileNameChanged)
    Q_PROPERTY(QString statusText READ statusText WRITE setStatusText NOTIFY statusTextChanged)

public:
    explicit Potenciostat(QObject *parent = nullptr);
    ~Potenciostat();

    Q_INVOKABLE void openSerialPort();
    Q_INVOKABLE void closeSerialPort();
    Q_INVOKABLE void getAvaliablePorts();

    Q_INVOKABLE void sendInit();
    Q_INVOKABLE void sendStart();
    Q_INVOKABLE void sendReset();

    QString selectedPort() const;

    QStringList avaliblePorts() const;

    void readData();

    bool isConnected() const;

    QString fileName() const;

    QString fileLocation() const;

    bool isRunning() const;

    QString statusText() const;

public slots:
    void setSelectedPort(QString selectedPort);

    void setAvaliblePorts(QStringList avaliblePorts);

    void setIsConnected(bool isConnected);

    void setFileName(QString fileName);

    void setFileLocation(QString fileLocation);

    void setIsRunning(bool isRunning);

    void setStatusText(QString statusText);

signals:
    void selectedPortChanged(QString selectedPort);

    void avaliblePortsChanged(QStringList avaliblePorts);

    void isConnectedChanged(bool isConnected);

    void fileNameChanged(QString fileName);

    void fileLocationChanged(QString fileLocation);

    void isRunningChanged(bool isRunning);

    void statusTextChanged(QString statusText);

private:
    QSerialPort *m_serial{nullptr};

    QString m_selectedPort;
    QStringList m_avaliblePorts;
    bool m_isConnected{false};
    bool m_isRunning{false};
    bool m_isWritingData{false};
    QString m_fileName{};
    QString m_fileLocation;
    QFile *m_file{nullptr};
    QString m_statusText;
};

#endif // POTENCIOSTAT_H

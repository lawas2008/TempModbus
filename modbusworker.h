#ifndef MODBUSWORKER_H
#define MODBUSWORKER_H

#include <QObject>
#include <modbus/modbus.h>

class ModbusWorker : public QObject
{
    Q_OBJECT
public:
    explicit ModbusWorker(QObject *parent = nullptr);
    ~ModbusWorker();
public slots:
    void connectModbus(QString com,int rate,int addr = 1);
    void disconnectModbus();
    void readRegister(int addr,int count);
    void writeRegister(int addr,uint16_t value);
signals:
    void connectStatusChanged(bool connected);
    void readFinished(const QVector<uint16_t> &data);
    void writeFinished(bool success);
    void error(const QString &msg);
private:
    modbus_t *modbus = nullptr;
    bool isconnected = false;

};

#endif // MODBUSWORKER_H

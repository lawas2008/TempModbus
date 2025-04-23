#include "modbusworker.h"
#include <QDebug>

/**
 * @brief calculateCRC16 crc16校验
 * @param data
 * @return
 */
quint16 calculateCRC16(const QByteArray &data) {
    quint16 crc = 0xFFFF; // 初始值
    for(int i = 0; i < data.size(); ++i) {
        crc ^= (quint8)data[i]; // XOR byte into least sig. byte of crc

        for(int j = 0; j < 8; ++j) { // Loop over each bit
            if((crc & 0x0001) != 0) { // If the LSB is set
                crc >>= 1; // Shift right and XOR 0xA001
                crc ^= 0xA001;
            } else { // Else LSB is not set
                crc >>= 1; // Just shift right
            }
        }
    }
    return crc;
}

ModbusWorker::ModbusWorker(QObject *parent): QObject{parent}{

}

ModbusWorker::~ModbusWorker(){
    disconnectModbus();
}

/**
 * @brief ModbusWorker::connectModbus
 * 连接
 */
void ModbusWorker::connectModbus(QString com,int rate,int addr){
    qDebug() << "ModbusWorker connectModbus com:" << com << "rate:" << rate;
    if(isconnected){
        return;
    }
    if(modbus){
        modbus_close(modbus);
        modbus_free(modbus);
        modbus = nullptr;
    }
    //初始化modbus RTU
    QByteArray ba = com.toLatin1();
    modbus = modbus_new_rtu(ba.data(),rate,'N',8,1);
    if(!modbus){
        emit error("Failed to create Modbus context");
        return;
    }
    //启用调试功能
    modbus_set_debug(modbus, TRUE);
    modbus_set_slave(modbus,addr);
    modbus_set_response_timeout(modbus,1000,1000);
    if(modbus_connect(modbus) == -1){
        emit error("Connection failed: " + QString(modbus_strerror(errno)));
        modbus_free(modbus);
        modbus = nullptr;
    }else{
        isconnected = true;
        emit connectStatusChanged(true);
        qDebug() << "Modbus Connected!";
    }
}

/**
 * @brief ModbusWorker::disconnectModbus
 * 断开连接
 */
void ModbusWorker::disconnectModbus(){
    qDebug() << "ModbusWorker disconnectModbus!";
    if(modbus){
        modbus_close(modbus);
        modbus_free(modbus);
        modbus = nullptr;
        isconnected = false;
        emit connectStatusChanged(false);
        qDebug() << "Modbus Disconnected!";
    }
}

/**
 * @brief ModbusWorker::readRegister
 *        读寄存器方法
 * @param addr 起始地址
 * @param count 个数
 */
void ModbusWorker::readRegister(int addr, int count)
{
    if(!modbus){
        return;
    }
    qDebug() << "ModbusWorker readRegister addr:" << addr << "count:" << count;
    QVector<uint16_t> buffer(count);
    int rc = modbus_read_registers(modbus, addr, count, buffer.data());
    qDebug() << "ModbusWorker readRegister addr:" << addr << "rc:" << rc;
    if (rc == -1) {
        emit error("Read error: " + QString(modbus_strerror(errno)));
    } else {
        emit readFinished(buffer);
    }
}

/**
 * @brief ModbusWorker::writeRegister
 * 写寄存器方法
 * @param addr 地址
 * @param value 值
 */
void ModbusWorker::writeRegister(int addr, uint16_t value)
{
    if(!modbus){
        return;
    }
    qDebug() << "ModbusWorker writeRegister addr:" << addr << "value:" << value;
    int rc = modbus_write_register(modbus,addr,value);
    emit writeFinished(rc != -1);
}


#include "modbusworker.h"
#include <QDebug>

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

}

/**
 * @brief ModbusWorker::writeRegister
 * 写寄存器方法
 * @param addr 地址
 * @param value 值
 */
void ModbusWorker::writeRegister(int addr, uint16_t value)
{

}


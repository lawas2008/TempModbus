#include "modbusworker.h"
#include <QDebug>
#include <fcntl.h>
#define SERVER_GPIO_INDEX   "PI10"


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

static int custom_rts_rtu_ioctl_on(void)
{
    int fd;
    fd = open("/sys/class/gpio/" SERVER_GPIO_INDEX "/value", O_WRONLY);
    if(fd < 0)
        return 1;

    write(fd, "1", 1);
    close(fd);
    qDebug() << "custom_rts_rtu_ioctl_off 1";
    return 0;
}

static int custom_rts_rtu_ioctl_off(void)
{
    int fd;

    fd = open("/sys/class/gpio/" SERVER_GPIO_INDEX "/value", O_WRONLY);
    if(fd < 0)
        return 1;

    write(fd, "0", 1);
    close(fd);
    qDebug() << "custom_rts_rtu_ioctl_off 0";
    return 0;
}

static void custom_rts_rtu(modbus_t *ctx, int on)
{
    if (on)
    {
        custom_rts_rtu_ioctl_on();
    }
    else
    {
        custom_rts_rtu_ioctl_off();
    }
    //100毫秒延时，保证数据发送完整
    usleep(100000);
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
void ModbusWorker::connectModbus(QString com, int rate, int addr) {
    qDebug() << "ModbusWorker connectModbus com:" << com << "rate:" << rate;

    if (isconnected) {
        return;
    }

    // 清理旧连接
    if (modbus) {
        modbus_close(modbus);
        modbus_free(modbus);
        modbus = nullptr;
    }

    // 初始化上下文
    QByteArray ba = com.toLatin1();
    modbus = modbus_new_rtu(ba.data(), rate, 'N', 8, 1);
    if (!modbus) {
        emit error("Failed to create Modbus context");
        return;
    }

    // 设置从机地址
    modbus_set_slave(modbus, addr);

    // 设置超时（单位：秒 + 微秒）
    modbus_set_response_timeout(modbus, 1, 0);  // 1秒超时

    // 启用调试模式（可选）
    modbus_set_debug(modbus, TRUE);

    // 连接串口（此时设备文件才会被打开）
    if (modbus_connect(modbus) == -1) {
        qDebug() << "Modbus connect failed:" << modbus_strerror(errno);
        modbus_free(modbus);
        modbus = nullptr;
        emit error("Failed to connect");
        return;
    }

    // 设置 RS485 模式
    if (modbus_rtu_set_serial_mode(modbus, MODBUS_RTU_RS485) == -1) {
        qDebug() << "Modbus set_serial_mode failed:" << errno << modbus_strerror(errno);
        modbus_free(modbus);
        modbus = nullptr;
        emit error("Failed to set RS485 mode");
        return;
    }

    if(modbus_rtu_set_custom_rts(modbus, custom_rts_rtu) == -1)
    {
        qDebug() << "Modbus set custom rts fun failed" << errno << modbus_strerror(errno);
        modbus_free(modbus);
        return;
    }

    if(modbus_rtu_set_rts(modbus,MODBUS_RTU_RTS_UP ) == -1)
    {
        qDebug() << "Modbus set rs485 rts up failed" << errno << modbus_strerror(errno);
        modbus_free(modbus);
        return;
    }

    qDebug() << "Modbus Connected!";
    isconnected = true;
    emit connectStatusChanged(true);
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
    qDebug() << "ModbusWorker readRegister addr:" << addr << "count:" << count;

    if(!modbus){
        return;
    }
    QVector<uint16_t> buffer(count);
    int rc = modbus_read_registers(modbus, addr, count, buffer.data());
    qDebug() << "ModbusWorker readRegister addr:" << addr << "rc:" << rc << "count:" << count << "buffer:" << buffer;

    if (rc == -1) {
        // 提供详细的错误信息
 //       emit error("Read error: " + QString("Error code %1: %2").arg(errno).arg(modbus_strerror(errno)));
    } else if (rc < count) {
 //       emit error("Partial read: expected " + QString::number(count) + " registers, got " + QString::number(rc));
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
    int rc = modbus_write_register(modbus,addr,value);
    qDebug() << "ModbusWorker writeRegister addr:" << addr << "value:" << value << "rc: " << rc;

    emit writeFinished(rc != -1);
}

/**
 * @brief ModbusWorker::sendMsgRaw
 * 发送原始数据
 * @param raw_request
 */
void ModbusWorker::sendMsgRaw(uint8_t *raw_request)
{
    if(!modbus){
        return;
    }
    qDebug() << "ModbusWorker sendMsgRaw raw_request.size:" << sizeof(raw_request);
    // 发送原始请求
    int rc = modbus_send_raw_request(modbus, raw_request, 8);
    if (rc == -1) {
        fprintf(stderr, "发送失败: %s\n", modbus_strerror(errno));
        modbus_close(modbus);
        modbus_free(modbus);
        return;
    }

    // 接收响应
    uint8_t response[MODBUS_RTU_MAX_ADU_LENGTH];
    rc = modbus_receive_confirmation(modbus, response);
    if (rc == -1) {
        fprintf(stderr, "接收失败: %s\n", modbus_strerror(errno));
    } else {
        printf("响应数据（HEX）: %d",rc);
        for (int i = 0; i < rc; i++) {
            printf("%02X ", response[i]);
        }
        printf("\n");
    }
}




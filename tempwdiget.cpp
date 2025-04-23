#include "tempwdiget.h"
#include "QHBoxLayout"
#include "QVBoxLayout"
#include "QGroupBox"
#include "QFormLayout"
#include "QSerialPortInfo"
#include "QThread"
#include "QMessageBox"
#include "QApplication"
#include "QDebug"

/**
 * @brief TempWdiget::TempWdiget 主界面
 * @param parent
 */
TempWdiget::TempWdiget(QWidget *parent): QWidget{parent}{

    //温度显示布局
    QVBoxLayout *tempshowLayout = new QVBoxLayout();

    //温湿度
    QHBoxLayout *tempCItemLayout = new QHBoxLayout();

    //温度
    QVBoxLayout *tempItemLayout = new QVBoxLayout();
    QLabel *tempTile = new QLabel("Temp");
    tempTile->setStyleSheet("QLabel { font-size: 20px; }");
    tempLabel = new QLabel("00.0");
    tempLabel->setStyleSheet("QLabel { color: green; font-size: 30px; }");
    tempItemLayout->addWidget(tempTile,0,Qt::AlignCenter);
    tempItemLayout->addWidget(tempLabel,0,Qt::AlignCenter);
    tempItemLayout->addStretch();
    tempCItemLayout->addStretch();
    tempCItemLayout->addLayout(tempItemLayout);

    tempCItemLayout->addSpacing(50);

    //湿度
    QVBoxLayout *coldItemLayout = new QVBoxLayout();
    QLabel *coldTile = new QLabel("Cold");
    coldTile->setStyleSheet("QLabel { font-size: 20px; }");
    coldLabel = new QLabel("00.0");
    coldLabel->setStyleSheet("QLabel { color: blue; font-size: 30px; }");
    coldItemLayout->addWidget(coldTile,0,Qt::AlignCenter);
    coldItemLayout->addWidget(coldLabel,0,Qt::AlignCenter);
    coldItemLayout->addStretch();
    tempCItemLayout->addLayout(coldItemLayout);
    tempCItemLayout->addStretch();

    //添加温湿度
    tempshowLayout->addLayout(tempCItemLayout);

    //参数布局
    QGroupBox *paramGroupBox = new QGroupBox("参数");
    QFormLayout *formLayout = new QFormLayout(paramGroupBox);
    QLabel *versionTitleLabel = new QLabel("固件版本");
    showVersionEt = new QLineEdit();
    QLabel *addrTitleLabel = new QLabel("站号");
    showAddrEt = new QLineEdit();
    QLabel *rateTitleLabel = new QLabel("波特率");
    showRateEt = new QLineEdit();
    formLayout->addRow(versionTitleLabel,showVersionEt);
    formLayout->addRow(addrTitleLabel,showAddrEt);
    formLayout->addRow(rateTitleLabel,showRateEt);

    //控制布局
    QGroupBox *controlGroupBox = new QGroupBox("控制");
    QVBoxLayout *groupVLayout = new QVBoxLayout(controlGroupBox);

    QHBoxLayout *allParamLayout = new QHBoxLayout();
    QLabel *paramTitle = new QLabel("所有参数");
    paramTitle->setFixedWidth(80);
    getParamSingleBtn = new QPushButton("单次");
    getParamCycleBtn = new QPushButton("循环");
    allParamLayout->addWidget(paramTitle);
    allParamLayout->addWidget(getParamSingleBtn);
    allParamLayout->addWidget(getParamCycleBtn);
    groupVLayout->addLayout(allParamLayout);

    QHBoxLayout *tempCLayout = new QHBoxLayout();
    QLabel *tempCTitle = new QLabel("温湿度");
    tempCTitle->setFixedWidth(80);
    getTempCSingleBtn = new QPushButton("单次");
    getTempCCycleBtn = new QPushButton("循环");
    tempCLayout->addWidget(tempCTitle);
    tempCLayout->addWidget(getTempCSingleBtn);
    tempCLayout->addWidget(getTempCCycleBtn);
    groupVLayout->addLayout(tempCLayout);

    QHBoxLayout *tempLayout = new QHBoxLayout();
    QLabel *tempGTitle = new QLabel("温度");
    tempGTitle->setFixedWidth(80);
    getTempSingleBtn = new QPushButton("单次");
    getTempCycleBtn = new QPushButton("循环");
    tempLayout->addWidget(tempGTitle);
    tempLayout->addWidget(getTempSingleBtn);
    tempLayout->addWidget(getTempCycleBtn);
    groupVLayout->addLayout(tempLayout);

    QHBoxLayout *coldLayout = new QHBoxLayout();
    QLabel *coldGTitle = new QLabel("湿度");
    coldGTitle->setFixedWidth(80);
    getColdSingleBtn = new QPushButton("单次");
    getColdeCycleBtn = new QPushButton("循环");
    coldLayout->addWidget(coldGTitle);
    coldLayout->addWidget(getColdSingleBtn);
    coldLayout->addWidget(getColdeCycleBtn);
    groupVLayout->addLayout(coldLayout);

    QHBoxLayout *addrLayout = new QHBoxLayout();
    QLabel *addrGTitle = new QLabel("站号");
    addrGTitle->setFixedWidth(80);
    addrLowEdit = new QLineEdit();
    addrHightEdit = new QLineEdit();
    addrSetBtn = new QPushButton("设置");
    addrLayout->addWidget(addrGTitle);
    addrLayout->addWidget(addrLowEdit);
    addrLayout->addWidget(addrHightEdit);
    addrLayout->addWidget(addrSetBtn);
    groupVLayout->addLayout(addrLayout);

    QHBoxLayout *rateLayout = new QHBoxLayout();
    QLabel *rateTitle = new QLabel("波特率");
    rateTitle->setFixedWidth(80);
    rateSetCombox = new QComboBox();
    rateSetBtn = new QPushButton("设置");
    rateLayout->addWidget(rateTitle);
    rateLayout->addWidget(rateSetCombox);
    rateLayout->addWidget(rateSetBtn);
    groupVLayout->addLayout(rateLayout);

    QHBoxLayout *versionLayout = new QHBoxLayout();
    QLabel *versionTitle = new QLabel("版本");
    versionTitle->setFixedWidth(80);
    getVersionBtn = new QPushButton("读取");
    versionLayout->addWidget(versionTitle);
    versionLayout->addWidget(getVersionBtn);
    groupVLayout->addLayout(versionLayout);

    groupVLayout->addStretch();

    //第一层水平布局居中
    QHBoxLayout *horizontalContainer = new QHBoxLayout();
    horizontalContainer->addLayout(tempshowLayout,4);
    horizontalContainer->addWidget(paramGroupBox,1);
    horizontalContainer->addWidget(controlGroupBox,2);

    //第二层
    QHBoxLayout *comLogLayout = new QHBoxLayout();
    //通信串口布局
    QGroupBox *comGroupBox = new QGroupBox("通信设置");
    QFormLayout *comLayout = new QFormLayout(comGroupBox);
    QLabel *comTitleLabel = new QLabel("端口");
    portCombox = new QComboBox();
    QLabel *comRateTitleLabel = new QLabel("波特率");
    ratesCombox = new QComboBox();
    openSerialBtn = new QPushButton("打开");
    comLayout->addRow(comTitleLabel,portCombox);
    comLayout->addRow(comRateTitleLabel,ratesCombox);
    comLayout->addRow(openSerialBtn);

    comLogLayout->addWidget(comGroupBox);

    QVBoxLayout *logLayout = new QVBoxLayout();
    logListView = new QListView();
    logLayout->addWidget(logListView,1);

    QHBoxLayout *sendLayout = new QHBoxLayout();
    sendCmdEt = new QLineEdit();
    sendCmdBtn = new QPushButton("发送");
    sendLayout->addWidget(sendCmdEt,1);
    sendLayout->addWidget(sendCmdBtn);
    logLayout->addLayout(sendLayout);

    comLogLayout->addLayout(logLayout,1);

    QVBoxLayout *allLayout = new QVBoxLayout();

    allLayout->addLayout(horizontalContainer);
    allLayout->addLayout(comLogLayout);

    setLayout(allLayout);

    initCombox();

    initCom();

    //初始化线程和worker
    modbusThread = new QThread(this);
    worker = new ModbusWorker();
    worker->moveToThread(modbusThread);
    connect(worker,&ModbusWorker::connectStatusChanged,this,&TempWdiget::updateOpenBtnStatus);
    connect(worker,&ModbusWorker::error,this,&TempWdiget::updateError);
    connect(worker,&ModbusWorker::readFinished,this,&TempWdiget::readDataFinish);
    connect(worker,&ModbusWorker::writeFinished,this,&TempWdiget::writeDataFinish);
    connect(modbusThread,&QThread::finished,worker,&QObject::deleteLater);
    modbusThread->start();

    //打开串口事件
    connect(openSerialBtn,&QPushButton::clicked,this,&TempWdiget::openCom);
    //获取温湿度单次
    connect(getTempCSingleBtn,&QPushButton::clicked,this,&TempWdiget::tempColdOne);
    //获取湿度单次
    connect(getColdSingleBtn,&QPushButton::clicked,this,&TempWdiget::coldOne);
    //读取版本号
    connect(getVersionBtn,&QPushButton::clicked,this,&TempWdiget::getVersion);
}

/**
 * @brief TempWdiget::initCombox
 * 初始化combox
 */
void TempWdiget::initCombox(){
    QStringList rateList;
    rateList << "4800" << "9600" << "14400" << "19200" << "38400" << "57600" << "115200";
    rateSetCombox->addItems(rateList);
    ratesCombox->addItems(rateList);
    rateSetCombox->setCurrentIndex(rateList.length()-1);
    ratesCombox->setCurrentIndex(rateList.length()-1);
}

/**
 * @brief TempWdiget::initCom
 * 初始化串口
 */
void TempWdiget::initCom(){
    // 获取所有可用的串口信息
    const auto infos = QSerialPortInfo::availablePorts();
    QStringList comList;
    for (const QSerialPortInfo &info : infos) {
       comList << info.portName();
    }
    if(comList.length() > 0){
        portCombox->addItems(comList);
    }
    portCombox->setCurrentIndex(4);
}

/**
 * @brief TempWdiget::openCom
 * 打开串口
 */
void TempWdiget::openCom(){
    if (openSerialBtn->text() == "打开") {
        // 触发连接操作（通过线程安全方式调用 Worker）
        QString com = "/dev/";
        com += portCombox->currentText();
        int rate = ratesCombox->currentText().toInt();
        int addr = 1;
        if(addrLowEdit->text().isEmpty()){
            addr = 1;
        }else{
            addr = addrLowEdit->text().toInt();
        }
        QMetaObject::invokeMethod(worker, "connectModbus", Qt::QueuedConnection,Q_ARG(QString, com),Q_ARG(int, rate),Q_ARG(int, addr));
    } else {
        // 触发断开操作
        QMetaObject::invokeMethod(worker, &ModbusWorker::disconnectModbus, Qt::QueuedConnection);
    }
}

/**
 * @brief TempWdiget::allParamOne
 * 全部参数获取一次
 */
void TempWdiget::allParamOne()
{

}

/**
 * @brief TempWdiget::allParamCycle
 * 全部参数循环获取
 */
void TempWdiget::allParamCycle()
{

}

/**
 * @brief TempWdiget::tempColdOne
 * 温湿度获取一次
 */
void TempWdiget::tempColdOne()
{
    if(!worker){
        return;
    }
    worker->readRegister(1,2);
}

/**
 * @brief TempWdiget::tempColdCycle
 * 温湿度获取循环
 */
void TempWdiget::tempColdCycle()
{

}

/**
 * @brief TempWdiget::tempOne
 * 温度获取一次
 */
void TempWdiget::tempOne()
{

}

/**
 * @brief TempWdiget::tempCycle
 * 温度获取循环
 */
void TempWdiget::tempCycle()
{

}

/**
 * @brief TempWdiget::coldOne
 * 湿度获取一次
 */
void TempWdiget::coldOne()
{
    if(!worker){
        return;
    }
    worker->readRegister(1,1);
}

/**
 * @brief TempWdiget::coldCycle
 * 湿度获取循环
 */
void TempWdiget::coldCycle()
{

}

/**
 * @brief TempWdiget::addrSet
 * 站点设置
 */
void TempWdiget::addrSet()
{

}

/**readDataFinish
 * @brief TempWdiget::setRate
 * 波特率设置
 */
void TempWdiget::setRate()
{

}

/**
 * @brief TempWdiget::getVersion
 * 版本号获取
 */
void TempWdiget::getVersion()
{
    if(!worker){
        return;
    }
    worker->readRegister(0,1);
}

/**
 * @brief TempWdiget::sendMsg
 * 消息发送
 */
void TempWdiget::sendMsg()
{

}

/**
 * @brief TempWdiget::updateOpenBtnStatus
 * 更新打开按钮状态
 * @param isconnected
 */
void TempWdiget::updateOpenBtnStatus(bool isconnected)
{
    openSerialBtn->setText(isconnected ? "关闭" : "打开");
    if (isconnected) {
        openSerialBtn->setStyleSheet("background-color: green; color: white;");
    } else {
        openSerialBtn->setStyleSheet("");
    }
}

/**
 * @brief TempWdiget::updateError
 * 更新错误提示信息
 * @param msg
 */
void TempWdiget::updateError(QString msg)
{
    QMessageBox msgBox;
    msgBox.setIcon(QMessageBox::Critical);    // 设置图标为错误类型
    msgBox.setWindowTitle("错误");             // 标题
    msgBox.setText("发生错误");                // 主文本
    msgBox.setInformativeText(msg);       // 详细描述
    msgBox.setStandardButtons(QMessageBox::Ok); // 按钮
    msgBox.setStyleSheet(
        "QMessageBox { background-color: #2b2b2b; color: white; }"
        "QLabel { color: white; }"
        "QPushButton { background-color: #4CAF50; color: white; }"
        );
    QWidget *parent = QApplication::activeWindow();
    if (parent) {
        msgBox.setParent(parent);
    }
    msgBox.exec();  // 阻塞式弹窗
}

/**
 * @brief TempWdiget::readDataFinish
 * 读数据完成
 * @param data
 */
void TempWdiget::readDataFinish(const QVector<uint16_t> &data)
{
    qDebug() << "TempWdiget readDataFinish data:" << data;
}

/**
 * @brief TempWdiget::writeDataFinish
 * 写数据完成
 * @param value
 */
void TempWdiget::writeDataFinish(int value)
{
    qDebug() << "TempWdiget writeDataFinish value:" << value;
}




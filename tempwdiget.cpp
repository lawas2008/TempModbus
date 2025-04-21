#include "tempwdiget.h"
#include "QHBoxLayout"
#include "QVBoxLayout"
#include "QGroupBox"
#include "QFormLayout"

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
    getParamSingleBtn = new QPushButton("单次");
    getParamCycleBtn = new QPushButton("循环");
    tempLayout->addWidget(tempGTitle);
    tempLayout->addWidget(getParamSingleBtn);
    tempLayout->addWidget(getParamCycleBtn);
    groupVLayout->addLayout(tempLayout);

    QHBoxLayout *coldLayout = new QHBoxLayout();
    QLabel *coldGTitle = new QLabel("湿度");
    coldGTitle->setFixedWidth(80);
    getParamSingleBtn = new QPushButton("单次");
    getParamCycleBtn = new QPushButton("循环");
    coldLayout->addWidget(coldGTitle);
    coldLayout->addWidget(getParamSingleBtn);
    coldLayout->addWidget(getParamCycleBtn);
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
}

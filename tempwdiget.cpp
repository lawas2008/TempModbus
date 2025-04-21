#include "tempwdiget.h"
#include "QHBoxLayout"
#include "QVBoxLayout"
#include "QGroupBox"

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

    //控制布局
    QGroupBox *controlGroupBox = new QGroupBox("控制");

    //水平布局居中
    QHBoxLayout *horizontalContainer = new QHBoxLayout();
    horizontalContainer->addLayout(tempshowLayout);
    setLayout(horizontalContainer);
}

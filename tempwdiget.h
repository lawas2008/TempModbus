#ifndef TEMPWDIGET_H
#define TEMPWDIGET_H

#include <QWidget>
#include <QLineEdit>
#include <QLabel>
#include <QPushButton>
#include <QComboBox>

class TempWdiget : public QWidget
{
    Q_OBJECT
public:
    explicit TempWdiget(QWidget *parent = nullptr);

private:
    //温度
    QLabel *tempLabel;
    //湿度
    QLabel *humiLabel;
    //端口
    QComboBox *portCombox;
    //波特率打开
    QComboBox *ratesCombox;
    //波特率设置
    QComboBox *rateComboxSet;
    //
signals:
};

#endif // TEMPWDIGET_H

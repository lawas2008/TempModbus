#ifndef TEMPWDIGET_H
#define TEMPWDIGET_H

#include <QWidget>
#include <QLineEdit>
#include <QLabel>
#include <QPushButton>
#include <QComboBox>
#include <QListView>
#include <modbusworker.h>

class TempWdiget : public QWidget
{
    Q_OBJECT
public:
    explicit TempWdiget(QWidget *parent = nullptr);

private:
    //温度
    QLabel *tempLabel;
    //湿度
    QLabel *coldLabel;
    //端口
    QComboBox *portCombox;
    //波特率打开
    QComboBox *ratesCombox;
    //波特率设置
    QComboBox *rateSetCombox;
    //打开串口
    QPushButton *openSerialBtn;
    //读取版本
    QPushButton *getVersionBtn;
    //所有参数单次读取
    QPushButton *getParamSingleBtn;
    //所有参数循环读取
    QPushButton *getParamCycleBtn;
    //温湿度单次读取
    QPushButton *getTempCSingleBtn;
    //温湿度循环读取
    QPushButton *getTempCCycleBtn;
    //温度单次读取
    QPushButton *getTempSingleBtn;
    //温度循环读取
    QPushButton *getTempCycleBtn;
    //湿度单次读取
    QPushButton *getColdSingleBtn;
    //湿度循环读取
    QPushButton *getColdeCycleBtn;
    //站号设置
    QLineEdit *addrLowEdit;
    QLineEdit *addrHightEdit;
    QPushButton *addrSetBtn;
    //波特率设置
    QPushButton *rateSetBtn;
    //版本号，站号，波特率显示
    QLineEdit *showVersionEt;
    QLineEdit *showAddrEt;
    QLineEdit *showRateEt;
    //日志消息
    QListView *logListView;
    //发送消息
    QLineEdit *sendCmdEt;
    QPushButton *sendCmdBtn;

    //libModbus线程
    ModbusWorker *worker;
    QThread *modbusThread;

private slots:
    //打开串口
    void openCom();
    //所有参数单次
    void allParamOne();
    //所有参数循环
    void allParamCycle();
    //温湿度单次
    void tempColdOne();
    //温湿度循环
    void tempColdCycle();
    //温度单次
    void tempOne();
    //温度循环
    void tempCycle();
    //湿度单次
    void coldOne();
    //湿度循环
    void coldCycle();
    //设置站号
    void addrSet();
    //设置波特率
    void setRate();
    //获取版本
    void getVersion();
    //发送消息
    void sendMsg();
    //更新串口打开按钮状态
    void updateOpenBtnStatus(bool isconnected);
    //更新错误信息弹窗
    void updateError(QString msg);

private:
    void initCombox();
    void initCom();

signals:
};

#endif // TEMPWDIGET_H

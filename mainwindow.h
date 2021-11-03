#ifndef MAINWINDOW_H
#define MAINWINDOW_H



#include <QMainWindow>
#include <QtCharts/QChartGlobal>

#include <iostream>
#include <QtSerialPort/QSerialPort>
#include <QtSerialPort/QSerialPortInfo>
#include <QMessageBox>
#include <QDebug>
#include <regex>

#include <QtCharts/QChartView>
#include <QtCharts/QLineSeries>
#include <QtCharts/QSplineSeries>
#include <QtCharts/QScatterSeries>
#include <QtWidgets/QLabel>
#include <QtCore/QRandomGenerator>
#include <QtCharts/QValueAxis>

#include <QTimer>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE


QT_BEGIN_NAMESPACE
class QChartView;
class QChart;
QT_END_NAMESPACE


typedef QPair<QPointF, QString> Data;
typedef QList<Data> DataList;
typedef QList<DataList> DataTable;


QT_USE_NAMESPACE


class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    int inAirCut;
    int outAirCut;
    int airSize;
    int setCut;   //用来记录 充气和放气的差

    QTimer *BulingBuling;
    bool Buling_Flag;
    int BulingBuling_interval; //用来记录 闪烁的小灯的间隔

    QString InTime; //用来给单片机发送充气时间
    QString OutTime; //用来给单片机发送充气时间


    QTimer *timerline;   //声明一个定时器


    QLineSeries *series;  //折线数据集
    QChart *serialchart;  //折线表
    QValueAxis *AxisX;    //x，y轴
    QValueAxis *AxisY;
    int i=1;            //全局变量坐标轴X的值


protected:
    void GetSeries();                //用于获取更新的点
    void dealClose();                 //用于关闭“x”操作



private slots:

    void SearchCom();
    void OpenCom();
    void CloseCom();


    void SendInfo(QByteArray &info);

    void ReceiveInfo();

    void on_pushButton_scanCom_clicked();
    void on_radioButton_switchCom_clicked();
    void on_comboBox_baudrate_currentTextChanged(const QString &arg1);


    DataTable generateRandomData(int listCount, int valueMax, int valueCount) const;
    QChart *createSplineChart() const;




    void Buling_timeout();

    void on_pushButton_inAir_clicked();

    void on_pushButton_outAir_clicked();

    void on_pushButton_SetZero_clicked();





    void on_pushButton_InAirTimeSet_clicked();

    void on_pushButton_OutAirTimeSet_clicked();



    void on_pushButton_clicked();

private:
    int m_listCount;
    int m_valueMax;
    int m_valueCount;
    QList<QChartView *> m_charts;
    DataTable m_dataTable;

    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H

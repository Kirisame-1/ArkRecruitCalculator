#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include <QSpinBox>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    
    // 连接所有SpinBox的信号到计算函数
    connect(ui->spinBox_ten_ticket, QOverload<int>::of(&QSpinBox::valueChanged),
            this, &MainWindow::calculatePulls);
    connect(ui->spinBox_normal_ticket, QOverload<int>::of(&QSpinBox::valueChanged),
            this, &MainWindow::calculatePulls);
    connect(ui->spinBox_originium, QOverload<int>::of(&QSpinBox::valueChanged),
            this, &MainWindow::calculatePulls);
    connect(ui->spinBox_orundum, QOverload<int>::of(&QSpinBox::valueChanged),
            this, &MainWindow::calculatePulls);
    
    // 初始计算
    calculatePulls();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::calculatePulls()
{
    // 获取输入值
    int tenTickets = ui->spinBox_ten_ticket->value();
    int normalTickets = ui->spinBox_normal_ticket->value();
    int originium = ui->spinBox_originium->value();
    int orundum = ui->spinBox_orundum->value();
    
    // 计算合成玉总量（包括源石转换）
    int totalOrundum = orundum + (originium * 180);
    
    // 计算抽卡次数
    int tenPulls = tenTickets;  // 十连抽次数
    int singlePulls = normalTickets;  // 单抽次数（普通凭证）
    
    // 计算合成玉可以进行的抽卡次数
    int orundumPulls = totalOrundum / 600;
    singlePulls += orundumPulls;
    
    // 计算总抽卡次数
    int totalPulls = (tenPulls * 10) + singlePulls;
    
    // 计算剩余资源
    int remainingOrundum = totalOrundum % 600;
    int remainingOriginium = 0;
    
    // 如果剩余合成玉来自源石转换，计算剩余源石
    if (remainingOrundum > orundum) {
        int extraOrundum = remainingOrundum - orundum;
        remainingOriginium = extraOrundum / 180;
        remainingOrundum = orundum + (extraOrundum % 180);
    }
    
    // 更新显示
    ui->label_total_pulls->setText(QString("总抽卡次数：%1").arg(totalPulls));
    ui->label_ten_pulls->setText(QString("十连抽次数：%1").arg(tenPulls));
    ui->label_single_pulls->setText(QString("单抽次数：%1").arg(singlePulls));
    ui->label_remaining_orundum->setText(QString("剩余合成玉：%1").arg(remainingOrundum));
    ui->label_remaining_originium->setText(QString("剩余源石：%1").arg(remainingOriginium));
}

#include "measurewidget.h"

MeasureWidget::MeasureWidget(QWidget *parent):QWidget(parent)
{
    // 创建图表
    chart = new QChart();
    chart->setTitle("XY坐标图");

    series = new QLineSeries();
    chart->addSeries(series);

    axisX = new QValueAxis();
    axisX->setTitleText("X轴");
    axisX->setRange(0, 10);

    axisY = new QValueAxis();
    axisY->setTitleText("Y轴");
    axisY->setRange(0, 10);

    // 先为图表添加坐标轴
    chart->addAxis(axisX, Qt::AlignBottom);
    chart->addAxis(axisY, Qt::AlignLeft);

    // 再将系列关联到坐标轴
    series->attachAxis(axisX);
    series->attachAxis(axisY);

    chartView = new QChartView(chart);
    chartView->setRenderHint(QPainter::Antialiasing);

    // 创建右侧控制面板
    updateButton = new QPushButton("更新图表");

    editX1 = new QLineEdit("0");
    editY1 = new QLineEdit("0");
    editX2 = new QLineEdit("10");
    editY2 = new QLineEdit("10");
    editTitle = new QLineEdit("线性函数");

    QVBoxLayout *rightLayout = new QVBoxLayout();
    rightLayout->addWidget(new QLabel("起点 X:"));
    rightLayout->addWidget(editX1);
    rightLayout->addWidget(new QLabel("起点 Y:"));
    rightLayout->addWidget(editY1);
    rightLayout->addWidget(new QLabel("终点 X:"));
    rightLayout->addWidget(editX2);
    rightLayout->addWidget(new QLabel("终点 Y:"));
    rightLayout->addWidget(editY2);
    rightLayout->addWidget(new QLabel("图表标题:"));
    rightLayout->addWidget(editTitle);
    rightLayout->addWidget(updateButton);
    rightLayout->addStretch();

    // 创建主布局
    QHBoxLayout *mainLayout = new QHBoxLayout(this);

    mainLayout->addWidget(chartView, 7);  // 左侧图表占70%空间
    mainLayout->addLayout(rightLayout, 3);  // 右侧控件占30%空间


    // 连接按钮点击事件
    connect(updateButton, &QPushButton::clicked, this, &MeasureWidget::updateChart);

    // 初始化图表数据
    updateChart();
}

MeasureWidget::~MeasureWidget()
{

}

void MeasureWidget::updateChart()
{
    // 从文本框获取数据
    double x1 = editX1->text().toDouble();
    double y1 = editY1->text().toDouble();
    double x2 = editX2->text().toDouble();
    double y2 = editY2->text().toDouble();
    QString title = editTitle->text();

    // 更新图表标题
    chart->setTitle(title);

    // 清除现有数据
    series->clear();

    // 添加新数据点（线性插值）
    for (double x = x1; x <= x2; x += (x2 - x1) / 100.0) {
        double y = y1 + (y2 - y1) * (x - x1) / (x2 - x1);
        series->append(x, y);
    }

    // 更新坐标轴范围
    axisX->setRange(qMin(x1, x2) - 1, qMax(x1, x2) + 1);
    axisY->setRange(qMin(y1, y2) - 1, qMax(y1, y2) + 1);
}

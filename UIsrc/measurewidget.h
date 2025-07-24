#ifndef MEASUREWIDGET_H
#define MEASUREWIDGET_H
#include<QWidget>
#include <QtCharts/QChartView>
#include <QtCharts/QLineSeries>
#include <QtCharts/QValueAxis>
#include<QPushButton>
#include<QLineEdit>
#include<QVBoxLayout>
#include<QLabel>
class MeasureWidget:public QWidget
{
    Q_OBJECT
public:
    explicit MeasureWidget(QWidget* parent = nullptr);
    ~MeasureWidget();

private:
    void updateChart();
    QChartView *chartView;
    QChart *chart;
    QLineSeries *series;
    QValueAxis *axisX;
    QValueAxis *axisY;

    QPushButton *updateButton;
    QLineEdit *editX1, *editY1, *editX2, *editY2, *editTitle;
};

#endif // MEASUREWIDGET_H

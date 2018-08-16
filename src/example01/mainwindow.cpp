#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "boxdatareader.h"
#include <QDockWidget>
#include <QChart>
#include <QBarCategoryAxis>
#include <QBoxPlotSeries>
#include <QBoxSet>
#include <QChartView>
#include <QFile>
#include <QLegend>

using namespace QtCharts;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent)
    //ui(new Ui::MainWindow)
{
    //ui->setupUi(this);

    auto m_dummyTitleBarWidget = new QWidget(this);

    exp_dock_ = new QDockWidget("exp_dock", this);
    exp_dock_->setAllowedAreas(Qt::LeftDockWidgetArea | Qt::RightDockWidgetArea | Qt::BottomDockWidgetArea |
        Qt::TopDockWidgetArea);
    //exp_dock_->setWidget(exp_);
  
    exp_dock_->setFeatures(QDockWidget::DockWidgetClosable | QDockWidget::DockWidgetMovable | QDockWidget::DockWidgetFloatable);

    exp_dock_->setMinimumWidth(200);
    exp_dock_->setStyleSheet(tr("background-color:green;"));

    /*QWidget *testWidget = new QWidget;
    QVBoxLayout *box = new QVBoxLayout;

    QPushButton *okButton = new QPushButton(tr("Ok1"));
    okButton->setStyleSheet(tr("background-color:white;"));
    connect(okButton, SIGNAL(clicked(bool)), this, SLOT(pushButtonClicked(bool)));
    box->addWidget(okButton);
    testWidget->setLayout(box);*/

    exp_dock_->setWidget(this->createChart());


    exp_dock_->setVisible(true);
    
    addDockWidget(Qt::LeftDockWidgetArea, exp_dock_);


    

    log_dock_ = new QDockWidget("log_dock", this);
    //log_dock_->setTitleBarWidget(m_dummyTitleBarWidget);
    log_dock_->setAllowedAreas(Qt::LeftDockWidgetArea | Qt::RightDockWidgetArea | Qt::BottomDockWidgetArea |
        Qt::TopDockWidgetArea);
    //log_dock_->setWidget(log);
    log_dock_->setFeatures(QDockWidget::DockWidgetClosable | QDockWidget::DockWidgetMovable | QDockWidget::DockWidgetFloatable);
    //log_dock_->setFeatures(QDockWidget::NoDockWidgetFeatures);
    log_dock_->setMinimumWidth(200);
    log_dock_->setStyleSheet(tr("background-color:orange;"));


   /* QWidget *testWidget2 = new QWidget;
    QVBoxLayout *box2 = new QVBoxLayout;

    QPushButton *okButton2 = new QPushButton(tr("Ok2"));
    okButton2->setStyleSheet(tr("background-color:white;"));
    box2->addWidget(okButton2);
    testWidget2->setLayout(box2);*/

    log_dock_->setWidget(this->createChart());




    log_dock_->setVisible(true);
    addDockWidget(Qt::BottomDockWidgetArea, log_dock_);

}

MainWindow::~MainWindow()
{
    //delete ui;
}

QtCharts::QChartView* MainWindow::createChart()
{
    
    QBoxPlotSeries *acmeSeries = new QBoxPlotSeries();
    acmeSeries->setName("Ace Ltd");

    QBoxPlotSeries *boxWhiskSeries = new QBoxPlotSeries();
    boxWhiskSeries->setName("BoxWhisk Inc");

    QFile acmeData(":acme_data.txt");
    if (!acmeData.open(QIODevice::ReadOnly | QIODevice::Text)) {
        return nullptr;
    }

    BoxDataReader dataReader(&acmeData);
    while (!dataReader.atEnd()) {
        QBoxSet *set = dataReader.readBox();
        if (set) {
            acmeSeries->append(set);
        }
    }

    QFile boxwhiskData(":boxwhisk_data.txt");
    if (!boxwhiskData.open(QIODevice::ReadOnly | QIODevice::Text)) {
        return nullptr;
    }

    dataReader.readFile(&boxwhiskData);
    while (!dataReader.atEnd()) {
        QBoxSet *set = dataReader.readBox();
        if (set) {
            boxWhiskSeries->append(set);
        }
    }

    QChart *chart = new QChart();
    chart->addSeries(acmeSeries);
    chart->addSeries(boxWhiskSeries);
    chart->setTitle("xiaohai chart example.");
    chart->setAnimationOptions(QChart::SeriesAnimations);

    chart->createDefaultAxes();
    chart->axisY()->setMin(15.0);
    chart->axisY()->setMax(34.0);

    chart->legend()->setVisible(true);
    chart->legend()->setAlignment(Qt::AlignBottom);

    QChartView *chartView = new QChartView(chart);
    chartView->setRenderHint(QPainter::Antialiasing);
    return chartView;
}

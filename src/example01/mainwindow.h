#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

namespace Ui {
class MainWindow;
}

class QDockWidget;

namespace QtCharts
{
    class QChartView;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    
private:
    QtCharts::QChartView* createChart();

private:
    //Ui::MainWindow *ui;
    QDockWidget* exp_dock_;
    QDockWidget* log_dock_;

};

#endif // MAINWINDOW_H

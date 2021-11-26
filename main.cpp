#include "read_file.h"
#include "combination_counter.h"

#include <QtWidgets/QApplication>
#include <QtWidgets/QMainWindow>

#include <QAbstractTableModel>
#include <QTableWidget>
#include <QStandardItemModel>

#include <QChart>
#include <QBarSet>
#include <QBarSeries>
#include <QBarCategoryAxis>
#include <QChartView>

#include <QHBoxLayout>
#include <QFileDialog>

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    QTableView *table = new QTableView;
    QStandardItemModel *model = new QStandardItemModel;
    QStandardItem *it = new QStandardItem(QObject::tr("Combination"));
    model->setHorizontalHeaderItem(0,it);
    QStandardItem *it1 = new QStandardItem(QObject::tr("Frequency"));
    model->setHorizontalHeaderItem(1,it1);

    QWidget *widget = new QWidget;

    auto file1Name = QFileDialog::getOpenFileName(widget,QObject::tr("Open text file"), "/home", QObject::tr("Text Files (*.txt)"));

    const std::string data = file_to_string(file1Name.toStdString());
    auto most_common = get_combination_statistics(std::string_view{data});

    QtCharts::QBarSet *bar_set = new QtCharts::QBarSet("");
    QStringList combinations;
    std::vector<std::string> percentage_strings;

    for(size_t row{0}; auto& elem: most_common){
        QStandardItem *it1 = new QStandardItem(QObject::tr(elem.first.c_str()));
        std::string percentage = std::to_string(elem.second) + '%';
        if(percentage.length() < 4)
            percentage = std::string(4 - percentage.length(), '0').append(percentage);
        percentage.insert(percentage.size()-3, ".");
        auto ref_to_percentage_string = percentage_strings.emplace_back(std::move(percentage));
        QStandardItem *it2 = new QStandardItem(QObject::tr(ref_to_percentage_string.c_str()));
        model->setItem(row, 0, it1);
        model->setItem(row, 1, it2);
        row++;

        bar_set->append(static_cast<float>(elem.second) / 100);
        combinations.append(elem.first.c_str());
    }

    table->setModel(model);

    QtCharts::QBarSeries *series = new QtCharts::QBarSeries();
    series->append(bar_set);
    QtCharts::QChart *chart = new QtCharts::QChart();
    chart->addSeries(series);
    chart->setTitle("Frequency");
    QtCharts::QBarCategoryAxis *axis = new QtCharts::QBarCategoryAxis();
    axis->append(combinations);
    chart->createDefaultAxes();
    chart->setAxisX(axis, series);
    QtCharts::QChartView *chartView = new QtCharts::QChartView(chart);

    QMainWindow window;
    QHBoxLayout *layout = new QHBoxLayout(widget);
    window.setCentralWidget(widget);
    layout->addWidget(table, 25);
    layout->addWidget(chartView, 75);
    window.resize(1280, 480);
    window.show();

    return app.exec();
}
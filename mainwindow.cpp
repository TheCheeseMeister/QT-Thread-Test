#include "mainwindow.h"
#include "./ui_mainwindow.h"

#include <QLabel>

#include <thread>
#include <chrono>
#include <vector>


std::vector<std::thread> labelThreads;
bool end; // tells threads to end

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    end = false;
}

MainWindow::~MainWindow()
{
    end = true;

    for (std::thread& label : labelThreads) {
        label.join();
    }

    delete ui;
}

void task1(QLabel *label)
{
    int count = 0;

    while(!end) {
        label->setText(QString::number(count));
        count++;
        std::this_thread::sleep_for(std::chrono::seconds(1));
    }
}

void MainWindow::on_pushButton_clicked()
{
    //QLabel* label = new QLabel(QString::number(count));
    QLabel* label = new QLabel("0");
    label->setAlignment(Qt::AlignCenter);

    ui->threadContainer->addWidget(label);

    std::thread tempThread(task1, label);
    labelThreads.push_back(std::move(tempThread));
}


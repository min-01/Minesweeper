#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include "field.h"
#include <QPushButton>
#include <QDebug>
//#include "mybutton.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    connect(ui->btnEasy, &QPushButton::clicked, this, [=](){difficulty(1);});
    connect(ui->btnMidd, &QPushButton::clicked, this, [=](){difficulty(2);});
    connect(ui->btnDiff, &QPushButton::clicked, this, [=](){difficulty(3);});
}

MainWindow::~MainWindow()
{
    delete ui;
    qDebug() << "退出主窗口";
}

void MainWindow::difficulty(int n)
{
    if(n == 1) {
        qDebug() << "点击简单";
        Field * easy = new Field(10,10);
        easy -> show();
        easy -> setAttribute(Qt::WA_DeleteOnClose);
    }
    else if(n == 2) {
        qDebug() << "点击中等";
        Field * easy = new Field(20,30);
        easy -> show();
        easy -> setAttribute(Qt::WA_DeleteOnClose);
    }
    else {
        qDebug() << "点击困难";
        Field * easy = new Field(23,45);
        easy -> show();
        easy -> setAttribute(Qt::WA_DeleteOnClose);
    }
}

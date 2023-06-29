#include "mybutton.h"
#include "ui_mybutton.h"
#include <QDebug>
#include <QToolButton>



MyButton::MyButton(QWidget *parent) :
    QToolButton(parent),
    ui(new Ui::MyButton)
{
    ui->setupUi(this);
    // 设置toolbutton不响应点击
    ui->MyToolButton->setAttribute(Qt::WA_TransparentForMouseEvents, true);
}

MyButton::~MyButton()
{
    delete ui;
}


void MyButton::mousePressEvent(QMouseEvent *e)
{
    if(opened) {
        if(mines != 0 ) {
            emit mineSignal(this->row,this->column,mines);
        }
    }
    else {
        if(e -> button() == Qt::RightButton) {
            if(flaged)
                ui->MyToolButton->setIcon(QIcon(QPixmap("")));
            else
                ui->MyToolButton->setIcon(QIcon(QPixmap(":/SaoLei/flag")));
            flaged = !flaged;
            qDebug() << "按下了右键";
        }
    }
}


void MyButton::mouseReleaseEvent(QMouseEvent* e)
{
    if(opened) return;
    if(e -> button() == Qt::LeftButton) {
        if(flaged) {
            flaged = !flaged;
            ui->MyToolButton->setIcon(QIcon(QPixmap("")));
        }
        else {
            openButton();
            if(!havemine && mines == 0) emit openSignal(this->row,this->column);
        }
    }
}

int MyButton::getMines() {
    return mines;
}

void MyButton::addMines() {
    mines++;
}

bool MyButton::getHavemine() {
    return havemine;
}

void MyButton::setHavemine() {
    havemine = !havemine;
}

bool MyButton::getOpened() {
    return opened;
}

void MyButton::setOpened(bool turn) {
    opened = turn;
}
void MyButton::openButton() {
    if(opened) return;
    opened = true;
    ui->MyToolButton->setStyleSheet("background-color:rgb(255,255,255);"
                                    "border:1px;border-style:solid;"
                                    "border-color:rgb(205,205,205);"
                                    "border-radius:4px;");
    if(havemine) {
        stepmine = true;
        ui->MyToolButton->setStyleSheet("background-color:rgb(255,205,205);"
                                        "border:1px;border-style:solid;"
                                        "border-color:rgb(205,205,205);"
                                        "border-radius:4px;");
        ui->MyToolButton->setIcon(QIcon(QPixmap(":/SaoLei/stepmine")));
    }
    else {
        switch (mines)
        {
            case 0 : break;
            case 1 : ui->MyToolButton->setIcon(QIcon(QPixmap(":/SaoLei/1")));break;
            case 2 : ui->MyToolButton->setIcon(QIcon(QPixmap(":/SaoLei/2")));break;
            case 3 : ui->MyToolButton->setIcon(QIcon(QPixmap(":/SaoLei/3")));break;
            case 4 : ui->MyToolButton->setIcon(QIcon(QPixmap(":/SaoLei/4")));break;
            case 5 : ui->MyToolButton->setIcon(QIcon(QPixmap(":/SaoLei/5")));break;
            case 6 : ui->MyToolButton->setIcon(QIcon(QPixmap(":/SaoLei/6")));break;
            case 7 : ui->MyToolButton->setIcon(QIcon(QPixmap(":/SaoLei/7")));break;
            case 8 : ui->MyToolButton->setIcon(QIcon(QPixmap(":/SaoLei/8")));break;
        }
    }
    emit judgeSignal(this->stepmine);
}
// 写入坐标
void MyButton::setCoord(int row, int column) {
    this->row = row;
    this->column = column;
}
// 翻开所有雷
void MyButton::turnMine() {
    opened = true;
    ui->MyToolButton->setStyleSheet("background-color:rgb(255,255,255);"
                                    "border:1px;border-style:solid;"
                                    "border-color:rgb(205,205,205);"
                                    "border-radius:4px;");
    ui->MyToolButton->setIcon(QIcon(QPixmap(":/SaoLei/mine")));
}
// 获取是否插旗
bool MyButton::getFlaged() {
    return flaged;
}

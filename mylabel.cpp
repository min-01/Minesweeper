#include "mylabel.h"
#include "ui_mylabel.h"

MyLabel::MyLabel(QWidget *parent) :
    QLabel(parent),
    ui(new Ui::MyLabel)
{
    ui->setupUi(this);


}

MyLabel::~MyLabel()
{
    delete ui;
}

void MyLabel::getArray(const vector< vector<int> > vec)
{

}

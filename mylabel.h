#ifndef MYLABEL_H
#define MYLABEL_H

#include <QLabel>
using namespace std;

namespace Ui {
class MyLabel;
}

class MyLabel : public QLabel
{
    Q_OBJECT

public:
    explicit MyLabel(QWidget *parent = nullptr);
    ~MyLabel();

    void getArray(const vector< vector<int> > vec);

private:
    Ui::MyLabel *ui;
};

#endif // MYLABEL_H

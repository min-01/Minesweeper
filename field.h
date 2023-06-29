#ifndef FIELD_H
#define FIELD_H

#include <QWidget>
#include <mybutton.h>
#include <QGridLayout>

using namespace std;

namespace Ui {
class Field;
}

class Field : public QWidget
{
    Q_OBJECT

public:
    explicit Field(int,int,QWidget *parent = nullptr);
    ~Field();
    void setMines();               // 布雷
    void countMines();             // 计算周围雷个数
    void openAround(int, int);     // 翻开周围空白块
    void ruleGame(bool);           // 裁决游戏或输或赢或继续
    void openMines();              // 踩雷则翻开所有雷
    void resultDialog(bool);       // 结果对话框
    void creatMybutton();          // 初始化
    void setMapsize(int, int);     // 设置行列
    void deleteMybutton();         // 释放空间
    void mindMines(int,int,int);   // 响应周围有雷
    void sleep_msec(int);          // 延时函数

private:
    Ui::Field *ui;
    bool win = false;              // 赢否
    bool lose = false;             // 输否
    int MAXROW = 10;               // 行数
    int MAXCOLUMN = 10;            // 列数
    int SETMINES = 14;             // 雷数
    MyButton*** mybtn;             // 二维指针数组
};

#endif // FIELD_H

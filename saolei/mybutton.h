#ifndef MYBUTTON_H
#define MYBUTTON_H

#include <QToolButton>
#include <QMouseEvent>


namespace Ui {
class MyButton;
}

class MyButton : public QToolButton
{
    Q_OBJECT

public:
    explicit MyButton(QWidget *parent = nullptr);
    ~MyButton();
    int getMines();            // 获取地雷数量
    void addMines();           // 增加地雷数量
    bool getHavemine();        // 获取是否有雷
    void setHavemine();        // 埋雷
    void openButton();         // 翻开
    bool getOpened();          // 获取是否翻开
    void setOpened(bool);      // 设置是否翻开
    void setCoord(int, int);   // 写入坐标
    void turnMine();           // 翻开所有雷
    bool getFlaged();          // 获取是否插旗

protected:
    // 重写鼠标按下事件
    void mousePressEvent(QMouseEvent* e);
    // 重写鼠标松开事件
    void mouseReleaseEvent(QMouseEvent* e);

private:
    Ui::MyButton *ui;
    int mines = 0;           // 周围地雷个数
    int row;                 // 按钮横坐标
    int column;              // 按钮纵坐标
    bool havemine = false;   // 有无地雷
    bool opened = false;     // 翻开与否
    bool flaged = false;     // 插旗与否
    bool stepmine = false;   // 是否踩雷

signals:
    void openSignal(int, int);       // 翻开空白块触发信号
    void mineSignal(int, int, int);  // 点击触发周围有雷
    void judgeSignal(bool);          // 裁决游戏
};

#endif // MYBUTTON_H

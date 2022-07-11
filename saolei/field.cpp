#include "field.h"
#include "ui_field.h"
#include <QDebug>
#include <QMessageBox>
#include <QToolButton>
#include <QTime>

Field::Field(int row,int column,QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Field)
{
    ui->setupUi(this);
    MAXROW = row;
    MAXCOLUMN = column;
    SETMINES = row*column/7;
    if(MAXROW == 10) this->setFixedSize(330,400);
    else if(MAXROW == 20) this->setFixedSize(940,700);
    else if(MAXROW == 23) this->setFixedSize(1390,790);
    creatMybutton();
    ui->toolButton->setIcon(QIcon(":/SaoLei/cute"));
    connect(ui->toolButton, &QToolButton::clicked, this, [=](){
        deleteMybutton();
        creatMybutton();
        this->setWindowIcon(QIcon(":/SaoLei/window_black"));
        ui->toolButton->setIcon(QIcon(":/SaoLei/cute"));
        win = false;lose = false;
    });

}

Field::~Field()
{
    delete ui;
}
// 初始化
void Field::creatMybutton() {
    // 生成按钮块，初始二维成员指针数组
    mybtn = new MyButton **[MAXROW];
    for(int i = 0; i < MAXROW; i++) {
        mybtn[i] = new MyButton *[MAXCOLUMN];
        for(int j = 0; j < MAXCOLUMN ; j++) {
            mybtn[i][j] = new MyButton();
            mybtn[i][j]->setParent(this);
            ui->gridLayout->addWidget(mybtn[i][j],i,j);
            mybtn[i][j]->setCoord(i, j);
            connect(mybtn[i][j], &MyButton::openSignal, this, &Field::openAround);
            connect(mybtn[i][j], &MyButton::judgeSignal, this, &Field::ruleGame);
            connect(mybtn[i][j], &MyButton::mineSignal, this, &Field::mindMines);
        }
    }
    setMines();
    countMines();
}
// 释放空间
void Field::deleteMybutton() {
    for(int i = 0; i < MAXROW; i++) {
        for(int j = 0; j < MAXCOLUMN ; j++) {
            delete mybtn[i][j];
        }
        delete[] mybtn[i];
    }
    delete[] mybtn;
}
// 埋雷
void Field::setMines() {
    for (int i = 0; i < SETMINES; i++) {
        srand(time(nullptr));
        // 通过死循环来实现不停的寻找，直到安置好雷
        while (true) {
            int row = rand()%MAXROW;
            int col = rand()%MAXCOLUMN;
            // 如果该位置没有布雷，那么则放置
            if (!mybtn[row][col]->getHavemine()) {
                mybtn[row][col]->setHavemine();
                break;
            }
        }
    }
}

// 计算周围雷个数
void Field::countMines() {
    for (int i = 0; i < MAXROW; i++) {
        for(int j = 0; j < MAXCOLUMN; j++) {
            if(!mybtn[i][j]->getHavemine()) {
                    if(i+1<MAXROW && mybtn[i+1][j]->getHavemine()) mybtn[i][j]->addMines();
                    if(j+1<MAXCOLUMN && mybtn[i][j+1]->getHavemine()) mybtn[i][j]->addMines();
                    if(i-1>=0 && mybtn[i-1][j]->getHavemine()) mybtn[i][j]->addMines();
                    if(j-1>=0 && mybtn[i][j-1]->getHavemine()) mybtn[i][j]->addMines();
                    if(i+1<MAXROW && j+1<MAXCOLUMN && mybtn[i+1][j+1]->getHavemine()) mybtn[i][j]->addMines();
                    if(i-1>=0 && j-1>=0 && mybtn[i-1][j-1]->getHavemine()) mybtn[i][j]->addMines();
                    if(i+1<MAXROW && j-1>=0 && mybtn[i+1][j-1]->getHavemine()) mybtn[i][j]->addMines();
                    if(i-1>=0 && j+1<MAXCOLUMN && mybtn[i-1][j+1]->getHavemine()) mybtn[i][j]->addMines();
            }
        }
    }
}

// 翻开周围空白块
void Field::openAround(int row, int column) {
    qDebug() << row << column;
    mybtn[row][column]->openButton();
    if(mybtn[row][column]->getMines()!=0) return;
    int nx,ny;
    int dx[8]={-1,1,-1,1,0,1,-1,0};
    int dy[8]={-1,1,1,-1,1,0,0,-1};
    for(int i=0;i<8;++i){
        nx=row+dx[i];
        ny=column+dy[i];
        // 下标合法并且还未被翻开
        if(0<=nx && nx<MAXROW && 0<=ny && ny<MAXCOLUMN && !mybtn[nx][ny]->getOpened()){
            openAround(nx,ny);
        }
    }
}

// 裁决游戏或输或赢或继续
void Field::ruleGame(bool stepmine) {
    if(!lose && !win && stepmine) {
        lose = true;
        ui->toolButton->setIcon(QIcon(":/SaoLei/lose"));
        // 翻开其他炸弹
        openMines();
        // 弹窗结果提示游戏失败
        resultDialog(false);
    }
    else {
        int sum=0;
        for(int i = 0; i < MAXROW; i++) {
            for(int j = 0; j < MAXCOLUMN; j++) {
                if(!mybtn[i][j]->getOpened()) sum++;
            }
        }
        if(!lose && sum == SETMINES) {
            win = true;
            ui->toolButton->setIcon(QIcon(":/SaoLei/win"));
            resultDialog(true);
        }
    }
}
// 踩雷则翻开所有雷
void Field::openMines() {
    for(int i = 0; i < MAXROW; i++) {
        for(int j = 0; j < MAXCOLUMN; j++) {
            if(!mybtn[i][j]->getOpened() && mybtn[i][j]->getHavemine()) {
                mybtn[i][j]->turnMine();
            }
        }
    }
}
// 结果对话框
void Field::resultDialog(bool result){
    // 消息对话框
    if(result) {
        QMessageBox::information(this,"提示","恭喜，胜利！！");
    }
    else {
        this->setWindowIcon(QIcon(":/SaoLei/window_red"));
        QMessageBox::information(this,"提示","遗憾，踩雷。");
    }
}
// 设置行列
void Field::setMapsize(int row, int column) {
    MAXROW = row;
    MAXCOLUMN = column;
    SETMINES = row*column/8;
}
// 响应周围有雷
void Field::mindMines(int row,int column,int mines) {
    int nx,ny;
    int dx[8]={-1,1,-1,1,0,1,-1,0};
    int dy[8]={-1,1,1,-1,1,0,0,-1};
    int flages = 0;
    for(int i=0;i<8;++i){
        nx=row+dx[i];
        ny=column+dy[i];
        // 下标合法并且还未被翻开
        if(0<=nx && nx<MAXROW && 0<=ny && ny<MAXCOLUMN && mybtn[nx][ny]->getFlaged()){
            flages++;
        }
    }
    // 雷数与插旗数相等则翻开周围格子
    if(flages == mines) {
        for(int i=0;i<8;++i){
            nx=row+dx[i];
            ny=column+dy[i];
            // 下标合法并且还未被翻开，未插旗
            if(0<=nx && nx<MAXROW && 0<=ny && ny<MAXCOLUMN && !mybtn[nx][ny]->getOpened() && !mybtn[nx][ny]->getFlaged()){
                openAround(nx,ny);
            }
        }
    }
    else {
        for(int i=0;i<8;++i){
            nx=row+dx[i];
            ny=column+dy[i];
            // 下标合法并且还未被翻开，未插旗
            if(0<=nx && nx<MAXROW && 0<=ny && ny<MAXCOLUMN && !mybtn[nx][ny]->getOpened() && !mybtn[nx][ny]->getFlaged()){
                mybtn[nx][ny]->hide();
            }
        }
        sleep_msec(100);
        for(int i=0;i<8;++i){
            nx=row+dx[i];
            ny=column+dy[i];
            // 下标合法并且还未被翻开，未插旗
            if(0<=nx && nx<MAXROW && 0<=ny && ny<MAXCOLUMN && !mybtn[nx][ny]->getOpened() && !mybtn[nx][ny]->getFlaged()){
                mybtn[nx][ny]->show();
            }
        }
    }
}

// 延时函数,此法不会阻塞当前线程,适合Qt单线程带UI程序
void Field::sleep_msec(int msec)
{
    QTime dieTime = QTime::currentTime().addMSecs(msec);
    while( QTime::currentTime() < dieTime )
    {
        //强制进入当前线程的事件循环,这样可以把堵塞的事件都处理掉,从而避免程序卡死。
        QCoreApplication::processEvents(QEventLoop::AllEvents, 100);
        //如果去掉QCoreApplication::processEvents; 可以延时,但会阻塞线程
    }
}

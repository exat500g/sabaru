#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMouseEvent>
#include <QContextMenuEvent>
#include <QDebug>
#include <windows.h>
#include <QVector2D>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->setAttribute(Qt::WA_TranslucentBackground, true);
    this->setWindowFlags(Qt::Tool|Qt::FramelessWindowHint|Qt::WindowStaysOnTopHint);//|Qt::BypassWindowManagerHint
    //this->setMouseTracking(true);
    //this->setWindowOpacity(0.95);
    {
        menu.addActions({ui->actionExit});
    }
    connect(&timer,&QTimer::timeout,this,&MainWindow::onTimer);
    timer.setInterval(20);
    timer.setSingleShot(false);
    timer.start();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::mousePressEvent(QMouseEvent *e){
    tracking=true;
    lastMousePos=e->screenPos().toPoint();
    lastWindowPos=this->pos();
}

void MainWindow::mouseReleaseEvent(QMouseEvent *){
    tracking=false;
}

void MainWindow::mouseMoveEvent(QMouseEvent *e){
    if(tracking){
        QPoint delta=e->screenPos().toPoint() - lastMousePos;
        this->move(lastWindowPos+delta);
    }
}

void MainWindow::contextMenuEvent(QContextMenuEvent* e){
    menu.popup(e->globalPos());
    e->accept();
}

void MainWindow::onTimer(){
    POINT p;
    GetCursorPos(&p);
    {
        QPoint screenPos(p.x,p.y);
        QVector2D v(screenPos - pos());
        v -= {110,170};
        v*=0.05;
        if(v.length()>5.0){
            v*=5.0/v.length();
        }
        if(v[1] > 3){
            v[1]=3;
        }else if(v[1]<-3){
            v[1]=-3;
        }
        QPoint offsetPixel=v.toPoint();
        offsetPixel += {-5,0};
        ui->eye->move(offsetPixel);
    }
}

void MainWindow::on_actionExit_triggered()
{
    qApp->exit();
}

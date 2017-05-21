#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMenu>
#include <QTimer>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
protected:
    void mousePressEvent(QMouseEvent *)override;
    void mouseReleaseEvent(QMouseEvent *)override;
    void mouseMoveEvent(QMouseEvent *)override;
    void contextMenuEvent(QContextMenuEvent*)override;

private slots:
    void onTimer();
    void on_actionExit_triggered();

private:
    bool tracking;
    QPoint lastMousePos;
    QPoint lastWindowPos;
    QMenu menu;
    QTimer timer;
};

#endif // MAINWINDOW_H

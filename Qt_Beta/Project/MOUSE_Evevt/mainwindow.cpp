#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QKeyEvent>
#include <QDebug>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::keyPressEvent(QKeyEvent *event)
{
    int keyValue = event->key();
    if (keyValue == Qt::Key_Control)
    {
        //获取鼠标位置
        qDebug() << "=== press key";
        QPoint pt = QCursor::pos();//获取鼠标的绝对位置
        QString str;
        str = QString("%1 , %2").arg(pt.x()).arg(pt.y());
        ui->lineEdit->setText(str);//显示

        // nowmouseplace(pt.x(),pt.y());
    }
    if (keyValue == Qt::Key_Shift)
    {
        //获取鼠标位置
        qDebug() << "=== press key";
        QPoint pt = QCursor::pos();//获取鼠标的绝对位置
        QString str;
        str = QString("%1 , %2").arg(pt.x()).arg(pt.y());
        ui->lineEdit_2->setText(str);//显示

        // nowmouseplace(pt.x(),pt.y());
    }
}



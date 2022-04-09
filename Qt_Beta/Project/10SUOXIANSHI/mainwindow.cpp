#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "vid_receiver.h"

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

void MainWindow::on_pushButton_clicked()
{

    unsigned char *data;


    AVC_VID_RECEIVER_INST_t *input;

    AVC_VID_RECEIVER_INST_t output;


    input->flag = 1;//应该是标志位


    //------------------------------------------------------------------------------
    //		nIp:	[IN] - 网络输入IP
    //		nPort:	[IN] - 网络输入端口
    //------------------------------------------------------------------------------
    input->nIp;
    input->nPort;

    //------------------------------------------------------------------------------
    //		pData:	[OUT] - 网络数据输出，用户提供输出缓冲区，用于存放输出数据。
    //		nLen:   [IN]  - 输入缓冲区长度，用户设置。
    //				[OUT] - 输出数据长度，本模块设置。

    input->nLen;

    input->pData = data;


    //AVC_VID_RECEIVER_INST_t.pArgs;//用户禁止操作

    AVC_VidReceiver_Create(input);


}

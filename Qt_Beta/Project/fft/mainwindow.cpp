#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "qcustomplot.h"
#include "fftw3.h"
#include "QDebug"

#include <QDebug>
#include <QTime>
#include <sys/time.h>
#include <windows.h>
#include <math.h>


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
    struct timeval tpstart, tpend;
    float timeuse;
    gettimeofday(&tpstart, NULL);
    on_pushButton_clicked();
    gettimeofday(&tpend, NULL);
    timeuse = (1000000 * (tpend.tv_sec - tpstart.tv_sec) + tpend.tv_usec - tpstart.tv_usec) / 1000000.0;
    qDebug() << timeuse << "s";
}

void MainWindow::on_pushButton_clicked()
{

    struct timeval tpstart, tpend;
    float timeuse;
    gettimeofday(&tpstart, NULL);

    int N = 4096;
    fftw_complex *in, *out;
    fftw_plan p;
    //add code;
    in = (fftw_complex *) fftw_malloc(sizeof(fftw_complex) * N);
    out = (fftw_complex *) fftw_malloc(sizeof(fftw_complex) * N);
    p = fftw_plan_dft_1d(N, in, out, FFTW_FORWARD, FFTW_ESTIMATE);
    //add code;
    for (int i = 0; i < N; i++)
    {
        in[i][0] = sin(i);//real
        in[i][1] = 0;//image
        qDebug() << *in << "," << &in;
    }
    qDebug() << "inin" << in;
    fftw_execute(p); /* repeat as needed */
    //add code;
//    double aabs  =  fabs(out);

    for (int i = 0; i < N; i++)
    {
        qDebug() << out[i][0] << "," << out[i][1];
    }

    /**/
    for(int i = 0; i < N; i++)
    {
        abss[i] = sqrt(out[i][0] * out[i][0] + out[i][1] * out[i][1]);
    }


    /**/
    fftw_destroy_plan(p);
    fftw_free(in);
    fftw_free(out);

    gettimeofday(&tpend, NULL);
    timeuse = (1000000 * (tpend.tv_sec - tpstart.tv_sec) + tpend.tv_usec - tpstart.tv_usec) / 1000000.0;
    qDebug() << timeuse << "s";
}

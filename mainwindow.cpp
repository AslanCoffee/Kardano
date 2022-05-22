#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "main.cpp"
#include <math.h>


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_clicked()
{
    QString TextShifr = ui->Text->text();//получил текст
    int size = ui->SizeBox->value();//получил размер

    int** reshetka2 = new int* [size * 2];//ну вывод решетки
    for (int i = 0; i < size * 2; i++)
        reshetka2[i] = new int[size * 2];

    int** key2 = new int* [size * 2];//преобразование в инт
    for (int i = 0; i < size * 2; i++)
        key2[i] = new int[size * 2];

    QString** kar = new QString* [size * 2];//это типа crypto
    for (int i = 0; i < size * 2; i++)
        kar[i] = new QString[size * 2];

    QChar** key3 = new QChar* [size * 2];//для того чтобы считать
    for (int i = 0; i < size * 2; i++)
        key3[i] = new QChar[size * 2];



    reshetka2 = shifrovka(size);
    key3 = keycreate(size, reshetka2);

    for(int i = 0; i < size*2; i++)
    {
        for(int j = 0; j < size*2; j++)
        {
            if(key3[i][j]=='1') key2[i][j] = 1;
            else key2[i][j] = 0;
        }
    }

     ui->Key->setText("");
    for(int i = 0; i < size*2; i++)
    {
        for(int j = 0; j < size*2; j++)
        {
            ui->Key->setText(ui->Key->text() + key3[i][j]);
        }
    }
    ui->Crypto->setText("");
    kar = kardanocreate(size, key2, TextShifr);

    for(int i = 0; i < size*2; i++)
    {
        for(int j = 0; j < size*2; j++)
        {
            ui->Crypto->setText(ui->Crypto->text() + kar[i][j]);
        }
    }
}


void MainWindow::on_ButDeshifr_clicked()
{
    QString TextDeShifr = ui->Crypto->text();
    QString key = ui->Key->text();

    int size = TextDeShifr.length();
    size = sqrt(size/4);

    int** key2 = new int* [size * 2];
    for (int i = 0; i < size * 2; i++)
        key2[i] = new int[size * 2];

    int count = 0;

    for(int i = 0; i < size*2; i++)
    {
        for(int j = 0; j < size*2; j++)
        {
            if(key[count]=='1')key2[i][j]=1;
            else key2[i][j]=0;
            count++;
        }
    }
    ui->answer->setText("");
    QString str = answerout(key2,size,TextDeShifr);
    ui->answer->setText(ui->answer->text() + str);
}


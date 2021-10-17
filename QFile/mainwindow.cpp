#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QFile>
#include <QTextStream>
#include <QMessageBox>
#include <QDebug>
#include <QVector>

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

//writing from file
void MainWindow::on_pushButton_clicked()
{
    QFile file("C:/Users/Jay/Desktop/QT Practice/QFile/myfile.csv");

    //if the file is not open
    if(!file.open(QFile::Append | QFile::Text)){
        QMessageBox::warning(this,"Error", "File not open");
    }
    //reference to your file
    QTextStream out(&file);
    QString text = ui->plainTextEdit->toPlainText();
    out << text << "," << "Hello World" << "\n";

    //flush the file after and close
    file.flush();
    file.close();
}

//reading from file
void MainWindow::on_pushButton_2_clicked()
{
    ui->listWidget->clear();
    QVector<QStringList> l = getList();
    qDebug() << l.size();
    for(int i = 0; i < l.size(); i++){
        for(int x = 0; x < 2; x++){
            ui->listWidget->addItem(l[i][x]);
        }
    }
}

QVector<QStringList>MainWindow::getList(){
    QFile file("C:/Users/Jay/Desktop/QT Practice/QFile/myfile.csv");

    //if the file is not open
    if(!file.open(QFile::ReadOnly | QFile::Text)){
        QMessageBox::warning(this,"Error", "File not open");
    }

    //Acts like a vector
    QVector<QStringList> list;
    //reference to your file
    QTextStream in(&file);

    //loop through csv data
    while(!in.atEnd()){
        QString line = file.readLine().replace("\n","");
        list.push_back(line.split(','));
    }
    //we dont need to flush bec we are only reading
    file.close();

    //ptrList = &list;
    return list;
}

void MainWindow::on_pushButton_3_clicked(){
    QVector<QStringList> l = getList();

    //int i = ui->listWidget->currentRow();

    l[0][0] = "Jay Shadow";

    QFile file("C:/Users/Jay/Desktop/QT Practice/QFile/myfile.csv");

    //if the file is not open
    if(!file.open(QFile::WriteOnly | QFile::Text)){
        QMessageBox::warning(this,"Error", "File not open");
    }
    //reference to your file
    QTextStream out(&file);

    for(int i = 0; i < l.size(); i++){
        for(int x = 0; x < 2; x++){
          out << l[i][x];
          if(x != l[i].size())
              out << ",";
        }
        out << "\n";
    }

    //flush the file after and close
    file.flush();
    file.close();
}



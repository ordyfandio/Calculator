#include "mainwindow.h"
#include "./ui_mainwindow.h"

double firstNum;
bool userIsTypingSecondNumber = false;

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    connect(ui->pushButton_0,SIGNAL(released()),this,SLOT(digit_pressed()));
    connect(ui->pushButton_1,SIGNAL(released()),this,SLOT(digit_pressed()));
    connect(ui->pushButton_2,SIGNAL(released()),this,SLOT(digit_pressed()));
    connect(ui->pushButton_3,SIGNAL(released()),this,SLOT(digit_pressed()));
    connect(ui->pushButton_4,SIGNAL(released()),this,SLOT(digit_pressed()));
    connect(ui->pushButton_5,SIGNAL(released()),this,SLOT(digit_pressed()));
    connect(ui->pushButton_6,SIGNAL(released()),this,SLOT(digit_pressed()));
    connect(ui->pushButton_7,SIGNAL(released()),this,SLOT(digit_pressed()));
    connect(ui->pushButton_8,SIGNAL(released()),this,SLOT(digit_pressed()));
    connect(ui->pushButton_9,SIGNAL(released()),this,SLOT(digit_pressed()));

    connect(ui->pushButton_PlusMinus,SIGNAL(released()),this,SLOT(unary_operation_pressed()));
    connect(ui->pushButton_percent,SIGNAL(released()),this,SLOT(unary_operation_pressed()));

    connect(ui->pushButton_add,SIGNAL(released()),this,SLOT(binary_operation_pressed()));
    connect(ui->pushButton_substract,SIGNAL(released()),this,SLOT(binary_operation_pressed()));
    connect(ui->pushButton_Multi,SIGNAL(released()),this,SLOT(binary_operation_pressed()));
    connect(ui->pushButton_divide,SIGNAL(released()),this,SLOT(binary_operation_pressed()));

    ui->pushButton_add->setCheckable(true);
    ui->pushButton_Multi->setCheckable(true);
    ui->pushButton_divide->setCheckable(true);
    ui->pushButton_substract->setCheckable(true);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::digit_pressed(){

   QPushButton * button = (QPushButton*)sender();
   QString newlabel;
   double  labelNumber;

   if((ui->pushButton_add->isChecked() || ui->pushButton_substract->isChecked() ||
           ui->pushButton_Multi->isChecked() || ui->pushButton_divide->isChecked()) && (!userIsTypingSecondNumber)){

       labelNumber= button->text().toDouble();
       userIsTypingSecondNumber = true;
       newlabel = QString::number(labelNumber,'g',15);
   }else{
       if(ui->label->text().contains('.') && button->text() == "0"){
           newlabel= ui->label->text() + button->text();
       }else{
          labelNumber= (ui->label->text() + button->text()).toDouble();
          newlabel = QString::number(labelNumber,'g',15);
       }
   }

   ui->label->setText(newlabel);
}

void MainWindow::on_pushButton_decimal_released()
{
    ui->label->setText(ui->label->text() + ".");
}

void MainWindow::unary_operation_pressed(){
    QPushButton *button=(QPushButton*) sender();
    QString newlabel;
    double  labelNumber;

    if(button->text() == "+/-"){
        labelNumber = ui->label->text().toDouble();
        labelNumber =  labelNumber * -1;
        newlabel = QString::number(labelNumber,'g',15);
        ui->label->setText(newlabel);
    }

    if(button->text() == "%"){
        labelNumber = ui->label->text().toDouble();
        labelNumber =  labelNumber * 0.01;
        newlabel = QString::number(labelNumber,'g',15);
        ui->label->setText(newlabel);
    }
}


void MainWindow::on_pushbutton_clear_released()
{
     ui->pushButton_add->setChecked(false);
     ui->pushButton_substract->setChecked(false);
     ui->pushButton_Multi->setChecked(false);
     ui->pushButton_divide->setChecked(false);

     userIsTypingSecondNumber = false;

     ui->label->setText("0");
}


void MainWindow::on_pushButton_equal_released()
{
    QString newlabel;
    double  labelNumber,secondNum;
    secondNum = ui->label->text().toDouble();

    if(ui->pushButton_add->isChecked()){
       labelNumber = firstNum + secondNum;
       newlabel = QString::number(labelNumber,'g',15);
       ui->label->setText(newlabel);
       ui->pushButton_add->setChecked(false);
    }
    else if(ui->pushButton_substract->isChecked()){
        labelNumber = firstNum - secondNum;
        newlabel = QString::number(labelNumber,'g',15);
        ui->label->setText(newlabel);
        ui->pushButton_substract->setChecked(false);
    }
    else if(ui->pushButton_Multi->isChecked()){
        labelNumber = firstNum * secondNum;
        newlabel = QString::number(labelNumber,'g',15);
        ui->label->setText(newlabel);
        ui->pushButton_Multi->setChecked(false);
    }
    else if(ui->pushButton_divide->isChecked()){
        labelNumber = firstNum / secondNum;
        newlabel = QString::number(labelNumber,'g',15);
        ui->label->setText(newlabel);
        ui->pushButton_divide->setChecked(false);
    }

    userIsTypingSecondNumber = false;
}

void MainWindow::binary_operation_pressed(){
    QPushButton *button=(QPushButton*) sender();

    firstNum = ui->label->text().toDouble();

    button->setChecked(true);
}


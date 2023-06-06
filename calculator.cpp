#include "calculator.h"
#include "ui_calculator.h"

double calcVal = 0.0;
bool divTrigger = false;
bool multTrigger = false;
bool addTrigger = false;
bool subTrigger = false;


Calculator::Calculator(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::Calculator)
{
    ui->setupUi(this);

    ui->Display->setText(QString::number(calcVal));
    QPushButton *numButtons[10];
    for(int i = 0; i<10; i++){
        QString butName = "Button" + QString::number(i);
        numButtons[i] = Calculator::findChild<QPushButton *>(butName); // search for specific widget provided by name
        connect(numButtons[i], SIGNAL(released()), this, SLOT(NumPressed()));
    }
    connect(ui->Add, SIGNAL(released()), this, SLOT(MathButtonPressed()));
    connect(ui->Substract, SIGNAL(released()), this, SLOT(MathButtonPressed()));
    connect(ui->Division, SIGNAL(released()), this, SLOT(MathButtonPressed()));
    connect(ui->Multiply, SIGNAL(released()), this, SLOT(MathButtonPressed()));
    connect(ui->Equals, SIGNAL(released()), this, SLOT(EqualButton()));
    connect(ui->Clear, SIGNAL(released()), this, SLOT(ClearAll()));
    connect(ui->Percent, SIGNAL(released()), this, SLOT(Percent()));
    connect(ui->Pow, SIGNAL(released()), this, SLOT(Pow()));
    connect(ui->BackSpace, SIGNAL(released()), this, SLOT(ClearOneElement()));

}

Calculator::~Calculator()
{
    delete ui;
}

void Calculator::NumPressed(){
    QPushButton *button = (QPushButton *)sender();
    QString butval = button->text(); //get number
    QString displayVal = ui->Display->text();
    if(displayVal.toDouble() == 0 || displayVal.toDouble() == 0.0){
        ui->Display->setText(butval);
    }else {
        QString newVal = displayVal+butval;
        double dbNewVal = newVal.toDouble();
        ui->Display->setText(QString::number(dbNewVal, 'g', 16));
    }
}


void Calculator::MathButtonPressed(){
    divTrigger = false;
    multTrigger = false;
    addTrigger = false;
    subTrigger = false;
    QString displayVal = ui->Display->text();
    calcVal = displayVal.toDouble();
    QPushButton *button = (QPushButton*)sender();
    QString butVal = button->text();
    if(QString::compare(butVal, "/", Qt::CaseInsensitive)==0){
        divTrigger =true;
    }else if(QString::compare(butVal, "*", Qt::CaseInsensitive)==0){
        multTrigger = true;
    }else if(QString::compare(butVal, "+", Qt::CaseInsensitive)==0){
        addTrigger = true;
    }else{
        subTrigger = true;
    }

    ui->Display->setText("");
}

void Calculator::EqualButton(){
    double solution = 0.0;
    QString displayVal = ui->Display->text();
    double dblDisplayVal = displayVal.toDouble();
    if (addTrigger || subTrigger || divTrigger || multTrigger){
        if(addTrigger){
            solution = calcVal + dblDisplayVal;
        }else if(subTrigger){
            solution = calcVal - dblDisplayVal;
        }else if(multTrigger){
        solution = calcVal * dblDisplayVal;
    }else{
            solution = calcVal / dblDisplayVal;
        }


    }
    ui->Display->setText(QString::number(solution));

}

void Calculator::ClearAll(){

    QPushButton *button = (QPushButton*)sender();
    QString butVal = button->text();
    if(QString::compare(butVal, "AC", Qt::CaseInsensitive)==0){
        ui->Display->setText("");
    }

}
void Calculator::ClearOneElement(){
    QPushButton *button = (QPushButton*)sender();
    QString butVal = button->text();

    if(QString::compare(butVal, "<-", Qt::CaseInsensitive)==0){
        QString displayVal = ui->Display->text();
        QString newVal = displayVal.removeLast();
        if(QString::compare(newVal, "", Qt::CaseInsensitive)==0 || newVal.toDouble() == 0.0 || newVal.toDouble() == 0 ){
            ui->Display->setText("0.0");
        }else{
            ui->Display->setText(newVal);
        }
    }
}

void Calculator::Percent(){
        QString displayVal = ui->Display->text();
        double dblDisplayValue = displayVal.toDouble();
        double solution = 0.0;

        solution = dblDisplayValue / 100;
        ui->Display->setText(QString::number(solution));
}


void Calculator::Pow(){
        QString displayVal = ui->Display->text();
        double dblDisplayValue = displayVal.toDouble();
        double solution = 0.0;

        solution = dblDisplayValue * dblDisplayValue;
        ui->Display->setText(QString::number(solution));
}


void Calculator::Square(){
        QString displayVal = ui->Display->text();
        double dblDisplayValue = displayVal.toDouble();
        double solution = 0.0;

        solution = sqrt(dblDisplayValue);
        ui->Display->setText(QString::number(solution));
}

#include "calculator.h"
#include "./ui_calculator.h"

double currentVal = 0.0;
bool divTrig = false;
bool multiTrig = false;
bool addTrig = false;
bool subTrig = false;
bool ac = false;

Calculator::Calculator(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::Calculator)
{
    ui->setupUi(this);
    ui->Display->setText(QString::number(currentVal));
    QPushButton *numButtons[10];
    for (int i = 0; i < 10; i++)
    {
        QString butName = "button" + QString::number(i);
        numButtons[i] = Calculator::findChild<QPushButton *>(butName);
        connect(numButtons[i], SIGNAL(released()), this, SLOT(NumPressed()));
    }

    connect(ui->plus, SIGNAL(released()), this, SLOT(MathButtonsPressed()));
    connect(ui->minus, SIGNAL(released()), this, SLOT(NathButtonsPressed()));
    connect(ui->multi, SIGNAL(released()), this, SLOT(MathButtonsPressed()));
    connect(ui->divide, SIGNAL(released()), this, SLOT(MathButtonsPressed()));

    connect(ui->equal, SIGNAL(released()), this, SLOT(EqualButton()));
    connect(ui->symbol, SIGNAL(released()), this, SLOT(ChangeSign()));
}

Calculator::~Calculator()
{
    delete ui;
}

void Calculator::NumPressed()
{
    QPushButton *button = (QPushButton *) sender();
    QString butVal = button->text();
    QString displayValue = ui->Display->text();
    if (displayValue.toDouble() == 0 || displayValue.toDouble() == 0.0)
    {
        ui->Display->setText(butVal);
    }
    else {
        QString newVal = displayValue + butVal;
        double dNewVal = newVal.toDouble();
        ui->Display->setText(QString::number(dNewVal, 'g', 16));
    }

}

void Calculator::MathButtonsPressed()
{
    divTrig = false;
    multiTrig = false;
    addTrig = false;
    subTrig = false;
    ac = false;

    QString displayVal = ui->Display->text();
    currentVal = displayVal.toDouble();
    QPushButton *button = (QPushButton *) sender();
    QString butVal = button->text();
    if (QString::compare(butVal, "/", Qt::CaseInsensitive) == 0)
    {
        divTrig = true;
    }
    else if (QString::compare(butVal, "*", Qt::CaseInsensitive) == 0)
    {
        multiTrig = true;
    }
    else if (QString::compare(butVal, "+", Qt::CaseInsensitive) == 0)
    {
        addTrig = true;
    }
    else if (QString::compare(butVal, "-", Qt::CaseInsensitive) == 0)
    {
        subTrig = true;
    }
    else if (QString::compare(butVal, "AC", Qt::CaseInsensitive) == 0)
    {
        ac = true;
        currentVal = 0;
        butVal = 0;
        displayVal = 0;
    }
    ui->Display->setText("");
}

void Calculator::EqualButton()
{
    double solution = 0.0;
    QString displayVal = ui->Display->text();
    double dDisplayVal = displayVal.toDouble();
    if (addTrig || subTrig || multiTrig || divTrig)
    {
        if (addTrig)
        {
            solution = currentVal + dDisplayVal;
        }
        else if (subTrig)
        {
            solution = currentVal - dDisplayVal;
        }
        else if (multiTrig)
        {
            solution = currentVal * dDisplayVal;
        }
        else if (divTrig)
        {
            solution = currentVal / dDisplayVal;
        }
        ui->Display->setText(QString::number(solution));
    }
}

void Calculator::ChangeSign()
{
    QString displayVal = ui->Display->text();
    QRegularExpression reg("[-]?[0-9.]*");
    QRegularExpressionMatch match = reg.match(displayVal);
    if (match.hasMatch())
    {
        double dDisplayVal = displayVal.toDouble();
        double dDisplayValSign = -1 * dDisplayVal;
        ui->Display->setText(QString::number(dDisplayVal));
    }
}


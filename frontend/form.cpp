#include "form.h"
#include "ui_form.h"

Form::Form(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::Form)
{
    ui->setupUi(this);
}

Form::~Form()
{
    delete ui;
}

void Form::on_pushButton_clicked()
{
    emit backSignal();
}

void Form::slot(QString id)
{
    ui->label->setText(id);
}





#include "categories.h"
#include "ui_categories.h"

Categories::Categories(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::Categories)
{
    ui->setupUi(this);
    connect(ui->listWidget, SIGNAL(itemClicked(QListWidgetItem*)),this, SLOT(onItemSelected(QListWidgetItem*)));
    ui->DeleteButton->setEnabled(false);
    ui->EditButton->setEnabled(false);
}

Categories::~Categories()
{
    delete ui;
}

//SLOT ON WINDOW SHOW
void Categories::GetCategoriesData(vector<QJsonObject> vect, QTcpSocket *sock, QString Category, int userid)
{
    //FILL WITH DATA
    socket = sock;
    categories = vect;
    CurrentCategory = Category;
    currentuserid = userid;

    //LIST WIDGET FILL
    ui->listWidget->clear();
    QListWidgetItem *newItem = new QListWidgetItem;
    newItem->setText("All Categories");
    newItem->setTextAlignment(Qt::AlignCenter);
    ui->lineEdit->clear();
    ui->listWidget->addItem(newItem);
    for(const auto &x: categories)
    {
        QListWidgetItem *newItem = new QListWidgetItem;
        newItem->setText(x.value("taskCategories_Name").toString());
        newItem->setTextAlignment(Qt::AlignCenter);
        ui->listWidget->addItem(newItem);
    }
    ui->listWidget->setCurrentRow(0);
    ui->EditButton->setText("Edit");

    //STYLES
    this->setStyleSheet("QMainWindow{background-color: white;} QPushButton {border: 1px solid black; } QLineEdit {border: 1px solid black; } QListWidget {border: 1px solid black; } ");
    ui->SetButton->setStyleSheet("QPushButton {border: 1px solid black; } QPushButton:hover { border: 1px solid darkgreen;}");
    ui->AddNewButton->setStyleSheet("QPushButton {border: 1px solid black; } QPushButton:hover { border: 1px solid darkgreen;}");
    ui->EditButton->setStyleSheet("QPushButton {border: 1px solid black; } QPushButton:hover { border: 1px solid blue;}");
    ui->DeleteButton->setStyleSheet("QPushButton {border: 1px solid black; } QPushButton:hover { border: 1px solid red;}");
}

void Categories::on_SetButton_clicked()
{
    QList<QListWidgetItem *> itemList = ui->listWidget->selectedItems();
    QString selected = itemList.at(0)->text();
    CurrentCategory = selected;
    emit ChangeCategory(CurrentCategory);
}

void Categories::onItemSelected(QListWidgetItem* item)
{
    QString value = item->text();
    for(const auto &x: categories)
    {
        if(x.value("taskCategories_Name").toString() == value)
        {
            if(x.value("taskCategories_User").toDouble() == 0)
            {
                ui->DeleteButton->setEnabled(false);
                ui->EditButton->setEnabled(false);
                break;
            }
            else
            {
                ui->DeleteButton->setEnabled(true);
                ui->EditButton->setEnabled(true);
                break;
            }
        }
    }
}


void Categories::on_EditButton_clicked()
{
    if(ui->EditButton->text() == "Edit")
    {
        QListWidgetItem *item = ui->listWidget->currentItem();
        item->setFlags(item->flags() | Qt::ItemIsEditable);
        ui->listWidget->editItem(item);
        ui->EditButton->setText("Ok");

        for(const auto &x: categories)
        {
            if(x.value("taskCategories_Name") == ui->listWidget->currentItem()->text())
            {
                chosenid = x.value("taskCategories_Id").toDouble();
                break;
            }
        }
    }
    else
    {
        if(ui->listWidget->currentItem()->text() != "")
        {
            ui->EditButton->setText("Edit");
            //EDIT OPERATION
            Operations::EditCategory(socket, chosenid, ui->listWidget->currentItem()->text());
        }
    }
}


void Categories::on_DeleteButton_clicked()
{
    for(const auto &x: categories)
    {
        if(x.value("taskCategories_Name") == ui->listWidget->currentItem()->text())
        {
            chosenid = x.value("taskCategories_Id").toDouble();
            break;
        }
    }

    Operations::DeleteCategory(socket, chosenid);
}


void Categories::on_AddNewButton_clicked()
{
    if(!ui->lineEdit->text().isEmpty())
    {
        Operations::AddCategory(socket, currentuserid, ui->lineEdit->text());
    }
}


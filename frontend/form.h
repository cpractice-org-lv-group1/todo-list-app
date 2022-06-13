#ifndef FORM_H
#define FORM_H

#include <QMainWindow>

namespace Ui {
class Form;
}

class Form : public QMainWindow
{
    Q_OBJECT

public:
    explicit Form(QWidget *parent = nullptr);
    ~Form();

signals:
     void backSignal();

private slots:
    void on_pushButton_clicked();

public slots:
    void slot(QString id);

private:
    Ui::Form *ui;
};

#endif // FORM_H

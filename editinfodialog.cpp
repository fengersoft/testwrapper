#include "editinfodialog.h"
#include "ui_editinfodialog.h"

EditInfoDialog::EditInfoDialog(QWidget* parent)
    : QDialog(parent)
    , ui(new Ui::EditInfoDialog)
{
    ui->setupUi(this);
}

EditInfoDialog::~EditInfoDialog()
{
    delete ui;
}

QString EditInfoDialog::getUserName()
{
    return ui->edtUserName->text();
}

QString EditInfoDialog::getPassWord()
{
    return ui->edtPassword->text();
}

void EditInfoDialog::setValue(QString username, QString password)
{
    ui->edtUserName->setText(username);
    ui->edtPassword->setText(password);
}

void EditInfoDialog::on_btnOk_clicked()
{
    accept();
}

void EditInfoDialog::on_btnCancel_clicked()
{
    reject();
}

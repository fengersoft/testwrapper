#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget* parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    db = nullptr;
    model = new QStandardItemModel(this);
    ui->lvData->setModel(model);
    QStringList labels;
    labels << "用户名"
           << "密码";
    model->setHorizontalHeaderLabels(labels);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_btnOpenDataBase_clicked()
{
    QString path = QApplication::applicationDirPath() + "/testdb.db";
    db = new SqliteWrapper(path, "testdb");
    db->open();
    bool b = db->isOpened();
    QString info = b == true ? "打开成功!" : "打开失败!";
    QMessageBox::information(this, "提示", info);
}

void MainWindow::on_btnShow_clicked()
{
    if (db == nullptr) {
        return;
    }
    db->select("select * from test", model);
}

void MainWindow::on_btnAdd_clicked()
{
    if (db == nullptr) {
        return;
    }
    EditInfoDialog* dlg = new EditInfoDialog();
    dlg->setWindowTitle("新增");
    int ret = dlg->exec();
    if (ret == QDialog::Accepted) {
        QString sql = "insert into test(username,password) values ('" + dlg->getUserName() + "','" + dlg->getPassWord() + "')";
        db->execute(sql);
        emit ui->btnShow->clicked();
    }
    delete dlg;
}

void MainWindow::on_btnEdit_clicked()
{
    QModelIndex index = ui->lvData->currentIndex();
    if (!index.isValid()) {
        return;
    }
    int n = index.row();
    EditInfoDialog* dlg = new EditInfoDialog();
    dlg->setWindowTitle("新增");
    dlg->setValue(model->item(n)->text(), model->item(n, 1)->text());
    int ret = dlg->exec();
    if (ret == QDialog::Accepted) {
        QString sql = "update test set username='" + dlg->getUserName() + "',password='" + dlg->getPassWord() + "' where username='" + model->item(n)->text() + "'";
        db->execute(sql);
        emit ui->btnShow->clicked();
    }
    delete dlg;
}

void MainWindow::on_btnDelete_clicked()
{
    QModelIndex index = ui->lvData->currentIndex();
    if (!index.isValid()) {
        return;
    }
    QString sql = "delete from test where username='" + model->item(index.row())->text() + "'";
    db->execute(sql);
    emit ui->btnShow->clicked();
}

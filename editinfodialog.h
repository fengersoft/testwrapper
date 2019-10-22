#ifndef EDITINFODIALOG_H
#define EDITINFODIALOG_H

#include <QDialog>

namespace Ui {
class EditInfoDialog;
}

class EditInfoDialog : public QDialog {
    Q_OBJECT

public:
    explicit EditInfoDialog(QWidget* parent = nullptr);
    ~EditInfoDialog();
    QString getUserName();
    QString getPassWord();
    void setValue(QString username, QString password);
private slots:
    void on_btnOk_clicked();

    void on_btnCancel_clicked();

private:
    Ui::EditInfoDialog* ui;
};

#endif // EDITINFODIALOG_H

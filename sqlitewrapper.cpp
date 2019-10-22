#include "sqlitewrapper.h"

SqliteWrapper::SqliteWrapper(QObject* parent)
    : QObject(parent)
{
}

SqliteWrapper::SqliteWrapper(QString fileName, QString dbName)
{
    this->fileName = fileName;
    this->dbName = dbName;
}

void SqliteWrapper::setFileName(QString fileName)
{
    this->fileName = fileName;
}

void SqliteWrapper::setDbName(QString dbName)
{
    this->dbName = dbName;
}

void SqliteWrapper::open()
{

    database = QSqlDatabase::addDatabase("QSQLITE", dbName);
    database.setDatabaseName(fileName);
    opened = database.open();
}

void SqliteWrapper::close()
{
    database.close();
    opened = false;
}

bool SqliteWrapper::isOpened()
{
    return opened;
}

void SqliteWrapper::select(QString sql, QStandardItemModel* model)
{
    model->removeRows(0, model->rowCount());
    QSqlQuery qry(sql, database);
    while (qry.next()) {
        QList<QStandardItem*> items;
        for (int i = 0; i < qry.record().count(); i++) {
            QStandardItem* item = new QStandardItem();
            item->setText(qry.value(i).toString());
            items.append(item);
        }
        model->appendRow(items);
    }
}

bool SqliteWrapper::execute(QString sql)
{
    QSqlQuery qry(database);
    bool ret = qry.exec(sql);
    if (!ret) {
        qDebug() << sql;
    }
    return ret;
}

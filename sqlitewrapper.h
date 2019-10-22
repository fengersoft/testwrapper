#ifndef SQLITEWRAPPER_H
#define SQLITEWRAPPER_H

#include <QObject>
#include <QStandardItemModel>
#include <QtDebug>
#include <QtSql/QSqlDatabase>
#include <QtSql/QSqlQuery>
#include <QtSql/QSqlRecord>

class SqliteWrapper : public QObject {
    Q_OBJECT
public:
    explicit SqliteWrapper(QObject* parent = nullptr);
    SqliteWrapper(QString fileName, QString dbName);
    ///设置Sqlite文件路径
    void setFileName(QString fileName);
    void setDbName(QString dbName);
    void open();
    void close();
    bool isOpened();
    ///显示数据
    void select(QString sql, QStandardItemModel* model);
    bool execute(QString sql);

private:
    QString fileName;
    QString dbName;
    QSqlDatabase database;
    bool opened;
signals:

public slots:
};

#endif // SQLITEWRAPPER_H

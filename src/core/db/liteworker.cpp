#include "liteworker.h"

#include <QCoreApplication>
#include <QSqlError>
#include <QUuid>

using namespace DB;

LiteWorker::LiteWorker() {}

QString LiteWorker::initConnection()
{
    m_connectionName = QUuid::createUuid().toString();

    auto db = QSqlDatabase::addDatabase(QStringLiteral("QSQLITE"), m_connectionName);
    db.setDatabaseName(dbPath());
    setDb(db);

    return db.open() ? QString{} : QStringLiteral("DB Connection Failed: ") % db.lastError().text();
}

QString LiteWorker::dbPath() const
{
    return QCoreApplication::applicationDirPath() % QStringLiteral("/system.db");
}
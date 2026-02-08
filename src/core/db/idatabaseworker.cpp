#include "idatabaseworker.h"

#include <QSqlError>
#include <QSqlQuery>
#include <QSqlRecord>

using namespace DB;

IDatabaseWorker::IDatabaseWorker(QObject* parent)
    : QObject{parent}
{
}

void IDatabaseWorker::process(const QString& sql, DbCallback callback, const QVariantMap& params)
{
    DbResponse response;

    if (!m_db.isOpen()) {
        const auto errMessage = initConnection();
        if (!errMessage.isEmpty()) {
            emit finished(response, callback);
            return;
        }
    }

    QSqlQuery query(m_db);
    query.prepare(sql);

    for (const auto& [key, value] : params.asKeyValueRange()) {
        query.bindValue(key, value);
    }

    if (query.exec()) {
        response.success = true;
        while (query.next()) {
            QVariantMap row;
            const auto record = query.record();
            for (int k = 0; k < record.count(); ++k) {
                row[record.fieldName(k)] = record.value(k);
            }
            response.data.push_back(row);
        }
    } else {
        response.success = false;
        response.error = query.lastError().text();
    }

    emit finished(response, callback);
}

void IDatabaseWorker::setDb(QSqlDatabase db) {
    m_db = db;
}

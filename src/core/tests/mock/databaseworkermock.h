#ifndef DATABASEWORKERMOCK_H
#define DATABASEWORKERMOCK_H

#include "core/db/idatabaseworker.h"
#include "core/db/types.h"

class MockDatabaseWorker : public DB::IDatabaseWorker
{
public:
    DB::DbResponse mockResponse;

    QString initConnection() override { return {}; }

public slots:
    void process(const QString& sql, DB::DbCallback callback, const QVariantMap& params) override
    {
        Q_UNUSED(sql);
        Q_UNUSED(params);

        emit finished(mockResponse, callback);
    }

};

#endif // DATABASEWORKERMOCK_H

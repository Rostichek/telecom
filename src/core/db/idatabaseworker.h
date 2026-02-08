#ifndef IDATABASEWORKER_H
#define IDATABASEWORKER_H

#include <QObject>
#include <QSqlDatabase>

#include "types.h"

namespace DB
{
    /**
     * @class   IDatabaseWorker
     * @brief   Abstract base class that defines the logic for a specific database backend (SQLite, Postgres, etc.)
     *
     * Concrete implementations (like LiteWorker) must override initConnection()
     * to set up the actual QSqlDatabase driver
     *
     * Usage Example (Creating a Concrete Worker):
     * @code
     * class LiteWorker : public IDatabaseWorker {
     *     QString initConnection() override {
     *         auto db = QSqlDatabase::addDatabase("QSQLITE", QUuid::createUuid().toString());
     *         db.setDatabaseName("app.db");
     *         setDb(db);
     *         return db.open() ? "" : db.lastError().text();
     *     }
     * };
     * @endcode
     */
    class IDatabaseWorker : public QObject
    {
        Q_OBJECT
    public:
        explicit IDatabaseWorker(QObject* parent = nullptr);

    signals:
        void finished(const DbResponse& data, DbCallback callback);

    public slots:
        void process(const QString& sql, DbCallback callback, const QVariantMap& params);

    protected:
        virtual QString initConnection() = 0;
        void setDb(QSqlDatabase db);

    private:
        QSqlDatabase m_db;
    };
} // namespace DB

#endif // IDATABASEWORKER_H

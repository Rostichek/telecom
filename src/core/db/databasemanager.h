#ifndef DATABASEMANAGER_H
#define DATABASEMANAGER_H

#include <QObject>
#include <QVariantMap>

#include "types.h"

class QThread;

namespace DB
{
    class IDatabaseWorker;
    /**
     * @class   DatabaseManager
     * @brief   A thread-safe Singleton that executes SQL queries asynchronously on a background thread
     *
     * Usage Example:
     * @code
     * QString sql = "SELECT * FROM countries WHERE name = :name";
     * QVariantMap params = {{":name", "Ukraine"}};
     *
     * DatabaseManager::instance()->query(sql, [](const DbResponse& response) {
     *    if (response.success) {
     *        // Handle response.data
     *    } else {
     *        qError() << response.error;
     *    }
     * }, params);
     * @endcode
     */
    class DatabaseManager : public QObject
    {
        Q_OBJECT
        Q_DISABLE_COPY_MOVE_X(DatabaseManager, "DatabaseManager is Singleton");

    public:
        ~DatabaseManager();

        /**
         * @brief Returns the global static instance
         */
        static DatabaseManager* instance();

        /**
         * @brief Queues a SQL query for execution on the background thread
         * @param sql       The SQL statement (e.g., "SELECT * FROM table")
         * @param callback  The slot to call with the results (DbResponse)
         * @param params    Optional map of named bindings (e.g., ":id" -> 1)
         * @note This function returns immediately. The callback is invoked later
         */
        void query(const QString& sql, DbCallback callback, const QVariantMap& params = {});

        /**
         * @brief Moves a worker in a thread
         * @param worker A pointer to a concrete worker (e.g., new LiteWorker{}).
         * The Manager takes ownership and moves it to the background thread
         */
        void initConnection(IDatabaseWorker* worker);

    private:
        explicit DatabaseManager(QObject* parent = nullptr);

    private:
        QThread* m_thread{nullptr};
        IDatabaseWorker* m_worker{nullptr};
    };
} // namespace DB

#endif // DATABASEMANAGER_H

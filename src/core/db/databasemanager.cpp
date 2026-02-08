#include "databasemanager.h"

#include "idatabaseworker.h"

#include <QCoreApplication>
#include <QThread>

using namespace DB;

DatabaseManager::DatabaseManager(QObject* parent)
    : QObject{parent}
{
    qRegisterMetaType<DbResponse>();
    qRegisterMetaType<DbCallback>();
}

DatabaseManager::~DatabaseManager()
{
    if (m_thread) {
        m_thread->quit();
        m_thread->wait();
    }
}

DatabaseManager* DatabaseManager::instance()
{
    static auto* instance = new DatabaseManager{};
    return instance;
}

void DatabaseManager::query(const QString& sql, DbCallback callback, const QVariantMap& params)
{
    if (!m_worker) {
        callback(
            DbResponse{.success = false,
                       .error = QStringLiteral("Manager hasn't been initialized. There is no worker to proceed the query")});
        return;
    }

    QMetaObject::invokeMethod(m_worker, "process", Qt::QueuedConnection, Q_ARG(QString, sql), Q_ARG(DbCallback, callback),
                              Q_ARG(QVariantMap, params));
}

void DatabaseManager::initConnection(IDatabaseWorker* worker)
{
    if (m_thread != nullptr) {
        return;
    }

    m_thread = new QThread(this);
    m_worker = worker;
    m_worker->moveToThread(m_thread);

    connect(m_worker, &IDatabaseWorker::finished, this, [](const DbResponse& data, DbCallback callback) {
        if (callback) callback(data);
    });

    connect(m_thread, &QThread::finished, m_worker, &QObject::deleteLater);
    connect(m_thread, &QThread::finished, m_worker, &QObject::deleteLater);

    m_thread->start();
}

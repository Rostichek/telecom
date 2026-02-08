#ifndef LITEWORKER_H
#define LITEWORKER_H

#include "idatabaseworker.h"

namespace DB
{
    class LiteWorker : public IDatabaseWorker
    {
    public:
        LiteWorker();

    protected:
        virtual QString initConnection() override;

    private:
        QString m_connectionName;

    private:
        QString dbPath() const;
    };
} // namespace DB

#endif // LITEWORKER_H

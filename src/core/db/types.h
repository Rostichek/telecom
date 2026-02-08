#ifndef TYPES_H
#define TYPES_H

#include <QObject>

namespace DB {
    using DbResult = std::vector<QVariantMap>;

    struct DbResponse {
        bool success { false };
        QString error;
        DbResult data;
    };

    using DbCallback = std::function<void(const DbResponse&)>;
}

Q_DECLARE_METATYPE(DB::DbCallback)
Q_DECLARE_METATYPE(DB::DbResponse)

#endif // TYPES_H

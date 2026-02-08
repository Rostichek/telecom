#ifndef ENTITIES_H
#define ENTITIES_H

#include <QString>
#include <QList>

struct Company {
    QString name;
    QString mcc;
    QString mnc;
};

struct Country {
    QString name;
    QString code;
    QList<Company> companies;
};

#endif // ENTITIES_H

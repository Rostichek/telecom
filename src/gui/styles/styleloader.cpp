#include "styleloader.h"

#include <QApplication>
#include <QFile>

void StyleLoader::attach(Style style)
{
    QString filepath = QStringLiteral(":/styles/styles/base/basestyle.qss");

    switch (style) {
    case Base: break;
    default:   qWarning() << "Unsupported style" << style;
    }

    QFile file(filepath);
    if (file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        qApp->setStyleSheet(file.readAll());
        file.close();
        return;
    }

    qWarning() << "Failed to load stylesheet:" << filepath;
}

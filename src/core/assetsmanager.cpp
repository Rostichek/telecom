#include "assetsmanager.h"
#include <QDebug>

AssetsManager* AssetsManager::instance()
{
    static auto* instance = new AssetsManager{};
    return instance;
}

QIcon AssetsManager::icon(const QString& name, const QString& type)
{
    const auto path = QStringLiteral(":/icons/%1.%2").arg(name, type);

    if (!m_cache.contains(path)) {
        QPixmap pix(path);
        auto* icon = new QIcon;
        icon->addPixmap(pix, QIcon::Normal);
        icon->addPixmap(pix, QIcon::Selected);
        m_cache.insert(path, icon);
    }

    const auto* icon = m_cache.object(path);
    if (icon->isNull()) {
        qWarning() << "Failed to find icon" << path;
        return {};
    }

    return *icon;
}
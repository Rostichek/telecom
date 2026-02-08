#ifndef ASSETSMANAGER_H
#define ASSETSMANAGER_H

#include <QCache>
#include <QIcon>
#include <QObject>

/**
 * @class   AssetsManager
 * @brief   A Singleton utility that provides gui with assets
 *
 * Usage Example:
 * @code
 * QIcon flag = AssetsManager::instance()->icon("germany", "png");
 *
 * @endcode
 */
class AssetsManager
{
    Q_DISABLE_COPY_MOVE_X(AssetsManager, "AssetsManager is Singleton");

public:
    /**
     * @brief Returns the global static instance of the manager
     */
    static AssetsManager* instance();

    /**
     * @brief Retrieves a QIcon from the cache or loads it from resources if missing
     * @param name The filename without extension (e.g., "germany")
     * @param type The file extension
     * @return A valid QIcon (cached) or an invalid icon if the file is not found
     */
    QIcon icon(const QString& name, const QString& type = QStringLiteral("png"));

private:
    static const auto s_cacheMaxSize{500};
    QCache<QString, QIcon> m_cache{s_cacheMaxSize};

private:
    AssetsManager() = default;
};

#endif // ASSETSMANAGER_H

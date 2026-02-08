#ifndef IDATALOADER_H
#define IDATALOADER_H

#include <QObject>

/**
 * @class   ILoaderSignals
 * @brief   A non-templated base class that defines the signal protocol for IDataLoader
 */
class ILoaderSignals : public QObject
{
    Q_OBJECT

public:
    explicit ILoaderSignals(QObject* parent = nullptr)
        : QObject(parent) {};

    virtual ~ILoaderSignals() = 0;

signals:
    /**
     * @brief Emitted when the asynchronous loading process completes successfully
     * The consumer should then call IDataLoader::getData() to retrieve the result.
     */
    void dataLoaded();

    /**
     * @brief Emitted when the loading process fails
     * @param message A user-readable description of the error
     */
    void errorOccurred(const QString& message);
};

/**
 * @class   IDataLoader
 * @brief   A generic interface for data fetching strategies (e.g., HTTP vs SQL)
 * @tparam  T The type of data to be loaded (e.g., QList<CountriesContainer>)
 *
 * Usage Example:
 * @code
 * IDataLoader<QList<QString>> *loader = new HTTPCountryNamesLoader{};
 *
 * connect(loader, &ILoaderSignals::dataLoaded, this, [loader](){
 *     auto data = loader->getData();
 *     // handle names list
 * });
 *
 * loader->load();
 * @endcode
 */
template <typename T>
class IDataLoader : public ILoaderSignals
{
public:
    explicit IDataLoader(QObject* parent = nullptr)
        : ILoaderSignals(parent) {};

    virtual void load() = 0;
    virtual const T& getData() const = 0;
};

inline ILoaderSignals::~ILoaderSignals() {}

#endif // IDATALOADER_H

#ifndef LOADERFACTORY_H
#define LOADERFACTORY_H

#include "dbcountryloader.h"
#include "idataloader.h"

#include <QDebug>

template<typename T>
concept IsLoader = requires { typename T::DataType; } && std::derived_from<T, IDataLoader<typename T::DataType>>;

class LoaderFactory {
public:
    template <IsLoader Interface>
    static Interface* create() {
        if constexpr (std::is_same_v<Interface, ICountryLoader>) {
            return new DBCountryLoader{};
        }

        qWarning() << "Thera is no loader defined for" << QMetaType::typeName(qMetaTypeId<Interface*>());
        return nullptr;
    }
};

#endif // LOADERFACTORY_H

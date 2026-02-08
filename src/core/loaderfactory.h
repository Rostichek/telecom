#ifndef LOADERFACTORY_H
#define LOADERFACTORY_H

#include "dbcountryloader.h"
#include "idataloader.h"

#include <QDebug>

/**
 * @concept IsLoader
 * @brief Constraints a type to be a valid data loader interface.
 *
 * @tparam T The interface type to validate.
 */
template <typename T>
concept IsLoader = requires
{
    typename T::DataType;
}
&&std::derived_from<T, IDataLoader<typename T::DataType>>;

/**
 * @class LoaderFactory
 * @brief A static factory for instantiating concrete data loaders based on their interfaces.
 *
 * The LoaderFactory abstracts the creation logic of data loaders, mapping abstract
 * interfaces (e.g., @c ICountryLoader) to their concrete implementations (e.g., @c DBCountryLoader).
 *
 * Usage Example:
 * @code
 * // Returns a new DBCountryLoader instance cast to ICountryLoader*
 * auto* loader = LoaderFactory::create<ICountryLoader>();
 * @endcode
 */
class LoaderFactory
{
public:
    /**
     * @brief Creates an instance of the specific loader implementation.
     *
     * This method resolves the concrete class type at compile-time using @c if @c constexpr checks.
     *
     * @tparam Interface The abstract interface class to instantiate. Must satisfy the @ref IsLoader concept.
     * @return A raw pointer to the new loader instance, or @c nullptr if no mapping is defined.
     *
     * @warning If the @c Interface is not mapped to a concrete class, a warning is logged
     * to the console and @c nullptr is returned.
     */
    template <IsLoader Interface>
    static Interface* create()
    {
        if constexpr (std::is_same_v<Interface, ICountryLoader>) {
            return new DBCountryLoader{};
        }

        qWarning() << "Thera is no loader defined for" << QMetaType::typeName(qMetaTypeId<Interface*>());
        return nullptr;
    }
};

#endif // LOADERFACTORY_H

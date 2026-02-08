#ifndef COUNTRYLOADER_H
#define COUNTRYLOADER_H

#include "core/entities.h"
#include "core/idataloader.h"

using CountryContainer = QList<Country>;

class ICountryLoader : public IDataLoader<CountryContainer>
{
public:
    using DataType = CountryContainer;

    explicit ICountryLoader(QObject* parent = nullptr)
        : IDataLoader<CountryContainer>{parent} {};

    const CountryContainer& getData() const override { return m_data; }

protected:
    CountryContainer m_data;
};

#endif // COUNTRYLOADER_H

#ifndef DBCOUNTRYLOADER_H
#define DBCOUNTRYLOADER_H

#include "countryloader.h"

class DBCountryLoader : public ICountryLoader
{
public:
    explicit DBCountryLoader(QObject* parent = nullptr);

    void load() override;

private:
    void parseResponse(const std::vector<QVariantMap>& response);
};

#endif // DBCOUNTRYLOADER_H

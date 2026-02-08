#include "dbcountryloader.h"

#include "core/db/databasemanager.h"
#include "core/entities.h"

using namespace DB;

DBCountryLoader::DBCountryLoader(QObject* parent)
    : ICountryLoader{parent} {};

void DBCountryLoader::load()
{
    const static auto select = QStringLiteral(
        "SELECT DISTINCT c.name AS country, c.code AS code, o.name AS operator, o.mcc AS mcc, o.mnc AS mnc FROM "
        "countries AS c INNER JOIN operators o ON o.mcc = c.mcc ORDER BY country, operator");

    auto callback = [this](const DbResponse& response) {
        if (!response.success) {
            emit errorOccurred(response.error);
            return;
        }
        parseResponse(response.data);
        emit dataLoaded();
    };

    DatabaseManager::instance()->query(select, callback);
}

void DBCountryLoader::parseResponse(const std::vector<QVariantMap>& response)
{
    QString lastCountryName;
    std::unique_ptr<Country> country;

    for (const auto row : response) {
        const auto countryName = row.value(QStringLiteral("country")).toString();

        if (lastCountryName != countryName) {
            if (!lastCountryName.isEmpty()) {
                m_data.append(*country.get());
            }
            country = std::make_unique<Country>();

            lastCountryName = countryName;
            country->name = lastCountryName;
            country->code = row.value(QStringLiteral("code")).toString();
        }

        Company company{.name = row.value(QStringLiteral("operator")).toString(),
                        .mcc = row.value(QStringLiteral("mcc")).toString(),
                        .mnc = row.value(QStringLiteral("mnc")).toString()};

        if (!company.name.isEmpty()) {
            country->companies.emplaceBack(std::move(company));
        }
    }

    if (country) {
        m_data.append(*country);
    }
}

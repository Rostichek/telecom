#include "mobileoperatorsmodel.h"

#include "core/countryloader.h"
#include "core/assetsmanager.h"

#include <QFont>

namespace
{
    const auto COUNTRY_ID = quintptr(-1);
}

MobileOperatorsModel::MobileOperatorsModel(ICountryLoader* source, QObject* parent)
    : QAbstractItemModel(parent),
      m_loader(source)
{
    m_loader->setParent(this);
    m_loader->load();

    connect(m_loader, &ICountryLoader::dataLoaded, this, [this] {
        beginResetModel();
        endResetModel();
    });
}

int MobileOperatorsModel::rowCount(const QModelIndex& parent) const
{
    if (!parent.isValid()) {
        return m_loader->getData().count();
    }

    if (parent.internalId() == COUNTRY_ID) {
        int countryIndex = parent.row();
        if (countryIndex < 0 || countryIndex >= m_loader->getData().count()) return 0;

        return m_loader->getData()[countryIndex].companies.count();
    }

    return 0;
}

QModelIndex MobileOperatorsModel::index(int row, int column, const QModelIndex& parent) const
{
    if (!hasIndex(row, column, parent)) return QModelIndex();

    if (!parent.isValid()) {
        return createIndex(row, column, COUNTRY_ID);
    }

    if (parent.internalId() == COUNTRY_ID) {
        quintptr countryIndex = parent.row();
        return createIndex(row, column, countryIndex);
    }

    return QModelIndex();
}

QModelIndex MobileOperatorsModel::parent(const QModelIndex& child) const
{
    if (!child.isValid()) return QModelIndex();

    quintptr id = child.internalId();

    if (id == COUNTRY_ID) {
        return QModelIndex();
    }

    return createIndex(static_cast<int>(id), 0, COUNTRY_ID);
}

QVariant MobileOperatorsModel::data(const QModelIndex& index, int role) const
{
    if (!index.isValid()) return QVariant();

    quintptr id = index.internalId();
    static const QFont boldFont = [] {
        QFont f;
        f.setBold(true);
        return f;
    }();

    if (id == COUNTRY_ID) {
        const auto& country = m_loader->getData().at(index.row());
        switch (role) {
        case Qt::DisplayRole:    return QStringLiteral("%1 (%2)").arg(country.name, country.code);
        case Qt::DecorationRole: return AssetsManager::instance()->icon(country.code);
        case Qt::FontRole:       return boldFont;
        default:                 return {};
        }
    }

    const auto& company = m_loader->getData().at(id).companies[index.row()];
    switch (role) {
    case Qt::DisplayRole:    return QStringLiteral("%1 (%2-%3)").arg(company.name, company.mcc, company.mnc); break;
    case Qt::DecorationRole: return AssetsManager::instance()->icon(QStringLiteral("%2_%3").arg(company.mcc, company.mnc));
    default:                 return {};
    }
}
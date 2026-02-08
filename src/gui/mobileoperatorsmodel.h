#ifndef MOBILEOPERATORSMODEL_H
#define MOBILEOPERATORSMODEL_H

#include <QAbstractItemModel>

class ICountryLoader;

class MobileOperatorsModel : public QAbstractItemModel
{
public:
    explicit MobileOperatorsModel(ICountryLoader* source, QObject* parent = nullptr);

    QModelIndex index(int row, int column, const QModelIndex &parent = QModelIndex()) const override;
    QModelIndex parent(const QModelIndex &child) const override;
    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    int columnCount(const QModelIndex &parent = QModelIndex()) const override { return 1; }
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;

private:
    ICountryLoader* const m_loader;
};

#endif // MOBILEOPERATORSMODEL_H

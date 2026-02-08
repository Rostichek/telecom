#include "mobileoperatorswidget.h"

#include "mobileoperatorsmodel.h"
#include "core/countryloader.h"

#include <QVBoxLayout>
#include <QStyledItemDelegate>

MobileOperatorsWidget::MobileOperatorsWidget(ICountryLoader* sourceDataLoader, QWidget* parent)
    : QWidget(parent),
    m_operatorsModel(new MobileOperatorsModel(sourceDataLoader, this)),
    m_treeView(new QTreeView(this))
{
    sourceDataLoader->setParent(this);

    QVBoxLayout* layout = new QVBoxLayout(this);
    layout->setContentsMargins(0, 0, 0, 0);

    m_treeView->setHeaderHidden(true);
    m_treeView->setModel(m_operatorsModel);
    m_treeView->setItemDelegate(new QStyledItemDelegate(m_treeView));

    layout->addWidget(m_treeView);


}

MobileOperatorsWidget::~MobileOperatorsWidget() = default;

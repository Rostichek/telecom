#ifndef MOBILEOPERATORSWIDGET_H
#define MOBILEOPERATORSWIDGET_H

#include <QTreeView>
#include <QWidget>

class MobileOperatorsModel;
class ICountryLoader;

class MobileOperatorsWidget : public QWidget
{
    Q_OBJECT
public:
    explicit MobileOperatorsWidget(ICountryLoader* sourceDataLoader, QWidget* parent = nullptr);
    ~MobileOperatorsWidget();

private:
    QTreeView* m_treeView;
    MobileOperatorsModel* m_operatorsModel;
};

#endif // MOBILEOPERATORSWIDGET_H

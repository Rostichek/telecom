#include "mainwindow.h"

#include "mobileoperatorswidget.h"
#include "core/loaderfactory.h"
#include "styles/styleloader.h"

#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget* parent)
    : QMainWindow(parent),
      m_ui(new Ui::MainWindow{}),
    m_mobileOperators(new MobileOperatorsWidget{LoaderFactory::create<ICountryLoader>(), this})
{
    StyleLoader::attach(StyleLoader::Base);

    m_ui->setupUi(this);
    setCentralWidget(m_mobileOperators);
}

MainWindow::~MainWindow() {}
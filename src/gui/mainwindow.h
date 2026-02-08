#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

namespace Ui
{
    class MainWindow;
}

class MobileOperatorsWidget;

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget* parent = nullptr);
    ~MainWindow();

private:
    const std::unique_ptr<Ui::MainWindow> m_ui;
    MobileOperatorsWidget* m_mobileOperators;
};
#endif // MAINWINDOW_H

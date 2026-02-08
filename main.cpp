#include "gui/mainwindow.h"

#include "core/db/databasemanager.h"
#include "core/db/liteworker.h"

#include <QApplication>
#include <QFile>

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    app.setApplicationDisplayName(QStringLiteral("Telecom"));

    QFile stylesheetFile(QStringLiteral(":/src/gui/styles/base/basestyle.qss"));
    if (stylesheetFile.open(QIODevice::ReadOnly | QIODevice::Text)) {
        app.setStyleSheet(stylesheetFile.readAll());
        stylesheetFile.close();
    }

    DB::DatabaseManager::instance()->initConnection(new DB::LiteWorker{});

    MainWindow mainWindow;
    mainWindow.show();

    return app.exec();
}

#include "gui/mainwindow.h"

#include "core/db/databasemanager.h"
#include "core/db/liteworker.h"

#include <QApplication>
#include <QFile>

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    app.setApplicationDisplayName(QStringLiteral("Telecom"));

    DB::DatabaseManager::instance()->initConnection(new DB::LiteWorker{});

    MainWindow mainWindow;
    mainWindow.show();

    return app.exec();
}

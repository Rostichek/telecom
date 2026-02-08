#include <QDebug>
#include <QSignalSpy>
#include <QSqlDatabase>
#include <QSqlError>
#include <QSqlQuery>
#include <QVariant>
#include <gtest/gtest.h>

#include "core/db/databasemanager.h"
#include "core/dbcountryloader.h"
#include "mock/databaseworkermock.h"

namespace DB
{
    class DBCountryLoaderTest : public ::testing::Test
    {
    protected:
        void SetUp() override
        {
            m_mockWorker = new MockDatabaseWorker();
            DB::DatabaseManager::instance()->initConnection(m_mockWorker);
        }

        void TearDown() override { DB::DatabaseManager::resetInstance(); }

        MockDatabaseWorker* m_mockWorker;
    };

    TEST_F(DBCountryLoaderTest, 01_parse)
    {
        QVariantMap row1{{"country", "Ukraine"}, {"code", "UA"}, {"operator", "Kyivstar"}, {"mcc", "255"}, {"mnc", "01"}};
        QVariantMap row2{{"country", "Ukraine"}, {"code", "UA"}, {"operator", "Vodafone"}, {"mcc", "255"}, {"mnc", "02"}};
        QVariantMap row3{{"country", "Poland"}, {"code", "PL"}, {"operator", "Orange"}, {"mcc", "260"}, {"mnc", "03"}};

        m_mockWorker->mockResponse = {.success = true, .data = {row3, row1, row2}};

        DBCountryLoader loader;
        QSignalSpy spySuccess(&loader, &DBCountryLoader::dataLoaded);
        QSignalSpy spyError(&loader, &DBCountryLoader::errorOccurred);

        loader.load();

        ASSERT_TRUE(spySuccess.wait(1000));
        ASSERT_EQ(spyError.count(), 0);

        const auto& data = loader.getData();
        ASSERT_EQ(data.size(), 2);

        EXPECT_EQ(data[0].name, "Poland");
        EXPECT_EQ(data[0].companies.size(), 1);

        EXPECT_EQ(data[1].name, "Ukraine");
        EXPECT_EQ(data[1].companies.size(), 2);
        EXPECT_EQ(data[1].companies[0].name, "Kyivstar");
        EXPECT_EQ(data[1].companies[1].name, "Vodafone");
    }

    TEST_F(DBCountryLoaderTest, 02_parseEmpty)
    {
        m_mockWorker->mockResponse = {.success = true, .data = {}};

        DBCountryLoader loader;
        QSignalSpy spy(&loader, &DBCountryLoader::dataLoaded);

        loader.load();

        ASSERT_TRUE(spy.wait());
        EXPECT_TRUE(loader.getData().isEmpty());
    }

    TEST_F(DBCountryLoaderTest, 03_parseWithError)
    {
        m_mockWorker->mockResponse = {.success = false};

        DBCountryLoader loader;
        QSignalSpy spySuccess(&loader, &DBCountryLoader::dataLoaded);
        QSignalSpy spyError(&loader, &DBCountryLoader::errorOccurred);

        loader.load();

        ASSERT_TRUE(spyError.wait(1000));
        ASSERT_EQ(spySuccess.count(), 0);
    }
} // namespace DB
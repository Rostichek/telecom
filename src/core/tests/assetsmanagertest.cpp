#include "core/assetsmanager.h"

#include "gtest/gtest.h"

class AssetsManagerTest : public testing::Test {};

TEST_F(AssetsManagerTest, 01_instance)
{
    AssetsManager* ptr1 = AssetsManager::instance();
    AssetsManager* ptr2 = AssetsManager::instance();

    ASSERT_NE(ptr1, nullptr);
    EXPECT_EQ(ptr1, ptr2);
}

TEST_F(AssetsManagerTest, 02_missingIcon)
{
    QIcon icon = AssetsManager::instance()->icon("non_existent_random_name", "png");
    EXPECT_TRUE(icon.isNull());

    icon = AssetsManager::instance()->icon("green", "svg");
    EXPECT_TRUE(icon.isNull());
}

TEST_F(AssetsManagerTest, 03_validIcon)
{
    QIcon icon = AssetsManager::instance()->icon("green", "png");
    EXPECT_FALSE(icon.isNull());
}

TEST_F(AssetsManagerTest, 04_caching)
{
    AssetsManager::instance()->m_cache.remove(":/icons/green.png");
    int initialCount = AssetsManager::instance()->m_cache.count();

    QIcon icon1 = AssetsManager::instance()->icon("green");

    EXPECT_FALSE(icon1.isNull());
    EXPECT_TRUE(AssetsManager::instance()->m_cache.contains(":/icons/green.png"));
    EXPECT_EQ(AssetsManager::instance()->m_cache.count(), initialCount + 1);

    QIcon icon2 = AssetsManager::instance()->icon("green");

    EXPECT_EQ(AssetsManager::instance()->m_cache.count(), initialCount + 1);
    EXPECT_EQ(icon1.cacheKey(), icon2.cacheKey());
}
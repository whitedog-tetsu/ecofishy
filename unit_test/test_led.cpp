/*************************************************************************//**
 * @file test_system.cpp
 * @author typeR
 * @brief 
 * @version 0.1
 * @date 2020-01-21
 * 
 * @copyright Copyright (c) 2020
 * 
 ****************************************************************************/
#include "gtest/gtest.h" 
#include "system.h"
#include "LED_lib.h"
#include <limits.h>


class LED_lib : public ::testing::Test
{
protected:
    virtual void SetUp()
    {

    }
    virtual void TearDown()
    {

    }
};

/*************************************************************************//**
 * @brief Test initial state value
 * 
 ****************************************************************************/
TEST_F(LED_lib, led_on_OK1)
{   
    EXPECT_EQ(OK, led_on(PIN_LED_BLU));
}


TEST_F(LED_lib, led_on_OK2)
{   
    EXPECT_EQ(OK, led_on(PIN_LED_RED));
}

TEST_F(LED_lib, led_on_NG1)
{   
    EXPECT_EQ(NG, led_on(8));
}

TEST_F(LED_lib, led_on_NG2)
{   
    EXPECT_EQ(NG, led_on(12));
}


TEST_F(LED_lib, led_off_OK1)
{   
    EXPECT_EQ(OK, led_off(PIN_LED_BLU));
}


TEST_F(LED_lib, led_off_OK2)
{   
    EXPECT_EQ(OK, led_off(PIN_LED_RED));
}

TEST_F(LED_lib, led_off_NG1)
{   
    EXPECT_EQ(NG, led_off(8));
}

TEST_F(LED_lib, led_off_NG2)
{   
    EXPECT_EQ(NG, led_off(12));
}

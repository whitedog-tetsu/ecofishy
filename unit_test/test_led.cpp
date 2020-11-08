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
TEST_F(LED_lib, led_pin_init)
{   
//    EXPECT_EQ(, led_all_on());
}


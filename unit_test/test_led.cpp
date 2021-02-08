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

/*************************************************************************//**
 * @brief Construct a new test f object
 * 
 *         input   output   
 * pin     9        OK    must
 * pin     10       OK    OK/NGの境界でテストを実施しているので、実施なくてもよい。
 * pin     11       OK    must
 * pin     8        NG    must
 * pin     12       NG    must
 * 
 * brt     0        OK    must
 * brt     128      OK    must
 * brt     255      OK    must
 * brt     -1       NG    must
 * brt     256      NG    must
 *         
 *               pin   brt
 * pattern1      OK    OK   must
 * pattern2      NG    OK   must
 * pattern3      OK    NG   must
 * pattern4      NG    NG   これはどちらが原因でNGになったか分からないので、実施しない。
 * 
 *  pin
 * 1 led_brightness(9 , 0)   OK/OK -> OK
 * 2 led_brightness(11 , 0)  OK/OK -> OK
 * 3 led_brightness(8 , 0)   NG/OK -> NG
 * 4 led_brightness(12 , 0)  NG/OK -> NG
 * 
 * 5 led_brightness(9 , 255)   OK/OK -> OK
 * 6 led_brightness(11 , 255)  OK/OK -> OK
 * 7 led_brightness(8 , 255)   NG/OK -> NG
 * 8 led_brightness(12 , 255)  NG/OK -> NG
 * 
 * 
 * 
 *  brt 
 * 9  led_brightness(9 , 255)  OK/OK -> OK
 * 10 led_brightness(9 , 128)  OK/OK -> OK
 * 11 led_brightness(9 , -1)   OK/NG -> NG
 * 12 led_brightness(9 , 256)  OK/NG -> NG
 * 
 * 13 led_brightness(11 , 255)  OK/OK -> OK
 * 14 led_brightness(11 , 128)  OK/OK -> OK
 * 15 led_brightness(11 , -1)   OK/NG -> NG
 * 16 led_brightness(11 , 256)  OK/NG -> NG
 * 
 * 
 * 
 ****************************************************************************/

TEST_F(LED_lib, led_brightness_pin1)
{   
    EXPECT_EQ(OK, led_brightness(9 , 0));
}

TEST_F(LED_lib, led_brightness_pin2)
{   
    EXPECT_EQ(OK, led_brightness(11 , 0));
}
TEST_F(LED_lib, led_brightness_pin3)
{   
    EXPECT_EQ(NG, led_brightness(8 , 0));
}
TEST_F(LED_lib, led_brightness_pin4)
{   
    EXPECT_EQ(NG, led_brightness(12 , 0));
}
TEST_F(LED_lib, led_brightness_pin5)
{   
    EXPECT_EQ(OK, led_brightness(9 , 255));
}
TEST_F(LED_lib, led_brightness_pin6)
{   
    EXPECT_EQ(OK, led_brightness(9 , 255));
}
TEST_F(LED_lib, led_brightness_pin7)
{   
    EXPECT_EQ(NG, led_brightness(9 , -1));
}
TEST_F(LED_lib, led_brightness_pin8)
{   
    EXPECT_EQ(NG, led_brightness(9 , 256));
}


TEST_F(LED_lib, led_brightness_pin9)
{   
    EXPECT_EQ(OK, led_brightness(9 , 255));
}

TEST_F(LED_lib, led_brightness_pin10)
{   
    EXPECT_EQ(OK, led_brightness(11 , 255));
}
TEST_F(LED_lib, led_brightness_pin11)
{   
    EXPECT_EQ(NG, led_brightness(8 , 255));
}
TEST_F(LED_lib, led_brightness_pin12)
{   
    EXPECT_EQ(NG, led_brightness(12 , 255));
}
TEST_F(LED_lib, led_brightness_pin13)
{   
    EXPECT_EQ(OK, led_brightness(11 , 255));
}
TEST_F(LED_lib, led_brightness_pin14)
{   
    EXPECT_EQ(OK, led_brightness(11 , 255));
}
TEST_F(LED_lib, led_brightness_pin15)
{   
    EXPECT_EQ(NG, led_brightness(11 , -1));
}
TEST_F(LED_lib, led_brightness_pin16)
{   
    EXPECT_EQ(NG, led_brightness(11 , 256));
}

TEST_F(LED_lib, judge_led_pin1)
{   
    EXPECT_EQ(OK, judge_led_pin(9, PIN_LED_BLU, PIN_LED_RED));
}

TEST_F(LED_lib, judge_led_pin2)
{   
    EXPECT_EQ(OK, judge_led_pin(11, PIN_LED_BLU, PIN_LED_RED));
}

TEST_F(LED_lib, judge_led_pin3)
{   
    EXPECT_EQ(NG, judge_led_pin(8, PIN_LED_BLU, PIN_LED_RED));
}

TEST_F(LED_lib, judge_led_pin4)
{   
    EXPECT_EQ(NG, judge_led_pin(12, PIN_LED_BLU, PIN_LED_RED));
}



/*************************************************************************//**
 * @brief Construct a new test f object
 * 
 * 
 *  pin
 *     OK case
 *     pin     pulse_time     repeat     EXPECT
 *     9        10             1          OK
 *     11       10             1          OK
 * 
 *     NG case
 *     pin     pulse_time     repeat     EXPECT
 *     8        10             1          NG
 *     12       10             1          NG
 *     
 * 
 * 
 * 
 ****************************************************************************/

TEST_F(LED_lib, led_blink1)
{   
    EXPECT_EQ(OK, led_blink_msec(9 , 1000 , 1 ));
}

TEST_F(LED_lib, led_blink2)
{   
    EXPECT_EQ(NG, led_blink_msec(9 , 9 , 1 ));
}

TEST_F(LED_lib, led_blink3)
{   
    EXPECT_EQ(NG, led_blink_msec(9 , 1001 , 1 ));
}


TEST_F(LED_lib, led_blink4)
{   
    EXPECT_EQ(OK, led_blink_msec(9 , 10 , 10 ));
}


TEST_F(LED_lib, led_blink5)
{   
    EXPECT_EQ(NG, led_blink_msec(9 , 10 , 0 ));
}

TEST_F(LED_lib, led_blink6)
{   
    EXPECT_EQ(NG, led_blink_msec(9 , 10 , 11 ));
}


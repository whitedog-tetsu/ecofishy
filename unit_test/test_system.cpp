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
#include "test_system.hpp"
#include <limits.h>


class system : public ::testing::Test
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
TEST_F(system, initial_state)
{
    EXPECT_EQ(OP_STATE_DEFAULT, get_last_state());
}

/*************************************************************************//**
 * @brief Test set state normal
 * 
 ****************************************************************************/
TEST_F(system, set_measure_state)
{
    set_last_state(COMPUTE_MEASURE_STATE);
    EXPECT_EQ(COMPUTE_MEASURE_STATE, get_last_state());
}

/*************************************************************************//**
 * @brief Test set state normal
 * 
 ****************************************************************************/
TEST_F(system, set_wait_state)
{
    set_last_state(COMPUTE_WAIT_STATE);
    EXPECT_EQ(COMPUTE_WAIT_STATE, get_last_state());
}


/*************************************************************************//**
 * @brief Test set state normal
 * 
 ****************************************************************************/
TEST_F(system, set_init_state)
{
    set_last_state(INIT_STATE);
    EXPECT_EQ(INIT_STATE, get_last_state());
}

/*************************************************************************//**
 * @brief Construct a new test f object
 * 
 ****************************************************************************/
TEST_F(system, set_last_state_1)
{
    set_last_state(OP_STATE_DEFAULT);
    EXPECT_EQ(OP_STATE_DEFAULT, get_last_state());
}

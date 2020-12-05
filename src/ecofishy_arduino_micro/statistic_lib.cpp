/*************************************************************************//**
 * @file statistic_lib.cpp
 * @author typeR
 * @brief 
 * @version 0.1
 * @date 2020-12-06
 * 
 * @copyright Copyright (c) 2020
 * 
 ****************************************************************************/
#include "statistic_lib.h"
#include <math.h>
#include <stdio.h>

/*************************************************************************//**
 * @brief 
 * 
 * @param data 
 * @param data_size 
 * @return double 
 ****************************************************************************/
double calc_sum_array(void* data, const int data_size)
{
    statistic_data_t* buf = (statistic_data_t*)data;
    int buf_index = 0;
    double sum = 0.0;

    for(buf_index = 0; buf_index < data_size; buf_index++) {
        sum += buf[buf_index];
        printf("%d %f %f\n", buf_index, buf[buf_index], sum);
    }

    return sum;
}

/*************************************************************************//**
 * @brief 
 * 
 * @param data 
 * @param data_size 
 * @return double 
 ****************************************************************************/
double calc_sqr_sum_array(void* data, const int data_size)
{
    statistic_data_t* buf = (statistic_data_t*)data;
    int buf_index = 0;
    double sqr_sum = 0.0;

    for(buf_index = 0; buf_index < data_size; buf_index++) {
        sqr_sum += (buf[buf_index] * buf[buf_index]);
        printf("%d %f %f\n", buf_index, buf[buf_index], sqr_sum);
    }

    return sqr_sum;

}

/*************************************************************************//**
 * @brief 
 * 
 * @param sum 
 * @param sqr_sum 
 * @param data_size 
 * @return double 
 ****************************************************************************/
double calc_std_dev(double sum, double sqr_sum, const int data_size)
{
    double std_dev = 0.0;
    double var = 0.0;

    var = calc_var(sqr_sum, sum, data_size);
    std_dev = sqrt(var);

    return std_dev;
}

/*************************************************************************//**
 * @brief 
 * 
 * @param sum 
 * @param sum_size 
 * @return double 
 ****************************************************************************/
double calc_ave(double sum, int sum_size)
{
    return  (sum / (double)sum_size);
}

double calc_rss(double sqr_sum, double sum, int sum_size)
{
    return (sqr_sum - ((sum * sum) / (double)sum_size));
}

/*************************************************************************//**
 * @brief 
 * 
 * @param sqr_sum 
 * @param sum 
 * @param sum_size 
 * @return double 
 ****************************************************************************/
double calc_var(double sqr_sum, double sum, int sum_size)
{
    double rss = 0.0;
    
    rss = calc_rss(sqr_sum, sum, sum_size);

    return (rss / (double)(sum_size - 1));
}

/*************************************************************************//**
 * @brief 
 * 
 * @param data 
 * @param data_size 
 * @return double 
 ****************************************************************************/
double calc_std_dev_array(void* data, const int data_size)
{
    double sum = 0.0;
    double sqr_sum = 0.0;
    double std_dev = 0.0;
    
    
    sum = calc_sum_array(data, data_size);
    sqr_sum = calc_sqr_sum_array(data, data_size);
    std_dev = calc_std_dev(sum, sqr_sum, data_size);

    return std_dev;
}

/*************************************************************************//**
 * @brief 
 * 
 * @param data 
 * @param data_size 
 * @return double 
 ****************************************************************************/
double calc_ave_array(void* data, const int data_size)
{
    double sum = 0.0;
    double ave = 0.0;
      
    sum = calc_sum_array(data, data_size);
    ave = calc_ave(sum, data_size);

    return ave;
}

/*************************************************************************//**
 * @brief 
 * 
 * @param data 
 * @param data_size 
 * @return double 
 ****************************************************************************/
double calc_rss_array(void* data, const int data_size)
{
    double rss = 0.0;
    double sum = 0.0;
    double sqr_sum = 0.0;
    
    sum = calc_sum_array(data, data_size);
    sqr_sum = calc_sqr_sum_array(data, data_size);
    rss = calc_rss(sqr_sum, sum, data_size);

    return rss;
}

/*************************************************************************//**
 * @brief 
 * 
 * @param data 
 * @param data_size 
 * @return double 
 ****************************************************************************/
double calc_var_array(void* data, const int data_size)
{
    double sum = 0.0;
    double sqr_sum = 0.0;
    double var = 0.0;
      
    sum = calc_sum_array(data, data_size);
    sqr_sum = calc_sqr_sum_array(data, data_size);
    var = calc_var(sqr_sum, sum, data_size);

    return var;
}


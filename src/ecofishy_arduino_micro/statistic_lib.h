#ifndef STATISTIC_LIB_H
#define STATISTIC_LIB_H

#ifdef __cplusplus
extern "C" {
#endif // __cplusplus

#define statistic_data_t double


extern double calc_ave(double sum, int sum_size);
extern double calc_var(double sqr_sum, double sum, int sum_size);
extern double calc_rss(double sqr_sum, double sum, int sum_size);
extern double calc_std_dev(double sum, double sqr_sum, const int data_size);

extern double calc_sum_array(void* buf, const int buf_size);
extern double calc_sqr_sum_array(void* buf, const int buf_size);
extern double calc_ave_array(void* data, const int data_size);
extern double calc_rss_array(void* data, const int data_size);
extern double calc_var_array(void* data, const int data_size);
extern double calc_std_dev_array(void* data, int data_size);


#ifdef __cplusplus
}
#endif // __cplusplus



#endif // STATISTIC_LIB_H

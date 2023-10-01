#ifndef SRC_S21_DECIMAL_H_
#define SRC_S21_DECIMAL_H_

#include <math.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BIT 8
#define SIZE_BITS 4
#define NUM_255 255
#define TRUE 1
#define FALSE 0

#define S21_MAX_UINT 4294967295

#define MAX_BITS_VAL 4294967295U
#define is_fin(x) __builtin_isfinite(x)  // eps in math.h
#define is_nan(x) __builtin_isnan(x)
#define is_inf(x) __builtin_isinf(x)

typedef enum operator{
  PLUS,  // Сложение
  MIN,   // Вычитание
  MUL,   // Умножение
  DIV    // Деление
}
operator;

// Индексы элементов массива bits в структуре s21_decimal
enum { LOW, MID, HIGH, SCALE };

// Результаты преобразования
typedef enum {
  CONVERTATION_OK,  // Преобразование выполнено успешно
  CONVERTATION_ERROR  // Ошибка преобразования
} conv_result;

// Результаты арифметических операций
typedef enum {
  OK,           // Операция выполнена успешно
  INF,          // Бесконечность
  MIN_INF,      // Минус бесконечность
  DIV_BY_ZERO,  // Деление на ноль
  ERROR         // Ошибка
} arith_result;

// Результаты других операций
typedef enum {
  OTHER_OK,    // Операция выполнена успешно
  OTHER_ERROR  // Ошибка
} other_result;

// Структура для представления числа в формате s21_decimal
typedef struct s21_decimal {
  unsigned int bits[4];  // Массив битов числа
} s21_decimal;

int format_div(s21_decimal *val_1, s21_decimal *val_2);
void add_help(s21_decimal v_1, s21_decimal v_2, s21_decimal *result);
int s21_add(s21_decimal v_1, s21_decimal v_2, s21_decimal *result);

void sub_help(s21_decimal v_1, s21_decimal v_2, s21_decimal *result);
int s21_sub(s21_decimal v_1, s21_decimal v_2, s21_decimal *result);

int s21_mul(s21_decimal v_1, s21_decimal v_2, s21_decimal *result);
int s21_div(s21_decimal v_1, s21_decimal v_2, s21_decimal *result);
int s21_mod(s21_decimal v_1, s21_decimal v_2, s21_decimal *result);

int s21_from_decimal_to_int(s21_decimal src, int *dst);
int s21_from_int_to_decimal(int src, s21_decimal *dst);
int s21_from_float_to_decimal(float src, s21_decimal *dst);
int s21_float_format(int integer, float fract, s21_decimal *value);
int s21_from_decimal_to_float(s21_decimal src, float *dst);
void add_in_start_chat(char *str, char ch);

s21_decimal s21_string_to_decimal(char *string);
void s21_decimal_to_string(char *dst, s21_decimal src);

int s21_equal_compare(s21_decimal dec1, s21_decimal dec2);
int s21_easy_compare(s21_decimal dec1, s21_decimal dec2);
void s21_decimal_null_sign(s21_decimal *temp);
int s21_is_less(s21_decimal dec1, s21_decimal dec2);  // меньше
int s21_is_less_or_equal(s21_decimal dec1,
                         s21_decimal dec2);  // меньше ли равно
int s21_is_greater(s21_decimal dec1, s21_decimal dec2);  // больше
int s21_is_greater_or_equal(s21_decimal dec1,
                            s21_decimal dec2);  // больше или равно
int s21_is_equal(s21_decimal dec1, s21_decimal dec2);      // равно
int s21_is_not_equal(s21_decimal dec1, s21_decimal dec2);  // неравно

int s21_negate(s21_decimal value,
               s21_decimal *result);  // Возвращает результат умножения
                                      // указанного Decimal на -1.
int s21_floor(s21_decimal value,
              s21_decimal *result);  // Округляет указанное Decimal число до
                                     // ближайшего целого числа в сторону
                                     // отрицательной бесконечности.
int s21_round(
    s21_decimal value,
    s21_decimal *result);  // Округляет Decimal до ближайшего целого числа.
int s21_truncate(s21_decimal value,
                 s21_decimal *result);  // Возвращает целые цифры указанного
                                        // Decimal числа; любые дробные цифры
                                        // отбрасываются, включая конечные нули.

void scale_is_equal(s21_decimal *dst1, s21_decimal *dst2);
void make_lower_scale(s21_decimal *val);
int buffer_overflow(s21_decimal val_1, s21_decimal val_2, operator oper);
int take_sign(s21_decimal number);
int take_bit(s21_decimal num, int position);
int delete_bit(s21_decimal *num, int position);
int take_scale(s21_decimal num);
void put_scale(s21_decimal *num, int exp);
int negative(int src);
int put_bit(s21_decimal *num, int position);
void init_decimal(s21_decimal *decimla_num);
void copy_decimal(s21_decimal *src, s21_decimal *dst);
bool decimal_is_null(s21_decimal num);

#endif  // SRC_S21_DECIMAL_H_
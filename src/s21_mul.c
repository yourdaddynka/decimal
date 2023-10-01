#include "s21_decimal.h"

void make_lower_scale(s21_decimal *val) {
  if (take_scale(*val) > 0) {
    int scale_retruned =
        take_scale(*val);  // Получение текущего значения степень
    int sign = take_sign(*val);  // Получение знака числа
    put_scale(val, 0);           // Установка степеньа в 0
    delete_bit(val, 127);        // Удаление знакового бита

    s21_decimal temp_mult = {
        {10, 0, 0, 0}};  // Создание временного операнда для умножения
    s21_decimal temp_res = {{0, 0, 0, 0}};  // Создание временного результата
    s21_decimal temp_val = {
        {0, 0, 0,
         0}};  // Создание временного числа для хранения промежуточных значений

    s21_mod(*val, temp_mult,
            &temp_res);  // Вычисление остатка от деления числа на 10

    while (decimal_is_null(temp_res) && scale_retruned > 0) {
      s21_div(*val, temp_mult, &temp_val);  // Деление числа на 10
      scale_retruned--;
      copy_decimal(&temp_val,
                   val);  // Копирование результата деления в основное число
    }

    put_scale(val, scale_retruned);  // Установка нового значения степеньа
    if (sign) {
      put_bit(val, 127);  // Установка знакового бита, если число отрицательное
    }
  }
}

int s21_mul(s21_decimal v_1, s21_decimal v_2, s21_decimal *result) {
  arith_result statys = OK;

  if (result && buffer_overflow(v_1, v_2, MUL) == 0) {
    int temp_cnt = 0;  // Счетчик для временного сдвига результата
    s21_decimal temp_sum;  // Временная переменная для хранения суммы
                           // промежуточных результатов
    init_decimal(&temp_sum);  // Инициализация временной переменной
    init_decimal(result);  // Инициализация результирующего числа

    int res_scale = take_scale(v_1) +
                    take_scale(v_2);  // Вычисление нового значения степеньа
    res_scale =
        (res_scale > 28) ? 28 : res_scale;  // Ограничение степеньа до 28

    s21_decimal ten = {{10, 0, 0, 0}};
    if (s21_is_equal(v_2, ten) && (res_scale > 0)) {
      *result = v_1;
      put_scale(result,
                take_scale(v_1) - 1);  // Установка нового значения степеньа
    } else {
      for (int cnt_v_2 = 0; cnt_v_2 < 96;
           cnt_v_2++) {  // Цикл по битам числа v_2
        init_decimal(result);  // Инициализация результата умножения для
                               // текущего бита v_2
        for (int cnt_v_1 = 0; cnt_v_1 < 96;
             cnt_v_1++) {  // Цикл по битам числа v_1
          int mul = take_bit(v_1, cnt_v_1) *
                    take_bit(v_2, cnt_v_2);  // Умножение текущих битов
          if (mul) {                         // Если mul == 1
            put_bit(
                result,
                cnt_v_1 +
                    temp_cnt);  // Установка соответствующего бита в результате
          } else {              // Если mul == 0
            delete_bit(
                result,
                cnt_v_1 +
                    temp_cnt);  // Удаление соответствующего бита в результате
          }
        }

        s21_add(*result, temp_sum,
                result);  // Сложение текущего результата с промежуточной суммой
        copy_decimal(
            result,
            &temp_sum);  // Копирование результата в промежуточную сумму
        temp_cnt++;  // Увеличение счетчика сдвига результата
      }
      put_scale(result,
                res_scale);  // Установка нового значения степеньа в результате
      if ((!take_sign(v_1) && take_sign(v_2)) ||
          (take_sign(v_1) && !take_sign(v_2))) {
        put_bit(result, 127);  // Установка знакового бита в результате, если
                               // знаки чисел разные
      }
      if (take_scale(*result) > 0) {
        make_lower_scale(
            result);  // Уменьшение степеньа результата, если необходимо
      }
    }
  } else {
    statys = buffer_overflow(v_1, v_2, MUL);  // Проверка на переполнение буфера
    if (result) {
      init_decimal(result);  // Инициализация результата в случае ошибки
    }
  }
  return statys;
}

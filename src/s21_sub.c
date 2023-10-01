#include "s21_decimal.h"

void sub_help(s21_decimal v_1, s21_decimal v_2, s21_decimal *result) {
  int scale_1 = take_scale(v_1);  // Получение степеньа числа v_1
  int scale_2 = take_scale(v_2);  // Получение степеньа числа v_2

  if (scale_1 > 0 ||
      scale_2 > 0) {  // Если хотя бы одно из чисел имеет степень больше нуля
    put_scale(result,
              (scale_1 > scale_2)
                  ? scale_1
                  : scale_2);  // Установка нового степеньа для результата
    put_scale((scale_1 > scale_2) ? &v_2 : &v_1,
              0);  // Установка степеньа нулевым для числа с меньшим степеньом
    s21_decimal shift = {
        {(int)pow(10.0, (double)fabs((double)scale_1 - (double)scale_2)), 0, 0,
         0}};  // Вычисление значения сдвига
    s21_decimal new_val_1 = {{0, 0, 0, 0}};  // Новое значение v_1
    s21_decimal new_val_2 = {{0, 0, 0, 0}};  // Новое значение v_2
    s21_mul((scale_1 > scale_2) ? v_2 : v_1, shift,
            (scale_1 > scale_2) ? &new_val_2
                                : &new_val_1);  // Умножение числа с меньшим
                                                // степеньом на значение сдвига
    copy_decimal(
        (scale_1 > scale_2) ? &new_val_2 : &new_val_1,
        (scale_1 > scale_2)
            ? &v_2
            : &v_1);  // Копирование нового значения в число с меньшим степеньом
  }

  int temp = 0;
  for (int cnt = 0; cnt < 96; cnt++) {  // Цикл по битам чисел v_1 и v_2
    int sub =
        take_bit(v_1, cnt) - take_bit(v_2, cnt);  // Вычитание текущих битов
    if (sub > 0) {  // Если sub > 0, то 1 - 0 - temp
      (temp == 0)
          ? put_bit(result, cnt)
          : delete_bit(result,
                       cnt);  // Установка или удаление бита в результате
      temp = 0;  // Установка значения временной переменной
    } else if (sub < 0) {  // Если sub < 0, то 0 - 1
      (temp == 0)
          ? put_bit(result, cnt)
          : delete_bit(result,
                       cnt);  // Установка или удаление бита в результате
      temp = 1;  // Установка значения временной переменной
    } else {  // Если sub == 0, то 0 - 0 или 1 - 1
      (temp == 0)
          ? delete_bit(result, cnt)
          : put_bit(result, cnt);  // Установка или удаление бита в результате
      temp = (temp == 0) ? 0 : 1;  // Установка значения временной переменной
    }
  }
}

int s21_sub(s21_decimal v_1, s21_decimal v_2, s21_decimal *result) {
  arith_result statys = OK;

  if (result && buffer_overflow(v_1, v_2, MIN) ==
                    0) {  // Если указатель на результат не является нулевым и
                          // нет переполнения буфера
    init_decimal(result);  // Инициализация результата
    if (take_bit(v_1, 127) == 0 &&
        take_bit(v_2, 127) == 0) {  // Если оба числа положительные
      sub_help(v_1, v_2, result);  // Вызов функции вычитания
    } else if (take_bit(v_1, 127) &&
               take_bit(v_2, 127)) {  // Если оба числа отрицательные
      delete_bit(&v_1, 127);  // Удаление знакового бита из чисел
      delete_bit(&v_2, 127);
      sub_help(v_1, v_2, result);  // Вызов функции вычитания
      put_bit(result, 127);  // Установка знакового бита в результате
    } else {  // Если числа имеют разные знаки
      if (take_bit(v_1, 127)) {  // Если первое число отрицательное
        add_help(v_1, v_2, result);  // Вызов функции сложения
        put_bit(result, 127);  // Установка знакового бита в результате
      } else {  // Если второе число отрицательное
        add_help(v_1, v_2, result);  // Вызов функции сложения
      }
    }
  } else {  // Если есть переполнение буфера
    statys = buffer_overflow(v_1, v_2, MIN);  // Установка статуса переполнения
    if (result) {
      init_decimal(result);  // Инициализация результата
    }
  }

  return statys;  // Возврат статуса операции
}

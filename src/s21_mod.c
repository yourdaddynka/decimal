#include "s21_decimal.h"
// вычисляет остаток от деления двух чиселs

int s21_mod(s21_decimal value_1, s21_decimal value_2, s21_decimal *result) {
  arith_result statys = OK;

  if (result && !decimal_is_null(value_2)) {
    delete_bit(&value_1, 127);  // Удаление знакового бита у первого операнда
    delete_bit(&value_2, 127);  // Удаление знакового бита у второго операнда
    scale_is_equal(&value_1, &value_2);  // Уравнивание степеньов операндов

    if (s21_is_less(value_1, value_2)) {
      copy_decimal(&value_1,
                   result);  // Копирование первого операнда в результат, если
                             // он меньше второго операнда
    } else {
      char value_1_string[255] = {
          '\0'};  // Строка для хранения первого операнда в виде строки
      char ostatok_string[255] = {
          '\0'};  // Строка для хранения остатка от деления в виде строки
      s21_decimal ostatok;
      init_decimal(&ostatok);  // Инициализация переменной для хранения остатка

      s21_decimal_to_string(
          value_1_string, value_1);  // Преобразование первого операнда в строку

      int cnt_shift = 0;
      for (; s21_is_less(s21_string_to_decimal(ostatok_string), value_2);
           cnt_shift++) {
        ostatok_string[cnt_shift] =
            value_1_string[cnt_shift];  // Заполнение строки остатка
      }
      memmove(value_1_string, value_1_string + cnt_shift,
              strlen(value_1_string));

      do {
        s21_sub(s21_string_to_decimal(ostatok_string), value_2,
                &ostatok);  // Вычитание второго операнда из остатка

        memset(ostatok_string, '\0', sizeof(ostatok_string));

        if (!decimal_is_null(ostatok)) {
          s21_decimal_to_string(ostatok_string,
                                ostatok);  // Преобразование остатка в строку
        }

        while (s21_is_less(ostatok, value_2)) {
          strncat(ostatok_string, value_1_string, 1);
          memmove(value_1_string, value_1_string + 1, strlen(value_1_string));
          ostatok = s21_string_to_decimal(ostatok_string);

          if ((decimal_is_null(s21_string_to_decimal(value_1_string)) &&
               decimal_is_null(ostatok)) ||
              !strlen(value_1_string)) {
            break;
          }
        }
      } while (s21_is_greater_or_equal(ostatok, value_2));

      copy_decimal(&ostatok, result);  // Копирование остатка в результат
      put_bit(result, 127);  // Установка знакового бита в результате
    }
  }

  return statys;
}

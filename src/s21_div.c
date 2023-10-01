#include "s21_decimal.h"

int format_div(s21_decimal *val_1, s21_decimal *val_2) {
  int scale = 0;  // Переменная для хранения степеньа результата

  if (take_scale(*val_1) == 0 && take_scale(*val_2) > 0) {
    // Если у первого значения степень равен 0, а у второго значение степеньа
    // больше 0, то устанавливаем степень результата равным степеньу второго
    // значения
    scale = take_scale(*val_2);
    int sign_1 = take_sign(*val_1);
    s21_decimal temp_mul = {
        {(int)pow(10, scale), 0, 0, 0}};  // Значение для умножения

    s21_decimal temp_v_1 = {
        {0, 0, 0, 0}};  // Временное значение для хранения результата умножения

    put_scale(val_1, 0);  // Устанавливаем степень первого значения равным 0
    s21_mul(*val_1, temp_mul,
            &temp_v_1);  // Умножаем первое значение на temp_mul
    copy_decimal(&temp_v_1,
                 val_1);  // Копируем результат умножения в первое значение
    if (sign_1) {
      put_bit(val_1, 127);  // Восстанавливаем знак в первом значении, если он
                            // был отрицательным
    }
    put_scale(val_2, 0);  // Устанавливаем степень второго значения равным 0
  } else if (take_scale(*val_1) > 0 && take_scale(*val_2) == 0) {
    // Если у первого значения степень больше 0, а у второго значение степеньа
    // равно 0, то устанавливаем степень результата равным степеньу первого
    // значения
    scale = take_scale(*val_1);
    int sign_1 = take_sign(*val_1);
    s21_decimal temp_mul = {
        {(int)pow(10, scale), 0, 0, 0}};  // Значение для умножения

    s21_decimal temp_v_2 = {
        {0, 0, 0, 0}};  // Временное значение для хранения результата умножения

    put_scale(val_2, 0);  // Устанавливаем степень второго значения равным 0
    s21_mul(*val_2, temp_mul,
            &temp_v_2);  // Умножаем второе значение на temp_mul
    copy_decimal(&temp_v_2,
                 val_2);  // Копируем результат умножения во второе значение
    if (sign_1) {
      put_bit(val_2, 127);  // Восстанавливаем знак во втором значении, если он
                            // был отрицательным
    }
    put_scale(val_1, 0);  // Устанавливаем степень первого значения равным 0
  } else if (take_scale(*val_1) > 0 && take_scale(*val_2) > 0) {
    // Если у обоих значений степень больше 0,
    // то устанавливаем степень результата равным максимальному степеньу обоих
    // значений
    int sign_1 = take_sign(*val_1);
    int sign_2 = take_sign(*val_2);

    s21_decimal temp_mul_v1 = {
        {(take_scale(*val_2) > 0) ? (int)pow(10, take_scale(*val_2)) : 1, 0, 0,
         0}};  // Значение для умножения первого значения
    s21_decimal temp_mul_v2 = {
        {(take_scale(*val_1) > 0) ? (int)pow(10, take_scale(*val_1)) : 1, 0, 0,
         0}};  // Значение для умножения второго значения

    int first = (int)pow(
        10,
        take_scale(
            *val_1));  // Значение для установки первого значения степеньа

    s21_decimal temp_v_1 = {
        {0, 0, 0, 0}};  // Временное значение для хранения результата умножения
                        // первого значения
    s21_decimal temp_v_2 = {
        {0, 0, 0, 0}};  // Временное значение для хранения результата умножения
                        // второго значения

    put_scale(val_1, 0);  // Устанавливаем степень первого значения равным 0
    s21_mul(*val_1, temp_mul_v1,
            &temp_v_1);  // Умножаем первое значение на temp_mul_v1
    copy_decimal(&temp_v_1,
                 val_1);  // Копируем результат умножения в первое значение
    if (sign_1) {
      put_bit(val_1, 127);  // Восстанавливаем знак в первом значении, если он
                            // был отрицательным
    }

    temp_mul_v2.bits[0] =
        first;  // Устанавливаем первое значение степеньа в temp_mul_v2
    put_scale(val_2, 0);  // Устанавливаем степень второго значения равным 0
    s21_mul(*val_2, temp_mul_v2,
            &temp_v_2);  // Умножаем второе значение на temp_mul_v2
    copy_decimal(&temp_v_2,
                 val_2);  // Копируем результат умножения во второе значение
    if (sign_2) {
      put_bit(val_1, 127);  // Восстанавливаем знак в первом значении, если он
                            // был отрицательным
    }
  }

  return 0;  // Возвращаем 0, как индикатор успешного выполнения
}

int s21_div(s21_decimal v_1, s21_decimal v_2, s21_decimal *result) {
  arith_result statys = OK;

  if (result && !decimal_is_null(v_2) && buffer_overflow(v_1, v_2, DIV) == 0) {
    int sign = 0;  // Флаг для хранения знака результата
    int scale = 0;  // Переменная для хранения степеньа результата

    // Установка знака результата в соответствии с знаками операндов
    if ((take_bit(v_1, 127) && !take_bit(v_2, 127)) ||
        (!take_bit(v_1, 127) && take_bit(v_2, 127))) {
      put_bit(result, 127);
    }

    // Установка флага для отрицательного результата
    if ((take_sign(v_1) == 0 && take_sign(v_2) == 1) ||
        (take_sign(v_1) == 1 && take_sign(v_2) == 0)) {
      sign = 1;
    }

    // Удаление знаковых битов у операндов
    delete_bit(&v_1, 127);
    delete_bit(&v_2, 127);

    // Форматирование операндов, если их степеньы больше 0
    if (take_scale(v_1) + take_scale(v_2) > 0) {
      scale = format_div(&v_1, &v_2);
    }

    // Выполнение деления операндов
    if (s21_is_less(v_1, v_2)) {
      result->bits[LOW] = 0;
    } else if (s21_is_equal(v_1, v_2)) {
      result->bits[LOW] = 1;
    } else {
      int position_bit_result = 0;  // Позиция текущего бита результата
      char val_1_string[255] = {
          '\0'};  // Строка для хранения первого операнда в виде строки
      char ostatok_string[255] = {
          '\0'};  // Строка для хранения остатка от деления в виде строки
      char result_string[255] = {
          '\0'};  // Строка для хранения результата деления в виде строки
      s21_decimal ostatok = {{0, 0, 0, 0}};  // Остаток от деления

      // Преобразование первого операнда в строку
      s21_decimal_to_string(val_1_string, v_1);

      int cnt_shift = 0;
      for (; s21_is_less(s21_string_to_decimal(ostatok_string), v_2);
           cnt_shift++) {
        ostatok_string[cnt_shift] = val_1_string[cnt_shift];
      }
      memmove(val_1_string, val_1_string + cnt_shift, strlen(val_1_string));

      do {
        s21_sub(s21_string_to_decimal(ostatok_string), v_2,
                &ostatok);  // Вычитание второго операнда из остатка
        result_string[position_bit_result++] = '1';  // Запись бита результата

        // Очистка строки остатка
        memset(ostatok_string, '\0', sizeof(ostatok_string));

        if (!decimal_is_null(ostatok)) {
          s21_decimal_to_string(ostatok_string,
                                ostatok);  // Преобразование остатка в строку
        }

        cnt_shift = 1;
        while (s21_is_less(ostatok, v_2)) {
          if (strlen(val_1_string) == 0) {
            break;
          }
          cnt_shift++;

          strncat(ostatok_string, val_1_string, 1);
          memmove(val_1_string, val_1_string + 1, strlen(val_1_string));
          ostatok = s21_string_to_decimal(ostatok_string);

          if (cnt_shift > 2) {
            result_string[position_bit_result++] = '0';
          }

          int temp = strlen(val_1_string);
          if (!temp) {
            if ((s21_is_less(ostatok, v_2) && !decimal_is_null(ostatok))) {
              result_string[position_bit_result++] = '0';
            } else if ((decimal_is_null(s21_string_to_decimal(val_1_string)) &&
                        decimal_is_null(ostatok))) {
              for (size_t i = 0; i < strlen(val_1_string); i++) {
                result_string[position_bit_result++] = '0';
              }
              for (size_t i = 0; i < strlen(ostatok_string); i++) {
                result_string[position_bit_result++] = '0';
              }
            }
            break;
          }

          if (decimal_is_null(s21_string_to_decimal(val_1_string)) &&
              decimal_is_null(ostatok)) {
            for (size_t i = 0; i < strlen(val_1_string) + 1; i++) {
              result_string[position_bit_result++] = '0';
            }
            break;
          }
        }
      } while (s21_is_greater_or_equal(ostatok, v_2));

      *result = s21_string_to_decimal(
          result_string);  // Преобразование строки
                           // результата в десятичное число

      put_scale(result, scale);  // Установка степеньа результата
      if (sign) {
        put_bit(result, 127);  // Установка знака результата
      }
      if (scale > 0) {
        make_lower_scale(
            result);  // Уменьшение степеньа результата до нижнего значения
      }
    }
  } else {
    statys = (!result) ? ERROR : buffer_overflow(v_1, v_2, DIV);
  }

  return statys;
}

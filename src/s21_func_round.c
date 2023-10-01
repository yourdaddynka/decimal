#include "s21_decimal.h"
#define MAX_DECIMAL 4294967295

int s21_floor(s21_decimal value, s21_decimal *result) {
  other_result statys = OTHER_OK;

  if (result) {  // Если передан указатель на результат
    init_decimal(result);  // Инициализация результата

    int sign = take_sign(value);  // Получение знака исходного значения
    s21_decimal one_val = {{1, 0, 0, 0}};  // Значение 1
    s21_decimal temp_val = {{0, 0, 0, 0}};  // Временное значение

    s21_truncate(value,
                 &temp_val);  // Обрезка десятичной части исходного значения
    if (sign) {
      s21_sub(temp_val, one_val,
              result);  // Если значение отрицательное, вычитаем 1 и записываем
                        // в результат
    } else {
      *result =
          temp_val;  // Иначе просто копируем обрезанное значение в результат
    }
  } else {
    statys = OTHER_ERROR;  // Если передан нулевой указатель на результат,
                           // возвращаем ошибку
  }
  return statys;  // Возвращаем статус выполнения операции
}

int s21_negate(s21_decimal value, s21_decimal *result) {
  other_result statys = OTHER_OK;

  if (result) {  // Если передан указатель на результат
    init_decimal(result);  // Инициализация результата
    put_scale(result,
              take_scale(value));  // Копирование степеньа исходного значения

    (take_bit(value, 127) == 0) ? put_bit(result, 127)
                                : delete_bit(result, 127);
    // Если исходное значение имеет нулевой бит знака, копируем нулевой бит в
    // результат, иначе удаляем нулевой бит из результата

    for (size_t position = 0; position < 96; position++) {
      if (take_bit(value, position) == 0) {
        delete_bit(result, position);  // Если бит значения равен нулю, удаляем
                                       // его из результата
      } else {
        put_bit(result, position);  // Если бит значения равен единице, копируем
                                    // его в результат
      }
    }
  } else {
    statys = OTHER_ERROR;  // Если передан нулевой указатель на результат,
                           // возвращаем ошибку
  }

  return statys;  // Возвращаем статус выполнения операции
}

int help_up_round(s21_decimal fract, s21_decimal integer) {
  int statys = 0;  // Переменная для хранения статуса округления
  s21_decimal fract_first_symbol = {
      {0, 0, 0, 0}};  // Первый символ дробной части
  s21_decimal five = {{5, 0, 0, 0}};  // Значение 5
  s21_decimal two = {{2, 0, 0, 0}};   // Значение 2
  s21_decimal temp = {{0, 0, 0, 0}};  // Временная переменная
  s21_decimal temp2 = {{0, 0, 0, 0}};  // Вторая временная переменная
  s21_decimal ten = {{10, 0, 0, 0}};  // Значение 10

  s21_truncate(fract,
               &fract_first_symbol);  // Отбрасываем лишние символы из дробной
                                      // части, оставляем только первый

  s21_mod(fract_first_symbol, ten,
          &temp);  // Находим остаток от деления первого символа на 10

  if (s21_is_greater_or_equal(temp, five)) {  // Если остаток больше или равен 5
    s21_mod(integer, two,
            &temp2);  // Находим остаток от деления целой части на 2
    statys = (decimal_is_null(temp2) && s21_is_equal(temp, five))
                 ? 0
                 : 1;  // Если остаток от деления целой части на 2 равен нулю и
                       // остаток от деления первого символа на 10 равен 5
  }

  return statys;  // Возвращаем статус округления (0 - округление не требуется,
                  // 1 - требуется округление вверх)
}

int s21_round(s21_decimal value, s21_decimal *result) {
  other_result statys = OTHER_OK;  // Переменная для хранения статуса округления

  if (result) {
    init_decimal(result);  // Инициализируем результат нулевым значением

    if (take_scale(value) == 0) {  // Если у значения нет дробной части
      *result = value;  // Результатом будет само значение без изменений
    } else {
      int sign = take_sign(value);  // Запоминаем знак значения
      delete_bit(&value, 127);  // Удаляем бит знака

      s21_decimal temp_val_int = {
          {0, 0, 0, 0}};  // Временная переменная для целой части
      s21_decimal temp_val_fract = {
          {0, 0, 0, 0}};  // Временная переменная для дробной части
      s21_decimal one_val = {{1, 0, 0, 0}};  // Значение 1

      s21_truncate(value, &temp_val_int);  // Получаем целую часть значения
      s21_sub(value, temp_val_int,
              &temp_val_fract);  // Получаем дробную часть значения
      put_scale(&temp_val_fract,
                take_scale(temp_val_fract) -
                    1);  // Уменьшаем степень дробной части на 1

      if (help_up_round(temp_val_fract,
                        temp_val_int)) {  // Если требуется округление вверх
        s21_truncate(value, &temp_val_int);  // Получаем целую часть значения
        s21_add(temp_val_int, one_val, result);  // Увеличиваем целую часть на 1
      } else {
        s21_truncate(value, result);  // Округляем значение до целой части
      }
      if (sign) {
        put_bit(result, 127);  // Восстанавливаем знак в результате, если он был
                               // отрицательным
      }
    }
  } else {
    statys = OTHER_ERROR;  // Устанавливаем статус ошибки, если указатель на
                           // результат недействителен
  }

  return statys;  // Возвращаем статус округления (OTHER_OK - успешное
                  // округление, OTHER_ERROR - ошибка)
}

int s21_truncate(s21_decimal value, s21_decimal *result) {
  other_result statys = OTHER_OK;  // Переменная для хранения статуса усечения

  if (result) {
    init_decimal(result);  // Инициализируем результат нулевым значением

    int val_scale = take_scale(value);  // Получаем степень значения
    int sign = take_sign(value);  // Запоминаем знак значения
    put_scale(&value, 0);  // Устанавливаем степень значения равным 0
    s21_decimal ten = {{10, 0, 0, 0}};  // Значение 10

    for (int i = 0; i < val_scale; i++) {
      s21_div(value, ten, result);  // Делим значение на 10, чтобы усечь одну
                                    // цифру дробной части
      value = *result;  // Обновляем значение для следующей итерации
    }

    *result = value;  // Результатом является усеченное значение

    if (sign) {
      put_bit(
          result,
          127);  // Восстанавливаем знак в результате, если он был отрицательным
    }
  } else {
    statys = OTHER_ERROR;  // Устанавливаем статус ошибки, если указатель на
                           // результат недействителен
  }
  return statys;  // Возвращаем статус усечения (OTHER_OK - успешное усечение,
                  // OTHER_ERROR - ошибка)
}

#include "s21_decimal.h"

int s21_equal_compare(s21_decimal dec1, s21_decimal dec2) {
  // Функция для сравнения на равенство двух s21_decimal чисел

  int res = -1;  // Изначально результат сравнения установлен на -1

  // Проверяем, имеют ли числа ненулевую шкалу и при необходимости выравниваем
  // их шкалы
  if (take_scale(dec1) > 0 || take_scale(dec2) > 0) {
    scale_is_equal(&dec1, &dec2);
  }

  // Сравниваем биты чисел dec1 и dec2 на каждой позиции
  // Если все биты на каждой позиции равны, устанавливаем результат на 1, иначе
  // на 0
  res = (dec1.bits[3] == dec2.bits[3] && dec1.bits[2] == dec2.bits[2] &&
         dec1.bits[1] == dec2.bits[1] && dec1.bits[0] == dec2.bits[0])
            ? 1
            : 0;

  return res;  // Возвращаем результат сравнения (1 - равны, 0 - не равны)
}

int s21_easy_compare(s21_decimal dec1, s21_decimal dec2) {
  // Функция для сравнения двух положительных s21_decimal чисел

  int res = -1;  // Изначально результат сравнения установлен на -1
  int bits1 = 0, bits2 = 0;  // Переменные для хранения битов на каждой позиции

  // Проверяем, имеют ли числа ненулевую шкалу и при необходимости выравниваем
  // их шкалы
  if (take_scale(dec1) > 0 || take_scale(dec2) > 0) {
    scale_is_equal(&dec1, &dec2);
  }

  // Сравниваем биты чисел dec1 и dec2 на каждой позиции, начиная с позиции 95
  for (int i = 95; i >= 0 && (res != 0 || res != 1); i--) {
    bits1 = take_bit(dec1, i);
    bits2 = take_bit(dec2, i);
    if (bits1 > bits2) {
      res = 0;
      break;
    } else if (bits1 < bits2) {
      res = 1;
      break;
    } else {
      res = 0;
    }
  }

  return res;  // Возвращаем результат сравнения
}

int s21_is_less(s21_decimal dec1, s21_decimal dec2) {
  // Функция для проверки, является ли dec1 меньшим числом, чем dec2

  int res = -1;  // Изначально результат установлен на -1
  int sign1 = take_bit(dec1, 127);  // Знак числа dec1
  int sign2 = take_bit(dec2, 127);  // Знак числа dec2

  // Если числа dec1 и dec2 равны, результат устанавливается на 0
  // Если знак dec1 > знак dec2, результат устанавливается на 1
  // Если оба числа отрицательные и dec1 < dec2, результат устанавливается на 1
  // В остальных случаях сравниваются числа dec1 и dec2 с помощью функции
  // s21_easy_compare() Результат сравнения возвращается
  res = s21_is_equal(dec1, dec2) ? 0
        : sign1 > sign2          ? 1
        : (sign1 == 1 && sign2 == 1)
            ? (s21_easy_compare(dec1, dec2) == 0 ? 1 : 0)
            : s21_easy_compare(dec1, dec2);

  return res;  // Возвращаем результат (0 - dec1 >= dec2, 1 - dec1 < dec2)
}

int s21_is_less_or_equal(s21_decimal dec1,
                         s21_decimal dec2) {  // меньше или равно
  return s21_is_less(dec1, dec2) || s21_is_equal(dec1, dec2);
}

int s21_is_greater(s21_decimal dec1, s21_decimal dec2) {  // больше
  return !s21_is_less_or_equal(dec1, dec2);
}

int s21_is_greater_or_equal(s21_decimal dec1,
                            s21_decimal dec2) {  // больше или равно
  return s21_is_greater(dec1, dec2) || s21_is_equal(dec1, dec2);
}

int s21_is_equal(s21_decimal dec1, s21_decimal dec2) {  // равно
  int res = -1, sign1 = take_sign(dec1), sign2 = take_sign(dec2);
  res = (sign1 == sign2) ? s21_equal_compare(dec1, dec2) : 0;
  return res;
}

int s21_is_not_equal(s21_decimal dec1, s21_decimal dec2) {  // не равно
  return !s21_is_equal(dec1, dec2);
}

#include "s21_decimal.h"

int take_bit(s21_decimal num, int position) {
  // Возвращает значение бита на указанной позиции в числе num
  unsigned int bit_mask = 1u << (position % 32);
  int a = ((num.bits[position / 32] & bit_mask) >> (position % 32));
  return a;
}
// 0000101 s21_decimal num
// 5
// 0000100 bit_mask - попозиции
// значение по данной позиции 1 возыращаем его

int put_bit(s21_decimal *num, int position) {
  // Устанавливает значение бита на указанной позиции в числе num
  unsigned int bit_mask = 1u << (position % 32);
  return num->bits[position / 32] = num->bits[position / 32] | bit_mask;
}

// 0000101 s21_decimal num
// 6
// 0000010 bit_mask - попозиции
// после данной операции мы получим 0000111

int delete_bit(s21_decimal *num, int position) {
  // Удаляет (устанавливает в ноль) значение бита на указанной позиции в числе
  // num
  unsigned int bit_mask = 1u << (position % 32);
  return num->bits[position / 32] = num->bits[position / 32] & ~bit_mask;
}

// 0000101 s21_decimal num
// 5
// 1111011 bit_mask - попозиции
// после данной операции мы получим 0000001

int take_scale(s21_decimal num) {
  // Возвращает значение cтепени числа num
  int bit_mask = 127 << 16;
  int scale = (bit_mask & num.bits[3]) >> 16;
  return scale;
}

// 00000000011111110000000000000000 bit_mask << 16
// 10000000010100010000000000000000  num.bits[3]
// 00000000010100010000000000000000  res bit_mask & num.bits[3]
// 00000000000000000000000001010001  scale =  bit_mask & num.bits[3] >> 16
// 81

void put_scale(s21_decimal *num, int exp) {
  // Устанавливает значение cтепени числа num
  int bit_mask = exp << 16;
  num->bits[3] = bit_mask;
}

// 00000000000000000000000000000000 bit_mask << 16  exp = 0
// 00000000000000000000000000000000 num->bits[3] = bit_mask

int negative(int src) {
  // Проверяет, является ли число src отрицательным
  return (src < 0);
}

void init_decimal(s21_decimal *decimla_num) {
  // Инициализирует значение числа decimla_num нулями
  memset(&(decimla_num->bits), 0, sizeof(decimla_num->bits));
}

void add_in_start_chat(char *str, char ch) {
  // Добавляет символ ch в начало строки str
  char temp[2] = {ch, '\0'};
  strcat(temp, str);
  strcpy(str, temp);
}

bool decimal_is_null(s21_decimal num) {
  // Проверяет, является ли число num нулевым
  bool statys = false;
  if (num.bits[0] == 0 && num.bits[1] == 0 && num.bits[2] == 0) {
    statys = true;
  }
  return statys;
}

void scale_is_equal(s21_decimal *dst1, s21_decimal *dst2) {
  // Уравнивает степень чисел dst1 и dst2
  unsigned int scale1 = take_scale(*dst1);
  unsigned int scale2 = take_scale(*dst2);
  s21_decimal ten = {{0, 0, 0, 0}};
  s21_decimal temp = {{0, 0, 0, 0}};

  if (scale1 > scale2) {
    put_scale(dst2, 0);
    for (int i = scale1 - scale2; i > 0; i--) {
      s21_from_int_to_decimal(10, &ten);
      s21_mul(*dst2, ten, &temp);
      *dst2 = temp;
    }
    put_scale(dst2, scale1);
  }

  if (scale1 < scale2) {
    put_scale(dst1, 0);
    for (int i = scale2 - scale1; i > 0; i--) {
      s21_from_int_to_decimal(10, &ten);
      s21_mul(*dst1, ten, &temp);
      *dst1 = temp;
    }
    put_scale(dst1, scale2);
  }
}

void copy_decimal(s21_decimal *src, s21_decimal *dst) {
  // Копирует значение числа src в число dst
  for (int position = LOW; position <= SCALE; position++) {
    dst->bits[position] = src->bits[position];
  }
}

int take_sign(s21_decimal number) {
  // Возвращает знак числа number (0 - положительное, 1 - отрицательное)
  int sign = take_bit(number, 127);
  return sign;
}

int buffer_overflow(s21_decimal val_1, s21_decimal val_2, operator oper) {
  arith_result statys = OK;

  if (oper == PLUS) {
    // Проверяет возможность переполнения при сложении
    long long int res =
        (long long int)val_1.bits[HIGH] + (long long int)val_2.bits[HIGH];
    if (res > MAX_BITS_VAL) {
      statys = INF;
      if (take_bit(val_1, 127) == 1 && take_bit(val_2, 127) == 1) {
        statys = MIN_INF;
      }
    }
  } else if (oper == MIN) {
    // Проверяет возможность переполнения при вычитании
    long long int res = 0;
    if ((take_sign(val_1) && !take_sign(val_2)) ||
        (!take_sign(val_1) && take_sign(val_2))) {
      res = (long long int)val_1.bits[HIGH] + (long long int)val_2.bits[HIGH];
    } else {
      res = (long long int)val_1.bits[HIGH] - (long long int)val_2.bits[HIGH];
    }
    if (res > MAX_BITS_VAL) {
      statys = INF;
      if (take_bit(val_1, 127) == 1 && take_bit(val_2, 127) == 1) {
        statys = MIN_INF;
      }
    }
  } else if (oper == MUL) {
    // Проверяет возможность переполнения при умножении
    int i = 95;
    int j = 95;
    while (take_bit(val_1, i) != 1 && i != 0) {
      i--;
    }
    while (take_bit(val_2, j) == 0 && j != 0) {
      j--;
    }
    if (i + j >= 96) {
      if ((take_sign(val_1) == 1 && take_sign(val_2) == 0) ||
          (take_sign(val_1) == 0 && take_sign(val_2) == 1)) {
        statys = MIN_INF;
      } else {
        statys = INF;
      }
    }
  } else if (oper == DIV) {
    // Проверяет возможность переполнения при делении
    if (decimal_is_null(val_1)) {
      statys = INF;
    } else if (decimal_is_null(val_2)) {
      statys = DIV_BY_ZERO;
    } else {
      int i = 95;
      int j = 95;
      while (take_bit(val_1, i) != 1 && i != 0) {
        i--;
      }
      while (take_bit(val_2, j) == 0 && j != 0) {
        j--;
      }
      if (i + j >= 96 && (take_scale(val_2) > 0)) {
        if ((take_sign(val_1) == 1 && take_sign(val_2) == 0) ||
            (take_sign(val_1) == 0 && take_sign(val_2) == 1)) {
          statys = MIN_INF;
        } else {
          statys = INF;
        }
      }
    }
  }

  return statys;
}

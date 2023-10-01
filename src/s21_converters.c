#include "s21_decimal.h"

int s21_from_int_to_decimal(int src, s21_decimal *dst) {
  conv_result statys = CONVERTATION_OK;

  if (dst) {
    // Преобразует целое число в десятичное представление s21_decimal
    memset(&(dst->bits), 0, sizeof(dst->bits));
    if (negative(src)) {
      put_bit(dst, 127);
      src *= -1;
    }
    if (src <= INT32_MAX) {
      dst->bits[0] = src;
    } else {
      init_decimal(dst);
      statys = CONVERTATION_ERROR;
    }

  } else {
    statys = CONVERTATION_ERROR;
  }

  return statys;
}

int s21_from_decimal_to_int(s21_decimal src, int *dst) {
  conv_result statys = CONVERTATION_OK;

  if (dst) {
    // Преобразует десятичное представление s21_decimal в целое число
    uint64_t buffer = 0;
    *dst = 0;
    int scale = take_scale(src);
    int sign = take_bit(src, 127);

    buffer = src.bits[0] + src.bits[1] * 4294967295 + src.bits[2] * 4294967295;
    if (scale != 0) {
      buffer /= (int)pow(10, scale);
    }

    if (buffer <= INT32_MAX) {
      buffer = (sign != 0) ? -buffer : buffer;
      *dst = (int32_t)buffer;

    } else {
      *dst = 0;
      statys = CONVERTATION_ERROR;
    }
  } else {
    statys = CONVERTATION_ERROR;
  }
  return statys;
}

int s21_from_float_to_decimal(float src, s21_decimal *dst) {
  conv_result statys = CONVERTATION_OK;
  bool flag_minus = false;

  if (dst && !is_inf(src) && !is_nan(src)) {
    // Преобразует число с плавающей запятой в десятичное представление
    // s21_decimal
    init_decimal(dst);

    if (src < 0) {
      src *= -1.0f;
      flag_minus = true;
    }

    float fl_int = 0.0;
    float fl_fract = modff(src, &fl_int);
    src = s21_float_format((int)fl_int, fl_fract, dst);
    int scale_temp = take_scale(*dst);
    s21_from_int_to_decimal(src, dst);
    put_scale(dst, scale_temp);
    if (flag_minus) {
      put_bit(dst, 127);
    }
  } else {
    if (dst) init_decimal(dst);
    statys = CONVERTATION_ERROR;
  }

  return statys;
}

int s21_from_decimal_to_float(s21_decimal src, float *dst) {
  conv_result statys = CONVERTATION_OK;

  if (dst) {
    // Преобразует десятичное представление s21_decimal в число с плавающей
    // запятой (float)
    uint64_t buffer = 0;
    *dst = 0;
    int scale = take_scale(src);
    int sign = take_bit(src, 127);

    buffer = src.bits[0] + src.bits[1] * 4294967295 + src.bits[2] * 4294967295;
    *dst = (float)buffer / powf(10.0, scale);

    if (buffer <= __FLT_MAX__) {
      *dst = (sign != 0) ? -*dst : *dst;
    } else {
      statys = CONVERTATION_ERROR;
    }
  } else {
    if (dst) *dst = 0.0;
    statys = CONVERTATION_ERROR;
  }

  return statys;
}

int s21_float_format(int integer, float fract, s21_decimal *value) {
  // Форматирует целую часть и дробную часть числа с плавающей запятой и
  // сохраняет результат в s21_decimal
  char fr_str[255] = {0};
  char int_str[255] = {0};
  int cnt = 0;
  int exp = 0;

  if (fract != 0.0) {
    sprintf(fr_str, "%.9f", fract);
  }
  sprintf(int_str, "%d", integer);

  memmove(fr_str, fr_str + 2, strlen(fr_str));
  exp = strlen(int_str);
  strcat(int_str, fr_str);

  size_t cnt_sign_number = strlen(int_str);
  cnt = cnt_sign_number;

  if (cnt_sign_number > 7 && strlen(fr_str) > 0) {
    while (cnt != 7) {
      int_str[cnt--] = '\0';
    }
    if ((int)int_str[cnt] - '0' > 4) {
      cnt--;
      if (int_str[cnt] == '9') {
        while (int_str[cnt] == '9') {
          int_str[cnt--] = '0';
        }
        if (cnt != -1) {
          int_str[cnt]++;
        } else {
          add_in_start_chat(int_str, '1');
        }
      } else {
        int_str[cnt]++;
      }
      int_str[7] = '\0';
      cnt = strlen(int_str) - 1;
      while (int_str[cnt] == '0') {
        int_str[cnt--] = '\0';
      }
    } else {
      while (int_str[cnt] == '0') {
        int_str[cnt--] = '\0';
      }
    }
  }
  exp = (strlen(int_str) - exp);
  put_scale(value, exp);

  return atoi(int_str);
}

void s21_decimal_to_string(char *dst, s21_decimal src) {
  // Преобразует десятичное представление s21_decimal в строку
  if (dst) {
    bool flag = false;
    char temp[255] = {'\0'};
    int length = 0;
    for (int cnt = 95; cnt >= 0; cnt--) {  // 95
      if (take_bit(src, cnt)) {
        temp[cnt] = '1';
        flag = true;
        length++;
      } else {
        if (flag) {
          temp[cnt] = '0';
          length++;
        }
      }
    }

    if (length == 0) {
      dst[0] = '0';
    }

    for (size_t i = 0, j = strlen(temp) - 1; i < strlen(temp); i++, j--) {
      dst[i] = temp[j];
    }
  }
}

s21_decimal s21_string_to_decimal(char *string) {
  // Преобразует строку в десятичное представление s21_decimal
  s21_decimal result;
  init_decimal(&result);

  char temp[255] = {'\0'};
  for (size_t i = 0, j = strlen(string) - 1; i < strlen(string); i++, j--) {
    temp[i] = string[j];
  }

  for (int cnt = 0; cnt < 96; cnt++) {
    if (temp[cnt] == '1') {
      put_bit(&result, cnt);
    } else {
      delete_bit(&result, cnt);
    }
  }

  return result;
}

#include "s21_decimal.h"

void add_help(s21_decimal v_1, s21_decimal v_2, s21_decimal *result) {
  int temp = 0;
  int scale_1 = take_scale(v_1);
  int scale_2 = take_scale(v_2);

  // Если одно из чисел имеет дробную часть, выравниваем их степень
  if (scale_1 > 0 || scale_2 > 0) {
    // Устанавливаем степень результата равным максимальной степени
    put_scale(result, (scale_1 > scale_2) ? scale_1 : scale_2);
    // Устанавливаем степень первого числа равным 0, если его степень больше
    // второго или степень второго числа равным 0, если его степень больше
    // первого
    put_scale((scale_1 > scale_2) ? &v_2 : &v_1, 0);

    // Вычисляем значение сдвига в зависимости от разницы степеней
    s21_decimal shift = {
        {(int)pow(10.0, (double)fabs((double)scale_1 - (double)scale_2)), 0, 0,
         0}};

    // Создаем новые переменные для хранения сдвинутых значений чисел
    s21_decimal new_val_1 = {{0}};
    s21_decimal new_val_2 = {{0}};

    // Умножаем число с большим степеньом на сдвиг
    // и сохраняем результат в новых переменных
    s21_mul((scale_1 > scale_2) ? v_2 : v_1, shift,
            (scale_1 > scale_2) ? &new_val_2 : &new_val_1);

    // Копируем сдвинутое значение обратно в исходные переменные
    copy_decimal((scale_1 > scale_2) ? &new_val_2 : &new_val_1,
                 (scale_1 > scale_2) ? &v_2 : &v_1);
  }

  // Выполняем сложение по битам
  for (int cnt = 0; cnt < 96; cnt++) {
    int sum = take_bit(v_1, cnt) + take_bit(v_2, cnt);
    if (sum == 2) {
      if (temp == 1) {
        put_bit(result, cnt);  // 2 + 1
      } else {
        delete_bit(result, cnt);  // 2 + 0
      }
      temp = 1;
    } else if (sum == 0) {
      (temp == 0) ? delete_bit(result, cnt) : put_bit(result, cnt);
      temp = 0;
    } else {
      (temp == 0) ? put_bit(result, cnt) : delete_bit(result, cnt);
      temp = (temp == 0) ? 0 : 1;
    }
  }
}

int s21_add(s21_decimal v_1, s21_decimal v_2, s21_decimal *result) {
  arith_result statys = OK;
  // Проверяем, что указатель на результат существует
  // и нет переполнения буфера при выполнении операции сложения
  if (result && buffer_overflow(v_1, v_2, PLUS) == 0) {
    init_decimal(result);

    // Если оба числа положительные, выполняем сложение
    if (!take_bit(v_1, 127) && !take_bit(v_2, 127)) {
      add_help(v_1, v_2, result);
    }
    // Если оба числа отрицательные, выполняем сложение без знака минуса,
    // а затем устанавливаем знак результата в отрицательный
    else if (take_bit(v_1, 127) == 1 && take_bit(v_2, 127) == 1) {
      delete_bit(&v_1, 127);
      delete_bit(&v_2, 127);
      add_help(v_1, v_2, result);
      put_bit(result, 127);
    }
    // Если числа имеют разные знаки, выполняем вычитание в зависимости от их
    // значений
    else {
      // Если первое число отрицательное (+ - +), создаем временную переменную,
      // в которой будет храниться отрицательное значение первого числа
      if (take_bit(v_1, 127)) {
        s21_decimal temp_v_1;
        init_decimal(&temp_v_1);
        s21_negate(v_1, &temp_v_1);
        put_scale(&temp_v_1, take_scale(v_1));

        // Если |v_1| > |v_2|, выполняем вычитание (|v_1| - |v_2|) и
        // устанавливаем знак результата в отрицательный
        if (s21_is_greater(temp_v_1, v_2)) {
          sub_help(temp_v_1, v_2, result);
          put_bit(result, 127);
        }
        // Если |v_1| < |v_2|, выполняем вычитание (|v_2| - |v_1|)
        else if (s21_is_less(temp_v_1, v_2)) {
          sub_help(v_2, temp_v_1, result);
        }
        // Если |v_1| == |v_2|, результат равен нулю
        else {
          init_decimal(result);
        }
      }
      // Если второе число отрицательное (+  +  -), выполняем вычитание в
      // зависимости от их значений
      else {
        // Если |v_1| > |v_2|, выполняем вычитание (|v_1| - |v_2|)
        if (s21_is_greater(v_1, v_2)) {
          sub_help(v_1, v_2, result);
        }
        // Если |v_1| < |v_2|, выполняем вычитание (|v_2| - |v_1|) и
        // устанавливаем знак результата в отрицательный
        else if (s21_is_less(v_1, v_2)) {
          sub_help(v_2, v_1, result);
          put_bit(result, 127);
        }
        // Если |v_1| == |v_2|, результат равен нулю
        else {
          init_decimal(result);
        }
      }
    }
  }
  // Если произошло переполнение буфера, устанавливаем соответствующий статус
  else {
    statys = buffer_overflow(v_1, v_2, PLUS);
    if (result) {
      init_decimal(result);
    }
  }

  return statys;
}

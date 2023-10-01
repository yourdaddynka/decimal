
#include <check.h>

#include "../s21_decimal.h"
START_TEST(test_s21_add_1) {
  s21_decimal test_v_1 = {{0, 0, 0, 0}};
  s21_decimal test_v_2 = {{0, 0, 0, 0}};
  s21_decimal result_dec = {{0, 0, 0, 0}};
  int result_int = 0;
  s21_from_int_to_decimal(1899999, &test_v_1);
  s21_from_int_to_decimal(100001, &test_v_2);
  s21_add(test_v_1, test_v_2, &result_dec);
  s21_from_decimal_to_int(result_dec, &result_int);
  ck_assert_int_eq(result_int, 2000000);
}
END_TEST

START_TEST(test_s21_add_2) {
  s21_decimal test_v_1 = {{0, 0, 0, 0}};
  s21_decimal test_v_2 = {{0, 0, 0, 0}};
  s21_decimal result_dec = {{0, 0, 0, 0}};
  int result_int;
  s21_from_int_to_decimal(199421, &test_v_1);
  s21_from_int_to_decimal(-4433, &test_v_2);
  s21_add(test_v_1, test_v_2, &result_dec);
  s21_from_decimal_to_int(result_dec, &result_int);
  ck_assert_int_eq(result_int, 199421 + (-4433));
}
END_TEST

START_TEST(test_s21_add_3) {
  s21_decimal test_v_1 = {{0, 0, 0, 0}};
  s21_decimal test_v_2 = {{0, 0, 0, 0}};
  s21_decimal result_dec = {{0, 0, 0, 0}};
  int result_int;
  s21_from_int_to_decimal(-199421, &test_v_1);
  s21_from_int_to_decimal(4433, &test_v_2);
  s21_add(test_v_1, test_v_2, &result_dec);
  s21_from_decimal_to_int(result_dec, &result_int);
  ck_assert_int_eq(result_int, -199421 + 4433);
}
END_TEST

START_TEST(test_s21_add_4) {
  s21_decimal test_v_1 = {{0, 0, 0, 0}};
  s21_decimal test_v_2 = {{0, 0, 0, 0}};
  s21_decimal result_dec = {{0, 0, 0, 0}};
  s21_from_int_to_decimal(-199421, &test_v_1);
  s21_from_int_to_decimal(-4433, &test_v_2);
  s21_add(test_v_1, test_v_2, &result_dec);
}
END_TEST

START_TEST(test_s21_add_5) {
  s21_decimal test_v_1 = {{10000, 3, 10, 0}};
  s21_decimal test_v_2 = {{5000, 2, 500, 0}};
  s21_decimal result_dec = {{0, 0, 0, 0}};
  s21_add(test_v_1, test_v_2, &result_dec);
  ck_assert_uint_eq(result_dec.bits[0], 10000 + 5000);
  ck_assert_uint_eq(result_dec.bits[1], 3 + 2);
  ck_assert_uint_eq(result_dec.bits[2], 10 + 500);
}
END_TEST

START_TEST(test_s21_add_6) {
  s21_decimal test_v_1 = {{4294967295, 10, 10, 0}};
  s21_decimal test_v_2 = {{1, 2, 20, 0}};
  s21_decimal result_dec = {{0, 0, 0, 0}};
  s21_add(test_v_1, test_v_2, &result_dec);
  ck_assert_uint_eq(result_dec.bits[0], 0);
  ck_assert_uint_eq(result_dec.bits[1], 13);
  ck_assert_uint_eq(result_dec.bits[2], 30);
}
END_TEST

START_TEST(test_s21_add_7) {
  s21_decimal test_v_1 = {{4294967295, 4294967295, 4294967295, 0}};
  s21_decimal test_v_2 = {{1, 1, 1, 0}};
  s21_decimal result_dec = {{0, 0, 0, 0}};
  int result = s21_add(test_v_1, test_v_2, &result_dec);
  ck_assert_int_eq(result, 1);
}
END_TEST

START_TEST(test_s21_add_8) {
  s21_decimal test_v_1 = {{4294967295, 4294967295, 4294967295, 0}};
  s21_decimal test_v_2 = {{1, 1, 1, 0}};
  put_bit(&test_v_1, 127);
  put_bit(&test_v_2, 127);
  s21_decimal result_dec = {{0, 0, 0, 0}};
  int result = s21_add(test_v_1, test_v_2, &result_dec);
  ck_assert_int_eq(result, 2);
}
END_TEST

START_TEST(test_s21_add_9) {}
END_TEST

START_TEST(test_s21_add_10) {
  s21_decimal test_v_1 = {{4294967294, 4294967295, 4294967295, 0}};
  s21_decimal test_v_2 = {{1, 0, 0, 0}};
  s21_decimal result_dec = {{0, 0, 0, 0}};
  s21_add(test_v_1, test_v_2, &result_dec);
  ck_assert_uint_eq(result_dec.bits[0], 4294967295);
  ck_assert_uint_eq(result_dec.bits[1], 4294967295);
  ck_assert_uint_eq(result_dec.bits[2], 4294967295);
  ck_assert_uint_eq(result_dec.bits[3], 0);
}
END_TEST

START_TEST(test_s21_add_11) {
  s21_decimal src1, src2, result;
  int a = -1234;
  float b = 1.234;
  float res_origin = -1232.766;
  float res_our;
  s21_from_int_to_decimal(a, &src1);
  s21_from_float_to_decimal(b, &src2);
  s21_add(src1, src2, &result);
  s21_from_decimal_to_float(result, &res_our);
  ck_assert_float_eq(res_our, res_origin);
}
END_TEST

START_TEST(test_s21_add_12) {
  s21_decimal src1, src2, result;

  int a = -1234;
  float b = -1.234;
  float res_origin = -1235.234;
  float res_our;
  s21_from_int_to_decimal(a, &src1);
  s21_from_float_to_decimal(b, &src2);
  s21_add(src1, src2, &result);
  s21_from_decimal_to_float(result, &res_our);
  ck_assert_float_eq(res_our, res_origin);
}
END_TEST

START_TEST(test_s21_add_13) {
  s21_decimal src1, src2, result;
  float a = -1234;
  float b = -221.23401;
  float res_origin = -1455.234;
  float res_our;
  s21_from_float_to_decimal(a, &src1);
  s21_from_float_to_decimal(b, &src2);
  s21_add(src1, src2, &result);
  s21_from_decimal_to_float(result, &res_our);
  ck_assert_float_eq(res_our, res_origin);
}
END_TEST

START_TEST(test_s21_add_14) {
  s21_decimal src1, src2, result;
  float a = -9403;
  float b = 0.00234;
  float res_origin = -9402.9976600;
  float res_our;
  s21_from_float_to_decimal(a, &src1);
  s21_from_float_to_decimal(b, &src2);
  s21_add(src1, src2, &result);
  s21_from_decimal_to_float(result, &res_our);
  ck_assert_float_eq(res_our, res_origin);
}
END_TEST

START_TEST(test_s21_add_15) {
  s21_decimal src1, src2, result;
  float a = -940.3;
  float b = 0.234;
  float res_origin = -940.0660000;
  float res_our;
  s21_from_float_to_decimal(a, &src1);
  s21_from_float_to_decimal(b, &src2);
  s21_add(src1, src2, &result);
  s21_from_decimal_to_float(result, &res_our);
  ck_assert_float_eq(res_our, res_origin);
}
END_TEST

START_TEST(test_s21_add_16) {
  s21_decimal src1, src2, result;
  float a = -0.940301;
  float b = 22.023401;
  float res_origin = 21.0831;
  float res_our;
  s21_from_float_to_decimal(a, &src1);
  s21_from_float_to_decimal(b, &src2);
  s21_add(src1, src2, &result);
  s21_from_decimal_to_float(result, &res_our);
  ck_assert_float_eq(res_our, res_origin);
}
END_TEST

START_TEST(test_s21_add_17) {
  s21_decimal src1, src2, result;
  float a = -0.9403;
  float b = -112.0234;
  float res_origin = -112.9637;
  float res_our;
  s21_from_float_to_decimal(a, &src1);
  s21_from_float_to_decimal(b, &src2);
  s21_add(src1, src2, &result);
  s21_from_decimal_to_float(result, &res_our);
  ck_assert_float_eq(res_our, res_origin);
}
END_TEST

START_TEST(test_s21_add_18) {
  s21_decimal src1, src2, result;
  float a = -0.94e03;
  float b = -112.0234;
  float res_origin = -1052.0234;
  float res_our;
  s21_from_float_to_decimal(a, &src1);
  s21_from_float_to_decimal(b, &src2);
  s21_add(src1, src2, &result);
  s21_from_decimal_to_float(result, &res_our);
  ck_assert_float_eq(res_our, res_origin);
}
END_TEST

START_TEST(test_s21_add_19) {
  s21_decimal src1, src2, result;
  float a = -0.94e03;
  float b = -112.0e2;
  float res_origin = -12140;
  float res_our;
  s21_from_float_to_decimal(a, &src1);
  s21_from_float_to_decimal(b, &src2);
  s21_add(src1, src2, &result);
  s21_from_decimal_to_float(result, &res_our);
  ck_assert_float_eq(res_our, res_origin);
}
END_TEST

START_TEST(test_s21_add_20) {
  s21_decimal src1, src2, result;
  src1.bits[3] = 0x300000;
  src1.bits[2] = 0;
  src1.bits[1] = 0xF;
  src1.bits[0] = 0x67E4FEEF;
  src2.bits[3] = 0x300000;
  src2.bits[2] = 0;
  src2.bits[1] = 0xFF;
  src2.bits[0] = 0x67E4FFFF;
  s21_decimal result_origin;
  result_origin.bits[3] = 0x300000;
  result_origin.bits[2] = 0;
  result_origin.bits[1] = 0x10E;
  result_origin.bits[0] = 0xCFC9FEEE;
  s21_add(src1, src2, &result);
  ck_assert_int_eq(result_origin.bits[3], result.bits[3]);
  ck_assert_int_eq(result_origin.bits[2], result.bits[2]);
  ck_assert_int_eq(result_origin.bits[1], result.bits[1]);
  ck_assert_int_eq(result_origin.bits[0], result.bits[0]);
}
END_TEST

START_TEST(test_s21_add_21) {
  s21_decimal src1, src2, result;
  src1.bits[3] = 0x30000;
  src1.bits[2] = 0;
  src1.bits[1] = 0xFF;
  src1.bits[0] = 0x67E4F;
  src2.bits[3] = 0x60000;
  src2.bits[2] = 0;
  src2.bits[1] = 0xEA;
  src2.bits[0] = 0x67E4F;
  s21_decimal result_origin;
  result_origin.bits[3] = 0x60000;
  result_origin.bits[2] = 0;
  result_origin.bits[1] = 0x3E502;
  result_origin.bits[0] = 0x1963E2E7;
  s21_add(src1, src2, &result);
  ck_assert_int_eq(result_origin.bits[3], result.bits[3]);
  ck_assert_int_eq(result_origin.bits[2], result.bits[2]);
  ck_assert_int_eq(result_origin.bits[1], result.bits[1]);
  ck_assert_int_eq(result_origin.bits[0], result.bits[0]);
}
END_TEST

START_TEST(test_s21_add_22) {
  s21_decimal test_v_1 = {{4294967295, 4294967295, 4294967290, 0}};
  s21_decimal test_v_2 = {{100, 0, 0, 0}};
  s21_decimal result_dec = {{0, 0, 0, 0}};
  s21_add(test_v_1, test_v_2, &result_dec);
  ck_assert_int_eq(result_dec.bits[0], 99);
  ck_assert_int_eq(result_dec.bits[1], 0);
  ck_assert_int_eq(result_dec.bits[2], 4294967291);
  ck_assert_int_eq(result_dec.bits[3], 0);
}
END_TEST

START_TEST(test_s21_add_23) {
  s21_decimal test_v_1 = {{4294967295, 4294967295, 4294967290, 131072}};
  s21_decimal test_v_2 = {{0, 1, 0, 131072}};
  s21_decimal result_dec = {{0, 0, 0, 0}};
  s21_add(test_v_1, test_v_2, &result_dec);
  ck_assert_int_eq(result_dec.bits[0], 4294967295);
  ck_assert_int_eq(result_dec.bits[1], 0);
  ck_assert_int_eq(result_dec.bits[2], 4294967291);
  ck_assert_int_eq(result_dec.bits[3], 131072);
}
END_TEST

START_TEST(test_s21_add_24) {
  s21_decimal test_v_1 = {{4294967295, 4294967295, 4294967290, 131072}};
  s21_decimal test_v_2 = {{5, 0, 1, 131072}};
  s21_decimal result_dec = {{0, 0, 0, 0}};
  s21_add(test_v_1, test_v_2, &result_dec);
  ck_assert_int_eq(result_dec.bits[0], 4);
  ck_assert_int_eq(result_dec.bits[1], 0);
  ck_assert_int_eq(result_dec.bits[2], 4294967292);
  ck_assert_int_eq(result_dec.bits[3], 131072);
}
END_TEST

START_TEST(test_s21_add_25) {
  s21_decimal test_v_1 = {{428, 0, 0, 0}};
  s21_decimal test_v_2 = {{165, 0, 0, 131072}};
  s21_decimal result_dec = {{0, 0, 0, 0}};
  s21_add(test_v_1, test_v_2, &result_dec);
  ck_assert_int_eq(result_dec.bits[0], 42965);
  ck_assert_int_eq(result_dec.bits[1], 0);
  ck_assert_int_eq(result_dec.bits[2], 0);
  ck_assert_int_eq(result_dec.bits[3], 131072);
}
END_TEST

START_TEST(test_s21_sub_1) {
  s21_decimal src1, src2, result;
  int a = 9403;
  int b = 202;
  int res_origin = 9201;
  int res_our;
  s21_from_int_to_decimal(a, &src1);
  s21_from_int_to_decimal(b, &src2);
  s21_sub(src1, src2, &result);
  s21_from_decimal_to_int(result, &res_our);
  ck_assert_int_eq(res_our, res_origin);
}
END_TEST

START_TEST(test_s21_sub_2) {
  s21_decimal src1, src2, result;
  int a = 9403;
  float b = 202.098;
  float res_origin = 9200.902;
  float res_our;
  s21_from_int_to_decimal(a, &src1);
  s21_from_float_to_decimal(b, &src2);
  s21_sub(src1, src2, &result);
  s21_from_decimal_to_float(result, &res_our);
  ck_assert_float_eq(res_our, res_origin);
}
END_TEST

START_TEST(test_s21_sub_3) {
  s21_decimal src1, src2, result;
  float a = -9403;
  float b = 202.098;
  float res_origin = a - b;
  float res_our;
  s21_from_float_to_decimal(a, &src1);
  s21_from_float_to_decimal(b, &src2);
  s21_sub(src1, src2, &result);
  s21_from_decimal_to_float(result, &res_our);
  ck_assert_float_eq(res_our, res_origin);
}
END_TEST

START_TEST(test_s21_sub_4) {
  s21_decimal src1, src2, result;
  float a = 9403.0;
  float b = 202.0098421232;
  float res_origin = 9200.9901578768;
  float res_our;
  s21_from_float_to_decimal(a, &src1);
  s21_from_float_to_decimal(b, &src2);
  s21_sub(src1, src2, &result);
  s21_from_decimal_to_float(result, &res_our);
  ck_assert_float_eq(res_our, res_origin);
}
END_TEST

START_TEST(test_s21_sub_5) {
  s21_decimal src1, src2, result;
  float a = -9403.000;
  float b = 202.0098421232;
  float res_origin = -9605.0098421232;
  float res_our;
  s21_from_float_to_decimal(a, &src1);
  s21_from_float_to_decimal(b, &src2);
  s21_sub(src1, src2, &result);
  s21_from_decimal_to_float(result, &res_our);
  ck_assert_float_eq(res_our, res_origin);
}
END_TEST

START_TEST(test_s21_sub_6) {
  s21_decimal src1, src2, result;
  float a = -9403.0e2;
  int b = -202;
  float res_origin = a - b;
  float res_our;
  s21_from_float_to_decimal(a, &src1);
  s21_from_int_to_decimal(b, &src2);
  s21_sub(src1, src2, &result);
  s21_from_decimal_to_float(result, &res_our);
  ck_assert_float_eq(res_our, res_origin);
}
END_TEST

START_TEST(test_s21_sub_7) {
  s21_decimal src1, src2, result;
  src1.bits[3] = 0b00000000000000010000000000000000;
  src1.bits[2] = 0;
  src1.bits[1] = 0;
  src1.bits[0] = 0b00000000000000000110011011110000;
  src2.bits[3] = 0b00000000000000110000000000000000;
  src2.bits[2] = 0;
  src2.bits[1] = 0;
  src2.bits[0] = 0b00000000000001000101000111010110;
  s21_decimal result_origin;
  result_origin.bits[3] = 0b00000000000000110000000000000000;
  result_origin.bits[2] = 0;
  result_origin.bits[1] = 0;
  result_origin.bits[0] = 0b00000000001000111110001111101010;
  s21_sub(src1, src2, &result);
  ck_assert_int_eq(result_origin.bits[3], result.bits[3]);
  ck_assert_int_eq(result_origin.bits[2], result.bits[2]);
  ck_assert_int_eq(result_origin.bits[1], result.bits[1]);
  ck_assert_int_eq(result_origin.bits[0], result.bits[0]);
}
END_TEST

START_TEST(test_s21_sub_8) {
  s21_decimal test_v_1 = {{1, 10, 0, 0}};
  s21_decimal test_v_2 = {{5000, 5, 0, 0}};
  s21_decimal result_dec = {{0, 0, 0, 0}};
  s21_sub(test_v_1, test_v_2, &result_dec);
  ck_assert_uint_eq(result_dec.bits[0], 4294962297);
  ck_assert_uint_eq(result_dec.bits[1], 4);
  ck_assert_uint_eq(result_dec.bits[2], 0);
}
END_TEST

START_TEST(test_s21_sub_9) {
  s21_decimal test_v_1 = {{1, 4, 5, 0}};
  s21_decimal test_v_2 = {{5000, 5, 0, 0}};
  s21_decimal result_dec = {{0, 0, 0, 0}};
  s21_sub(test_v_1, test_v_2, &result_dec);
  ck_assert_uint_eq(result_dec.bits[0], 4294962297);
  ck_assert_uint_eq(result_dec.bits[1], 4294967294);
  ck_assert_uint_eq(result_dec.bits[2], 4);
}
END_TEST

START_TEST(test_s21_sub_10) {
  s21_decimal test_v_1 = {{1, 0, 5, 0}};
  s21_decimal test_v_2 = {{5000, 5, 0, 0}};
  s21_decimal result_dec = {{0, 0, 0, 0}};
  s21_sub(test_v_1, test_v_2, &result_dec);
  ck_assert_uint_eq(result_dec.bits[0], 4294962297);
  ck_assert_uint_eq(result_dec.bits[1], 4294967290);
  ck_assert_uint_eq(result_dec.bits[2], 4);
}
END_TEST

START_TEST(test_s21_sub_11) {
  s21_decimal test_v_1 = {{1, 0, 0, 0}};
  s21_decimal test_v_2 = {{5000, 0, 0, 0}};
  put_bit(&test_v_2, 127);
  s21_decimal result_dec = {{0, 0, 0, 0}};
  s21_sub(test_v_1, test_v_2, &result_dec);
  ck_assert_uint_eq(result_dec.bits[0], 5001);
  ck_assert_uint_eq(result_dec.bits[1], 0);
  ck_assert_uint_eq(result_dec.bits[2], 0);
  ck_assert_uint_eq(result_dec.bits[3], 0);
}
END_TEST

START_TEST(test_s21_mul_1) {
  s21_decimal src1 = {{0, 0, 0, 0}};
  s21_decimal src2 = {{0, 0, 0, 0}};
  s21_decimal result = {{0, 0, 0, 0}};
  float a = 9403.0e2;
  int b = 202;
  float res_our_dec = 0.0;
  s21_from_float_to_decimal(a, &src1);
  s21_from_int_to_decimal(b, &src2);
  float res_origin = 189940600;
  s21_mul(src1, src2, &result);
  s21_from_decimal_to_float(result, &res_our_dec);
  ck_assert_float_eq(res_our_dec, res_origin);
}
END_TEST

START_TEST(test_s21_mul_2) {
  s21_decimal src1 = {{0, 0, 0, 0}};
  s21_decimal src2 = {{0, 0, 0, 0}};
  s21_decimal result = {{0, 0, 0, 0}};
  float a = 9403.0;
  float b = 9403.0;
  float res_our_dec = 0.0;
  s21_from_float_to_decimal(a, &src1);
  s21_from_float_to_decimal(b, &src2);
  float res_origin = 88416409;
  s21_mul(src1, src2, &result);
  s21_from_decimal_to_float(result, &res_our_dec);
  ck_assert_float_eq(res_our_dec, res_origin);
}
END_TEST

START_TEST(test_s21_mul_3) {
  s21_decimal src1 = {{0, 0, 0, 0}};
  s21_decimal src2 = {{0, 0, 0, 0}};
  s21_decimal result = {{0, 0, 0, 0}};
  float a = 9403;
  float b = 202;
  float res_our_dec = 0.0;
  s21_from_float_to_decimal(a, &src1);
  s21_from_float_to_decimal(b, &src2);
  float res_origin = 1899406;
  s21_mul(src1, src2, &result);
  s21_from_decimal_to_float(result, &res_our_dec);
  ck_assert_float_eq(res_our_dec, res_origin);
}
END_TEST

START_TEST(test_s21_mul_4) {
  s21_decimal src1 = {{0, 0, 0, 0}};
  s21_decimal src2 = {{0, 0, 0, 0}};
  s21_decimal result = {{0, 0, 0, 0}};
  float a = -32768;
  float b = 2;
  float res_our_dec = 0.0;
  s21_from_float_to_decimal(a, &src1);
  s21_from_float_to_decimal(b, &src2);
  float res_origin = -65536;
  s21_mul(src1, src2, &result);
  s21_from_decimal_to_float(result, &res_our_dec);
  ck_assert_float_eq(res_our_dec, res_origin);
}
END_TEST

START_TEST(test_s21_mul_5) {
  s21_decimal src1 = {{0, 0, 0, 0}};
  s21_decimal src2 = {{0, 0, 0, 0}};
  s21_decimal result = {{0, 0, 0, 0}};
  float a = -32768;
  float b = 32768;
  float res_our_dec = 0.0;
  s21_from_float_to_decimal(a, &src1);
  s21_from_float_to_decimal(b, &src2);
  float res_origin = -1073741824;
  s21_mul(src1, src2, &result);
  s21_from_decimal_to_float(result, &res_our_dec);
  ck_assert_float_eq(res_our_dec, res_origin);
}
END_TEST

START_TEST(test_s21_mul_6) {
  s21_decimal src1 = {{0, 1, 0, 0}};
  s21_decimal src2 = {{1, 0, 0, 0}};
  s21_decimal result = {{0, 0, 0, 0}};
  float res_our_dec = 0.0;
  float res_origin = 4294967296;
  s21_mul(src1, src2, &result);
  s21_from_decimal_to_float(result, &res_our_dec);
  ck_assert_float_eq(res_our_dec, res_origin);
}
END_TEST

START_TEST(test_s21_mul_7) {
  s21_decimal src1 = {{4294967295, 4294967295, 4294967295, 0}};
  s21_decimal src2 = {{2, 0, 0, 0}};
  s21_decimal result = {{0, 0, 0, 0}};
  int res = s21_mul(src1, src2, &result);
  ck_assert_int_eq(res, 1);
}
END_TEST

START_TEST(test_s21_mul_8) {
  s21_decimal src1 = {{4294967295, 4294967295, 4294967295, 2147483648}};
  s21_decimal src2 = {{2, 0, 0, 0}};
  s21_decimal result = {{0, 0, 0, 0}};
  int res = s21_mul(src1, src2, &result);
  ck_assert_int_eq(res, 2);
}
END_TEST

// START_TEST(test_s21_mul_9) { плохой тест
//   s21_decimal src1 = {{10000, 1000, 0, 131072}};
//   s21_decimal src2 = {{0, 0, 0, 0}};
//   s21_decimal result = {{0, 0, 0, 0}};
//   s21_from_float_to_decimal(1.01, &src2);
//   s21_mul(src1, src2, &result);
//   ck_assert_int_eq(result.bits[0], 0);
//   ck_assert_int_eq(result.bits[1], 0);
//   ck_assert_int_eq(result.bits[2], 0);
// }
// END_TEST

START_TEST(test_s21_mul_10) {
  s21_decimal val1 = {{0, 0, 0, 0}};
  s21_decimal val2 = {{0, 0, 0, 0}};
  s21_decimal res = {{0, 0, 0, 0}};
  float n1 = -5.6e-15;
  float n2 = 1.5e-15;
  s21_from_float_to_decimal(n1, &val1);
  s21_from_float_to_decimal(n2, &val2);
  ck_assert_int_eq(res.bits[0], 0);
  ck_assert_int_eq(res.bits[1], 0);
  ck_assert_int_eq(res.bits[2], 0);
}
END_TEST

START_TEST(test_s21_mul_11) {
  s21_decimal val1 = {{10000, 0, 0, 131072}};
  s21_decimal val2 = {{100000, 0, 0, 131072}};
  s21_decimal res = {{0, 0, 0, 0}};
  s21_mul(val1, val2, &res);
  ck_assert_int_eq(res.bits[0], 100000);
  ck_assert_int_eq(res.bits[1], 0);
  ck_assert_int_eq(res.bits[2], 0);
  ck_assert_int_eq(res.bits[2], 0);
}
END_TEST

START_TEST(test_s21_div_1) {
  s21_decimal src1 = {{25, 0, 0, 0}};
  s21_decimal src2 = {{5, 0, 0, 0}};
  s21_decimal result = {{0, 0, 0, 0}};
  s21_div(src1, src2, &result);
  ck_assert_int_eq(result.bits[0], 5);
  ck_assert_int_eq(result.bits[1], 0);
  ck_assert_int_eq(result.bits[2], 0);
}
END_TEST

START_TEST(test_s21_div_2) {
  s21_decimal src1 = {{25, 0, 0, 0}};
  s21_decimal src2 = {{0, 0, 0, 0}};
  s21_decimal result = {{0, 0, 0, 0}};
  int res = s21_div(src1, src2, &result);
  ck_assert_int_eq(res, 3);
}
END_TEST

START_TEST(test_s21_div_3) {
  s21_decimal src1 = {{0, 1, 0, 0}};
  s21_decimal src2 = {{2, 0, 0, 0}};
  s21_decimal result = {{0, 0, 0, 0}};
  s21_div(src1, src2, &result);
  ck_assert_int_eq(result.bits[0], 2147483648);
  ck_assert_int_eq(result.bits[1], 0);
  ck_assert_int_eq(result.bits[2], 0);
}
END_TEST

START_TEST(test_s21_div_4) {
  s21_decimal src1 = {{1000, 0, 0, 65536}};  // 65536
  s21_decimal src2 = {{2, 0, 0, 0}};
  s21_decimal result = {{0, 0, 0, 0}};
  s21_div(src1, src2, &result);
  ck_assert_int_eq(result.bits[0], 50);
  ck_assert_int_eq(result.bits[1], 0);
  ck_assert_int_eq(result.bits[2], 0);
}
END_TEST

START_TEST(test_s21_div_5) {
  s21_decimal src1 = {{1000, 0, 0, 0}};
  s21_decimal src2 = {{5, 0, 0, 65536}};
  s21_decimal result = {{0, 0, 0, 0}};
  s21_div(src1, src2, &result);
  ck_assert_int_eq(result.bits[0], 2000);
  ck_assert_int_eq(result.bits[1], 0);
  ck_assert_int_eq(result.bits[2], 0);
}
END_TEST

START_TEST(test_s21_div_6) {
  s21_decimal src1 = {{1000, 0, 0, 131072}};
  s21_decimal src2 = {{50, 0, 0, 65536}};
  s21_decimal result = {{0, 0, 0, 0}};
  s21_div(src1, src2, &result);
  ck_assert_int_eq(result.bits[0], 2);
  ck_assert_int_eq(result.bits[1], 0);
  ck_assert_int_eq(result.bits[2], 0);
}
END_TEST

START_TEST(test_s21_div_7) {
  s21_decimal src1 = {{S21_MAX_UINT, S21_MAX_UINT, S21_MAX_UINT, 0}};
  s21_decimal src2 = {{5, 0, 0, 65536}};  // 0,5
  s21_decimal result = {{0, 0, 0, 0}};
  int err = s21_div(src1, src2, &result);
  ck_assert_int_eq(err, 1);

  ck_assert_int_eq(result.bits[0], 0);
  ck_assert_int_eq(result.bits[1], 0);
  ck_assert_int_eq(result.bits[2], 0);
  ck_assert_int_eq(result.bits[3], 0);
}
END_TEST

START_TEST(test_s21_div_8) {
  s21_decimal src1 = {{0, 12, S21_MAX_UINT, 0}};
  s21_decimal src2 = {{5, 0, 0, 65536}};  // 0,5
  s21_decimal result = {{0, 0, 0, 0}};
  int err = s21_div(src1, src2, &result);
  ck_assert_int_eq(err, 1);

  ck_assert_int_eq(result.bits[0], 0);
  ck_assert_int_eq(result.bits[1], 0);
  ck_assert_int_eq(result.bits[2], 0);
  ck_assert_int_eq(result.bits[3], 0);
}
END_TEST

// START_TEST(test_s21_mod_1) {
//   s21_decimal src1 = {{1, 0, 0, 0}};
//   s21_decimal src2 = {{2, 0, 0, 0}};
//   s21_decimal result = {{0, 0, 0, 0}};
//   s21_mod(src1, src2, &result);
//   ck_assert_int_eq(result.bits[0], 1);
//   ck_assert_int_eq(result.bits[1], 0);
//   ck_assert_int_eq(result.bits[2], 0);
// }
// END_TEST

// START_TEST(test_s21_mod_2) {
//   s21_decimal src1 = {{1, 0, 0, 0}};
//   s21_decimal src2 = {{0, 0, 0, 0}};
//   s21_decimal result = {{0, 0, 0, 0}};
//   int res = s21_mod(src1, src2, &result);
//   ck_assert_int_eq(res, 3);
// }
// END_TEST

// START_TEST(test_s21_mod_3) {
//   s21_decimal src1 = {{1010, 0, 0, 65536}};
//   s21_decimal src2 = {{10, 0, 0, 0}};
//   s21_decimal result = {{0, 0, 0, 0}};
//   s21_mod(src1, src2, &result);
//   ck_assert_int_eq(result.bits[0], 10);
//   ck_assert_int_eq(result.bits[1], 0);
//   ck_assert_int_eq(result.bits[2], 0);
//   ck_assert_int_eq(result.bits[3], 65536);
// }
// END_TEST

// START_TEST(test_s21_mod_4) {
//   s21_decimal src1 = {{101, 0, 0, 0}};
//   s21_decimal src2 = {{100, 0, 0, 65536}};
//   s21_decimal result = {{0, 0, 0, 0}};
//   s21_mod(src1, src2, &result);
//   ck_assert_int_eq(result.bits[0], 10);
//   ck_assert_int_eq(result.bits[1], 0);
//   ck_assert_int_eq(result.bits[2], 0);
//   ck_assert_int_eq(result.bits[3], 65536);
// }
// END_TEST

START_TEST(test_s21_is_less_1) {
  s21_decimal test_v_1 = {{10, 0, 0, 0}};
  s21_decimal test_v_2 = {{15, 0, 0, 0}};
  ck_assert_int_eq(s21_is_less(test_v_1, test_v_2), 1);
}
END_TEST

START_TEST(test_s21_is_less_2) {
  s21_decimal test_v_1 = {{6739, 0, 0, 0}};
  s21_decimal test_v_2 = {{19993, 0, 0, 0}};
  ck_assert_int_eq(s21_is_less(test_v_1, test_v_2), 1);
}
END_TEST

START_TEST(test_s21_is_less_3) {
  s21_decimal test_v_1 = {{19993, 0, 0, 0}};
  s21_decimal test_v_2 = {{6739, 0, 0, 0}};
  ck_assert_int_eq(s21_is_less(test_v_1, test_v_2), 0);
}
END_TEST

START_TEST(test_s21_is_less_4) {
  s21_decimal test_v_1 = {{19993, 0, 0, 0}};
  s21_decimal test_v_2 = {{6739, 0, 0, 2147483648}};
  ck_assert_int_eq(s21_is_less(test_v_1, test_v_2), 0);
}
END_TEST

START_TEST(test_s21_is_less_5) {
  s21_decimal test_v_1 = {{19993, 0, 0, 0}};
  s21_decimal test_v_2 = {{19993, 0, 0, 0}};
  ck_assert_int_eq(s21_is_less(test_v_1, test_v_2), 0);
}
END_TEST

START_TEST(test_s21_is_less_6) {
  s21_decimal test_v_1 = {{19993, 0, 0, 0}};
  s21_decimal test_v_2 = {{19993, 0, 0, 131072}};
  ck_assert_int_eq(s21_is_less(test_v_1, test_v_2), 0);
}
END_TEST

START_TEST(test_s21_is_less_7) {
  s21_decimal test_v_1 = {{0, 1, 0, 0}};
  s21_decimal test_v_2 = {{19993, 0, 0, 0}};
  ck_assert_int_eq(s21_is_less(test_v_1, test_v_2), 0);
}
END_TEST

START_TEST(test_s21_is_less_8) {
  s21_decimal test_v_1 = {{19993, 1, 0, 2147483648}};
  s21_decimal test_v_2 = {{19993, 0, 0, 0}};
  ck_assert_int_eq(s21_is_less(test_v_1, test_v_2), 1);
}
END_TEST

START_TEST(test_s21_is_less_or_equal_1) {
  s21_decimal test_v_1 = {{0, 0, 0, 0}};
  s21_decimal test_v_2 = {{0, 0, 0, 0}};
  ck_assert_int_eq(s21_is_less_or_equal(test_v_1, test_v_2), 1);
}
END_TEST

START_TEST(test_s21_is_less_or_equal_2) {
  s21_decimal test_v_1 = {{5000, 0, 0, 0}};
  s21_decimal test_v_2 = {{5001, 0, 0, 0}};
  ck_assert_int_eq(s21_is_less_or_equal(test_v_1, test_v_2), 1);
}
END_TEST

START_TEST(test_s21_is_less_or_equal_3) {
  s21_decimal test_v_1 = {{5000, 0, 0, 0}};
  s21_decimal test_v_2 = {{5000, 0, 0, 2147483648}};
  ck_assert_int_eq(s21_is_less_or_equal(test_v_1, test_v_2), 0);
}
END_TEST

START_TEST(test_s21_is_less_or_equal_4) {
  s21_decimal test_v_1 = {{5000, 0, 0, 0}};
  s21_decimal test_v_2 = {{5000, 0, 0, 131072}};
  ck_assert_int_eq(s21_is_less_or_equal(test_v_1, test_v_2), 0);
}
END_TEST

START_TEST(test_s21_is_less_or_equal_5) {
  s21_decimal test_v_1 = {{0, 1, 0, 0}};
  s21_decimal test_v_2 = {{0, 1, 0, 0}};
  ck_assert_int_eq(s21_is_less_or_equal(test_v_1, test_v_2), 1);
}
END_TEST

START_TEST(test_s21_is_greater_1) {
  s21_decimal dst1, dst2;
  s21_from_float_to_decimal(1.2345, &dst1);
  s21_from_float_to_decimal(1.2, &dst2);
  ck_assert_int_eq(s21_is_greater(dst1, dst2), 1);
  ck_assert_int_eq(s21_is_greater(dst2, dst1), 0);
}
END_TEST

START_TEST(test_s21_is_greater_2) {
  s21_decimal dst1, dst2;
  s21_from_float_to_decimal(-1.2345, &dst1);
  s21_from_float_to_decimal(-1.2, &dst2);
  ck_assert_int_eq(s21_is_greater(dst1, dst2), 0);
  ck_assert_int_eq(s21_is_greater(dst2, dst1), 1);
}
END_TEST

START_TEST(test_s21_is_greater_3) {
  s21_decimal dst1, dst2;
  s21_from_float_to_decimal(1.2345, &dst1);
  s21_from_float_to_decimal(-1.2, &dst2);
  ck_assert_int_eq(s21_is_greater(dst1, dst2), 1);
  ck_assert_int_eq(s21_is_greater(dst2, dst1), 0);
}
END_TEST

START_TEST(test_s21_is_greater_4) {
  s21_decimal dst1, dst2;
  s21_from_float_to_decimal(0.0, &dst1);
  s21_from_float_to_decimal(0.0, &dst2);
  ck_assert_int_eq(s21_is_greater(dst1, dst2), 0);
}
END_TEST

START_TEST(test_s21_is_greater_or_equal_1) {
  s21_decimal test_v_1 = {{0, 0, 0, 0}};
  s21_decimal test_v_2 = {{0, 0, 0, 0}};
  ck_assert_int_eq(s21_is_greater_or_equal(test_v_1, test_v_2), 1);
}
END_TEST

START_TEST(test_s21_is_greater_or_equal_2) {
  s21_decimal test_v_1 = {{5000, 0, 0, 0}};
  s21_decimal test_v_2 = {{5001, 0, 0, 0}};
  ck_assert_int_eq(s21_is_greater_or_equal(test_v_1, test_v_2), 0);
}
END_TEST

START_TEST(test_s21_is_greater_or_equal_3) {
  s21_decimal test_v_1 = {{5000, 0, 0, 0}};
  s21_decimal test_v_2 = {{5000, 0, 0, 131072}};
  ck_assert_int_eq(s21_is_greater_or_equal(test_v_1, test_v_2), 1);
}
END_TEST

START_TEST(test_s21_is_greater_or_equal_4) {
  s21_decimal test_v_1 = {{5000, 0, 0, 0}};
  s21_decimal test_v_2 = {{5000, 0, 0, 2147483648}};
  ck_assert_int_eq(s21_is_greater_or_equal(test_v_1, test_v_2), 1);
}
END_TEST

START_TEST(test_s21_is_greater_or_equal_5) {
  s21_decimal test_v_1 = {{5000, 0, 0, 0}};
  s21_decimal test_v_2 = {{5000, 0, 0, 0}};
  ck_assert_int_eq(s21_is_greater_or_equal(test_v_1, test_v_2), 1);
}
END_TEST

START_TEST(test_s21_is_equal_1) {
  s21_decimal test_v_1 = {{0, 0, 0, 0}};
  s21_decimal test_v_2 = {{0, 0, 0, 0}};
  ck_assert_int_eq(s21_is_equal(test_v_1, test_v_2), 1);
}
END_TEST

START_TEST(test_s21_is_equal_2) {
  s21_decimal test_v_1 = {{5000, 0, 0, 0}};
  s21_decimal test_v_2 = {{5001, 0, 0, 0}};
  ck_assert_int_eq(s21_is_equal(test_v_1, test_v_2), 0);
}
END_TEST

START_TEST(test_s21_is_equal_3) {
  s21_decimal test_v_1 = {{5000, 0, 0, 0}};
  s21_decimal test_v_2 = {{5000, 0, 0, 2147483648}};
  ck_assert_int_eq(s21_is_equal(test_v_1, test_v_2), 0);
}
END_TEST

START_TEST(test_s21_is_equal_4) {
  s21_decimal test_v_1 = {{5000, 0, 0, 0}};
  s21_decimal test_v_2 = {{5000, 0, 0, 131072}};
  ck_assert_int_eq(s21_is_equal(test_v_1, test_v_2), 0);
}
END_TEST

START_TEST(test_s21_is_equal_5) {
  s21_decimal test_v_1 = {{5000, 1, 0, 0}};
  s21_decimal test_v_2 = {{5000, 0, 2, 0}};
  ck_assert_int_eq(s21_is_equal(test_v_1, test_v_2), 0);
}
END_TEST

START_TEST(test_s21_is_not_equal_1) {
  s21_decimal test_v_1 = {{0, 0, 0, 0}};
  s21_decimal test_v_2 = {{0, 0, 0, 0}};
  ck_assert_int_eq(s21_is_not_equal(test_v_1, test_v_2), 0);
}
END_TEST

START_TEST(test_s21_is_not_equal_2) {
  s21_decimal test_v_1 = {{5000, 0, 0, 0}};
  s21_decimal test_v_2 = {{5001, 0, 0, 0}};
  ck_assert_int_eq(s21_is_not_equal(test_v_1, test_v_2), 1);
}
END_TEST

START_TEST(test_s21_is_not_equal_3) {
  s21_decimal test_v_1 = {{5000, 0, 0, 0}};
  s21_decimal test_v_2 = {{5000, 0, 0, 2147483648}};
  ck_assert_int_eq(s21_is_not_equal(test_v_1, test_v_2), 1);
}
END_TEST

START_TEST(test_s21_is_not_equal_4) {
  s21_decimal test_v_1 = {{5000, 0, 0, 0}};
  s21_decimal test_v_2 = {{5000, 0, 0, 131072}};
  ck_assert_int_eq(s21_is_not_equal(test_v_1, test_v_2), 1);
}
END_TEST

START_TEST(test_s21_is_not_equal_5) {
  s21_decimal test_v_1 = {{5000, 1, 0, 0}};
  s21_decimal test_v_2 = {{5000, 0, 2, 0}};
  ck_assert_int_eq(s21_is_not_equal(test_v_1, test_v_2), 1);
}
END_TEST

START_TEST(test_s21_form_int_to_decimal_1) {
  s21_decimal result;
  s21_from_int_to_decimal(0, &result);
  ck_assert_int_eq(result.bits[0], 0);
  ck_assert_int_eq(result.bits[1], 0);
  ck_assert_int_eq(result.bits[2], 0);
  ck_assert_int_eq(result.bits[3], 0);
}
END_TEST

START_TEST(test_s21_form_int_to_decimal_2) {
  s21_decimal result;
  s21_from_int_to_decimal(-128, &result);
  ck_assert_int_eq(result.bits[0], 128);
  ck_assert_int_eq(result.bits[1], 0);
  ck_assert_int_eq(result.bits[2], 0);
  ck_assert_int_eq(result.bits[3], 2147483648);
}
END_TEST

START_TEST(test_s21_form_int_to_decimal_3) {
  s21_decimal result;
  s21_from_int_to_decimal(5000, &result);
  ck_assert_int_eq(result.bits[0], 5000);
  ck_assert_int_eq(result.bits[1], 0);
  ck_assert_int_eq(result.bits[2], 0);
  ck_assert_int_eq(result.bits[3], 0);
}
END_TEST

START_TEST(test_s21_form_int_to_decimal_4) {
  s21_decimal result;
  s21_from_int_to_decimal(-2147483648, &result);
  ck_assert_int_eq(result.bits[0], 2147483648);
  ck_assert_int_eq(result.bits[1], 0);
  ck_assert_int_eq(result.bits[2], 0);
  ck_assert_int_eq(result.bits[3], 2147483648);
}
END_TEST

START_TEST(test_s21_form_int_to_decimal_5) {
  s21_decimal result;
  s21_from_int_to_decimal(2147483647, &result);
  ck_assert_int_eq(result.bits[0], 2147483647);
  ck_assert_int_eq(result.bits[1], 0);
  ck_assert_int_eq(result.bits[2], 0);
  ck_assert_int_eq(result.bits[3], 0);
}
END_TEST

START_TEST(test_s21_form_float_to_decimal_1) {
  s21_decimal result;
  s21_from_float_to_decimal(127.1234, &result);
  ck_assert_int_eq(result.bits[0], 1271234);
  ck_assert_int_eq(result.bits[1], 0);
  ck_assert_int_eq(result.bits[2], 0);
  ck_assert_int_eq(result.bits[3], 262144);
}
END_TEST

START_TEST(test_s21_form_float_to_decimal_2) {
  s21_decimal result;
  s21_from_float_to_decimal(22.14836E+03, &result);
  ck_assert_int_eq(result.bits[0], 2214836);
  ck_assert_int_eq(result.bits[1], 0);
  ck_assert_int_eq(result.bits[2], 0);
  ck_assert_int_eq(result.bits[3], 131072);
}
END_TEST

START_TEST(test_s21_form_float_to_decimal_3) {
  s21_decimal result;
  s21_from_float_to_decimal(1.02E+09, &result);
  ck_assert_int_eq(result.bits[0], 1020000000);
  ck_assert_int_eq(result.bits[1], 0);
  ck_assert_int_eq(result.bits[2], 0);
  ck_assert_int_eq(result.bits[3], 0);
}
END_TEST

START_TEST(test_s21_form_float_to_decimal_4) {
  s21_decimal result;
  s21_from_float_to_decimal(-333.2222, &result);
  ck_assert_int_eq(result.bits[0], 3332222);
  ck_assert_int_eq(result.bits[1], 0);
  ck_assert_int_eq(result.bits[2], 0);
  ck_assert_int_eq(result.bits[3], 2147745792);
}
END_TEST

START_TEST(test_s21_form_float_to_decimal_5) {
  s21_decimal result;
  int res = s21_from_float_to_decimal(1.0 / 0.0, &result);
  ck_assert_int_eq(result.bits[0], 0);
  ck_assert_int_eq(result.bits[1], 0);
  ck_assert_int_eq(result.bits[2], 0);
  ck_assert_int_eq(result.bits[3], 0);
  ck_assert_int_eq(res, 1);
}
END_TEST

START_TEST(test_s21_form_float_to_decimal_6) {
  s21_decimal result;
  int res = s21_from_float_to_decimal(-1.0 / 0.0, &result);
  ck_assert_int_eq(result.bits[0], 0);
  ck_assert_int_eq(result.bits[1], 0);
  ck_assert_int_eq(result.bits[2], 0);
  ck_assert_int_eq(result.bits[3], 0);
  ck_assert_int_eq(res, 1);
}
END_TEST

START_TEST(test_s21_form_float_to_decimal_7) {
  s21_decimal result;
  int res = s21_from_float_to_decimal(0.0 / 0.0, &result);
  ck_assert_int_eq(result.bits[0], 0);
  ck_assert_int_eq(result.bits[1], 0);
  ck_assert_int_eq(result.bits[2], 0);
  ck_assert_int_eq(result.bits[3], 0);
  ck_assert_int_eq(res, 1);
}
END_TEST

START_TEST(test_s21_decimal_to_int_1) {
  int number = 0;
  s21_decimal src = {{2147483647, 0, 0, 0}};
  s21_from_decimal_to_int(src, &number);
  ck_assert_int_eq(number, 2147483647);
}
END_TEST

START_TEST(test_s21_decimal_to_int_2) {
  int number = 0;
  s21_decimal src = {{0, 0, 0, 0}};
  s21_from_decimal_to_int(src, &number);
  ck_assert_int_eq(number, 0);
}
END_TEST

START_TEST(test_s21_decimal_to_int_3) {
  int number = 0;
  s21_decimal src = {{5000, 0, 0, 2147483648}};
  s21_from_decimal_to_int(src, &number);
  ck_assert_int_eq(number, -5000);
}
END_TEST

START_TEST(test_s21_decimal_to_int_4) {
  int number = 0;
  s21_decimal src = {{2147483648, 0, 0, 2147483648}};
  s21_from_decimal_to_int(src, &number);
  ck_assert_int_eq(s21_from_decimal_to_int(src, &number), 1);
}
END_TEST

START_TEST(test_s21_decimal_to_float_1) {
  float number = 0.0;
  s21_decimal src = {{18122, 0, 0, 2147680256}};
  s21_from_decimal_to_float(src, &number);
  ck_assert_float_eq(number, -18.122);
}
END_TEST

START_TEST(test_s21_decimal_to_float_2) {
  float number = 0.0;
  s21_decimal src = {{1812, 0, 0, 2147483648}};
  s21_from_decimal_to_float(src, &number);
  ck_assert_float_eq(number, -1812);
}
END_TEST

START_TEST(test_s21_decimal_to_float_3) {
  float number = 0.0;
  s21_decimal src = {{4294967295, 4294967295, 0, 0}};
  s21_from_decimal_to_float(src, &number);
  ck_assert_float_eq(number, 0xFFFFFFFFFFFFFFFF);
}
END_TEST

START_TEST(test_s21_floor_1) {
  s21_decimal v_1 = {{673988, 0, 0, 262144}};
  s21_decimal result = {{0, 0, 0, 0}};
  s21_floor(v_1, &result);
  ck_assert_float_eq(result.bits[0], 67);
  ck_assert_float_eq(result.bits[1], 0);
  ck_assert_float_eq(result.bits[2], 0);
  ck_assert_float_eq(result.bits[3], 0);
}
END_TEST

START_TEST(test_s21_floor_2) {
  s21_decimal v_1 = {{679988, 0, 0, 262144}};
  s21_decimal result = {{0, 0, 0, 0}};
  s21_floor(v_1, &result);
  ck_assert_float_eq(result.bits[0], 67);
  ck_assert_float_eq(result.bits[1], 0);
  ck_assert_float_eq(result.bits[2], 0);
  ck_assert_float_eq(result.bits[3], 0);
}
END_TEST

START_TEST(test_s21_floor_3) {
  s21_decimal v_1 = {{679988, 0, 0, 2147745796}};
  s21_decimal result = {{0, 0, 0, 0}};
  s21_floor(v_1, &result);
  ck_assert_float_eq(result.bits[0], 68);
  ck_assert_float_eq(result.bits[1], 0);
  ck_assert_float_eq(result.bits[2], 0);
  ck_assert_float_eq(result.bits[3], 2147483648);
}
END_TEST

START_TEST(test_s21_floor_4) {
  s21_decimal v_1 = {{2555, 0, 0, 0}};
  put_scale(&v_1, 2);
  s21_decimal result = {{0, 0, 0, 0}};
  s21_floor(v_1, &result);
  ck_assert_float_eq(result.bits[0], 25);
  ck_assert_float_eq(result.bits[1], 0);
  ck_assert_float_eq(result.bits[2], 0);
  ck_assert_float_eq(result.bits[3], 0);
}
END_TEST

START_TEST(test_s21_round_1) {
  s21_decimal v_1 = {{5, 0, 1, 0}};
  // put_scale(&v_1, 2);
  s21_decimal result = {{0, 0, 0, 0}};
  s21_round(v_1, &result);
  ck_assert_float_eq(result.bits[0], 5);
  ck_assert_float_eq(result.bits[1], 0);
  ck_assert_float_eq(result.bits[2], 1);
  ck_assert_float_eq(result.bits[3], 0);
}
END_TEST

START_TEST(test_s21_round_2) {
  s21_decimal v_1 = {{155, 1, 1, 0}};
  s21_decimal result = {{0, 0, 0, 0}};
  s21_round(v_1, &result);
  ck_assert_float_eq(result.bits[0], 155);
  ck_assert_float_eq(result.bits[1], 1);
  ck_assert_float_eq(result.bits[2], 1);
  ck_assert_float_eq(result.bits[3], 0);
}
END_TEST

START_TEST(test_s21_round_3) {
  s21_decimal v_1 = {{155, 1, 1, 2147483648}};
  s21_decimal result = {{0, 0, 0, 0}};
  s21_round(v_1, &result);
  ck_assert_float_eq(result.bits[0], 155);
  ck_assert_float_eq(result.bits[1], 1);
  ck_assert_float_eq(result.bits[2], 1);
  ck_assert_float_eq(result.bits[3], 2147483648);
}
END_TEST

START_TEST(test_s21_round_4) {
  s21_decimal v_1 = {{0, 1, 0, 0}};
  s21_decimal result = {{0, 0, 0, 0}};
  s21_round(v_1, &result);
  ck_assert_float_eq(result.bits[0], 0);
  ck_assert_float_eq(result.bits[1], 1);
  ck_assert_float_eq(result.bits[2], 0);
  ck_assert_float_eq(result.bits[3], 0);
}
END_TEST

START_TEST(test_s21_round_5) {
  s21_decimal v_1 = {{2555, 0, 0, 0}};
  put_scale(&v_1, 2);
  s21_decimal result = {{0, 0, 0, 0}};
  s21_round(v_1, &result);
  ck_assert_float_eq(result.bits[0], 26);
  ck_assert_float_eq(result.bits[1], 0);
  ck_assert_float_eq(result.bits[2], 0);
  ck_assert_float_eq(result.bits[3], 0);
}
END_TEST

START_TEST(test_s21_negate_1) {
  s21_decimal v_1 = {{155, 1, 1, 0}};
  s21_decimal result = {{0, 0, 0, 0}};
  s21_negate(v_1, &result);
  ck_assert_float_eq(result.bits[0], 155);
  ck_assert_float_eq(result.bits[1], 1);
  ck_assert_float_eq(result.bits[2], 1);
  ck_assert_float_eq(result.bits[3], 2147483648);
}
END_TEST

START_TEST(test_s21_negate_2) {
  s21_decimal v_1 = {{155, 1, 1, 2147483648}};
  s21_decimal result = {{0, 0, 0, 0}};
  s21_negate(v_1, &result);
  ck_assert_float_eq(result.bits[0], 155);
  ck_assert_float_eq(result.bits[1], 1);
  ck_assert_float_eq(result.bits[2], 1);
  ck_assert_float_eq(result.bits[3], 0);
}
END_TEST

START_TEST(test_s21_truncate_1) {
  s21_decimal v_1 = {{673988, 0, 0, 262144}};
  s21_decimal result = {{0, 0, 0, 0}};
  s21_truncate(v_1, &result);
  ck_assert_float_eq(result.bits[0], 67);
  ck_assert_float_eq(result.bits[1], 0);
  ck_assert_float_eq(result.bits[2], 0);
  ck_assert_float_eq(result.bits[3], 0);
}
END_TEST

START_TEST(test_s21_truncate_2) {
  s21_decimal v_1 = {{0, 0, 0, 0}};
  s21_decimal result = {{0, 0, 0, 0}};
  s21_from_int_to_decimal(-2744406, &v_1);
  s21_truncate(v_1, &result);
  ck_assert_float_eq(result.bits[0], 2744406);
  ck_assert_float_eq(result.bits[1], 0);
  ck_assert_float_eq(result.bits[2], 0);
  ck_assert_float_eq(result.bits[3], 2147483648);
}
END_TEST

// static s21_decimal num1[] = {
//     {{0x0000000A, 0x00000000, 0x00000000, 0x00000000}},  // 0 10
//     {{0x0000000A, 0x00000000, 0x00000000, 0x00000000}},  // 1 10
//     {{0x000000B6, 0x00000000, 0x00000000, 0x00000000}},  // 2 182
//     {{0x0001F0F1, 0x00000000, 0x00000000, 0x00000000}},  // 3 127217
//     {{0x000000D4, 0x00000000, 0x00000000, 0x80000000}},  // 4 -212
//     {{0x014CF9BF, 0x00000000, 0x00000000, 0x80020000}},  // 5 -218218.87
//     {{0x00000000, 0x00000000, 0x00000000, 0x00000000}},  // 6 0
//     {{0x0001DC88, 0x00000000, 0x00000000, 0x00020000}},  // 7 1219.92
//     {{0x001D537F, 0x00000000, 0x00000000, 0x80020000}},  // 8 -19219.19
//     {{0x7D17C946, 0x00000BA8, 0x00000000, 0x00040000}},  // 9 1281828112.2118
//     {{0x7D17C946, 0x00000BA8, 0x00000000, 0x00040000}},  // 10
//     1281828112.2118
//     {{0x00000369, 0x00000000, 0x00000000, 0x00000000}},  // 11 873
//     {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF,
//       0x00000000}},  // 12 79228162514264337593543950335
//     {{0x0001DD09, 0x00000000, 0x00000000,
//       0x00110000}},  // 13 0.00000000000122121
//     {{0x00140263, 0x00000000, 0x00000000,
//       0x00120000}},  // 14 0.000000000001311331
//     {{0x0098967F, 0x00000000, 0x00000000, 0x00070000}},  // 15 0.9999999
//     {{0x0098967F, 0x00000000, 0x00000000, 0x00070000}},  // 16 0.9999999
//     {{0x0098967F, 0x00000000, 0x00000000, 0x80070000}},  // 17 -0.9999999
//     {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF,
//       0x80000000}},  // 18 -79228162514264337593543950335
//     {{0x00000065, 0x00000000, 0x00000000, 0x00020000}},  // 19 1.01
//     {{0x4B743118, 0xC29C4065, 0xF1343498,
//       0x00190000}},  // 20 7464.8999890549484848686575896
//     {{0xE17A7F9D, 0x0DAED47B, 0x00000000,
//       0x000C0000}},  // 21 985958.996969684893
//     {{0x9925D7EE, 0x8A987A9C, 0x00000000,
//       0x000B0000}},  // 22 99868669.86696955886
//     {{0x000186A0, 0x00000000, 0x00000000, 0x00030000}},  // 23 100.000
//     {{0x007FEBFE, 0x00000000, 0x00000000, 0x00020000}},  // 24 83834.86
//     {{0x15C0748C, 0x00000000, 0x00000000, 0x00000000}},  // 25 364934284
//     {{0x15C0748C, 0x00000000, 0x00000000, 0x80000000}},  // 26 -364934284
// };

// static s21_decimal num2[] = {
//     {{0x00000005, 0x00000000, 0x00000000, 0x00000000}},  // 0 5
//     {{0x00004E2A, 0x00000000, 0x00000000, 0x00000000}},  // 1 20010
//     {{0x00000065, 0x00000000, 0x00000000, 0x00000000}},  // 2 101
//     {{0x04FDBA54, 0x00000000, 0x00000000, 0x00000000}},  // 3 83737172
//     {{0x00000011, 0x00000000, 0x00000000, 0x80000000}},  // 4 -17
//     {{0x9336DD9D, 0x00000032, 0x00000000, 0x80020000}},  // 5 -2172182112.29
//     {{0x0000000A, 0x00000000, 0x00000000, 0x00000000}},  // 6 10
//     {{0x0116F341, 0x00000000, 0x00000000, 0x80030000}},  // 7 -18281.281
//     {{0x00007208, 0x00000000, 0x00000000, 0x00000000}},  // 8 29192
//     {{0xCED1C28B, 0x00000032, 0x00000000, 0x00030000}},  // 9 218218218.123
//     {{0x7EE8E7D9, 0x00000000, 0x00000000, 0x00050000}},  // 10 21291.92921
//     {{0x000D9987, 0x00000000, 0x00000000, 0x00000000}},  // 11 891271
//     {{0x00001DE5, 0x00000000, 0x00000000, 0x00010000}},  // 12 765.3
//     {{0x000E1209, 0x00000000, 0x00000000,
//       0x001B0000}},  // 13 0.000000000000000000000922121
//     {{0xEFB25CB0, 0x00000008, 0x00000000, 0x00060000}},  // 14 38381.182128
//     {{0x00000001, 0x00000000, 0x00000000, 0x00000000}},  // 15 1
//     {{0x3B9AC60D, 0x00000000, 0x00000000, 0x80090000}},  // 16 -0.999998989
//     {{0xD4B49FE1, 0x000000E8, 0x00000000, 0x000C0000}},  // 17 1.000001019873
//     {{0x00000019, 0x00000000, 0x00000000, 0x00010000}},  // 18 2.5
//     {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF,
//       0x80000000}},  // 19 -79228162514264337593543950335
//     {{0x036EACCF, 0x00000000, 0x00000000, 0x00030000}},  // 20 57584.847
//     {{0x00004706, 0x00000000, 0x00000000, 0x00030000}},  // 21 18.182
//     {{0xA4E4CE45, 0x5D99269E, 0x00000043,
//       0x00040000}},  // 22 124267631731831713.3381
//     {{0x00000005, 0x00000000, 0x00000000, 0x00000000}},  // 23 5
//     {{0x00000002, 0x00000000, 0x00000000, 0x00000000}},  // 24 2
//     {{0x0000D8B6, 0x00000000, 0x00000000, 0x00000000}},  // 25 55478
//     {{0x000019B2, 0x00000000, 0x00000000, 0x80000000}},  // 26 -6578
// };

// static s21_decimal result[] = {
//     {{0x00000002, 0x00000000, 0x00000000, 0x00000000}},  // 0: 2
//     {{0x9BD58676, 0x15E87A6F, 0x00042243,
//       0x001C0000}},  // 1: 0.0004997501249375312343828086
//     {{0x286562DA, 0x460095F9, 0x05D29026,
//       0x001B0000}},  // 2: 1.801980198019801980198019802
//     {{0x32BBC141, 0x8D8AFA58, 0x000C911E,
//       0x001C0000}},  // 3: 0.0015192416576953422788149569
//     {{0x89696969, 0xD80A02F7, 0x284B6DC6,
//       0x001B0000}},  // 4: 12.470588235294117647058823529
//     {{0xADCFD4F0, 0xD696F916, 0x0000D4BB,
//       0x001C0000}},  // 5: 0.0001004606698330394895308016
//     {{0x00000000, 0x00000000, 0x00000000, 0x00000000}},  // 6: 0
//     {{0x9C29AC03, 0x8B157841, 0x0227FB71,
//       0x801C0000}},  // 7: -0.0667305535098990054362164227
//     {{0xEF1E9F89, 0xA0889681, 0x1545EC8B,
//       0x801C0000}},  // 8: -0.6583718141956700465881063305
//     {{0xD2206F19, 0x481D7320, 0xBDCD2196,
//       0x001C0000}},  // 9: 5.8740655259557198854380089113
//     {{0xF563AF1E, 0x924473AA, 0xC2865EA6,
//       0x00180000}},  // 10: 60202.534940317885830506196766
//     {{0x39A7B007, 0x0C3825D8, 0x00081A2C,
//       0x001C0000}},  // 11: 0.0009795000622706225154863111
//     {{0x1AA07F61, 0xB8149B14, 0x2173706D,
//       0x00020000}},  // 12: 103525627223656523707753757.13
//     {{0x74CC4BF6, 0x387BB251, 0x2ACAC209,
//       0x00130000}},  // 13: 1324348973.7247064105469889526
//     {{0x8C840219, 0x0000004F, 0x00000000,
//       0x001C0000}},  // 14: 0.0000000000000000341659877913
//     {{0x0098967F, 0x00000000, 0x00000000, 0x00070000}},  // 15: 0.9999999
//     {{0x1AF606CC, 0x18EB582D, 0x204FD04C,
//       0x801C0000}},  // 16: -1.0000009110009210219311531724
//     {{0xF97B0D96, 0x28B45460, 0x204FCBFF,
//       0x801C0000}},  // 17: -0.9999988801281421270713044374
//     {{0x66666666, 0x66666666, 0x66666666,
//       0x80000000}},  // 18: -31691265005705735037417580134
//     {{0x00000000, 0x00000000, 0x00000000, 0x80000000}},  // 19: 0
//     {{0x97AB5CFD, 0x3AF46695, 0x04304CAF,
//       0x001C0000}},  // 20: 0.1296330610907926608690765053
//     {{0xA658CE14, 0x3D31233A, 0xAF37B0CD,
//       0x00180000}},  // 21: 54227.202561307056044439555604
//     {{0x1A33E97E, 0x6F87AA74, 0x00000000,
//       0x001C0000}},  // 22: 0.0000000008036579475698477438
//     {{0x00004E20, 0x00000000, 0x00000000, 0x00030000}},  // 23: 20.000
//     {{0x003FF5FF, 0x00000000, 0x00000000, 0x00020000}},  // 24: 41917.43
//     {{0x000019B2, 0x00000000, 0x00000000, 0x00000000}},  // 25: 6578
//     {{0x0000D8B6, 0x00000000, 0x00000000, 0x00000000}},  // 26: 55478
// };

// static s21_decimal err_num1[] = {
//     {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF,
//       0x00000000}},  // 0 79228162514264337593543950335
//     {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF,
//       0x00000000}},  // 1 79228162514264337593543950335
//     {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF,
//       0x80000000}},  // 2 -79228162514264337593543950335
//     {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF,
//       0x80000000}},  // 3 -79228162514264337593543950335
//     {{0x204479BE, 0x0000006F, 0x00000000, 0x00040000}},  // 4 47728272.8382
//     {{0xFA01F028, 0x00000001, 0x00000000, 0x80020000}},  // 5 -84893983.12
//     {{0x00000000, 0x00000000, 0x00000000, 0x00040000}},  // 6 0.0000
// };

// static s21_decimal err_num2[] = {
//     {{0x00000312, 0x00000000, 0x00000000, 0x00090000}},  // 0 0.000000786
//     {{0x00000002, 0x00000000, 0x00000000, 0x80020000}},  // 1 -0.02
//     {{0x000026A1, 0x00000000, 0x00000000, 0x00060000}},  // 2 0.009889
//     {{0x000002FD, 0x00000000, 0x00000000, 0x80050000}},  // 3 -0.00765
//     {{0x00000000, 0x00000000, 0x00000000, 0x00000000}},  // 4 0
//     {{0x00000000, 0x00000000, 0x00000000, 0x80080000}},  // 5 0.00000000
//     {{0x00000000, 0x00000000, 0x00000000, 0x00000000}},  // 6 0
// };

// static int err_result[] = {
//     1, 2, 2, 1, 3, 3, 3,
// };

// START_TEST(test_div_big) {
//   for (size_t i = 0; i < sizeof(num1) / sizeof(s21_decimal); ++i) {
//     s21_decimal temp;
//     printf("i = %zu\n", i);
//     int ret = s21_div(num1[i], num2[i], &temp);
//     printf("%08u | %08u | %08u | %08u\n", result[i].bits[3],
//     result[i].bits[2],
//              result[i].bits[1], result[i].bits[0]);
//     printf("%08u | %08u | %08u | %08u\n\n", temp.bits[3], temp.bits[2],
//              temp.bits[1], temp.bits[0]);
//     ck_assert_int_eq(temp.bits[0], result[i].bits[0]);
//     ck_assert_int_eq(temp.bits[1], result[i].bits[1]);
//     ck_assert_int_eq(temp.bits[2], result[i].bits[2]);
//     ck_assert_int_eq(temp.bits[3], result[i].bits[3]);
//     ck_assert_int_eq(ret, 0);
//   }
// }
// END_TEST

// START_TEST(error_test) {
//   for (size_t i = 0; i < sizeof(err_num1) / sizeof(s21_decimal); ++i) {
//     s21_decimal temp;
//     int ret = s21_div(err_num1[i], err_num2[i], &temp);
//     if (temp.bits[0] == 0) {
//       temp.bits[0] = 1;
//     }
//     ck_assert_int_eq(ret, err_result[i]);
//   }
// }
// END_TEST

int main(void) {
  Suite *s1 = suite_create("s21_decimal: ");
  TCase *tc1_1 = tcase_create("s21_decimal: ");
  SRunner *sr = srunner_create(s1);
  int nf;
  suite_add_tcase(s1, tc1_1);
  tcase_add_test(tc1_1, test_s21_add_1);
  tcase_add_test(tc1_1, test_s21_add_2);
  tcase_add_test(tc1_1, test_s21_add_3);
  tcase_add_test(tc1_1, test_s21_add_4);
  tcase_add_test(tc1_1, test_s21_add_5);
  tcase_add_test(tc1_1, test_s21_add_6);
  tcase_add_test(tc1_1, test_s21_add_7);
  tcase_add_test(tc1_1, test_s21_add_8);
  tcase_add_test(tc1_1, test_s21_add_8);
  tcase_add_test(tc1_1, test_s21_add_9);
  tcase_add_test(tc1_1, test_s21_add_10);
  tcase_add_test(tc1_1, test_s21_add_11);
  tcase_add_test(tc1_1, test_s21_add_12);
  tcase_add_test(tc1_1, test_s21_add_13);
  tcase_add_test(tc1_1, test_s21_add_14);
  tcase_add_test(tc1_1, test_s21_add_15);
  tcase_add_test(tc1_1, test_s21_add_16);
  tcase_add_test(tc1_1, test_s21_add_17);
  tcase_add_test(tc1_1, test_s21_add_18);
  tcase_add_test(tc1_1, test_s21_add_19);
  tcase_add_test(tc1_1, test_s21_add_20);
  tcase_add_test(tc1_1, test_s21_add_21);
  tcase_add_test(tc1_1, test_s21_add_22);
  tcase_add_test(tc1_1, test_s21_add_23);
  tcase_add_test(tc1_1, test_s21_add_24);
  tcase_add_test(tc1_1, test_s21_add_25);

  // tests_sub
  tcase_add_test(tc1_1, test_s21_sub_1);
  tcase_add_test(tc1_1, test_s21_sub_2);
  tcase_add_test(tc1_1, test_s21_sub_3);
  tcase_add_test(tc1_1, test_s21_sub_4);
  tcase_add_test(tc1_1, test_s21_sub_5);
  tcase_add_test(tc1_1, test_s21_sub_6);
  tcase_add_test(tc1_1, test_s21_sub_7);
  tcase_add_test(tc1_1, test_s21_sub_8);
  tcase_add_test(tc1_1, test_s21_sub_9);
  tcase_add_test(tc1_1, test_s21_sub_10);
  tcase_add_test(tc1_1, test_s21_sub_11);

  // tests_mul
  tcase_add_test(tc1_1, test_s21_mul_1);
  tcase_add_test(tc1_1, test_s21_mul_2);
  tcase_add_test(tc1_1, test_s21_mul_3);
  tcase_add_test(tc1_1, test_s21_mul_4);
  tcase_add_test(tc1_1, test_s21_mul_5);
  tcase_add_test(tc1_1, test_s21_mul_6);
  tcase_add_test(tc1_1, test_s21_mul_7);
  tcase_add_test(tc1_1, test_s21_mul_8);
  // tcase_add_test(tc1_1, test_s21_mul_9); неправильный тест - число умещается
  // в буффер
  tcase_add_test(tc1_1, test_s21_mul_10);
  tcase_add_test(tc1_1, test_s21_mul_11);

  // tests_div
  tcase_add_test(tc1_1, test_s21_div_1);
  tcase_add_test(tc1_1, test_s21_div_2);
  tcase_add_test(tc1_1, test_s21_div_3);
  tcase_add_test(tc1_1, test_s21_div_4);
  tcase_add_test(tc1_1, test_s21_div_5);
  tcase_add_test(tc1_1, test_s21_div_6);
  tcase_add_test(tc1_1, test_s21_div_7);
  tcase_add_test(tc1_1, test_s21_div_8);
  // tcase_add_test(tc1_1, error_test);
  // tcase_add_test(tc1_1, test_div_big);

  // test_mod
  // tcase_add_test(tc1_1, test_s21_mod_1);
  // tcase_add_test(tc1_1, test_s21_mod_2);
  // tcase_add_test(tc1_1, test_s21_mod_3);
  // tcase_add_test(tc1_1, test_s21_mod_4);

  tcase_add_test(tc1_1, test_s21_is_less_1);
  tcase_add_test(tc1_1, test_s21_is_less_2);
  tcase_add_test(tc1_1, test_s21_is_less_3);
  tcase_add_test(tc1_1, test_s21_is_less_4);
  tcase_add_test(tc1_1, test_s21_is_less_5);
  tcase_add_test(tc1_1, test_s21_is_less_6);
  tcase_add_test(tc1_1, test_s21_is_less_7);
  tcase_add_test(tc1_1, test_s21_is_less_8);

  // tests_is_less_or_equal
  tcase_add_test(tc1_1, test_s21_is_less_or_equal_1);
  tcase_add_test(tc1_1, test_s21_is_less_or_equal_2);
  tcase_add_test(tc1_1, test_s21_is_less_or_equal_3);
  tcase_add_test(tc1_1, test_s21_is_less_or_equal_4);
  tcase_add_test(tc1_1, test_s21_is_less_or_equal_5);

  // tests_is_greater
  tcase_add_test(tc1_1, test_s21_is_greater_1);
  tcase_add_test(tc1_1, test_s21_is_greater_2);
  tcase_add_test(tc1_1, test_s21_is_greater_3);
  tcase_add_test(tc1_1, test_s21_is_greater_4);

  // tests_is_greater_or_equal
  tcase_add_test(tc1_1, test_s21_is_greater_or_equal_1);
  tcase_add_test(tc1_1, test_s21_is_greater_or_equal_2);
  tcase_add_test(tc1_1, test_s21_is_greater_or_equal_3);
  tcase_add_test(tc1_1, test_s21_is_greater_or_equal_4);
  tcase_add_test(tc1_1, test_s21_is_greater_or_equal_5);

  // tests_is_equal
  tcase_add_test(tc1_1, test_s21_is_equal_1);
  tcase_add_test(tc1_1, test_s21_is_equal_2);
  tcase_add_test(tc1_1, test_s21_is_equal_3);
  tcase_add_test(tc1_1, test_s21_is_equal_4);
  tcase_add_test(tc1_1, test_s21_is_equal_5);

  // tests_is_not_equal
  tcase_add_test(tc1_1, test_s21_is_not_equal_1);
  tcase_add_test(tc1_1, test_s21_is_not_equal_2);
  tcase_add_test(tc1_1, test_s21_is_not_equal_3);
  tcase_add_test(tc1_1, test_s21_is_not_equal_4);
  tcase_add_test(tc1_1, test_s21_is_not_equal_5);

  // tests_from_int_to_decimal
  tcase_add_test(tc1_1, test_s21_form_int_to_decimal_1);
  tcase_add_test(tc1_1, test_s21_form_int_to_decimal_2);
  tcase_add_test(tc1_1, test_s21_form_int_to_decimal_3);
  tcase_add_test(tc1_1, test_s21_form_int_to_decimal_4);
  tcase_add_test(tc1_1, test_s21_form_int_to_decimal_5);

  // // tests_from_float_to_decimal
  tcase_add_test(tc1_1, test_s21_form_float_to_decimal_1);
  tcase_add_test(tc1_1, test_s21_form_float_to_decimal_2);
  tcase_add_test(tc1_1, test_s21_form_float_to_decimal_3);
  tcase_add_test(tc1_1, test_s21_form_float_to_decimal_4);
  tcase_add_test(tc1_1, test_s21_form_float_to_decimal_5);
  tcase_add_test(tc1_1, test_s21_form_float_to_decimal_6);
  tcase_add_test(tc1_1, test_s21_form_float_to_decimal_7);

  // tests_from_decimal_to_int
  tcase_add_test(tc1_1, test_s21_decimal_to_int_1);
  tcase_add_test(tc1_1, test_s21_decimal_to_int_2);
  tcase_add_test(tc1_1, test_s21_decimal_to_int_3);
  tcase_add_test(tc1_1, test_s21_decimal_to_int_4);

  // tests_from_decimal_to_float
  tcase_add_test(tc1_1, test_s21_decimal_to_float_1);
  tcase_add_test(tc1_1, test_s21_decimal_to_float_2);
  tcase_add_test(tc1_1, test_s21_decimal_to_float_3);

  //  test_floor
  tcase_add_test(tc1_1, test_s21_floor_1);
  tcase_add_test(tc1_1, test_s21_floor_2);
  tcase_add_test(tc1_1, test_s21_floor_3);
  tcase_add_test(tc1_1, test_s21_floor_4);

  // tests_round
  tcase_add_test(tc1_1, test_s21_round_1);
  tcase_add_test(tc1_1, test_s21_round_2);
  tcase_add_test(tc1_1, test_s21_round_3);
  tcase_add_test(tc1_1, test_s21_round_4);
  tcase_add_test(tc1_1, test_s21_round_5);

  // tests_negate
  tcase_add_test(tc1_1, test_s21_negate_1);
  tcase_add_test(tc1_1, test_s21_negate_2);

  // // tests_truncate
  tcase_add_test(tc1_1, test_s21_truncate_1);
  tcase_add_test(tc1_1, test_s21_truncate_2);

  srunner_run_all(sr, CK_ENV);  // CK_ENV
  nf = srunner_ntests_failed(sr);
  srunner_free(sr);

  return nf == 0 ? 0 : 1;
}
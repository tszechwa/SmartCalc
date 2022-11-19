#include <gtest/gtest.h>

#include "Model/smartCalcModel.cpp"

TEST(random_tests, random_test_1) {
  s21::SmartCalcModel test;
  char arr[256] = "(256/32)/4*2+256/(32/4*2)+256/(32/4)*2";
  ASSERT_EQ(test.ErrorParcer(arr, 0), 84);
}

TEST(random_tests, random_test_2) {
  s21::SmartCalcModel test;
  char arr[256] =
      "5*(1.75+0.234)*sin(cos(tan(5%3))*tan(sin(5))+ln(2))*5^2+sin(5)";
  ASSERT_NEAR(test.ErrorParcer(arr, 0), 246.648, 0.0001);
}

TEST(random_tests, random_test_3) {
  s21::SmartCalcModel test;
  char arr[256] =
      "-5*(1.75+0.234)*-sin(cos(tan(5%3))*tan(sin(-5))+ln(2))*5^2+-sin(5)-13";
  ASSERT_NEAR(test.ErrorParcer(arr, 0), -43.745468, 0.0001);
}

TEST(random_tests, random_test_4) {
  s21::SmartCalcModel test;
  char arr[256] = "2^3^4";
  ASSERT_NEAR(test.ErrorParcer(arr, 0), 2.4178516392292583e+24, 0.0001);
}

TEST(random_tests, random_test_5) {
  s21::SmartCalcModel test;
  char arr[256] = "1000%10%12";
  ASSERT_NEAR(test.ErrorParcer(arr, 0), 0, 0.0001);
}

TEST(random_tests, random_test_6) {
  s21::SmartCalcModel test;
  char arr[256] = "435435*10%232^3";
  ASSERT_NEAR(test.ErrorParcer(arr, 0), 4354350, 0.0001);
}

TEST(random_tests, random_test_7) {
  s21::SmartCalcModel test;
  char arr[256] = "+5*(+2.75+2.25)*+12%7/sin(5)*5^2";
  ASSERT_NEAR(test.ErrorParcer(arr, 0), -156.425281, 0.0001);
}

TEST(random_tests, random_test_8) {
  s21::SmartCalcModel test;
  char arr[256] = "sin(cos(-tan(5%3)-100))";
  ASSERT_NEAR(test.ErrorParcer(arr, 0), -0.789992, 0.0001);
}

TEST(sin_tests, sin_test_1) {
  s21::SmartCalcModel test;
  char arr[256] = "sin(sin(sin(sin(435435*10%232^3)+7)*3)+25)";
  ASSERT_NEAR(test.ErrorParcer(arr, 0), 0.009980, 0.0001);
}

TEST(cos_tests, cos_test_1) {
  s21::SmartCalcModel test;
  char arr[256] = "+cos(cos(cos(cos(435435*10%232^3)+7)*3)+25)";
  ASSERT_NEAR(test.ErrorParcer(arr, 0), 0.449615, 0.0001);
}

TEST(tan_tests, tan_test_1) {
  s21::SmartCalcModel test;
  char arr[256] = "-tan(-cos(tan(5^3)))";
  ASSERT_NEAR(test.ErrorParcer(arr, 0), 0.858595, 0.0001);
}

TEST(acos_tests, acos_test_1) {
  s21::SmartCalcModel test;
  char arr[256] = "acos(0.142214)";
  ASSERT_NEAR(test.ErrorParcer(arr, 0), 1.42809854, 0.0001);
}

TEST(asin_tests, asin_test_1) {
  s21::SmartCalcModel test;
  char arr[256] = "asin(-0.3223)";
  ASSERT_NEAR(test.ErrorParcer(arr, 0), -0.328158, 0.0001);
}

TEST(atan_tests, atan_test_1) {
  s21::SmartCalcModel test;
  char arr[256] = "atan(0.99)";
  ASSERT_NEAR(test.ErrorParcer(arr, 0), 0.780373, 0.0001);
}

TEST(sqrt_tests, sqrt_test_1) {
  s21::SmartCalcModel test;
  char arr[256] = "-sqrt(sqrt(34058%234)/sqrt(9))";
  ASSERT_NEAR(test.ErrorParcer(arr, 0), -1.941967, 0.0001);
}

TEST(ln_tests, ln_test_1) {
  s21::SmartCalcModel test;
  char arr[256] = "ln(35/12)%-ln(700)";
  ASSERT_NEAR(test.ErrorParcer(arr, 0), 1.070441, 0.0001);
}

TEST(log_tests, log_test_1) {
  s21::SmartCalcModel test;
  char arr[256] = "log(213+-cos(33)/-sin(62))";
  ASSERT_NEAR(test.ErrorParcer(arr, 0), 2.328416, 0.0001);
}

int main(int argc, char *argv[]) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}

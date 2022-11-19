#ifndef SRC_MODEL_SMARTCALCMODEL_H_
#define SRC_MODEL_SMARTCALCMODEL_H_

#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <iostream>
#include <stack>

namespace s21 {
class SmartCalcModel {
 public:
  SmartCalcModel() {}
  ~SmartCalcModel() {}

  double ErrorParcer(char str[], double x);
  double GraphCalculateStep(double end, double begin);

 private:
  std::stack<double> stack_double_;
  std::stack<char> stack_char_;

  void CalculateExpression();
  int Prior(char a);
  double GetResult(char str[], double x);
  void FunctionExpression(char str[], int &i, char tmpstr[], int &count_numbers,
                          int value);
};
}  // namespace s21

#endif  // SRC_MODEL_SMARTCALCMODEL_H_

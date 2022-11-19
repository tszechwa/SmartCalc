#include "smartCalcModel.h"

namespace s21 {
double s21::SmartCalcModel::GraphCalculateStep(double end, double begin) {
  return fabs(end - begin) / 1000000;
}

void s21::SmartCalcModel::FunctionExpression(char str[], int &i, char tmpstr[],
                                             int &count_numbers, int value) {
  memset(tmpstr, 0, 256);
  int open_bkt = 1;
  int close_bkt = 0;
  for (i += value; open_bkt != close_bkt; i++) {
    if (str[i] == '(') {
      open_bkt++;
    } else if (str[i] == ')') {
      close_bkt++;
    }
    if (open_bkt != close_bkt) {
      strncat(tmpstr, str + i, 1);
    }
  }
  count_numbers++;
  i--;
}

double s21::SmartCalcModel::GetResult(char str[], double x) {
  s21::SmartCalcModel tmp_;
  int count_numbers = 0;
  double result = -1;

  char tmpstr[256] = "\0";

  for (int i = 0; str[i] != '\0'; i++) {
    int unar_minus = 1;

    if (str[i] == '+' &&
        (i == 0 || str[i - 1] == '(' || str[i - 1] == '+' ||
         str[i - 1] == '-' || str[i - 1] == '*' || str[i - 1] == '/' ||
         str[i - 1] == '^' || str[i - 1] == '%')) {
      i++;
    }

    if (str[i] == '-' &&
        (i == 0 || str[i - 1] == '(' || str[i - 1] == '+' ||
         str[i - 1] == '-' || str[i - 1] == '*' || str[i - 1] == '/' ||
         str[i - 1] == '^' || str[i - 1] == '%')) {
      unar_minus = -1;
      i++;
    }
    // sin
    if (str[i] == 's' && str[i + 1] == 'i' && str[i + 2] == 'n' &&
        str[i + 3] == '(') {
      FunctionExpression(str, i, tmpstr, count_numbers, 4);
      stack_double_.push(unar_minus * sin(tmp_.GetResult(tmpstr, x)));
      continue;
    }
    // cos
    if (str[i] == 'c' && str[i + 1] == 'o' && str[i + 2] == 's' &&
        str[i + 3] == '(') {
      FunctionExpression(str, i, tmpstr, count_numbers, 4);
      stack_double_.push(unar_minus * cos(tmp_.GetResult(tmpstr, x)));
      continue;
    }
    // tan
    if (str[i] == 't' && str[i + 1] == 'a' && str[i + 2] == 'n' &&
        str[i + 3] == '(') {
      FunctionExpression(str, i, tmpstr, count_numbers, 4);
      stack_double_.push(unar_minus * tan(tmp_.GetResult(tmpstr, x)));
      continue;
    }
    // acos
    if (str[i] == 'a' && str[i + 1] == 'c' && str[i + 2] == 'o' &&
        str[i + 3] == 's' && str[i + 4] == '(') {
      FunctionExpression(str, i, tmpstr, count_numbers, 5);
      stack_double_.push(unar_minus * acos(tmp_.GetResult(tmpstr, x)));
      continue;
    }
    // asin
    if (str[i] == 'a' && str[i + 1] == 's' && str[i + 2] == 'i' &&
        str[i + 3] == 'n' && str[i + 4] == '(') {
      FunctionExpression(str, i, tmpstr, count_numbers, 5);
      stack_double_.push(unar_minus * asin(tmp_.GetResult(tmpstr, x)));
      continue;
    }
    // atan
    if (str[i] == 'a' && str[i + 1] == 't' && str[i + 2] == 'a' &&
        str[i + 3] == 'n' && str[i + 4] == '(') {
      FunctionExpression(str, i, tmpstr, count_numbers, 5);
      stack_double_.push(unar_minus * atan(tmp_.GetResult(tmpstr, x)));
      continue;
    }
    // sqrt
    if (str[i] == 's' && str[i + 1] == 'q' && str[i + 2] == 'r' &&
        str[i + 3] == 't' && str[i + 4] == '(') {
      FunctionExpression(str, i, tmpstr, count_numbers, 5);
      stack_double_.push(unar_minus * sqrt(tmp_.GetResult(tmpstr, x)));
      continue;
    }
    // ln
    if (str[i] == 'l' && str[i + 1] == 'n' && str[i + 2] == '(') {
      FunctionExpression(str, i, tmpstr, count_numbers, 3);
      stack_double_.push(unar_minus * log(tmp_.GetResult(tmpstr, x)));
      continue;
    }
    // log
    if (str[i] == 'l' && str[i + 1] == 'o' && str[i + 2] == 'g' &&
        str[i + 3] == '(') {
      FunctionExpression(str, i, tmpstr, count_numbers, 4);
      stack_double_.push(unar_minus * log10(tmp_.GetResult(tmpstr, x)));
      continue;
    }
    ///////
    if (str[i] == ')' && !stack_char_.empty()) {
      while (stack_char_.top() != '(') {
        CalculateExpression();
        count_numbers--;
      }
      stack_char_.pop();
    }

    if (str[i] == 'x') {
      stack_double_.push(unar_minus * x);
      count_numbers++;
    }

    if ((str[i] >= '0' && str[i] <= '9')) {
      size_t count = 0;
      double num = std::stod(str + i, &count);
      stack_double_.push(unar_minus * num);
      count_numbers++;
      i += count - 1;
    }

    if (str[i] == '(') stack_char_.push(str[i]);

    if (str[i] == '+' || str[i] == '-' || str[i] == '*' || str[i] == '/' ||
        str[i] == '^' || str[i] == '%') {
      int sym_prioruty = Prior(str[i]);
      while (!(stack_char_.empty()) &&
             Prior(stack_char_.top()) >= sym_prioruty && sym_prioruty != 4) {
        CalculateExpression();
        count_numbers--;
      }
      stack_char_.push(str[i]);
    }
  }

  while (!stack_char_.empty()) {
    CalculateExpression();
    count_numbers--;
  }

  if (count_numbers == 0 || count_numbers > 1) {
    result = NAN;
  } else {
    result = stack_double_.top();
    stack_double_.pop();
  }
  return result;
}

void s21::SmartCalcModel::CalculateExpression() {
  char operation = '\0';
  double num1 = 0, num2 = 0, result = 0;
  if (!stack_char_.empty()) {
    operation = stack_char_.top();
    stack_char_.pop();
  }
  if (!stack_double_.empty()) {
    num1 = stack_double_.top();
    stack_double_.pop();
  }
  if (!stack_double_.empty()) {
    num2 = stack_double_.top();
    stack_double_.pop();
  }

  switch (operation) {
    case '+':
      result = num2 + num1;
      break;
    case '-':
      result = num2 - num1;
      break;
    case '*':
      result = num2 * num1;
      break;
    case '/':
      result = num2 / num1;
      break;
    case '^':
      result = pow(num2, num1);
      break;
    case '%':
      result = fmod(num2, num1);
      break;
  }
  stack_double_.push(result);
}

int s21::SmartCalcModel::Prior(char a) {
  int priority = 0;
  switch (a) {
    case '^':
      priority = 4;
      break;
    case '*':
    case '/':
    case '%':
      priority = 3;
      break;
    case '-':
    case '+':
      priority = 2;
      break;
    case '(':
      priority = 1;
      break;
  }
  return priority;
}

double s21::SmartCalcModel::ErrorParcer(char str[], double x) {
  s21::SmartCalcModel tmp_;
  int close_bracket = 0, open_bracket = 0, errorflag = 0;
  double result;
  int end_string = strlen(str) - 1;

  for (int i = 0; str[i] != '\0'; i++) {
    if (str[i] == 'E') {
      errorflag = 1;
    }

    if ((str[i] == '.') && (str[i + 1] == '.')) {
      errorflag = 1;
    }

    if ((str[i] == '*' || str[i] == '/' || str[i] == '^' || str[i] == '%' ||
         str[i] == '+' || str[i] == '-' || str[i] == '.' || str[i] == '(') &&
        (str[i + 1] == '*' || str[i + 1] == '/' || str[i + 1] == '^' ||
         str[i + 1] == '%' || str[i + 1] == '.')) {
      errorflag = 1;
    }

    if ((str[i] == '+' || str[i] == '-') &&
        (str[i + 1] == '+' || str[i + 1] == '-') &&
        (str[i + 2] == '+' || str[i + 2] == '-')) {
      errorflag = 1;
    }

    if ((str[i] == '(' && str[i + 1] == ')') ||
        (str[i] == ')' && str[i + 1] == '(')) {
      errorflag = 1;
    }

    if (str[i] == '(') {
      open_bracket++;
    }
    if (str[i] == ')') {
      close_bracket++;
    }
  }

  if (str[0] == '*' || str[0] == '/' || str[0] == '^' || str[0] == '%' ||
      str[0] == ')' || str[0] == '.') {
    errorflag = 1;
  }

  if (str[end_string] == '*' || str[end_string] == '/' ||
      str[end_string] == '^' || str[end_string] == '%' ||
      str[end_string] == '(' || str[end_string] == '+' ||
      str[end_string] == '-' || str[end_string] == '.') {
    errorflag = 1;
  }

  if (open_bracket != close_bracket) {
    errorflag = 1;
  }

  if (errorflag) {
    result = NAN;
  } else {
    result = tmp_.GetResult(str, x);
  }

  return result;
}
}  // namespace s21

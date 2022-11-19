#include "creditCalculatorModel.h"

namespace s21 {
double CreditCalculatorModel::CreditCalculatorTotalPayment(
    double monthly_payment, double count_mounth) {
  return monthly_payment * count_mounth;
}

double CreditCalculatorModel::MonthlyPayment(double sum_credit,
                                             double procent_rate_mouth,
                                             double count_mounth) {
  return sum_credit * (procent_rate_mouth /
                       (1 - pow((1 + procent_rate_mouth), -count_mounth)));
}

double CreditCalculatorModel::ProcentRatePerMounth(double procent_rate) {
  return (procent_rate / (100 * 12));
}

double CreditCalculatorModel::Overpayment(double total_payment,
                                          double sum_credit) {
  return total_payment - sum_credit;
}

double CreditCalculatorModel::TotalPayment(double monthly_payment,
                                           double count_mounth) {
  return monthly_payment * count_mounth;
}

void CreditCalculatorModel::CreditCalculatorDifferentiatedCalculate(
    double sum_credit, double count_mounth, double procent_rate_mouth,
    double *total_payment, double *array) {
  double sum_credit_differentiated = sum_credit / count_mounth;
  int size = count_mounth;
  for (int i = 0; i < size; i++) {
    double monthly_payment_differentiated;
    monthly_payment_differentiated =
        sum_credit / count_mounth + sum_credit * procent_rate_mouth;
    *total_payment += monthly_payment_differentiated;
    count_mounth--;
    sum_credit -= sum_credit_differentiated;
    array[i] = monthly_payment_differentiated;
  }
}
}  // namespace s21

#ifndef SRC_CONTROL_SMARTCALCCONTROLLER_H
#define SRC_CONTROL_SMARTCALCCONTROLLER_H

#include <QMainWindow>
#include <QVector>
#include <QWidget>
#include <cmath>
#include <cstring>
#include <iostream>

#include "Model/creditCalculatorModel.h"
#include "Model/smartCalcModel.h"

namespace s21 {
class SmartCalcController {
 public:
  SmartCalcController(s21::SmartCalcModel *model,
                      CreditCalculatorModel *credit_model)
      : smart_calc_model_(model), credit_calculator_model_(credit_model) {}
  ~SmartCalcController() {}

  double CalculatorMainFunction(char str[], double x);

  double GraphStepCalculate(double end, double begin);

  double CreditCalculatorMounthlyPayment(double sum_credit,
                                         double procent_rate_mouth,
                                         double count_mounth);
  double CreditCalculatorProcentRatePerMounth(double procent_rate);
  double CreditCalculatorOverpayment(double total_payment, double sum_credit);
  double CreditCalculatorTotalPayment(double monthly_payment,
                                      double count_mounth);
  void CreditCalculatorDifferentiatedCalculate(double sum_credit,
                                               double count_mounth,
                                               double procent_rate_mouth,
                                               double *total_payment,
                                               double *array);

 private:
  s21::SmartCalcModel *smart_calc_model_;
  CreditCalculatorModel *credit_calculator_model_;
};
}  // namespace s21

#endif  // SRC_CONTROL_SMARTCALCCONTROLLER_H

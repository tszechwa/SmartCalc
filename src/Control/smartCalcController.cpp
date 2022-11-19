#include "smartCalcController.h"

namespace s21 {
double SmartCalcController::GraphStepCalculate(double end, double begin) {
  return smart_calc_model_->GraphCalculateStep(end, begin);
}

double SmartCalcController::CreditCalculatorMounthlyPayment(
    double sum_credit, double procent_rate_mouth, double count_mounth) {
  return credit_calculator_model_->MonthlyPayment(
      sum_credit, procent_rate_mouth, count_mounth);
}

double SmartCalcController::CreditCalculatorProcentRatePerMounth(
    double procent_rate) {
  return credit_calculator_model_->ProcentRatePerMounth(procent_rate);
}

double SmartCalcController::CreditCalculatorOverpayment(double total_payment,
                                                        double sum_credit) {
  return credit_calculator_model_->Overpayment(total_payment, sum_credit);
}

void SmartCalcController::CreditCalculatorDifferentiatedCalculate(
    double sum_credit, double count_mounth, double procent_rate_mouth,
    double *total_payment, double *array) {
  credit_calculator_model_->CreditCalculatorDifferentiatedCalculate(
      sum_credit, count_mounth, procent_rate_mouth, total_payment, array);
}

double SmartCalcController::CreditCalculatorTotalPayment(double monthly_payment,
                                                         double count_mounth) {
  return credit_calculator_model_->CreditCalculatorTotalPayment(monthly_payment,
                                                                count_mounth);
}

double SmartCalcController::CalculatorMainFunction(char str[], double x) {
  return smart_calc_model_->ErrorParcer(str, x);
}
}  // namespace s21

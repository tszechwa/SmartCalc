#ifndef SRC_MODEL_CREDITCALCULATORMODEL_H_
#define SRC_MODEL_CREDITCALCULATORMODEL_H_

#include <cmath>

namespace s21 {
class CreditCalculatorModel {
 public:
  CreditCalculatorModel() {}
  ~CreditCalculatorModel() {}
  double CreditCalculatorTotalPayment(double monthly_payment,
                                      double count_mounth);
  double MonthlyPayment(double sum_credit, double procent_rate_mouth,
                        double count_mounth);
  double ProcentRatePerMounth(double procent_rate);
  double Overpayment(double total_payment, double sum_credit);
  double TotalPayment(double monthly_payment, double count_mounth);
  void CreditCalculatorDifferentiatedCalculate(double sum_credit,
                                               double count_mounth,
                                               double procent_rate_mouth,
                                               double *total_payment,
                                               double *array);
};
}  // namespace s21

#endif  // SRC_MODEL_CREDITCALCULATORMODEL_H_

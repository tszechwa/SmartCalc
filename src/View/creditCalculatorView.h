#ifndef SRC_VIEW_CREDITCALCULATORVIEW_H_
#define SRC_VIEW_CREDITCALCULATORVIEW_H_

#include "Control/smartCalcController.h"

namespace Ui {
class CreditCalculator;
}

namespace s21 {
class CreditCalculatorView : public QWidget {
  Q_OBJECT

 public:
  explicit CreditCalculatorView(SmartCalcController *cont,
                                QWidget *parent = nullptr);
  ~CreditCalculatorView();

 private slots:
  void on_pushButton_clicked();

 private:
  Ui::CreditCalculator *ui_;
  SmartCalcController *credit_calculator_controller_;

  void ErrorAlert();
  void FillTable(double count_mounth, double *array);
};
}  // namespace s21

#endif  // SRC_VIEW_CREDITCALCULATORVIEW_H_

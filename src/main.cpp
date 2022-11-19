#include <QApplication>
#include <QLabel>

#include "View/smartCalcView.h"

int main(int argc, char *argv[]) {
  QApplication a(argc, argv);
  s21::SmartCalcModel model;
  s21::CreditCalculatorModel model_credit;
  s21::SmartCalcController controller(&model, &model_credit);
  s21::SmartCalcView view(&controller);
  view.show();
  return a.exec();
}

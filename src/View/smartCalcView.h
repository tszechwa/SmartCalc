#ifndef SRC_VIEW_SMARTCALCVIEW_H_
#define SRC_VIEW_SMARTCALCVIEW_H_

#include "creditCalculatorView.h"
#include "graphView.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class SmartCalc;
}
QT_END_NAMESPACE

namespace s21 {
class SmartCalcView : public QMainWindow {
  Q_OBJECT

 public:
  explicit SmartCalcView(SmartCalcController *cont, QWidget *parent = nullptr);
  ~SmartCalcView();

 private slots:
  void digit_value();
  void on_pushButton_backspace_clicked();
  void on_pushButton_AC_clicked();
  void on_pushButton_result_clicked();
  void on_pushButton_backspacex_clicked();
  void on_pushButton_creditcalculator_clicked();
  void on_radioButton_x_clicked();
  void on_radioButton_string_clicked();
  void on_pushButton_graph_clicked();

 private:
  Ui::SmartCalc *ui_;
  SmartCalcController *controller_;
  CreditCalculatorView *credit_;
  GraphView *graph_menu_;

 signals:
  void signal(QString);
};
}  // namespace s21

#endif  // SRC_VIEW_SMARTCALCVIEW_H_

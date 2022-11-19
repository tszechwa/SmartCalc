#include "creditCalculatorView.h"

#include <QMessageBox>

#include "ui_creditCalculatorView.h"

namespace s21 {
CreditCalculatorView::~CreditCalculatorView() { delete ui_; }

CreditCalculatorView::CreditCalculatorView(SmartCalcController *cont,
                                           QWidget *parent)
    : QWidget(parent),
      ui_(new Ui::CreditCalculator),
      credit_calculator_controller_(cont) {
  ui_->setupUi(this);
  ui_->radioButton_a->setChecked(true);
  ui_->lineEdit_pereplata->setEnabled(false);
  ui_->lineEdit_finallypay->setEnabled(false);
  ui_->tableWidget->setColumnCount(1);
  ui_->tableWidget->setHorizontalHeaderLabels(QStringList()
                                              << "Ежемесячный платеж");
}

void CreditCalculatorView::on_pushButton_clicked() {
  bool check, check2, check3;
  double sum_credit = ui_->lineEdit_sumcredit->text().toDouble(&check);
  double procent_rate = ui_->lineEdit_procent->text().toDouble(&check2);
  double count_mounth = ui_->lineEdit_srok->text().toDouble(&check3);
  double *array = new double[count_mounth];
  double procent_rate_mouth =
      credit_calculator_controller_->CreditCalculatorProcentRatePerMounth(
          procent_rate);
  double monthly_payment =
      credit_calculator_controller_->CreditCalculatorMounthlyPayment(
          sum_credit, procent_rate_mouth, count_mounth);
  ui_->tableWidget->setRowCount(count_mounth);

  if (check && check2 && check3 && sum_credit > 0 && procent_rate > 0 &&
      count_mounth > 0 && count_mounth < 501) {
    double total_payment = 0;
    if (ui_->radioButton_a->isChecked()) {
      total_payment =
          credit_calculator_controller_->CreditCalculatorTotalPayment(
              monthly_payment, count_mounth);
      for (int i = 0; i < count_mounth; i++) array[i] = monthly_payment;
    } else {
      credit_calculator_controller_->CreditCalculatorDifferentiatedCalculate(
          sum_credit, count_mounth, procent_rate_mouth, &total_payment, array);
    }
    FillTable(count_mounth, array);
    double overpayment =
        credit_calculator_controller_->CreditCalculatorOverpayment(
            total_payment, sum_credit);
    ui_->lineEdit_pereplata->setText(QString::number(overpayment, 'f', 7));
    ui_->lineEdit_finallypay->setText(QString::number(total_payment, 'f', 7));
  } else {
    ErrorAlert();
  }
  delete[] array;
}

void CreditCalculatorView::FillTable(double count_mounth, double *array) {
  for (int i = 0; i < count_mounth; i++) {
    QTableWidgetItem *item = new QTableWidgetItem(tr("%1").arg(array[i]));
    ui_->tableWidget->setItem(i, 0, item);
  }
}

void CreditCalculatorView::ErrorAlert() {
  QMessageBox message_box;
  ui_->lineEdit_finallypay->clear();
  ui_->lineEdit_pereplata->clear();
  ui_->tableWidget->setRowCount(0);
  message_box.critical(0, "Error", "An error has occured !");
  message_box.setFixedSize(500, 200);
}
}  // namespace s21

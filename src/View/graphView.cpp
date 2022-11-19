#include "graphView.h"

#include "ui_graphView.h"

namespace s21 {
GraphView::~GraphView() { delete ui_; }

GraphView::GraphView(SmartCalcController *cont, QWidget *parent)
    : QWidget(parent), ui_(new Ui::Graph), graph_controller_(cont) {
  ui_->setupUi(this);
  ui_->widget->xAxis->setRange(-5, 5);
  ui_->widget->yAxis->setRange(-5, 5);
}

void GraphView::on_pushButton_postroit_clicked() {
  x_vector_.clear();
  y_vector_.clear();
  ui_->widget->clearGraphs();
  bool check, check2;
  double number;
  char utf_8_arr_char[255] = "\0";
  QString string_formula = ui_->label_formula->text();
  std::string utf_8_string = string_formula.toUtf8().constData();
  std::strcpy(utf_8_arr_char, utf_8_string.c_str());
  x_begin_ = ui_->lineEdit_min->text().toDouble(&check);
  x_end_ = ui_->lineEdit_max->text().toDouble(&check2);
  h_ = graph_controller_->GraphStepCalculate(x_end_, x_begin_);

  if (check && check2 && x_end_ >= -1000000 && x_end_ <= 1000000 &&
      x_begin_ >= -1000000 && x_begin_ <= 1000000 && x_begin_ != x_end_) {
    ui_->widget->xAxis->setRange(x_begin_, x_end_);
    ui_->widget->yAxis->setRange(x_begin_, x_end_);

    for (x_ = x_begin_; x_ <= x_end_; x_ += h_) {
      x_vector_.push_back(x_);
      number = graph_controller_->CalculatorMainFunction(utf_8_arr_char, x_);
      y_vector_.push_back(number);
    }
    ui_->widget->addGraph();
    ui_->widget->graph(0)->addData(x_vector_, y_vector_);
    ui_->widget->replot();
    ui_->widget->setInteraction(QCP::iRangeZoom, true);
    ui_->widget->setInteraction(QCP::iRangeDrag, true);
  } else {
    ErrorAlert();
  }
}

void GraphView::slot(QString string) { ui_->label_formula->setText(string); }

void GraphView::ErrorAlert() {
  QMessageBox messageBox;
  messageBox.critical(0, "Error", "An error has occured !");
  messageBox.setFixedSize(500, 200);
}
}  // namespace s21

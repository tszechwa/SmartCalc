#include "smartCalcView.h"

#include "ui_smartCalcView.h"

namespace s21 {
SmartCalcView::~SmartCalcView() { delete ui_; }

void SmartCalcView::on_pushButton_AC_clicked() {
  ui_->lineEdit_string->clear();
}

SmartCalcView::SmartCalcView(SmartCalcController *cont, QWidget *parent)
    : QMainWindow(parent), ui_(new Ui::SmartCalc), controller_(cont) {
  ui_->setupUi(this);
  ui_->lineEdit_string->setEnabled(false);
  ui_->lineEdit_x->setEnabled(false);

  ui_->radioButton_string->setChecked(true);
  ui_->pushButton_graph->setDisabled(true);

  credit_ = new CreditCalculatorView(controller_);
  graph_menu_ = new GraphView(controller_);

  connect(ui_->pushButton_0, SIGNAL(clicked()), this, SLOT(digit_value()));
  connect(ui_->pushButton_1, SIGNAL(clicked()), this, SLOT(digit_value()));
  connect(ui_->pushButton_2, SIGNAL(clicked()), this, SLOT(digit_value()));
  connect(ui_->pushButton_3, SIGNAL(clicked()), this, SLOT(digit_value()));
  connect(ui_->pushButton_4, SIGNAL(clicked()), this, SLOT(digit_value()));
  connect(ui_->pushButton_5, SIGNAL(clicked()), this, SLOT(digit_value()));
  connect(ui_->pushButton_6, SIGNAL(clicked()), this, SLOT(digit_value()));
  connect(ui_->pushButton_7, SIGNAL(clicked()), this, SLOT(digit_value()));
  connect(ui_->pushButton_8, SIGNAL(clicked()), this, SLOT(digit_value()));
  connect(ui_->pushButton_9, SIGNAL(clicked()), this, SLOT(digit_value()));
  connect(ui_->pushButton_dot, SIGNAL(clicked()), this, SLOT(digit_value()));
  connect(ui_->pushButton_mod, SIGNAL(clicked()), this, SLOT(digit_value()));
  connect(ui_->pushButton_bracketclose, SIGNAL(clicked()), this,
          SLOT(digit_value()));
  connect(ui_->pushButton_bracketopen, SIGNAL(clicked()), this,
          SLOT(digit_value()));
  connect(ui_->pushButton_difference, SIGNAL(clicked()), this,
          SLOT(digit_value()));
  connect(ui_->pushButton_mult, SIGNAL(clicked()), this, SLOT(digit_value()));
  connect(ui_->pushButton_division, SIGNAL(clicked()), this,
          SLOT(digit_value()));
  connect(ui_->pushButton_addition, SIGNAL(clicked()), this,
          SLOT(digit_value()));
  connect(ui_->pushButton_ln, SIGNAL(clicked()), this, SLOT(digit_value()));
  connect(ui_->pushButton_log, SIGNAL(clicked()), this, SLOT(digit_value()));
  connect(ui_->pushButton_sqrt, SIGNAL(clicked()), this, SLOT(digit_value()));
  connect(ui_->pushButton_cos, SIGNAL(clicked()), this, SLOT(digit_value()));
  connect(ui_->pushButton_sin, SIGNAL(clicked()), this, SLOT(digit_value()));
  connect(ui_->pushButton_tan, SIGNAL(clicked()), this, SLOT(digit_value()));
  connect(ui_->pushButton_asin, SIGNAL(clicked()), this, SLOT(digit_value()));
  connect(ui_->pushButton_acos, SIGNAL(clicked()), this, SLOT(digit_value()));
  connect(ui_->pushButton_atan, SIGNAL(clicked()), this, SLOT(digit_value()));
  connect(ui_->pushButton_pow, SIGNAL(clicked()), this, SLOT(digit_value()));
  connect(ui_->pushButton_xnumber, SIGNAL(clicked()), this,
          SLOT(digit_value()));
  connect(ui_->pushButton_e, SIGNAL(clicked()), this, SLOT(digit_value()));
}

void SmartCalcView::digit_value() {
  QPushButton *button = (QPushButton *)sender();
  QString new_label;

  if (ui_->radioButton_string->isChecked()) {
    new_label = (ui_->lineEdit_string->text() + button->text());
    ui_->lineEdit_string->setText(new_label);
  } else if (ui_->radioButton_x->isChecked()) {
    new_label = (ui_->lineEdit_x->text() + button->text());
    ui_->lineEdit_x->setText(new_label);
    if (!ui_->lineEdit_x->text().isEmpty()) {
      ui_->pushButton_difference->setDisabled(true);
      ui_->pushButton_dot->setDisabled(false);
    }
  }

  QString check_graph = ui_->lineEdit_string->text();
  std::string utf_8_string = check_graph.toUtf8().constData();

  if (std::strchr(utf_8_string.c_str(), 'x') != NULL) {
    ui_->pushButton_graph->setDisabled(false);
  } else {
    ui_->pushButton_graph->setDisabled(true);
  }
}

void SmartCalcView::on_pushButton_backspace_clicked() {
  QString deleted_string = ui_->lineEdit_string->text();

  if (deleted_string.endsWith("atan(") || deleted_string.endsWith("asin(") ||
      deleted_string.endsWith("acos(") || deleted_string.endsWith("sqrt(")) {
    deleted_string.chop(5);
  } else if (deleted_string.endsWith("tan(") ||
             deleted_string.endsWith("cos(") ||
             deleted_string.endsWith("sin(") ||
             deleted_string.endsWith("log(")) {
    deleted_string.chop(4);
  } else if (deleted_string.endsWith("ln(")) {
    deleted_string.chop(3);
  } else {
    deleted_string.chop(1);
  }
  ui_->lineEdit_string->setText(deleted_string);

  QString check_graph = ui_->lineEdit_string->text();
  std::string utf_8_string = check_graph.toUtf8().constData();
  if (std::strchr(utf_8_string.c_str(), 'x') != NULL) {
    ui_->pushButton_graph->setDisabled(false);
  } else {
    ui_->pushButton_graph->setDisabled(true);
  }
}

void SmartCalcView::on_pushButton_result_clicked() {
  if (!ui_->lineEdit_string->text().isEmpty()) {
    QString result_output;
    int flagerror = 0, dotcount = 0;
    double result_calculation, number_x;
    char utf_8_arr_char[255] = "\0";
    char utf_8_arr_char_x[255] = "\0";

    QString xstring = ui_->lineEdit_x->text();
    std::string utf_8_string_x = xstring.toUtf8().constData();
    strcpy(utf_8_arr_char_x, utf_8_string_x.c_str());

    for (size_t i = 0; i < strlen(utf_8_arr_char_x); i++) {
      if ((utf_8_arr_char_x[0] == '-') && (utf_8_arr_char_x[1] == '.')) {
        flagerror = 1;
      }
      if (utf_8_arr_char_x[i] == '.') {
        dotcount++;
      }
    }
    if (dotcount > 1) {
      flagerror = 1;
    }

    number_x = atof(utf_8_arr_char_x);

    QString mystring = ui_->lineEdit_string->text();
    std::string utf_8_string = mystring.toUtf8().constData();
    strcpy(utf_8_arr_char, utf_8_string.c_str());

    result_calculation =
        controller_->CalculatorMainFunction(utf_8_arr_char, number_x);

    if (std::isnan(result_calculation) || flagerror) {
      ui_->lineEdit_string->setText("ERROR");
      ui_->lineEdit_x->clear();
    } else {
      result_output = QString::number(result_calculation, 'f', 7);
      ui_->lineEdit_string->setText(result_output);
    }
  } else {
    ui_->lineEdit_string->setText("EMPTY");
  }
}

void SmartCalcView::on_pushButton_backspacex_clicked() {
  QString deleted_string = ui_->lineEdit_x->text();
  deleted_string.chop(1);
  ui_->lineEdit_x->setText(deleted_string);
  if (ui_->radioButton_x->isChecked()) {
    if (ui_->lineEdit_x->text().isEmpty()) {
      ui_->pushButton_difference->setDisabled(false);
      ui_->pushButton_dot->setDisabled(true);
    }
  }
}

void SmartCalcView::on_radioButton_x_clicked() {
  ui_->pushButton_dot->setDisabled(true);
  ui_->pushButton_sin->setDisabled(true);
  ui_->pushButton_cos->setDisabled(true);
  ui_->pushButton_tan->setDisabled(true);
  ui_->pushButton_acos->setDisabled(true);
  ui_->pushButton_asin->setDisabled(true);
  ui_->pushButton_atan->setDisabled(true);
  ui_->pushButton_sqrt->setDisabled(true);
  ui_->pushButton_ln->setDisabled(true);
  ui_->pushButton_log->setDisabled(true);
  ui_->pushButton_pow->setDisabled(true);
  ui_->pushButton_addition->setDisabled(true);
  ui_->pushButton_sin->setDisabled(true);
  ui_->pushButton_xnumber->setDisabled(true);
  ui_->pushButton_bracketclose->setDisabled(true);
  ui_->pushButton_bracketopen->setDisabled(true);
  ui_->pushButton_mod->setDisabled(true);
  ui_->pushButton_division->setDisabled(true);
  ui_->pushButton_mult->setDisabled(true);
  ui_->pushButton_e->setDisabled(true);
}

void SmartCalcView::on_radioButton_string_clicked() {
  ui_->pushButton_dot->setDisabled(false);
  ui_->pushButton_difference->setDisabled(false);
  ui_->pushButton_sin->setDisabled(false);
  ui_->pushButton_cos->setDisabled(false);
  ui_->pushButton_tan->setDisabled(false);
  ui_->pushButton_acos->setDisabled(false);
  ui_->pushButton_asin->setDisabled(false);
  ui_->pushButton_atan->setDisabled(false);
  ui_->pushButton_sqrt->setDisabled(false);
  ui_->pushButton_ln->setDisabled(false);
  ui_->pushButton_log->setDisabled(false);
  ui_->pushButton_pow->setDisabled(false);
  ui_->pushButton_addition->setDisabled(false);
  ui_->pushButton_sin->setDisabled(false);
  ui_->pushButton_xnumber->setDisabled(false);
  ui_->pushButton_bracketclose->setDisabled(false);
  ui_->pushButton_bracketopen->setDisabled(false);
  ui_->pushButton_mod->setDisabled(false);
  ui_->pushButton_division->setDisabled(false);
  ui_->pushButton_mult->setDisabled(false);
  ui_->pushButton_e->setDisabled(false);
}

void SmartCalcView::on_pushButton_creditcalculator_clicked() {
  credit_->show();
}

void SmartCalcView::on_pushButton_graph_clicked() {
  graph_menu_->show();
  connect(this, &SmartCalcView::signal, graph_menu_, &GraphView::slot);
  emit signal(ui_->lineEdit_string->text());
}
}  // namespace s21

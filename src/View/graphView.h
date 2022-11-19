#ifndef SRC_VIEW_GRAPHVIEW_H_
#define SRC_VIEW_GRAPHVIEW_H_

#include "Control/smartCalcController.h"

namespace Ui {
class Graph;
}

namespace s21 {
class GraphView : public QWidget {
  Q_OBJECT
 public:
  explicit GraphView(SmartCalcController *cont, QWidget *parent = nullptr);
  ~GraphView();

 public slots:
  void slot(QString string);

 private:
  Ui::Graph *ui_;
  SmartCalcController *graph_controller_;
  QVector<double> x_vector_, y_vector_;
  double x_begin_, x_end_, h_, x_;

  void ErrorAlert();

 private slots:
  void on_pushButton_postroit_clicked();
};
}  // namespace s21

#endif  // SRC_VIEW_GRAPHVIEW_H_

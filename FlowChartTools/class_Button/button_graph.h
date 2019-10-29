#ifndef BUTTON_GRAPH_H
#define BUTTON_GRAPH_H
#include <QPushButton>
#include "class_Charts/chart_base.h"
#include "comdef.h"

class FlowChart;
class Button_Graph : public QPushButton
{
public:
    Button_Graph(QWidget *parent = nullptr);
    virtual ~Button_Graph();
    void setPaintChartType(int i);
};

#endif // BUTTON_GRAPH_H

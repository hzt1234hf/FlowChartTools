#include "button_graph.h"

Button_Graph::Button_Graph(QWidget *parent) : QPushButton (parent)
{

}

Button_Graph::~Button_Graph()
{

}
Chart_Base* Button_Graph::newChart()
{

}
void setPaintChart(FlowChart &fc, Chart_Base *cb);
{
    fc.curPaintChart = newChart();
}

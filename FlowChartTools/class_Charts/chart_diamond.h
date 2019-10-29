#ifndef CHART_DIAMOND_H
#define CHART_DIAMOND_H
#include "chart_base.h"

class Chart_Diamond : public Chart_Base
{
private:
    virtual void paintChart(QPainter & p);

public:
    Chart_Diamond(QWidget *parent = nullptr, PaintChartType type = PaintChartType::DIAMOND) : Chart_Base(parent,type,false,true){}
    Chart_Diamond(Chart_Diamond &cr):Chart_Base(cr){}
    Chart_Diamond( int x1, int y1, int x2, int y2, QWidget *parent = nullptr,PaintChartType type = PaintChartType::DIAMOND) : Chart_Base(x1,y1,x2,y2,parent,type){}
    ~Chart_Diamond(){}

};

#endif // CHART_DIAMOND_H

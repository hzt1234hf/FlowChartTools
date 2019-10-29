#ifndef CHART_ROUNDRECT_H
#define CHART_ROUNDRECT_H
#include "chart_base.h"

class Chart_RoundRect : public Chart_Base
{
private:
    virtual void paintChart(QPainter & p);

public:
    Chart_RoundRect(QWidget *parent = nullptr, PaintChartType type = PaintChartType::ROUNDRECT) : Chart_Base(parent,type,false,true){}
    Chart_RoundRect(Chart_RoundRect &cr):Chart_Base(cr){}
    Chart_RoundRect( int x1, int y1, int x2, int y2, QWidget *parent = nullptr,PaintChartType type = PaintChartType::ROUNDRECT) : Chart_Base(x1,y1,x2,y2,parent,type){}
    ~Chart_RoundRect(){}
};

#endif // CHART_ROUNDRECT_H

#ifndef CHART_RECT_H
#define CHART_RECT_H
#include "chart_base.h"

class Chart_Rect : public Chart_Base
{
private:
    virtual void paintChart(QPainter & p);
    virtual void updateMagPointInfo();

public:
    Chart_Rect(QWidget *parent = nullptr, PaintChartType type = PaintChartType::RECT) : Chart_Base(parent,type,false,true,8){}
    Chart_Rect(Chart_Rect &cr):Chart_Base(cr){}
    Chart_Rect( int x1, int y1, int x2, int y2, QWidget *parent = nullptr,PaintChartType type = PaintChartType::RECT) : Chart_Base(x1,y1,x2,y2,parent,type){}
    ~Chart_Rect(){}


};

#endif // CHART_RECT_H

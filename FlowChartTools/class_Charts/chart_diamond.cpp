#include "chart_diamond.h"

void Chart_Diamond::paintChart(QPainter & p)
{
    QPen tmp = p.pen();
    p.setPen(paintChartDrawPen);

    int sx = paintStart.rx(),sy = paintStart.ry(),ex = paintEnd.rx(),ey = paintEnd.ry();
    int midx = (sx+ex)>>1,midy = (sy+ey)>>1;

    if(graphPath) delete graphPath;
    graphPath = new QPainterPath;
    graphPath->moveTo(midx,sy);
    graphPath->lineTo(ex,midy);
    graphPath->lineTo(midx,ey);
    graphPath->lineTo(sx,midy);
    graphPath->lineTo(midx,sy);

    p.fillPath(*graphPath,paintChartFillPen);
    p.drawPath(*graphPath);

    p.setPen(tmp);
}

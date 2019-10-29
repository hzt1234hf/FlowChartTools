#include "chart_line.h"
double Chart_Line::extendWidth45 = 0;
double Chart_Line::arrayLength45 = 0;
double Chart_Line::arrayLength75 = 0;
double Chart_Line::arrayWidth75 = 0;
double Chart_Line::arrayLength15 = 0;
double Chart_Line::arrayWidth15 = 0;

#if (OPTIMIZATION == 1)
void Chart_Line::angle0(QPainterPath &linePath, int &sx,int &sy, int &ex, int &ey)
{
    ex = endPos.rx();
    ey = endPos.ry() - extendWidth;
    if(sy>ey)
    {
        linePath.lineTo(sx,ey);
        linePath.lineTo(ex,ey);
        graphPath->addRect(sx - containsWidth1_2,sy,containsWidth,ey - sy);
        graphPath->addRect(sx,ey - containsWidth1_2,ex-sx,containsWidth);
    }else{
        linePath.lineTo(ex,sy);
        linePath.lineTo(ex,ey);
        graphPath->addRect(sx,sy + containsWidth1_2,ex - sx,-containsWidth);
        graphPath->addRect(ex - containsWidth1_2,sy,containsWidth,ey - sy);
    }
}
void Chart_Line::anglePos90(QPainterPath &linePath, int &sx,int &sy, int &ex, int &ey)
{
    int midx,midy;
    ex = endPos.rx();
    ey = endPos.ry() + extendWidth;
    if(sy>ey)
    {
        if(sx>ex)
        {
            linePath.lineTo(ex,sy);
            linePath.lineTo(ex,ey);
            graphPath->addRect(sx,sy-containsWidth1_2,ex-sx,containsWidth);
            graphPath->addRect(ex-containsWidth1_2,sy,containsWidth,ey-sy);
        }else{
            midy = (sy+ey)>>1;
            linePath.lineTo(sx,midy);
            linePath.lineTo(ex,midy);
            linePath.lineTo(ex,ey);
            graphPath->addRect(sx - containsWidth1_2,sy,containsWidth,midy - sy);
            graphPath->addRect(sx,midy - containsWidth1_2,ex-sx,containsWidth);
            graphPath->addRect(ex - containsWidth1_2,midy,containsWidth,ey-midy);
        }
    }else{
        if(sx>ex)
        {
            midx = (sx+ex)>>1;
            linePath.lineTo(midx,sy);
            linePath.lineTo(midx,ey);
            linePath.lineTo(ex,ey);
            graphPath->addRect(sx,sy-containsWidth1_2,midx-sx,containsWidth);
            graphPath->addRect(midx-containsWidth1_2,sy,containsWidth,ey-sy);
            graphPath->addRect(midx,ey-containsWidth1_2,ex-midx,containsWidth);
        }else{
            linePath.lineTo(sx,ey);
            linePath.lineTo(ex,ey);
            graphPath->addRect(sx - containsWidth1_2,sy,containsWidth,ey - sy);
            graphPath->addRect(sx,ey - containsWidth1_2,ex - sx,containsWidth);
        }
    }
}
void Chart_Line::angleNeg90(QPainterPath &linePath, int &sx,int &sy, int &ex, int &ey)
{
    int midx,midy;
    ex = endPos.rx();
    ey = endPos.ry() - extendWidth;
    if(sy>ey)
    {
        if(sx>ex)
        {
            midx = (sx+ex)>>1;
            linePath.lineTo(midx,sy);
            linePath.lineTo(midx,ey);
            linePath.lineTo(ex,ey);
            graphPath->addRect(sx,sy-containsWidth1_2,midx-sx,containsWidth);
            graphPath->addRect(midx-containsWidth1_2,sy,containsWidth,ey-sy);
            graphPath->addRect(midx,ey-containsWidth1_2,ex-midx,containsWidth);
        }else{
            linePath.lineTo(sx,ey);
            linePath.lineTo(ex,ey);
            graphPath->addRect(sx - containsWidth1_2,sy,containsWidth,ey - sy);
            graphPath->addRect(sx,ey - containsWidth1_2,ex - sx,containsWidth);
        }
    }else{
        if(sx>ex)
        {
            linePath.lineTo(sx,ey);
            linePath.lineTo(ex,ey);
            graphPath->addRect(sx - containsWidth1_2,sy,containsWidth,ey - sy);
            graphPath->addRect(sx,ey - containsWidth1_2,ex - sx, containsWidth);
        }else{
            midy = (sy+ey)>>1;
            linePath.lineTo(sx,midy);
            linePath.lineTo(ex,midy);
            linePath.lineTo(ex,ey);
            graphPath->addRect(sx - containsWidth1_2,sy,containsWidth,midy - sy);
            graphPath->addRect(sx,midy-containsWidth1_2,ex-sx,containsWidth);
            graphPath->addRect(ex - containsWidth1_2,midy,containsWidth,ey-midy);
        }
    }
}
void Chart_Line::angle1EastWest(QPainterPath &linePath, int &sx,int &sy, int &ex, int &ey)
{
    int midx,midy;
    ex = endPos.rx() + extendWidth;
    ey = endPos.ry();
    if(sx>ex)
    {
        midx = (sx+ex)>>1;
        linePath.lineTo(midx,sy);
        linePath.lineTo(midx,ey);
        linePath.lineTo(ex,ey);
        graphPath->addRect(sx,sy - containsWidth1_2,midx - sx,containsWidth);
        graphPath->addRect(midx - containsWidth1_2,sy,containsWidth,ey - sy);
        graphPath->addRect(midx,ey - containsWidth1_2,ex - midx,containsWidth);
    }else{
        midy = (sy+ey)>>1;
        linePath.lineTo(sx,midy);
        linePath.lineTo(ex,midy);
        linePath.lineTo(ex,ey);
        graphPath->addRect(sx - containsWidth1_2,sy,containsWidth,midy - sy);
        graphPath->addRect(sx,midy-containsWidth1_2,ex-sx,containsWidth);
        graphPath->addRect(ex - containsWidth1_2,midy,containsWidth,ey-midy);
    }
}
void Chart_Line::angle1SouthNorth(QPainterPath &linePath, int &sx,int &sy, int &ex, int &ey)
{
    int midx,midy;
    ex = endPos.rx();
    ey = endPos.ry() - extendWidth;
    if(sy>ey)
    {
        midx = (sx+ex)>>1;
        linePath.lineTo(midx,sy);
        linePath.lineTo(midx,ey);
        linePath.lineTo(ex,ey);
        graphPath->addRect(sx,sy - containsWidth1_2,midx - sx,containsWidth);
        graphPath->addRect(midx - containsWidth1_2,sy,containsWidth,ey - sy);
        graphPath->addRect(midx,ey - containsWidth1_2,ex - midx,containsWidth);
    }else{
        midy = (sy+ey)>>1;
        linePath.lineTo(sx,midy);
        linePath.lineTo(ex,midy);
        linePath.lineTo(ex,ey);
        graphPath->addRect(sx - containsWidth1_2,sy,containsWidth,midy - sy);
        graphPath->addRect(sx,midy-containsWidth1_2,ex-sx,containsWidth);
        graphPath->addRect(ex - containsWidth1_2,midy,containsWidth,ey-midy);
    }
}

#endif

void Chart_Line::drawLineHead(const ORIENTION o,const LINE_HEAD_TYPE lht,const int x,const int y,QPainter & p,QPainterPath &linePath, QPainterPath &graphPath)
{

    switch(o)
    {
        case ORIENTION::NORTH:{
            linePath.moveTo(x,y - extendWidth);
            linePath.lineTo(x,y - arrayLength);
            graphPath.addRect(x - containsWidth1_2,y,containsWidth,-extendWidth);
            switch(lht)
            {
                case LINE_HEAD_TYPE::ARROW1:{
                    linePath.lineTo(x,y);
                    linePath.lineTo(x-arrayWidth,y-arrayLength);
                    linePath.moveTo(x,y);
                    linePath.lineTo(x+arrayWidth,y-arrayLength);
                    linePath.moveTo(x,y);
                }break;
                case LINE_HEAD_TYPE::ARROW2:{
                    linePath.moveTo(x - arrayWidth,y - arrayLength);
                    linePath.lineTo(x + arrayWidth,y - arrayLength);
                    linePath.lineTo(x,y);
                    linePath.lineTo(x - arrayWidth,y - arrayLength);
                    linePath.moveTo(x,y);
                }break;
                case LINE_HEAD_TYPE::ARROW3:{
                    QPainterPath tmp;
                    tmp.moveTo(x - arrayWidth,y - arrayLength);
                    tmp.lineTo(x + arrayWidth,y - arrayLength);
                    tmp.lineTo(x,y);
                    tmp.lineTo(x - arrayWidth,y - arrayLength);

                    p.fillPath(tmp,p.pen().brush());
                    p.drawPath(tmp);
                    linePath.moveTo(x,y);
                }break;
                case LINE_HEAD_TYPE::ARROW0:{
                    linePath.lineTo(x,y);
                }break;
                default:{

                }break;
            }
        }break;
        case ORIENTION::EAST:{
            linePath.moveTo(x + extendWidth,y);
            linePath.lineTo(x + arrayLength,y);
            graphPath.addRect(x,y - containsWidth1_2,extendWidth,containsWidth);
            switch(lht)
            {
                case LINE_HEAD_TYPE::ARROW1:{
                    linePath.lineTo(x,y);
                    linePath.lineTo(x+arrayLength,y+arrayWidth);
                    linePath.moveTo(x,y);
                    linePath.lineTo(x+arrayLength,y-arrayWidth);
                    linePath.moveTo(x,y);
                }break;
                case LINE_HEAD_TYPE::ARROW2:{
                    linePath.moveTo(x + arrayLength,y - arrayWidth);
                    linePath.lineTo(x + arrayLength,y + arrayWidth);
                    linePath.lineTo(x,y);
                    linePath.lineTo(x + arrayLength,y - arrayWidth);
                    linePath.moveTo(x,y);

                }break;
                case LINE_HEAD_TYPE::ARROW3:{
                    QPainterPath tmp;
                    tmp.moveTo(x + arrayLength,y - arrayWidth);
                    tmp.lineTo(x + arrayLength,y + arrayWidth);
                    tmp.lineTo(x,y);
                    tmp.lineTo(x + arrayLength,y - arrayWidth);

                    p.fillPath(tmp,p.pen().brush());
                    p.drawPath(tmp);
                    linePath.moveTo(x,y);
                }break;
                case LINE_HEAD_TYPE::ARROW0:{
                    linePath.lineTo(x,y);
                }break;
                default:{

                }break;
            }

        }break;
        case ORIENTION::SOUTH:{
            linePath.moveTo(x,y + extendWidth);
            linePath.lineTo(x,y + arrayLength);
            graphPath.addRect(x - containsWidth1_2,y,containsWidth,extendWidth);
            switch(lht)
            {
                case LINE_HEAD_TYPE::ARROW1:{
                linePath.lineTo(x,y);
                    linePath.lineTo(x-arrayWidth,y+arrayLength);
                    linePath.moveTo(x,y);
                    linePath.lineTo(x+arrayWidth,y+arrayLength);
                    linePath.moveTo(x,y);
                }break;
                case LINE_HEAD_TYPE::ARROW2:{
                    linePath.moveTo(x - arrayWidth,y + arrayLength);
                    linePath.lineTo(x + arrayWidth,y + arrayLength);
                    linePath.lineTo(x,y);
                    linePath.lineTo(x - arrayWidth,y + arrayLength);
                    linePath.moveTo(x,y);
                }break;
                case LINE_HEAD_TYPE::ARROW3:{
                QPainterPath tmp;
                tmp.moveTo(x - arrayWidth,y + arrayLength);
                tmp.lineTo(x + arrayWidth,y + arrayLength);
                tmp.lineTo(x,y);
                tmp.lineTo(x - arrayWidth,y + arrayLength);

                p.fillPath(tmp,p.pen().brush());
                p.drawPath(tmp);
                linePath.moveTo(x,y);
                }break;
                case LINE_HEAD_TYPE::ARROW0:{
                    linePath.lineTo(x,y);
                }break;
                default:{

                }break;
            }
        }break;
        case ORIENTION::WEST:{
            linePath.moveTo(x - extendWidth,y);
            linePath.lineTo(x - arrayLength,y);
            graphPath.addRect(x,y - containsWidth1_2,-extendWidth,containsWidth);
            switch(lht)
            {
                case LINE_HEAD_TYPE::ARROW1:{
                    linePath.lineTo(x,y);
                    linePath.lineTo(x-arrayLength,y+arrayWidth);
                    linePath.moveTo(x,y);
                    linePath.lineTo(x-arrayLength,y-arrayWidth);
                    linePath.moveTo(x,y);
                }break;
                case LINE_HEAD_TYPE::ARROW2:{
                    linePath.moveTo(x - arrayLength,y - arrayWidth);
                    linePath.lineTo(x - arrayLength,y + arrayWidth);
                    linePath.lineTo(x,y);
                    linePath.lineTo(x - arrayLength,y - arrayWidth);
                    linePath.moveTo(x,y);
                }break;
                case LINE_HEAD_TYPE::ARROW3:{
                    QPainterPath tmp;
                    tmp.moveTo(x - arrayLength,y - arrayWidth);
                    tmp.lineTo(x - arrayLength,y + arrayWidth);
                    tmp.lineTo(x,y);
                    tmp.lineTo(x - arrayLength,y - arrayWidth);

                    p.fillPath(tmp,p.pen().brush());
                    p.drawPath(tmp);
                    linePath.moveTo(x,y);
                }break;
                case LINE_HEAD_TYPE::ARROW0:{
                    linePath.lineTo(x,y);
                }break;
                default:{

                }break;
            }
        }break;
        case ORIENTION::NORTHEAST:{
            linePath.moveTo(x + extendWidth45,y - extendWidth45);
            linePath.lineTo(x + arrayLength45,y - arrayLength45);
            //graphPath.addRect(x,y - containsWidth1_2,-extendWidth,containsWidth);

            QPolygonF tmp;
            tmp<<QPointF(x + extendWidth45-(arrayLength45 - arrayLength75),y - extendWidth45-(arrayWidth75 - arrayLength45))
              <<QPointF(x + extendWidth45+(arrayLength15 - arrayLength45),y - extendWidth45+(arrayLength45 - arrayWidth15))
             <<QPointF(x+(arrayLength15 - arrayLength45),y+(arrayLength45 - arrayWidth15))
            <<QPointF(x-(arrayLength45 - arrayLength75),y-(arrayWidth75 - arrayLength45))
            <<QPointF(x + extendWidth45-(arrayLength45 - arrayLength75),y - extendWidth45-(arrayWidth75 - arrayLength45));
            graphPath.addPolygon(tmp);

            switch(lht)
            {
                case LINE_HEAD_TYPE::ARROW1:{
                    linePath.lineTo(x,y);
                    linePath.lineTo(x+arrayLength75,y-arrayWidth75);
                    linePath.moveTo(x,y);
                    linePath.lineTo(x+arrayLength15,y-arrayWidth15);
                    linePath.moveTo(x,y);
                }break;
                case LINE_HEAD_TYPE::ARROW2:{
                    linePath.moveTo(x + arrayLength75,y - arrayWidth75);
                    linePath.lineTo(x + arrayLength15,y - arrayWidth15);
                    linePath.lineTo(x,y);
                    linePath.lineTo(x + arrayLength75,y - arrayWidth75);
                    linePath.moveTo(x,y);
                }break;
                case LINE_HEAD_TYPE::ARROW3:{
                    QPainterPath tmp;
                    tmp.moveTo(x + arrayLength75,y - arrayWidth75);
                    tmp.lineTo(x + arrayLength15,y - arrayWidth15);
                    tmp.lineTo(x,y);
                    tmp.lineTo(x + arrayLength75,y - arrayWidth75);

                    p.fillPath(tmp,p.pen().brush());
                    p.drawPath(tmp);
                    linePath.moveTo(x,y);
                }break;
                case LINE_HEAD_TYPE::ARROW0:{
                    linePath.lineTo(x,y);
                }break;
                default:{

                }break;
            }
        }break;
        case ORIENTION::NORTHWEST:{
            linePath.moveTo(x - extendWidth45,y - extendWidth45);
            linePath.lineTo(x - arrayLength45,y - arrayLength45);
            //graphPath.addRect(x,y - containsWidth1_2,-extendWidth,containsWidth);

            QPolygonF tmp;
            tmp<<QPointF(x - extendWidth45+(arrayLength45 - arrayLength75),y - extendWidth45-(arrayWidth75 - arrayLength45))
              <<QPointF(x - extendWidth45-(arrayLength15 - arrayLength45),y - extendWidth45+(arrayLength45 - arrayWidth15))
             <<QPointF(x-(arrayLength15 - arrayLength45),y+(arrayLength45 - arrayWidth15))
            <<QPointF(x+(arrayLength45 - arrayLength75),y-(arrayWidth75 - arrayLength45))
            <<QPointF(x - extendWidth45+(arrayLength45 - arrayLength75),y - extendWidth45-(arrayWidth75 - arrayLength45));
            graphPath.addPolygon(tmp);

            switch(lht)
            {
                case LINE_HEAD_TYPE::ARROW1:{
                    linePath.lineTo(x,y);
                    linePath.lineTo(x-arrayLength75,y-arrayWidth75);
                    linePath.moveTo(x,y);
                    linePath.lineTo(x-arrayLength15,y-arrayWidth15);
                    linePath.moveTo(x,y);
                }break;
                case LINE_HEAD_TYPE::ARROW2:{
                    linePath.moveTo(x - arrayLength75,y - arrayWidth75);
                    linePath.lineTo(x - arrayLength15,y - arrayWidth15);
                    linePath.lineTo(x,y);
                    linePath.lineTo(x - arrayLength75,y - arrayWidth75);
                    linePath.moveTo(x,y);
                }break;
                case LINE_HEAD_TYPE::ARROW3:{
                    QPainterPath tmp;
                    tmp.moveTo(x - arrayLength75,y - arrayWidth75);
                    tmp.lineTo(x - arrayLength15,y - arrayWidth15);
                    tmp.lineTo(x,y);
                    tmp.lineTo(x - arrayLength75,y - arrayWidth75);

                    p.fillPath(tmp,p.pen().brush());
                    p.drawPath(tmp);
                    linePath.moveTo(x,y);
                }break;
                case LINE_HEAD_TYPE::ARROW0:{
                    linePath.lineTo(x,y);
                }break;
                default:{

                }break;
            }
        }break;
        case ORIENTION::SOUTHWEST:{
            linePath.moveTo(x - extendWidth45,y + extendWidth45);
            linePath.lineTo(x - arrayLength45,y + arrayLength45);
            //graphPath.addRect(x,y - containsWidth1_2,-extendWidth,containsWidth);

            QPolygonF tmp;
            tmp<<QPointF(x - extendWidth45+(arrayLength45 - arrayLength75),y + extendWidth45+(arrayWidth75 - arrayLength45))
              <<QPointF(x - extendWidth45-(arrayLength15 - arrayLength45),y + extendWidth45-(arrayLength45 - arrayWidth15))
             <<QPointF(x-(arrayLength15 - arrayLength45),y-(arrayLength45 - arrayWidth15))
            <<QPointF(x+(arrayLength45 - arrayLength75),y+(arrayWidth75 - arrayLength45))
            <<QPointF(x - extendWidth45+(arrayLength45 - arrayLength75),y + extendWidth45+(arrayWidth75 - arrayLength45));
            graphPath.addPolygon(tmp);

            switch(lht)
            {
                case LINE_HEAD_TYPE::ARROW1:{
                    linePath.lineTo(x,y);
                    linePath.lineTo(x-arrayLength75,y+arrayWidth75);
                    linePath.moveTo(x,y);
                    linePath.lineTo(x-arrayLength15,y+arrayWidth15);
                    linePath.moveTo(x,y);
                }break;
                case LINE_HEAD_TYPE::ARROW2:{
                    linePath.moveTo(x - arrayLength75,y + arrayWidth75);
                    linePath.lineTo(x - arrayLength15,y + arrayWidth15);
                    linePath.lineTo(x,y);
                    linePath.lineTo(x - arrayLength75,y + arrayWidth75);
                    linePath.moveTo(x,y);
                }break;
                case LINE_HEAD_TYPE::ARROW3:{
                    QPainterPath tmp;
                    tmp.moveTo(x - arrayLength75,y + arrayWidth75);
                    tmp.lineTo(x - arrayLength15,y + arrayWidth15);
                    tmp.lineTo(x,y);
                    tmp.lineTo(x - arrayLength75,y + arrayWidth75);

                    p.fillPath(tmp,p.pen().brush());
                    p.drawPath(tmp);
                    linePath.moveTo(x,y);
                }break;
                case LINE_HEAD_TYPE::ARROW0:{
                    linePath.lineTo(x,y);
                }break;
                default:{

                }break;
            }
        }break;
        case ORIENTION::SOUTHEAST:{
            linePath.moveTo(x + extendWidth45,y + extendWidth45);
            linePath.lineTo(x + arrayLength45,y + arrayLength45);
            //graphPath.addRect(x,y - containsWidth1_2,-extendWidth,containsWidth);

            QPolygonF tmp;
            tmp<<QPointF(x + extendWidth45-(arrayLength45 - arrayLength75),y + extendWidth45+(arrayWidth75 - arrayLength45))
              <<QPointF(x + extendWidth45+(arrayLength15 - arrayLength45),y + extendWidth45-(arrayLength45 - arrayWidth15))
             <<QPointF(x+(arrayLength15 - arrayLength45),y-(arrayLength45 - arrayWidth15))
            <<QPointF(x-(arrayLength45 - arrayLength75),y+(arrayWidth75 - arrayLength45))
            <<QPointF(x + extendWidth45-(arrayLength45 - arrayLength75),y + extendWidth45+(arrayWidth75 - arrayLength45));
            graphPath.addPolygon(tmp);

            switch(lht)
            {
                case LINE_HEAD_TYPE::ARROW1:{
                    linePath.lineTo(x,y);
                    linePath.lineTo(x+arrayLength75,y+arrayWidth75);
                    linePath.moveTo(x,y);
                    linePath.lineTo(x+arrayLength15,y+arrayWidth15);
                    linePath.moveTo(x,y);
                }break;
                case LINE_HEAD_TYPE::ARROW2:{
                    linePath.moveTo(x + arrayLength75,y + arrayWidth75);
                    linePath.lineTo(x + arrayLength15,y + arrayWidth15);
                    linePath.lineTo(x,y);
                    linePath.lineTo(x + arrayLength75,y + arrayWidth75);
                    linePath.moveTo(x,y);
                }break;
                case LINE_HEAD_TYPE::ARROW3:{
                    QPainterPath tmp;
                    tmp.moveTo(x + arrayLength75,y + arrayWidth75);
                    tmp.lineTo(x + arrayLength15,y + arrayWidth15);
                    tmp.lineTo(x,y);
                    tmp.lineTo(x + arrayLength75,y + arrayWidth75);

                    p.fillPath(tmp,p.pen().brush());
                    p.drawPath(tmp);
                    linePath.moveTo(x,y);
                }break;
                case LINE_HEAD_TYPE::ARROW0:{
                    linePath.lineTo(x,y);
                }break;
                default:{

                }break;
            }
        }break;
    }
}
void Chart_Line::drawStraightLine(int sx, int sy, int ex, int ey,QPainterPath &linePath, QPainterPath &graphPath)
{
    linePath.moveTo(sx,sy);
    linePath.lineTo(ex,ey);
    if(sx<ex && sy<ey)
    {
        QPolygonF tmp;
        tmp<<QPointF(sx,sy)<<QPointF(sx+containsWidth1_2,sy)<<QPointF(ex,ey-containsWidth1_2)<<QPointF(ex,ey)<<QPointF(ex - containsWidth1_2,ey)<<QPointF(sx,sy+containsWidth1_2)<<QPointF(sx,sy);
        graphPath.addPolygon(tmp);
    }else if(sx>ex && sy>ey)
    {
        QPolygonF tmp;
        tmp<<QPointF(ex,ey)<<QPointF(ex+containsWidth1_2,ey)<<QPointF(sx,sy-containsWidth1_2)<<QPointF(sx,sy)<<QPointF(sx - containsWidth1_2,sy)<<QPointF(ex,ey+containsWidth1_2)<<QPointF(ex,ey);
        graphPath.addPolygon(tmp);
    }else if(sx<ex)
    {
        QPolygonF tmp;
        tmp<<QPointF(sx,sy)<<QPointF(sx+containsWidth1_2,sy)<<QPointF(ex,ey+containsWidth1_2)<<QPointF(ex,ey)<<QPointF(ex - containsWidth1_2,ey)<<QPointF(sx,sy-containsWidth1_2)<<QPointF(sx,sy);
        graphPath.addPolygon(tmp);
    }else
    {
        QPolygonF tmp;
        tmp<<QPointF(ex,ey)<<QPointF(ex+containsWidth1_2,ey)<<QPointF(sx,sy+containsWidth1_2)<<QPointF(sx,sy)<<QPointF(sx - containsWidth1_2,sy)<<QPointF(ex,ey-containsWidth1_2)<<QPointF(ex,ey);
        graphPath.addPolygon(tmp);
    }
}

void Chart_Line::paintChart(QPainter & p)
{
    QPen tmp = p.pen();
    p.setPen(paintChartDrawPen);

    chartText.textType1->setGeometry((width()>>1) - (chartText.textType1->width()>>1),(height()>>1) - (chartText.textType1->height()>>1),chartText.textType1->width(),chartText.textType1->height());
    int midx,midy;
    int sx,sy,ex,ey;
    QPainterPath linePath;

    if(graphPath) delete graphPath;
    graphPath = new QPainterPath;
#if (OPTIMIZATION == 1)
    switch(startDirect)
    {
        case ORIENTION::NORTH:{
            sx = startPos.rx();
            sy = startPos.ry() - extendWidth;
            linePath.moveTo(startPos.rx(),startPos.ry());
            linePath.lineTo(sx,sy);
            graphPath->addRect(sx - containsWidth1_2,startPos.ry(),containsWidth,-extendWidth);
            switch(endDirect)
            {
                case ORIENTION::NORTH:{
                    angle0(linePath,sx,sy,ex,ey);
                    graphPath->addRect(ex - containsWidth1_2,ey,containsWidth,extendWidth);
                }break;
                case ORIENTION::EAST:{
                    angleNeg90(linePath,sx,sy,ex,ey);
                    graphPath->addRect(ex,ey - containsWidth1_2,-extendWidth,containsWidth);
                }break;
                case ORIENTION::SOUTH:{
                    angle1SouthNorth(linePath,sx,sy,ex,ey);
                    graphPath->addRect(ex - containsWidth1_2,ey,containsWidth,-extendWidth);
                }break;
                case ORIENTION::WEST:{
                    anglePos90(linePath,sx,sy,ex,ey);
                    graphPath->addRect(ex,ey - containsWidth1_2,extendWidth,containsWidth);
                }
            }
            linePath.lineTo(endPos.rx(),endPos.ry());
        }break;
        case ORIENTION::EAST:{
            sx = startPos.rx() + extendWidth;
            sy = startPos.ry();
            linePath.moveTo(startPos.rx(),startPos.ry());
            linePath.lineTo(sx,sy);
            graphPath->addRect(startPos.rx(),sy - containsWidth1_2,extendWidth,containsWidth);
            switch(endDirect)
            {
                case ORIENTION::NORTH:{
                    anglePos90(linePath,sx,sy,ex,ey);
                    graphPath->addRect(ex - containsWidth1_2,ey,containsWidth,extendWidth);
                }break;
                case ORIENTION::EAST:{
                    angle0(linePath,sx,sy,ex,ey);
                    graphPath->addRect(ex,ey - containsWidth1_2,-extendWidth,containsWidth);
                }break;
                case ORIENTION::SOUTH:{
                    angleNeg90(linePath,sx,sy,ex,ey);
                    graphPath->addRect(ex - containsWidth1_2,ey,containsWidth,-extendWidth);
                }break;
                case ORIENTION::WEST:{
                    angle1EastWest(linePath,sx,sy,ex,ey);
                    graphPath->addRect(ex,ey - containsWidth1_2,extendWidth,containsWidth);
                }
            }
            linePath.lineTo(endPos.rx(),endPos.ry());
        }break;
        case ORIENTION::SOUTH:{
            sx = startPos.rx();
            sy = startPos.ry() + extendWidth;
            linePath.moveTo(startPos.rx(),startPos.ry());
            linePath.lineTo(sx,sy);
            graphPath->addRect(startPos.rx() - extendWidth,startPos.ry(),containsWidth,extendWidth);
            switch(endDirect)
            {
                case ORIENTION::NORTH:{
                    angle1SouthNorth(linePath,sx,sy,ex,ey);
                    graphPath->addRect(ex - containsWidth1_2,ey,containsWidth,extendWidth);
                }break;
                case ORIENTION::EAST:{
                    anglePos90(linePath,sx,sy,ex,ey);
                    graphPath->addRect(ex,ey - containsWidth1_2,-extendWidth,containsWidth);
                }break;
                case ORIENTION::SOUTH:{
                    angle0(linePath,sx,sy,ex,ey);
                    graphPath->addRect(ex - containsWidth1_2,ey,containsWidth,-extendWidth);

                }break;
                case ORIENTION::WEST:{
                    angleNeg90(linePath,sx,sy,ex,ey);
                    graphPath->addRect(ex,ey - containsWidth1_2,extendWidth,containsWidth);
                }
            }
            linePath.lineTo(endPos.rx(),endPos.ry());
        }break;
        case ORIENTION::WEST:{
            sx = startPos.rx() - extendWidth;
            sy = startPos.ry();
            linePath.moveTo(startPos.rx(),startPos.ry());
            linePath.lineTo(sx,sy);
            graphPath->addRect(startPos.rx(),startPos.ry() - containsWidth1_2,-extendWidth,containsWidth);
            switch(endDirect)
            {
                case ORIENTION::NORTH:{
                    anglePos90(linePath,sx,sy,ex,ey);
                    graphPath->addRect(ex - containsWidth1_2,ey,containsWidth,extendWidth);
                }break;
                case ORIENTION::EAST:{
                    angle1EastWest(linePath,sx,sy,ex,ey);
                    graphPath->addRect(ex,ey - containsWidth1_2,-extendWidth,containsWidth);
                }break;
                case ORIENTION::SOUTH:{
                    anglePos90(linePath,sx,sy,ex,ey);
                    graphPath->addRect(ex - containsWidth1_2,ey,containsWidth,-extendWidth);
                }break;
                case ORIENTION::WEST:{
                    angle0(linePath,sx,sy,ex,ey);
                    graphPath->addRect(ex,ey - containsWidth1_2,extendWidth,containsWidth);
                }
            }
            linePath.lineTo(endPos.rx(),endPos.ry());
        }break;
        default:
        {
        }
    }
#else
    switch(startDirect)
    {
        case ORIENTION::NORTH:{
            sx = startPos.rx();
            sy = startPos.ry() - extendWidth;
            drawLineHead(startDirect,startLineHeadType,startPos.rx(),startPos.ry(),p,linePath,*graphPath);
            linePath.moveTo(sx,sy);
            switch(endDirect)
            {
                case ORIENTION::NORTH:{
                    ex = endPos.rx();
                    ey = endPos.ry() - extendWidth;
                    if(sy>ey)
                    {
                        linePath.lineTo(sx,ey);
                        linePath.lineTo(ex,ey);
                        graphPath->addRect(sx - containsWidth1_2,sy,containsWidth,ey - sy);
                        graphPath->addRect(sx,ey - containsWidth1_2,ex-sx,containsWidth);
                        chartText.textType1->setGeometry((width()>>1) - (chartText.textType1->width()>>1),ey - (chartText.textType1->height()>>1),chartText.textType1->width(),chartText.textType1->height());
                    }else{
                        linePath.lineTo(ex,sy);
                        linePath.lineTo(ex,ey);
                        graphPath->addRect(sx,sy + containsWidth1_2,ex - sx,-containsWidth);
                        graphPath->addRect(ex - containsWidth1_2,sy,containsWidth,ey - sy);
                        chartText.textType1->setGeometry((width()>>1) - (chartText.textType1->width()>>1),sy - (chartText.textType1->height()>>1),chartText.textType1->width(),chartText.textType1->height());
                    }
                    drawLineHead(endDirect,endLineHeadType,endPos.rx(),endPos.ry(),p,linePath,*graphPath);
                }break;
                case ORIENTION::EAST:{
                    ex = endPos.rx() + extendWidth;
                    ey = endPos.ry();
                    if(sy>ey)
                    {
                        if(sx>ex)
                        {
                            linePath.lineTo(sx,ey);
                            linePath.lineTo(ex,ey);
                            graphPath->addRect(sx - containsWidth1_2,sy,containsWidth,ey - sy);
                            graphPath->addRect(sx,ey - containsWidth1_2,ex - sx, containsWidth);
                            chartText.textType1->setGeometry((width()>>1) - (chartText.textType1->width()>>1),ey - (chartText.textType1->height()>>1),chartText.textType1->width(),chartText.textType1->height());

                        }else{
                            midy = (sy+ey)>>1;
                            linePath.lineTo(sx,midy);
                            linePath.lineTo(ex,midy);
                            linePath.lineTo(ex,ey);
                            graphPath->addRect(sx - containsWidth1_2,sy,containsWidth,midy - sy);
                            graphPath->addRect(sx,midy - containsWidth1_2,ex-sx,containsWidth);
                            graphPath->addRect(ex - containsWidth1_2,midy,containsWidth,ey-midy);
                            chartText.textType1->setGeometry((width()>>1) - (chartText.textType1->width()>>1),midy - (chartText.textType1->height()>>1),chartText.textType1->width(),chartText.textType1->height());
                        }
                    }else{
                        if(sx>ex)
                        {
                            midx = (sx + ex)>>1;
                            linePath.lineTo(midx,sy);
                            linePath.lineTo(midx,ey);
                            linePath.lineTo(ex,ey);
                            graphPath->addRect(sx,sy-containsWidth1_2,midx-sx,containsWidth);
                            graphPath->addRect(midx-containsWidth1_2,sy,containsWidth,ey-sy);
                            graphPath->addRect(midx,ey-containsWidth1_2,ex-midx,containsWidth);
                            chartText.textType1->setGeometry(midx - (chartText.textType1->width()>>1),(height()>>1)  - (chartText.textType1->height()>>1),chartText.textType1->width(),chartText.textType1->height());
                        }else{
                            linePath.lineTo(ex,sy);
                            linePath.lineTo(ex,ey);
                            graphPath->addRect(sx,sy-containsWidth1_2,ex-sx,containsWidth);
                            graphPath->addRect(ex-containsWidth1_2,sy,containsWidth,ey-sy);
                            chartText.textType1->setGeometry((width()>>1) - (chartText.textType1->width()>>1),sy - (chartText.textType1->height()>>1),chartText.textType1->width(),chartText.textType1->height());
                        }
                    }
                    drawLineHead(endDirect,endLineHeadType,endPos.rx(),endPos.ry(),p,linePath,*graphPath);
                }break;
                case ORIENTION::SOUTH:{
                    ex = endPos.rx();
                    ey = endPos.ry() + extendWidth;
                    if(sy>ey)
                    {
                        midy = (sy+ey)>>1;
                        linePath.lineTo(sx,midy);
                        linePath.lineTo(ex,midy);
                        linePath.lineTo(ex,ey);
                        graphPath->addRect(sx - containsWidth1_2,sy,containsWidth,midy - sy);
                        graphPath->addRect(sx,midy-containsWidth1_2,ex-sx,containsWidth);
                        graphPath->addRect(ex - containsWidth1_2,midy,containsWidth,ey-midy);
                        chartText.textType1->setGeometry((width()>>1) - (chartText.textType1->width()>>1),midy - (chartText.textType1->height()>>1),chartText.textType1->width(),chartText.textType1->height());
                    }else{
                        midx = (sx + ex)>>1;
                        linePath.lineTo(midx,sy);
                        linePath.lineTo(midx,ey);
                        linePath.lineTo(ex,ey);
                        graphPath->addRect(sx,sy - containsWidth1_2,midx - sx,containsWidth);
                        graphPath->addRect(midx - containsWidth1_2,sy,containsWidth,ey - sy);
                        graphPath->addRect(midx,ey - containsWidth1_2,ex - midx,containsWidth);
                        chartText.textType1->setGeometry(midx - (chartText.textType1->width()>>1),(height()>>1) - (chartText.textType1->height()>>1),chartText.textType1->width(),chartText.textType1->height());
                    }
                    drawLineHead(endDirect,endLineHeadType,endPos.rx(),endPos.ry(),p,linePath,*graphPath);
                }break;
                case ORIENTION::WEST:{
                    ex = endPos.rx() - extendWidth;
                    ey = endPos.ry();
                    if(sy>ey)
                    {
                        if(sx>ex)
                        {
                            midy = (sy+ey)>>1;
                            linePath.lineTo(sx,midy);
                            linePath.lineTo(ex,midy);
                            linePath.lineTo(ex,ey);
                            graphPath->addRect(sx - containsWidth1_2,sy,containsWidth,midy - sy);
                            graphPath->addRect(sx,midy - containsWidth1_2,ex - sx,containsWidth);
                            graphPath->addRect(ex - containsWidth1_2,midy,containsWidth,ey - midy);
                            chartText.textType1->setGeometry((width()>>1) - (chartText.textType1->width()>>1),midy - (chartText.textType1->height()>>1),chartText.textType1->width(),chartText.textType1->height());

                        }else{
                            linePath.lineTo(sx,ey);
                            linePath.lineTo(ex,ey);
                            graphPath->addRect(sx - containsWidth1_2,sy,containsWidth,ey - sy);
                            graphPath->addRect(sx,ey - containsWidth1_2,ex - sx,containsWidth);
                            chartText.textType1->setGeometry((width()>>1) - (chartText.textType1->width()>>1),ey - (chartText.textType1->height()>>1),chartText.textType1->width(),chartText.textType1->height());
                        }
                    }else{
                        if(sx>ex)
                        {
                            linePath.lineTo(ex,sy);
                            linePath.lineTo(ex,ey);
                            graphPath->addRect(sx,sy - containsWidth1_2,ex-sx,containsWidth);
                            graphPath->addRect(ex - containsWidth1_2,sy,containsWidth,ey-sy);
                            chartText.textType1->setGeometry((width()>>1) - (chartText.textType1->width()>>1),sy - (chartText.textType1->height()>>1),chartText.textType1->width(),chartText.textType1->height());
                        }else{
                            midx = (sx+ex)>>1;
                            linePath.lineTo(midx,sy);
                            linePath.lineTo(midx,ey);
                            linePath.lineTo(ex,ey);
                            graphPath->addRect(sx,sy - containsWidth1_2,midx-sx,containsWidth);
                            graphPath->addRect(midx - containsWidth1_2,sy,containsWidth,ey-sy);
                            graphPath->addRect(midx,ey - containsWidth1_2,ex-midx,containsWidth);
                            chartText.textType1->setGeometry(midx - (chartText.textType1->width()>>1),(height()>>1) - (chartText.textType1->height()>>1),chartText.textType1->width(),chartText.textType1->height());
                        }
                    }
                    drawLineHead(endDirect,endLineHeadType,endPos.rx(),endPos.ry(),p,linePath,*graphPath);
                }break;
                case ORIENTION::ENDPOINT:{
                    drawStraightLine(sx,sy,endPos.rx(),endPos.ry(),linePath,*graphPath);
                }break;
                case ORIENTION::NORTHEAST:
                {
                    drawStraightLine(sx,sy,endPos.rx() + extendWidth45,endPos.ry() - extendWidth45,linePath,*graphPath);
                    drawLineHead(endDirect,endLineHeadType,endPos.rx(),endPos.ry(),p,linePath,*graphPath);
                }break;
                case ORIENTION::NORTHWEST:
                {
                    drawStraightLine(sx,sy,endPos.rx() - extendWidth45,endPos.ry() - extendWidth45,linePath,*graphPath);
                    drawLineHead(endDirect,endLineHeadType,endPos.rx(),endPos.ry(),p,linePath,*graphPath);
                }break;
                case ORIENTION::SOUTHEAST:{
                    drawStraightLine(sx,sy,endPos.rx() + extendWidth45,endPos.ry() + extendWidth45,linePath,*graphPath);
                    drawLineHead(endDirect,endLineHeadType,endPos.rx(),endPos.ry(),p,linePath,*graphPath);
                }break;
                case ORIENTION::SOUTHWEST:
                {
                    drawStraightLine(sx,sy,endPos.rx() - extendWidth45,endPos.ry() + extendWidth45,linePath,*graphPath);
                    drawLineHead(endDirect,endLineHeadType,endPos.rx(),endPos.ry(),p,linePath,*graphPath);
                }break;
                default:
                {
                }
            }
            //linePath.lineTo(endPos.rx(),endPos.ry());
        }break;
        case ORIENTION::EAST:{

            sx = startPos.rx() + extendWidth;
            sy = startPos.ry();
            drawLineHead(startDirect,startLineHeadType,startPos.rx(),startPos.ry(),p,linePath,*graphPath);
            linePath.moveTo(sx,sy);

            switch(endDirect)
            {
                case ORIENTION::NORTH:{
                    ex = endPos.rx();
                    ey = endPos.ry() - extendWidth;
                    if(sy>ey)
                    {
                        if(sx>ex)
                        {
                            linePath.lineTo(sx,ey);
                            linePath.lineTo(ex,ey);
                            linePath.lineTo(endPos.rx(),endPos.ry());
                            graphPath->addRect(sx - containsWidth1_2,sy,containsWidth,ey - sy);
                            graphPath->addRect(sx,ey - containsWidth1_2,ex - sx,containsWidth);
                            chartText.textType1->setGeometry((width()>>1) - (chartText.textType1->width()>>1),ey - (chartText.textType1->height()>>1),chartText.textType1->width(),chartText.textType1->height());
                        }else{
                            midx = (sx + ex)>>1;
                            linePath.lineTo(midx,sy);
                            linePath.lineTo(midx,ey);
                            linePath.lineTo(ex,ey);
                            linePath.lineTo(endPos.rx(),endPos.ry());
                            graphPath->addRect(sx,sy-containsWidth1_2,midx-sx,containsWidth);
                            graphPath->addRect(midx-containsWidth1_2,sy,containsWidth,ey-sy);
                            graphPath->addRect(midx,ey-containsWidth1_2,ex-midx,containsWidth);
                            chartText.textType1->setGeometry(midx - (chartText.textType1->width()>>1),(height()>>1) - (chartText.textType1->height()>>1),chartText.textType1->width(),chartText.textType1->height());
                        }
                    }else{
                        if(sx>ex)
                        {
                            midy = (sy + ey)>>1;
                            linePath.lineTo(sx,midy);
                            linePath.lineTo(ex,midy);
                            linePath.lineTo(ex,ey);
                            graphPath->addRect(sx - containsWidth1_2,sy,containsWidth,midy - sy);
                            graphPath->addRect(sx,midy - containsWidth1_2,ex-sx,containsWidth);
                            graphPath->addRect(ex - containsWidth1_2,midy,containsWidth,ey-midy);
                            chartText.textType1->setGeometry((width()>>1) - (chartText.textType1->width()>>1),midy - (chartText.textType1->height()>>1),chartText.textType1->width(),chartText.textType1->height());
                        }else{
                            linePath.lineTo(ex,sy);
                            linePath.lineTo(ex,ey);
                            graphPath->addRect(sx,sy-containsWidth1_2,ex-sx,containsWidth);
                            graphPath->addRect(ex-containsWidth1_2,sy,containsWidth,ey-sy);
                            chartText.textType1->setGeometry((width()>>1) - (chartText.textType1->width()>>1),sy - (chartText.textType1->height()>>1),chartText.textType1->width(),chartText.textType1->height());
                        }
                    }
                    drawLineHead(endDirect,endLineHeadType,endPos.rx(),endPos.ry(),p,linePath,*graphPath);
                }break;
                case ORIENTION::EAST:{
                    ex = endPos.rx() + extendWidth;
                    ey = endPos.ry();
                    if(sx>ex)
                    {
                        linePath.lineTo(sx,ey);
                        linePath.lineTo(ex,ey);
                        graphPath->addRect(sx - containsWidth1_2,sy,containsWidth,ey - sy);
                        graphPath->addRect(sx,ey - containsWidth1_2,ex - sx, containsWidth);
                        chartText.textType1->setGeometry(sx - (chartText.textType1->width()>>1),(height()>>1) - (chartText.textType1->height()>>1),chartText.textType1->width(),chartText.textType1->height());
                    }else{
                        linePath.lineTo(ex,sy);
                        linePath.lineTo(ex,ey);
                        graphPath->addRect(sx,sy-containsWidth1_2,ex-sx,containsWidth);
                        graphPath->addRect(ex-containsWidth1_2,sy,containsWidth,ey-sy);
                        chartText.textType1->setGeometry(ex - (chartText.textType1->width()>>1),(height()>>1) - (chartText.textType1->height()>>1),chartText.textType1->width(),chartText.textType1->height());
                    }
                    drawLineHead(endDirect,endLineHeadType,endPos.rx(),endPos.ry(),p,linePath,*graphPath);

                }break;
                case ORIENTION::SOUTH:{
                    ex = endPos.rx();
                    ey = endPos.ry() + extendWidth;
                    if(sy>ey)
                    {
                        if(sx>ex)
                        {
                            midy = (sy+ey)>>1;
                            linePath.lineTo(sx,midy);
                            linePath.lineTo(ex,midy);
                            linePath.lineTo(ex,ey);
                            graphPath->addRect(sx - containsWidth1_2,sy,containsWidth,midy - sy);
                            graphPath->addRect(sx,midy-containsWidth1_2,ex-sx,containsWidth);
                            graphPath->addRect(ex - containsWidth1_2,midy,containsWidth,ey-midy);
                            chartText.textType1->setGeometry((width()>>1) - (chartText.textType1->width()>>1),midy - (chartText.textType1->height()>>1),chartText.textType1->width(),chartText.textType1->height());
                        }else{
                            linePath.lineTo(ex,sy);
                            linePath.lineTo(ex,ey);
                            graphPath->addRect(sx,sy + containsWidth1_2,ex - sx,-containsWidth);
                            graphPath->addRect(ex - containsWidth1_2,sy,containsWidth,ey - sy);
                            chartText.textType1->setGeometry((width()>>1) - (chartText.textType1->width()>>1),ey - (chartText.textType1->height()>>1),chartText.textType1->width(),chartText.textType1->height());
                        }
                    }else{
                        if(sx>ex)
                        {
                            linePath.lineTo(sx,ey);
                            linePath.lineTo(ex,ey);
                            graphPath->addRect(sx - containsWidth1_2,sy,containsWidth,ey - sy);
                            graphPath->addRect(sx,ey - containsWidth1_2,ex - sx, containsWidth);
                            chartText.textType1->setGeometry((width()>>1) - (chartText.textType1->width()>>1),ey - (chartText.textType1->height()>>1),chartText.textType1->width(),chartText.textType1->height());
                        }else{
                            midx = (sx + ex)>>1;
                            linePath.lineTo(midx,sy);
                            linePath.lineTo(midx,ey);
                            linePath.lineTo(ex,ey);
                            graphPath->addRect(sx,sy-containsWidth1_2,midx-sx,containsWidth);
                            graphPath->addRect(midx-containsWidth1_2,sy,containsWidth,ey-sy);
                            graphPath->addRect(midx,ey-containsWidth1_2,ex-midx,containsWidth);
                            chartText.textType1->setGeometry(midx - (chartText.textType1->width()>>1),(height()>>1) - (chartText.textType1->height()>>1),chartText.textType1->width(),chartText.textType1->height());
                        }
                    }
                    drawLineHead(endDirect,endLineHeadType,endPos.rx(),endPos.ry(),p,linePath,*graphPath);
                }break;
                case ORIENTION::WEST:{
                    ex = endPos.rx() - extendWidth;
                    ey = endPos.ry();
                    if(sx>ex)
                    {
                        midy = (sy + ey)>>1;
                        linePath.lineTo(sx,midy);
                        linePath.lineTo(ex,midy);
                        linePath.lineTo(ex,ey);
                        graphPath->addRect(sx - containsWidth1_2,sy,containsWidth,midy - sy);
                        graphPath->addRect(sx,midy-containsWidth1_2,ex-sx,containsWidth);
                        graphPath->addRect(ex - containsWidth1_2,midy,containsWidth,ey-midy);
                        chartText.textType1->setGeometry((width()>>1) - (chartText.textType1->width()>>1),midy - (chartText.textType1->height()>>1),chartText.textType1->width(),chartText.textType1->height());
                    }else{
                        midx = (sx + ex)>>1;
                        linePath.lineTo(midx,sy);
                        linePath.lineTo(midx,ey);
                        linePath.lineTo(ex,ey);
                        graphPath->addRect(sx,sy - containsWidth1_2,midx - sx,containsWidth);
                        graphPath->addRect(midx - containsWidth1_2,sy,containsWidth,ey - sy);
                        graphPath->addRect(midx,ey - containsWidth1_2,ex - midx,containsWidth);
                        chartText.textType1->setGeometry(midx - (chartText.textType1->width()>>1),(height()>>1) - (chartText.textType1->height()>>1),chartText.textType1->width(),chartText.textType1->height());
                    }
                    drawLineHead(endDirect,endLineHeadType,endPos.rx(),endPos.ry(),p,linePath,*graphPath);
                }break;
                case ORIENTION::ENDPOINT:{
                    drawStraightLine(sx,sy,endPos.rx(),endPos.ry(),linePath,*graphPath);
                }break;
                case ORIENTION::NORTHEAST:
                {
                    drawStraightLine(sx,sy,endPos.rx() + extendWidth45,endPos.ry() - extendWidth45,linePath,*graphPath);
                    drawLineHead(endDirect,endLineHeadType,endPos.rx(),endPos.ry(),p,linePath,*graphPath);
                }break;
                case ORIENTION::NORTHWEST:
                {
                    drawStraightLine(sx,sy,endPos.rx() - extendWidth45,endPos.ry() - extendWidth45,linePath,*graphPath);
                    drawLineHead(endDirect,endLineHeadType,endPos.rx(),endPos.ry(),p,linePath,*graphPath);
                }break;
                case ORIENTION::SOUTHEAST:{
                    drawStraightLine(sx,sy,endPos.rx() + extendWidth45,endPos.ry() + extendWidth45,linePath,*graphPath);
                    drawLineHead(endDirect,endLineHeadType,endPos.rx(),endPos.ry(),p,linePath,*graphPath);
                }break;
                case ORIENTION::SOUTHWEST:
                {
                    drawStraightLine(sx,sy,endPos.rx() - extendWidth45,endPos.ry() + extendWidth45,linePath,*graphPath);
                    drawLineHead(endDirect,endLineHeadType,endPos.rx(),endPos.ry(),p,linePath,*graphPath);
                }break;
                default:
                {
                }
            }
            //linePath.lineTo(endPos.rx(),endPos.ry());
        }break;
        case ORIENTION::SOUTH:
        {
            sx = startPos.rx();
            sy = startPos.ry() + extendWidth;
            drawLineHead(startDirect,startLineHeadType,startPos.rx(),startPos.ry(),p,linePath,*graphPath);
            linePath.moveTo(sx,sy);
            switch(endDirect)
            {
                case ORIENTION::NORTH:{
                    ex = endPos.rx();
                    ey = endPos.ry() - extendWidth;
                    if(sy>ey)
                    {
                        midx = (sx+ex)>>1;
                        linePath.lineTo(midx,sy);
                        linePath.lineTo(midx,ey);
                        linePath.lineTo(ex,ey);
                        graphPath->addRect(sx,sy - containsWidth1_2,midx - sx,containsWidth);
                        graphPath->addRect(midx - containsWidth1_2,sy,containsWidth,ey - sy);
                        graphPath->addRect(midx,ey - containsWidth1_2,ex - midx,containsWidth);
                        chartText.textType1->setGeometry(midx - (chartText.textType1->width()>>1),(height()>>1) - (chartText.textType1->height()>>1),chartText.textType1->width(),chartText.textType1->height());
                    }else{
                        midy = (sy+ey)>>1;
                        linePath.lineTo(sx,midy);
                        linePath.lineTo(ex,midy);
                        linePath.lineTo(ex,ey);
                        graphPath->addRect(sx - containsWidth1_2,sy,containsWidth,midy - sy);
                        graphPath->addRect(sx,midy-containsWidth1_2,ex-sx,containsWidth);
                        graphPath->addRect(ex - containsWidth1_2,midy,containsWidth,ey-midy);
                        chartText.textType1->setGeometry((width()>>1) - (chartText.textType1->width()>>1),midy - (chartText.textType1->height()>>1),chartText.textType1->width(),chartText.textType1->height());
                    }
                    drawLineHead(endDirect,endLineHeadType,endPos.rx(),endPos.ry(),p,linePath,*graphPath);
                }break;
                case ORIENTION::EAST:{
                    ex = endPos.rx() + extendWidth;
                    ey = endPos.ry();
                    if(sy>ey)
                    {
                        if(sx>ex)
                        {
                            midx = (sx+ex)>>1;
                            linePath.lineTo(midx,sy);
                            linePath.lineTo(midx,ey);
                            linePath.lineTo(ex,ey);
                            graphPath->addRect(sx,sy-containsWidth1_2,midx-sx,containsWidth);
                            graphPath->addRect(midx-containsWidth1_2,sy,containsWidth,ey-sy);
                            graphPath->addRect(midx,ey-containsWidth1_2,ex-midx,containsWidth);
                            chartText.textType1->setGeometry(midx - (chartText.textType1->width()>>1),(height()>>1) - (chartText.textType1->height()>>1),chartText.textType1->width(),chartText.textType1->height());
                        }else{
                            linePath.lineTo(ex,sy);
                            linePath.lineTo(ex,ey);
                            graphPath->addRect(sx,sy + containsWidth1_2,ex - sx,-containsWidth);
                            graphPath->addRect(ex - containsWidth1_2,sy,containsWidth,ey - sy);
                            chartText.textType1->setGeometry((width()>>1) - (chartText.textType1->width()>>1),sy - (chartText.textType1->height()>>1),chartText.textType1->width(),chartText.textType1->height());
                        }

                    }else{
                        if(sx>ex){
                            linePath.lineTo(sx,ey);
                            linePath.lineTo(ex,ey);
                            graphPath->addRect(sx - containsWidth1_2,sy,containsWidth,ey - sy);
                            graphPath->addRect(sx,ey - containsWidth1_2,ex - sx, containsWidth);
                            chartText.textType1->setGeometry((width()>>1) - (chartText.textType1->width()>>1),ey - (chartText.textType1->height()>>1),chartText.textType1->width(),chartText.textType1->height());
                        }else{
                            midy = (sy+ey)>>1;
                            linePath.lineTo(sx,midy);
                            linePath.lineTo(ex,midy);
                            linePath.lineTo(ex,ey);
                            graphPath->addRect(sx - containsWidth1_2,sy,containsWidth,midy - sy);
                            graphPath->addRect(sx,midy-containsWidth1_2,ex-sx,containsWidth);
                            graphPath->addRect(ex - containsWidth1_2,midy,containsWidth,ey-midy);
                            chartText.textType1->setGeometry((width()>>1) - (chartText.textType1->width()>>1),midy - (chartText.textType1->height()>>1),chartText.textType1->width(),chartText.textType1->height());
                        }
                    }
                    drawLineHead(endDirect,endLineHeadType,endPos.rx(),endPos.ry(),p,linePath,*graphPath);
                }break;
                case ORIENTION::SOUTH:{
                    ex = endPos.rx();
                    ey = endPos.ry() + extendWidth;
                    if(sy>ey)
                    {
                        linePath.lineTo(ex,sy);
                        linePath.lineTo(ex,ey);
                        graphPath->addRect(sx,sy-containsWidth1_2,ex-sx,containsWidth);
                        graphPath->addRect(ex-containsWidth1_2,sy,containsWidth,ey-sy);
                        chartText.textType1->setGeometry((width()>>1) - (chartText.textType1->width()>>1),sy - (chartText.textType1->height()>>1),chartText.textType1->width(),chartText.textType1->height());
                    }else{
                        linePath.lineTo(sx,ey);
                        linePath.lineTo(ex,ey);
                        graphPath->addRect(sx - containsWidth1_2,sy,containsWidth,ey - sy);
                        graphPath->addRect(sx,ey - containsWidth1_2,ex - sx, containsWidth);
                        chartText.textType1->setGeometry((width()>>1) - (chartText.textType1->width()>>1),ey - (chartText.textType1->height()>>1),chartText.textType1->width(),chartText.textType1->height());
                    }
                    drawLineHead(endDirect,endLineHeadType,endPos.rx(),endPos.ry(),p,linePath,*graphPath);
                }break;
                case ORIENTION::WEST:{
                    ex = endPos.rx() - extendWidth;
                    ey = endPos.ry();
                    if(sy>ey)
                    {
                        if(sx>ex)
                        {
                            linePath.lineTo(ex,sy);
                            linePath.lineTo(ex,ey);
                            graphPath->addRect(sx,sy-containsWidth1_2,ex-sx,containsWidth);
                            graphPath->addRect(ex-containsWidth1_2,sy,containsWidth,ey-sy);
                            chartText.textType1->setGeometry((width()>>1) - (chartText.textType1->width()>>1),sy - (chartText.textType1->height()>>1),chartText.textType1->width(),chartText.textType1->height());
                        }else{
                            midx = (sx+ex)>>1;
                            linePath.lineTo(midx,sy);
                            linePath.lineTo(midx,ey);
                            linePath.lineTo(ex,ey);
                            graphPath->addRect(sx,sy-containsWidth1_2,midx-sx,containsWidth);
                            graphPath->addRect(midx-containsWidth1_2,sy,containsWidth,ey-sy);
                            graphPath->addRect(midx,ey-containsWidth1_2,ex-midx,containsWidth);
                            chartText.textType1->setGeometry(midx - (chartText.textType1->width()>>1),(height()>>1) - (chartText.textType1->height()>>1),chartText.textType1->width(),chartText.textType1->height());
                        }
                    }else{
                        if(sx>ex)
                        {
                            midy = (sy+ey)>>1;
                            linePath.lineTo(sx,midy);
                            linePath.lineTo(ex,midy);
                            linePath.lineTo(ex,ey);
                            graphPath->addRect(sx - containsWidth1_2,sy,containsWidth,midy - sy);
                            graphPath->addRect(sx,midy - containsWidth1_2,ex-sx,containsWidth);
                            graphPath->addRect(ex - containsWidth1_2,midy,containsWidth,ey-midy);
                            chartText.textType1->setGeometry((width()>>1) - (chartText.textType1->width()>>1),midy - (chartText.textType1->height()>>1),chartText.textType1->width(),chartText.textType1->height());
                        }else{
                            linePath.lineTo(sx,ey);
                            linePath.lineTo(ex,ey);
                            graphPath->addRect(sx - containsWidth1_2,sy,containsWidth,ey - sy);
                            graphPath->addRect(sx,ey - containsWidth1_2,ex - sx,containsWidth);
                            chartText.textType1->setGeometry((width()>>1) - (chartText.textType1->width()>>1),ey - (chartText.textType1->height()>>1),chartText.textType1->width(),chartText.textType1->height());
                        }
                    }
                    drawLineHead(endDirect,endLineHeadType,endPos.rx(),endPos.ry(),p,linePath,*graphPath);
                }break;
                case ORIENTION::ENDPOINT:{
                    drawStraightLine(sx,sy,endPos.rx(),endPos.ry(),linePath,*graphPath);
                }break;
                case ORIENTION::NORTHEAST:
                {
                    drawStraightLine(sx,sy,endPos.rx() + extendWidth45,endPos.ry() - extendWidth45,linePath,*graphPath);
                    drawLineHead(endDirect,endLineHeadType,endPos.rx(),endPos.ry(),p,linePath,*graphPath);
                }break;
                case ORIENTION::NORTHWEST:
                {
                    drawStraightLine(sx,sy,endPos.rx() - extendWidth45,endPos.ry() - extendWidth45,linePath,*graphPath);
                    drawLineHead(endDirect,endLineHeadType,endPos.rx(),endPos.ry(),p,linePath,*graphPath);
                }break;
                case ORIENTION::SOUTHEAST:{
                    drawStraightLine(sx,sy,endPos.rx() + extendWidth45,endPos.ry() + extendWidth45,linePath,*graphPath);
                    drawLineHead(endDirect,endLineHeadType,endPos.rx(),endPos.ry(),p,linePath,*graphPath);
                }break;
                case ORIENTION::SOUTHWEST:
                {
                    drawStraightLine(sx,sy,endPos.rx() - extendWidth45,endPos.ry() + extendWidth45,linePath,*graphPath);
                    drawLineHead(endDirect,endLineHeadType,endPos.rx(),endPos.ry(),p,linePath,*graphPath);
                }break;
                default:
                {
                }
            }
            //linePath.lineTo(endPos.rx(),endPos.ry());
        }break;
        case ORIENTION::WEST:
        {
            sx = startPos.rx() - extendWidth;
            sy = startPos.ry();
            drawLineHead(startDirect,startLineHeadType,startPos.rx(),startPos.ry(),p,linePath,*graphPath);
            linePath.moveTo(sx,sy);
            switch(endDirect)
            {
                case ORIENTION::NORTH:{
                    ex = endPos.rx();
                    ey = endPos.ry() - extendWidth;
                    if(sy>ey)
                    {
                        if(sx>ex)
                        {
                            midx = (sx+ex)>>1;
                            linePath.lineTo(midx,sy);
                            linePath.lineTo(midx,ey);
                            linePath.lineTo(ex,ey);
                            graphPath->addRect(sx,sy-containsWidth1_2,midx-sx,containsWidth);
                            graphPath->addRect(midx-containsWidth1_2,sy,containsWidth,ey-sy);
                            graphPath->addRect(midx,ey-containsWidth1_2,ex-midx,containsWidth);
                            chartText.textType1->setGeometry(midx - (chartText.textType1->width()>>1),(height()>>1) - (chartText.textType1->height()>>1),chartText.textType1->width(),chartText.textType1->height());
                        }else{
                            linePath.lineTo(sx,ey);
                            linePath.lineTo(ex,ey);
                            graphPath->addRect(sx - containsWidth1_2,sy,containsWidth,ey - sy);
                            graphPath->addRect(sx,ey - containsWidth1_2,ex - sx,containsWidth);
                            chartText.textType1->setGeometry((width()>>1) - (chartText.textType1->width()>>1),ey - (chartText.textType1->height()>>1),chartText.textType1->width(),chartText.textType1->height());
                        }
                    }else{
                        if(sx>ex)
                        {
                            linePath.lineTo(ex,sy);
                            linePath.lineTo(ex,ey);
                            graphPath->addRect(sx - containsWidth1_2,sy,containsWidth,ey - sy);
                            graphPath->addRect(sx,ey - containsWidth1_2,ex - sx, containsWidth);
                            chartText.textType1->setGeometry((width()>>1) - (chartText.textType1->width()>>1),sy - (chartText.textType1->height()>>1),chartText.textType1->width(),chartText.textType1->height());
                        }else{
                            midy = (sy+ey)>>1;
                            linePath.lineTo(sx,midy);
                            linePath.lineTo(ex,midy);
                            linePath.lineTo(ex,ey);
                            graphPath->addRect(sx - containsWidth1_2,sy,containsWidth,midy - sy);
                            graphPath->addRect(sx,midy-containsWidth1_2,ex-sx,containsWidth);
                            graphPath->addRect(ex - containsWidth1_2,midy,containsWidth,ey-midy);
                            chartText.textType1->setGeometry((width()>>1) - (chartText.textType1->width()>>1),midy - (chartText.textType1->height()>>1),chartText.textType1->width(),chartText.textType1->height());
                        }
                    }
                    drawLineHead(endDirect,endLineHeadType,endPos.rx(),endPos.ry(),p,linePath,*graphPath);
                }break;
                case ORIENTION::EAST:{
                    ex = endPos.rx() + extendWidth;
                    ey = endPos.ry();
                    if(sx>ex)
                    {
                        midx = (sx+ex)>>1;
                        linePath.lineTo(midx,sy);
                        linePath.lineTo(midx,ey);
                        linePath.lineTo(ex,ey);
                        graphPath->addRect(sx,sy - containsWidth1_2,midx - sx,containsWidth);
                        graphPath->addRect(midx - containsWidth1_2,sy,containsWidth,ey - sy);
                        graphPath->addRect(midx,ey - containsWidth1_2,ex - midx,containsWidth);
                        chartText.textType1->setGeometry(midx - (chartText.textType1->width()>>1),(height()>>1) - (chartText.textType1->height()>>1),chartText.textType1->width(),chartText.textType1->height());
                    }else{
                        midy = (sy+ey)>>1;
                        linePath.lineTo(sx,midy);
                        linePath.lineTo(ex,midy);
                        linePath.lineTo(ex,ey);
                        graphPath->addRect(sx - containsWidth1_2,sy,containsWidth,midy - sy);
                        graphPath->addRect(sx,midy-containsWidth1_2,ex-sx,containsWidth);
                        graphPath->addRect(ex - containsWidth1_2,midy,containsWidth,ey-midy);
                        chartText.textType1->setGeometry((width()>>1) - (chartText.textType1->width()>>1),midy - (chartText.textType1->height()>>1),chartText.textType1->width(),chartText.textType1->height());
                    }
                    drawLineHead(endDirect,endLineHeadType,endPos.rx(),endPos.ry(),p,linePath,*graphPath);
                }break;
                case ORIENTION::SOUTH:{
                    ex = endPos.rx();
                    ey = endPos.ry() + extendWidth;
                    if(sy>ey)
                    {
                        if(sx>ex)
                        {
                            linePath.lineTo(ex,sy);
                            linePath.lineTo(ex,ey);
                            graphPath->addRect(sx,sy-containsWidth1_2,ex-sx,containsWidth);
                            graphPath->addRect(ex-containsWidth1_2,sy,containsWidth,ey-sy);
                            chartText.textType1->setGeometry((width()>>1) - (chartText.textType1->width()>>1),sy - (chartText.textType1->height()>>1),chartText.textType1->width(),chartText.textType1->height());
                        }else{
                            midy = (sy+ey)>>1;
                            linePath.lineTo(sx,midy);
                            linePath.lineTo(ex,midy);
                            linePath.lineTo(ex,ey);
                            graphPath->addRect(sx - containsWidth1_2,sy,containsWidth,midy - sy);
                            graphPath->addRect(sx,midy - containsWidth1_2,ex-sx,containsWidth);
                            graphPath->addRect(ex - containsWidth1_2,midy,containsWidth,ey-midy);
                            chartText.textType1->setGeometry((width()>>1) - (chartText.textType1->width()>>1),midy - (chartText.textType1->height()>>1),chartText.textType1->width(),chartText.textType1->height());
                        }
                    }else{
                        if(sx>ex)
                        {
                            midx = (sx+ex)>>1;
                            linePath.lineTo(midx,sy);
                            linePath.lineTo(midx,ey);
                            linePath.lineTo(ex,ey);
                            graphPath->addRect(sx,sy-containsWidth1_2,midx-sx,containsWidth);
                            graphPath->addRect(midx-containsWidth1_2,sy,containsWidth,ey-sy);
                            graphPath->addRect(midx,ey-containsWidth1_2,ex-midx,containsWidth);
                            chartText.textType1->setGeometry(midx - (chartText.textType1->width()>>1),(height()>>1) - (chartText.textType1->height()>>1),chartText.textType1->width(),chartText.textType1->height());
                        }else{
                            linePath.lineTo(sx,ey);
                            linePath.lineTo(ex,ey);
                            graphPath->addRect(sx - containsWidth1_2,sy,containsWidth,ey - sy);
                            graphPath->addRect(sx,ey - containsWidth1_2,ex - sx,containsWidth);
                            chartText.textType1->setGeometry((width()>>1) - (chartText.textType1->width()>>1),ey - (chartText.textType1->height()>>1),chartText.textType1->width(),chartText.textType1->height());
                        }
                    }
                    drawLineHead(endDirect,endLineHeadType,endPos.rx(),endPos.ry(),p,linePath,*graphPath);
                }break;
                case ORIENTION::WEST:{
                    ex = endPos.rx() - extendWidth;
                    ey = endPos.ry();
                    if(sx>ex)
                    {
                        linePath.lineTo(ex,sy);
                        linePath.lineTo(ex,ey);
                        graphPath->addRect(sx,sy-containsWidth1_2,ex-sx,containsWidth);
                        graphPath->addRect(ex-containsWidth1_2,sy,containsWidth,ey-sy);
                        chartText.textType1->setGeometry(ex - (chartText.textType1->width()>>1),(height()>>1) - (chartText.textType1->height()>>1),chartText.textType1->width(),chartText.textType1->height());
                    }else{
                        linePath.lineTo(sx,ey);
                        linePath.lineTo(ex,ey);
                        graphPath->addRect(sx - containsWidth1_2,sy,containsWidth,ey - sy);
                        graphPath->addRect(sx,ey - containsWidth1_2,ex - sx, containsWidth);
                        chartText.textType1->setGeometry(sx - (chartText.textType1->width()>>1),(height()>>1) - (chartText.textType1->height()>>1),chartText.textType1->width(),chartText.textType1->height());
                    }
                    drawLineHead(endDirect,endLineHeadType,endPos.rx(),endPos.ry(),p,linePath,*graphPath);
                }break;
                case ORIENTION::ENDPOINT:{
                    drawStraightLine(sx,sy,endPos.rx(),endPos.ry(),linePath,*graphPath);
                }break;
                case ORIENTION::NORTHEAST:
                {
                    drawStraightLine(sx,sy,endPos.rx() + extendWidth45,endPos.ry() - extendWidth45,linePath,*graphPath);
                    drawLineHead(endDirect,endLineHeadType,endPos.rx(),endPos.ry(),p,linePath,*graphPath);
                }break;
                case ORIENTION::NORTHWEST:
                {
                    drawStraightLine(sx,sy,endPos.rx() - extendWidth45,endPos.ry() - extendWidth45,linePath,*graphPath);
                    drawLineHead(endDirect,endLineHeadType,endPos.rx(),endPos.ry(),p,linePath,*graphPath);
                }break;
                case ORIENTION::SOUTHEAST:{
                    drawStraightLine(sx,sy,endPos.rx() + extendWidth45,endPos.ry() + extendWidth45,linePath,*graphPath);
                    drawLineHead(endDirect,endLineHeadType,endPos.rx(),endPos.ry(),p,linePath,*graphPath);
                }break;
                case ORIENTION::SOUTHWEST:
                {
                    drawStraightLine(sx,sy,endPos.rx() - extendWidth45,endPos.ry() + extendWidth45,linePath,*graphPath);
                    drawLineHead(endDirect,endLineHeadType,endPos.rx(),endPos.ry(),p,linePath,*graphPath);
                }break;
                default:
                {

                }
            }
        }break;
        case ORIENTION::STARTPOINT:{
            sx = startPos.rx();
            sy = startPos.ry();
            ex = endPos.rx();
            ey = endPos.ry();
            switch(endDirect)
            {
                case ORIENTION::NORTH:{
                    drawStraightLine(sx,sy,ex,ey - extendWidth,linePath,*graphPath);
                    drawLineHead(endDirect,endLineHeadType,endPos.rx(),endPos.ry(),p,linePath,*graphPath);
                }break;
                case ORIENTION::EAST:{
                    drawStraightLine(sx,sy,ex + extendWidth,ey,linePath,*graphPath);
                    drawLineHead(endDirect,endLineHeadType,endPos.rx(),endPos.ry(),p,linePath,*graphPath);
                }break;
                case ORIENTION::SOUTH:{
                    drawStraightLine(sx,sy,ex,ey + extendWidth,linePath,*graphPath);
                    drawLineHead(endDirect,endLineHeadType,endPos.rx(),endPos.ry(),p,linePath,*graphPath);
                }break;
                case ORIENTION::WEST:{
                    drawStraightLine(sx,sy,ex - extendWidth,ey,linePath,*graphPath);
                    drawLineHead(endDirect,endLineHeadType,endPos.rx(),endPos.ry(),p,linePath,*graphPath);
                }break;
                case ORIENTION::ENDPOINT:{
                    drawStraightLine(sx,sy,ex,ey,linePath,*graphPath);
                }break;
                case ORIENTION::NORTHEAST:
                {
                    drawStraightLine(sx,sy,endPos.rx() + extendWidth45,endPos.ry() - extendWidth45,linePath,*graphPath);
                    drawLineHead(endDirect,endLineHeadType,endPos.rx(),endPos.ry(),p,linePath,*graphPath);
                }break;
                case ORIENTION::NORTHWEST:
                {
                    drawStraightLine(sx,sy,endPos.rx() - extendWidth45,endPos.ry() - extendWidth45,linePath,*graphPath);
                    drawLineHead(endDirect,endLineHeadType,endPos.rx(),endPos.ry(),p,linePath,*graphPath);
                }break;
                case ORIENTION::SOUTHEAST:{
                    drawStraightLine(sx,sy,endPos.rx() + extendWidth45,endPos.ry() + extendWidth45,linePath,*graphPath);
                    drawLineHead(endDirect,endLineHeadType,endPos.rx(),endPos.ry(),p,linePath,*graphPath);
                }break;
                case ORIENTION::SOUTHWEST:
                {
                    drawStraightLine(sx,sy,endPos.rx() - extendWidth45,endPos.ry() + extendWidth45,linePath,*graphPath);
                    drawLineHead(endDirect,endLineHeadType,endPos.rx(),endPos.ry(),p,linePath,*graphPath);
                }break;
            };
        }break;
        case ORIENTION::NORTHEAST:{
            sx = startPos.rx() + extendWidth45;
            sy = startPos.ry() - extendWidth45;
            ex = endPos.rx();
            ey = endPos.ry();
            drawLineHead(startDirect,startLineHeadType,startPos.rx(),startPos.ry(),p,linePath,*graphPath);
            linePath.moveTo(sx,sy);
            switch(endDirect)
            {
                case ORIENTION::NORTH:{
                    drawStraightLine(sx,sy,ex,ey - extendWidth,linePath,*graphPath);
                    drawLineHead(endDirect,endLineHeadType,ex,ey,p,linePath,*graphPath);
                }break;
                case ORIENTION::EAST:{
                    drawStraightLine(sx,sy,ex + extendWidth,ey,linePath,*graphPath);
                    drawLineHead(endDirect,endLineHeadType,ex,ey,p,linePath,*graphPath);
                }break;
                case ORIENTION::SOUTH:{
                    drawStraightLine(sx,sy,ex,ey + extendWidth,linePath,*graphPath);
                    drawLineHead(endDirect,endLineHeadType,ex,ey,p,linePath,*graphPath);
                }break;
                case ORIENTION::WEST:{
                    drawStraightLine(sx,sy,ex - extendWidth,ey,linePath,*graphPath);
                    drawLineHead(endDirect,endLineHeadType,ex,ey,p,linePath,*graphPath);
                }break;
                case ORIENTION::ENDPOINT:{
                    drawStraightLine(sx,sy,ex,ey,linePath,*graphPath);
                }break;
                case ORIENTION::NORTHEAST:
                {
                    drawStraightLine(sx,sy,ex + extendWidth45,ey - extendWidth45,linePath,*graphPath);
                    drawLineHead(endDirect,endLineHeadType,ex,ey,p,linePath,*graphPath);
                }break;
                case ORIENTION::NORTHWEST:
                {
                    drawStraightLine(sx,sy,ex - extendWidth45,ey - extendWidth45,linePath,*graphPath);
                    drawLineHead(endDirect,endLineHeadType,ex,ey,p,linePath,*graphPath);
                }break;
                case ORIENTION::SOUTHEAST:{
                    drawStraightLine(sx,sy,ex + extendWidth45,ey + extendWidth45,linePath,*graphPath);
                    drawLineHead(endDirect,endLineHeadType,ex,ey,p,linePath,*graphPath);
                }break;
                case ORIENTION::SOUTHWEST:
                {
                    drawStraightLine(sx,sy,ex - extendWidth45,ey + extendWidth45,linePath,*graphPath);
                    drawLineHead(endDirect,endLineHeadType,ex,ey,p,linePath,*graphPath);
                }break;
            };
        }break;
        case ORIENTION::NORTHWEST:{
            sx = startPos.rx() - extendWidth45;
            sy = startPos.ry() - extendWidth45;
            ex = endPos.rx();
            ey = endPos.ry();
            drawLineHead(startDirect,startLineHeadType,startPos.rx(),startPos.ry(),p,linePath,*graphPath);
            switch(endDirect)
            {
                case ORIENTION::NORTH:
                {
                    drawStraightLine(sx,sy,ex,ey - extendWidth,linePath,*graphPath);
                    drawLineHead(endDirect,endLineHeadType,ex,ey,p,linePath,*graphPath);
                }break;
                case ORIENTION::EAST:
                {
                    drawStraightLine(sx,sy,ex + extendWidth,ey,linePath,*graphPath);
                    drawLineHead(endDirect,endLineHeadType,ex,ey,p,linePath,*graphPath);
                }break;
                case ORIENTION::SOUTH:
                {
                    drawStraightLine(sx,sy,ex,ey + extendWidth,linePath,*graphPath);
                    drawLineHead(endDirect,endLineHeadType,ex,ey,p,linePath,*graphPath);
                }break;
                case ORIENTION::WEST:
                {
                    drawStraightLine(sx,sy,ex - extendWidth,ey,linePath,*graphPath);
                    drawLineHead(endDirect,endLineHeadType,ex,ey,p,linePath,*graphPath);
                }break;
                case ORIENTION::ENDPOINT:
                {
                    drawStraightLine(sx,sy,ex,ey,linePath,*graphPath);
                }break;
                case ORIENTION::NORTHEAST:
                {
                    drawStraightLine(sx,sy,ex + extendWidth45,ey - extendWidth45,linePath,*graphPath);
                    drawLineHead(endDirect,endLineHeadType,ex,ey,p,linePath,*graphPath);
                }break;
                case ORIENTION::NORTHWEST:
                {
                    drawStraightLine(sx,sy,ex - extendWidth45,ey - extendWidth45,linePath,*graphPath);
                    drawLineHead(endDirect,endLineHeadType,ex,ey,p,linePath,*graphPath);
                }break;
                case ORIENTION::SOUTHEAST:
                {
                    drawStraightLine(sx,sy,ex + extendWidth45,ey + extendWidth45,linePath,*graphPath);
                    drawLineHead(endDirect,endLineHeadType,ex,ey,p,linePath,*graphPath);
                }break;
                case ORIENTION::SOUTHWEST:
                {
                    drawStraightLine(sx,sy,ex - extendWidth45,ey + extendWidth45,linePath,*graphPath);
                    drawLineHead(endDirect,endLineHeadType,ex,ey,p,linePath,*graphPath);
                }break;
            };
        }break;
        case ORIENTION::SOUTHWEST:{
            sx = startPos.rx() - extendWidth45;
            sy = startPos.ry() + extendWidth45;
            ex = endPos.rx();
            ey = endPos.ry();
            drawLineHead(startDirect,startLineHeadType,startPos.rx(),startPos.ry(),p,linePath,*graphPath);
            switch(endDirect)
            {
                case ORIENTION::NORTH:
                {
                    drawStraightLine(sx,sy,ex,ey - extendWidth,linePath,*graphPath);
                    drawLineHead(endDirect,endLineHeadType,ex,ey,p,linePath,*graphPath);
                }break;
                case ORIENTION::EAST:
                {
                    drawStraightLine(sx,sy,ex + extendWidth,ey,linePath,*graphPath);
                    drawLineHead(endDirect,endLineHeadType,ex,ey,p,linePath,*graphPath);
                }break;
                case ORIENTION::SOUTH:
                {
                    drawStraightLine(sx,sy,ex,ey + extendWidth,linePath,*graphPath);
                    drawLineHead(endDirect,endLineHeadType,ex,ey,p,linePath,*graphPath);
                }break;
                case ORIENTION::WEST:
                {
                    drawStraightLine(sx,sy,ex - extendWidth,ey,linePath,*graphPath);
                    drawLineHead(endDirect,endLineHeadType,ex,ey,p,linePath,*graphPath);
                }break;
                case ORIENTION::ENDPOINT:
                {
                    drawStraightLine(sx,sy,ex,ey,linePath,*graphPath);
                }break;
                case ORIENTION::NORTHEAST:
                {
                    drawStraightLine(sx,sy,ex + extendWidth45,ey - extendWidth45,linePath,*graphPath);
                    drawLineHead(endDirect,endLineHeadType,ex,ey,p,linePath,*graphPath);
                }break;
                case ORIENTION::NORTHWEST:
                {
                    drawStraightLine(sx,sy,ex - extendWidth45,ey - extendWidth45,linePath,*graphPath);
                    drawLineHead(endDirect,endLineHeadType,ex,ey,p,linePath,*graphPath);
                }break;
                case ORIENTION::SOUTHEAST:
                {
                    drawStraightLine(sx,sy,ex + extendWidth45,ey + extendWidth45,linePath,*graphPath);
                    drawLineHead(endDirect,endLineHeadType,ex,ey,p,linePath,*graphPath);
                }break;
                case ORIENTION::SOUTHWEST:
                {
                    drawStraightLine(sx,sy,ex - extendWidth45,ey + extendWidth45,linePath,*graphPath);
                    drawLineHead(endDirect,endLineHeadType,ex,ey,p,linePath,*graphPath);
                }break;
            };
        }break;
        case ORIENTION::SOUTHEAST:{
            sx = startPos.rx() + extendWidth45;
            sy = startPos.ry() + extendWidth45;
            ex = endPos.rx();
            ey = endPos.ry();
            drawLineHead(startDirect,startLineHeadType,startPos.rx(),startPos.ry(),p,linePath,*graphPath);
            switch(endDirect)
            {
                case ORIENTION::NORTH:
                {
                    drawStraightLine(sx,sy,ex,ey - extendWidth,linePath,*graphPath);
                    drawLineHead(endDirect,endLineHeadType,ex,ey,p,linePath,*graphPath);
                }break;
                case ORIENTION::EAST:
                {
                    drawStraightLine(sx,sy,ex + extendWidth,ey,linePath,*graphPath);
                    drawLineHead(endDirect,endLineHeadType,ex,ey,p,linePath,*graphPath);
                }break;
                case ORIENTION::SOUTH:
                {
                    drawStraightLine(sx,sy,ex,ey + extendWidth,linePath,*graphPath);
                    drawLineHead(endDirect,endLineHeadType,ex,ey,p,linePath,*graphPath);
                }break;
                case ORIENTION::WEST:
                {
                    drawStraightLine(sx,sy,ex - extendWidth,ey,linePath,*graphPath);
                    drawLineHead(endDirect,endLineHeadType,ex,ey,p,linePath,*graphPath);
                }break;
                case ORIENTION::ENDPOINT:
                {
                    drawStraightLine(sx,sy,ex,ey,linePath,*graphPath);
                }break;
                case ORIENTION::NORTHEAST:
                {
                    drawStraightLine(sx,sy,ex + extendWidth45,ey - extendWidth45,linePath,*graphPath);
                    drawLineHead(endDirect,endLineHeadType,ex,ey,p,linePath,*graphPath);
                }break;
                case ORIENTION::NORTHWEST:
                {
                    drawStraightLine(sx,sy,ex - extendWidth45,ey - extendWidth45,linePath,*graphPath);
                    drawLineHead(endDirect,endLineHeadType,ex,ey,p,linePath,*graphPath);
                }break;
                case ORIENTION::SOUTHEAST:
                {
                    drawStraightLine(sx,sy,ex + extendWidth45,ey + extendWidth45,linePath,*graphPath);
                    drawLineHead(endDirect,endLineHeadType,ex,ey,p,linePath,*graphPath);
                }break;
                case ORIENTION::SOUTHWEST:
                {
                    drawStraightLine(sx,sy,ex - extendWidth45,ey + extendWidth45,linePath,*graphPath);
                    drawLineHead(endDirect,endLineHeadType,ex,ey,p,linePath,*graphPath);
                }break;
            };
        }break;
        default:{
        }
    }

#endif
//    linePath.lineTo(midx,startPos.ry());
//    linePath.lineTo(midx,endPos.ry());
//    linePath.lineTo(endPos.rx(),endPos.ry());


    p.drawPath(linePath);
//    graphPath->addRect(startPos.rx(),startPos.ry()-containsWidth1_2,midx-startPos.rx(),containsWidth);
//    graphPath->addRect(midx-containsWidth1_2,startPos.ry()-containsWidth1_2,containsWidth,endPos.ry()-startPos.ry()+containsWidth);
//    graphPath->addRect(midx-containsWidth1_2,endPos.ry()-containsWidth1_2,endPos.rx()-midx+containsWidth,containsWidth);
    p.setPen(QPen(QColor(0,0,0,0),0));
    graphPath->setFillRule(Qt::WindingFill);
    p.drawPath(*graphPath);
    //p.fillPath(*graphPath,QBrush(QColor(255,255,100,200)));

    p.setPen(tmp);
}

void Chart_Line::updateMagPointInfo()
{
//    magPoint.i_point[0]->setX(startPos.rx());
//    magPoint.i_point[0]->setY(startPos.ry());
//    magPoint.i_point[0]->setRotate(ORIENTION::STARTPOINT);
//    magPoint.i_point[1]->setX(endPos.rx());
//    magPoint.i_point[1]->setY(endPos.ry());
//    magPoint.i_point[1]->setRotate(ORIENTION::ENDPOINT);

}
void Chart_Line::updateSizePointInfo()
{
    if(widgetStart.rx() > widgetEnd.rx())
    {
        startPos.setX(paintEnd.rx());
        endPos.setX(paintStart.rx());
    }else
    {
        startPos.setX(paintStart.rx());
        endPos.setX(paintEnd.rx());
    }
    if(widgetStart.ry()>widgetEnd.ry())
    {
        startPos.setY(paintEnd.ry());
        endPos.setY(paintStart.ry());
    }
    else
    {
        startPos.setY(paintStart.ry());
        endPos.setY(paintEnd.ry());
    }

    sizePoint.i_point[0]->setX(startPos.rx());
    sizePoint.i_point[0]->setY(startPos.ry());
    sizePoint.i_point[0]->setRotate(ORIENTION::STARTPOINT);
    sizePoint.i_point[1]->setX(endPos.rx());
    sizePoint.i_point[1]->setY(endPos.ry());
    sizePoint.i_point[1]->setRotate(ORIENTION::ENDPOINT);
}
void Chart_Line::specialWidgetUpdate(int &x,int &y, int &w, int &h)
{
    x -= extendWidth;
    y -= extendWidth;
    w += extendWidth + extendWidth;
    h += extendWidth + extendWidth;
}
void Chart_Line::specialPaintUpdate(QPoint &s, QPoint &e)
{
    s.setX(s.rx() + extendWidth);
    s.setY(s.ry() + extendWidth);
    e.setX(e.rx() + extendWidth);
    e.setY(e.ry() + extendWidth);
}
QDataStream &operator<<(QDataStream &fout, const Chart_Line &cl)
{
    fout<<cl.startPos<<cl.endPos;
    fout.writeRawData(reinterpret_cast<const char*>(&cl.startDirect),sizeof(ORIENTION));
    fout.writeRawData(reinterpret_cast<const char*>(&cl.endDirect),sizeof(ORIENTION));
    fout.writeRawData(reinterpret_cast<const char*>(&cl.startMagIndex),sizeof(int));
    fout.writeRawData(reinterpret_cast<const char*>(&cl.endMagIndex),sizeof(int));
    fout.writeRawData(reinterpret_cast<const char*>(&cl.startLineHeadType),sizeof(LINE_HEAD_TYPE));
    fout.writeRawData(reinterpret_cast<const char*>(&cl.endLineHeadType),sizeof(LINE_HEAD_TYPE));
    if(cl.startChartMag)
        fout.writeRawData(reinterpret_cast<const char*>(&cl.startChartMag->getID()),sizeof(int));
    else{
        int i = -1;
        fout.writeRawData(reinterpret_cast<const char*>(&i),sizeof(int));
    }
    if(cl.endChartMag)
        fout.writeRawData(reinterpret_cast<const char*>(&cl.endChartMag->getID()),sizeof(int));
    else{
        int i = -1;
        fout.writeRawData(reinterpret_cast<const char*>(&i),sizeof(int));
    }

    return fout;
}
QDataStream &operator>>(QDataStream &fin, Chart_Line &cl)
{
    fin>>cl.startPos>>cl.endPos;
    fin.readRawData(reinterpret_cast<char*>(&cl.startDirect),sizeof(ORIENTION));
    fin.readRawData(reinterpret_cast<char*>(&cl.endDirect),sizeof(ORIENTION));
    fin.readRawData(reinterpret_cast<char*>(&cl.startMagIndex),sizeof(int));
    fin.readRawData(reinterpret_cast<char*>(&cl.endMagIndex),sizeof(int));
    fin.readRawData(reinterpret_cast<char*>(&cl.startLineHeadType),sizeof(LINE_HEAD_TYPE));
    fin.readRawData(reinterpret_cast<char*>(&cl.endLineHeadType),sizeof(LINE_HEAD_TYPE));

    return fin;
}


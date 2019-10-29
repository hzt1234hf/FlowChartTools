#include "chart_base.h"
int Chart_Base::magPointWidth = 7;
int Chart_Base::sizePointWidth = 9;
int Chart_Base::magPointWidth1_2 = magPointWidth/2;
int Chart_Base::sizePointWidth1_2 = sizePointWidth/2;
int Chart_Base::pointLineWidth = 2;
int Chart_Base::pointLineWidth1_2 = pointLineWidth/2;
int Chart_Base::chartIDCount = 0;

QPen Chart_Base::paintDrawPen  = QPen(QColor(150,80,80),pointLineWidth);
QBrush Chart_Base::paintFillPen  = QBrush(QColor(255,255,255));

Chart_Base::Chart_Base(QWidget *parent, PaintChartType type, bool textType, bool mov, int mpc, int spc):QWidget(parent),magPoint(mpc),sizePoint(spc),movable(mov),chartText(textType)
{
    chartType = type;
    widgetPosInit();
    varInit();
    paintInit();
    pointInit();
    colorInit();
    textInit();
//    installEventFilter(this);
    setMouseTracking(true);
}

Chart_Base::Chart_Base( int x, int y, int w, int h, QWidget *parent, PaintChartType type):QWidget(parent),magPoint(4),sizePoint(4)
{
    chartType = type;
    widgetPosInit(x,y,w,h);
    varInit();
    paintInit();
    pointInit();
    colorInit();
    textInit();
//    installEventFilter(this);
    setMouseTracking(true);
}

Chart_Base::Chart_Base(Chart_Base &cb)
{
    chartType = cb.chartType;
    paintStart = cb.paintStart;
    paintEnd = cb.paintEnd;
    magPoint = cb.magPoint;
    sizePoint = cb.sizePoint;
#if 0
    for(auto it = magPoint.begin();it!=magPoint.end();it++)
    {
        QPainterPath *tmp = new QPainterPath(*(it->i_path));
        it->i_path = tmp;
    }
    for(auto it = sizePoint.begin();it!=sizePoint.end();it++)
    {
        QPainterPath *tmp = new QPainterPath(*(it->i_path));
        it->i_path = tmp;
    }
#endif
    varInit();
    paintInit();
    pointInit();
    colorInit();
    textInit();
//    installEventFilter(this);
    setMouseTracking(true);
}









void Chart_Base::widgetPosInit(int x,int y,int w,int h)
{
    widgetStart.setX(x);
    widgetStart.setY(y);
    //widgetPos = widgetStart;
    widgetEnd.setX(x+w);
    widgetEnd.setY(y+h);
    updateWidgetPosInof();
}

void Chart_Base::varInit(int mpw,int spw,int plw,bool sa,bool smo)
{
    qDebug()<<chartIDCount;
    ID = chartIDCount++;
    Chart_Base::magPointWidth = mpw;
    Chart_Base::sizePointWidth = spw;
    updatePaddingInfo();
    Chart_Base::pointLineWidth = plw;
    showAll = sa;
    showMag = smo;
    qDebug()<<"Create ";
}

void Chart_Base::paintInit()
{
    updatePaintInfo();
}

void Chart_Base::pointInit()
{
    for(auto it = magPoint.i_point.begin();it != magPoint.i_point.end(); it++)
    {
        (*it) = new i_magpointbase;
        (*it)->i_pos = new QPoint;
    }
    for(auto it = sizePoint.i_point.begin();it != sizePoint.i_point.end(); it++)
    {
        (*it) = new i_pointbase;
        (*it)->i_pos = new QPoint;
    }

    updateSizePointInfo();
    updateSizePointPath();
    updateMagPointInfo();
    updateMagPointPath();
}


void Chart_Base::textInit()
{
    if(chartText.textType)
    {
        chartText.textType1 = new Chart_Label(this);
        chartText.textType1->setText("文本注释");
        chartText.textType1->setWordWrap(true);
        chartText.textType1->move(paintStart.rx() + sizePointWidth,paintStart.ry() + sizePointWidth);
        chartText.textType1->adjustSize();
        connect(chartText.textType1,SIGNAL(setTypeChangeTextPos(CHART_LABEL_MOUSE_TYPE,int,int)),this,SLOT(setTypeChangeTextPos(CHART_LABEL_MOUSE_TYPE,int,int)));
        //chartText.textType1->show();
    }
    else
    {
        chartText.textType2 = new Chart_PlainText(this);
        chartText.textType2->appendPlainText("文本注释");
        //chartText.textType2->show();
        chartText.textType2->setFrameShape(QFrame::NoFrame);
        chartText.textType2->setFrameShadow(QFrame::Plain);
        chartText.textType2->move(paintStart.rx() + sizePointWidth,paintStart.ry() + sizePointWidth);
        chartText.textType2->setStyleSheet("background:transparent;");
        chartText.textType2->setSizePolicy(QSizePolicy::Preferred,QSizePolicy::Preferred);
        chartText.textType2->adjustSize();
        chartText.textType2->setSizeAdjustPolicy(QAbstractScrollArea::AdjustToContents);
        chartText.textType2->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
        chartText.textType2->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
        connect(chartText.textType2,SIGNAL(setTypeChangeTextPos(CHART_TEXT_MOUSE_TYPE,int,int)),this,SLOT(setTypeChangeTextPos(CHART_TEXT_MOUSE_TYPE,int,int)));
        chartText.textType2->setTextInteractionFlags(Qt::NoTextInteraction);
    }

}

void Chart_Base::colorInit()
{
    paintChartDrawPen  = QPen(QColor(0,0,0),2);
    paintChartFillPen  = QBrush(QColor(255,255,255));
}











void Chart_Base::updatePaddingInfo()
{
    magPointWidth1_2 = magPointWidth>>1;
    sizePointWidth1_2 = sizePointWidth>>1;
    pointLineWidth1_2 = pointLineWidth>>1;
}

void Chart_Base::updateWidgetPosInof()
{
#if 1
    int w;// = widgetEnd.rx()-widgetStart.rx();
    int h;// = widgetEnd.ry()-widgetStart.ry();
    int x,y;
    if(widgetEnd.rx() < widgetStart.rx())
    {
        x = widgetEnd.rx() - borderWidth;
        w = widgetStart.rx() - widgetEnd.rx() + borderWidth + borderWidth;
    }
    else
    {
        x = widgetStart.rx() - borderWidth;
        w = widgetEnd.rx() - widgetStart.rx()  + borderWidth + borderWidth;
    }
    if(widgetEnd.ry() < widgetStart.ry())
    {
        y = widgetEnd.ry() - borderWidth;
        h = widgetStart.ry() - widgetEnd.ry()  + borderWidth + borderWidth;
    }
    else
    {
        y = widgetStart.ry() - borderWidth;
        h = widgetEnd.ry() - widgetStart.ry()  + borderWidth + borderWidth;
    }
    //setGeometry(widgetStart.rx(),widgetStart.ry(),w>minSizeWH?w:minSizeWH,h>minSizeWH?h:minSizeWH);
    specialWidgetUpdate(x,y,w,h);
    setGeometry(x,y,w,h);
#else
    int w = widgetEnd.rx()-widgetStart.rx();
    int h = widgetEnd.ry()-widgetStart.ry();
    //setGeometry(widgetStart.rx(),widgetStart.ry(),w>minSizeWH?w:minSizeWH,h>minSizeWH?h:minSizeWH);
    setGeometry(widgetStart.rx(),widgetStart.ry(),w,h);
#endif
}
void Chart_Base::updatePaintInfo()
{
    paintStart.setX(borderWidth);
    paintStart.setY(borderWidth);
    paintEnd.setX(borderWidth + abs(widgetEnd.rx() - widgetStart.rx()));
    paintEnd.setY(borderWidth + abs(widgetEnd.ry() - widgetStart.ry()));
    specialPaintUpdate(paintStart,paintEnd);
}

void Chart_Base::updateSizePointInfo()
{
    if(sizePoint.i_point.size()>=4)
    {
        int x1 = paintStart.rx(),y1 = paintStart.ry();
        int x2 = paintEnd.rx(),y2 = paintEnd.ry();
        sizePoint.i_point[0]->setX(x1);
        sizePoint.i_point[0]->setY(y1);
        sizePoint.i_point[0]->setRotate(ORIENTION::NORTHWEST);
        sizePoint.i_point[1]->setX(x2);
        sizePoint.i_point[1]->setY(y1);
        sizePoint.i_point[1]->setRotate(ORIENTION::NORTHEAST);
        sizePoint.i_point[2]->setX(x2);
        sizePoint.i_point[2]->setY(y2);
        sizePoint.i_point[2]->setRotate(ORIENTION::SOUTHEAST);
        sizePoint.i_point[3]->setX(x1);
        sizePoint.i_point[3]->setY(y2);
        sizePoint.i_point[3]->setRotate(ORIENTION::SOUTHWEST);
    }
}

void Chart_Base::updateMagPointInfo()
{
    if(magPoint.i_point.size()>=4)
    {
        int x1 = paintStart.rx(),y1 = paintStart.ry();
        int x2 = paintEnd.rx(),y2 = paintEnd.ry();
        int midx = ((paintStart.rx() + paintEnd.rx())>>1);
        int midy = ((paintStart.ry() + paintEnd.ry())>>1);

        magPoint.i_point[0]->setX(midx);
        magPoint.i_point[0]->setY(y1);
        magPoint.i_point[0]->setRotate(ORIENTION::NORTH);
        magPoint.i_point[1]->setX(x2);
        magPoint.i_point[1]->setY(midy);
        magPoint.i_point[1]->setRotate(ORIENTION::EAST);
        magPoint.i_point[2]->setX(midx);
        magPoint.i_point[2]->setY(y2);
        magPoint.i_point[2]->setRotate(ORIENTION::SOUTH);
        magPoint.i_point[3]->setX(x1);
        magPoint.i_point[3]->setY(midy);
        magPoint.i_point[3]->setRotate(ORIENTION::WEST);
    }
}

void Chart_Base::adjustPointInfo()
{
    for(auto it = magPoint.i_point.begin();it!=magPoint.i_point.end();it++)
    {
        switch((*it)->getRotate())
        {
            default:case ORIENTION::NONE:case ORIENTION::NORTHWEST:break;
            case ORIENTION::NORTH:(*it)->setX((*it)->getX() + pointLineWidth1_2);break;
            case ORIENTION::NORTHEAST:(*it)->setX((*it)->getX() + pointLineWidth);break;
            case ORIENTION::EAST:(*it)->setX((*it)->getX() + pointLineWidth);(*it)->setY((*it)->getY() + pointLineWidth1_2);break;
            case ORIENTION::SOUTHEAST:(*it)->setX((*it)->getX() + pointLineWidth);(*it)->setY((*it)->getY() + pointLineWidth);break;
            case ORIENTION::SOUTH:(*it)->setX((*it)->getX() + pointLineWidth1_2);(*it)->setY((*it)->getY() + pointLineWidth);break;
            case ORIENTION::SOUTHWEST:(*it)->setY((*it)->getY() + pointLineWidth);break;
            case ORIENTION::WEST:(*it)->setY((*it)->getY() + pointLineWidth1_2);break;
        }
    }
    for(auto it = sizePoint.i_point.begin();it!=sizePoint.i_point.end();it++)
    {
        switch((*it)->getRotate())
        {
            default:case ORIENTION::NONE:case ORIENTION::NORTHWEST:break;
            case ORIENTION::NORTH:(*it)->setX((*it)->getX() + pointLineWidth1_2);break;
            case ORIENTION::NORTHEAST:(*it)->setX((*it)->getX() + pointLineWidth);break;
            case ORIENTION::EAST:(*it)->setX((*it)->getX() + pointLineWidth);(*it)->setY((*it)->getY() + pointLineWidth1_2);break;
            case ORIENTION::SOUTHEAST:(*it)->setX((*it)->getX() + pointLineWidth);(*it)->setY((*it)->getY() + pointLineWidth);break;
            case ORIENTION::SOUTH:(*it)->setX((*it)->getX() + pointLineWidth1_2);(*it)->setY((*it)->getY() + pointLineWidth);break;
            case ORIENTION::SOUTHWEST:(*it)->setY((*it)->getY() + pointLineWidth);break;
            case ORIENTION::WEST:(*it)->setY((*it)->getY() + pointLineWidth1_2);break;
        }
    }
}
void Chart_Base::updateMagPointPath()
{
    for(auto it = magPoint.i_point.begin(),end = magPoint.i_point.end();it != end;it++)
    {
        (*it)->newPath()->addEllipse((*it)->getX() - sizePointWidth1_2,(*it)->getY() - sizePointWidth1_2,sizePointWidth,sizePointWidth);
    }
}

void Chart_Base::updateSizePointPath()
{
    for(auto it = sizePoint.i_point.begin(),end = sizePoint.i_point.end();it != end;it++)
    {
        (*it)->newPath()->addRect((*it)->getX() - sizePointWidth1_2,(*it)->getY() - sizePointWidth1_2,sizePointWidth,sizePointWidth);
    }
}
void Chart_Base::updateMagPointLine()
{
    for(auto it = magPoint.i_point.begin(),end = magPoint.i_point.end();it != end;it++)
    {
        for(auto l_it = (*it)->i_lineStart.begin(),l_end = (*it)->i_lineStart.end();l_it != l_end;l_it++)
        {
            if( (*l_it)->widgetStart.rx() != (*it)->getX() + x() || (*l_it)->widgetStart.ry() != (*it)->getY() + y())
            {
                (*l_it)->setStartPos((*it)->getX() + x(),(*it)->getY() + y());

                (*l_it)->updateWidgetPosInof();
                (*l_it)->updatePaintInfo();
                (*l_it)->updateSizePointInfo();
                (*l_it)->updateSizePointPath();
                (*l_it)->updateTextInfo();
            }
        }
        for(auto l_it = (*it)->i_lineEnd.begin(),l_end = (*it)->i_lineEnd.end();l_it != l_end;l_it++)
        {
            if( (*l_it)->widgetEnd.rx() != (*it)->getX() + x() || (*l_it)->widgetEnd.ry() != (*it)->getY() + y())
            {
                (*l_it)->setEndPos((*it)->getX() + x(),(*it)->getY() + y());

                (*l_it)->updateWidgetPosInof();
                (*l_it)->updatePaintInfo();
                (*l_it)->updateSizePointInfo();
                (*l_it)->updateSizePointPath();
                (*l_it)->updateTextInfo();
            }
        }
    }
}
void Chart_Base::updateTextInfo()
{
    int w = paintEnd.rx() - paintStart.rx();
    w = w>0?w:0;
    if(chartText.textType)
    {
        chartText.textType1->setMaximumWidth(w);
        chartText.textType1->setMaximumHeight(w);
        chartText.textType1->adjustSize();
        if(chartText.textType1->x() + chartText.textType1->width() >paintEnd.rx())
        {
            if(paintEnd.rx() - chartText.textType1->width()<paintStart.rx())
                chartText.textType1->move(paintStart.rx(),chartText.textType1->y());
            else
                chartText.textType1->move(paintEnd.rx() - chartText.textType1->width(),chartText.textType1->y());
        }
        if(chartText.textType1->y() + chartText.textType1->height() >paintEnd.ry())
        {
            if(paintEnd.ry() - chartText.textType1->height()<paintStart.ry())
                chartText.textType1->move(chartText.textType1->x(),paintStart.ry());
            else
                chartText.textType1->move(chartText.textType1->x(),paintEnd.ry() - chartText.textType1->height());
        }
    }
    else
    {
        chartText.textType2->setMaximumWidth(w);
        chartText.textType2->setMaximumHeight(w);
        chartText.textType2->adjustSize();
        if(chartText.textType2->x() + chartText.textType2->width() >paintEnd.rx())
        {
            if(paintEnd.rx() - chartText.textType2->width()<paintStart.rx())
                chartText.textType2->move(paintStart.rx(),chartText.textType2->y());
            else
                chartText.textType2->move(paintEnd.rx() - chartText.textType2->width(),chartText.textType2->y());
        }
        if(chartText.textType2->y() + chartText.textType2->height() >paintEnd.ry())
        {
            if(paintEnd.ry() - chartText.textType2->height()<paintStart.ry())
                chartText.textType2->move(chartText.textType2->x(),paintStart.ry());
            else
                chartText.textType2->move(chartText.textType2->x(),paintEnd.ry() - chartText.textType2->height());
        }
    }
}












void Chart_Base::paintMagPoint(QPainter & p)
{
    QPen tmp = p.pen();
    p.setPen(paintDrawPen);
#if (RUNTIME_PAINTMAG == ENABLE)
    QPainterPath path;
#else
    QPainterPath* tmpPath;
#endif
    for(auto it = magPoint.i_point.begin(),end = magPoint.i_point.end(); it != end;it++)
    {
#if (RUNTIME_PAINTMAG == ENABLE)
        path.addEllipse((*it).i_pos.rx()-magPointWidth1_2,(*it).i_pos.ry()-magPointWidth1_2,magPointWidth,magPointWidth);
#else
        tmpPath = (*it)->getPath();
        p.drawPath(*tmpPath);
        p.fillPath(*tmpPath,paintFillPen);
#endif
    }
#if (RUNTIME_PAINTMAG == ENABLE)
    p.fillPath(path,tb);
    p.drawPath(path);
#endif
    p.setPen(tmp);
}

void Chart_Base::paintSizePoint(QPainter & p)
{
    QPen tmp = p.pen();
    p.setPen(paintDrawPen);


#if (RUNTIME_PAINTSIZE == ENABLE)
    QPainterPath path;
#else
    QPainterPath* tmpPath;
#endif
    for(auto it = sizePoint.i_point.begin(),end = sizePoint.i_point.end(); it != end;it++)
    {
#if (RUNTIME_PAINTSIZE == ENABLE)
        path.addRect((*it).i_pos.rx()-sizePointWidth1_2,(*it).i_pos.ry()-sizePointWidth1_2,sizePointWidth,sizePointWidth);
#else
        tmpPath = (*it)->getPath();
        p.drawPath(*tmpPath);
        p.fillPath(*tmpPath,paintFillPen);
#endif
    }

#if (RUNTIME_PAINTSIZE == ENABLE)
    p.fillPath(path,tb);
    p.drawPath(path);
#endif
    p.setPen(tmp);
}
void Chart_Base::paintSizeEdge(QPainter & p)
{
    QPen tmp = p.pen();
    p.setPen(paintDrawPen);

    int sx = paintStart.rx(),sy = paintStart.ry(),ex = paintEnd.rx(),ey = paintEnd.ry();
    int /*sx1 = sx-sizePointWidth1_2,*/sx2 = sx+sizePointWidth1_2,/*sy1 = sy-sizePointWidth1_2,*/sy2 = sy+sizePointWidth1_2;
    int ex1 = ex-sizePointWidth1_2/*,ex2 = ex+sizePointWidth1_2*/,ey1 = ey-sizePointWidth1_2/*,ey2 = ey+sizePointWidth1_2*/;
    p.drawLine(sx2,sy,ex1,sy);
    p.drawLine(ex,sy2,ex,ey1);
    p.drawLine(ex1,ey,sx2,ey);
    p.drawLine(sx,ey1,sx,sy2);

    p.setPen(tmp);
}

bool Chart_Base::inPath(const QPointF &p)
{
    for(auto it = magPoint.i_point.begin(),end = magPoint.i_point.end();it!=end;it++)
    {
        if((*it)->inPath(p))return true;
    }
    for(auto it = sizePoint.i_point.begin(),end = sizePoint.i_point.end();it!=end;it++)
    {
        if((*it)->inPath(p))return true;
    }
    return inGraphisPath(p);
}
bool Chart_Base::inMagPath(const QPointF &p, ORIENTION &b, int &index) const
{
    int i = 0;
    for(auto it = magPoint.i_point.begin(),end = magPoint.i_point.end();it!=end;it++,i++)
    {
        if((*it)->inPath(p))
        {
            b = (*it)->getRotate();
            index = i;
            return true;
        }
    }
    return false;
}
bool Chart_Base::inSizePath(const QPointF &p, ORIENTION &b) const
{
    int x,y;
    for(auto it = sizePoint.i_point.begin(),end = sizePoint.i_point.end();it!=end;it++)
    {
        if((*it)->inPath(p))
        //x = p.x()-(*it)->getX();
        //y = p.y()-(*it)->getY();
        //if(x>=0&&x<=sizePointWidth && y>=0&&y<=sizePointWidth)
        {
            b = (*it)->getRotate();
            return true;
        }
    }
    return false;
}
void Chart_Base::setStartPos(int x,int y)
{
    widgetStart.setX(x);
    widgetStart.setY(y);
}
void Chart_Base::setEndPos(int x,int y)
{
    widgetEnd.setX(x);
    widgetEnd.setY(y);
}
//void Chart_Base::setGeometryNew(int x,int y,int w, int h)
//{
//    int *x1,*y1;
//    int *x2,*y2;
//    if(widgetEnd.rx()<widgetStart.rx())
//    {
//        x1 = &widgetEnd.rx();
//        x2 = &widgetStart.rx();
//    }else{
//        x1 = &widgetStart.rx();
//        x2 = &widgetEnd.rx();
//    }
//    if(widgetEnd.ry()<widgetStart.ry())
//    {
//        y1 = &widgetEnd.ry();
//        y2 = &widgetStart.ry();
//    }else{
//        y1 = &widgetStart.ry();
//        y2 = &widgetEnd.ry();
//    }
//    *x2 = x + w;
//    *y2 = y + h;
//    *x1 = x;
//    *y1 = y;

////    widgetStart.setX(x);
////    widgetStart.setY(y);
////    widgetEnd.setX(x+w);
////    widgetEnd.setY(y+h);

//    updateWidgetPosInof();
//    updatePaintInfo();
//    updateSizePointInfo();
//    updateSizePointPath();
//    updateMagPointInfo();
//    updateMagPointPath();
//    updateMagPointLine();
//    updateTextInfo();
//}
void Chart_Base::setXY(int x, int y)
{
    int *x1,*y1;
    int *x2,*y2;
    if(widgetEnd.rx()<widgetStart.rx())
    {
        x1 = &widgetEnd.rx();
        x2 = &widgetStart.rx();
    }else{
        x1 = &widgetStart.rx();
        x2 = &widgetEnd.rx();
    }
    if(widgetEnd.ry()<widgetStart.ry())
    {
        y1 = &widgetEnd.ry();
        y2 = &widgetStart.ry();
    }else{
        y1 = &widgetStart.ry();
        y2 = &widgetEnd.ry();
    }
    *x2 = x + *x2 - *x1;
    *y2 = y + *y2 - *y1;
    *x1 = x;
    *y1 = y;

    //widgetEnd.setX(x+widgetEnd.rx()-widgetStart.rx());
    //widgetEnd.setY(y+widgetEnd.ry()-widgetStart.ry());
    //widgetStart.setX(x);
    //widgetStart.setY(y);

    updateWidgetPosInof();
    updateMagPointLine();
}
void Chart_Base::setWidthHeight(int x, int y)
{
#if 0
    ORIENTION type;
    if(x>=widgetPos.rx()+borderWidth)
    {
        if(y>=widgetPos.ry()+borderWidth)  type = ORIENTION::SOUTHEAST;
        else type = ORIENTION::NORTHEAST;
    }
    else if(y>=widgetPos.ry()+borderWidth)
    {
        if(x>=widgetPos.rx()+borderWidth) type = ORIENTION::SOUTHEAST;
        else    type = ORIENTION::SOUTHWEST;
    }
    else
    {
        type = ORIENTION::NORTHWEST;
    }

    switch(type)
    {
        case ORIENTION::NORTHWEST:
        {
            if(type != lastType)
            {
                widgetEnd.setX(widgetPos.rx()+borderWidth);
                widgetEnd.setY(widgetPos.ry()+borderWidth);
            }
            widgetStart.setX(x - borderWidth);
            widgetStart.setY(y - borderWidth);
        }break;
        case ORIENTION::NORTHEAST:
        {
            if(type != lastType)
            {
                widgetEnd.setY(widgetPos.ry()+borderWidth);
                widgetStart.setX(widgetPos.rx()+borderWidth);
            }
            widgetEnd.setX(x + borderWidth);
            widgetStart.setY(y - borderWidth);
        }break;
        case ORIENTION::SOUTHEAST:
        {
            if(type != lastType)
            {
                widgetStart.setX(widgetPos.rx()+borderWidth);
                widgetStart.setY(widgetPos.ry()+borderWidth);
            }
            widgetEnd.setX(x + borderWidth);
            widgetEnd.setY(y + borderWidth);
        }break;
        case ORIENTION::SOUTHWEST:
        {
            if(type != lastType)
            {
                widgetStart.setY(widgetPos.ry()+borderWidth);
                widgetEnd.setX(widgetPos.rx()+borderWidth);
            }
            widgetStart.setX(x - borderWidth);
            widgetEnd.setY(y + borderWidth);
        }break;
    }
    lastType = type;
#elif 0
    ORIENTION type;
    if(x < widgetStart.rx())
    {
        widgetEnd.setX(x);
        //widgetStart.setY(widgetStart.ry()+borderWidth);
    }
    else
    {
        widgetEnd.setX(x);
    }
    if(y < widgetStart.ry())
    {
        widgetEnd.setY(y);
        //widgetStart.setX(widgetStart.rx()+borderWidth);
    }
    else
    {
        widgetEnd.setY(y);
    }
#else
    widgetEnd.setX(x);
    widgetEnd.setY(y);
#endif

    updateWidgetPosInof();
    updatePaintInfo();
    updateSizePointInfo();
    updateSizePointPath();
    updateMagPointInfo();
    updateMagPointPath();
    updateMagPointLine();
    updateTextInfo();
}
void Chart_Base::setWidthHeight(int x, int y, ORIENTION type)
{
    int *x1,*y1;
    int *x2,*y2;
    if(widgetEnd.rx()<widgetStart.rx())
    {
        x1 = &widgetEnd.rx();
        x2 = &widgetStart.rx();
    }else{
        x1 = &widgetStart.rx();
        x2 = &widgetEnd.rx();
    }
    if(widgetEnd.ry()<widgetStart.ry())
    {
        y1 = &widgetEnd.ry();
        y2 = &widgetStart.ry();
    }else{
        y1 = &widgetStart.ry();
        y2 = &widgetEnd.ry();
    }
    switch(type)
    {
        case ORIENTION::NORTHWEST:
        {
            if(*x2-x<minSizeWH) *x1 = *x2-minSizeWH;
            else *x1 = x;
            if(*y2-y<minSizeWH) *y1 = *y2-minSizeWH;
            else *y1 = y;
            //widgetPos = widgetStart;
        }break;
        case ORIENTION::NORTHEAST:
        {
            if(x-*x1<minSizeWH) *x2 = *x1+minSizeWH;
            else *x2 = x;
            if(*y2-y<minSizeWH) *y1 = *y2-minSizeWH;
            else *y1 = y;
            //widgetPos = widgetStart;
        }break;
        case ORIENTION::SOUTHEAST:
        {
            if(x-*x1<minSizeWH) *x2 = *x1+minSizeWH;
            else *x2 = x;
            if(y-*y1<minSizeWH) *y2 = *y1+minSizeWH;
            else *y2 = y;
            //widgetPos = widgetStart;
        }break;
        case ORIENTION::SOUTHWEST:
        {
            if(*x2-x<minSizeWH) *x1 = *x2-minSizeWH;
            else *x1 = x;
            if(y-*y1<minSizeWH) *y2 = *y1+minSizeWH;
            else *y2 = y;
            //widgetPos = widgetStart;
        }break;
        case ORIENTION::STARTPOINT:{
            if(x<widgetEnd.rx())
                widgetStart.setX(x );
            else
                widgetStart.setX(x );
            if(y<widgetEnd.ry())
                widgetStart.setY(y );
            else
                widgetStart.setY(y );
        }break;
        case ORIENTION::ENDPOINT:{
            if(x<widgetStart.rx())
                widgetEnd.setX(x );
            else
                widgetEnd.setX(x );
            if(y<widgetStart.ry())
                widgetEnd.setY(y );
            else
                widgetEnd.setY(y );
        }break;
        default:{
        }
    }

    updateWidgetPosInof();
    updatePaintInfo();
    updateSizePointInfo();
    updateSizePointPath();
    updateMagPointInfo();
    updateMagPointPath();
    updateMagPointLine();
    updateTextInfo();
}
void Chart_Base::applyWidthHeight()
{
    updateWidgetPosInof();
    updatePaintInfo();
    updateSizePointInfo();
    updateSizePointPath();
    updateMagPointInfo();
    updateMagPointPath();
    updateMagPointLine();
    updateTextInfo();
}
//void Chart_Base::setSizePoint(const std::vector<QPoint> &p)
//{
//    for(auto it = sizePoint.begin();it != sizePoint.end();it++)
//        if((*it).i_path) delete (*it).i_path;
//    sizePoint.clear();
//    for(auto it = p.begin(); it!=p.end();it++)
//        sizePoint.push_back({*it,nullptr});
//}
//void Chart_Base::setMagPoint(const std::vector<QPoint> &p)
//{
//    for(auto it = magPoint.begin();it != magPoint.end();it++)
//        if((*it).i_path) delete (*it).i_path;
//    magPoint.clear();
//    for(auto it = p.begin(); it!=p.end();it++)
//        magPoint.push_back({*it,nullptr});
//}

bool Chart_Base::autoSetMagi(int &abcx,int &abcy, int &index)
{
    int mx = abcx;
    int my = abcy;
    if(mx >= x() && my >= y() && mx-x()<=width() && my-y()<=width())
    {
        showMagOnly();
        int x1,y1;
        mx -= x();
        my -= y();
        int i = 0;
        for(auto it = magPoint.i_point.begin(),end = magPoint.i_point.end();it != end;it++,i++)
        {
            x1 = (*it)->getX() +  magPointWidth1_2;
            y1 = (*it)->getY() +  magPointWidth1_2;
            if(abs(x1-mx) <= magPointAutoMagiRange && abs(y1-my) <= magPointAutoMagiRange)
            {
                abcx = x() + (*it)->getX();
                abcy = y() + (*it)->getY();
                index = i;
                return true;
            }
        }
    }
    else
    {
        hideMagOnly();
    }

    return false;
}
void Chart_Base::overlapChartMousePressed(QMouseEvent *event)
{
    int mx = event->pos().rx();
    int my = event->pos().ry();
    if(mx >= x() && my >= y() && mx-x()<=width() && my-y()<=width())
    {
        QPointF tmp(mx-this->x(),my-this->y());
        ORIENTION direct = ORIENTION::NONE;

        if(inGraphisPath(tmp))
        {
            emit sendThisClass(this,tmp.rx()-borderWidth,tmp.ry()-borderWidth);
            curFlag = MOUSE_EVENT_TYPE::RUNTIME_CHANGE_POS;
            event->accept();
            raise();
        }
    }
}
void Chart_Base::overlapChartMouseMove(QMouseEvent *event)
{
    int mx = event->pos().rx();
    int my = event->pos().ry();

    if( mx >= x() && my >= y() && mx-x()<=width() && my-y()<=height())
    {
        ORIENTION direct = ORIENTION::NONE;
        int index;
        QPointF tmp(mx-this->x(),my-this->y());
        if(showMag)
        {
            if(inMagPath(tmp,direct,index))
            {
                setCursor(QCursor(Qt::SizeAllCursor));
                event->accept();
                raise();
            }
            else if(inGraphisPath(tmp))
            {
                setCursor(QCursor(Qt::SizeAllCursor));
                event->accept();
                raise();
            }
            else
            {
                hideMagOnly();
                setCursor(QCursor(Qt::ArrowCursor));
            }
        }
        else
        {
            if(inGraphisPath(tmp))
            {
                setCursor(QCursor(Qt::SizeAllCursor));
                event->accept();
                raise();
            }
            else
            {
                setCursor(QCursor(Qt::ArrowCursor));
            }
        }
    }
}
void Chart_Base::deleteThisChart()
{
}
void Chart_Base::saveStaticValue(QDataStream &fout)
{
    fout.writeRawData(reinterpret_cast<const char*>(&Chart_Base::magPointWidth),sizeof(int));
    fout.writeRawData(reinterpret_cast<const char*>(&Chart_Base::sizePointWidth),sizeof(int));
    fout.writeRawData(reinterpret_cast<const char*>(&Chart_Base::pointLineWidth),sizeof(int));
    //fout.writeRawData(reinterpret_cast<const char*>(&Chart_Base::chartIDCount),sizeof(int));
    qDebug()<<magPointWidth<<" "<<sizePointWidth<<" "<<pointLineWidth<<" "<<chartIDCount;
}
void Chart_Base::loadStaticValue(QDataStream &fin)
{
    fin.readRawData(reinterpret_cast<char*>(&Chart_Base::magPointWidth),sizeof(int));
    fin.readRawData(reinterpret_cast<char*>(&Chart_Base::sizePointWidth),sizeof(int));
    fin.readRawData(reinterpret_cast<char*>(&Chart_Base::pointLineWidth),sizeof(int));
    updatePaddingInfo();
    //fin.readRawData(reinterpret_cast<char*>(&Chart_Base::chartIDCount),sizeof(int));
    qDebug()<<"static value:"<<magPointWidth<<" "<<sizePointWidth<<" "<<pointLineWidth<<" "<<chartIDCount;
}
QDataStream &operator<<(QDataStream &fout,  const Chart_Base &cb)
{
    fout.writeRawData(reinterpret_cast<const char*>(&cb.chartType),sizeof(PaintChartType));
    fout.writeRawData(reinterpret_cast<const char*>(&cb.ID),sizeof(int));
    fout<<cb.chartText;//<<cb.magPoint;
    fout<<cb.paintStart<<cb.paintEnd<<cb.widgetStart<<cb.widgetEnd<<cb.paintChartDrawPen<<cb.paintChartFillPen;
//    fout.writeRawData(reinterpret_cast<char*>(&cb.paintStart.rx()),sizeof(int));
//    fout.writeRawData(reinterpret_cast<char*>(&cb.paintEnd.rx()),sizeof(int));
//    fout.writeRawData(reinterpret_cast<char*>(&cb.widgetStart.rx()),sizeof(int));
//    fout.writeRawData(reinterpret_cast<char*>(&cb.widgetEnd.rx()),sizeof(int));
//    fout.writeRawData(reinterpret_cast<char*>(&cb.paintChartDrawPen),sizeof(QPen));
//    fout.writeRawData(reinterpret_cast<char*>(&cb.paintChartFillPen),sizeof(QBrush));
    fout.writeRawData(reinterpret_cast<const char*>(&cb.movable),sizeof(bool));
    qDebug()<<"Chart Base Info:"<<cb.paintStart<<cb.paintEnd<<cb.widgetStart<<cb.widgetEnd<<cb.paintChartDrawPen<<cb.paintChartFillPen;
    return fout;
}
QDataStream &operator>>(QDataStream &fin, Chart_Base &cb)
{
    //fin.readRawData(reinterpret_cast<char*>(&cb.chartType),sizeof(PaintChartType));
    fin.readRawData(reinterpret_cast<char*>(&cb.ID),sizeof(int));
    fin>>cb.chartText;//>>cb.magPoint;
    fin>>cb.paintStart>>cb.paintEnd>>cb.widgetStart>>cb.widgetEnd>>cb.paintChartDrawPen>>cb.paintChartFillPen;
//    fin.readRawData(reinterpret_cast<char*>(&cb.paintStart.rx()),sizeof(int));
//    fin.readRawData(reinterpret_cast<char*>(&cb.paintEnd.rx()),sizeof(int));
//    fin.readRawData(reinterpret_cast<char*>(&cb.widgetStart.rx()),sizeof(int));
//    fin.readRawData(reinterpret_cast<char*>(&cb.widgetEnd.rx()),sizeof(int));
//    fin.readRawData(reinterpret_cast<char*>(&cb.paintChartDrawPen),sizeof(QPen));
//    fin.readRawData(reinterpret_cast<char*>(&cb.paintChartFillPen),sizeof(QBrush));
    fin.readRawData(reinterpret_cast<char*>(&cb.movable),sizeof(bool));
    qDebug()<<"Chart Base Info:"<<cb.paintStart<<cb.paintEnd<<cb.widgetStart<<cb.widgetEnd<<cb.paintChartDrawPen<<cb.paintChartFillPen;
    return fin;
}






void Chart_Base::showMagSize()
{
    showAll = true;
    showMag = false;
    update();
}
void Chart_Base::hideMagSize()
{
    if(showAll)
    {
        this->releaseKeyboard();
        showAll = false;
        if(chartText.textType)
        {
            if(chartText.tmpEdit1)
            {
                chartText.textType1->setText(chartText.tmpEdit1->text());
                chartText.textType1->adjustSize();
                delete chartText.tmpEdit1;
                chartText.tmpEdit1 = nullptr;
            }
        }
        else
        {
            if(chartText.tmpEdit2)
            {

                //chartText.setText(tmpLineEdit->text());
                chartText.textType2->setPlainText(chartText.tmpEdit2->toPlainText());
                chartText.textType2->setSizePolicy(QSizePolicy::Preferred,QSizePolicy::Preferred);

                chartText.textType2->setSizeAdjustPolicy(QAbstractScrollArea::AdjustToContents);
                chartText.textType2->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
                chartText.textType2->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
                chartText.textType2->adjustSize();
                delete chartText.tmpEdit2;
                chartText.tmpEdit2 = nullptr;
            }
        }
        //curFlag = MOUSE_EVENT_TYPE::NONE;
        update();
    }
}


void Chart_Base::showMagOnly()
{
    if(showMag == false)
    {
        showMag = true;
        showAll = false;
        update();
    }
}
void Chart_Base::hideMagOnly()
{
    if(showMag)
    {
        this->releaseKeyboard();
        showMag = false;
        if(chartText.textType)
        {
            if(chartText.tmpEdit1)
            {
                chartText.textType1->setText(chartText.tmpEdit1->text());
                chartText.textType1->adjustSize();
                delete chartText.tmpEdit1;
                chartText.tmpEdit1 = nullptr;
            }
        }
        else
        {
            if(chartText.tmpEdit2)
            {

                //chartText.setText(tmpLineEdit->text());
                chartText.textType2->setPlainText(chartText.tmpEdit2->toPlainText());
                chartText.textType2->setSizePolicy(QSizePolicy::Preferred,QSizePolicy::Preferred);

                chartText.textType2->setSizeAdjustPolicy(QAbstractScrollArea::AdjustToContents);
                chartText.textType2->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
                chartText.textType2->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
                chartText.textType2->adjustSize();
                delete chartText.tmpEdit2;
                chartText.tmpEdit2 = nullptr;
            }
        }
        update();
    }
}




void Chart_Base::paintEvent(QPaintEvent *event)
{
    QPainter p(this);
    paintChart(p);
    if(showAll)
    {
        paintSizeEdge(p);
        paintMagPoint(p);
        paintSizePoint(p);
    }else if(showMag)
    {
        paintMagPoint(p);
    }
    event->accept();
}

//bool Chart_Base::eventFilter(QObject *target, QEvent *event)
//{
//    //qDebug()<<QCursor::pos();
////    if(event->type() == QEvent::Enter)
////    {
////        showMagOnly();
////        event->accept();
////    }
////    else if(event->type() == QEvent::Leave)
////    {
////        hideMagOnly();
////        event->accept();
////    }

//    return QWidget::eventFilter(target, event);
//}

void Chart_Base::mousePressEvent(QMouseEvent *event)
{
    //if(curFlag == MOUSE_EVENT_TYPE::NONE)
    {
        ORIENTION direct = ORIENTION::NONE;
        int index;

        if(showAll&&inSizePath(event->pos(),direct))
        {
            emit setTypeChangeSize(direct);
            curFlag = MOUSE_EVENT_TYPE::RUNTIME_CHANGE_SIZE;
            curIndex = direct;
            raise();

        }
        else if((showAll||showMag)&&inMagPath(event->pos(),direct,index))
        {
            emit setTypeCreateMagPoint(this,direct,index);
            curFlag = MOUSE_EVENT_TYPE::RUNTIME_CREATE_MAGPOINT;
            curIndex = direct;
            showMagOnly();
            raise();
        }
        else if(inGraphisPath(event->pos()) )
        {
            emit sendThisClass(this,event->pos().rx()-borderWidth,event->pos().ry()-borderWidth);
            curFlag = MOUSE_EVENT_TYPE::RUNTIME_CHANGE_POS;
            curIndex = direct;
            raise();
        }
        else
        {
            curFlag = MOUSE_EVENT_TYPE::NONE;
            showAll = false;
            event->ignore();
        }

    }
    //else
    {
        //event->ignore();
    }
}
void Chart_Base::mouseMoveEvent(QMouseEvent *event)
{
    if(curFlag == MOUSE_EVENT_TYPE::NONE)
    {
        ORIENTION direct = ORIENTION::NONE;
        int index;

        if(showAll)
        {
            if(inSizePath(event->pos(),direct))
            {
                switch(ORIENTION(direct))
                {
                    case ORIENTION::NORTHWEST:case ORIENTION::SOUTHEAST:{
                        setCursor(QCursor(Qt::SizeFDiagCursor));
                    }break;
                    case ORIENTION::NORTHEAST:case ORIENTION::SOUTHWEST:{
                        setCursor(QCursor(Qt::SizeBDiagCursor));
                    }break;
                    case ORIENTION::STARTPOINT:case ORIENTION::ENDPOINT:{
                        setCursor(QCursor(Qt::SizeAllCursor));
                    }break;
                }
                raise();
            }
            else if(inMagPath(event->pos(),direct,index))
            {
                setCursor(QCursor(Qt::CrossCursor));
                raise();
            }
            else if(inGraphisPath(event->pos()))
            {
                setCursor(QCursor(Qt::SizeAllCursor));
                raise();
            }
            else
            {
                //setCursor(QCursor(Qt::ArrowCursor));
                event->ignore();
            }
        }
        else if(showMag)
        {
            if(inMagPath(event->pos(),direct,index))
            {
                setCursor(QCursor(Qt::CrossCursor));
                raise();
            }
            else if(inGraphisPath(event->pos()))
            {
                setCursor(QCursor(Qt::SizeAllCursor));
                raise();
            }
            else
            {
                //setCursor(QCursor(Qt::ArrowCursor));
                hideMagOnly();
                event->ignore();
            }
        }
        else
        {
            if(inGraphisPath(event->pos()))
            {
                setCursor(QCursor(Qt::SizeAllCursor));
                showMagOnly();
                raise();
            }
            else
            {
                //setCursor(QCursor(Qt::ArrowCursor));
                event->ignore();
            }
        }
        if(chartText.textMouseT1 == CHART_LABEL_MOUSE_TYPE::CHANGE_POS)
        {
            emit sendThisClass(this,event->pos().rx()-borderWidth,event->pos().ry()-borderWidth);
            if(chartText.textType == 1)
            {
                chartText.textType1->move(event->pos().rx()-chartText.chartTextMousePos.rx(),event->pos().ry()-chartText.chartTextMousePos.ry());
                chartText.textType1->adjustSize();
            }
            else
            {
                chartText.textType2->move(event->pos().rx()-chartText.chartTextMousePos.rx(),event->pos().ry()-chartText.chartTextMousePos.ry());
            }
        }
    }
    else
    {
        event->ignore();
    }

}
void Chart_Base::mouseReleaseEvent(QMouseEvent *event)
{
    if(chartText.textType)
    {
        chartText.textMouseT1 = CHART_LABEL_MOUSE_TYPE::NONE;
    }
    else
    {
        chartText.textMouseT2 = CHART_TEXT_MOUSE_TYPE::NONE;
    }
    curFlag = MOUSE_EVENT_TYPE::NONE;
    //setCursor(QCursor(Qt::ArrowCursor));
    event->ignore();
}
void Chart_Base::mouseDoubleClickEvent(QMouseEvent *event)
{
    if(inPath(event->pos()))
    {
        emit sendThisClass(this,event->pos().rx()-borderWidth,event->pos().ry()-borderWidth);
        if(chartText.textType)
        {
            chartText.tmpEdit1 = new QLineEdit(chartText.textType1->text(),this);
            chartText.textType1->setText("");
            chartText.tmpEdit1->adjustSize();
            chartText.tmpEdit1->setStyleSheet("background:transparent;");
            chartText.tmpEdit1->setGeometry(chartText.textType1->x(),chartText.textType1->y(),chartText.textType1->width() + (textBorderWidth<<1),chartText.textType1->height() + (textBorderWidth<<1));
            chartText.tmpEdit1->show();
            chartText.tmpEdit1->setFocus();
        }
        else
        {
            chartText.tmpEdit2 = new QPlainTextEdit(chartText.textType2->toPlainText(),this);
            chartText.textType2->setPlainText("");
            chartText.tmpEdit2->adjustSize();
            chartText.tmpEdit2->setStyleSheet("background:transparent;");
            chartText.tmpEdit2->setGeometry(paintStart.rx() + textBorderWidth,paintStart.ry() + textBorderWidth,paintEnd.rx() - paintStart.rx() - (textBorderWidth<<1),paintEnd.ry() - paintStart.ry() - (textBorderWidth<<1));
            chartText.tmpEdit2->show();
            chartText.tmpEdit2->setFocus();
        }
        this->grabKeyboard();
    }else{
        event->ignore();
    }
}

void Chart_Base::leaveEvent(QEvent *event)
{
    hideMagOnly();
}

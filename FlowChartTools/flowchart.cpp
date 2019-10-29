#include "flowchart.h"


FlowChart::FlowChart(QWidget *parent, Qt::WindowFlags f) : QWidget(parent,f)
{
    this->grabKeyboard();
//    installEventFilter(this);
    initVar();
    setMouseTracking(true);
    update();
}

void FlowChart::initVar()
{
    mouseEventType = MOUSE_EVENT_TYPE::NONE;
    curPaintChart = nullptr;
    curSelecChart = nullptr;
    newLineChart = nullptr;
    newLineFromSelectChart = nullptr;
    newLineToSelectChart = nullptr;
}

void FlowChart::resetFlowChartPanel()
{
    Chart_Base::resetStaticVal();
    curPaintChart = nullptr;
    curPaintChartType = PaintChartType::NONE;
    curSelecChart = nullptr;
    curSelecChartPos = QPoint();
    newLineChart = nullptr;
    newLineToSelectChart = nullptr;
    newLineFromSelectChart = nullptr;
    magPointDirect = ORIENTION::NONE;
    magPointFromIndex = 0;
    magPointToIndex = 0;
    sizePointDirect = ORIENTION::NONE;
    clearChartsLine();
    charts.reserve(0);
    charts.resize(0);
    line.reserve(0);
    line.resize(0);
    mouseEventType = MOUSE_EVENT_TYPE::NONE;
    fileIsOpened = false;
    fileIsSaved = true;
    filePath = "";
    setFileNameShow(fileIsSaved);
}

void FlowChart::setFileSetSaved(bool isSaved)
{
    if(fileIsSaved != isSaved)
    {
        fileIsSaved = isSaved;
        setFileNameShow(fileIsSaved);
    }
}

void FlowChart::setFileNameShow(bool isSaved)
{
    QString tmp;
    if(fileIsOpened)
    {
        tmp = QString("%1%2").arg(filePath).arg((isSaved?"":" *"));
        emit updateWindowTitle(tmp);
    }else
    {
        tmp = QString("%1%2").arg("Untitle").arg((isSaved?"":" *"));
        emit updateWindowTitle(tmp);
    }
}

Chart_Base * FlowChart::getCurPaintChart()
{
    return curPaintChart;
}

void FlowChart::setSelChartLineColor(const QColor &color)
{
    curSelecChart->paintChartDrawPen.setColor(color);
    curSelecChart->update();
}

void FlowChart::setSelChartFillColor(const QColor &color)
{
    curSelecChart->paintChartFillPen.setColor(color);
    curSelecChart->update();
}

void FlowChart::setMousePressedFlag(MOUSE_EVENT_TYPE f)
{
    mouseEventType = f;
}

void FlowChart::setPaintChart()
{
    if(curPaintChart != nullptr)
        delete curPaintChart;

    switch(curPaintChartType)
    {
        case PaintChartType::RECT:
        {
            curPaintChart = new Chart_Rect(this);
        }break;
        case PaintChartType::DIAMOND:
        {
            curPaintChart = new Chart_Diamond(this);
        }break;
        case PaintChartType::ROUNDRECT:
        {
            curPaintChart = new Chart_RoundRect(this);
        }break;
        case PaintChartType::ELLIPSE:
        {
            curPaintChart = new Chart_Ellipse(this);
        }break;
        case PaintChartType::LINE:
        {
            curPaintChart = new Chart_Line(this);
        }break;
        case PaintChartType::TRAPEZOID:
        {
            curPaintChart = new Chart_Trapezoid(this);
        }break;
        default:case PaintChartType::NONE:{
            curPaintChart = nullptr;
        }break;
    }
    if(curPaintChart)
    {
        mouseEventType = MOUSE_EVENT_TYPE::CREATING_CNANGE_SIZE;
    }
}

void FlowChart::setSelecChart(Chart_Base * cb, int x, int y)
{

    emit disableStyle();
    this->grabKeyboard();
    if(curSelecChart != nullptr) curSelecChart->hideMagSize();
    curSelecChart = cb;
    curSelecChart->showMagSize();
    curSelecChartPos = QPoint(x,y);
    mouseEventType = MOUSE_EVENT_TYPE::RUNTIME_CHANGE_POS;
    Chart_Line *cl = nullptr;
    if(nullptr == (cl = dynamic_cast<Chart_Line*>(cb)))
    {
        emit sendChartStyle(cb->paintChartDrawPen,cb->paintChartFillPen);
    }else
    {
        emit sendLineStyle(cl->paintChartDrawPen,cl->getStartLineHeadType(),cl->getEndLineHeadType());
    }
}

bool FlowChart::openChartFile()
{
    if(!fileIsSaved)
    {
        QMessageBox tmp(QMessageBox::Warning,tr("警告！"),tr("不保存文件就关闭？"),QMessageBox::NoButton,this->parentWidget());
        QPushButton *saveclose = tmp.addButton(tr("保存并关闭"),QMessageBox::ActionRole);
        QPushButton *nosaveclose = tmp.addButton(tr("不保存关闭"),QMessageBox::AcceptRole);
        QPushButton *cancel = tmp.addButton(tr("取消"),QMessageBox::RejectRole);
        tmp.exec();
        if(tmp.clickedButton() == saveclose)
        {
            if(saveChartFile())
            {
                resetFlowChartPanel();
            }else
                return false;
            //qDebug()<<"Save and Quit";
        }else if(tmp.clickedButton() == nosaveclose)
        {
            //qDebug()<<"Not Save and Quit";
            resetFlowChartPanel();
        }else if(tmp.clickedButton() == cancel)
        {
            return true;
            //qDebug()<<"cancel ";
        }
    }
    resetFlowChartPanel();
    QString tmpFilePath = QFileDialog::getOpenFileName(this,tr("打开文件"),"F:",tr("FCT文件(*.fct)"));
    if(tmpFilePath == "") return false;

    if(loadFile(tmpFilePath) == false)
    {
        QMessageBox::critical(this->parentWidget(),tr("错误！"),tr("打开文件失败！\n文件损坏或类型不正确"),QMessageBox::Ok);
        return false;
    }else
    {
        fileIsOpened = true;
        this->filePath = tmpFilePath;
        setFileNameShow(fileIsSaved);
        qDebug()<<"Load File Success"<<fileIsSaved;
    }
    qDebug()<<"charts size:"<<charts.size()<<" line size::"<<line.size();
    return true;
}

bool FlowChart::saveChartFile()
{
    if(fileIsSaved)
    {
        return true;
    }else
    {
        if(fileIsOpened)
        {
            if(saveFile(filePath))
            {
                filePath = "";
            }else
            {
                QMessageBox::critical(this->parentWidget(),tr("错误！"),tr("保存文件失败！\n文件已占用或者访问权限不足"),QMessageBox::Ok);
                return false;
            }
        }else{
            QString tmpFilePath = QFileDialog::getSaveFileName(this,tr("保存文件"),"F:",tr("FCT文件(*.fct)"));
            if(tmpFilePath == "") return false;
            if(saveFile(tmpFilePath))
            {
                filePath = tmpFilePath;
                fileIsOpened = true;
            }else
            {
                QMessageBox::critical(this->parentWidget(),tr("错误！"),tr("保存文件失败！\n文件已占用或者访问权限不足"),QMessageBox::Ok);
                return false;
            }
        }
        setFileSetSaved(true);
    }
    return true;
}
bool FlowChart::newChartFile()
{
    if(!fileIsSaved)
    {
        QMessageBox tmp(QMessageBox::Warning,tr("警告！"),tr("不保存文件就关闭？"),QMessageBox::NoButton,this->parentWidget());
        QPushButton *saveclose = tmp.addButton(tr("保存并关闭"),QMessageBox::ActionRole);
        QPushButton *nosaveclose = tmp.addButton(tr("不保存关闭"),QMessageBox::AcceptRole);
        QPushButton *cancel = tmp.addButton(tr("取消"),QMessageBox::RejectRole);
        tmp.exec();
        if(tmp.clickedButton() == saveclose)
        {
            if(saveChartFile())
            {
                resetFlowChartPanel();
            }else{
                return false;
            }
            //qDebug()<<"Save and Quit";

        }else if(tmp.clickedButton() == nosaveclose)
        {
            //qDebug()<<"Not Save and Quit";
            resetFlowChartPanel();
        }else if(tmp.clickedButton() == cancel)
        {
            //qDebug()<<"cancel ";
        }
    }else{
        resetFlowChartPanel();
    }
    return true;
}

//void FlowChart::resetSeletcChart()
//{
//    if(curSelecChart != nullptr) curSelecChart->hideMagSize();
//    curSelecChart = nullptr;
//}

Chart_Base * FlowChart::getCurSeleChart()
{
    return curSelecChart;
}


void FlowChart::addChart(Chart_Base *cb)
{
    charts.push_back(cb);
}
bool FlowChart::delChart(Chart_Base *&cb)
{
    for(auto it = charts.begin();it != charts.end();it++)
    {
        if(*it == cb)
        {
            Chart_Base *tmp = cb;
            cb = nullptr;
            charts.erase(it);
#if 1
            for(auto magit = tmp->magPoint.i_point.begin();magit!=tmp->magPoint.i_point.end();magit++)
            {
                for(auto magLineStIt = (*magit)->i_lineStart.begin();magLineStIt != (*magit)->i_lineStart.end();magLineStIt++)
                {
                    dynamic_cast<Chart_Line*>(*magLineStIt) ->resetEndChart();
                    if(!delLine(*magLineStIt))
                    {
                        qDebug()<<"Error";
                    }else{
                        qDebug()<<"Succeed.";
                    }
                }
                for(auto magLineEnIt = (*magit)->i_lineEnd.begin();magLineEnIt != (*magit)->i_lineEnd.end();magLineEnIt++)
                {
                    dynamic_cast<Chart_Line*>(*magLineEnIt) ->resetStartChart();
                    if(!delLine(*magLineEnIt))
                    {
                        qDebug()<<"Error";
                    }else{
                        qDebug()<<"Succeed.";
                    }
                }
            }
#endif
            delete[] tmp;

            return true;
        }
    }
    return false;
}
void FlowChart::addLine(Chart_Base *cb)
{
    line.push_back(cb);
}
bool FlowChart::delLine(Chart_Base *&cb)
{
    for(auto it = line.begin();it != line.end();it++)
    {
        if(*it == cb)
        {
            Chart_Line *tmp = dynamic_cast<Chart_Line*>(*it);
            cb = nullptr;
            line.erase(it);
            qDebug()<<tmp->magPoint.i_point.size();


            tmp->resetEndChart();
            tmp->resetStartChart();
            delete tmp;
            return true;
        }
    }
    return false;
}

void FlowChart::hideMagSizeAll()
{
    for(auto it = charts.begin();it!=charts.end();it++)
    {
        (*it)->hideMagSize();
    }
    for(auto it = line.begin();it!=line.end();it++)
    {
        (*it)->hideMagSize();
    }
    curSelecChart = nullptr;
    mouseEventType = MOUSE_EVENT_TYPE::NONE;
    emit disableStyle();
}

bool FlowChart::saveFile(QString filePath)
{
    QFile file(filePath);
    file.open(QIODevice::WriteOnly);
    QDataStream fout(&file);

    Chart_Base::saveStaticValue(fout);
    unsigned long long i;
    i = charts.size();
    fout.writeRawData(reinterpret_cast<const char*>(&i),sizeof(unsigned long long));
    for(auto it = charts.begin(); it!=charts.end(); it++)
    {
        fout<<*(*it);
    }
    i = line.size();
    fout.writeRawData(reinterpret_cast<const char*>(&i),sizeof(unsigned long long));
    for(auto it = line.begin(); it!=line.end(); it++)
    {
        fout<<*(*it)<<*(reinterpret_cast<const Chart_Line*>(*it));
    }
    file.close();
    return true;
}

bool FlowChart::loadFile(QString filePath)
{
    QFile file(filePath);
    file.open(QIODevice::ReadOnly);
    QDataStream fin(&file);
    std::map<int,Chart_Base*> chartMap;

    Chart_Base::loadStaticValue(fin);
    unsigned long long cnt;
    fin.readRawData(reinterpret_cast<char*>(&cnt),sizeof(unsigned long long));
    qDebug()<<"图形个数："<<cnt;
    for(unsigned long long i = 0;i<cnt;i++)
    {
        PaintChartType tmp;
        Chart_Base *cb;
        fin.readRawData(reinterpret_cast<char*>(&tmp),sizeof(PaintChartType));
        switch(tmp)
        {

            case PaintChartType::RECT:
            {
                cb = new Chart_Rect(this);
            }break;
            case PaintChartType::DIAMOND:
            {
                cb = new Chart_Diamond(this);
            }break;
            case PaintChartType::ROUNDRECT:
            {
                cb = new Chart_RoundRect(this);
            }break;
            case PaintChartType::ELLIPSE:
            {
                cb = new Chart_Ellipse(this);
            }break;
            case PaintChartType::TRAPEZOID:
            {
                cb = new Chart_Trapezoid(this);
            }break;
            default:case PaintChartType::NONE:{
                cb = nullptr;
            }break;
        }
        cb->chartType = tmp;
        fin>>(*cb);
        connect(cb,SIGNAL(sendThisClass(Chart_Base *, int,int)),this,SLOT(setSelecChart(Chart_Base *, int,int)));
        connect(cb,SIGNAL(setTypeChangeSize(ORIENTION)),this,SLOT(setTypeChangeSize(ORIENTION)));
        connect(cb,SIGNAL(setTypeCreateMagPoint(Chart_Base *,ORIENTION,int)),this,SLOT(setTypeCreateMagPoint(Chart_Base *,ORIENTION,int)));
        addChart(cb);
        cb->applyWidthHeight();
        cb->update();
        cb->show();
        chartMap[cb->getID()] = cb;
    }
    fin.readRawData(reinterpret_cast<char*>(&cnt),sizeof(unsigned long long));
    qDebug()<<"连线个数："<<cnt;
    for(unsigned long long i = 0;i<cnt;i++)
    {
        PaintChartType tmp;
        Chart_Base *cb;
        Chart_Line *cl;
        int id;
        fin.readRawData(reinterpret_cast<char*>(&tmp),sizeof(PaintChartType));
        cb = new Chart_Line(this);
        addLine(cb);
        if(nullptr == (cl = dynamic_cast<Chart_Line*>(cb))) qDebug()<<"error";
        fin>>(*cb)>>(*cl);
        try{
            fin.readRawData(reinterpret_cast<char*>(&id),sizeof(int));
            if(id>=0)
            {
                Chart_Base *cbs = chartMap.at(id);
                cbs->addMagiPointStartLine(cl->getStartMagIndex(),cl);
                cl->setStartChart(cbs);
            }
        }catch(std::out_of_range &oor){
            qDebug()<<oor.what()<<"Not Found Start chart.";
        }
        try{
            fin.readRawData(reinterpret_cast<char*>(&id),sizeof(int));
            if(id>=0)
            {
                Chart_Base *cbe = chartMap.at(id);
                cbe->addMagiPointEndLine(cl->getEndMagIndex(),cl);
                cl->setEndChart(cbe);
            }
        }catch(std::out_of_range &oor){
            qDebug()<<oor.what()<<"Not Found End chart.";
        }
        connect(cl,SIGNAL(sendThisClass(Chart_Base *, int,int)),this,SLOT(setSelecChart(Chart_Base *, int,int)));
        connect(cl,SIGNAL(setTypeChangeSize(ORIENTION)),this,SLOT(setTypeChangeSize(ORIENTION)));
        cl->applyWidthHeight();
        cl->update();
        cl->show();
    }
    hideMagSizeAll();
    return true;
}


void FlowChart::paintEvent(QPaintEvent *event)
{
    QPainter p(this);
    p.setPen(QColor(150,150,150));
    const int gap = 30;
    for(int i = 1;i * gap < width();i++)
    {
        if(i%5 == 0)
            p.drawLine(QLineF(i*gap,0,i*gap,height()));
    }
    for(int i = 1;i * gap < height();i++)
    {
        if(i%5 == 0)
            p.drawLine(QLineF(0,i*gap,width(),i*gap));
    }

    p.setPen(QColor(200,200,200,150));
    //p.setPen(Qt::DotLine);
    //p.setOpacity(200);
    for(int i = 1;i * gap < width();i++)
    {
        if(i%5 == 0) continue;
        p.drawLine(QLineF(i*gap,0,i*gap,height()));
    }
    for(int i = 1;i * gap < height();i++)
    {
        if(i%5 == 0) continue;
        p.drawLine(QLineF(0,i*gap,width(),i*gap));
    }


    QStyleOption opt;
    opt.init(this);
    style()->drawPrimitive(QStyle::PE_Widget, &opt, &p, this);
    QWidget::paintEvent(event);

    //event->accept();
}
void FlowChart::mousePressEvent(QMouseEvent *event)
{
    event->ignore();
    switch(mouseEventType)
    {
        case MOUSE_EVENT_TYPE::CREATING_CNANGE_SIZE:{
            int x = event->pos().rx();
            int y = event->pos().ry();
            //curPaintChart->setObjectName(QStringLiteral("tttt"));
            if(curSelecChart) curSelecChart->hideMagSize();
            curSelecChart = curPaintChart;
            curPaintChart->setXY(x,y);
            //curPaintChart->setAttribute(Qt::WA_StyledBackground,true);
            //curPaintChart->setStyleSheet(QStringLiteral("background-color: rgb(100, 100, 100);"));
            if(curPaintChart->chartType == PaintChartType::LINE)
            {
                connect(curPaintChart,SIGNAL(sendThisClass(Chart_Base *, int,int)),this,SLOT(setSelecChart(Chart_Base *, int,int)));
                connect(curPaintChart,SIGNAL(setTypeChangeSize(ORIENTION)),this,SLOT(setTypeChangeSize(ORIENTION)));
                addLine(curPaintChart);
                Chart_Line *cl = dynamic_cast<Chart_Line*>(curSelecChart);
                emit sendLineStyle(cl->paintChartDrawPen,cl->getStartLineHeadType(),cl->getEndLineHeadType());
            }else
            {
                connect(curPaintChart,SIGNAL(sendThisClass(Chart_Base *, int,int)),this,SLOT(setSelecChart(Chart_Base *, int,int)));
                connect(curPaintChart,SIGNAL(setTypeChangeSize(ORIENTION)),this,SLOT(setTypeChangeSize(ORIENTION)));
                connect(curPaintChart,SIGNAL(setTypeCreateMagPoint(Chart_Base *,ORIENTION,int)),this,SLOT(setTypeCreateMagPoint(Chart_Base *,ORIENTION,int)));
                //connect(curPaintChart,SIGNAL(hideThisClass()),this,SLOT(resetSeletcChart()));
                addChart(curPaintChart);
                emit sendChartStyle(curSelecChart->paintChartDrawPen,curSelecChart->paintChartFillPen);
            }
            curPaintChart->update();
            curPaintChart->show();
            //mouseEventType = MOUSE_EVENT_TYPE::CREATING_CNANGE_SIZE;
            event->accept();
        }break;
        default:case MOUSE_EVENT_TYPE::NONE:{
            for(auto it = charts.begin();it!=charts.end();it++)
            {
                (*it)->overlapChartMousePressed(event);
                if(event->isAccepted()) return;
            }
            for(auto a:line)
            {
                a->overlapChartMousePressed(event);
                if(event->isAccepted()) return;
            }
            hideMagSizeAll();
        }break;
    }
}
void FlowChart::mouseMoveEvent(QMouseEvent *event)
{
    //if(event->isAccepted()) return;
    event->ignore();
    switch(mouseEventType)
    {
        default:case MOUSE_EVENT_TYPE::NONE:
        {
            for(auto it = charts.begin();it!=charts.end();it++)
            {
                (*it)->overlapChartMouseMove(event);
                if(event->isAccepted()) return;
            }
            for(auto it = line.begin();it!=line.end();it++)
            {
                (*it)->overlapChartMouseMove(event);
                if(event->isAccepted()) return;
            }
            if(curSelecChart == nullptr)
            {
                setCursor(QCursor(Qt::ArrowCursor));
                hideMagSizeAll();
            }
        }break;
        case MOUSE_EVENT_TYPE::CREATING_CNANGE_SIZE:
        {
            int x = event->pos().rx(),y = event->pos().ry();
            if(curSelecChart)
            {
                if(curSelecChart->chartType == PaintChartType::LINE)
                {
                    for(auto it = charts.begin();it!=charts.end();it++)
                    {
                        if((*it)->autoSetMagi(x,y,magPointIndex))
                        {
                            lineSelectChart = *it;
                            break;
                        }else{
                            lineSelectChart = nullptr;
                        }
                    }
                    //if(!lineSelectChart) reinterpret_cast<Chart_Line *>(curSelecChart)->resetEndChart();
                }
                curPaintChart->setWidthHeight(x,y);
            }
            event->accept();
        }break;
        case MOUSE_EVENT_TYPE::RUNTIME_CHANGE_SIZE:
        {
            int x = event->pos().rx(),y = event->pos().ry();

            if(curSelecChart->chartType == PaintChartType::LINE)
            {
                qDebug()<<"hehe";
                for(auto it = charts.begin();it!=charts.end();it++)
                {
                    if((*it)->autoSetMagi(x,y,magPointIndex))
                    {
                        lineSelectChart = *it;
                        break;
                    }else{
                        lineSelectChart = nullptr;
                    }
                }
                //if(!lineSelectChart) reinterpret_cast<Chart_Line *>(curSelecChart)->resetEndChart();
            }
            curSelecChart->setWidthHeight(x,y,sizePointDirect);
            event->accept();
        }break;
        case MOUSE_EVENT_TYPE::RUNTIME_CREATE_MAGPOINT:
        {
            if(newLineChart == nullptr)
            {
                newLineChart = new Chart_Line(this);
                if(curSelecChart)
                    curSelecChart->hideMagSize();
                curSelecChart = newLineChart;
                addLine(newLineChart);
                //newLineChart->setAttribute(Qt::WA_StyledBackground,true);
                //newLineChart->setStyleSheet(QStringLiteral("background-color: rgb(100, 100, 100);"));
                connect(newLineChart,SIGNAL(sendThisClass(Chart_Base *, int,int)),this,SLOT(setSelecChart(Chart_Base *, int,int)));
                connect(newLineChart,SIGNAL(setTypeChangeSize(ORIENTION)),this,SLOT(setTypeChangeSize(ORIENTION)));
                newLineChart->setXY(newLineFromSelectChart->getMagiPointAbsX(magPointFromIndex),newLineFromSelectChart->getMagiPointAbsY(magPointFromIndex));
                newLineChart->setStartChart(newLineFromSelectChart);
                newLineChart->setStartMagIndex(magPointFromIndex);
                newLineChart->setStartDirect(magPointDirect);
                newLineChart->update();
                newLineChart->show();

                newLineFromSelectChart->addMagiPointStartLine(magPointFromIndex,newLineChart);
            }
            int x = event->pos().rx(),y = event->pos().ry();

            for(auto it = charts.begin();it!=charts.end();it++)
            {
                //if(*it == newLineFromSelectChart) continue;
                if((*it)->autoSetMagi(x,y,magPointToIndex))
                {
                    newLineToSelectChart = *it;
                    break;
                }else{
                    newLineToSelectChart = nullptr;
                }
            }
            //if(!newLineToSelectChart) newLineChart->resetEndChart();
            newLineChart->setWidthHeight(x,y,ORIENTION::ENDPOINT);
            event->ignore();
        }break;
        case MOUSE_EVENT_TYPE::RUNTIME_CHANGE_POS:
        {
            if(curSelecChart->chartType != PaintChartType::LINE)
            {
                curSelecChart->setXY(event->pos().rx() - curSelecChartPos.rx(),event->pos().ry() - curSelecChartPos.ry());
                event->accept();
            }
        }break;
    }
}

void FlowChart::mouseReleaseEvent(QMouseEvent *event)
{
    switch(mouseEventType)
    {
        case MOUSE_EVENT_TYPE::CREATING_CNANGE_SIZE:
        {
            //curPaintChart->updatePath();
            resetPaintChartType();
            if(curSelecChart->chartType == PaintChartType::LINE)
            {
                Chart_Line *cl = reinterpret_cast<Chart_Line *>(curSelecChart);

                if(lineSelectChart)
                {
                    lineSelectChart->addMagiPointEndLine(magPointIndex,curSelecChart);
                    lineSelectChart->hideMagOnly();
                    cl->setEndChart(lineSelectChart);
                    cl->setEndMagIndex(magPointIndex);
                    cl->setEndDirect(lineSelectChart->getMagiPointDirect(magPointIndex));
                    cl->update();
                    lineSelectChart = nullptr;
                }
                else{
                    cl->resetEndChart();
                }

            }


            curPaintChart = nullptr;
            mouseEventType = MOUSE_EVENT_TYPE::NONE;
            setFileSetSaved(false);
            event->accept();
        }break;
        case MOUSE_EVENT_TYPE::RUNTIME_CHANGE_SIZE:
        {
            if(curSelecChart->chartType == PaintChartType::LINE)
            {
                Chart_Line *cl = reinterpret_cast<Chart_Line *>(curSelecChart);
                if(lineSelectChart)
                {
                    if(sizePointDirect == ORIENTION::STARTPOINT)
                    {
                        cl->resetStartChart();
                        lineSelectChart->addMagiPointStartLine(magPointIndex,curSelecChart);
                        lineSelectChart->hideMagOnly();
                        cl->setStartChart(lineSelectChart);
                        cl->setStartMagIndex(magPointIndex);
                        cl->setStartDirect(lineSelectChart->getMagiPointDirect(magPointIndex));
                    }else if(sizePointDirect == ORIENTION::ENDPOINT)
                    {
                        cl->resetEndChart();
                        lineSelectChart->addMagiPointEndLine(magPointIndex,curSelecChart);
                        lineSelectChart->hideMagOnly();
                        cl->setEndChart(lineSelectChart);
                        cl->setEndMagIndex(magPointIndex);
                        cl->setEndDirect(lineSelectChart->getMagiPointDirect(magPointIndex));
                    }else{
                        qDebug()<<"Error";
                    }

                    cl->update();
                }else
                {
                    if(sizePointDirect == ORIENTION::STARTPOINT)
                    {
                        cl->resetStartChart();
                    }else if(sizePointDirect == ORIENTION::ENDPOINT)
                    {
                        cl->resetEndChart();
                    }else
                    {
                        qDebug()<<"Error";
                    }
                }
            }
            mouseEventType = MOUSE_EVENT_TYPE::NONE;
            lineSelectChart = nullptr;
            setFileSetSaved(false);
            event->accept();
        }break;
        case MOUSE_EVENT_TYPE::RUNTIME_CREATE_MAGPOINT:
        {
            if(newLineToSelectChart)
            {
                newLineToSelectChart->addMagiPointEndLine(magPointToIndex,newLineChart);
                newLineToSelectChart->hideMagOnly();
                newLineChart->setEndChart(newLineToSelectChart);
                newLineChart->setEndMagIndex(magPointToIndex);
                newLineChart->setEndDirect(newLineToSelectChart->getMagiPointDirect(magPointToIndex));
                newLineChart->update();
            }else
            {
                if(newLineChart)
                    newLineChart->resetEndChart();
            }
            mouseEventType = MOUSE_EVENT_TYPE::NONE;
            newLineChart = nullptr;
            newLineFromSelectChart = nullptr;
            newLineToSelectChart = nullptr;
            setFileSetSaved(false);
            event->accept();
        }break;
        case MOUSE_EVENT_TYPE::RUNTIME_CHANGE_POS:
        {
            mouseEventType = MOUSE_EVENT_TYPE::NONE;
            setFileSetSaved(false);
            event->accept();
        }break;
        default:case MOUSE_EVENT_TYPE::NONE:
        {
            event->ignore();
        }break;
    }

}
void FlowChart::keyPressEvent(QKeyEvent *ev)
{
    ev->ignore();
    switch(ev->key())
    {
        case Qt::Key_Escape:
        {
            if(curSelecChart)
            {
                curSelecChart->hideMagSize();
                curSelecChart = nullptr;
            }
        }break;
        case Qt::Key_Delete:
        {
            if(curSelecChart)
            {
                if(curSelecChart->chartType == PaintChartType::LINE)
                {
                    if(!delLine(curSelecChart))
                    {
                        qDebug()<<"Error";
                    }
                }else{
                    if(!delChart(curSelecChart))
                    {
                        qDebug()<<"Error";
                    }
                }
                curSelecChart = nullptr;
            }
        }break;
#if 0
        case Qt::Key_Q:
        {
            qDebug()<<"总个数：charts:"<<charts.size()<<",lines:"<<line.size();
            for(auto it = charts.begin();it != charts.end();it++)
            {
                qDebug()<<"\t磁力点个数："<<(*it)->magPoint.i_point.size();
                for(auto magit = (*it)->magPoint.i_point.begin();magit!=(*it)->magPoint.i_point.end();magit++)
                {
                    qDebug()<<"\t\t线头个数："<<(*magit)->i_lineStart.size()<<"，线尾个数："<<(*magit)->i_lineEnd.size();
                    for(auto magLineStIt = (*magit)->i_lineStart.begin();magLineStIt != (*magit)->i_lineStart.end();magLineStIt++)
                    {
                        qDebug()<<"\t\t\t线头ID："<<(*magLineStIt)->getID();
                    }
                    for(auto magLineEnIt = (*magit)->i_lineEnd.begin();magLineEnIt != (*magit)->i_lineEnd.end();magLineEnIt++)
                    {
                        qDebug()<<"\t\t\t线尾ID："<<(*magLineEnIt)->getID();
                    }
                }
            }
            qDebug();
            for(auto it = line.begin();it != line.end();it++)
            {
                qDebug()<<"\t线头："<<((dynamic_cast<Chart_Line*>(*it)->getStartChart() == nullptr)?"-":"有")<<"，线尾："<<(((dynamic_cast<Chart_Line*>(*it)->getEndChart()) == nullptr)?"-":"有");
            }
        }break;
#endif
        default:{
            ev->ignore();
        }
    }
}
void FlowChart::keyReleaseEvent(QKeyEvent *ev)
{
    ev->ignore();
}

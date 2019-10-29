#ifndef FLOWCHART_H
#define FLOWCHART_H
#pragma execution_character_set("utf-8")
#include <map>
#include <stdexcept>

#include <QWidget>
#include <QPainter>
#include <vector>
#include <QDebug>
#include <QMouseEvent>
#include <QPolygon>
#include<QStyleOption>


#include <QPushButton>
#include <QMessageBox>
#include <QFileDialog>
#include <QColorDialog>

#include "class_Charts/chart_base.h"
#include "class_Charts/chart_rect.h"
#include "class_Charts/chart_diamond.h"
#include "class_Charts/chart_roundrect.h"
#include "class_Charts/chart_ellipse.h"
#include "class_Charts/chart_line.h"
#include "class_Charts/chart_trapezoid.h"

#include "comdef.h"

class FlowChart : public QWidget
{
    Q_OBJECT
private:
    friend class Chart_Base;
    Chart_Base *curPaintChart = nullptr;                        // 将要放置的图形
    PaintChartType curPaintChartType = PaintChartType::NONE;    // 绘制的图形的类型

    Chart_Base *curSelecChart = nullptr;    // 选中的画板上的图形
    QPoint curSelecChartPos;                // 选中时指针在图像对象上的位置信息

    Chart_Line *newLineChart = nullptr;             // 要创建的磁力点的连线的指针
    Chart_Base *newLineToSelectChart = nullptr;     // 要连接到的磁力点的图形的指针
    Chart_Base *newLineFromSelectChart = nullptr;   // 要创建的磁力点的图形的指针
    ORIENTION magPointDirect = ORIENTION::NONE;     // 选中时要创建的起始磁力点的方向类型
    int magPointFromIndex;                          // 要创建的磁力点的索引
    int magPointToIndex;                            // 要创建的磁力点的索引

    Chart_Base *lineSelectChart = nullptr;  // 运行时线的吸附到的图形的指针
    int magPointIndex;                      // 运行时线吸附到的图形的磁力点的索引

    ORIENTION sizePointDirect = ORIENTION::NONE;    // 选中时要改变大小的大小点的方向类型

    std::vector<Chart_Base*> charts;    // 画板上图形的集合
    std::vector<Chart_Base*> line;      // 画板上线的集合

    MOUSE_EVENT_TYPE mouseEventType = MOUSE_EVENT_TYPE::NONE;   // 当前鼠标事件类型

    bool fileIsOpened = false;      // 是否打开了文件
    bool fileIsSaved = true;        // 是否保存了文件
    QString filePath;               // 打开文件的路径

    void initVar();             // 变量默认初始化函数
    void resetFlowChartPanel(); // 重置流图画板
    void setFileSetSaved(bool isSaved);     // 设置文件未保存
    void setFileNameShow(bool isSaved);     // 设置窗体文件名
    void clearChartsLine(){                 // 释放图形、连线内存
        for(auto it = charts.begin();it!=charts.end();it++) {
            if(*it) delete *it;
            *it = nullptr;
        }
        for(auto it = line.begin();it!=line.end();it++) {
            if(*it) delete *it;
            *it = nullptr;
        }
    }

public:
    explicit FlowChart(QWidget *parent = nullptr , Qt::WindowFlags f = 0);
    virtual ~FlowChart()
    {
        //delete[] curPaintChart;
        //delete[] curSelecChart;
        //delete[] newLineChart;
        //delete[] newLineToSelectChart;
        newChartFile();
        clearChartsLine();

    }


    Chart_Base * getCurPaintChart();    // 获取新的图形
    Chart_Base * getCurSeleChart();     // 获取当前选中的图形
    void addChart(Chart_Base *cb);        // 添加图形到图形容器
    bool delChart(Chart_Base *&cb);      // 删除图形
    void addLine(Chart_Base *cb);       // 添加线条到线条容器
    bool delLine(Chart_Base *&cb);       // 添加图形
    void hideMagSizeAll();              // 隐藏所有元素
    bool saveFile(QString filePath);    // 保存文件
    bool loadFile(QString filePath);    // 读取文件


protected:
virtual void paintEvent(QPaintEvent *event);
virtual void mousePressEvent(QMouseEvent *event);
virtual void mouseMoveEvent(QMouseEvent *event);
virtual void mouseReleaseEvent(QMouseEvent *event);
virtual void keyPressEvent(QKeyEvent *ev);
virtual void keyReleaseEvent(QKeyEvent *ev);

//bool eventFilter(QObject *target, QEvent *event);
signals:
    void sendChartStyle(QPen &qp, QBrush &qb);                                                          // 发送图形颜色信息
    void sendLineStyle(QPen &qp, LINE_HEAD_TYPE &startLineHeadType, LINE_HEAD_TYPE &endLineHeadType);   // 发送线条颜色和线头类型信息
    void disableStyle();                        // 关闭主窗体颜色信息设置
    void updateWindowTitle(const QString &);    // 更新主窗体标题
public slots:
    void setPen(QPen &qp){curSelecChart->paintChartDrawPen = qp;}                                                       // 设置笔刷
    void setBrush(QBrush &qb){curSelecChart->paintChartFillPen = qb;}                                                   // 设置填充颜色
    void setLineWidth(int i){curSelecChart->paintChartDrawPen.setWidth(i);}                                             // 设置线宽
    void setLineStartStyle(int i){dynamic_cast<Chart_Line *>(curSelecChart)->setStartLineHeadType(LINE_HEAD_TYPE(i));}  // 设置起点线头类型
    void setLineEndStyle(int i){dynamic_cast<Chart_Line *>(curSelecChart)->setEndLineHeadType(LINE_HEAD_TYPE(i));}      // 设置终点线头类型
public:
    void setSelChartLineColor(const QColor &color);     // 设置图形线条颜色
    void setSelChartFillColor(const QColor &color);     // 设置图形填充颜色

public slots:
    void setMousePressedFlag(MOUSE_EVENT_TYPE);         // 设置鼠标按下事件类型
    void setPaintChart();                           // 设置将要绘制的图形
    void setSelecChart(Chart_Base *, int ,int);     // 设置选中的画板的图像
//    void resetSeletcChart();

public slots:
    void setPaintChart_Rect(){curPaintChartType = PaintChartType::RECT;setPaintChart();}                // 获取一个新的矩形
    void setPaintChart_Diamond(){curPaintChartType = PaintChartType::DIAMOND;setPaintChart();}          // 获取一个新的菱形
    void setPaintChart_RoundRect(){curPaintChartType = PaintChartType::ROUNDRECT;setPaintChart();}      // 获取一个新的圆角矩形
    void setPaintChart_Ellipse(){curPaintChartType = PaintChartType::ELLIPSE;setPaintChart();}          // 获取一个新的圆形
    void setPaintChart_Line(){curPaintChartType = PaintChartType::LINE;setPaintChart();}                // 获取一个新的线段
    void setPaintChart_trapezoid(){curPaintChartType = PaintChartType::TRAPEZOID;setPaintChart();}      // 获取一个新的梯形
    void resetPaintChartType(){curPaintChartType = PaintChartType::NONE;}                               // 清空类型


public slots:
    void setTypeChangeSize(ORIENTION i){mouseEventType = MOUSE_EVENT_TYPE::RUNTIME_CHANGE_SIZE;sizePointDirect = i; }                                                                                                       // 设置鼠标事件类型为改变大小
    void setTypeCreateMagPoint(Chart_Base *cb,ORIENTION d,int i){newLineFromSelectChart = cb;mouseEventType = MOUSE_EVENT_TYPE::RUNTIME_CREATE_MAGPOINT;magPointDirect = d;magPointFromIndex = i;newLineChart = nullptr; }  // 设置鼠标事件类型为创建线段

    bool openChartFile();   // 打开文件
    bool saveChartFile();   // 保存文件
    bool newChartFile();    // 新建文件

};

#endif // FLOWCHART_H



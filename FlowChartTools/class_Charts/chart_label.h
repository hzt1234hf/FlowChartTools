#ifndef CHART_LABEL_H
#define CHART_LABEL_H
#include <QLabel>
#include <QWidget>
#include <QPlainTextEdit>
#include <QMouseEvent>
#include <qDebug>
enum class CHART_LABEL_MOUSE_TYPE{NONE,CHANGE_POS};

class Chart_Label : public QLabel
{
    Q_OBJECT
private:
    //Chart_Base &parent;
public:
    Chart_Label(QWidget *parent = nullptr):QLabel(parent){}
    virtual ~Chart_Label(){}
    void createText();
    void changeText();

signals:
    void setTypeChangeTextPos(CHART_LABEL_MOUSE_TYPE t,int x,int y);    // 设置位置

protected:
    virtual void mousePressEvent(QMouseEvent *event);
    virtual void mouseDoubleClickEvent(QMouseEvent *event);
    virtual void mouseMoveEvent(QMouseEvent *event);
    virtual void mouseReleaseEvent(QMouseEvent *event);

};

#endif // CHART_LABEL_H

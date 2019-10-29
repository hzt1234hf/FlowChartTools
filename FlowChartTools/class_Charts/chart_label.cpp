#include "chart_label.h"

void Chart_Label::changeText()
{
}
void Chart_Label::createText()
{
}
void Chart_Label::mousePressEvent(QMouseEvent *event)
{
    setFrameShape(QFrame::Panel);
    adjustSize();
    //emit setTypeChangeTextPos(CHART_LABEL_MOUSE_TYPE::CHANGE_POS,event->pos().rx(),event->pos().ry());
    //event->ignore();
}
void Chart_Label::mouseDoubleClickEvent(QMouseEvent *event)
{
    changeText();
    qDebug()<<"999";
    event->ignore();
}
void Chart_Label::mouseMoveEvent(QMouseEvent *event)
{
    event->ignore();
}
void Chart_Label::mouseReleaseEvent(QMouseEvent *event)
{
    setFrameShape(QFrame::NoFrame);
    event->ignore();
}

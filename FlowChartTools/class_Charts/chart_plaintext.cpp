#include "chart_plaintext.h"


void Chart_PlainText::changeText()
{
}
void Chart_PlainText::createText()
{
}
void Chart_PlainText::mousePressEvent(QMouseEvent *event)
{
    setFrameShape(QFrame::Panel);
    adjustSize();
    emit setTypeChangeTextPos(CHART_TEXT_MOUSE_TYPE::CHANGE_POS,event->pos().rx(),event->pos().ry());
    //event->ignore();
}
void Chart_PlainText::mouseDoubleClickEvent(QMouseEvent *event)
{
    changeText();
    qDebug()<<"999";
    event->ignore();
}
void Chart_PlainText::mouseMoveEvent(QMouseEvent *event)
{
    event->ignore();
}
void Chart_PlainText::mouseReleaseEvent(QMouseEvent *event)
{
    setFrameShape(QFrame::NoFrame);
    event->ignore();
}

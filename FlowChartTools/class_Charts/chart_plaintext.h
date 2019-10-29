#ifndef CHART_PLAINTEXT_H
#define CHART_PLAINTEXT_H
#include <QWidget>
#include <QPlainTextEdit>
#include <QMouseEvent>
#include <qDebug>

enum class CHART_TEXT_MOUSE_TYPE{NONE,CHANGE_POS};

class Chart_PlainText : public QPlainTextEdit
{
    Q_OBJECT
private:
    //Chart_Base &parent;
public:
    Chart_PlainText(QWidget *parent = nullptr):QPlainTextEdit(parent){}
    virtual ~Chart_PlainText(){}
    void createText();
    void changeText();

signals:
    void setTypeChangeTextPos(CHART_TEXT_MOUSE_TYPE t,int x,int y);
protected:
    virtual void mousePressEvent(QMouseEvent *event);
    virtual void mouseDoubleClickEvent(QMouseEvent *event);
    virtual void mouseMoveEvent(QMouseEvent *event);
    virtual void mouseReleaseEvent(QMouseEvent *event);

};

#endif // CHART_PLAINTEXT_H

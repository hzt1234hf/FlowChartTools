#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    connect(ui->chart_rect,SIGNAL(clicked()),ui->flowChart_widget,SLOT(setPaintChart_Rect()));
    connect(ui->chart_diam,SIGNAL(clicked()),ui->flowChart_widget,SLOT(setPaintChart_Diamond()));
    connect(ui->chart_roundrect,SIGNAL(clicked()),ui->flowChart_widget,SLOT(setPaintChart_RoundRect()));
    connect(ui->chart_ellipse,SIGNAL(clicked()),ui->flowChart_widget,SLOT(setPaintChart_Ellipse()));
    connect(ui->chart_line,SIGNAL(clicked()),ui->flowChart_widget,SLOT(setPaintChart_Line()));
    connect(ui->chart_trapezoid,SIGNAL(clicked()),ui->flowChart_widget,SLOT(setPaintChart_trapezoid()));

    connect(ui->actionOpenFile,SIGNAL(triggered(bool)),ui->flowChart_widget,SLOT(openChartFile()));
    connect(ui->actionSaveFile,SIGNAL(triggered(bool)),ui->flowChart_widget,SLOT(saveChartFile()));
    connect(ui->actionNewFile,SIGNAL(triggered(bool)),ui->flowChart_widget,SLOT(newChartFile()));

    connect(ui->LineColorButton,SIGNAL(clicked(bool)),this,SLOT(sendSelChartLineColor()));
    connect(ui->FillColorButton,SIGNAL(clicked(bool)),this,SLOT(sendSelChartFillColor()));
    connect(ui->LineWidthCBox,SIGNAL(currentIndexChanged(int)),ui->flowChart_widget,SLOT(setLineWidth(int)));
    connect(ui->LineStartStyleCBox,SIGNAL(currentIndexChanged(int)),ui->flowChart_widget,SLOT(setLineStartStyle(int)));
    connect(ui->LineEndStyleCBox,SIGNAL(currentIndexChanged(int)),ui->flowChart_widget,SLOT(setLineEndStyle(int)));

    connect(ui->flowChart_widget,SIGNAL(sendChartStyle(QPen &, QBrush &)),this,SLOT(setFillStyle(QPen &, QBrush &)));
    connect(ui->flowChart_widget,SIGNAL(sendLineStyle(QPen &, LINE_HEAD_TYPE &, LINE_HEAD_TYPE &)),this,SLOT(setLineStyle(QPen &, LINE_HEAD_TYPE &, LINE_HEAD_TYPE &)));
    connect(ui->flowChart_widget,SIGNAL(disableStyle()),this,SLOT(disableStylePanel()));
    connect(ui->flowChart_widget,SIGNAL(updateWindowTitle(const QString &)),this,SLOT(changeWindowTitle(const QString &)));

    //connect(ui->actionCloseFile,SIGNAL(triggered(bool)),ui->flowChart_widget,SLOT(saveChartFile()));

    //ui->abcdef->setGeometryNew(10,10,200,200);
    //ui->abcdef->update();
    //ui->flowChart_widget->setStyleSheet(QStringLiteral("background-color: rgb(206, 232, 255);"));
    //ui->flowChart_widget->setAttribute(Qt::WA_StyledBackground,true);
    //ui->flowChart_widget->update();
}

MainWindow::~MainWindow()
{
    ui->flowChart_widget->newChartFile();
    delete ui;
}

void MainWindow::setFillStyle(QPen &qp, QBrush &qb)
{
    ui->FillColorGroup->setEnabled(true);
    ui->LineColorGroup->setEnabled(true);
    ui->FillColorButton->setEnabled(true);
    ui->LineColorButton->setEnabled(true);
    ui->LineColorButton->setStyleSheet(QString("QPushButton\
    {\
        background-color:rgb(%1,%2,%3);\
        opacity:1;\
    };"
    ).arg(qp.color().red()).arg(qp.color().green()).arg(qp.color().blue()));
    ui->FillColorButton->setStyleSheet(QString("QPushButton\
    {\
        background-color:rgb(%1,%2,%3);\
        opacity:1;\
    };"
    ).arg(qb.color().red()).arg(qb.color().green()).arg(qb.color().blue()));

}

void MainWindow::setLineStyle(QPen &qp,LINE_HEAD_TYPE &startLineHeadType, LINE_HEAD_TYPE &endLineHeadTypeb)
{
    ui->LineColorGroup->setEnabled(true);
    ui->LineWidthGroup->setEnabled(true);
    ui->LineStartStyleGroup->setEnabled(true);
    ui->LineEndStyleGroup->setEnabled(true);
    ui->LineColorButton->setEnabled(true);
    ui->LineWidthCBox->setEnabled(true);
    ui->LineStartStyleCBox->setEnabled(true);
    ui->LineEndStyleCBox->setEnabled(true);
    ui->LineColorButton->setStyleSheet(QString("QPlainTextEdit\
    {\
        background-color:rgb(%1,%2,%3);\
        opacity:1;\
    }"
    ).arg(qp.color().red()).arg(qp.color().green()).arg(qp.color().blue()));
    ui->LineWidthCBox->setCurrentIndex(qp.width());
    ui->LineStartStyleCBox->setCurrentIndex(int(startLineHeadType));
    ui->LineEndStyleCBox->setCurrentIndex(int(endLineHeadTypeb));
}

void MainWindow::disableStylePanel()
{
    ui->FillColorGroup->setEnabled(false);
    ui->LineColorGroup->setEnabled(false);
    ui->LineWidthGroup->setEnabled(false);
    ui->LineStartStyleGroup->setEnabled(false);
    ui->LineEndStyleGroup->setEnabled(false);
    ui->LineColorButton->setStyleSheet(QString("QPushButton\
    {\
        opacity:0.9;\
    };"));
    ui->FillColorButton->setStyleSheet(QString("QPushButton\
    {\
        opacity:0.9;\
    };"));
}

void MainWindow::sendSelChartLineColor()
{
    QColor color = QColorDialog::getColor(Qt::white,this,tr("设置线条颜色"));
    ui->flowChart_widget->setSelChartLineColor(color);
    ui->LineColorButton->setStyleSheet(QString("QPushButton\
    {\
        background-color:rgb(%1,%2,%3);\
        opacity:1;\
    };"
    ).arg(color.red()).arg(color.green()).arg(color.blue()));
}

void MainWindow::sendSelChartFillColor()
{
    QColor color = QColorDialog::getColor(Qt::white,this,tr("设置填充颜色"));
    ui->flowChart_widget->setSelChartFillColor(color);
    ui->FillColorButton->setStyleSheet(QString("QPushButton\
    {\
        background-color:rgb(%1,%2,%3);\
        opacity:1;\
    };"
    ).arg(color.red()).arg(color.green()).arg(color.blue()));
}
void MainWindow::changeWindowTitle(const QString & title)
{
    QString tmp = QString("比图吧 - %1").arg(title);
    this->setWindowTitle(tmp);
}



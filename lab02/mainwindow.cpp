#include "mainwindow.h"
#include <common.h>
#include <QToolBar>
#include <QColorDialog>
#include <QLabel>
#include <QComboBox>
#include <QSpinBox>
#include <QToolButton>
#include <QDebug>
#include <QLayout>
#include <QPainter>


//构造函数  工具栏和绘图窗口的创建
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
   centerFrame = new CenterFrame;   //新建CenterFrame对象
   setCentralWidget (centerFrame);  //新建的centerFrame->insideWidget()对象作为主窗口的中央窗口
   createToolBar ();                //创建一个工具栏
   setMinimumSize (600, 400);       //设置主窗体的最小尺寸
   setWindowTitle(tr("实验二 - 窗口、控件及基本绘图实验 "));

   penStyleChangged(styleComboBox->currentData().toInt());       //初始化线型，设置控件中当前值作为初始值

   centerFrame->setPenWidth (widthSpinBox->value ());           //设置初始线宽
   centerFrame->setPenColor (FOREGROUND_COLOR);                 //设置初始颜色
}

MainWindow::~MainWindow()
{
}


//创建工具栏按键菜单
void MainWindow::createToolBar ()
{
   QToolBar *toolBar = addToolBar (tr("Tool"));   //为主窗口创建一个工具栏对象

   // 线型选择下拉框
   styleLabel = new QLabel(tr("线型"));
   styleComboBox = new QComboBox;
   styleComboBox->setToolTip(tr("选择画笔线型"));
   // 此处在下拉框的每个Item里，设置了一个item的userData，
   styleComboBox->addItem (tr("实线(SolidLine)"), static_cast<int>(Qt::SolidLine));
   styleComboBox->addItem (tr("虚线(DashLine)"), static_cast<int>(Qt::DashLine));
   styleComboBox->addItem (tr("点线(DotLine)"), static_cast<int>(Qt::DotLine));
   styleComboBox->addItem (tr("点划线(DashDotLine)"), static_cast<int>(Qt::DashDotLine));
   styleComboBox->addItem (tr("连点划线(DashDotDotLine)"), static_cast<int>(Qt::DashDotDotLine));
   connect (styleComboBox, static_cast<void(QComboBox::*)(int)>(&QComboBox::currentIndexChanged),
               this, &MainWindow::penStyleChangged);//（下拉框）信号与（画笔风格）槽绑定

   styleComboBox->setCurrentIndex(1);//初始状态


   // 线宽选择框
   widthLabel = new QLabel(tr("线宽"));
   widthSpinBox = new QSpinBox;
   widthSpinBox->setToolTip(tr("选择画笔线宽"));
   widthSpinBox->setRange(1,50);        //线宽范围
   connect (widthSpinBox, static_cast<void(QSpinBox::*)(int )>(&QSpinBox::valueChanged),
              centerFrame, &CenterFrame::setPenWidth);
   widthSpinBox->setValue(1);

   // 颜色选择框
   colorBtn = new QToolButton;
   QPixmap pixmap(20, 20);
   pixmap.fill (FOREGROUND_COLOR);
   colorBtn->setIcon (QIcon(pixmap));
   colorBtn->setToolTip(tr("选择画笔颜色"));
   connect (colorBtn, &QToolButton::clicked, this, &MainWindow::penColorChangged);

   //  创建清除工具栏
   clearBtn = new QToolButton;
   clearBtn->setText (tr("清除"));
   clearBtn->setToolTip(tr("清除当前画板"));
   connect (clearBtn, &QToolButton::clicked, centerFrame, &CenterFrame::clearPaint);


   //创建图标
   //imageBtn = new QToolButton;

  // 向工具栏上添加各个控件
   toolBar->addWidget (styleLabel);
   toolBar->addWidget (styleComboBox);
   toolBar->addWidget (widthLabel);
   toolBar->addWidget (widthSpinBox);
   toolBar->addWidget (colorBtn);
   toolBar->addSeparator();
   toolBar->addWidget (clearBtn);
   //toolBar->addWidget(imageBtn);
}


//用户选择不同的画笔风格
void MainWindow::penStyleChangged (int index)
{
   Q_UNUSED(index)
   centerFrame->setPenStyle(styleComboBox->currentData().toInt ());
}


//用户选择不同的颜色
void MainWindow::penColorChangged ()
{
   QColor color = QColorDialog::getColor (static_cast<int>(FOREGROUND_COLOR),
                                          this,
                                          tr("选取画笔颜色"));

   //判断颜色是否有效
   if(color.isValid ())
    {
        centerFrame->setPenColor (color);
        QPixmap p(20, 20);
        p.fill (color);
        colorBtn->setIcon (QIcon(p));
    }
}


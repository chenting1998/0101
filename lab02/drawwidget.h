#ifndef DRAWWIDGET_H
#define DRAWWIDGET_H
#include <common.h>
#include <QWidget>
#include <QPixmap>
#include <QPoint>
#include <QPainter>
#include <QPalette>

class DrawWidget : public QWidget
{
   Q_OBJECT
public:
   explicit DrawWidget(QWidget *parent = 0);
    ~DrawWidget();

   void setShapeType(ST::ShapeType type);//设置绘图类型
   ST::ShapeType shapeType();//返回当前绘图类型
   void setDrawnText(QString text);//设置需要绘制的文本

protected:
   void mousePressEvent (QMouseEvent *e);//鼠标点击事件
   void mouseMoveEvent (QMouseEvent *e);//鼠标移动事件
   void mouseReleaseEvent(QMouseEvent *e);//鼠标释放事件
   void paintEvent (QPaintEvent *);//处理绘图事件
   void resizeEvent (QResizeEvent *);//处理窗口大小变化时的resize事件
   void drawShape(const QPointF ptStart,const QPointF ptEnd,const ST::ShapeType drawType);
   //根据起始点、结束点和绘图类型进行绘图
   QRectF textRect(const QPointF ptStart, const QPointF ptEnd, QString displayText, QFontMetrics fm);
//计算绘制文本时所需要的最佳矩形大小

public slots:
   void setStyle(int);
   void setWidth(int);
   void setColor(QColor);
   void clear();
   void drawpic();

private :
   QPixmap *pix;//定义一个画板指针
   QPoint startpos;//绘图起始点
   QPoint endpos;//绘图终点
   bool canDraw;//绘图标志：true:绘制， false:不绘制
   bool bgpic;
   int style;//绘图时使用的画笔风格
   int weight;//绘图时的画笔线宽
   QColor color;//绘图时的画笔颜色
   ST::ShapeType drawType;
   QString drawnText;
   //QPixmap *pic;//定义一个图片指针
   QPixmap ldpix;
  // QString open_fileName;
};
#endif // DRAWWIDGET_H

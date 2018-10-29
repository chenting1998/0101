#include "drawwidget.h"
#include <QMouseEvent>
#include <QPen>
#include <QMessageBox>
#include <QString>
#include <QFileDialog>
#include <QMessageBox>

DrawWidget::DrawWidget(QWidget *parent) : QWidget(parent)
{
    drawType = ST::None;
    canDraw = false;
    setAutoFillBackground (true);   //设置窗体背景色
    setPalette (QPalette(BACKGROUND_COLOR));
    pix = new QPixmap(size());      //此QPixmap对象用来准备随时接受绘制的内容
    pix->fill (BACKGROUND_COLOR);    //填充背景色为白色
    setMinimumSize (600, 400);      //设置绘制区窗体的最小尺寸
    //pic = new QPixmap(size());      //此QPixmap对象用来准备随时接受绘制的内容
    //pic->fill (Qt::KeepAspectRatio);
}

DrawWidget::~DrawWidget()
{
         // 注意：一定要删除pix指针
   delete pix;
   //delete pic;

}

//接收用户选定的画笔风格
void DrawWidget::setStyle (int s)
{
    style = s;
}

//接收用户选定的画笔宽度值
void DrawWidget::setWidth (int w)
{
    weight = w;
}

//接收用户选定的画笔颜色值
void DrawWidget::setColor (QColor c)
{
    color = c;
}


//鼠标点击事件
void DrawWidget::mousePressEvent (QMouseEvent *e)
{
    if(e->button() == Qt::LeftButton){  //左键按下
        startpos = e->pos();//获取起始坐标
        canDraw = true;
    }
}


//鼠标移动事件
void DrawWidget::mouseMoveEvent (QMouseEvent *e)
{

    if ( ! drawType){   //判断是否是绘制任意曲线
        if(canDraw){    //判断是否是绘制任意曲线
            QPainter painter;
            QPen pen;
            pen.setStyle ((Qt::PenStyle)style);
            pen.setWidth (weight);
            pen.setColor (color);
            painter.begin (pix);

            // 抗锯齿必须在painter激活后，也就是绘制对象确定后设置
            painter.setRenderHint(QPainter::Antialiasing);
            painter.setPen (pen);
            painter.drawLine (startpos, e->pos ());
            painter.end ();
            startpos = e->pos ();   //更新鼠标的位置
            update ();//进行绘制
        }
    }
}

//鼠标释放事件
void DrawWidget::mouseReleaseEvent(QMouseEvent *e)
{
    if (e->button() == Qt::LeftButton){
        endpos = e->pos();
        // 起点、终点都有了，那么根据用户要求的图形类别开始画形状
        drawShape(startpos,endpos,drawType);

        // 如果将update函数去掉，那么绘图区将不再更新，除非出现窗口尺寸变化或遮住等情况
        update();
        canDraw = false;//绘图标志，表明本次绘图完成
    }
}




//处理绘图事件
void DrawWidget::paintEvent (QPaintEvent *)
{
    QPainter painter(this);
    painter.drawPixmap (QPoint(0, 0), *pix);
    //painter.drawPixmap (this->width()/4,this->height()/4,this->width()/2,this->height()/2, *pic);
}



//处理窗口大小变化时的resize事件
void DrawWidget::resizeEvent (QResizeEvent *event)
{
   //if(height () > pix->height () || width() > pix->width ())//判断改变窗口的大小是否大于原窗体的长和宽
        QPixmap *newPix = new QPixmap(size());
        newPix->fill (BACKGROUND_COLOR);//填充新QPixmap对象的newPix的颜色为白色背景11q                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                            色
        QPainter p(newPix);
        if(!bgpic){
            p.drawPixmap (QPoint(0, 0), *pix);
            delete pix;     //一定要删除原来的对象，否则会出现内存泄漏
            pix = newPix;  //newPix赋值给pix作为新的绘制图形接收对象
        }
        else{
            QPixmap pic=ldpix.scaled(size(),Qt::KeepAspectRatio);
            p.drawPixmap(QPoint((width()-pic.width())/2,0),pic);
            delete pix;     //一定要删除原来的对象，否则会出现内存泄漏
            pix= newPix;  //newPix赋值给pix作为新的绘制图形接收对象
        }
    QWidget::resizeEvent(event);

}


void DrawWidget::clear ()
{
    pix->fill(BACKGROUND_COLOR);// 清除绘图内容，简单的用背景色填充整个画布即可
    //pic->fill(Qt::transparent);
    update ();
}


void DrawWidget::drawpic()
{
    QString open_fileName;  //获取文件路径
    open_fileName = QFileDialog::getOpenFileName(this,tr("选择图片"), ".",tr("Image Files (*.png *.jpg *.bmp)"));

    if(open_fileName.isEmpty())
    {
        QMessageBox mesg;
        mesg.warning(this,"警告","没有选择图片!");
        return;
    }

    //绘制选择的图片
    pix->load(open_fileName);
    ldpix=*pix;
    bgpic=true;
    QPixmap *newPix=new QPixmap(size());
    newPix->fill (BACKGROUND_COLOR);
    QPainter p(newPix);
    QPixmap pic=pix->scaled(size(),Qt::KeepAspectRatio);
    p.drawPixmap(QPoint((width()-pic.width())/2,0),pic);
    delete pix;
    pix = newPix;
    update();
}


//设置绘图类型
void DrawWidget::setShapeType(ST::ShapeType type)
{
    drawType = type;
}


//返回当前绘图类型
ST::ShapeType DrawWidget::shapeType()
{
   return drawType;
}


//设置需要绘制的文本
void DrawWidget::setDrawnText(QString text)
{
    drawnText = text;
}


//计算绘制文本时所需要的最佳矩形大小
QRectF DrawWidget::textRect(const QPointF ptStart, //用户输入矩形的起始点
                            const QPointF ptEnd, //用户输入矩形的结束点
                            QString displayText, //需要显示的文本
                            QFontMetrics fm     //字体的metrics对象，表示当前字体的几何特征
                            )
{
    // 获取显示字符串需要的Rect
    int pixelsWide = fm.width(displayText);  // 宽度，单位：px
    int pixelsHigh = fm.height();        // 高度，单位：px

   // 起始点和结束点之间的矩形坐标标准化，即左上角->右下角的形式
    QRectF rect=QRectF(ptStart,ptEnd).normalized();
    //qDebug()<<"ori rect"<<rect<<rect.topLeft()<<rect.bottomRight();
    // 将绘制矩形修改为文本需要的矩形大小
    if(rect.width() < pixelsWide)
        rect.setWidth(pixelsWide);
    if(rect.height() < pixelsHigh)
        rect.setHeight(pixelsHigh);

    // 判断矩形是否超出窗口，如果超出窗口则将矩形框限制在窗口内
    qreal xTopLeft;
    qreal yTopLeft;
    qreal xBottomRight;
    qreal yBottomRight;
    // 获取左上角和右下角的坐标值
    rect.getCoords(&xTopLeft,&yTopLeft,&xBottomRight,&yBottomRight);

    // 处理左上角x坐标
    if ( xTopLeft < 0 ) {
        xTopLeft = 0 ;
        // 当左上角x坐标为0时，如果右下角x坐标小于绘制文本所需的宽度，
        // 则将其置为文本绘制最小宽度值
        if(xBottomRight < pixelsWide)
            xBottomRight = pixelsWide;
    }
    // 处理左上角y坐标
    if ( yTopLeft < 0 ) {
        yTopLeft = 0 ;
        // 当左上角y坐标为0时，如果右下角y坐标小于绘制文本所需的高度，
        // 则将其置为文本绘制最小高度值
        if(yBottomRight < pixelsHigh)
            yBottomRight = pixelsHigh;
    }
    // 处理右下角x坐标
    if ( xBottomRight > pix->width() ) {
       xBottomRight = pix->width()-1;
        // 当右下角x坐标为绘图区最大值时，如果矩形宽度小于绘制文本所需的宽度，
        // 则以右下角x坐标为基准，将左上角x坐标置为文本绘制最小宽度值所对应的坐标
        if (xBottomRight-xTopLeft < pixelsWide)
           xTopLeft = xBottomRight-pixelsWide;
    }

    // 处理右下角y坐标
    if ( yBottomRight > pix->height() ) {
       yBottomRight = pix->height()-1;
        // 当右下角y坐标为绘图区最大值时，如果矩形宽度小于绘制文本所需的高度，
       // 则以右下角y坐标为基准，将左上角y坐标置为文本绘制最小高度值所对应的坐标
        if (yBottomRight - yTopLeft < pixelsHigh)
            yTopLeft = yBottomRight-pixelsHigh;
    }

   // 重新设置正确的坐标
    rect.setCoords(xTopLeft,yTopLeft,xBottomRight,yBottomRight);

    return rect;
}



//根据起始点、结束点和绘图类型进行绘图
void DrawWidget::drawShape(const QPointF ptStart,
                           const QPointF ptEnd,
                           const ST::ShapeType drawType
                           )
{
    QPainter painter;

    QPen pen;
    pen.setStyle ((Qt::PenStyle)style);
    pen.setWidth (weight);
    pen.setColor (color);

    painter.begin (pix);
    // 抗锯齿必须在painter激活后，也就是绘制对象确定后设置
    painter.setRenderHint(QPainter::Antialiasing);
    painter.setPen (pen);
    switch (drawType) {
   case ST::Rectangle:
       painter.drawRect(QRectF(ptStart,ptEnd));
        break;
    case ST::Ellipse:
        painter.drawEllipse(QRectF(ptStart,ptEnd));
      break;
    case ST::Line:
       painter.drawLine(ptStart,ptEnd);
       break;
    case ST::Triangle:{
        //三角形的三个顶点
       QPointF point1( (ptStart.x()+ptEnd.x())/2,ptStart.y());
        QPointF point2( ptStart.x(),ptEnd.y());
       QPointF point3( ptEnd);

        QVector<QPointF> points;
        points<<point1<<point2<<point3;

        // 画多边形
       painter.drawPolygon(points);
    }
        break;
    case ST::Text:{

       if(drawnText.isEmpty()){
            QMessageBox::information(this,tr("提示"),tr("请输入需要绘制的文本！"));
        }else{
            QFont font = painter.font();
            font.setPixelSize(32);
            // 计算给定字符串的宽度和高度
            QFontMetrics fm(font);
           painter.setFont(font);

            QRectF rect = textRect(ptStart, ptEnd, drawnText, fm);


            painter.drawText(rect,Qt::AlignCenter,drawnText);
          painter.drawRect(rect);

        }
    }
        break;
    case ST::Diamond:{
              //菱形的四个顶点
              QPointF point4((ptStart.x()+ptEnd.x())/2,ptStart.y());
              QPointF point5(ptStart.x(),(ptStart.y()+ptEnd.y())/2);
              QPointF point6((ptStart.x()+ptEnd.x())/2,ptEnd.y());
              QPointF point7(ptEnd.x(),(ptStart.y()+ptEnd.y())/2);
              QVector<QPointF> pointb;
              pointb<<point4<<point5<<point6<<point7;
              painter.drawPolygon(pointb);
          }
        break;
    default:
        break;
    }

    painter.end ();
}

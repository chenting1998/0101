#ifndef CENTERFRAME_H
#define CENTERFRAME_H
#include <QFrame>
#include <common.h>


class QVBoxLayout;
class QHBoxLayout;
class DrawWidget;
class QGroupBox;
class QPushButton;
class QLineEdit;

class CenterFrame : public QFrame
{
    Q_OBJECT
public:
    explicit CenterFrame(QWidget *parent=0);

    DrawWidget* insideWidget() const;

protected:

    void createUserCommandArea();// 创建用户命令区

    void createUI();// 创建界面

    void updateButtonStatus();//更新按键状态


public slots:
    void setPenStyle(int penStyle);
    void setPenWidth(int width=1);
    void setPenColor(QColor color);
    void clearPaint();//清除当前绘图


protected slots:
    void on_btnRectClicked();
    void on_btnEllipseClicked();
    void on_btnLineClicked();
    void on_btnTriangleClicked();
    void on_btnTextClicked();//绘制文本按钮槽函数
    void on_edtTextEdited(const QString &text);//输入文本响应槽函数
    void on_btnDiamondClicked();//菱形
    void on_btnDrawpicClicked();//图片


private:
    QVBoxLayout* vLayout;
    QHBoxLayout* hLayout;
    DrawWidget* drawWidget;
    QGroupBox* group;
    QPushButton* btnRect;
    QPushButton* btnEllipse;
    QPushButton* btnLine;
    QPushButton* btnTriangle;
    QPushButton* btnText;
    QLineEdit* edtText;
    QPushButton* btnDiamond;
    QPushButton* btnDrawpic;
};

#endif // CENTERFRAME_H


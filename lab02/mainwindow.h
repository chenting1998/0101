#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "centerframe.h"
#include <QMainWindow>

class QLabel;
class QComboBox;
class QSpinBox;
class QToolButton;

class MainWindow : public QMainWindow
{
    Q_OBJECT
public:
    MainWindow(QWidget *parent = 0);
   ~MainWindow();

    void createToolBar();


public slots:
    void penStyleChangged(int index=0);
    void penColorChangged();

private:
    CenterFrame *centerFrame; //用户界面中心窗口
    QLabel *styleLabel;//风格标签
    QComboBox *styleComboBox;//画笔风格下拉框
    QLabel *widthLabel;//线宽标签
    QSpinBox *widthSpinBox;//画笔线宽
    QToolButton *colorBtn;//颜色选择工具栏按键
    QToolButton *clearBtn;//“清除”工具栏按键
    //QToolButton *imageBtn;//插入图片按键
};
#endif // MAINWINDOW_H


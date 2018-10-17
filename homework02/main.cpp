#include <QCoreApplication>
#include <QDebug>
#include <QTextStream>
#include <QFile>
#include<QList>


namespace SK {
enum SortKind{

    col01    =   0x00000001<<0,         //!< 第1列

    col02    =   0x00000001<<1,         //!< 第2列

    col03    =   0x00000001<<2,         //!< 第3列

    col04    =   0x00000001<<3,         //!< 第4列

    col05    =   0x00000001<<4,         //!< 第5列

    col06    =   0x00000001<<5,         //!< 第6列

    col07    =   0x00000001<<6,         //!< 第7列

    col08    =   0x00000001<<7,         //!< 第8列

    col09    =   0x00000001<<8,         //!< 第9列

    col10    =   0x00000001<<9,         //!< 第10列

    col11    =   0x00000001<<10,        //!< 第11列

    col12    =   0x00000001<<11,        //!< 第12列

    col13    =   0x00000001<<12,        //!< 第13列

    col14    =   0x00000001<<13,        //!< 第14列

    col15    =   0x00000001<<14,        //!< 第15列

    col16    =   0x00000001<<15,        //!< 第16列

    col17    =   0x00000001<<16,        //!< 第17列

    col18    =   0x00000001<<17,        //!< 第18列

    col19    =   0x00000001<<18,        //!< 第19列

    col20    =   0x00000001<<19,        //!< 第20列

    col21    =   0x00000001<<20,        //!< 第21列

    col22    =   0x00000001<<21,        //!< 第22列

    col23    =   0x00000001<<22,        //!< 第23列

    col24    =   0x00000001<<23,        //!< 第24列

    col25    =   0x00000001<<24,        //!< 第25列

    col26    =   0x00000001<<25,        //!< 第26列

    col27    =   0x00000001<<26,        //!< 第27列

    col28    =   0x00000001<<27,        //!< 第28列

    col29    =   0x00000001<<28,        //!< 第29列

    col30    =   0x00000001<<29,        //!< 第30列

    col31    =   0x00000001<<30,        //!< 第31列

    col32    =   0x00000001<<31,        //!< 第32列

};
}

//定义学生数据结构体
typedef struct{
     QStringList stud;
} studData;


//运算符重载函数，使其可以直接输出studData结构
QDebug operator<<(QDebug d, const studData &data){
    for(int i=0;i<data.stud.size();i++)
    {
        d<<data.stud.at(i);
    }
    qDebug()<<""<<endl;
    return d;
}

//比较类，用于std::sort第三个参数
class myCmp {
public:
    myCmp(int selectedColumn){ this->currentColumn = selectedColumn;}
    bool operator()(const studData& d1,const studData& d2);
private:
    int currentColumn;
};
bool myCmp::operator()(const studData &d1, const studData &d2)
{
    bool result = false;
    quint32 sortedColumn = 0x00000001<<currentColumn;
    switch (sortedColumn) {
    default: result=(d1.stud.at(currentColumn+1)>=d2.stud.at(currentColumn+1));break;
    }
    return result;
}


class ScoreSorter
{
public:
    ScoreSorter(QString dataFile);
    void readFile();
    void doSort();
private:
    QString filename;
    QList<studData> data;
    QStringList title;
};

ScoreSorter::ScoreSorter(QString dataFile)
{
    filename=dataFile;
}

void ScoreSorter::readFile()
{
    QFile file(filename);
    if(!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
            qDebug()<<"文件无法打开"<<endl;
       }
    QString titi=file.readLine();
    title=titi.split(" ", QString::SkipEmptyParts);
    studData tempdata;
    while(!file.atEnd()){
        QString str(file.readLine());
        tempdata.stud=str.split(" ", QString::SkipEmptyParts);
        if((tempdata.stud).last() == "\n")
            tempdata.stud.removeLast();
        if(tempdata.stud.size()==0)
            continue;
        data.append(tempdata);
    }
    file.close();
    qDebug()<<"文件读取完成"<<endl;
    qDebug()<<title;
}

void ScoreSorter::doSort()
{
    for(int i=1;i<title.size();i++){
     myCmp cmp_temp(i-1);//从左移0位开始
     std::sort(data.begin(),data.end(),cmp_temp);
     qDebug()<<"排序后输出，当前排序第 "<<i<<" 列："<<"\n";
     qDebug()<<title;
     for(int i=0;i<data.size();i++)
        qDebug()<<data.at(i);
     qDebug()<<"-------------------------------------------------\n";
    }
}


int main()
{
    QString datafile = "C:/Users/admin/Documents/homework02/data.txt";//data.txt文件路径
    ScoreSorter s(datafile);
    s.readFile();
    s.doSort();
    return 0;
}

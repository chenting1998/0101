#include <QCoreApplication>
#include <QDebug>
#include <iostream>
#include <QString>
#include <algorithm>
#include <QList>

using namespace std;
struct students{
    int num;
    int class1;
    int class2;
    QString name;
};

void Students(QList<students> &qli,int num,QString name, int class1, int class2){
    students stu;
    stu.num=num;
    stu.name=name;
    stu.class1=class1;
    stu.class2=class2;
    qli.push_back(stu);
}
bool sortname(const students &s1,const students &s2){
    return s1.name > s2.name;
}                                      //按姓名排序
bool sortclass1(const students &s1,const students &s2){
    return s1.class1 > s2.class1;
}                                      //按课程1成绩降序排序
bool sortclass2(const students &s1,const students &s2){
    return s1.class2 > s2.class2;
}                                      //按课程2成绩降序排序

int main(){
    QList<students> qli;
    Students(qli,1403130209,"鲁智深",80,72);
    Students(qli,1403140101,"林冲",82,76);
    Students(qli,1403140102,"宋江",76,85);
    Students(qli,1403140103,"武松",88,80);
    qDebug()<< "排序前:" << endl;
    for(QList<students>::iterator iter = qli.begin(); iter != qli.end(); ++iter){
        qDebug()<<(*iter).num<<" "<< (*iter).name<<" "<< (*iter).class1<< " "<< (*iter).class2 << endl;
    }
    sort(qli.begin(),qli.end(),sortname);
    qDebug()<< "按姓名排序后:" << endl;
    for(QList<students>::iterator iter = qli.begin(); iter != qli.end(); ++iter){
        qDebug()<<(*iter).num<<" "<< (*iter).name<<" "<< (*iter).class1<< " "<< (*iter).class2 << endl;
    }
    sort(qli.begin(),qli.end(),sortclass1);
    qDebug()<<"按课程1成绩降序排序后:"<< endl;
    for(QList<students>::iterator iter = qli.begin(); iter != qli.end(); ++iter){
        qDebug()<<(*iter).num<<" "<< (*iter).name<<" "<< (*iter).class1<< " "<< (*iter).class2 << endl;
    }
    sort(qli.begin(),qli.end(),sortclass2);
    qDebug()<< "按课程2成绩降序排序后:" << endl;
    for(QList<students>::iterator iter = qli.begin(); iter != qli.end(); ++iter){
        qDebug()<<(*iter).num<<" "<< (*iter).name<<" "<< (*iter).class1<< " "<< (*iter).class2 << endl;
    }
}


#include<QDebug>
typedef quint8 byte;
typedef quint32 word;
#define  LLO(xxx)  ((byte) ((word)(xxx)&255))
#define  HLO(xxx)  ((byte) ((word)(xxx)>>8))
#define  LHI(xxx)  ((byte) ((word)(xxx)>>16))
#define  HHI(xxx)  ((byte) ((word)(xxx)>>24))
#define  MAX(a,b)  (((a)>(b))?(a):(b))
#define  MIN(a,b)  (((a)<(b))?(a):(b))
int main()
{
    quint32 i=0x12345678;
    QList<quint8> vaules;
    vaules<<HHI(i)<<LHI(i)<<HLO(i)<<LLO(i);//取出最高8位（HHL）、次高8位（LHI）、次低8位（HLO）、最低8位（LLO）并将结果存入vaules中
    qDebug("原始值：0x%x==%d",i,i);// 输出数字并转化为10进制
    qDebug("0x%x==%d  0x%x==%d  0x%x==%d  0x%x==%d",HHI(i),HHI(i),LHI(i),LHI(i),HLO(i),HLO(i),LLO(i),LLO(i));//用16进制和10进制输出最高8位（HHL）、次高8位（LHI）、次低8位（HLO）、最低8位（LLO）
    qDebug("最高8位和次高8位的最大值：0x%x==%d",MAX(HHI(i),LHI(i)),MAX(HHI(i),LHI(i)));//输出最高8位和次高8位的最大值
    qDebug("次低8位和最低8位的最小值：0x%x==%d",MIN(HLO(i),LLO(i)),MIN(HLO(i),LLO(i)));//输出次低8位和最低8位的最小值
    quint32 t=(LHI(i)&0xff)<<0|(LLO(i)&0xff)<<8|(HHI(i)&0xff)<<16|(HLO(i)&0xff)<<24;//组合成一个新的32位无符号整形数，其从高到低分别为原次低8位、最高8位、最低8位和次高8位
    qDebug("重组后的数字：0x%x==%d",t,t);//用16进制和10进制分别输出该数字
    qDebug()<<"排序前："<<vaules;//输出排序前的vaules数组
    std::sort(vaules.begin(),vaules.end(),std::greater<quint8>());//将vaules中的数字按照从大到小排序
    qDebug()<<"排序后："<<vaules;//输出排序后的vaules数字
    return 0;
}


#ifndef DECODE_H
#define DECODE_H
#include <QByteArray>



class decode
{
public:
    decode(QByteArray data);
    QByteArray decode_data(){return deal_data();}
private:
    bool check_data();//检查数据是否正确
    QByteArray first_deal_data();//初步处理，将其转为
    QByteArray deal_data();//对数据处理
    QByteArray _data;
};

#endif // DECODE_H


#include "decode.h"

decode::decode(QByteArray data)
{
    _data = data;
}

bool decode::check_data()
{

    return true;
}

QByteArray decode::deal_data()
{
    int n = _data.size();
    for(int i = 0; i < n-5; i++)
    {
        if(_data[i] == ' ')
            continue;
        if(_data[i] == 'a' || _data[i] == 'A'){
            if(_data[i+1] == 'a' || _data[i+1] == 'A'){
               // if()
            }
        }
    }
}


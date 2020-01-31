#ifndef SR_RECIVER_H
#define SR_RECIVER_H

#include <RdtReceiver.h>
#include <vector>
#include "SRSetting.h"

class SRReceiver : public RdtReceiver
{
private:
    int base;// 接收窗口基
    Packet AckPkt;//确认报文
    std::vector<Packet> q;//缓存队列


public:
    SRReceiver();
    ~SRReceiver();


public:
    void receive(const Packet &packet);	//接收报文，将被NetworkService调用
};
#endif //SR_RECIVER_H

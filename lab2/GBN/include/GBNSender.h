
#ifndef GDB_GBNSENDER_H
#define GDB_GBNSENDER_H

#include "RdtSender.h"
#include <vector>

class GBNSender : public RdtSender
{

private:
    int nextseqnum;	// 下一个发送序号
    bool waitingState;// 为1时，窗口满，处于等待状态
    int base;//窗口基序号
    std::vector<Packet> q;//窗口中的packet的队列

public:
    GBNSender();
    virtual ~GBNSender();
public:
    bool send(const Message &message) ;						//发送应用层下来的Message，由NetworkService调用,如果发送方成功地将Message发送到网络层，返回true;如果因为发送方处于等待确认状态或发送窗口已满而拒绝发送Message，则返回false
    void receive(const Packet &ackPkt) ;						//接受确认Ack，将被NetworkService调用
    void timeoutHandler(int seqNum) ;					//Timeout handler，将被NetworkService调用
    bool getWaitingState() ;
};


#endif //GDB_GBNSENDER_H

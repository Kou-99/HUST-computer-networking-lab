
#ifndef SR_GBNSENDER_H
#define SR_GBNSENDER_H

#include "RdtSender.h"
#include <vector>

class SRSender : public RdtSender
{

private:
    int nextseqnum;	// 下一个发送序号
    bool waitingState;// 为1时，窗口满，处于等待状态
    int base;//窗口基序号
    std::vector<Packet> q;//窗口中的packet的队列
    std::vector<Packet> ready;//已收到过ack的队列

public:
    SRSender();
    virtual ~SRSender();
public:
    bool send(const Message &message) ;						//发送应用层下来的Message，由NetworkService调用,如果发送方成功地将Message发送到网络层，返回true;如果因为发送方处于等待确认状态或发送窗口已满而拒绝发送Message，则返回false
    void receive(const Packet &ackPkt) ;						//接受确认Ack，将被NetworkService调用
    void timeoutHandler(int seqNum) ;					//Timeout handler，将被NetworkService调用
    bool getWaitingState() ;
};


#endif //GDB_GBNSENDER_H

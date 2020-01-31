#include "TCPSender.h"
#include "Global.h"
#include "TCPSetting.h"

TCPSender::TCPSender(): waitingState(false), base(0), nextseqnum(0),redundent(0),reduAck(0){
    //初始化
}

TCPSender::~TCPSender()=default;

bool TCPSender::getWaitingState() {
    return waitingState;
}

bool TCPSender::send(const Message &message) {
    if (this->waitingState) {
        return false;//等待状态不发送
    }

    if(((this->nextseqnum+SEQ_LENGTH-this->base)%SEQ_LENGTH)==WINDOW_LENGTH-1)
        this->waitingState=true;//当前要发送的packet为窗口中最后一个时，将等待状态置为true

    Packet* newPacket=(Packet *)malloc(sizeof(Packet));
    newPacket->acknum = -1; //发送packet时，acknum统一为-1
    newPacket->seqnum = this->nextseqnum;
    newPacket->checksum = 0;
    memcpy(newPacket->payload, message.data, sizeof(message.data));
    newPacket->checksum = pUtils->calculateCheckSum(*newPacket);
    pUtils->printPacket("发送方发送报文", *newPacket);

    this->q.push_back(*newPacket);//newPacket加入窗口队列
    if(this->nextseqnum==this->base)
        pns->startTimer(SENDER, Configuration::TIME_OUT,newPacket->seqnum);//启动发送方定时器
    pns->sendToNetworkLayer(RECEIVER, *newPacket);//调用模拟网络环境的sendToNetworkLayer，通过网络层发送到对方

    this->nextseqnum=add(this->nextseqnum);//nextseqnum指向下一个序号
    free(newPacket);
    return true;
}

void TCPSender::receive(const Packet &ackPkt) {
    cout<<"TCPSender::receive called, window: ";//输出窗口信息
    for(auto iter=this->q.begin();iter!=q.end();++iter)
        cout<<iter->seqnum<<" ";
    cout<<endl;

    int checkSum = pUtils->calculateCheckSum(ackPkt);//计算校验和
    if (checkSum == ackPkt.checksum)//校验和正确
    {
        auto iter=this->q.begin();
        for(;iter!=q.end();++iter)//判断收到的ack是否在队列中
        {
            if(iter->seqnum==ackPkt.acknum)
                break;
        }
        if(iter!=q.end())//等待ack队列中某个packet的被ack
        {
            pns->stopTimer(SENDER, this->q.begin()->seqnum);//关闭计时器
            q.erase(this->q.begin(),iter+1);//删除被ack的包及之前的包
            this->base=add(ackPkt.acknum);//更新base
            cout<<"window moved, new base: "<<base<<endl;
            if(!q.empty())//窗口中还有未被ack的包，则为第一个未ack的包开始计时
                pns->startTimer(SENDER, Configuration::TIME_OUT, this->q.begin()->seqnum);
            if(this->waitingState)
                this->waitingState=false;//队列停止等待
            pUtils->printPacket("发送方正确收到确认", ackPkt);
        }
        else//收到的ack不在队列中，为冗余ack
        {
            pUtils->printPacket("收到冗余ack", ackPkt);
            if(ackPkt.acknum==reduAck)//是曾经收到过的冗余ack
            {
                if(this->redundent==2)
                {
                    pUtils->printPacket("收到3个冗余ack，快速重传如下的packet", *q.begin());
                    //重启计时器
                    pns->stopTimer(SENDER, this->q.begin()->seqnum);
                    pns->startTimer(SENDER, Configuration::TIME_OUT, this->q.begin()->seqnum);
                    //重传第一个packet
                    pns->sendToNetworkLayer(RECEIVER, *q.begin());
                    this->redundent=0;
                }
                else
                {
                    this->redundent+=1;
                    cout<<"这是"<<reduAck<<"的第"<<redundent<<"个冗余ack"<<endl;
                }
            }
            else//未收到过的冗余ack
            {
                reduAck=ackPkt.acknum;
                redundent=1;
                cout<<"这是"<<reduAck<<"的第"<<redundent<<"个冗余ack"<<endl;
            }


        }
    }
    else
        pUtils->printPacket("发送方没有正确收到确认", ackPkt);
}

void TCPSender::timeoutHandler(int seqNum) {
    pns->stopTimer(SENDER,seqNum);//关闭定时器
    pns->startTimer(SENDER, Configuration::TIME_OUT,seqNum);//重新启动发送方定时器
    pUtils->printPacket("发送方定时器时间到，重发窗口中第一个报文", *q.begin());
    pns->sendToNetworkLayer(RECEIVER, *q.begin());
}
#include "SRSender.h"
#include "Global.h"
#include "SRSetting.h"

SRSender::SRSender(): waitingState(false), base(0), nextseqnum(0){
    //初始化
}

SRSender::~SRSender()=default;

bool SRSender::getWaitingState() {
cout<<"getWaitingState被调用，返回： "<<this->waitingState<<endl;
    return this->waitingState;
}

bool SRSender::send(const Message &message) {
    if (this->waitingState) {
cout<<"SR发送方返回窗口满不能发送"<<endl;
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
    pns->startTimer(SENDER, Configuration::TIME_OUT,newPacket->seqnum);//对每个packet启动发送方定时器
    pns->sendToNetworkLayer(RECEIVER, *newPacket);//调用模拟网络环境的sendToNetworkLayer，通过网络层发送到对方

    this->nextseqnum=add(this->nextseqnum);//nextseqnum指向下一个序号
    free(newPacket);
    return true;
}

void SRSender::receive(const Packet &ackPkt) {
    int checkSum = pUtils->calculateCheckSum(ackPkt);//计算校验和

pUtils->printPacket("收到的ack", ackPkt);
cout<<"sender::receive q: ";
for(auto iter=q.begin();iter!=q.end();++iter){
    cout<<iter->seqnum<<" ";
}
cout<<endl<<"ready: ";
for(auto iter=ready.begin();iter!=ready.end();++iter){
    cout<<iter->seqnum<<" ";
}
cout<<endl;

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
            pns->stopTimer(SENDER, ackPkt.acknum);//关闭计时器

            //将收到ack的packet从q中删除，并插入ready中正确的位置
            auto iter2=ready.begin();
            if(ready.empty()){
                ready.insert(ready.begin(),*iter);
                q.erase(iter);
            }
            else{
                for(;iter2!=ready.end();++iter2){
                    if(modSeqGreater(iter2->seqnum,ackPkt.acknum,this->base))
                        break;
                }
                ready.insert(iter2,*iter);
                q.erase(iter);
            }


            if(base==(ready.begin()->seqnum))//出现有序ack，窗口可以开始滑动
            {
                for(iter2=ready.begin();iter2!=ready.end();)//循环将所有连续ack出队
                {
                    if(base==(iter2->seqnum))
                    {
cout<<iter2->seqnum<<' ';
                        ready.erase(iter2);
                        base=add(base);
cout<<"erased ";
                    }
                    else{
                        break;
                    }
                }
cout<<endl<<"window moved, base: "<<base<<endl;
                if(this->waitingState)
                    this->waitingState=false;//队列停止等待
            }
            pUtils->printPacket("发送方正确收到确认", ackPkt);
        }
        else
            pUtils->printPacket("发送方收到的ack不在队列q中", ackPkt);
            //收到的ack不在队列中，则不做任何事情
    }
    else
        pUtils->printPacket("发送方没有正确收到确认", ackPkt);
}

void SRSender::timeoutHandler(int seqNum) {
    pns->stopTimer(SENDER,seqNum);//关闭定时器
    pns->startTimer(SENDER, Configuration::TIME_OUT,seqNum);//重新启动发送方定时器

    auto iter=q.begin();
    for(;iter->seqnum!=seqNum;iter++);//找到要重发的报文
    pUtils->printPacket("发送方定时器时间到，重发某一报文", *iter);
    pns->sendToNetworkLayer(RECEIVER, *iter);
}
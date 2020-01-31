#include "SRReceiver.h"
#include "Global.h"
#include "SRSetting.h"

SRReceiver::SRReceiver(): base(0) {
    AckPkt.acknum = -1; //初始状态下，上次发送的确认包的确认序号为-1，使得当第一个接受的数据包出错时该确认报文的确认号为-1
    AckPkt.checksum = 0;
    AckPkt.seqnum = -1;	//忽略该字段
    for(int i = 0; i < Configuration::PAYLOAD_SIZE;i++){
        AckPkt.payload[i] = '.';
    }
}

SRReceiver::~SRReceiver()= default;

void SRReceiver::receive(const Packet &packet) {
    int checkSum = pUtils->calculateCheckSum(packet);

//pUtils->printPacket("收到的packet", packet);
//    cout<<"receive called q size ="<<q.size()<<": ";
//for(auto iter0=q.begin();iter0!=q.end();++iter0){
//    cout<<iter0->seqnum;
//}
//cout<<endl;

    if (checkSum == packet.checksum)//校验和正确
    {
        //判断是否在[base-N，base+N-1]中
        bool inRange;
        bool upperhalf=false;
        int upper=base+WINDOW_LENGTH-1;
        int lower=base-WINDOW_LENGTH;
        if(upper>SEQ_LENGTH-1)
        {
            inRange = (packet.seqnum >= lower) || (packet.seqnum <= (upper - SEQ_LENGTH));
            if(inRange)
            {
                upperhalf = !((packet.seqnum >= lower) && (packet.seqnum < base));
            }
        }
        else if(lower<0)
        {
            inRange = (packet.seqnum<=upper) || (packet.seqnum>=(lower+SEQ_LENGTH));
            if(inRange)
            {
                upperhalf = (packet.seqnum <= upper) && (packet.seqnum>= base);
            }
        }
        else
        {
            inRange = (packet.seqnum>=lower)&&(packet.seqnum<=upper);
            if(inRange)
            {
                upperhalf = (packet.seqnum <= upper) && (packet.seqnum>= base);
            }
        }
        if(inRange)
        {
            if(upperhalf)//[base,base+WINDOW_LEN-1]
            {
                //首先判断收到的报文是否已经被缓存
                bool inQue=false;
                for(auto iter=q.begin();iter!=q.end();++iter)
                {
                    if(iter->seqnum==packet.seqnum)
                    {
                        inQue=true;
                        break;
                    }
                }
                if (packet.seqnum == base)//有序
                {
                    if(inQue)
                    {
                        pUtils->printPacket("接收方有序收到已缓存的发送方报文", packet);
                    }
                    else
                    {
                        pUtils->printPacket("接收方有序收到发送方的报文", packet);
                        q.insert(q.begin(), packet);
                    }
                    Message msg;

                    if(q.size()>WINDOW_LENGTH)
                        q.size();

                    for (auto iter = q.begin(); iter != q.end(); base = add(base)) {
                        if (iter->seqnum == base)//有序时连续提交
                        {
                            memcpy(msg.data, iter->payload, sizeof(packet.payload));
                            pns->delivertoAppLayer(RECEIVER, msg);
                            q.erase(iter);
                        }
                        else//失序时退出循环
                            break;
                    }
                }
                else//失序
                {
                    if(inQue)
                    {
                        pUtils->printPacket("接收方无序收到已缓存的发送方报文", packet);
                    }
                    else
                    {
                        auto iter = q.begin();
                        for (; iter != q.end(); iter++) {
                            if (modSeqGreater(iter->seqnum,packet.seqnum,this->base))//缓存按序号由小到大排列
                                break;
                        }
                        q.insert(iter, packet);
                        pUtils->printPacket("接收方无序收到发送方的报文", packet);
                    }
                }
            }
            else
                pUtils->printPacket("接收方收到在范围[base-N,base-1]内的报文", AckPkt);
            this->AckPkt.acknum=packet.seqnum;//确认序号等于收到的报文序号
            this->AckPkt.checksum=pUtils->calculateCheckSum(AckPkt);
            pUtils->printPacket("接收方发送确认报文", AckPkt);
            pns->sendToNetworkLayer(SENDER, AckPkt);//调用模拟网络环境的sendToNetworkLayer，通过网络层发送确认报文到对方
        }
        else
            pUtils->printPacket("接收方收到发送方的报文超出范围,不做任何响应", packet);;//不在范围内则不做任何处理
    }
    else //校验和错误
    {
        pUtils->printPacket("接收方没有正确收到发送方的报文,数据校验错误", packet);
        //不做确认处理
    }
}

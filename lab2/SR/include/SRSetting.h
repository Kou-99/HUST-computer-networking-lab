
#ifndef SR_GBNSETTING_H
#define SR_GBNSETTING_H

#define WINDOW_LENGTH 4
#define SEQ_LENGTH 16

inline int add(int num){
    return (num==SEQ_LENGTH-1)?0:(num+1);
}

//true if a>b
inline bool modSeqGreater(int a,int b,int base){
    if(base+WINDOW_LENGTH-1>SEQ_LENGTH-1){
        if(a+SEQ_LENGTH<base+WINDOW_LENGTH)
            a+=SEQ_LENGTH;
        if(b+SEQ_LENGTH<base+WINDOW_LENGTH)
            b+=SEQ_LENGTH;
        return a>b;
    }
    else if(base-WINDOW_LENGTH<0){
        if(a-SEQ_LENGTH>=base-WINDOW_LENGTH)
            a-=SEQ_LENGTH;
        if(b-SEQ_LENGTH>=base-WINDOW_LENGTH)
            b-=SEQ_LENGTH;
        return a>b;
    }
    else
        return a>b;
}

#endif //GBN_GBNSETTING_H

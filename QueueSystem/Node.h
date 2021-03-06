//  
//  Node.h
//  QueueSystem
//
//  Create by Euryugasaki on 2014-03-24.
//  Copyright (c) 2014 Euryugasaki. All rights reserved.
// 

#ifndef __NODE_H_
#define __NODE_H_

typedef struct Node
{
    int arrive_time;    // 到达时间
    int duration;       // 服务时间,办理完事物所需要的时间
    struct Node *next;
} Node, Customer;       // 顾客也是队列中的一个节点

#endif
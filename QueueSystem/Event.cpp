//  
//  Event.cpp
//  QueueSystem
//
//  Create by Euryugasaki on 2014-03-24.
//  Copyright (c) 2014 Euryugasaki. All rights reserved.
// 

#include "Event.h"
#include "Random.h"
#include <iostream>

void initEventList(Event* &eventList)
{
    eventList = new Event;
    if (!eventList)
        exit(-1);
    eventList->next = NULL;

    Event event;
    event.occur_time = getPoisson(30); // 第一个事件发生的时间是随机的，服从泊松分布
    event.event_type = -1;             // 第一个事件肯定是到达事件
    event.next = NULL;
    orderInsert(eventList, event);     // 将第一个事件插入事件链表
}

// 插入事件
void orderInsert(Event* &eventList, Event &event)
{
    Event* temp_event;
    temp_event = new Event;
    if (!temp_event)
        exit(-1);
    temp_event->occur_time = event.occur_time;
    temp_event->event_type = event.event_type;
    temp_event->next = NULL;

    // 如果eventList里面是没有事件的话，那么我们需要把temp_event直接插入
    if (!eventList->next)
    {
        eventList->next = temp_event;
        return;
    }

    // 按照时间顺序来进行插入
    Event *temp_event_list = eventList;
    // 如果有下一个事件，且下一个事件的发生时间小于要插入事件的发生时间，则继续后移指针
    while (temp_event_list->next && temp_event_list->next->occur_time < event.occur_time)
    {
        temp_event_list = temp_event_list->next;
    }
    // 将事件插入
    temp_event->next = temp_event_list->next;
    temp_event_list->next = temp_event;

}

void deleteFirstEvent(Event* &eventList)
{
    Event *temp;
    temp = eventList->next;
    eventList->next = temp->next;
    delete temp;
}

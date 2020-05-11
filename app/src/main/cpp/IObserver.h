//
// Created by Administrator on 2020/4/28.
//

#ifndef YPLAYER_IOBSERVER_H
#define YPLAYER_IOBSERVER_H
#include<list>
#include <vector>
#include "IObserver.h"
#include "XData.h"
#include "XThread.h"

class IObserver : public XThread{
public:
    void addObserver(IObserver *observer);
    void notify(XData *data);
    virtual void update(XData *data) {};
private:
    //  std::list<IObserver*> m_observers;
    std::vector<IObserver*> m_observers;
};


#endif //YPLAYER_IOBSERVER_H

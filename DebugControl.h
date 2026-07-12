#pragma once
#include"Config.h"
#include <AsyncTCP.h>
class DebugControl{
    //Global status broadcast
    public:
    DebugControl(){}
    ~DebugControl(){}
    void broadcastStatus(String type, String message);
    void broadcastStatus(String count);
};
extern DebugControl DebugStatus;
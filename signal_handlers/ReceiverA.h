#ifndef _RECEIVER_A_
#define _RECEIVER_A_

#include "signals.h"
#include "SignalReceiver.h"

class ReceiverA : public SignalReceiver
{
  public:
    
    explicit ReceiverA(SignalDispatcher& signalDispatcher);
    
    void receiveSignal(SIGNAL* signal);
    
  private:
    
    void handleSomeSignalRequest(const SomeSignalReq& request);
    void handleWhateverRequest(const WhateverReq& request);
};

#endif // _RECEIVER_A_

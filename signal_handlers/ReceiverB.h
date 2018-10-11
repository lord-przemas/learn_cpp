#ifndef _RECEIVER_B_
#define _RECEIVER_B_

#include "signals.h"
#include "SignalReceiver.h"

class ReceiverB : public SignalReceiver
{
  public:
    
    explicit ReceiverB(SignalDispatcher& signalDispatcher);
    
    void receiveSignal(SIGNAL* signal);
    
  private:
    
    void handleBlablaSignalRequest(const BlablaSignalReq& request);
};

#endif // _RECEIVER_B_

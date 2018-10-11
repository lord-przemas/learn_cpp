#ifndef _SIGNAL_RECEIVER_
#define _SIGNAL_RECEIVER_

#include <unordered_map>

union SIGNAL;
class SignalDispatcher;


class SignalReceiver
{
  public:
    
    virtual ~SignalReceiver() = default;
    
    virtual void receiveSignal(SIGNAL* signal) = 0;
};


class SignalDispatcher
{
  public:
      
    void subscribe(uint32_t sigNo, SignalReceiver* receiver);
    void dispatchSignal(SIGNAL* signal) const;
    virtual ~SignalDispatcher();
    
  private:
    
    std::unordered_map<uint32_t, SignalReceiver*> recTable;
};

#endif // _SIGNAL_RECEIVER_

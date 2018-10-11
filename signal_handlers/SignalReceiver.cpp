#include "SignalReceiver.h"

union SIGNAL
{
    uint32_t sigNo;
};

void SignalDispatcher::subscribe(uint32_t sigNo, SignalReceiver* receiver)
{
  recTable.insert(std::pair<uint32_t, SignalReceiver*>(sigNo, receiver));
}

void SignalDispatcher::dispatchSignal(SIGNAL* signal) const
{  
  try
  {
    SignalReceiver *receiver = recTable.at(signal->sigNo);
    receiver->receiveSignal(signal);
  }
  catch(std::out_of_range& err)
  {
    printf("Error: Uknown signal id: %u\n", signal->sigNo);
  }
}
SignalDispatcher::~SignalDispatcher()
{}

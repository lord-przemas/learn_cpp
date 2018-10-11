#include "ReceiverA.h"

ReceiverA::ReceiverA(SignalDispatcher& signalDispatcher)
{
  signalDispatcher.subscribe(SIG_SOME_SIGNAL_REQ, this);
  signalDispatcher.subscribe(SIG_WHATEVER_REQ, this);
}

void ReceiverA::receiveSignal(SIGNAL* signal)
{
  printf("----------------------------------\n");
  printf("received Signal -> ");
  
  switch (signal->sigNo)
  {
    case SIG_SOME_SIGNAL_REQ:
      handleSomeSignalRequest(signal->someSignalReq);
      break;
      
    case SIG_WHATEVER_REQ:
      handleWhateverRequest(signal->whateverReq);
      break;
  }
}

void ReceiverA::handleSomeSignalRequest(const SomeSignalReq& request)
{
  printf("ReceiverA::handleSomeSignalRequest\n");

  printf("SomeSignalReq::sigNo: %x\n", request.sigNo);
  printf("SomeSignalReq::value: %u\n", request.value);
  printf("SomeSignalReq::liczba: %llu\n", request.liczba);
  printf("SomeSignalReq::dupa: %c\n", request.dupa);
}

void ReceiverA::handleWhateverRequest(const WhateverReq& request)
{
  printf("ReceiverA::handleWhateverRequest\n");
  
  printf("WhateverReq::sigNo: %x\n", request.sigNo);
  printf("WhateverReq::value: %u\n", request.value);
  printf("WhateverReq::liczba: %llu\n", request.liczba);
  printf("WhateverReq::dupa: %u\n", request.dupa);
}

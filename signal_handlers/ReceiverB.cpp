#include "ReceiverB.h"

ReceiverB::ReceiverB(SignalDispatcher& signalDispatcher)
{
  signalDispatcher.subscribe(SIG_BLABLA_SIGNAL_REQ, this);
}

void ReceiverB::receiveSignal(SIGNAL* signal)
{
  printf("----------------------------------\n");
  printf("received Signal -> ");
  
  switch (signal->sigNo)
  {
    case SIG_BLABLA_SIGNAL_REQ:
      handleBlablaSignalRequest(signal->blablaSignalReq);
      break;
  }
}

void ReceiverB::handleBlablaSignalRequest(const BlablaSignalReq& request)
{
  printf("ReceiverB::handleBlablaSignalRequest\n");

  printf("BlablaSignalReq::sigNo: %x\n", request.sigNo);
  printf("BlablaSignalReq::value: %u\n", request.value);
  printf("BlablaSignalReq::liczba: %d\n", request.liczba);
  printf("BlablaSignalReq::chuj: %s\n", request.chuj);
}


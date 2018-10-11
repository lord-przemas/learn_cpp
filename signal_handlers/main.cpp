#include <cstdio>
#include <cstring>
#include "signal.h"
#include "SignalReceiver.h"
#include "ReceiverA.h"
#include "ReceiverB.h"



int main()
{  

  // Some examples of signals
  SIGNAL* sig[3] {
    (SIGNAL*)malloc(sizeof(SomeSignalReq)),
    (SIGNAL*)malloc(sizeof(BlablaSignalReq)),
    (SIGNAL*)malloc(sizeof(WhateverReq))
  };

  sig[0]->someSignalReq.sigNo = SIG_SOME_SIGNAL_REQ;
  sig[0]->someSignalReq.value = 1918;
  sig[0]->someSignalReq.liczba = 987654321987654321;
  sig[0]->someSignalReq.dupa = 'A';
  
  sig[1]->blablaSignalReq.sigNo = SIG_BLABLA_SIGNAL_REQ;
  sig[1]->blablaSignalReq.value = 2354;
  sig[1]->blablaSignalReq.liczba = 457547;
  strcpy(sig[1]->blablaSignalReq.chuj, "Hello World!");

  sig[2]->whateverReq.sigNo = SIG_WHATEVER_REQ;
  sig[2]->whateverReq.value = 123456;
  sig[2]->whateverReq.liczba = 36756434453463634;
  sig[2]->whateverReq.dupa = -9876543;

//*********** MAIN *************** 

  SignalDispatcher dispatcher;
  ReceiverA receiverA(dispatcher);
  ReceiverB receiverB(dispatcher);
  
  for(auto s : sig)
    dispatcher.dispatchSignal(s);
  
//********************************** 

  for(auto s : sig)
    free(s);

  return 0;
}

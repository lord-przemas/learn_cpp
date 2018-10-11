#ifndef _SIGNALS_
#define _SIGNALS_

#include <cstdint>

#define SIG_SOME_SIGNAL_REQ	0x34cd
#define SIG_WHATEVER_REQ	0xab23
#define SIG_BLABLA_SIGNAL_REQ	0x54e2

struct SomeSignalReq
{
    uint32_t sigNo;
    uint32_t value;
    long long int liczba;
    char dupa;
    char text[1];
};

struct WhateverReq
{
    uint32_t sigNo;
    uint32_t value;
    long long int liczba;
    int dupa;
};

struct BlablaSignalReq
{
    uint32_t sigNo;
    short value;
    int liczba;
    char chuj[20];
};

union SIGNAL
{
  uint32_t sigNo;
  
  struct SomeSignalReq someSignalReq;
  struct WhateverReq whateverReq;
  struct BlablaSignalReq blablaSignalReq;
};

#endif // _SIGNALS_

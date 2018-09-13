

int value_1 { 1 };              // external linkage
extern int value_2 { 2 };       // external linkage

const int value_3 { 3 };        // internal linkage
extern const int value_4 { 4 }; // external linkage

static int value_5 { 5 };       // internal linkage
//extern static int value_6 { 6 };// compiler ERROR! - it's forbidden!

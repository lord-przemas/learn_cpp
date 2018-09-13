#ifndef HEADER_H
#define HEADER_H

// When header is included in multiple file,
// then it will result in compiler ERROR:
// multiple definition of `variable_1'
//int variable_1 { 1 }; // external linkage

// When header is included in multiple file,
// then it will compile successfuly,
// but there will be a separate instance in each file
const int variable_2 { 2 };  // internal linkage
static int variable_3 { 3 }; // internal linkage
void printVariable3();

// Now compilation is always sucessful
// and there is only one copy of variable
// in entire project
extern int variable_4;       // external linkage
extern const int variable_5; // external linkage
void printVariable4();
void printVariable5Address();

// When header is included in multiple file,
// then it will result in compiler ERROR:
// multiple definition of `externalLinkage1()'
//void externalLinkage1() {}

// Now compilation is always sucessful
// and there is only one definition of function
// in entire project
void externalLinkage2();

// Compilation is always sucessful
// There will be copy of function definition in each file
static void internalLinkage1() {};

// Compilation ERROR!
// There will be only copy of function forwar declaration in each file
// but definition is undefined due to internal linkage
//static void internalLinkage2();
//static void internalLinkage3();
//void internalLinkage4();

// Compilation is sucessful
// Functiob is going to be inlined
inline void inlineFunction1(){}


#endif // HEADER_H

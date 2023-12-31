#ifndef LIB_H
#define LIB_H
#include <stdbool.h>
#include <stdint.h>

typedef struct regStruct
{
    uint64_t rax, rbx, rcx, rdx;
    uint64_t rsi, rdi, rbp, rsp;
    uint64_t r8, r9, r10, r11;
    uint64_t r12, r13, r14, r15;
    uint64_t rip, cs, rflags, ss;
} regStruct;

void saveRegsBuffer(uint64_t regs);
void *memset(void *destination, int32_t character, uint64_t length);
void *memcpy(void *destination, const void *source, uint64_t length);
char *cpuVendor(char *result);

// Auxiliary Assembly functions

void userBuild(void);
uint8_t inb(uint16_t in1);
void outb(uint16_t out1, uint8_t in1);

// keyboard support:

uint8_t getKey(void);
void addToBuffer(char c);
char getKbChar(void);
void keyPressed(bool state);
bool keyIsPressed(void);

// clock functionality:

unsigned int seconds();
unsigned int minutes();
unsigned int hours();
unsigned int year();
unsigned int day();
unsigned int month();
void timeToStr(char *dest);
void dateToStr(char *dest);
void getDate(char *dest);
void printRegs();
#endif
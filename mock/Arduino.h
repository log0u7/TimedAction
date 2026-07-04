#pragma once
#include <stddef.h>
#include <stdint.h>

#define HIGH 0x1
#define LOW  0x0
#define INPUT 0x0
#define OUTPUT 0x1
#define INPUT_PULLUP 0x2

#define DEC 10
#define HEX 16
#define OCT 8
#define BIN 2
#define BYTE 0

typedef uint8_t byte;
typedef bool boolean;

static unsigned long _mock_millis_counter = 0;

static inline unsigned long millis() {
    return _mock_millis_counter;
}

static inline void pinMode(uint8_t, uint8_t) {}
static inline void digitalWrite(uint8_t, uint8_t) {}
static inline int digitalRead(uint8_t) { return LOW; }
static inline void delay(unsigned long) {}

struct Serial_ {
    void begin(unsigned long) {}
    void print(const char*) {}
    void print(char) {}
    void print(int val, int fmt = DEC) { (void)val; (void)fmt; }
    void println(const char*) {}
    void println(char) {}
    void println(int val, int fmt = DEC) { (void)val; (void)fmt; }
    int available() { return 0; }
    int read() { return -1; }
    size_t write(uint8_t) { return 1; }
    void flush() {}
};

static Serial_ Serial;

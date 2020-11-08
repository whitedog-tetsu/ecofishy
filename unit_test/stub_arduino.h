#ifndef STUB_ARDUINO_H
#define STUB_ARDUINO_H
#ifdef __cplusplus
extern "C" {
#endif

#pragma once 

#include <stdio.h>
#include <stdint.h>




#define HIGH 0x1
#define LOW  0x0

#define INPUT 0x0
#define OUTPUT 0x1
#define INPUT_PULLUP 0x2

#ifdef WIN32
#elif linux
#else
#define true 0x1
#define false 0x0
#endif

#define PI 3.1415926535897932384626433832795
#define HALF_PI 1.5707963267948966192313216916398
#define TWO_PI 6.283185307179586476925286766559
#define DEG_TO_RAD 0.017453292519943295769236907684886
#define RAD_TO_DEG 57.295779513082320876798154814105

#define SERIAL  0x0
#define DISPLAY 0x1

#define LSBFIRST 0
#define MSBFIRST 1

#define CHANGE 1
#define FALLING 2
#define RISING 3

#define DEC 10
#define HEX 16
#define OCT 8
#define BIN 2

typedef uint8_t boolean;
typedef uint8_t byte;





extern void pinMode(uint8_t a, uint8_t b);
extern uint8_t digitalRead(uint8_t a);
extern void digitalWrite(uint8_t a, uint8_t b);
extern uint8_t analogRead(uint8_t a);
extern void analogWrite(uint8_t a, uint8_t b);


class Serial_ {

  private:
    static bool printToCout;

  public:
    static void setPrintToCout(bool flag);

  public:
    static size_t print(const char[]);
    static size_t print(char);
    static size_t print(unsigned char, int = DEC);
    static size_t print(int, int = DEC);
    static size_t print(unsigned int, int = DEC);
    static size_t print(long, int = DEC);
    static size_t print(unsigned long, int = DEC);
    static size_t print(double, int = 2);

    static size_t println(const char[]);
    static size_t println(char);
    static size_t println(unsigned char, int = DEC);
    static size_t println(int, int = DEC);
    static size_t println(unsigned int, int = DEC);
    static size_t println(long, int = DEC);
    static size_t println(unsigned long, int = DEC);
    static size_t println(double, int = 2);
    static size_t println(void);

    size_t write(uint8_t);
    size_t write(const char *str);
    size_t write(const uint8_t *buffer, size_t size);

    uint8_t begin(uint32_t);

    uint8_t available();
    uint8_t read();

    static void flush();

    /*
    TODO: Not implemented yet.
    int getWriteError();
    void clearWriteError();
    static size_t print(const __FlashStringHelper *);
    static size_t print(const String &);
    static size_t print(const Printable&);
    static size_t println(const __FlashStringHelper *);
    static size_t println(const String &s);
    static size_t println(const Printable&);
    */
};
extern Serial_ Serial;


#ifdef __cplusplus
}
#endif

#endif // STUB_ARDUINO_H

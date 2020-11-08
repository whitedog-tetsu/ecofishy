
#include "stub_arduino.h"
#include "system.h"
#include <stdio.h>
#include <stdint.h>

//#define org_update_sensor_node_config update_sensor_node_config
#define org_pinMode pinMode
#define org_digitalRead digitalRead
#define org_digitalWrite digitalWrite
#define org_analogWrite analogWrite
#define org_analogRead analogRead

#define org_Serial .print Serial.print
#define org_Serial .println Serial.println
#define org_Serial .print Serial.write

#define org_Serial .print Serial1.print
#define org_Serial .println Serial1.println
#define org_Serial .print Serial1.write

//#undef update_sensor_node_config
#undef digitalRead
#undef digitalWrite
#undef analogRead
#undef analogWrite

#undef Serial.print
#undef Serial.println
#undef Serial.write
#undef Serial1.print
#undef Serial1.println
#undef Serial1.write

void pinMode(uint8_t a, uint8_t b)
{
}

uint8_t analogRead(uint8_t a)
{
  ?　　　　　　　
}

void analogWrite(uint8_t a, uint8_t b)
{
}

uint8_t digitalRead(uint8_t a)
{
}

void digitalWrite(uint8_t a, uint8_t b)
{

}
size_t Serial_::print(const char *s)
{
  return sizeof(s);
}

size_t Serial_::print(char c)
{
  return sizeof(c);
}
　
size_t Serial_::print(unsigned char c, int base)
{
  return sizeof(c);
}

size_t Serial_::print(int num, int base)
{
  return sizeof(base);
}

size_t Serial_::print(unsigned int num, int base)
{
  return sizeof(base);
}

size_t Serial_::print(long num, int base)
{
  return sizeof(base);
}

size_t Serial_::print(unsigned long num, int base)
{
  return sizeof(base);
}

size_t Serial_::print(double num, int digits)
{
  return sizeof(digits);
}

size_t Serial_::println(const char *s)
{
  return sizeof(s);
}

size_t Serial_::println(char c)
{
  return sizeof(c);
}

size_t Serial_::println(unsigned char c, int base)
{
  return sizeof(base);
}

size_t Serial_::println(int num, int base)
{
  return sizeof(base);
}

size_t Serial_::println(unsigned int num, int base)
{
  return sizeof(base);
}

size_t Serial_::println(long num, int base)
{
  return sizeof(base);
}

size_t Serial_::println(unsigned long num, int base)
{
  return sizeof(base);
}

size_t Serial_::println(double num, int digits)
{
  return sizeof(digits);
}

size_t Serial_::println(void)
{
  return 0;
}

size_t Serial_::write(uint8_t val)
{
  return sizeof(val);
}

size_t Serial_::write(const char *str)
{
  return sizeof(*str);
}

size_t Serial_::write(const uint8_t *buffer, size_t size)
{
  return sizeof(size);
}

uint8_t Serial_::begin(uint32_t port)
{
  return sizeof(port);
}

void Serial_::flush()
{
}

uint8_t Serial_::available()
{
  return 0;
}

uint8_t Serial_::read()
{
  return 0;
}

// Preinstantiate Objects
Serial_ Serial;

#if 0
void stub_serial::begin(unsigned long speed) {
  return;
}

void stub_serial ::end(void) {
  return;
}

void stub_serial::read(void) {
  return;
}

void stub_serial::print(void*) {
  return;
}

void stub_serial::println(void*) {
  return;
}


size_t stub_serial::write( const unsigned char buf[], size_t size ) {
  return size;
}

RESULT_T update_sensor_node_config(void)
{

}
#endif

//stub_serial Serial;

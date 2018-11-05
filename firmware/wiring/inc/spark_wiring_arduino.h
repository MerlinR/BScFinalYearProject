/**
  ******************************************************************************
  Copyright (c) 2015 Particle Industries, Inc.  All rights reserved.

  This library is free software; you can redistribute it and/or
  modify it under the terms of the GNU Lesser General Public
  License as published by the Free Software Foundation, either
  version 3 of the License, or (at your option) any later version.

  This library is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
  Lesser General Public License for more details.

  You should have received a copy of the GNU Lesser General Public
  License along with this library; if not, see <http://www.gnu.org/licenses/>.
  ******************************************************************************
  */

#ifndef SPARK_WIRING_ARDUINO_H
#define	SPARK_WIRING_ARDUINO_H

#if PARTICLE_ARDUINO_COMPATIBILITY == 1

#ifndef ARDUINO
#define ARDUINO 10800
#endif

#ifndef __cplusplus
#include <math.h>
#else
#include <cmath>
#endif // __cplusplus

#include "avr/pgmspace.h"
#include "spark_wiring_arduino_constants.h"
#include "spark_wiring_arduino_binary.h"

#undef F
#define F(X) (reinterpret_cast<const __FlashStringHelper*>(X))

#ifndef makeWord
inline uint16_t makeWord(uint16_t w) {
  return w;
}

inline uint16_t makeWord(uint8_t h, uint8_t l) {
  return ((uint16_t)h << 8) | ((uint16_t)l);
}
#endif

#ifndef word
#define word(...) makeWord(__VA_ARGS__)
#endif

#ifndef WEAK
#define WEAK __attribute__ ((weak))
#endif

#ifndef SYSTEM_CORE_CLOCK
#define SYSTEM_CORE_CLOCK             SystemCoreClock
#endif

#ifndef clockCyclesPerMicrosecond
#define clockCyclesPerMicrosecond()   (SystemCoreClock / 1000000L)
#endif

#ifndef clockCyclesToMicroseconds
#define clockCyclesToMicroseconds(a)  (((a) * 1000L) / (SystemCoreClock / 1000L))
#endif

#ifndef microsecondsToClockCycles
#define microsecondsToClockCycles(a)  ((a) * (SystemCoreClock / 1000000L))
#endif

#define digitalPinToInterrupt(P)      (P)

inline void yield() {
#if PLATFORM_THREADING
  os_thread_yield();
#endif // PLATFORM_THREADING
}

#ifndef PINS_COUNT
#define PINS_COUNT           TOTAL_PINS
#endif

#ifndef NUM_DIGITAL_PINS
#define NUM_DIGITAL_PINS     TOTAL_PINS
#endif

#ifndef NUM_ANALOG_INPUTS
#define NUM_ANALOG_INPUTS    TOTAL_ANALOG_PINS
#endif

#ifndef NUM_ANALOG_OUTPUTS
#define NUM_ANALOG_OUTPUTS   TOTAL_DAC_PINS
#endif

#ifndef analogInputToDigitalPin
#define analogInputToDigitalPin(p)  (((p < TOTAL_ANALOG_PINS) && (p >= 0)) ? (p) + FIRST_ANALOG_PIN : -1)
#endif

// XXX
#if PLATFORM_ID == PLATFORM_SPARK_CORE || PLATFORM_ID == PLATFORM_PHOTON_PRODUCTION || PLATFORM_ID == PLATFORM_P1 || PLATFORM_ID == PLATFORM_ELECTRON_PRODUCTION || PLATFORM_ID == PLATFORM_DUO_PRODUCTION

# ifndef digitalPinToPort
# define digitalPinToPort(P)        ( HAL_Pin_Map()[P].gpio_peripheral )
# endif

# ifndef digitalPinToBitMask
# define digitalPinToBitMask(P)     ( HAL_Pin_Map()[P].gpio_pin )
# endif
//#define analogInPinToBit(P)        ( )
# ifndef portOutputRegister
# define portOutputRegister(port)   ( &(port->ODR) )
# endif

# ifndef portInputRegister
# define portInputRegister(port)    ( &(port->IDR) )
# endif

//#define portModeRegister(port)     ( &(port->CRL) )
# ifndef digitalPinHasPWM
# define digitalPinHasPWM(P)        ( HAL_Validate_Pin_Function(P, PF_TIMER) == PF_TIMER )
# endif

#endif // PLATFORM_ID == PLATFORM_SPARK_CORE || PLATFORM_ID == PLATFORM_PHOTON_PRODUCTION || PLATFORM_ID == PLATFORM_P1 || PLATFORM_ID == PLATFORM_ELECTRON_PRODUCTION || PLATFORM_ID == PLATFORM_DUO_PRODUCTION

#ifndef _BV
#define _BV(x)  (((uint32_t)1) << (x))
#endif

// XXX
#ifndef sei
#define sei() HAL_enable_irq(0)
#endif

// XXX
#ifndef cli
#define cli() (void)HAL_disable_irq()
#endif

#ifndef cbi
#define cbi(sfr, bit) ((sfr) &= ~_BV(bit))
#endif
#ifndef sbi
#define sbi(sfr, bit) ((sfr) |= _BV(bit))
#endif

// XXX
#ifndef RwReg
typedef volatile uint32_t RwReg;
#endif

// Pins

// LED
#if PLATFORM_ID == PLATFORM_SPARK_CORE || PLATFORM_ID == PLATFORM_PHOTON_PRODUCTION || PLATFORM_ID == PLATFORM_P1 || PLATFORM_ID == PLATFORM_ELECTRON_PRODUCTION || PLATFORM_ID == PLATFORM_DUO_PRODUCTION
# ifndef LED_BUILTIN
# define LED_BUILTIN D7
# endif

# ifndef ATN
# define ATN SS
# endif

#endif // PLATFORM_ID == PLATFORM_SPARK_CORE || PLATFORM_ID == PLATFORM_PHOTON_PRODUCTION || PLATFORM_ID == PLATFORM_P1 || PLATFORM_ID == PLATFORM_ELECTRON_PRODUCTION || PLATFORM_ID == PLATFORM_DUO_PRODUCTION

// C++ only
#ifdef __cplusplus

#ifndef isnan
#define isnan std::isnan
#endif

#ifndef isinf
#define isinf std::isinf
#endif


// Hardware serial defines

#define UBRRH
#define UBRR1H
#if Wiring_Serial2
#define UBRR2H
#endif
#if Wiring_Serial3
#define UBRR3H
#endif
#if Wiring_Serial4
#define UBRR4H
#endif
#if Wiring_Serial5
#define UBRR5H
#endif

typedef USARTSerial HardwareSerial;

#ifndef SERIAL_PORT_MONITOR
#define SERIAL_PORT_MONITOR               Serial
#endif

#ifndef SERIAL_PORT_USBVIRTUAL
#define SERIAL_PORT_USBVIRTUAL            Serial
#endif

#ifndef SERIAL_PORT_HARDWARE_OPEN
#define SERIAL_PORT_HARDWARE_OPEN         Serial1
#endif

#ifndef SERIAL_PORT_HARDWARE_OPEN1
#define SERIAL_PORT_HARDWARE_OPEN1        Serial1
#endif

#if !defined(SERIAL_PORT_HARDWARE_OPEN2) && Wiring_Serial2
#define SERIAL_PORT_HARDWARE_OPEN2        Serial2
#endif

#if !defined(SERIAL_PORT_HARDWARE_OPEN3) && Wiring_Serial3
#define SERIAL_PORT_HARDWARE_OPEN3        Serial3
#endif

#if !defined(SERIAL_PORT_HARDWARE_OPEN4) && Wiring_Serial4
#define SERIAL_PORT_HARDWARE_OPEN4        Serial4
#endif

#if !defined(SERIAL_PORT_HARDWARE_OPEN5) && Wiring_Serial5
#define SERIAL_PORT_HARDWARE_OPEN5        Serial5
#endif

#ifndef SERIAL_PORT_HARDWARE
#define SERIAL_PORT_HARDWARE              Serial1
#endif

#ifndef SERIAL_PORT_HARDWARE1
#define SERIAL_PORT_HARDWARE1             Serial1
#endif

#if !defined(SERIAL_PORT_HARDWARE2) && Wiring_Serial2
#define SERIAL_PORT_HARDWARE2             Serial2
#endif

#if !defined(SERIAL_PORT_HARDWARE3) && Wiring_Serial3
#define SERIAL_PORT_HARDWARE3             Serial3
#endif

#if !defined(SERIAL_PORT_HARDWARE4) && Wiring_Serial4
#define SERIAL_PORT_HARDWARE4             Serial4
#endif

#if !defined(SERIAL_PORT_HARDWARE5) && Wiring_Serial5
#define SERIAL_PORT_HARDWARE5             Serial5
#endif

#ifndef SerialUSB
#define SerialUSB                         Serial
#endif

#endif // __cplusplus

#endif // PARTICLE_ARDUINO_COMPATIBILITY

#endif	/* SPARK_WIRING_ARDUINO_H */

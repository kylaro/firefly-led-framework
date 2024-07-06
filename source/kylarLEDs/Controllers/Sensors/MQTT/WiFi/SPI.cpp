/*
    SPI Master library for the Raspberry Pi Pico RP2040

    Copyright (c) 2021 Earle F. Philhower, III <earlephilhower@yahoo.com>

    This library is free software; you can redistribute it and/or
    modify it under the terms of the GNU Lesser General Public
    License as published by the Free Software Foundation; either
    version 2.1 of the License, or (at your option) any later version.

    This library is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
    Lesser General Public License for more details.

    You should have received a copy of the GNU Lesser General Public
    License along with this library; if not, write to the Free Software
    Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA
*/

#include "SPI.h"
#include <hardware/spi.h>
#include <hardware/gpio.h>
#include <hardware/structs/iobank0.h>
#include <hardware/irq.h>

// #ifdef USE_TINYUSB
// For Serial when selecting TinyUSB.  Can't include in the core because Arduino IDE
// will not link in libraries called from the core.  Instead, add the header to all
// the standard libraries in the hope it will still catch some user cases where they
// use these libraries.
// See https://github.com/earlephilhower/arduino-pico/issues/167#issuecomment-848622174
// #include <Adafruit_TinyUSB.h>
// #endif

SPIClassRP2040::SPIClassRP2040(spi_inst_t *spi, pin_size_t rx, pin_size_t cs, pin_size_t sck, pin_size_t tx) {
    _spi = spi;
    _running = false;
    _initted = false;
    _spis = SPISettings(0, LSBFIRST, SPI_MODE0); // Ensure spi_init called by setting current freq to 0
    _RX = rx;
    _TX = tx;
    _SCK = sck;
    _CS = cs;
}

inline spi_cpol_t SPIClassRP2040::cpol() {
    switch (_spis.getDataMode()) {
    case SPI_MODE0:
        return SPI_CPOL_0;
    case SPI_MODE1:
        return SPI_CPOL_0;
    case SPI_MODE2:
        return SPI_CPOL_1;
    case SPI_MODE3:
        return SPI_CPOL_1;
    }
    // Error
    return SPI_CPOL_0;
}

inline spi_cpha_t SPIClassRP2040::cpha() {
    switch (_spis.getDataMode()) {
    case SPI_MODE0:
        return SPI_CPHA_0;
    case SPI_MODE1:
        return SPI_CPHA_1;
    case SPI_MODE2:
        return SPI_CPHA_0;
    case SPI_MODE3:
        return SPI_CPHA_1;
    }
    // Error
    return SPI_CPHA_0;
}

inline uint8_t SPIClassRP2040::reverseByte(uint8_t b) {
    b = (b & 0xF0) >> 4 | (b & 0x0F) << 4;
    b = (b & 0xCC) >> 2 | (b & 0x33) << 2;
    b = (b & 0xAA) >> 1 | (b & 0x55) << 1;
    return b;
}

inline uint16_t SPIClassRP2040::reverse16Bit(uint16_t w) {
    return (reverseByte(w & 0xff) << 8) | (reverseByte(w >> 8));
}

// The HW can't do LSB first, only MSB first, so need to bitreverse
void SPIClassRP2040::adjustBuffer(const void *s, void *d, size_t cnt, bool by16) {
    if (_spis.getBitOrder() == MSBFIRST) {
        memcpy(d, s, cnt * (by16 ? 2 : 1));
    } else if (!by16) {
        const uint8_t *src = (const uint8_t *)s;
        uint8_t *dst = (uint8_t *)d;
        for (size_t i = 0; i < cnt; i++) {
            *(dst++) = reverseByte(*(src++));
        }
    } else { /* by16 */
        const uint16_t *src = (const uint16_t *)s;
        uint16_t *dst = (uint16_t *)d;
        for (size_t i = 0; i < cnt; i++) {
            *(dst++) = reverse16Bit(*(src++));
        }
    }
}

byte SPIClassRP2040::transfer(uint8_t data) {
    uint8_t ret;
    if (!_initted) {
        return 0;
    }
    data = (_spis.getBitOrder() == MSBFIRST) ? data : reverseByte(data);
    DEBUGSPI("SPI::transfer(%02x), cpol=%d, cpha=%d\n", data, cpol(), cpha());
    hw_write_masked(&spi_get_hw(_spi)->cr0, (8 - 1) << SPI_SSPCR0_DSS_LSB, SPI_SSPCR0_DSS_BITS); // Fast set to 8-bits
    spi_write_read_blocking(_spi, &data, &ret, 1);
    ret = (_spis.getBitOrder() == MSBFIRST) ? ret : reverseByte(ret);
    DEBUGSPI("SPI: read back %02x\n", ret);
    return ret;
}

uint16_t SPIClassRP2040::transfer16(uint16_t data) {
    uint16_t ret;
    if (!_initted) {
        return 0;
    }
    data = (_spis.getBitOrder() == MSBFIRST) ? data : reverse16Bit(data);
    DEBUGSPI("SPI::transfer16(%04x), cpol=%d, cpha=%d\n", data, cpol(), cpha());
    hw_write_masked(&spi_get_hw(_spi)->cr0, (16 - 1) << SPI_SSPCR0_DSS_LSB, SPI_SSPCR0_DSS_BITS); // Fast set to 16-bits
    spi_write16_read16_blocking(_spi, &data, &ret, 1);
    ret = (_spis.getBitOrder() == MSBFIRST) ? ret : reverse16Bit(ret);
    DEBUGSPI("SPI: read back %02x\n", ret);
    return ret;
}

void SPIClassRP2040::transfer(void *buf, size_t count) {
    DEBUGSPI("SPI::transfer(%p, %d)\n", buf, count);
    uint8_t *buff = reinterpret_cast<uint8_t *>(buf);
    for (size_t i = 0; i < count; i++) {
        *buff = transfer(*buff);
        buff++;
    }
    DEBUGSPI("SPI::transfer completed\n");
}

void SPIClassRP2040::transfer(const void *txbuf, void *rxbuf, size_t count) {
    if (!_initted) {
        return;
    }

    hw_write_masked(&spi_get_hw(_spi)->cr0, (8 - 1) << SPI_SSPCR0_DSS_LSB, SPI_SSPCR0_DSS_BITS); // Fast set to 8-bits

    DEBUGSPI("SPI::transfer(%p, %p, %d)\n", txbuf, rxbuf, count);
    const uint8_t *txbuff = reinterpret_cast<const uint8_t *>(txbuf);
    uint8_t *rxbuff = reinterpret_cast<uint8_t *>(rxbuf);

    // MSB version is easy!
    if (_spis.getBitOrder() == MSBFIRST) {
        if (rxbuf == nullptr) { // transmit only!
            spi_write_blocking(_spi, txbuff, count);
            return;
        }
        if (txbuf == nullptr) { // receive only!
            spi_read_blocking(_spi, 0xFF, rxbuff, count);
            return;
        }
        // transmit and receive!
        spi_write_read_blocking(_spi, txbuff, rxbuff, count);
        return;
    }

    // If its LSB this isn't nearly as fun, we'll just let transfer(x) do it :(
    for (size_t i = 0; i < count; i++) {
        *rxbuff = transfer(*txbuff);
        *rxbuff = (_spis.getBitOrder() == MSBFIRST) ? *rxbuff : reverseByte(*rxbuff);
        txbuff++;
        rxbuff++;
    }
    DEBUGSPI("SPI::transfer completed\n");
}

void SPIClassRP2040::beginTransaction(SPISettings settings) {
    noInterrupts(); // Avoid possible race conditions if IRQ comes in while main app is in middle of this
    DEBUGSPI("SPI::beginTransaction(clk=%lu, bo=%s)\n", settings.getClockFreq(), (settings.getBitOrder() == MSBFIRST) ? "MSB" : "LSB");
    if (_initted && settings == _spis) {
        DEBUGSPI("SPI: Reusing existing initted SPI\n");
    } else {
        /* Only de-init if the clock changes frequency */
        if (settings.getClockFreq() != _spis.getClockFreq()) {
            if (_initted) {
                DEBUGSPI("SPI: deinitting currently active SPI\n");
                spi_deinit(_spi);
            }
            DEBUGSPI("SPI: initting SPI\n");
            spi_init(_spi, settings.getClockFreq());
            DEBUGSPI("SPI: actual baudrate=%u\n", spi_get_baudrate(_spi));
        }
        _spis = settings;
        spi_set_format(_spi, 8, cpol(), cpha(), SPI_MSB_FIRST);
        _initted = true;
    }
    // Disable any IRQs that are being used for SPI
    io_irq_ctrl_hw_t *irq_ctrl_base = get_core_num() ? &iobank0_hw->proc1_irq_ctrl : &iobank0_hw->proc0_irq_ctrl;
    DEBUGSPI("SPI: IRQ masks before = %08x %08x %08x %08x\n", (unsigned)irq_ctrl_base->inte[0], (unsigned)irq_ctrl_base->inte[1], (unsigned)irq_ctrl_base->inte[2], (unsigned)irq_ctrl_base->inte[3]);
    for (auto entry : _usingIRQs) {
        int gpio = entry.first;

        // There is no gpio_get_irq, so manually twiddle the register
        io_rw_32 *en_reg = &irq_ctrl_base->inte[gpio / 8];
        uint32_t val = ((*en_reg) >> (4 * (gpio % 8))) & 0xf;
        _usingIRQs.insert_or_assign(gpio, val);
        DEBUGSPI("SPI: GPIO %d = %lu\n", gpio, val);
        (*en_reg) ^= val << (4 * (gpio % 8));
    }
    DEBUGSPI("SPI: IRQ masks after = %08x %08x %08x %08x\n", (unsigned)irq_ctrl_base->inte[0], (unsigned)irq_ctrl_base->inte[1], (unsigned)irq_ctrl_base->inte[2], (unsigned)irq_ctrl_base->inte[3]);
    interrupts();
}

void SPIClassRP2040::endTransaction(void) {
    noInterrupts(); // Avoid race condition so the GPIO IRQs won't come back until all state is restored
    DEBUGSPI("SPI::endTransaction()\n");
    // Re-enablke IRQs
    for (auto entry : _usingIRQs) {
        int gpio = entry.first;
        int mode = entry.second;
        gpio_set_irq_enabled(gpio, mode, true);
    }
    io_irq_ctrl_hw_t *irq_ctrl_base = get_core_num() ? &iobank0_hw->proc1_irq_ctrl : &iobank0_hw->proc0_irq_ctrl;
    (void) irq_ctrl_base;
    DEBUGSPI("SPI: IRQ masks = %08x %08x %08x %08x\n", (unsigned)irq_ctrl_base->inte[0], (unsigned)irq_ctrl_base->inte[1], (unsigned)irq_ctrl_base->inte[2], (unsigned)irq_ctrl_base->inte[3]);
    interrupts();
}

bool SPIClassRP2040::setRX(pin_size_t pin) {
    constexpr uint32_t valid[2] = { __bitset({0, 4, 16, 20}) /* SPI0 */,
                                    __bitset({8, 12, 24, 28})  /* SPI1 */
                                  };
    if ((!_running) && ((1 << pin) & valid[spi_get_index(_spi)])) {
        _RX = pin;
        return true;
    }

    if (_RX == pin) {
        return true;
    }

    if (_running) {
        panic("FATAL: Attempting to set SPI%s.RX while running", spi_get_index(_spi) ? "1" : "");
    } else {
        panic("FATAL: Attempting to set SPI%s.RX to illegal pin %d", spi_get_index(_spi) ? "1" : "", pin);
    }
    return false;
}

bool SPIClassRP2040::setCS(pin_size_t pin) {
    constexpr uint32_t valid[2] = { __bitset({1, 5, 17, 21}) /* SPI0 */,
                                    __bitset({9, 13, 25, 29})  /* SPI1 */
                                  };
    if ((!_running) && ((1 << pin) & valid[spi_get_index(_spi)])) {
        _CS = pin;
        return true;
    }

    if (_CS == pin) {
        return true;
    }

    if (_running) {
        panic("FATAL: Attempting to set SPI%s.CS while running", spi_get_index(_spi) ? "1" : "");
    } else {
        panic("FATAL: Attempting to set SPI%s.CS to illegal pin %d", spi_get_index(_spi) ? "1" : "", pin);
    }
    return false;
}

bool SPIClassRP2040::setSCK(pin_size_t pin) {
    constexpr uint32_t valid[2] = { __bitset({2, 6, 18, 22}) /* SPI0 */,
                                    __bitset({10, 14, 26})  /* SPI1 */
                                  };
    if ((!_running) && ((1 << pin) & valid[spi_get_index(_spi)])) {
        _SCK = pin;
        return true;
    }

    if (_SCK == pin) {
        return true;
    }

    if (_running) {
        panic("FATAL: Attempting to set SPI%s.SCK while running", spi_get_index(_spi) ? "1" : "");
    } else {
        panic("FATAL: Attempting to set SPI%s.SCK to illegal pin %d", spi_get_index(_spi) ? "1" : "", pin);
    }
    return false;
}

bool SPIClassRP2040::setTX(pin_size_t pin) {
    constexpr uint32_t valid[2] = { __bitset({3, 7, 19, 23}) /* SPI0 */,
                                    __bitset({11, 15, 27})  /* SPI1 */
                                  };
    if ((!_running) && ((1 << pin) & valid[spi_get_index(_spi)])) {
        _TX = pin;
        return true;
    }

    if (_TX == pin) {
        return true;
    }

    if (_running) {
        panic("FATAL: Attempting to set SPI%s.TX while running", spi_get_index(_spi) ? "1" : "");
    } else {
        panic("FATAL: Attempting to set SPI%s.TX to illegal pin %d", spi_get_index(_spi) ? "1" : "", pin);
    }
    return false;
}

void SPIClassRP2040::begin(bool hwCS) {
    DEBUGSPI("SPI::begin(%d), rx=%d, cs=%d, sck=%d, tx=%d\n", hwCS, _RX, _CS, _SCK, _TX);
    gpio_set_function(_RX, GPIO_FUNC_SPI);
    _hwCS = hwCS;
    if (hwCS) {
        gpio_set_function(_CS, GPIO_FUNC_SPI);
    }
    gpio_set_function(_SCK, GPIO_FUNC_SPI);
    gpio_set_function(_TX, GPIO_FUNC_SPI);
    // Give a default config in case user doesn't use beginTransaction
    beginTransaction(_spis);
    endTransaction();
}

void SPIClassRP2040::end() {
    DEBUGSPI("SPI::end()\n");
    if (_initted) {
        DEBUGSPI("SPI: deinitting currently active SPI\n");
        _initted = false;
        spi_deinit(_spi);
    }
    gpio_set_function(_RX, GPIO_FUNC_SIO);
    if (_hwCS) {
        gpio_set_function(_CS, GPIO_FUNC_SIO);
    }
    gpio_set_function(_SCK, GPIO_FUNC_SIO);
    gpio_set_function(_TX, GPIO_FUNC_SIO);
    _spis = SPISettings(0, LSBFIRST, SPI_MODE0);
}

void SPIClassRP2040::setBitOrder(BitOrder order) {
    _spis = SPISettings(_spis.getClockFreq(), order, _spis.getDataMode());
    beginTransaction(_spis);
    endTransaction();
}

void SPIClassRP2040::setDataMode(uint8_t uc_mode) {
    _spis = SPISettings(_spis.getClockFreq(), _spis.getBitOrder(), uc_mode);
    beginTransaction(_spis);
    endTransaction();
}

void SPIClassRP2040::setClockDivider(uint8_t uc_div) {
    (void) uc_div; // no-op
}

#ifndef __SPI0_DEVICE
#define __SPI0_DEVICE spi0
#endif
#ifndef __SPI1_DEVICE
#define __SPI1_DEVICE spi1
#endif

// #ifdef PIN_SPI0_MISO
SPIClassRP2040 SPI(__SPI0_DEVICE, PIN_SPI0_MISO, PIN_SPI0_SS, PIN_SPI0_SCK, PIN_SPI0_MOSI);
// #endif

// #ifdef PIN_SPI1_MISO
SPIClassRP2040 SPI1(__SPI1_DEVICE, PIN_SPI1_MISO, PIN_SPI1_SS, PIN_SPI1_SCK, PIN_SPI1_MOSI);
// #endif

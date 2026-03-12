#pragma once
#include <Arduino.h>

#include "VirtualKey.h"

// =========================== AnalogKeyScan ===========================
class AnalogKeyScan {
   public:
    // массив сигналов кнопок, его длина, ширина окна сигнала
    AnalogKeyScan(const int16_t* sigs, uint8_t len, uint8_t window = 15) : _sigs(sigs), _len(len), _offs(window / 2) {}

    // сканировать клавиатуру. Вернёт индекс кнопки, -1 если не нажата
    int8_t scan(int16_t signal) const {
        for (uint8_t i = 0; i < _len; i++) {
            int16_t diff = _sigs[i] - signal;
            if (diff >= -_offs && diff <= _offs) return i;
        }
        return -1;
    }

    // установить окно сигнала (умолч. 15)
    void setWindow(uint8_t window) {
        _offs = window / 2;
    }

   private:
    const int16_t* _sigs;
    uint8_t _len;
    int8_t _offs;
};

// =========================== AnalogKeyMin ===========================
class AnalogKeyMin : public AnalogKeyScan, public VirtualKeyMin {
   public:
    AnalogKeyMin(uint8_t pin, const int16_t* sigs, uint8_t len, uint8_t window = 20) : AnalogKeyScan(sigs, len, window), _pin(pin) {}

   private:
    uint8_t _pin;

    int8_t scanKey() override {
        return AnalogKeyScan::scan(analogRead(_pin));
    }
};

// =========================== AnalogKey ===========================
class AnalogKey : public AnalogKeyScan, public VirtualKey {
   public:
    AnalogKey(uint8_t pin, const int16_t* sigs, uint8_t len, uint8_t window = 20) : AnalogKeyScan(sigs, len, window), _pin(pin) {}

   private:
    uint8_t _pin;

    int8_t scanKey() override {
        return AnalogKeyScan::scan(analogRead(_pin));
    }
};
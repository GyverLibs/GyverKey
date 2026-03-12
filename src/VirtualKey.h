#pragma once
#include <Arduino.h>
#include <uButtonVirt.h>

// =========================== VirtualKeyMin ===========================
class VirtualKeyMin {
   public:
    // тикер, вызывать в loop. Вернёт true при нажатии кнопки
    bool tick() {
        if (uint8_t(uint8_t(millis()) - _tmr) < _prd) return false;
        _tmr = millis();

        int8_t cur = scanKey();
        if (_prev == cur) return false;

        _prev = cur;
        return cur >= 0;
    }

    // установить период сканирования кнопок в мс (умолч 30)
    void setScanPeriod(uint8_t ms) {
        _prd = ms;
    }

    // получить индекс нажатой кнопки, -1 если не нажата
    int8_t key() {
        return _prev;
    }

    // получить символ кнопки из строки, NULL если не нажата
    char key(const char* keys) {
        return _prev >= 0 ? keys[_prev] : '\0';
    }

   protected:
    virtual int8_t scanKey() = 0;

   private:
    uint8_t _tmr = 0;
    uint8_t _prd = 30;
    int8_t _prev = -1;
};

// =========================== VirtualKey ===========================
class VirtualKey : public uButtonVirt {
   public:
    // тикер, вызывать в loop. Вернёт true при смене состояния кнопки
    bool tick() {
        if (uint8_t(uint8_t(millis()) - _tmr) >= _prd) {
            _tmr = millis();
            int8_t cur = scanKey();
            if (_prev >= 0 && cur >= 0 && _prev != cur) reset();
            else if (!busy()) _n = -1;
            if (cur >= 0) _n = cur;
            _prev = cur;
        }
        return poll(_prev >= 0);
    }

    // установить период сканирования кнопок в мс (умолч 30)
    void setScanPeriod(uint8_t ms) {
        _prd = ms;
    }

    // получить индекс нажатой кнопки, -1 если не нажата
    int8_t key() {
        return _n;
    }

    // получить символ кнопки из строки, NULL если не нажата
    char key(const char* keys) {
        return _n >= 0 ? keys[_n] : '\0';
    }

   protected:
    virtual int8_t scanKey() = 0;

   private:
    uint8_t _tmr = 0;
    uint8_t _prd = 30;
    int8_t _prev = -1;
    int8_t _n = -1;
};
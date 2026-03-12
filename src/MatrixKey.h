#pragma once
#include <Arduino.h>
#include <GyverIO.h>

#include "VirtualKey.h"

// =========================== MatrixKeyScan ===========================
class MatrixKeyScan {
   public:
    // массивы и количества пинов строк и столбцов матрицы, режим работы пинов (INPUT/INPUT_PULLUP)
    MatrixKeyScan(const uint8_t* rowPins,
                  uint8_t rows,
                  const uint8_t* colPins,
                  uint8_t cols,
                  uint8_t mode = INPUT_PULLUP) : _rowPins(rowPins),
                                                 _colPins(colPins),
                                                 _rows(rows),
                                                 _cols(cols),
                                                 _mode(mode) {
        for (uint8_t r = 0; r < _rows; r++) pinMode(_rowPins[r], _mode);
        for (uint8_t c = 0; c < _cols; c++) pinMode(_colPins[c], _mode);
    }

    // сканировать клавиатуру. Вернёт индекс кнопки, -1 если не нажата
    int8_t scan() const {
        for (uint8_t c = 0; c < _cols; c++) {
            gio::mode(_colPins[c], OUTPUT);
            gio::low(_colPins[c]);
            for (uint8_t r = 0; r < _rows; r++) {
                if (!gio::read(_rowPins[r])) {
                    gio::mode(_colPins[c], _mode);
                    return r * _cols + c;
                }
            }
            gio::mode(_colPins[c], _mode);
        }
        return -1;
    }

   private:
    const uint8_t *_rowPins, *_colPins;
    const uint8_t _rows, _cols;
    uint8_t _mode;
};

// =========================== MatrixKeyMin ===========================
class MatrixKeyMin : public MatrixKeyScan, public VirtualKeyMin {
   public:
    using MatrixKeyScan::MatrixKeyScan;

   private:
    int8_t scanKey() override {
        return MatrixKeyScan::scan();
    }
};

// =========================== MatrixKey ===========================
class MatrixKey : public MatrixKeyScan, public VirtualKey {
   public:
    using MatrixKeyScan::MatrixKeyScan;

   private:
    int8_t scanKey() override {
        return MatrixKeyScan::scan();
    }
};
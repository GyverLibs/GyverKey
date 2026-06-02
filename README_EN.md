This is an automatic translation and may be incorrect in some places. See the source README and examples for authoritative information.

[![latest](https://img.shields.io/github/v/release/GyverLibs/GyverKey.svg?color=brightgreen)](https://github.com/GyverLibs/GyverKey/releases/latest/download/GyverKey.zip)
[![PIO](https://badges.registry.platformio.org/packages/gyverlibs/library/GyverKey.svg)](https://registry.platformio.org/libraries/gyverlibs/GyverKey)
[![Foo](https://img.shields.io/badge/Website-AlexGyver.ru-blue.svg?style=flat-square)](https://alexgyver.ru/)
[![Foo](https://img.shields.io/badge/%E2%82%BD%24%E2%82%AC%20%D0%9F%D0%BE%D0%B4%D0%B4%D0%B5%D1%80%D0%B6%D0%B0%D1%82%D1%8C-%D0%B0%D0%B2%D1%82%D0%BE%D1%80%D0%B0-orange.svg?style=flat-square)](https://alexgyver.ru/support_alex/)
[![Foo](https://img.shields.io/badge/README-ENGLISH-blueviolet.svg?style=flat-square)](https://github-com.translate.goog/GyverLibs/GyverKey?_x_tr_sl=ru&_x_tr_tl=en)  

[![Foo](https://img.shields.io/badge/ПОДПИСАТЬСЯ-НА%20ОБНОВЛЕНИЯ-brightgreen.svg?style=social&logo=telegram&color=blue)](https://t.me/GyverLibs)

# GyverKey
Library for processing matrix keyboards
- Support for matrix digital and analog keyboards
- Two options - simple and extended on the basis of the library[uButton](https://github.com/GyverLibs/uButton)(Retention processing, clicking etc.)

### Compatibility
Compatible with all Arduino platforms (Arduino features are used)

### Dependencies
- GyverIO
- uButton

## Contents
- [Use of use](#usage)
- [Versions](#versions)
- [Installation](#install)
- [Bugs and feedback](#feedback)

<a id="usage"></a>

## Use of use
### Description of classes
The library contains 4 classes:

- `MatrixKeyMin`Simple class of digital matrix keyboard (issues only the index of the pressed button)
- `MatrixKey`Extended class of digital matrix keyboard, allows you to process clicks, retentions, etc. from the library[uButton](https://github.com/GyverLibs/uButton)
- `AnalogKeyMin`Simple class of analog keyboard (issues only the button index)
- `AnalogKey`Extended class of analog keyboard, allows you to process clicks, retentions, etc. from the library[uButton](https://github.com/GyverLibs/uButton)

Initialization:

```cpp
MatrixKeyMin(const uint8_t* rowPins, uint8_t rows, const uint8_t* colPins, uint8_t cols, uint8_t mode = INPUT_PULLUP);
MatrixKey(const uint8_t* rowPins, uint8_t rows, const uint8_t* colPins, uint8_t cols, uint8_t mode = INPUT_PULLUP);

AnalogKeyMin(const int16_t* sigs, uint8_t len, uint8_t window = 15);
AnalogKey(const int16_t* sigs, uint8_t len, uint8_t window = 15);
```

Common methods for all classes:

```cpp
// ticker, call the loop. Return true when you press the button
bool tick();

// set the period of scanning buttons in MS (silent 30)
void setScanPeriod(uint8_t ms);

// Get the index of the pressed button, -1 if not pressed
int8_t key();

// get the button symbol from the line, NULL if not pressed
char key(const char* keys);
```

Additional for analog:

```cpp
// set the signal window (default 15)
void setWindow(uint8_t window);
```

## Examples
### Matrix
```cpp
#include <MatrixKey.h>

uint8_t rowPins[] = {9, 8, 7, 6};
uint8_t colPins[] = {5, 4, 3, 2};

MatrixKeyMin mx(rowPins, 4, colPins, 4);
const char* keys = "123A456B789C*0#D";

void setup() {
    Serial.begin(115200);
}

void loop() {
    if (mx.tick()) {
        Serial.print(mx.key());
        Serial.print(": '");
        Serial.print(mx.key(keys));
        Serial.println("'");
    }
}
```

### Analog
```cpp
#include <AnalogKey.h>

const int16_t sigs[] = {1023, 925, 853, 787, 672, 632, 595, 562, 502, 479, 457, 437, 400, 322, 270, 231};

AnalogKeyMin mx(0, sigs, sizeof(sigs) / sizeof(sigs[0]));

void setup() {
    Serial.begin(115200);
}

void loop() {
    if (mx.tick()) {
        Serial.println(mx.key());
    }
}
```

<a id="versions"></a>

## Versions
- v1.0

<a id="install"></a>
## Installation
- The library can be found under the name **GyverKey** and installed through the library manager in:
    - Arduino IDE
    - Arduino IDE v2
    - PlatformIO
- [Download the library](https://github.com/GyverLibs/GyverKey/archive/refs/heads/main.zip).zip archive for manual installation:
    - Unpack and put in *C:\Program Files (x86)\Arduino\libraries* (Windows x64)
    - Unpack and put in *C:\Program Files\Arduino\libraries* (Windows x32)
    - Unpack and put in *Documents/Arduino/libraries/ *
    - (Arduino IDE) Automatic installation from .zip: *Sketch/Connect library/Add .ZIP library...* and specify downloaded archive
- Read more detailed instructions for installing libraries[here](https://alexgyver.ru/arduino-first/#%D0%A3%D1%81%D1%82%D0%B0%D0%BD%D0%BE%D0%B2%D0%BA%D0%B0_%D0%B1%D0%B8%D0%B1%D0%BB%D0%B8%D0%BE%D1%82%D0%B5%D0%BA)
### Update
- I recommend always updating the library: new versions fix errors and bugs, as well as optimize and add new features.
- Through the library manager IDE: find the library as when installing and click "Update"
- Manually: **Delete the folder with the old version** and then put the new one in its place. “Replacement” can not be done: sometimes new versions delete files that will remain when replaced and can lead to errors!

<a id="feedback"></a>

## Bugs and feedback
If you find bugs, create **Issue**, or better write to the mail immediately.[alex@alexgyver.ru](mailto:alex@alexgyver.ru)  
The library is open for revision and your **Pull Requests*!

When reporting bugs or incorrect work of the library, it is necessary to specify:
- Library version
- What is used by the IC
- SDK version (for ESP)
- Arduino IDE version
- Are embedded examples that use features and designs that cause bugs in your code working correctly?
- What code was downloaded, what work was expected from it and how it works in reality
- Ideally, attach the minimum code in which the bug is observed. Not a canvas of a thousand lines, but a minimum code.

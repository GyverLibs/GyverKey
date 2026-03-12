[![latest](https://img.shields.io/github/v/release/GyverLibs/GyverKey.svg?color=brightgreen)](https://github.com/GyverLibs/GyverKey/releases/latest/download/GyverKey.zip)
[![PIO](https://badges.registry.platformio.org/packages/gyverlibs/library/GyverKey.svg)](https://registry.platformio.org/libraries/gyverlibs/GyverKey)
[![Foo](https://img.shields.io/badge/Website-AlexGyver.ru-blue.svg?style=flat-square)](https://alexgyver.ru/)
[![Foo](https://img.shields.io/badge/%E2%82%BD%24%E2%82%AC%20%D0%9F%D0%BE%D0%B4%D0%B4%D0%B5%D1%80%D0%B6%D0%B0%D1%82%D1%8C-%D0%B0%D0%B2%D1%82%D0%BE%D1%80%D0%B0-orange.svg?style=flat-square)](https://alexgyver.ru/support_alex/)
[![Foo](https://img.shields.io/badge/README-ENGLISH-blueviolet.svg?style=flat-square)](https://github-com.translate.goog/GyverLibs/GyverKey?_x_tr_sl=ru&_x_tr_tl=en)  

[![Foo](https://img.shields.io/badge/ПОДПИСАТЬСЯ-НА%20ОБНОВЛЕНИЯ-brightgreen.svg?style=social&logo=telegram&color=blue)](https://t.me/GyverLibs)

# GyverKey
Библиотека для обработки матричных клавиатур
- Поддержка матричных цифровых и аналоговых клавиатур
- Два варианта - простой и расширенный на базе библиотеки [uButton](https://github.com/GyverLibs/uButton) (обработка удержания, накликивания итд)

### Совместимость
Совместима со всеми Arduino платформами (используются Arduino-функции)

### Зависимости
- GyverIO
- uButton

## Содержание
- [Использование](#usage)
- [Версии](#versions)
- [Установка](#install)
- [Баги и обратная связь](#feedback)

<a id="usage"></a>

## Использование
### Описание классов
Библиотека содержит 4 класса:

- `MatrixKeyMin` - простой класс цифровой матричной клавиатуры (выдаёт только индекс нажатой кнопки)
- `MatrixKey` - расширенный класс цифровой матричной клавиатуры, позволяет обрабатывать клики, удержания и прочее из библиотеки [uButton](https://github.com/GyverLibs/uButton)
- `AnalogKeyMin` - простой класс аналоговой клавиатуры (выдаёт только индекс нажатой кнопки)
- `AnalogKey` - расширенный класс аналоговой клавиатуры, позволяет обрабатывать клики, удержания и прочее из библиотеки [uButton](https://github.com/GyverLibs/uButton)

Инициализация:

```cpp
MatrixKeyMin(const uint8_t* rowPins, uint8_t rows, const uint8_t* colPins, uint8_t cols, uint8_t mode = INPUT_PULLUP);
MatrixKey(const uint8_t* rowPins, uint8_t rows, const uint8_t* colPins, uint8_t cols, uint8_t mode = INPUT_PULLUP);

AnalogKeyMin(const int16_t* sigs, uint8_t len, uint8_t window = 15);
AnalogKey(const int16_t* sigs, uint8_t len, uint8_t window = 15);
```

Общие методы для всех классов:

```cpp
// тикер, вызывать в loop. Вернёт true при нажатии кнопки
bool tick();

// установить период сканирования кнопок в мс (умолч 30)
void setScanPeriod(uint8_t ms);

// получить индекс нажатой кнопки, -1 если не нажата
int8_t key();

// получить символ кнопки из строки, NULL если не нажата
char key(const char* keys);
```

Дополнительные для аналоговых:

```cpp
// установить окно сигнала (умолч. 15)
void setWindow(uint8_t window);
```

## Примеры
### Матричная
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

### Аналоговая
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

## Версии
- v1.0

<a id="install"></a>
## Установка
- Библиотеку можно найти по названию **GyverKey** и установить через менеджер библиотек в:
    - Arduino IDE
    - Arduino IDE v2
    - PlatformIO
- [Скачать библиотеку](https://github.com/GyverLibs/GyverKey/archive/refs/heads/main.zip) .zip архивом для ручной установки:
    - Распаковать и положить в *C:\Program Files (x86)\Arduino\libraries* (Windows x64)
    - Распаковать и положить в *C:\Program Files\Arduino\libraries* (Windows x32)
    - Распаковать и положить в *Документы/Arduino/libraries/*
    - (Arduino IDE) автоматическая установка из .zip: *Скетч/Подключить библиотеку/Добавить .ZIP библиотеку…* и указать скачанный архив
- Читай более подробную инструкцию по установке библиотек [здесь](https://alexgyver.ru/arduino-first/#%D0%A3%D1%81%D1%82%D0%B0%D0%BD%D0%BE%D0%B2%D0%BA%D0%B0_%D0%B1%D0%B8%D0%B1%D0%BB%D0%B8%D0%BE%D1%82%D0%B5%D0%BA)
### Обновление
- Рекомендую всегда обновлять библиотеку: в новых версиях исправляются ошибки и баги, а также проводится оптимизация и добавляются новые фичи
- Через менеджер библиотек IDE: найти библиотеку как при установке и нажать "Обновить"
- Вручную: **удалить папку со старой версией**, а затем положить на её место новую. "Замену" делать нельзя: иногда в новых версиях удаляются файлы, которые останутся при замене и могут привести к ошибкам!

<a id="feedback"></a>

## Баги и обратная связь
При нахождении багов создавайте **Issue**, а лучше сразу пишите на почту [alex@alexgyver.ru](mailto:alex@alexgyver.ru)  
Библиотека открыта для доработки и ваших **Pull Request**'ов!

При сообщении о багах или некорректной работе библиотеки нужно обязательно указывать:
- Версия библиотеки
- Какой используется МК
- Версия SDK (для ESP)
- Версия Arduino IDE
- Корректно ли работают ли встроенные примеры, в которых используются функции и конструкции, приводящие к багу в вашем коде
- Какой код загружался, какая работа от него ожидалась и как он работает в реальности
- В идеале приложить минимальный код, в котором наблюдается баг. Не полотно из тысячи строк, а минимальный код
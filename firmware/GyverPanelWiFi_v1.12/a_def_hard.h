// ****************** ПРОФИЛИ УСТРОЙСТВ *******************

// ВНИМАНИЕ!!! 
// --------------------------------------------------------
// Для плат Wemos D1 mini / Wemos D1 pro в настройках компиляции выбирайте "NodeMCU 1.0(ESP-12E Module)"
// Для плат ESP32 в настройках компиляции выбирайте "ESP32 Dev Module"
// --------------------------------------------------------
// При использовании платы микроконтроллера Wemos D1 (xxxx) и выбранной в менеджере плат "Wemos D1 (xxxx)"
// прошивка скорее всего нормально работать не будет. 
// Наблюдались следующие сбои у разных пользователей:
// - нестабильная работа WiFi (постоянные отваливания и пропадание сети) - попробуйте варианты с разным значением параметров компиляции IwIP в Arduino IDE
// - прекращение вывода контрольной информации в Serial.print()
// - настройки в EEPROM не сохраняются
// Думаю все эти проблемы из-за некорректной работы ядра ESP8266 для платы (варианта компиляции) Wemos D1 (xxxx) в версии ядра ESP8266
// --------------------------------------------------------
//
// Если вы собираетесь испорльзовать возможность сохранения нарисованных в WiFiPlayer картинок в файловой системе микроконтроллера,
// в меню "Инструменты" Arduino IDE в настройке распределения памяти устройства выберите вариант:
//   Для микроконтроллеров ESP8266 с 4МБ флэш-памяти рекомендуется вариант "Flash Size: 4MB(FS:2MB OTA:~1019KB)"
//   Для микроконтроллеров ESP32   с 4МБ флэш-памяти рекомендуется вариант "Partition scheme: Default 4MB with spiff(1.2MB APP/1.5MB SPIFFS)"; 
// Также для ESP32 требуется дополнительно установить библиотеку 'LittleFS_esp32'
//
// --------------------------------------------------------
//
// Текущая версия ядра ESP32 на некоторых платах не видит SD-карты более 4GB
// Если вы скопировали файлы эффктов в соответствующую папку на SD-карте, вставили ее в SD-card shield, 
// но при запуске прошивки в мониторе порта (при включенном отладочном выводе) вы видите, что
//   Папка с эффектами обнаружена
//   Доступных файлов эффектов не найдено
//   SD-карта недоступна
// попробуйте заменить карту на другую, желательно объемом не более 4GB
//
// --------------------------------------------------------

#define HOST_NAME  F("WiFiPanel")

#define A_DEF_DEVC 1          // 1 - Настройки профилей ваших устройств в отдельном файле a_def_devc.h
                              // 0 - Настройки профиля вашего устройства размещены ниже в этом файле
                              // Файл a_def_devc.h в комплект не входит, нужно создать, скопировать туда настройки профилей ваших устройств
                              
#define A_DEF_PASS 1          // 1 - Настройки MQTT и API KEY OpenWeatherMap в отдельном файле a_def_pass.h
                              // 0 - Настройки MQTT и API KEY OpenWeatherMap определен ниже
                              // Файл a_def_pass.h в комплект не входит, нужно создать, скопировать туда указанные строки

                              // Ключ доступа к информации о погоде с сервиса OpenWeatherMap (зарегистрируйтесь на сервере https://openweathermap.org/api и получите свой ключ!)
#define WEATHER_API_KEY "6a4ba421859c9f4166697758b68d889b"  

#define INITIALIZE_TEXTS 0    // Заполнить память текстов бегущей строки текстом из примеров при первичной загрузке прошивки или при смене значения EEPROM_OK, когда
                              // все настройки сбрасываются в значения по-умолчанию

#if defined(ESP8266)
#define DEVICE_VARIANT 0      // Поставьте 0 - если ваше устройство использует только часть из доступных компонентов в схемах с ESP8266 - не полная схема
                              // Поставьте 1 - если ваше устройство ИСПОЛЬЗУЕТ ВСЕ ВОЗМОЖНЫЕ К ПОДКЛЮЧЕНИЮ компоненты (кнопка, DFPlayer, SD-card, TM1637, управление питанием) - полная схема
                              // Для варианта DEVICE_VARIANT == 1 обязательно должен быть отключен отладочный вывод в Serial, поскольку пины контроллера, связанные с
                              // отладочным выводом (D9 и D10 / RX и TX) заняты под подключение компонент кнопки и индикатора TM1637
                              
                              // Обратите внимание - пины подключения для DEVICE_VARIANT == 0 и DEVICE_VARIANT == 1 - отличаются
                              // Выполняйте сборку устройства в соответственно с выбранной схемой
                              //
                              // При необходимости измените настройки подключении в соответсвии с вариантом вашего устройства:
                              //   для DEVICE_VARIANT == 0 --> строки 70-110
                              //   для DEVICE_VARIANT == 1 --> строки 112-156
#endif

// =================== ESP8266 (NodeMCU, Wemos d1) ===================

/*
 * Wemos d1 mini
 * В менеджере плат выбрано NodeMCU v1.0 (ESP-12E)
 */ 
 
#if defined(ESP8266)

#if (DEVICE_VARIANT == 0)

// ===================================================================
// Если вы собираете матрицу из ленты светодиодов или одной готовой заводской матрицы 8x8, 16x16 или 8x32,
// укажите ниже в параметрах WIDTH, HEIGHT, MATRIX_TYPE, CONNECTION_ANGLE и STRIP_DIRECTION значения,
// описывающие размеры вашей матрицы, её тип (змейка / параллельная) и угол подключения.
//
// В параметры META_MATRIX_WIDTH и META_MATRIX_HEIGHT поставьте 1 (матрица состоит из одного сегмента),
// параметры META_MATRIX_TYPE, META_MATRIX_ANGLE, META_MATRIX_DIRECTION не имеют значения
//
// 
// Если у вас в наличии несколько заводских матриц 8x8, 16x16 или 8x32 и вы из них собираете одну большую матрицу,
// укажите ниже в параметрах WIDTH, HEIGHT, MATRIX_TYPE, CONNECTION_ANGLE и STRIP_DIRECTION значения,
// описывающие размеры, тип и угол подключения ОДНОГО СЕГМЕНТА вашей заводской матрицы.
// 
// В параметр META_MATRIX_WIDTH укажите сколько сегментов (заводских матриц) у вас подключено в ширину вашей составной матрицы,
// в параметр META_MATRIX_HEIGHT  укажите сколько сегментов (заводских матриц) у вас подключено в высоту вашей составной матрицы,
// параметры META_MATRIX_TYPE, META_MATRIX_ANGLE, META_MATRIX_DIRECTION укажите угол, где находится матрица №1, зигзагом или параллельно
// составлена ваша составная матрица из отдельных сегментов, а также направление следования матриц.
// 
// Эти параметры META_MATRIX_TYPE, META_MATRIX_ANGLE, META_MATRIX_DIRECTION имеют значения, по смыслу такие же, как для 
// подключения диодов в одной заводской матрице (MATRIX_TYPE, CONNECTION_ANGLE и STRIP_DIRECTION).
//
// Внимание!!!
// Все сегменты (заводские матрицы) из которых собрана ваша сборная матрица должны быть одного размера и ориентированы 
// одинаково по углу подключения и направлению диодов из угла,как описано в параметрах MATRIX_TYPE, CONNECTION_ANGLE и STRIP_DIRECTION.
// Сами сегменты (заводские матрицы) подключены по типу параллельного подключения или змейкой, последовательность соединения сегментов - 
// в соответствии с указанными параметрами META_MATRIX_TYPE, META_MATRIX_ANGLE, META_MATRIX_DIRECTION
// =================================================================== */

#define WIDTH 16                // ширина одного сегмента матрицы
#define HEIGHT 16               // высота одного сегмента матрицы
#define MATRIX_TYPE 0           // тип соединения диодов в сегменте матрицы: 0 - зигзаг, 1 - параллельная
#define CONNECTION_ANGLE 1      // угол подключения диодов в сегменте: 0 - левый нижний, 1 - левый верхний, 2 - правый верхний, 3 - правый нижний
#define STRIP_DIRECTION 3       // направление ленты из угла сегмента: 0 - вправо, 1 - вверх, 2 - влево, 3 - вниз

#define META_MATRIX_WIDTH 1     // количество сегментов в ширину сборной матрицы
#define META_MATRIX_HEIGHT 1    // количество сегментов в высоту сборной матрицы
#define META_MATRIX_TYPE 0      // тип сборной матрицы: 0 - зигзаг, 1 - параллельная
#define META_MATRIX_ANGLE 0     // угол 1-го сегмента сборной матрицы: 0 - левый нижний, 1 - левый верхний, 2 - правый верхний, 3 - правый нижний
#define META_MATRIX_DIRECTION 0 // направление следующих сегментов сборной матрицы из угла: 0 - вправо, 1 - вверх, 2 - влево, 3 - вниз

#define DEVICE_TYPE 1           // Использование матрицы: 0 - свернута в трубу для лампы; 1 - плоская матрица в рамке   
#define BUTTON_TYPE 1           // Тип кнопки: 0 - сенсорная (touch button); 1 - обычная кнопка на замыкание при нажатии (или если кнопки нет вообще)  
#define USE_SD 0                // поставьте 0, если у вас нет SD-card модуля
#define USE_MP3 0               // поставьте 0, если у вас нет звуковой карты MP3 плеера
#define USE_TM1637 0            // поставьте 1, если используется дополнительный индикатор TM1637, 0 если индикатора нет
#define USE_POWER 1             // 1 - использовать отключение питания матрицы через MOSFET / реле; 0 - не использовать 
#define USE_MQTT 0              // 1 - использовать управление по MQTT-каналу; 0 - не использовать 
#define USE_WEATHER 1           // 1 - использовать получение информации о текущей погоде; 0 - не использовать 
#define USE_E131 0              // 1 - использовать протокол E1.31 для синхронизации устройств или приема внешнего потока на матрицу с Jinx! или другого аналогичного ПО
#define BIG_FONT 0              // 0 - шрифт 5x8, 1 - шрифт  10x16; 2 - шрифт 8x13

#define LED_PIN  2              // D2 пин ленты
#define PIN_BTN D4              // D4 кнопка подключена сюда (D4 --- КНОПКА --- GND) 
                                // D6 для схем с DFPlayer    (D6 --- КНОПКА --- GND)
#define POWER_PIN D1            // D1 управляющий пин вкл/выкл матрицы через MOSFET / реле; POWER_ON - HIGH, POWER_OFF - LOW
#define SD_CS_PIN D8            // пин выбора SD карты - ChipSelect; Также SD карта использует D5 (CLK), D6 (MISO), D7 (MOSI)
#define STX D3                  // подключен в RX пин (2) модуля DFPlayer
#define SRX D4                  // подключен в TX пин (3) модуля DFPlayer
#define DIO D5                  // D5 TM1637 display DIO pin - требуется для компиляции скетча (USE_TM1637 == 1)
#define CLK D7                  // D7 TM1637 display CLK pin - требуется для компиляции скетча (USE_TM1637 == 1)

                                // Для USE_SD == 1 - поведение при проигрывании файла эффекта с SD-карты 
#define WAIT_PLAY_FINISHED 1    // 1 - переключаться на следующий эффект только когда весь файл полностью показан; 
                                // 0 - прерывать показ файла с SD-карты по истечении времени эффекта

#define DEBUG_SERIAL 1          // включить/выключить отладочный вывод в Serial: 0 - выключено 1 - включено
#endif

#if (DEVICE_VARIANT == 1)
// Схему соединений смотри в папке "schemes" проекта
// ESP8266+ALL.JPG             - подключены все возможные компоненты, сенсорная кнопка (BUTTON_TYPE == 0)
#define WIDTH 16                // ширина одного сегмента матрицы
#define HEIGHT 16               // высота одного сегмента матрицы
#define MATRIX_TYPE 0           // тип соединения диодов в сегменте матрицы: 0 - зигзаг, 1 - параллельная
#define CONNECTION_ANGLE 0      // угол подключения диодов в сегменте: 0 - левый нижний, 1 - левый верхний, 2 - правый верхний, 3 - правый нижний
#define STRIP_DIRECTION 0       // направление ленты из угла сегмента: 0 - вправо, 1 - вверх, 2 - влево, 3 - вниз

#define META_MATRIX_WIDTH 1     // количество сегментов в ширину сборной матрицы
#define META_MATRIX_HEIGHT 1    // количество сегментов в высоту сборной матрицы
#define META_MATRIX_TYPE 0      // тип сборной матрицы: 0 - зигзаг, 1 - параллельная
#define META_MATRIX_ANGLE 0     // угол 1-го сегмента сборной матрицы: 0 - левый нижний, 1 - левый верхний, 2 - правый верхний, 3 - правый нижний
#define META_MATRIX_DIRECTION 0 // направление следующих сегментов сборной матрицы из угла: 0 - вправо, 1 - вверх, 2 - влево, 3 - вниз

#define DEVICE_TYPE 1           // Использование матрицы: 0 - свернута в трубу для лампы; 1 - плоская матрица в рамке   
#define BUTTON_TYPE 1           // Тип кнопки: 0 - сенсорная (touch button); 1 - обычная кнопка на замыкание при нажатии (или если кнопки нет вообще)  
#define USE_SD 1                // поставьте 0, если у вас нет SD-card модуля
#define USE_MP3 1               // поставьте 0, если у вас нет звуковой карты MP3 плеера
#define USE_TM1637 1            // поставьте 1, если используется дополнительный индикатор TM1637, 0 если индикатора нет
#define USE_POWER 1             // 1 - использовать отключение питания матрицы через MOSFET; 0 - не использовать 
#define USE_MQTT 0              // 1 - использовать управление по MQTT-каналу; 0 - не использовать 
#define USE_WEATHER 1           // 1 - использовать получение информации о текущей погоде; 0 - не использовать 
#define USE_E131 0              // 1 - использовать протокол E1.31 для синхронизации устройств или приема внешнего потока на матрицу с Jinx! или другого аналогичного ПО
#define BIG_FONT 0              // 0 - шрифт 5x8, 1 - шрифт  10x16; 2 - шрифт 8x13

// Внимание!!!
// Данная компоновка работает только при отключенном отладочном выводе (DEBUG_SERIAL == 0), поскольку вывод в Serial использует D9 и D10 
// которые в данной схеме заняты под пин кнопки и пин CLK TM1637
// Если используется сенсорная кнопка - для прошивки ESP8266 необходимо отсоединить управляющий провод идущий от кнопки до Rx.
 
#define LED_PIN 2               // пин ленты
#define PIN_BTN D9              // кнопка подключена сюда (D9 --- КНОПКА --- GND) 
#define POWER_PIN D1            // управляющий пин вкл/выкл матрицы через MOSFET / реле; POWER_ON - HIGH, POWER_OFF - LOW
#define SD_CS_PIN D8            // пин выбора SD карты - ChipSelect; Также SD карта использует D5 (CLK), D6 (MISO), D7 (MOSI)
#define STX D3                  // подключен в RX пин (2) модуля DFPlayer
#define SRX D4                  // подключен в TX пин (3) модуля DFPlayer
#define DIO D0                  // TM1637 display DIO pin
#define CLK D10                 // TM1637 display CLK pin

                                // Для USE_SD == 1 - поведение при проигрывании файла эффекта с SD-карты 
#define WAIT_PLAY_FINISHED 1    // 1 - переключаться на следующий эффект только когда весь файл полностью показан; 
                                // 0 - прерывать показ файла с SD-карты по истечении времени эффекта

#define DEBUG_SERIAL 0          // включить/выключить отладочный вывод в Serial: 0 - выключено 1 - включено
#endif

#endif

// ============================== ESP32 ==============================

/*
 * ESP32
 * В менеджере плат выбрано "ESP32 Dev Module"
 */ 

// Схемы соединений смотри в папке "schemes" проекта
// ESP32+ALL.JPG             - подключены все возможные компоненты, сенсорная кнопка (BUTTON_TYPE == 0)
// ESP32+button_noRELAY.jpg  - нет реле для управления питанием матрицы, обычная кнопка (BUTTON_TYPE == 1)
// ESP32+MOSFET.JPG          - управления питанием матрицы через MOSFET, сенсорная кнопка  (BUTTON_TYPE == 0)

#if defined(ESP32)
#define WIDTH 16                // ширина одного сегмента матрицы
#define HEIGHT 16               // высота одного сегмента матрицы
#define MATRIX_TYPE 0           // тип соединения диодов в сегменте матрицы: 0 - зигзаг, 1 - параллельная
#define CONNECTION_ANGLE 1      // угол подключения диодов в сегменте: 0 - левый нижний, 1 - левый верхний, 2 - правый верхний, 3 - правый нижний
#define STRIP_DIRECTION 3       // направление ленты из угла сегмента: 0 - вправо, 1 - вверх, 2 - влево, 3 - вниз

#define META_MATRIX_WIDTH 1     // количество сегментов в ширину сборной матрицы
#define META_MATRIX_HEIGHT 1    // количество сегментов в высоту сборной матрицы
#define META_MATRIX_TYPE 0      // тип сборной матрицы: 0 - зигзаг, 1 - параллельная
#define META_MATRIX_ANGLE 0     // угол 1-го сегмента сборной матрицы: 0 - левый нижний, 1 - левый верхний, 2 - правый верхний, 3 - правый нижний
#define META_MATRIX_DIRECTION 0 // направление следующих сегментов сборной матрицы из угла: 0 - вправо, 1 - вверх, 2 - влево, 3 - вниз

#define DEVICE_TYPE 1           // Использование матрицы: 0 - свернута в трубу для лампы; 1 - плоская матрица в рамке   
#define BUTTON_TYPE 1           // Тип кнопки: 0 - сенсорная (touch button); 1 - обычная кнопка на замыкание при нажатии (или если кнопки нет вообще)  
#define USE_SD 1                // поставьте 0, если у вас нет SD-card модуля
#define USE_MP3 0               // поставьте 0, если у вас нет звуковой карты MP3 плеера
#define USE_TM1637 0            // поставьте 1, если используется дополнительный индикатор TM1637, 0 если индикатора нет
#define USE_POWER 1             // 1 - использовать отключение питания матрицы через MOSFET; 0 - не использовать 
#define USE_MQTT 1              // 1 - использовать управление по MQTT-каналу; 0 - не использовать 
#define USE_WEATHER 1           // 1 - использовать получение информации о текущей погоде; 0 - не использовать 
#define USE_E131 0              // 1 - использовать протокол E1.31 для синхронизации устройств или приема внешнего потока на матрицу с Jinx! или другого аналогичного ПО
#define BIG_FONT 0              // 0 - шрифт 5x8, 1 - шрифт  10x16; 2 - шрифт 8x13

// Схема подключения для ESP32 - в папке Schemes, файл 'ESP32+ALL.JPG'
 
#define LED_PIN (2U)            // пин ленты
#define PIN_BTN (15U)           // кнопка подключена сюда (PIN --- КНОПКА --- GND)
#define POWER_PIN (26U)         // G26 управляющий пин вкл/выкл матрицы через MOSFET или реле
#define SD_CS_PIN (5U)          // G5 пин выбора (ChipSelect) SD карты. Также SD карта использует G18 (CLK), G19 (MISO), G23 (MOSI) // на SD-shild: D8 (CS), D5 (CLK), D6 (MISO), D7 (MOSI)

#define SRX (16U)               // G16 RX пин ESP32, подключен в TX пин (3) модуля DFPlayer
#define STX (17U)               // G17 TX пин ESP32, подключен в RX пин (2) модуля DFPlayer
#define DIO (33U)               // TM1637 display DIO pin
#define CLK (32U)               // TM1637 display CLK pin

                                // Для USE_SD == 1 - поведение при проигрывании файла эффекта с SD-карты 
#define WAIT_PLAY_FINISHED 1    // 1 - переключаться на следующий эффект только когда весь файл полностью показан; 
                                // 0 - прерывать показ файла с SD-карты по истечении времени эффекта

#define DEBUG_SERIAL 1          // включить/выключить отладочный вывод в Serial: 0 - выключено 1 - включено
#endif

// =======================================================

#if (A_DEF_DEVC == 1)
#include "a_def_devc.h"       // Если здесь ошибка - смотри комментарий к определению A_DEF_DEVC выше в начале этого файла
#endif

// =======================================================

// ************** ИСПОЛЬЗУЕМЫЕ БИБЛИОТЕКИ ****************

#if defined(ESP8266)
  #include <ESP8266WiFi.h>
  #include <ESP8266mDNS.h>
#endif

#if defined(ESP32)
  #include <ESPmDNS.h>
#endif

#if (USE_MQTT == 1)
#define MQTT_KEEPALIVE 15        // Интервал "пинга" MQTT ервера для проверки, что соединение еще "живо"
#define MQTT_SOCKET_TIMEOUT 1    // Таймаут UDP-сокета передачи данных в канал MQTT брокеру
#include <PubSubClient.h>        // Библиотека для работы с MQTT
#endif

#include <ArduinoOTA.h>          // Библиотека обновления "по воздуху"
#include <WiFiUdp.h>             // Библиотека поддержки WiFi
#include <TimeLib.h>             // Библиотека поддержки функций времени
#include <EEPROM.h>              // Библиотека поддержки постоянной памяти
#include <FastLED.h>             // Установите в менеджере библиотек стандартную библиотеку FastLED
#include <ArduinoJson.h>         // Библиотека для работы с JSON (погода, mqtt, состояние системы)

#if (USE_TM1637 == 1)
#include "TM1637Display.h"       // Внимание!!! Библиотека в папке проекта libraries изменена - константы букв и цифр переименованы с вида _1, _A на _1_, _A_ из-за ошибок компиляции для ESP32
#endif 

#include "timerMinim.h"          // Библиотека таймеров
#include "GyverButton.h"         // Библиотека поддержки кнопок
#include "fonts.h"               // Шрифты, определенные для бегущей строки

#if (USE_MP3 == 1)
#include <SoftwareSerial.h>      // Установите в менеджере библиотек "EspSoftwareSerial" для ESP8266/ESP32 https://github.com/plerup/espsoftwareserial/
#include "DFMiniMp3.h"           // Установите в менеджере библиотек стандартную библиотеку DFMiniMp3 от Makuha ("DFPlayer Mini MP3 by Makuna" https://github.com/Makuna/DFMiniMp3)
#endif

#if (USE_SD == 1)
#include <SPI.h>                 // Библиотеки поддержки работы с SD-картой
#include <SD.h>
#endif

#if (USE_E131 == 1)              // Внимание!!! Библиотека в папке проекта libraries изменена - исправлены ошибки, добавлен деструктор, добавлены функции multicast-отправки пакета
#include <ESPAsyncE131.h>        // Библиотека приема потока по протоколу E1.31; Требует установленной библиотеки ESPAcyncUDP
#endif

#include "FS.h"                  // Работа с внутренней файловой системой чипа ESP8266/ESP32
#if defined(ESP32)
  #define   LittleFS LITTLEFS
  #include <LITTLEFS.h>
#else
  #include <LittleFS.h>
#endif

// =======================================================

#if (A_DEF_PASS == 1)
#include "a_def_pass.h"          // Если здесь ошибка - смотри комментарий к определению A_DEF_PASS выше в начале этого файла
#endif

// =======================================================

#if (DEBUG_SERIAL == 1)
#define DEBUGLN(x)   Serial.println(x)
#define DEBUG(x)     Serial.print(x)
#define DEBUGR(x, r) Serial.print(x, r)
#else
#define DEBUGLN(x)
#define DEBUG(x)
#define DEBUGR(x ,r)
#endif

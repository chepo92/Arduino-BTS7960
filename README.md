# BTS7960 Library

Arduino library for the **BTS7960 (IBT-2)** dual H-Bridge motor driver.

The library provides two abstraction levels:

- **BTS7960Bridge**: Controls an individual bridge (Left or Right) of the BTS7960 module.
- **BTS7960Driver**: Controls both bridges together as a complete RC car (or similar) dual motor driver .

Current sensing through the **L_IS** and **R_IS** pins is supported when available.

---

# Features

- Supports Arduino, ESP8266, ESP32 and most Arduino-compatible boards
- Independent control of the Left and Right bridges
- High-level driver for controlling both bridges together
- Enable/Disable control
- Forward and reverse PWM control
- Current sensing support through **L_IS** and **R_IS**
- Optional ADC resolution configuration

---

# Supported Hardware

- Arduino AVR boards (Uno, Nano, Mega, etc.)
- ESP8266
- ESP32
- Any board supported by the Arduino framework

---

# Installation

Install the library through the Arduino Library Manager or copy it into your `libraries` folder.

## Dependencies

### ESP32

This library depends on:

- **ESP32_AnalogWrite**
  - https://github.com/ERROPiX/ESP32_AnalogWrite

---

# Module Layout

The BTS7960 module exposes two independent bridges labeled:

- **Left (L)** → `L_EN`, `L_PWM`, `L_IS`
- **Right (R)** → `R_EN`, `R_PWM`, `R_IS`

These names correspond to the labels printed on most BTS7960 modules. They may also be considered **Bridge A** and **Bridge B**, depending on the manufacturer.

---

# Constructors

## BTS7960Bridge

Controls one bridge of the BTS7960 module.

```cpp
BTS7960Bridge(
    enablePin,
    forwardPwmPin,
    reversePwmPin,
    currentSensePin,
    adcResolution);
```

Example:

```cpp
BTS7960Bridge leftBridge(
    L_EN,
    L_PWM,
    R_PWM,
    L_IS,
    4095);
```

---

## BTS7960Driver

Controls both bridges simultaneously.

```cpp
BTS7960Driver(
    leftEnable,
    rightEnable,
    leftForwardPwm,
    leftReversePwm,
    rightForwardPwm,
    rightReversePwm,
    leftCurrentSense,
    rightCurrentSense,
    leftAdcResolution,
    rightAdcResolution);
```

Example:

```cpp
BTS7960Driver driver(
    L_EN,
    R_EN,
    L_PWM,
    R_PWM,
    L_PWM2,
    R_PWM2,
    L_IS,
    R_IS,
    4095,
    4095);
```

---

# API Summary

## BTS7960Bridge

| Method | Parameters | Returns | Description |
| :------ | :--------- | :-----: | :---------- |
| **enable()** | none | void | Enables the bridge. |
| **disable()** | none | void | Disables the bridge. |
| **forward()** | `uint8_t pwm` | void | Drives the bridge in the forward direction. |
| **reverse()** | `uint8_t pwm` | void | Drives the bridge in the reverse direction. |
| **stop()** | none | void | Stops PWM output. |
| **currentRaw()** | none | `uint16_t` | Returns the raw ADC reading. |
| **current()** | none | `float` | Returns the current measurement. |

---

## BTS7960Driver

| Method | Parameters | Returns | Description |
| :------ | :--------- | :-----: | :---------- |
| **enable()** | none | void | Enables both bridges. |
| **disable()** | none | void | Disables both bridges. |
| **forward()** | `uint8_t pwm` | void | Drives both bridges forward. |
| **reverse()** | `uint8_t pwm` | void | Drives both bridges in reverse. |
| **stop()** | none | void | Stops both bridges. |

---

# API Reference

## BTS7960Bridge

### enable()

Enables the bridge.

```cpp
bridge.enable();
```

---

### disable()

Disables the bridge.

```cpp
bridge.disable();
```

---

### forward()

Drives the bridge in the forward direction.

```cpp
bridge.forward(180);
```

---

### reverse()

Drives the bridge in the reverse direction.

```cpp
bridge.reverse(180);
```

---

### stop()

Stops PWM output.

```cpp
bridge.stop();
```

---

### currentRaw()

Returns the raw ADC reading.

```cpp
uint16_t raw = bridge.currentRaw();
```

---

### current()

Returns the measured current.

```cpp
float current = bridge.current();
```

---

## BTS7960Driver

### enable()

Enables both bridges.

```cpp
driver.enable();
```

---

### disable()

Disables both bridges.

```cpp
driver.disable();
```

---

### forward()

Drives both bridges forward.

```cpp
driver.forward(180);
```

---

### reverse()

Drives both bridges in reverse.

```cpp
driver.reverse(180);
```

---

### stop()

Stops both bridges.

```cpp
driver.stop();
```

---

# Examples

The library includes two ready-to-use examples in the **examples/** folder.

| Example | Description |
|----------|-------------|
| **BasicControl** | Demonstrates standard motor control using `BTS7960Driver`. |
| **CurrentSense** | Demonstrates current sensing using the `BTS7960Bridge` interface. |

---

# Basic Example

```cpp
#include <BTS7960.h>

BTS7960Driver driver(
    L_EN,
    R_EN,
    L_PWM,
    R_PWM,
    L_PWM2,
    R_PWM2,
    L_IS,
    R_IS,
    4095,
    4095);

void setup()
{
    driver.enable();
}

void loop()
{
    driver.forward(200);
    delay(2000);

    driver.stop();
    delay(500);

    driver.reverse(200);
    delay(2000);

    driver.stop();
    delay(500);
}
```

---

# Advanced Example

Each bridge can also be controlled independently.

```cpp
#include <BTS7960.h>

BTS7960Driver driver(...);

void setup()
{
    driver.left.enable();
    driver.right.enable();
}

void loop()
{
    driver.left.forward(255);
    driver.right.reverse(200);

    Serial.print("Left current: ");
    Serial.println(driver.left.current());

    Serial.print("Right current: ");
    Serial.println(driver.right.current());

    delay(500);
}
```

---

# Notes

- PWM values range from **0** to **255**.
- Always call `enable()` before driving the bridge.
- `disable()` disables the corresponding bridge.
- Current sensing requires the **L_IS** and/or **R_IS** pins to be connected.
- Configure the appropriate ADC resolution for your platform (1023 for most Arduino boards, 4095 for ESP32).

---

# License

Licensed MIT

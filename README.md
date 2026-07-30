# BTS7960 Library

Arduino library for controlling the **BTS7960 (IBT-2)** dual H-Bridge motor driver, capable of driving DC motors up to **43 A** (with adequate cooling and power supply).

The library supports:

- Enable/Disable control
- PWM speed control in both directions
- Active braking
- Current sensing through the **L_IS** and **R_IS** pins (optional)
- Arduino, ESP8266, ESP32, and most Arduino-compatible boards

---

# Supported Hardware

- Arduino AVR boards (Uno, Nano, Mega, etc.)
- ESP8266
- ESP32
- Any board supported by the Arduino framework

---

# Installation

Install the library through the Arduino Library Manager or copy it into your `libraries` folder.

For ESP32, this library depends on:

- **ESP32_AnalogWrite**
  - https://github.com/ERROPiX/ESP32_AnalogWrite

---

# Constructors

## 1. Shared Enable Pin

Use this constructor when both enable inputs are tied together.

```cpp
BTS7960 motor(EN, L_PWM, R_PWM);
```

Example:

```cpp
BTS7960 motor(4, 5, 6);
```

---

## 2. Independent Enable Pins

Use separate enable pins for the left and right half-bridges.

```cpp
BTS7960 motor(L_EN, R_EN, L_PWM, R_PWM);
```

Example:

```cpp
BTS7960 motor(7, 8, 5, 6);
```

---

## 3. Current Sense Support

If your BTS7960 module exposes the **L_IS** and **R_IS** outputs, they can be connected for current monitoring.

```cpp
BTS7960 motor(
    L_EN,
    R_EN,
    L_PWM,
    R_PWM,
    L_IS,
    R_IS
);
```

Example:

```cpp
BTS7960 motor(7, 8, 5, 6, A0, A1);
```

---

## 4. Custom Current Sense Resolution

Allows specifying the ADC resolution used for each current sense input.

```cpp
BTS7960 motor(
    L_EN,
    R_EN,
    L_PWM,
    R_PWM,
    L_IS,
    R_IS,
    L_IS_RES,
    R_IS_RES
);
```

Example:

```cpp
BTS7960 motor(
    7,
    8,
    5,
    6,
    A0,
    A1,
    4095,
    4095
);
```

Typical values:

| Platform | ADC Resolution |
|----------|---------------:|
| Arduino AVR | 1023 |
| ESP8266 | 1023 |
| ESP32 | 4095 |

---
---

# Examples

The library includes two ready-to-use examples in the **examples/** folder:

| Example | Description |
|----------|-------------|
| **BasicControl** | Demonstrates standard motor control using Enable(), TurnLeft(), TurnRight(), Stop(), and Disable(). |
| **CurrentSense** | Demonstrates how to use the current sensing inputs (L_IS and R_IS) to measure motor current while driving the motor. |

These examples provide a good starting point for most applications.

---

# API Summary

| Method | Parameters | Returns | Description |
| :----- | :--------- | :-----: | :---------- |
| **Enable()** | none | void | Enables the motor driver. |
| **Disable()** | none | void | Disables the driver (motor coasts freely). |
| **Stop()** | none | void | Applies active braking. |
| **TurnLeft()** | `uint8_t pwm` | void | Rotates the motor in the forward direction at the specified PWM duty cycle. |
| **TurnRight()** | `uint8_t pwm` | void | Rotates the motor in the reverse direction at the specified PWM duty cycle. |
| **CurrentSenseLeft()** | none | `float` | Returns the estimated current measured on the left half-bridge. Requires **L_IS** to be connected. |
| **CurrentSenseRight()** | none | `float` | Returns the estimated current measured on the right half-bridge. Requires **R_IS** to be connected. |

---

# API Reference

## Enable()

Enables the motor driver.

```cpp
motor.Enable();
```

---

## Disable()

Disables the driver, leaving the motor in freewheel (coast).

```cpp
motor.Disable();
```

---

## TurnLeft()

Drives the motor in the forward direction.

```cpp
motor.TurnLeft(pwm);
```

Parameter:

| Name | Type | Range |
|------|------|------|
| pwm | uint8_t | 0–255 |

Example:

```cpp
motor.TurnLeft(180);
```

---

## TurnRight()

Drives the motor in the reverse direction.

```cpp
motor.TurnRight(pwm);
```

Parameter:

| Name | Type | Range |
|------|------|------|
| pwm | uint8_t | 0–255 |

Example:

```cpp
motor.TurnRight(255);
```

---

## Stop()

Actively brakes the motor.

```cpp
motor.Stop();
```

---

## CurrentSenseLeft()

Returns the estimated current flowing through the left half-bridge.

```cpp
float current = motor.CurrentSenseLeft();
```

Returns:

- Current in amperes.

Requires the **L_IS** pin to be connected.

---

## CurrentSenseRight()

Returns the estimated current flowing through the right half-bridge.

```cpp
float current = motor.CurrentSenseRight();
```

Returns:

- Current in amperes.

Requires the **R_IS** pin to be connected.

---

# Example

```cpp
#include <BTS7960.h>

BTS7960 motor(4, 5, 18);

void setup()
{
    motor.Enable();
}

void loop()
{
    motor.TurnLeft(200);
    delay(2000);

    motor.Stop();
    delay(500);

    motor.TurnRight(200);
    delay(2000);

    motor.Stop();
    delay(500);
}
```

---

# Notes

- PWM values range from **0** to **255**.
- Call `Enable()` before commanding the motor.
- `Disable()` places the outputs in a high-impedance state, allowing the motor to spin freely.
- `Stop()` performs active braking.
- Current sensing requires the module's **L_IS** and **R_IS** pins to be wired to ADC-capable inputs.
- On ESP32, set the correct ADC resolution when using custom analog configurations.

---

# License

MIT License.

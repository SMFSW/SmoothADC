# SmoothADC

[![author](https://img.shields.io/endpoint?url=https://gist.githubusercontent.com/SMFSW/a9a2b2a02fda1b33461d53ddfe69d649/raw/auth_SMFSW.json)](https://github.com/SMFSW)
![badge](https://img.shields.io/endpoint?url=https://gist.githubusercontent.com/SMFSW/a9a2b2a02fda1b33461d53ddfe69d649/raw/SmoothADC_status_badge.json)
[![license](https://img.shields.io/badge/License-GNU_LGPL-darkgreen.svg)](LICENSE)
[![CodeFactor](https://www.codefactor.io/repository/github/smfsw/smoothadc/badge)](https://www.codefactor.io/repository/github/smfsw/smoothadc)

![platform](https://img.shields.io/endpoint?url=https://gist.githubusercontent.com/SMFSW/a9a2b2a02fda1b33461d53ddfe69d649/raw/platform_INO.json)

[![doxy](https://img.shields.io/endpoint?url=https://gist.githubusercontent.com/SMFSW/a9a2b2a02fda1b33461d53ddfe69d649/raw/tool_DOXY.json)](https://smfsw.github.io/SmoothADC)
[![re_note](https://img.shields.io/endpoint?url=https://gist.githubusercontent.com/SMFSW/a9a2b2a02fda1b33461d53ddfe69d649/raw/tool_RN.json)](ReleaseNotes.md)

Arduino library for smooth ADC results

The SmoothADC library helps filtering ADC values when smoother evolution of values is needed (getting rid of pikes for example).
4 values, average on mid ones.

I tried to keep the lib as tiny as possible.

## Usage

- Declare a `SmoothADC` instance (called `adc` below)
- Initialize instance with `adc.init(Pin, Resolution, Period)`
  - `Pin`: adc pin
  - `Resolution`: timing resolution (us/ms)
  - `Period`: sample rate
- `adc.serviceADCPin()`: Method to service the ADC pin when module is enabled (should be placed somewhere in the main loop)
- `adc.getADCVal()`: Get the average ADC pin value (should replace usual analogRead)
- `adc.setPin(pin)`: Set ADC pin to service
- `adc.setResolution(resolution)`: Set Resolution of ADC pin to service (us/ms)
- `adc.setPeriod(period)`: Set sample rate of servicing
- `adc.getPin()`: Get the serviced ADC pin
- `adc.getResolution()`: Get the resolution for the serviced ADC pin
- `adc.getPeriod()`: Get the sample rate of the serviced pin
- `adc.enable()`: Enable ADC smoothing module
- `adc.disable()`: Disable ADC smoothing module
- `adc.isEnabled()`: Test if ADC smoothing is enabled
- `adc.isDisabled()`: Test if ADC smoothing is disabled

## Examples included

- [SmoothADCExample.ino](examples/SmoothADCExample/SmoothADCExample.ino)

This example defines A0 & A1 (analog inputs) to be handled by SmoothADC library

Samples every 50ms for A0

Samples every 500us for A1

Every second, the average value from A0 & A1 are sent to serial port

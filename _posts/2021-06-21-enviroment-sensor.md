---
layout: post
title: Environment Sensor with Display
description: An Arduino Project
date: 2021-06-21
img: /assets/enviro_sensor/img/screen.png
thumbnail: /assets/enviro_sensor/img/screen-thumb.png
importance: 1
# category: fun
tags: arduino sensors embedded-systems
# related_publications: einstein1956investigations, einstein1950meaning
---

Initially developed as a automation tool for gardening, this device monitors qualities of air, light, and soil in its environment.

------
## Overview

The purpose of this device is to monitor its environment. It measures air pressure, temperature, humidity, volatile organic compounds (VOCs), ambient light luminosity, crude spectral analysis, and soil moisture. The exterior shell is 3D printed PLA, folded into its final shape. It's controlled, and powered, using an Arduino Nano Sense BLE.

### Peripherals

The device takes advantage of several sensors, external and onboard, and a screen to display the information on. Below is a description of each:

* [BME680 Air Quality Sensor](https://learn.adafruit.com/adafruit-bme680-humidity-temperature-barometic-pressure-voc-gas/overview)
  - Temperature, pressure, humidity, VOCs
  - I2C/SPI
  - Requires calibration

* [TSL2591 HDR Light Sensor](https://learn.adafruit.com/adafruit-tsl2591)
  - Luminosity
  - I2C
  - Contains IR diodes

* [GUVA UV Sensor](https://www.adafruit.com/product/1918)
  - UVB/UVA (240-370nm)
  - Analog

* [ADPS9960 Light Sensor](https://www.adafruit.com/product/3595)
  - RGB color sensing
  - Onboard Arduino Sense
  - Contains IR detectors

* [DFRobot Soil Sensor](https://wiki.dfrobot.com/Capacitive_Soil_Moisture_Sensor_SKU_SEN0193)
  - Capacitive moisture sensing
  - Analog
  - Requires calibration

* [ST7789 1.54" TFT Display](https://wiki.dfrobot.com/1.54%20Inches%20240_240_IPS_TFT_LCD_Display_with_MicroSD_Card_Breakout_SKU_DFR0649)
  - 240x240 pixels
  - SPI communication

### Enclosure

I decided to work with a folding assembly technique. This makes mounting the sensors easy in a small space while also simplifying the design. Below is an early shot of the foldable layout.

<p>
    <center><img src="/assets/enviro_sensor/img/foldy_face.png" width="80%;" height="100%;" alt/>
    <br>
    <em>Figure 1: 3D model of enclosure</em></center>
</p>

## Control

A few libraries need to be included for the sensors to operate. I found Adafruit's display library easier to use than DFRobot's. Some of the sensors need to be initialized beforehand, notably the VOC. It's recommended that it run for 30 mins while in use. "This is because the sensitivity levels of the sensor will change during early use and the resistance will slowly rise over time as the MOX warms up to its baseline reading." - [Adafruit BME680 Overview](https://learn.adafruit.com/adafruit-bme680-humidity-temperature-barometic-pressure-voc-gas/overview). For this reasion, the device has a 5 minute warm-up period before displaying VOC data.

> `  bme.setGasHeater(320, 150); // 320*C for 150 ms`

Likewise, the TSL2591 has a special initialization parameters:

> ` void configureTSL2591(void){`
>
> `  tsl.setGain(TSL2591_GAIN_MED);      // 25x gain`
> `  tsl.setTiming(TSL2591_INTEGRATIONTIME_300MS);`
> `  tsl2591Gain_t gain = tsl.getGain();`
>
> `}`

The controller assumes the TSL2591 and the APDS9960 have the same spectral response. First, the TSL2591 has two photodiodes: Visible spectrum + Infrared (VS+IR) response, and Infrared (IR) response. Subtracting the IR photodiode activity from the VS+IR activity leaves visible light. See Figure 2, left. 

Spectral responses are different, but similar enough to each other for this trick to work. The ADPS9960 might exhibit more activity towards the lowered end of the spectrum. Even though we're strictly using the RGB channels, this will present a slight bias towards blue later in the project.

<div class="img_row">
  <img class="col two" src="/assets/enviro_sensor/img/tsl2591_spectrum.png">
  <img class="col two" src="/assets/enviro_sensor/img/apds9960_spectrum.png" style="float: right">
</div>
<div class="col three caption">
  Figure 2: left, TSL2591 spectral response; right, onboard APDS9960 spectral response
</div>

The GUVA UV wavelength response is ~240-380nm, just out of reach of the APDS9960. Because of this, there's no way to estimate how much luminosity is in the UV range<sup>*</sup>. This is a good excuse for a better UV sensor!

<h6>I didn't know of a way off hand and left it at that.</h6>

<div class="img_row">
  <img class="col three" src="/assets/enviro_sensor/img/guva_spectrum.png">
</div>
<div class="col three caption">
  Figure 3: GUVA responsivity curve
</div>

From here, we normalize color activity by dividing each color channel by the sum of all color channels:

> red % = r/(r+g+b)
>
> green % = g/(r+g+b)
>
> blue % = b/(r+g+b)

We use these values with the visible light data to give us RGB luminosity data. With this and the IR luminosity data earlier, we can make a "full spectrum" wavelength response graph. 

<p>
    <center><img src="/assets/enviro_sensor/img/screen.png" width="80%;" height="100%;" alt/>
    <br>
    <em>Figure 4: Spectral data displayed on screen</em></center>
</p>

<br>
We'll never know why I took screenshots instead of saving the original responsivity figures
#include <SPI.h>              // Arduino SPI library
#include <Wire.h>

#include <Adafruit_Sensor.h>  // Core sensor library
#include <Adafruit_GFX.h>     // Core graphics library
#include <Arduino_HTS221.h>   // Onboard temp / humidity sensor library
#include <Arduino_APDS9960.h> // Onboard light sensor library
#include <Arduino_LPS22HB.h>  // Onboard pressure sensor library

#include <Adafruit_ST7789.h>  // ST7789 driver library
#include "Adafruit_BME680.h"  // BME680 sensor library
#include "Adafruit_TSL2591.h" // TSL2591 sensor library

// SPI Modules
#define BME_CS     7  // define BME680 chip select pin

#define TFT_CS    10  // define chip select pin
#define TFT_DC     9  // define data/command pin
#define TFT_RST    8  // define reset pin, or set to -1 and connect to Arduino RESET pin

// Analog Pins
#define soil_pin  A6  // define analog pin for soil sensor
#define UV_pin    A7  // define analog pin for UV sensor

// Initialize Adafruit ST7789 TFT library
Adafruit_ST7789 tft = Adafruit_ST7789(TFT_CS, TFT_DC, TFT_RST);
Adafruit_BME680 bme(BME_CS);
Adafruit_TSL2591 tsl = Adafruit_TSL2591(2591);

// Light sensor variables
int proximity = 0;
int r = 0, g = 0, b = 0;
unsigned long lastUpdate = 0;
int UVsensor = 0;  // variable to store the value coming from the sensor

// Soil sensor variables
const int AirValue = 782;   //you need to replace this value with Value_1
const int WaterValue = 416;  //you need to replace this value with Value_2
int intervals = (AirValue - WaterValue)/3;
int soilMoistureValue = 0;

void setup() {

  Serial.begin(9600);

  if (!HTS.begin()) {
    Serial.println("Failed to initialize HTS221 sensor!");
    while (1);
  }

  if (!APDS.begin()) {
    Serial.println("Failed to initialize APDS9960 sensor!");
    while (true); // Stop forever
  }

  if (!BARO.begin()) {
    Serial.println("Failed to initialize LPS22HB sensor!");
    while (1);
  }

  if (!bme.begin()) {
    Serial.println("Failed to initialize BME680 sensor!");
    while (1);
  }
  if (!tsl.begin()) {
    Serial.println(F("Failed to initialize TSL2591 sensor!"));
    while (1);
  }

  // Initialize BME680
  bme.setTemperatureOversampling(BME680_OS_8X);
  bme.setHumidityOversampling(BME680_OS_2X);
  bme.setPressureOversampling(BME680_OS_4X);
  bme.setIIRFilterSize(BME680_FILTER_SIZE_3);
  bme.setGasHeater(320, 150); // 320*C for 150 ms

  // Initialize Screen
  tft.init(240, 240, SPI_MODE2);    // Init ST7789 display 240x240 pixel
  tft.setRotation(3);
  tft.setCursor(0, 0);
  tft.setTextWrap(false);
  tft.setTextSize(2);
  tft.fillScreen(ST77XX_BLACK);

  // Initialize TSL2591
  configureTSL2591();
  
}

void loop() {
  // put your main code here, to run repeatedly:
  tft.setCursor(0, 0);
  tft.setTextColor(ST77XX_WHITE, ST77XX_BLACK);

  do_runtime();
  tft.println();
  do_temperature();
  do_humidity();
  do_pressure();
  do_gas();
  tft.println();
  do_light();
  tft.println();
  do_uv();
  tft.println();
  do_dirt();
}

void do_runtime() {
  tft.setTextColor(ST77XX_WHITE, ST77XX_BLACK);
  tft.print("Runtime: ");
  tft.setTextColor(ST77XX_MAGENTA, ST77XX_BLACK);
  tft.print(millis() / 1000);
  tft.setTextColor(ST77XX_WHITE, ST77XX_BLACK);
  tft.println(" s");
}

void do_temperature() {
  float temperature = ((1.25 * bme.temperature) + (1.75 * HTS.readTemperature())) / 2;
  float temperature_F = (temperature * (9 / 5)) + 32;

  tft.print("Temp: ");
  tft.print(temperature_F);
  tft.println(" *F");
}

void do_humidity() {
  float humidity = (bme.humidity + HTS.readHumidity()) / 2;

  tft.print("Hum:  ");
  tft.print(humidity);
  tft.println(" %");
}

void do_pressure() {
  float pressure = ((bme.pressure / 1000.0) + BARO.readPressure()) / 2;

  tft.print("Baro: ");
  tft.print(pressure);
  tft.println(" kPa");
}

void do_gas() {
  tft.print("Gas: ");

  if ((millis() / 1000) > 1800) {
    tft.print(bme.gas_resistance / 1000.0);
    tft.println(" kOhms");
  } else {
    tft.println("STABLIZING");
  }
}

void do_light() {

  uint32_t lum = tsl.getFullLuminosity();
  uint16_t ir, full, vis;
  ir = lum >> 16;
  full = lum & 0xFFFF;
  vis = full - ir;
  
  if (APDS.colorAvailable()) {
    APDS.readColor(r, g, b);
  }
//  rgb_total = r+g+b;

  float ir_percent = 1.0*ir/full;
  float vis_percent = 1.0*vis/full;
  float r_percent = vis_percent*1.0*r/(r+g+b);
  float g_percent = vis_percent*1.0*g/(r+g+b);
  float b_percent = vis_percent*1.0*b/(r+g+b);
  
  if (! bme.performReading()) {
    tft.println("Failed to perform reading :(");
    return;
  }
  tft.print("Light: ");
  tft.print(tsl.calculateLux(full, ir));
  tft.println(" Lux   ");
  tft.println();
  tft.println();
  tft.fillRect(0, 135, ir_percent*tft.width(), 6, ILI9341_RED << 3);
  tft.fillRect(ir_percent*tft.width()+1, 135, tft.width(), 6, ST77XX_BLACK);
  tft.fillRect(0, 142, r_percent*tft.width(), 6, ST77XX_RED);
  tft.fillRect(r_percent*tft.width()+1, 142, tft.width(), 6, ST77XX_BLACK);
  tft.fillRect(0, 149, g_percent*tft.width(), 6, ILI9341_GREEN << 2);
  tft.fillRect(g_percent*tft.width()+1, 149, tft.width(), 6, ST77XX_BLACK);
  tft.fillRect(0, 156, b_percent*tft.width(), 6, ST77XX_BLUE);
  tft.fillRect(b_percent*tft.width()+1, 156, tft.width(), 6, ST77XX_BLACK);  
}

void do_uv() {
  UVsensor = (analogRead(UV_pin));
  float v_calc = (5 * UVsensor / 1023.0) * 1000;

  tft.setTextColor(ST77XX_WHITE, ST77XX_BLACK);
  tft.print("UV Index: ");
//  tft.println(UVsensor);
  if (v_calc <= 50) {
    tft.setTextColor(ST77XX_BLACK << 8, ST77XX_BLACK);
    tft.println("None      ");
  }
  else if (v_calc > 50 && v_calc <= 227) {
    tft.setTextColor(ST77XX_GREEN, ST77XX_BLACK);
    tft.println("Good      ");
  }
  else if (v_calc > 227 && v_calc <= 318) {
    tft.setTextColor(ST77XX_GREEN << 2, ST77XX_BLACK);
    tft.println("Good      ");
  }
  else if (v_calc > 318 && v_calc <= 408) {
    tft.setTextColor(ST77XX_GREEN << 4, ST77XX_BLACK);
    tft.println("Good      ");
  }
  else if (v_calc > 408 && v_calc <= 503) {
    tft.setTextColor(ST77XX_YELLOW, ST77XX_BLACK);
    tft.println("ok        ");
  }
  else if (v_calc > 503 && v_calc <= 606) {
    tft.setTextColor(ST77XX_YELLOW << 2, ST77XX_BLACK);
    tft.println("ok        ");
  }
  else if (v_calc > 606 && v_calc <= 696) {
    tft.setTextColor(ST77XX_ORANGE, ST77XX_BLACK);
    tft.println("moderate  ");
  }
  else if (v_calc > 696 && v_calc <= 795) {
    tft.setTextColor(ST77XX_ORANGE << 2, ST77XX_BLACK);
    tft.println("moderate  ");
  }
  else if (v_calc > 795 && v_calc <= 1079) {
    tft.setTextColor(ST77XX_RED, ST77XX_BLACK);
    tft.println("BAD       ");
  }
  else {
    tft.setTextColor(ST77XX_MAGENTA, ST77XX_BLACK);
    tft.println("SEVERE    ");
  }
}

void do_dirt(){
  
  soilMoistureValue = analogRead(soil_pin);  //put Sensor insert into soil

  tft.setTextColor(ST77XX_WHITE, ST77XX_BLACK);
  tft.print("Soil: ");
//  tft.print(soilMoistureValue);
  if(soilMoistureValue > WaterValue && soilMoistureValue < (WaterValue + intervals)){
    tft.setTextColor(ST77XX_BLUE, ST77XX_BLACK);
    tft.println("Very Wet");
  }
  else if(soilMoistureValue > (WaterValue + intervals) && soilMoistureValue < (AirValue - intervals)){
    tft.setTextColor(ST77XX_CYAN, ST77XX_BLACK);
    tft.println("Wet     ");
  }
  else if(soilMoistureValue < AirValue && soilMoistureValue > (AirValue - intervals)){
    tft.setTextColor(ST77XX_YELLOW, ST77XX_BLACK);
    tft.println("Dry     ");
  }
  tft.setTextColor(ST77XX_WHITE, ST77XX_BLACK);
}

void configureTSL2591(void)
{
  // You can change the gain on the fly, to adapt to brighter/dimmer light situations
  //tsl.setGain(TSL2591_GAIN_LOW);    // 1x gain (bright light)
  tsl.setGain(TSL2591_GAIN_MED);      // 25x gain
  //tsl.setGain(TSL2591_GAIN_HIGH);   // 428x gain
  
  // Changing the integration time gives you a longer time over which to sense light
  // longer timelines are slower, but are good in very low light situtations!
  //tsl.setTiming(TSL2591_INTEGRATIONTIME_100MS);  // shortest integration time (bright light)
  // tsl.setTiming(TSL2591_INTEGRATIONTIME_200MS);
  tsl.setTiming(TSL2591_INTEGRATIONTIME_300MS);
  // tsl.setTiming(TSL2591_INTEGRATIONTIME_400MS);
  // tsl.setTiming(TSL2591_INTEGRATIONTIME_500MS);
  // tsl.setTiming(TSL2591_INTEGRATIONTIME_600MS);  // longest integration time (dim light)

  /* Display the gain and integration time for reference sake */  
//  Serial.println(F("------------------------------------"));
//  Serial.print  (F("Gain:         "));
  tsl2591Gain_t gain = tsl.getGain();
//  switch(gain)
//  {
//    case TSL2591_GAIN_LOW:
//      Serial.println(F("1x (Low)"));
//      break;
//    case TSL2591_GAIN_MED:
//      Serial.println(F("25x (Medium)"));
//      break;
//    case TSL2591_GAIN_HIGH:
//      Serial.println(F("428x (High)"));
//      break;
//    case TSL2591_GAIN_MAX:
//      Serial.println(F("9876x (Max)"));
//      break;
//  }
//  Serial.print  (F("Timing:       "));
//  Serial.print((tsl.getTiming() + 1) * 100, DEC); 
//  Serial.println(F(" ms"));
//  Serial.println(F("------------------------------------"));
//  Serial.println(F(""));
}

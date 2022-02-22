#pragma once

const Temperaturelimits limitsforcoolingtype[3] = {{0,35},{0,45},{0,40}}; 

typedef enum {
  PASSIVE_COOLING,
  HI_ACTIVE_COOLING,
  MED_ACTIVE_COOLING
} CoolingType;

typedef enum {
  NORMAL,
  TOO_LOW,
  TOO_HIGH
} BreachType;

BreachType inferBreach(double value, double lowerLimit, double upperLimit);
BreachType classifyTemperatureBreach(CoolingType coolingType, double temperatureInC);
BreachType findPassiveCollingTemperatureBreach(double temperatureInC);
BreachType findHighActiveCollingTemperatureBreach(double temperatureInC);
BreachType findMediumActiveCollingTemperatureBreach(double temperatureInC);

typedef enum {
  TO_CONTROLLER,
  TO_EMAIL
} AlertTarget;

typedef struct {
  CoolingType coolingType;
  char brand[48];
} BatteryCharacter;

typedef struct {
  double lowerlimit;
  double upperlimit;
} Temperaturelimits;

int checkAndAlert(
  AlertTarget alertTarget, BatteryCharacter batteryChar, double temperatureInC);

void sendToController(BreachType breachType);
void sendToEmail(BreachType breachType);

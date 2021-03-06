#pragma once


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

typedef struct {
  double lowerlimit;
  double upperlimit;
} Temperaturelimits;

typedef enum {
  CONTROLLERMODE,
  EMAILMODE
} AlertMode;

BreachType inferBreach(double value, Temperaturelimits limits);
BreachType classifyTemperatureBreach(CoolingType coolingType, double temperatureInC);

typedef enum {
  TO_CONTROLLER,
  TO_EMAIL
} AlertTarget;

typedef struct {
  CoolingType coolingType;
  char brand[48];
} BatteryCharacter;


AlertMode checkAndAlert(
  AlertTarget alertTarget, BatteryCharacter batteryChar, double temperatureInC);

AlertMode sendToController(BreachType breachType);
AlertMode sendToEmail(BreachType breachType);

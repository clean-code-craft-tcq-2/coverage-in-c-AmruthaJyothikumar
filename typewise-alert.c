#include "typewise-alert.h"
#include <stdio.h>
  
BreachType inferBreach(double value, Temperaturelimits) {
  if(value < Temperaturelimits.lowerlimit) {
    return TOO_LOW;
  }
  if(value > Temperaturelimits.upperlimit) {
    return TOO_HIGH;
  }
  return NORMAL;
}


BreachType classifyTemperatureBreach(
    CoolingType coolingType, double temperatureInC) {
  return inferBreach(double temperatureInC,limitsforcoolingtype[coolingType]; 
}

      
int checkAndAlert(
    AlertTarget alertTarget, BatteryCharacter batteryChar, double temperatureInC) {

  BreachType breachType = classifyTemperatureBreach(
    batteryChar.coolingType, temperatureInC
  );

  switch(alertTarget) {
    case TO_CONTROLLER:
      sendToController(breachType);
      return 0;
      break;
    case TO_EMAIL:
      sendToEmail(breachType);
      return 1;
      break;
  }
}

void sendToController(BreachType breachType) {
  const unsigned short header = 0xfeed;
  printf("%x : %x\n", header, breachType);
}

void sendToEmail(BreachType breachType) {
  const char* recepient = "a.b@c.com";
  switch(breachType) {
    case TOO_LOW:
      printf("To: %s\n", recepient);
      printf("Hi, the temperature is too low\n");
      break;
    case TOO_HIGH:
      printf("To: %s\n", recepient);
      printf("Hi, the temperature is too high\n");
      break;
    case NORMAL:
      break;
  }
}

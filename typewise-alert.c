#include "typewise-alert.h"
#include <stdio.h>

BreachType inferBreach(double value, double lowerLimit, double upperLimit) {
  if(value < lowerLimit) {
    return TOO_LOW;
  }
  if(value > upperLimit) {
    return TOO_HIGH;
  }
  return NORMAL;
}

BreachType classifyTemperatureBreach(
    CoolingType coolingType, double temperatureInC) {

  switch(coolingType) {
     case PASSIVE_COOLING: 
          return findPassiveCollingTemperatureBreach(temperatureInC);
          break;
     case HI_ACTIVE_COOLING: 
          return findHighActiveCollingTemperatureBreach(temperatureInC);
          break;
     case MED_ACTIVE_COOLING: 
          return findMediumActiveCollingTemperatureBreach(temperatureInC);
          break;
   }  
}

BreachType findPassiveCollingTemperatureBreach(
     double temperatureInC) {
   int lowerLimit = 0;
    int upperLimit = 35; 
    return inferBreach(temperatureInC, lowerLimit, upperLimit);
}

BreachType findHighActiveCollingTemperatureBreach(
     double temperatureInC) {
    int lowerLimit = 0;
    int upperLimit = 45; 
    return inferBreach(temperatureInC, lowerLimit, upperLimit);
}

BreachType findMediumActiveCollingTemperatureBreach(
     double temperatureInC) {
    int lowerLimit = 0;
    int upperLimit = 40; 
    return inferBreach(temperatureInC, lowerLimit, upperLimit);
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

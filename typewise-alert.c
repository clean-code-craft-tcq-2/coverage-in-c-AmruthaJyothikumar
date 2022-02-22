#include "typewise-alert.h"
#include <stdio.h>
  
const Temperaturelimits limitsforcoolingtype[3] = {{0,35},{0,45},{0,40}}; 
AlertMode (*Functionmodeofalert[])(BreachType breachType) = {sendToController,sendToEmail};

BreachType inferBreach(double value, Temperaturelimits limits) {
  if(value < limits.lowerlimit) {
    return TOO_LOW;
  }
  if(value > limits.upperlimit) {
    return TOO_HIGH;
  }
  return NORMAL;
}

BreachType classifyTemperatureBreach(
    CoolingType coolingType, double temperatureInC) {
  return inferBreach(temperatureInC,limitsforcoolingtype[coolingType]); 
}
    
AlertMode checkAndAlert(
    AlertTarget alertTarget, BatteryCharacter batteryChar, double temperatureInC) {

  BreachType breachType = classifyTemperatureBreach(
    batteryChar.coolingType, temperatureInC
  );
  return (*Functionmodeofalert[alertTarget])(breachType);    
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

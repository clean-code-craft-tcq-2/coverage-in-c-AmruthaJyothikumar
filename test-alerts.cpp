#define CATCH_CONFIG_MAIN  // This tells Catch to provide a main() - only do this in one cpp file

#include "test/catch.hpp"
#include "typewise-alert.h"

TEST_CASE("infers the breach according to limits") {
  REQUIRE(inferBreach(0, {0,35}) == TOO_LOW);
  REQUIRE(inferBreach(50, {0,45}) == TOO_HIGH);
  REQUIRE(inferBreach(12, {0,40}) == NORMAL);
}

TEST_CASE("classify the temperature breach") {
  REQUIRE(classifyTemperatureBreach(PASSIVE_COOLING,-5) == TOO_LOW);
  REQUIRE(classifyTemperatureBreach(PASSIVE_COOLING,40) == TOO_HIGH);
  REQUIRE(classifyTemperatureBreach(PASSIVE_COOLING,10) == NORMAL);
  
  REQUIRE(classifyTemperatureBreach(HI_ACTIVE_COOLING,-5) == TOO_LOW);
  REQUIRE(classifyTemperatureBreach(HI_ACTIVE_COOLING,50) == TOO_HIGH);
  REQUIRE(classifyTemperatureBreach(HI_ACTIVE_COOLING,30) == NORMAL); 
  
  REQUIRE(classifyTemperatureBreach(MED_ACTIVE_COOLING,-5) == TOO_LOW);
  REQUIRE(classifyTemperatureBreach(MED_ACTIVE_COOLING,55) == TOO_HIGH);
  REQUIRE(classifyTemperatureBreach(MED_ACTIVE_COOLING,30) == NORMAL);   
}

TEST_CASE("alters breachtype for passive cooling") {
  BatteryCharacter batteryChar;
  batteryChar.coolingType =  PASSIVE_COOLING;
  REQUIRE(checkAndAlert(TO_CONTROLLER, batteryChar, 40) == 0);
  REQUIRE(checkAndAlert(TO_CONTROLLER, batteryChar, 10) == 0);
  REQUIRE(checkAndAlert(TO_CONTROLLER, batteryChar, -5) == 0);
  
  REQUIRE(checkAndAlert(TO_EMAIL, batteryChar, 40) == 1);
  REQUIRE(checkAndAlert(TO_EMAIL, batteryChar, 10) == 1);
  REQUIRE(checkAndAlert(TO_EMAIL, batteryChar, -5) == 1);
}

TEST_CASE("alters breachtype for hi_active cooling") {
  BatteryCharacter batteryChar;
  batteryChar.coolingType =  HI_ACTIVE_COOLING;
  REQUIRE(checkAndAlert(TO_CONTROLLER, batteryChar, 40) == 0);
  REQUIRE(checkAndAlert(TO_CONTROLLER, batteryChar, 10) == 0);
  REQUIRE(checkAndAlert(TO_CONTROLLER, batteryChar, -5) == 0);
  
  REQUIRE(checkAndAlert(TO_EMAIL, batteryChar, 40) == 1);
  REQUIRE(checkAndAlert(TO_EMAIL, batteryChar, 10) == 1);
  REQUIRE(checkAndAlert(TO_EMAIL, batteryChar, -5) == 1);
}

TEST_CASE("alters breachtype for med_active cooling") {
  BatteryCharacter batteryChar;
  batteryChar.coolingType =  MED_ACTIVE_COOLING;
  REQUIRE(checkAndAlert(TO_CONTROLLER, batteryChar, 40) == 0);
  REQUIRE(checkAndAlert(TO_CONTROLLER, batteryChar, 10) == 0);
  REQUIRE(checkAndAlert(TO_CONTROLLER, batteryChar, -5) == 0);
  
  REQUIRE(checkAndAlert(TO_EMAIL, batteryChar, 40) == 1);
  REQUIRE(checkAndAlert(TO_EMAIL, batteryChar, 10) == 1);
  REQUIRE(checkAndAlert(TO_EMAIL, batteryChar, -5) == 1);
}


#include <Arduino.h>

#define HOT_TEMPERATURE_TRESHOLD         (770) // 35C
#define COLD_TEMPERATURE_TRESHOLD        (420) // 10C
#define HUMID_AIR_TRESHOLD               (HOT_TEMPERATURE_TRESHOLD) // TODO Experimental
#define DRY_AIR_TRESHOLD                 (COLD_TEMPERATURE_TRESHOLD) // TODO Experimental

#define FANS_PIN                         (2)
#define FOUNTAIN_PIN                     (3)
#define HEATING_SYSTEM_PIN               (4)
#define COOLING_SYSTEM_PIN               (5)
#define TEMPERATURE_SENSOR_PIN           (A0)
#define MOISTURE_SENSOR_PIN              (A1)

#define SECOND                           (1000)
#define MINUTE                           (SECOND * 60)
#define HOUR                             (MINUTE * 60)

typedef enum {
  OFF,
  ON
} STATE;

uint16_t volatile current_temperature;
uint16_t volatile current_moisture;

bool isHot(uint16_t temperature) { return (temperature > HOT_TEMPERATURE_TRESHOLD); }
bool isCold(uint16_t temperature) { return (temperature < COLD_TEMPERATURE_TRESHOLD); }
bool isHumid(uint16_t moisture) { return (moisture > HUMID_AIR_TRESHOLD); }
bool isDry(uint16_t moisture) { return (moisture < DRY_AIR_TRESHOLD); }

// cool the environment
void coolingSystem( STATE s ) { digitalWrite( COOLING_SYSTEM_PIN, s ); }

// heat the environment
void heatingSystem( STATE s) { digitalWrite( HEATING_SYSTEM_PIN, s ); }

// increse Moisture levels
void fountainSystem( STATE s) { digitalWrite( FOUNTAIN_PIN, s ); }

// reduce Moisture levels
void ventilationSystem( STATE s) { digitalWrite( FANS_PIN, s ); }

void setup() {
  pinMode(FANS_PIN,           OUTPUT);
  pinMode(FOUNTAIN_PIN,       OUTPUT);
  pinMode(HEATING_SYSTEM_PIN, OUTPUT);
  pinMode(COOLING_SYSTEM_PIN, OUTPUT);
}

void loop() {
  current_temperature = analogRead(TEMPERATURE_SENSOR_PIN);
  current_moisture = analogRead(MOISTURE_SENSOR_PIN);

  isHot   ( current_temperature ) ? coolingSystem     ( ON ) : coolingSystem     ( OFF );
  isCold  ( current_temperature ) ? heatingSystem     ( ON ) : heatingSystem     ( OFF );
  isHumid ( current_moisture )    ? fountainSystem    ( ON ) : fountainSystem    ( OFF );
  isDry   ( current_moisture )    ? ventilationSystem ( ON ) : ventilationSystem ( OFF );
  
  delay(2 * MINUTE);
}
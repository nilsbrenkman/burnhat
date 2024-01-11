
 * Project LedCube
 * Description:
 * Author:
 * Date:
 */

#include "application.h"
#include "CubeController.h"

void setup();
void loop();

CubeController * cube_controller;

void setup() {
  Serial.begin(9600);

  pinMode(LED_DATA_PIN,  OUTPUT);
  pinMode(LED_CLOCK_PIN, OUTPUT);
  pinMode(LED_LATCH_PIN, OUTPUT);

  cube_controller = new CubeController();

  delay(500);
}

void loop() {

  cube_controller->refresh();
  
}

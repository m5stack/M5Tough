#include <M5Tough.h>

// This program tested for M5Buttons

ButtonColors on_clrs = {BLUE, WHITE, WHITE};
ButtonColors off_clrs = {BLACK, WHITE, WHITE};
Button bl(20, 200, 80, 40, false, "A", off_clrs, on_clrs, MC_DATUM);
Button b2(120, 200, 80, 40, false, "B", off_clrs, on_clrs, MC_DATUM);
Button b3(220, 200, 80, 40, false, "C", off_clrs, on_clrs, MC_DATUM);

void eventDisplay(Event& e) {
  M5.Lcd.fillRect(0, 0, 320, 150, BLACK);
  Serial.printf("%-12s finger%d  %-18s (%3d, %3d) --> (%3d, %3d)   ",
                e.typeName(), e.finger, e.objName(), e.from.x, e.from.y,
                e.to.x, e.to.y);

  Serial.printf("( dir %d deg, dist %d, %d ms )\r\n", e.direction(),
                e.distance(), e.duration);

  char info[50];
  //print the button name
  sprintf(info, "Btn %s wasPressed", e.objName());
  M5.Lcd.drawString(info, 160, 100);
}

void setup() {
  M5.begin();
  M5.Lcd.setTextSize(2);
  M5.Lcd.setTextDatum(MC_DATUM);
  M5.Buttons.draw();
  //add handler for the buttons
  bl.addHandler(eventDisplay, E_ALL);
  b2.addHandler(eventDisplay, E_ALL);
  b3.addHandler(eventDisplay, E_ALL);
}

void loop() {
  M5.update();
}

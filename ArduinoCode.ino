//Copyright © Franco Martino 2021

#include <CapacitiveSensor.h>

CapacitiveSensor sensors[6] = {CapacitiveSensor(4, 2), CapacitiveSensor(4, 3), CapacitiveSensor(4, 5), CapacitiveSensor(4, 6), CapacitiveSensor(4, 7), CapacitiveSensor(4, 8)};

bool sensorState[6] = {false, false, false, false, false, false};
bool oldSensorState[6] = {false, false, false, false, false, false};

int p1;
int oldP1;

int p2;
int oldP2;

void setup() {
  Serial.begin(31250);
}

void loop() {
  p1 = map(analogRead(A0), 1023, 0, 0, 127);
  p2 = map(analogRead(A1), 1023, 0, 0, 127);

  if (p1 != oldP1) {
    serialMsg(2, p1);
  }
  if (p2 != oldP2) {
    serialMsg(3, p2);
  }

  for (int i = 0; i < 6; i++) {
    long sensorVal =  sensors[i].capacitiveSensor(250);
    if (sensorVal) {
      sensorState[i] = true;
    } else {
      sensorState[i] = false;
    }
    if (sensorState[i] && oldSensorState[i] == false) {
      serialMsg(1, i);
    }
    else if (!sensorState[i] && oldSensorState[i] == true) {
      serialMsg(0, i);
    }
    oldSensorState[i] = sensorState[i];
  }

  oldP1 = p1;
  oldP2 = p2;
}

void serialMsg(int cmd, int value) {
  Serial.print(cmd);
  Serial.print("/");
  Serial.print(value);
  Serial.print("-");
  Serial.println("");
}

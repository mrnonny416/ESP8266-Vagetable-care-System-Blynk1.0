
#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>
#include <TimeLib.h>
#include <WidgetRTC.h>
#include "./env.h"
// You should get Auth Token in the Blynk App.
// Go to the Project Settings (nut icon).
char auth[] = AUTHENTICAION_TOKEN;

// Your WiFi credentials.
// Set password to "" for open networks.
char ssid[] = WIFI_SSID;
char pass[] = WIFI_PASSWORD;
char server[] = SERVER_URL;
int port = SERVER_PORT;


WidgetTerminal terminal(V0);
BlynkTimer timer;
WidgetRTC rtc;

String currentTime;
String currentDate;

// Define light Port
const int light1 = D0;
const int light2 = D1;
const int light3 = D2;
const int light4 = D3;
// Define Water Port
const int water1 = D5;
const int water2 = D6;
const int water3 = D7;
const int water4 = D8;

TimeInputParam* Timer_1 = NULL;  //global
TimeInputParam* Timer_2 = NULL;  //global
TimeInputParam* Timer_3 = NULL;  //global
TimeInputParam* Timer_4 = NULL;  //global
TimeInputParam* Timer_5 = NULL;  //global
TimeInputParam* Timer_6 = NULL;  //global
TimeInputParam* Timer_7 = NULL;  //global
TimeInputParam* Timer_8 = NULL;  //global

bool timer_manual;
bool manual_light_1;
bool manual_light_2;
bool manual_light_3;
bool manual_light_4;
bool manual_water_1;
bool manual_water_2;
bool manual_water_3;
bool manual_water_4;

void setup() {
  // Debug console
  Serial.begin(115200);
  Serial.println();
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, pass);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("");
  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
  pinMode(light1, OUTPUT);
  pinMode(light2, OUTPUT);
  pinMode(light3, OUTPUT);
  pinMode(light4, OUTPUT);
  pinMode(water1, OUTPUT);
  pinMode(water2, OUTPUT);
  pinMode(water3, OUTPUT);
  pinMode(water4, OUTPUT);

  digitalWrite(light1, HIGH);
  digitalWrite(light2, HIGH);
  digitalWrite(light3, HIGH);
  digitalWrite(light4, HIGH);
  digitalWrite(water1, HIGH);
  digitalWrite(water2, HIGH);
  digitalWrite(water3, HIGH);
  digitalWrite(water4, HIGH);

  Blynk.begin(auth, ssid, pass, server, port);  // ใช้เป็น Server Blynk ฟรี

  setSyncInterval(10 * 60);  // Sync interval in seconds (10 minutes)

  // Display digital clock every 10 seconds
  timer.setInterval(10000, clockDisplay);
}

void loop() {
  Blynk.run();
  timer.run();
  if (timer_manual) {

  } else {
    digitalWrite(light1, manual_light_1);
    digitalWrite(light2, manual_light_2);
    digitalWrite(light3, manual_light_3);
    digitalWrite(light4, manual_light_4);
    digitalWrite(water1, manual_water_1);
    digitalWrite(water2, manual_water_2);
    digitalWrite(water3, manual_water_3);
    digitalWrite(water4, manual_water_4);
  }
}

//----------Terminal-----------
BLYNK_WRITE(V0) {
  // if you type "Marco" into Terminal Widget - it will respond: "Polo:"
  if (String("Time") == param.asStr()) {
    terminal.print("Current time : ");
    terminal.print(currentTime);
    terminal.print("\nCurrent Date : ");
    terminal.print(currentDate);
  } else if (String("Timer") == param.asStr()) {
    //code here Timer List
    terminal.print(Timer_1 != NULL ? String(Timer_1->getTZ()) : "");
  } else {
    terminal.clear();
    // Send it back
    terminal.print("You said:");
    terminal.write(param.getBuffer(), param.getLength());
    terminal.println();
  }
  // Ensure everything is sent
  terminal.flush();
}

//-----------Real Time Clock-----------
void clockDisplay() {
  currentTime = String(hour()) + ":" + minute() + ":" + second();
  currentDate = String(day()) + " " + month() + " " + year() + " ";  //+weekday();//sunday = 1 satuaday = 7
}

BLYNK_CONNECTED() {
  // Synchronize time on connection
  rtc.begin();
}
//-----------Timer Set 1--------
//Timer_1.hasStartTime()
//Timer_1.getStartHour()
//Timer_1.getStartMinute()
//Timer_1.getStartSecond()
//Timer_1.isStartSunrise()
//Timer_1.isStartSunset()

//Timer_1.hasStopTime()
//Timer_1.getStopHour()
//Timer_1.getStopMinute()
//Timer_1.getStopSecond()
//Timer_1.isStopSunrise()
//Timer_1.isStopSunset()

//Timer_1.getTZ()
//Timer_1.getTZ_Offset()

//Timer_1.isWeekdaySelected(i)



BLYNK_WRITE(V1) {
  if (Timer_1 != NULL)
    delete Timer_1;
  Timer_1 = new TimeInputParam(param);
}
BLYNK_WRITE(V2) {
  if (Timer_2 != NULL)
    delete Timer_2;
  Timer_2 = new TimeInputParam(param);
}
BLYNK_WRITE(V3) {
  if (Timer_3 != NULL)
    delete Timer_3;
  Timer_3 = new TimeInputParam(param);
}
BLYNK_WRITE(V4) {
  if (Timer_4 != NULL)
    delete Timer_4;
  Timer_4 = new TimeInputParam(param);
}
BLYNK_WRITE(V5) {
  if (Timer_5 != NULL)
    delete Timer_5;
  Timer_5 = new TimeInputParam(param);
}
BLYNK_WRITE(V6) {
  if (Timer_6 != NULL)
    delete Timer_6;
  Timer_6 = new TimeInputParam(param);
}
BLYNK_WRITE(V7) {
  if (Timer_7 != NULL)
    delete Timer_7;
  Timer_7 = new TimeInputParam(param);
}
BLYNK_WRITE(V8) {
  if (Timer_8 != NULL)
    delete Timer_8;
  Timer_8 = new TimeInputParam(param);
}
//-----------Switch-----------

BLYNK_WRITE(V10) {
  switch (param.asInt()) {
    case 1:
      {
        timer_manual = true;
        Serial.println("Item 1 Selected");
        Blynk.setProperty(V1, "color", "#09FFA2");
        Blynk.setProperty(V2, "color", "#09FFA2");
        Blynk.setProperty(V3, "color", "#09FFA2");
        Blynk.setProperty(V4, "color", "#09FFA2");
        Blynk.setProperty(V5, "color", "#09FFA2");
        Blynk.setProperty(V6, "color", "#09FFA2");
        Blynk.setProperty(V7, "color", "#09FFA2");
        Blynk.setProperty(V8, "color", "#09FFA2");
        Blynk.setProperty(V11, "color", "#7D7D7D");
        Blynk.setProperty(V12, "color", "#7D7D7D");
        Blynk.setProperty(V13, "color", "#7D7D7D");
        Blynk.setProperty(V14, "color", "#7D7D7D");
        Blynk.setProperty(V15, "color", "#7D7D7D");
        Blynk.setProperty(V16, "color", "#7D7D7D");
        Blynk.setProperty(V17, "color", "#7D7D7D");
        Blynk.setProperty(V18, "color", "#7D7D7D");
        break;
      }
    case 2:
      {
        timer_manual = false;
        Serial.println("Item 2 Selected");
        Blynk.setProperty(V1, "color", "#7D7D7D");
        Blynk.setProperty(V2, "color", "#7D7D7D");
        Blynk.setProperty(V3, "color", "#7D7D7D");
        Blynk.setProperty(V4, "color", "#7D7D7D");
        Blynk.setProperty(V5, "color", "#7D7D7D");
        Blynk.setProperty(V6, "color", "#7D7D7D");
        Blynk.setProperty(V7, "color", "#7D7D7D");
        Blynk.setProperty(V8, "color", "#7D7D7D");
        Blynk.setProperty(V11, "color", "#FF8C09");
        Blynk.setProperty(V12, "color", "#FF8C09");
        Blynk.setProperty(V13, "color", "#FF8C09");
        Blynk.setProperty(V14, "color", "#FF8C09");
        Blynk.setProperty(V15, "color", "#09C3FF");
        Blynk.setProperty(V16, "color", "#09C3FF");
        Blynk.setProperty(V17, "color", "#09C3FF");
        Blynk.setProperty(V18, "color", "#09C3FF");
        break;
      }
  }
}

//-----------Light 1-----------
BLYNK_WRITE(V11) {
  if (param.asInt() == 1) {
    Serial.print("Light 1 : On");
    manual_light_1 = true;
  } else {
    Serial.print("Light 1 : Off");
    manual_light_1 = false;
  }
}
//-----------Light 2-----------
BLYNK_WRITE(V12) {
  if (param.asInt() == 1) {
    Serial.print("Light 2 : On");
    manual_light_2 = true;
  } else {
    Serial.print("Light 2 : Off");
    manual_light_2 = false;
  }
}
//-----------Light 3-----------
BLYNK_WRITE(V13) {
  if (param.asInt() == 1) {
    Serial.print("Light 3 : On");
    manual_light_3 = true;
  } else {
    Serial.print("Light 3 : Off");
    manual_light_3 = false;
  }
}
//-----------Light 4-----------
BLYNK_WRITE(V14) {
  if (param.asInt() == 1) {
    Serial.print("Light 4 : On");
    manual_light_4 = true;
  } else {
    Serial.print("Light 4 : Off");
    manual_light_4 = false;
  }
}
//-----------Water 1-----------
BLYNK_WRITE(V15) {
  if (param.asInt() == 1) {
    Serial.print("Water 1 : On");
    manual_water_1 = true;
  } else {
    Serial.print("Water 1 : Off");
    manual_water_1 = false;
  }
}
//-----------Water 2-----------
BLYNK_WRITE(V16) {
  if (param.asInt() == 1) {
    Serial.print("Water 2 : On");
    manual_water_2 = true;
  } else {
    Serial.print("Water 2 : Off");
    manual_water_2 = false;
  }
}
//-----------Water 3-----------
BLYNK_WRITE(V17) {
  if (param.asInt() == 1) {
    Serial.print("Water 3 : On");
    manual_water_3 = true;
  } else {
    Serial.print("Water 3 : Off");
    manual_water_3 = false;
  }
}
//-----------Water 4-----------
BLYNK_WRITE(V18) {
  if (param.asInt() == 1) {
    Serial.print("Water 4 : On");
    manual_water_4 = true;
  } else {
    Serial.print("Water 4 : Off");
    manual_water_4 = false;
  }
}

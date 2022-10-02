#include <PS2Kbd.h>
#include <WiFi.h>
#include <ESP32Lib.h>
#include <Ressources/Font6x8.h>

#define KEYBOARD_DATA 23
#define KEYBOARD_CLK  22

const int redPin = 17;
const int greenPin = 19;
const int bluePin = 18;
const int hsyncPin = 16;
const int vsyncPin = 21;

PS2Kbd keyboard(KEYBOARD_DATA, KEYBOARD_CLK);

VGA3Bit vga;

String currentText = "";

void setup() {
  Serial.begin(9600);
  Mode myMode = vga.MODE640x400.custom(450, 400);
  myMode.print<HardwareSerial>(Serial);
  vga.init(myMode, redPin, greenPin, bluePin, hsyncPin, vsyncPin);
  vga.setFont(Font6x8);
  initText();
  keyboard.begin();
}

// 8 (Borrar)
// 10 (Enter)

void loop() {
  if (keyboard.available()) {
    int num = keyboard.read();
    if (num == 10) {
      // int length = currentText.length(); Anda
      // currentText.remove(length - 1);
      vga.println(" ");
      if (currentText.substring(0, currentText.indexOf('(')) == "WIFI") {
        initWiFi();
      }
      currentText = "";
      vga.print("> ");
    }
    else {
      vga.print(char(num));
      currentText = currentText + char(num);
    }
    Serial.println(num);
  }
}

// Use "//" to print "/"/*
void initText() {
  vga.clear(vga.RGBA(0, 0, 0));
  vga.setCursor(0, 0);
  vga.println(" _   ___        ______      _           _   _          ");
  vga.println("| | / (_)       | ___ |    | |         | | (_)         ");
  vga.println("| |/ / _ _ __   | |_/ /___ | |__   ___ | |_ _  ___ ___ ");
  vga.println("|    \\| | '_ \\  |    // _ \\| '_ | / _ \\| __| |/ __/ __|");
  vga.println("| |\\  \\ | |_) | | |\\ \\ (_) | |_)|| (_) | |_| ||(__|__ |");
  vga.println("\\_| \\_/_| .__/  \\_| \\_\\___/|_.__/ \\___/|___|_||___|___/");
  vga.println("        | |                                            ");
  vga.println("        |_|                                            ");
  vga.println("-------------------------------------------------------");
  vga.println("");
  vga.print("> ");
}

void initWiFi() {
  WiFi.mode(WIFI_STA);
  WiFi.begin("KIP_LAB", "47052482");
  
  vga.print("Connecting to WiFi ...");
  while (WiFi.status() != WL_CONNECTED) {
    vga.print(".");
    delay(1000);
  }
  vga.println("");
  vga.print(WiFi.localIP()[0]); vga.print("."); vga.print(WiFi.localIP()[1]); vga.print(".");
  vga.print(WiFi.localIP()[2]); vga.print("."); vga.println(WiFi.localIP()[3]);
  vga.println("");
}

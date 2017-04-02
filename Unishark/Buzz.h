#ifdef Buzz

#include <IRremote.h>
IRrecv irrecv(RECV_PIN);
decode_results results;
uint16_t volt ;

void search() {
  while (goat < 1) {
    autocalib();
    if (rssi2 > 50 || rssi3 > 50)goat = 1;
    delay(20);
    display.setCursor(45, 53);
    display.print(rssi2);
    display.drawCircle(25, display.height() / 2, rssi2, WHITE);
    display.drawCircle(25, display.height() / 2, rssi2 / 2, WHITE);
    display.drawCircle(25, display.height() / 2, rssi2 / 5, WHITE);
    display.display();
    delay(15);
    display.clearDisplay();
    display.setCursor(45, 53);
    display.print(rssi2);
    display.drawCircle(102, display.height() / 2, rssi3, WHITE);
    display.drawCircle(102, display.height() / 2, rssi3 / 2, WHITE);
    display.drawCircle(102, display.height() / 2, rssi3 / 5, WHITE);
    display.display();
    delay(15);
    display.clearDisplay();
    display.setCursor(45, 53);
    // display.print("FINDER");
    display.print(rssi2);
    display.fillRect(23, rssi2 - rssi3, 5, 6, WHITE);
    display.fillRect(100, rssi3 - rssi2, 5, 6, WHITE);
    display.display();
    delay(15);
  }
  goat = 0;
}
void strong() {
  best = 0;
  delay(50);
  if (channel >= 40 && channel <= 47) {
    for (uint8_t i = 40; i <= 47; i++) {
      channel = i;
      delay (10);
      test();
      delay(100);
      rssi = (analogRead(A0));
      delay (50);
      if (rssi  - 10 > best + 20 ) {
        best = rssi - 5 ;
        digitalWrite(ledPin, HIGH);
        delay (50);
        memo = channel;
      }
      uint8_t ext = map(channel, 0, 48, 0, 128);
      rssi = map(rssi, 100, 300, 63, 40);
      display.clearDisplay();
      display.setTextSize(1);
      display.setCursor(23, 20);
      display.print(">> SCANNING <<");
      display.setCursor(64, 40);
      display.print(channel - 39);
      display.fillRect(ext, rssi, 2, 14, WHITE);
      display.display();
      delay (100);
      digitalWrite(ledPin, LOW);
    }
    delay (50);
    channel = memo - 1;
    test();
    display.clearDisplay();
    display.setCursor(23, 20);
    display.print(">> STRONGEST <<");
    display.setTextSize(2);
    display.setCursor(20, 40);
    display.print(channel - 39);
    display.setTextSize(1);
    display.setCursor(72, 48);
    delay (50);
    memo = channel - 39;
    display.print("D/5.3");
    display.display();
    delay (1300);
    best = 0;
    return;
  }
  else if (channel >= 32 && channel <= 39 ) {
    for (uint8_t i = 32; i <= 39; i++) {
      channel = i;
      delay (10);
      test();
      delay(100);
      rssi = (analogRead(A0));
      delay (50);
      if (rssi  - 10 > best + 20 ) {
        best = rssi - 5 ;
        digitalWrite(ledPin, HIGH);
        delay (50);
        memo = channel;
      }
      uint8_t ext = map(channel, 0, 48, 0, 128);
      rssi = map(rssi, 100, 300, 63, 40);
      display.clearDisplay();
      display.setTextSize(1);
      display.setCursor(23, 20);
      display.print(">> SCANNING <<");
      display.setCursor(64, 40);
      display.print(channel - 31);
      display.fillRect(ext, rssi, 2, 14, WHITE);
      display.display();
      delay (100);
      digitalWrite(ledPin, LOW);
    }
    delay (50);
    channel = memo - 1 ;
    test();
    display.clearDisplay();
    display.setCursor(23, 20);
    display.print(">> STRONGEST <<");
    display.setTextSize(2);
    display.setCursor(20, 40);
    display.print(channel - 31);
    display.setTextSize(1);
    display.setCursor(72, 48);
    delay (50);
    memo = channel - 31;
    display.print("C/Race");
    display.display();
    delay (1300);
    best = 0;
    return;
  }
  else if (channel >= 24 && channel <= 31) {
    best = 0;
    for (uint8_t i = 24; i <= 31; i++) {
      channel = i;
      delay (10);
      test();
      delay(100);
      rssi = (analogRead(A0));
      delay (50);
      if (rssi  - 10 > best + 20 ) {
        best = rssi - 5 ;
        digitalWrite(ledPin, HIGH);
        delay (50);
        memo = channel;
      }
      uint8_t ext = map(channel, 0, 48, 0, 128);
      rssi = map(rssi, 100, 300, 63, 40);
      display.clearDisplay();
      display.setTextSize(1);
      display.setCursor(23, 20);
      display.print(">> SCANNING <<");
      display.setCursor(64, 40);
      display.print(channel - 23 );
      display.fillRect(ext, rssi, 2, 14, WHITE);
      display.display();
      delay (100);
      digitalWrite(ledPin, LOW);
    }
    delay (50);
    channel = memo - 1 ;
    test();
    display.clearDisplay();
    display.setCursor(23, 20);
    display.print(">> STRONGEST <<");
    display.setTextSize(2);
    display.setCursor(20, 40);
    display.print(channel - 23);
    display.setTextSize(1);
    display.setCursor(72, 48);
    delay (50);
    memo = channel - 23;
    display.print("F/Airwave");
    display.display();
    delay (1300);
    best = 0;
    return;
  }
  else if (channel >= 16 && channel <= 23) {
    for (uint8_t i = 16; i <= 23; i++) {
      channel = i;
      delay (10);
      test();
      delay(100);
      rssi = (analogRead(A0));
      delay (50);
      if (rssi  - 10 > best + 20 ) {
        best = rssi - 5 ;
        digitalWrite(ledPin, HIGH);
        delay (50);
        memo = channel;
      }
      uint8_t ext = map(channel, 0, 48, 0, 128);
      rssi = map(rssi, 100, 300, 63, 40);
      display.clearDisplay();
      display.setTextSize(1);
      display.setCursor(23, 20);
      display.print(">> SCANNING <<");
      display.setCursor(64, 40);
      display.print(channel - 15);
      display.fillRect(ext, rssi, 2, 14, WHITE);
      display.display();
      delay (100);
      digitalWrite(ledPin, LOW);
    }
    delay (50);
    channel = memo - 1 ;
    test();
    display.clearDisplay();
    display.setCursor(23, 20);
    display.print(">> STRONGEST <<");
    display.setTextSize(2);
    display.setCursor(20, 40);
    display.print(channel - 15);
    display.setTextSize(1);
    display.setCursor(72, 48);
    delay (50);
    memo = channel - 15;
    display.print("E");
    display.display();
    delay (1300);
    best = 0;
    return;
  }
  else if (channel >= 8 && channel <= 15) {
    for (uint8_t i = 8; i <= 15; i++) {
      channel = i;
      delay (10);
      test();
      delay(100);
      rssi = (analogRead(A0));
      delay (50);
      if (rssi  - 10 > best + 20 ) {
        best = rssi - 5 ;
        digitalWrite(ledPin, HIGH);
        delay (50);
        memo = channel;
      }
      uint8_t ext = map(channel, 0, 48, 0, 128);
      rssi = map(rssi, 100, 300, 63, 40);
      display.clearDisplay();
      display.setTextSize(1);
      display.setCursor(23, 20);
      display.print(">> SCANNING <<");
      display.setCursor(64, 40);
      display.print(channel - 7);
      display.fillRect(ext, rssi, 2, 14, WHITE);
      display.display();
      delay (100);
      digitalWrite(ledPin, LOW);
    }
    delay (50);
    channel = memo - 1;
    test();
    display.clearDisplay();
    display.setCursor(23, 20);
    display.print(">> STRONGEST <<");
    display.setTextSize(2);
    display.setCursor(20, 40);
    display.print(channel - 7);
    display.setTextSize(1);
    display.setCursor(72, 48);
    delay (50);
    memo = channel - 7;
    display.print("B");
    display.display();
    delay (1300);
    best = 0;
    return;
  }
  else if (channel <= 7 ) {
    for (uint8_t i = 0; i <= 7; i++) {
      channel = i;
      delay (10);
      test();
      delay(100);
      rssi = (analogRead(A0));
      delay (50);
      if (rssi  - 10 > best + 20 ) {
        best = rssi - 5 ;
        digitalWrite(ledPin, HIGH);
        delay (50);
        memo = channel;
      }
      uint8_t ext = map(channel, 0, 48, 0, 128);
      rssi = map(rssi, 100, 300, 63, 40);
      display.clearDisplay();
      display.setTextSize(1);
      display.setCursor(23, 20);
      display.print(">> SCANNING <<");
      display.setCursor(64, 40);
      display.print(channel );
      display.fillRect(ext, rssi, 2, 14, WHITE);
      display.display();
      delay (100);
      digitalWrite(ledPin, LOW);
    }
    delay (50);
    channel = memo - 1;
    test();
    display.clearDisplay();
    display.setCursor(23, 20);
    display.print(">> STRONGEST <<");
    display.setTextSize(2);
    display.setCursor(20, 40);
    display.print(channel);
    display.setTextSize(1);
    display.setCursor(72, 48);
    delay (50);
    display.print("A");
    display.setCursor(72, 40);
    display.display();
    delay (1300);
    best = 0;
    return;
  }
}



void scope() {
  scp = 0;
  while (scp < 111) {
    scp++;
    autocalib();
    display.fillRect(0, 62, 124, 2, WHITE);
    display.fillRect(1, 0, 1, 63, WHITE);
    display.fillRect(2, rssi2, 10, 10 , WHITE);
    display.fillRect(12, 0, 1, 63, WHITE);
    display.fillRect(112, 0, 1, 63, WHITE);
    display.fillRect(113, rssi3, 10, 10 , WHITE);
    display.fillRect(123, 0, 1, 63, WHITE);
    if (scp > 11 ) {
      display.fillRect(scp, rssi2, 1, 1 , WHITE);
      display.fillRect(scp, rssi3, 3, 1 , WHITE);
    }
    else if (scp > 112 ) {
      display.clearDisplay();
      scp = 0;
      return;
    }
    display.display();
    delay(5);
  }
}

void loop() {
  turboswitch();
  delay (20);
  autocalib();
  scr = scr + 1;
  display.clearDisplay();
  // Ir reactions //
  if (irrecv.decode(&results)) {
    scp = 0;
    display.clearDisplay();
    while (scp < 10) {
      scp++;
      display.drawCircle(63, display.height() / 2, scp * 2, WHITE);
      display.display();
      digitalWrite(ledPin, HIGH);
    }
    scp = 0;
    if (results.value == Ircode2 || results.value == Ircode22) {
      channel = channel - 8;
      if (channel < 1)channel = 0;
      mnu = 2;
      display.clearDisplay();
      display.setTextSize(2);
      display.setCursor(0, 20);
      display.print(" BAND -");  // disable
      display.display();
      delay (200);
      display.clearDisplay();
      test();
      scr = 95;
      delay (10);
    }
    if (results.value == Ircode1 || results.value == Ircode11) {
      channel = channel + 8;
      if (channel > 47)channel = 0;
      mnu = 2;
      display.clearDisplay();
      display.setTextSize(2);
      display.setCursor(0, 20);
      display.print(" BAND +");  // disable
      display.display();
      delay (200);
      display.clearDisplay();
      test();
      scr = 95;
      delay (10);
    }
    if (results.value  == Ircode3 || results.value == Ircode33) {
      channel = channel + 1;
      display.clearDisplay();
      display.setTextSize(4);
      display.setCursor(0, 20);
      display.print("  UP   ");  // disable
      display.display();
      delay (200);
      display.setTextSize(1);
      test();
      scr = 95;
      delay (10);
    }
    if (results.value == Ircode4 || results.value == Ircode44) {
      channel = channel - 1;
      display.clearDisplay();
      display.setTextSize(4);
      display.setCursor(0, 20);
      display.print(" DOWN   ");  // disable
      display.display();
      delay (200);
      display.setTextSize(1);
      test();
      scr = 95;
      delay (10);
    }
    if (results.value == Ircode5 || results.value == Ircode55) {
      display.clearDisplay();
      display.setTextSize(2);
      display.setCursor(0, 20);
      display.print("    SCAN   ");  // disable
      display.display();
      delay (200);
      display.setTextSize(1);
      best = 0;
      strong();
    }
    if (results.value == Ircode6 || results.value == Ircode66) {
      display.clearDisplay();
      display.setTextSize(2);
      display.setCursor(0, 20);
      display.print("   SEARCH   ");  // disable
      display.display();
      delay (200);
      display.setTextSize(1);
      best = 0;
      search();
    }
    if (results.value == Ircode7 || results.value == Ircode77) {
      display.clearDisplay();
      display.setTextSize(2);
      display.setCursor(0, 20);
      display.print("   SCOPE   ");  // disable
      display.display();
      delay (200);
      display.setTextSize(1);
      best = 0;
      scope();
    }
    irrecv.resume(); // Receive the next value
    delay (100);
    if (channel > 47)channel = 0;
    if (channel < 1  )channel = 0;
    display.clearDisplay();
  }
  // Oled Stuff //
  display.clearDisplay();
  if (scr < 40) {
    display.drawBitmap(1, 1, myBitmap2, 64, 64, 1);
  }
  display.setTextSize(1);
  if (scr > 40 && scr < 95) {  // NOT USED IN V2 DISABLE FOR USE
    volt = analogRead(A1);
    volt = map(volt, 1024, 0, 50, 0);
    delay (10);
    display.fillRect(30, 0, 1, 63, WHITE);
    display.fillRect(33, volt, 30, 63, WHITE);
    display.fillRect(64, 0, 1, 63, WHITE);
    display.fillRect(45, 37, 5, 40, BLACK);
    display.fillRect(40, 40, 15, 63, BLACK);
    display.setCursor(0, 50);
    display.print("BATT");
    display.setCursor(8, volt);
    volt = analogRead(A1);
    volt = map(volt, 1024, 0, 0, 60);
    display.print(volt);
    display.print(">");
  }
  if (scr > 95 ) {
    display.setCursor(10, 10);
    display.setTextSize(2);
    display.print(pgm_read_word_near(channel + channelFreqTable));
    display.setCursor(10, 35);
    display.print("MHZ");
    display.setTextSize(1);
    if (scr > 115)scr = 0;
  }
  display.setTextSize(1);
  if (rssi2 < 20 || rssi3 < 20) {
    display.setCursor(71, 13);
    display.print("LOW SIG !");
    delay (10);
  }
  else if (rssi2 > 35 && rssi3 > 35 ) {
    display.setCursor(71, 13);
    display.print("GOOD SIG ");
    delay (10);
  }
  display.setTextColor(WHITE);
  display.setTextSize(1);
  display.setCursor(2, 0);
  display.print("           CH < ");
  display.print(memo);
  display.print(" >");
  delay (10);
  display.fillRect(72, 27, 55, 2, WHITE);
  display.fillRect(72, 29, rssi2, 2, WHITE);
  display.fillRect(72, 34, rssi3, 2, WHITE);
  display.fillRect(72, 36, 55, 2, WHITE);
  display.display();
  delay(10);
  display.setCursor(72, 48);
  if (channel > 39) {
    memo = channel - 39;
    display.print("D/5.3");
  }
  else if (channel > 31) {
    memo = channel - 31;
    display.print("C/Race");
  }
  else if (channel > 23) {
    memo = channel - 23;
    display.print("F/Airwave");
  }
  else if (channel > 15) {
    memo = channel - 15;
    display.print("E");
  }
  else if (channel > 7) {
    memo = channel - 7;
    display.print("B");
  }
  else if (channel < 7) {
    display.print("A");
    memo = channel + 1 ;
  }
  display.display();
}
#endif


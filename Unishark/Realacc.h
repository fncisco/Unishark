
#ifdef Realac
void search() {
  while (goat < 1) {
    buttonState0 = digitalRead(BUT1);
    buttonState1 = digitalRead(BUT2);
    buttonState2 = digitalRead(BUT3);
    autocalib();
    if (buttonState0 == LOW && buttonState2 == LOW) {
      display.clearDisplay();
      display.setCursor(34, 32);
      display.print("BACK MENU");
      display.display();
      selector = 4;
      goat = 0;
      return;
      delay (500);
    }
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

///////////////////  MAIN SCREEN LOOP ///////////////////////////////////////////////////////////////
void manual() {  // just manual main screen mode //
  display.clearDisplay();
  buttonState0 = digitalRead(BUT1);
  buttonState1 = digitalRead(BUT2);
  buttonState2 = digitalRead(BUT3);
  if (buttonState1 == HIGH )  but = 0;
  if (buttonState0 == LOW ) {
    channel = channel + 1;
    if (channel >= 55)channel = 55;
    display.clearDisplay();
    display.setTextSize(4);
    display.setCursor(0, 20);
    display.print("  UP   ");  // disable
    display.display();
    delay (200);
    display.setTextSize(1);
    test();
    scr = 95;
    mnu = 1;
    dp = 0;
    delay (10);
  }
  if (buttonState2 == LOW ) {
    channel = channel - 1;
    if (channel <= 0)channel = 0;
    display.clearDisplay();
    display.setTextSize(4);
    display.setCursor(0, 20);
    display.print(" DOWN   ");  // disable
    display.display();
    delay (200);
    display.setTextSize(1);
    test();
    scr = 95;
    mnu = 2;
    dp = 0;
    delay (10);
  }
  if (buttonState1 == LOW  ) {  // middle presh menu test !!??!! dexters way of doing shit !
    but = but + 1;
    scp = 0;
    dp = 0;
    while (scp < 10) {
      scp++;
      display.drawCircle(63, display.height() / 2, scp * 2, WHITE);
      display.display();
      digitalWrite(ledPin, HIGH);
    }
    if (but > 5)but = 0;
    if (but == 1) { // band up
      display.clearDisplay();
      display.setTextSize(2);
      display.setCursor(0, 20);
      display.print(" BAND + ");  // disable
      display.display();
      delay (600);
      display.setTextSize(1);
      display.clearDisplay();
      delay (100);
      buttonState1 = digitalRead(BUT2);
      if (buttonState1 == LOW )return;
      but = 0;
      display.clearDisplay();
      display.setTextSize(2);
      display.setCursor(0, 20);
      display.print(" OK ");  // disable
      display.display();
      channel = channel + 8;
      if (channel >= 47)channel = 47;
      test();
      scr = 80;
      delay (320);
      display.setTextSize(1);
      display.clearDisplay();
      delay (320);
      return;
    }
    if (but == 2 ) {
      display.clearDisplay();
      display.setTextSize(2);
      display.setCursor(0, 20);
      display.print(" BAND - ");  // disable
      display.display();
      delay (600);
      display.setTextSize(1);
      display.clearDisplay();
      buttonState1 = digitalRead(BUT2);
      if (buttonState1 == LOW )return;
      but = 0;
      display.clearDisplay();
      display.setTextSize(2);
      display.setCursor(0, 20);
      display.print(" OK ");  // disable
      display.display();
      channel = channel - 8;
      if (channel <= 0)channel = 0;
      test();
      scr = 80;
      delay (320);
      display.setTextSize(1);
      display.clearDisplay();
      delay (320);
      sub1 = 0;
      return;
    }
    if (but == 3) {
      display.clearDisplay();
      display.setTextSize(2);
      display.setCursor(0, 20);
      display.print(" SFAVO ");  // disable
      display.display();
      delay (600);
      display.clearDisplay();
      buttonState1 = digitalRead(BUT2);
      if (buttonState1 == LOW )return;
      but = 0;
      display.clearDisplay();
      display.setTextSize(2);
      display.setCursor(0, 20);
      display.print(" OK ");  // disable
      display.display();
      delay (320);
      display.setTextSize(1);
      display.clearDisplay();
      delay (320);
      selector = 5;
    }
    if (but == 4) {
      display.clearDisplay();
      display.setTextSize(2);
      display.setCursor(0, 20);
      display.print(" MENU ");  // disable
      display.display();
      delay (600);
      display.clearDisplay();
      buttonState1 = digitalRead(BUT2);
      if (buttonState1 == LOW )return;
      but = 0;
      display.clearDisplay();
      display.setTextSize(2);
      display.setCursor(0, 20);
      display.print(" OK ");  // disable
      display.display();
      delay (320);
      display.setTextSize(1);
      display.clearDisplay();
      delay (320);
      selector = 0;
    }
    display.setTextSize(1);
    display.clearDisplay();
    delay (320);
  }
  delay (20);
  autocalib();
  scr = scr + 1;
  display.clearDisplay();             ////////////////////////////////////////////////////////////////////////////////  SCREENSAVER PART //////
  if (scr < 40) {
    display.drawBitmap(1, 1, myBitmap2, 64, 64, 1);
    /////////////////////////////////////////////////////////////////////////////////////
    //display.drawCircle(33, 15, rssi3 / 4, WHITE);    // Biohazard up   //also used for RotorRiot
    //display.drawCircle(33, 15, rssi2 / 4, WHITE);    // Biohazard up
    //display.drawCircle(17, 42, rssi2 / 4, WHITE);    // Biohazrd left
    //display.drawCircle(48, 42, rssi2 / 4, WHITE);    // Biohazrd right

    //display.drawCircle(33, 33, rssi3 / 2, WHITE);    // Biohazard up
    //display.drawCircle(33, 33, rssi2 / 2, WHITE);    // Biohazard up

    //display.drawCircle(33, 15, rssi3 / 6, WHITE);    // Biohazard up
    //display.drawCircle(33, 15, rssi2 / 6, WHITE);    // Biohazard up
    //display.drawCircle(17, 42, rssi2 / 6, WHITE);    // Biohazrd left
    //display.drawCircle(48, 42, rssi2 / 6, WHITE);    // Biohazrd right
    ////////////////////////////////////////////////////////////////////////////////
    display.drawCircle(52, 6, rssi3 / 4, WHITE);    // TX Bubbles
    display.drawCircle(52, 6, rssi2 / 4, WHITE);         // TX Bubbles
    ////////////////////////////////////////////////////////////////////////////////////
    // display.drawCircle(20, 5, rssi3 / 6, WHITE);     // fish bubbles
    // display.drawCircle(35, 2, rssi2 / 4, WHITE);     // fish bubbles
    // display.drawCircle(10, 9, rssi3 / 6, WHITE);     // fish bubbles
    // display.drawCircle(5, 12, rssi2 / 4, WHITE);     // fish bubbles
  }
  if (scr > 40 && scr < 95 ) {
    display.setCursor(10, 5);
    display.setTextSize(8);
    display.print(memo);
    display.setTextSize(1);
  }
  if (scr > 95 ) {
    display.setCursor(10, 10);
    display.setTextSize(2);
    if (channel == 48)display.print(pgm_read_word_near(fav1 + channelFreqTable));
    if (channel == 49)display.print(pgm_read_word_near(fav2 + channelFreqTable));
    if (channel == 50)display.print(pgm_read_word_near(fav3 + channelFreqTable));
    if (channel == 51)display.print(pgm_read_word_near(fav4 + channelFreqTable));
    if (channel == 52)display.print(pgm_read_word_near(fav5 + channelFreqTable));
    if (channel == 53)display.print(pgm_read_word_near(fav6 + channelFreqTable));
    if (channel == 54)display.print(pgm_read_word_near(fav7 + channelFreqTable));
    if (channel == 55)display.print(pgm_read_word_near(fav8 + channelFreqTable));
    if (channel <= 47)display.print(pgm_read_word_near(channel + channelFreqTable));
    display.setCursor(10, 35);
    display.print("MHZ");
    display.setTextSize(1);
    if (scr > 115)scr = 0;
  }
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
  display.print("            CH < ");
  display.print(memo);
  display.print(" >");
  delay (10);
  display.fillRect(72, 27, 55, 2, WHITE);
  display.fillRect(72, 29, rssi2, 2, WHITE);
  display.fillRect(72, 34, rssi3, 2, WHITE);
  display.fillRect(72, 36, 55, 2, WHITE);
  display.fillRect(72, 29, HIS1, 3, BLACK); // new
  display.fillRect(72, 34, HIS2, 3, BLACK); // new
  display.setCursor(72, 48);
  if (channel > 47) {
    memo = channel - 47;
    display.print("!FAV!");
  }
  else if (channel > 39) {
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
  else display.print("A");
  display.display();
  delay(10);
  if (channel > 55)channel = 0;
  if (channel < 1 )channel = 55;
}
#endif
#ifdef Realac
void filter() {  // menu to set filter treshold //
  buttonState0 = digitalRead(BUT1);
  buttonState1 = digitalRead(BUT2);
  buttonState2 = digitalRead(BUT3);
  if (buttonState0 == LOW) {
    HISFILT = HISFILT - 1;
    delay (100);;
  }
  if (buttonState1 == LOW) {
    selector = 0;
    delay (100);
  }
  if (buttonState2 == LOW) {
    HISFILT = HISFILT + 1;
    delay (100);
  }
  if (HISFILT > 25)HISFILT = 5;
  if (HISFILT < 5)HISFILT = 5;
  EEPROM.write(2, HISFILT);
  display.clearDisplay();
  display.setTextSize(1);
  display.setCursor(2, 0);
  display.print("  << SET FILTER >>");
  display.setCursor(61, 20);
  display.print(HISFILT);
  display.setCursor(32, 40);
  if (HISFILT <= 10)display.print("FILTER LOW");
  if (HISFILT > 10  && HISFILT < 15)display.print("FILTER MEDIUM");
  if (HISFILT >= 15)display.print("FILTER HIGH");
  display.display();
  digitalWrite(ledPin, LOW);
}


void favorsave() {
  EEPROM.write(3, fav1);
  EEPROM.write(4, fav2);
  EEPROM.write(5, fav3);
  EEPROM.write(6, fav4);
  EEPROM.write(7, fav5);
  EEPROM.write(8, fav6);
  EEPROM.write(9, fav7);
  EEPROM.write(10, fav8);
}

void favorread() {
  fav1 = EEPROM.read(3);
  fav2 = EEPROM.read(4);
  fav3 = EEPROM.read(5);
  fav4 = EEPROM.read(6);
  fav5 = EEPROM.read(7);
  fav6 = EEPROM.read(8);
  fav7 = EEPROM.read(9);
  fav8 = EEPROM.read(10);
  if (fav1 < 0 || fav1 > 55)fav1 = 24;
  if (fav2 < 0 || fav2 > 55)fav2 = 31;
  if (fav3 < 0 || fav3 > 55)fav3 = 24;
  if (fav4 < 0 || fav4 > 55)fav4 = 31;
  if (fav5 < 0 || fav5 > 55)fav5 = 24;
  if (fav6 < 0 || fav6 > 55)fav6 = 31;
  if (fav7 < 0 || fav7 > 55)fav7 = 24;
  if (fav8 < 0 || fav8 > 55)fav8 = 31;
}

void favor() {  // menu to set filter treshold //
  buttonState0 = digitalRead(BUT1);
  buttonState1 = digitalRead(BUT2);
  buttonState2 = digitalRead(BUT3);
  if (buttonState0 == LOW) {
    favselect = favselect - 1;

    delay (100);

  }
  if (buttonState1 == LOW) {
    selector = 4;
    /////////////////////////////////////////////////////
    if (favselect == 1)fav1 = channel;
    if (favselect == 2)fav2 = channel;
    if (favselect == 3)fav3 = channel;
    if (favselect == 4)fav4 = channel;
    if (favselect == 5)fav5 = channel;
    if (favselect == 6)fav6 = channel;
    if (favselect == 7)fav7 = channel;
    if (favselect == 8)fav8 = channel;
    ///////////////////////////////////////////////// new Favorite part !

    delay (100);

    favorsave();
  }
  if (buttonState2 == LOW) {
    favselect = favselect + 1;

    delay (100);

  }
  if (favselect > 8)favselect = 1;
  if (favselect < 1)favselect = 8;
  display.clearDisplay();
  display.setTextSize(1);
  display.setCursor(2, 0);
  display.print("  << SET FAVO CH >>");
  display.setCursor(61, 20);
  display.print(favselect);
  display.display();
  digitalWrite(ledPin, LOW);
}



void scope() {
  display.clearDisplay();
  scp = 0;
  while (scp < 111) {
    scp++;
    display.drawBitmap(30, 0, flagy, 64, 64, 1);
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
    selector = 4;
    delay(5);
  }
}
void loop () {  //  loop used onley for switching //
  if (dp > screentime) {
    turbo();
    dp = screentime + 5;
    buttonState0 = digitalRead(BUT1);
    buttonState1 = digitalRead(BUT2);
    buttonState2 = digitalRead(BUT3);
    if (buttonState0 == LOW || buttonState1 == LOW || buttonState2 == LOW) dp = 0;
    return;
  }
  turboswitch();
  dp++;

#ifdef osd
  osdt ++;
  if (osdt > 2) {
    osd();
    osdt = 0;
  }
#endif
  if (selector == 1) {
    search();
    return;
  }
  if (selector == 2) {
    filter();
    return;
  }
  if (selector == 3) {
    scope();
    return;
  }
  if (selector == 4) {
    manual();
    return;
  }
  if (selector == 5) {
    favor();
    return;
  }
  buttonState0 = digitalRead(BUT1);
  buttonState1 = digitalRead(BUT2);
  buttonState2 = digitalRead(BUT3);
  if (buttonState0 == LOW) {
    scan = scan - 1;
    dp = 0;
  }
  if (buttonState1 == LOW) {
    selector = scan;
    dp = 0;
  }
  if (buttonState2 == LOW) {
    scan = scan + 1;
    dp = 0;
  }
  if (scan >= 5)scan = 1;
  if (scan < 1)scan = 1;
  display.clearDisplay();
  display.drawBitmap(0, 0, border, 128, 64, 1);
  display.setTextSize(1);
  display.fillRect(3, 10 * scan + 3, 120, 10, WHITE);
  display.setTextColor(scan == 0 ? BLACK : WHITE);
  display.setCursor(0, 1);
  display.print(PSTR2("      "));
  display.setTextColor(scan == 1 ? BLACK : WHITE);
  display.setCursor(2, 10 * 1 + 5);
  display.print(PSTR2("       SEARCH "));
  display.setTextColor(scan == 2 ? BLACK : WHITE);
  display.setCursor(2, 10 * 2 + 5);
  display.print(PSTR2("  SET FILTER L M H"));
  display.setTextColor(scan == 3 ? BLACK : WHITE);
  display.setCursor(2, 10 * 3 + 5);
  display.print(PSTR2("       SCOPE "));
  display.setTextColor(scan == 4 ? BLACK : WHITE);
  display.setCursor(2, 10 * 4 + 5);
  display.print(PSTR2("        BACK  "));
  display.display();
  digitalWrite(ledPin, LOW);
}

#endif


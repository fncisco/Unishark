#ifdef osd
void osd() {  // new section to send data 2 osd ,,
#ifdef Furious
  rssiosd1 = map(analogRead(A6), rssi1_MIN, rssi1_MAX, 100, 0);
  delay (30);
  rssiosd2 = map(analogRead(A7), rssi2_MIN, rssi2_MAX, 100, 0);
#endif
#ifdef Realac
  rssiosd1 = map(analogRead(A6), rssi1_MIN, rssi1_MAX, 100, 0);
  delay (30);
  rssiosd2 = map(analogRead(A7), rssi2_MIN, rssi2_MAX, 100, 0);
#endif
  delay (30);
  Serial.print(channel);
  Serial.print(",");
  delay (3);
  Serial.print(rssiosd1);
  Serial.print(",");
  delay (3);
  Serial.print(rssiosd2);
  Serial.print(",");
  delay (3);
  Serial.print(swt);
  Serial.print(",");
  delay (3);
  Serial.println(mnu);///  new for showing menu stuff ,,///
  mnu = 0;
  return;
}
#endif

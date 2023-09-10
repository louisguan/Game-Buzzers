#define BTNnumber 9
#define LEDnumber 2
int BTNnLED[BTNnumber][LEDnumber] =
{
  {13, 10}, // #1
  {A0, 8}, // #2
  {12, 6}, // #3
  {11, 4}, // #4
  {A1, 9}, // #5
  {A2, 7}, // #6
  {A3, 5}, // #7
  {A4, 3}, // #8
  {A5, 2} // #Judge
};

int BTNState[BTNnumber]
{
  0, 0, 0, 0, 0, 0, 0, 0, 0
};

bool BTNEn[BTNnumber]
{
  true, true, true, true, true, true, true, true, true
};

void setup()
{
  for (int i = 0; i < BTNnumber; i++)
  {
    pinMode(BTNnLED[i][0], INPUT_PULLUP);
  }
  for (int j = 0; j < BTNnumber; j++)
  {
    pinMode(BTNnLED[j][1], OUTPUT);
  }
  for (int j = 0; j < BTNnumber; j++)
  {
    digitalWrite(BTNnLED[j][1], LOW);
  }

  for (int j = 0; j < BTNnumber; j++)
  {
    digitalWrite(BTNnLED[j][1], HIGH);
    delay(100);
    digitalWrite(BTNnLED[j][1], LOW);
    delay(50);
  }
}

void loop()
{
  for (int i = 0; i < BTNnumber; i++) // 歸位
  {
    BTNEn[i] = true;
    digitalWrite(BTNnLED[i][1], LOW);
  }
  //
  //
  while (digitalRead(BTNnLED[8][0]) == HIGH ) // 主持人尚未說可以開始，大家等待
  {

  }
  if (digitalRead(BTNnLED[8][0]) == LOW ) // MCU太快，需要延遲
  {
    while (digitalRead(BTNnLED[8][0]) == LOW )
    {
      delay(10);
    }
  }
  //
  //
  while (digitalRead(BTNnLED[8][0]) == HIGH ) // 開始搶答
  {
    digitalWrite(BTNnLED[8][1], HIGH);
    int i;
    for (i = 0; i < BTNnumber; i++)
    {
      BTNState[i] = digitalRead(BTNnLED[i][0]);
      if (BTNEn[i] == true && BTNState[i] == LOW)
      {
        for (int j = 0; j < BTNnumber; j++)
        {
          BTNEn[j] = false;
          digitalWrite(BTNnLED[j][1], LOW);
        }
        BTNEn[i] = true; // 第一位
        digitalWrite(BTNnLED[i][1], HIGH); // 第一位
        // digitalWrite(BTNnLED[8][1], HIGH); // 評審
      }
    }
  }
}

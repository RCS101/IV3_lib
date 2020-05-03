#include <IV3.h>

#define ZERO  0x3F
#define ONE   0x06
#define TWO   0x5B
#define THREE 0x4F
#define FOUR  0x66
#define FIVE  0x6D
#define SIX   0x7D
#define SEVEN 0x07
#define EIGHT 0x7F
#define NINE  0x6F
#define DP    0x80

IV3_clock IV3;

uint8_t tubes[4];
uint16_t cnt = 100;
int k =0, j;

void setup()
{
  Serial.begin(9600);
}

void loop()
{
  IV3.user_display(tubes);
  delay(200);

  for(j=0;j<4;j++)
  {
    if(j==k)
      tubes[j] |= DP;
    else
      tubes[j] &= 0x7F;
  }

  k++;
  if(k==5)
  {
    cnt--;
    k=0;
    write_IV3_num(cnt, tubes);
  }

  if (cnt == 0)
  {
    IV3.clock_mode();
    while (1);
  }
}

void numberWang(uint16_t numb, uint8_t *numbers)
{
  numbers[0] = numb / 1000;
  numbers[1] = (numb / 100) % 10;
  numbers[2] = (numb / 10) % 10;
  numbers[3] = numb % 10;
  Serial.print(numbers[0]);
  Serial.print(" ");
  Serial.print(numbers[1]);
  Serial.print(" ");
  Serial.print(numbers[2]);
  Serial.print(" ");
  Serial.print(numbers[3]);
  Serial.println("");
}

void write_IV3_num(uint16_t numb, uint8_t *t)
{
  uint8_t numbers[4];

  numberWang(numb, numbers);

  for (int i = 0; i < 4; i++)
  {
    switch (numbers[i])
    {
      case 0:
        t[i] = ZERO;
        break;
      case 1:
        t[i] = ONE;
        break;
      case 2:
        t[i] = TWO;
        break;
      case 3:
        t[i] = THREE;
        break;
      case 4:
        t[i] = FOUR;
        break;
      case 5:
        t[i] = FIVE;
        break;
      case 6:
        t[i] = SIX;
        break;
      case 7:
        t[i] = SEVEN;
        break;
      case 8:
        t[i] = EIGHT;
        break;
      case 9:
        t[i] = NINE;
        break;
      case 10:
        t[i] = DP;
        break;
    }
  }
}

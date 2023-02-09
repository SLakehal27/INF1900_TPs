#define F_CPU 8000000
#include <avr/io.h>
#include <util/delay.h>

void delaiUs(uint16_t count)
{
  for (int i = 0; i < count; i++)
  {
    _delay_us(1);
  }
}

int main()
{
  DDRA = 0xff; // PORT A est en mode sortie
  DDRD = 0x00; // PORT D est en mode entree
  const uint8_t INCOLORE = 0x00, ROUGE = 0x01, VERT = 0x02;
  const uint16_t B = 1000;
  uint16_t A = 0, COULEUR = 0x03;
  bool change = false;
  bool changeCouleur = false;

  while (true)
  {
    if (changeCouleur)
    {
      COULEUR = VERT;
    }
    else
    {
      COULEUR = ROUGE;
    }

    if (A == 0)
    {
      change = false;
    }
    if (A == 1000)
    {
      change = true;
      switch (changeCouleur)
      {
      case true:
        changeCouleur = false;
        break;
      case false:
        changeCouleur = true;
        break;
      }
    }
    if (change)
    {
      A -= 1;
    }

    if (!change)
    {
      A += 1;
    }

    PORTA = INCOLORE & 0x3;
    delaiUs(A);
    PORTA = COULEUR & 0x3;
    delaiUs(B - A);
  }

  return 0;
}
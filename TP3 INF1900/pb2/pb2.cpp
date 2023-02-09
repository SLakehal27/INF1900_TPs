#define F_CPU 8000000
#include <avr/io.h>
#include <util/delay.h>

enum class Etats
{
  INIT,
  TRANS,
  ETAT2,
};

void delaiUs(uint16_t count)
{
  for (int i = 0; i < count; i++)
  {
    _delay_us(1);
  }
}

void vitesse(uint16_t* a, uint16_t b)
{
  // const uint8_t INACTIF = 0x00 , ACTIF = 0x02;
  // int iterations = 5;
  // for(int i = 0; i<iterations;i++)
  // {
  //   PORTB = INACTIF & 0x3;
  //   delaiUs(*a);
  //   PORTB = ACTIF & 0x3;
  //   delaiUs(b - *a);
  //   _delay_ms(2000);
  //   *a += 15;
  // }

} 

int main()
{
  DDRA = 0xff; // PORT A est en mode sortie
  DDRB = 0xff;

  uint16_t B = 60;
  uint16_t A = 30;
  const uint8_t INACTIF = 0x00 , ACTIF = 0x02;
  bool foo = false;

  Etats foobar = Etats::INIT;

  while (true)
  {  
    // vitesse(&A,B);
    // // PORTA = ACTIF & 0x3;
    // // return 0;
    // // A += 15;
    switch (foobar)
    {
    case Etats::INIT:
      PORTB = INACTIF & 0x3;
      delaiUs(A);
      PORTB = ACTIF & 0x3;
      delaiUs(B - A);
      foobar = Etats::TRANS;
      break;
    
    case Etats::TRANS:
      foobar = Etats::ETAT2;
      break;

    case Etats::ETAT2:
      PORTB = INACTIF & 0x3;
      delaiUs(A);
      PORTB = ACTIF & 0x3;
      delaiUs(B - A);
      foobar = Etats::TRANS;
      break;
    }
  }

  return 0;
}
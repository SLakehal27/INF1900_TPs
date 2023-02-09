#define F_CPU 8000000
#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#include "memoire_24.h"

int main()
{
  DDRA = 0xff; // PORT A est en mode sortie
  DDRB = 0xff; // PORT B est en mode sortie
  DDRC = 0x00; // PORT C est en mode sortie
  DDRD = 0x00; // PORT D est en mode entree
  Memoire24CXXX memoire;
  const uint8_t INCOLORE = 0x00, ROUGE = 0x01, VERT = 0x02, DELAI_ECRITURE = 5;
  uint8_t longueur = 47; 
  uint8_t message[longueur] = " *P*O*L*Y*T*E*C*H*N*I*Q*U*E* *M*O*N*T*R*E*A*L*";
  memoire.ecriture((uint16_t)0, message, longueur);
  _delay_ms(DELAI_ECRITURE);
  uint8_t message2[longueur];
  memoire.lecture((uint16_t)0,message2,longueur);

  for (int i =0; i < longueur; i++)
  {
    if (message[i] == message2[i])
    {
      PORTA = VERT & 0x3;
    }
    else
    {
      PORTA = ROUGE & 0x3;
      break;
    }
  }

  return 0;
}

#define F_CPU 8000000
#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>

void ajustementPwm (uint8_t niveau) {

// mise à un des sorties OC1A et OC1B sur comparaison

// réussie en mode PWM 8 bits, phase correcte

// et valeur de TOP fixe à 0xFF (mode #1 de la table 16-5

// page 130 de la description technique du ATmega324PA)

OCR1A = niveau;

OCR1B = niveau;


// division d'horloge par 8 - implique une fréquence de PWM fixe

TCCR1A = (1<<WGM10)|(1<<COM1A1)|(1<<COM1B1);

TCCR1B = (1 << CS11);

TCCR1C = 0;

}


int main()
{
  DDRD = 0xff;
  while (true)
  {
    ajustementPwm(0);
    _delay_ms(2000);
    ajustementPwm(64);
    _delay_ms(2000);
    ajustementPwm(128);
    _delay_ms(2000);
    ajustementPwm(192);
    _delay_ms(2000);
    ajustementPwm(255);
    _delay_ms(2000);
  }
  return 0;
}



//     case Etats::ETEINT2:
//     PORTA = INCOLORE & 0x03;
//       if (verifierBouton())
//       {
//         changerEtat(Etats::CLICK3);
//       }
//       break;

//     case Etats::CLICK3:
//     PORTA = VERT & 0x03;
//       if (!verifierBouton())
//       {
//         changerEtat(Etats::ETEINT);
//       }
//       break;
//   }
// }

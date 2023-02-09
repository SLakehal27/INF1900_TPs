#define F_CPU 8000000
#include <avr/io.h>
#include <util/delay.h>
const uint8_t incolore = 0x00, rouge = 0x01, vert = 0x02, ambre = 0x03;
unsigned long compteur = 0; // le compteur est initialise a 0.
uint8_t couleur = 0x01, precouleur = 0x00;
int blank = 0;

bool pressed = false;

bool verifierBoutton(bool check)
{
  if (PIND & 0x04)
  {
    _delay_ms(10);
    check = true;
  }
  else
  {
    check = false;
  }
  return check;
}

int main()
{
  DDRA = 0xff; // PORT A est en mode sortie
  DDRB = 0xff; // PORT B est en mode sortie
  DDRC = 0xff; // PORT C est en mode sortie
  DDRD = 0x00; // PORT D est en mode entree
  for (;;)
  {
    compteur++;
    pressed = verifierBoutton(pressed);
    if (!pressed)
    {
      PORTA = incolore & 0x3;
    }
    if (pressed && couleur == vert)
    {
      PORTA = vert & 0x3;
      _delay_ms(10);
      blank++;
    }
    else if (pressed && couleur == rouge)
    {
      PORTA = rouge & 0x3;
      _delay_ms(10);
      blank++;
    }
    else if (pressed && couleur == ambre)
    {
      PORTA = rouge & 0x3;
      _delay_ms(5);
      PORTA = vert & 0x3;
      _delay_ms(5);
      blank++;
    }
    if (precouleur == couleur && !pressed && blank != 0)
    {
      if (couleur == rouge)
      {
        couleur = vert;
      }
      else if (couleur == vert)
      {
        couleur = ambre;
      }
      else if (couleur == ambre)
      {
        couleur = rouge;
      }
      blank = 0;
    }
    precouleur = couleur;
  }

  // Couleur Rouge
  // PORTA = rouge & 0x3;
  //_delay_ms(250);

  // Couleur Verte
  // PORTA = vert & 0x3;
  //_delay_ms(250);

  // for (int i = 0; i < 35; i++)
  //{
  //  Couleur Ambrée
  // PORTA = rouge & 0x3;
  //_delay_ms(5);
  // PORTA = vert & 0x3;
  //_delay_ms(5);

  // if (i == 35)
  //{
  // break;
  //}
  //}
  return 0;
}
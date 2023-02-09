#define F_CPU 8000000
#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#include <avr/eeprom.h>
#include "memoire_24.h"

void initialisationUART(void)
{

  // 2400 bauds. Nous vous donnons la valeur des deux

  // premiers registres pour vous éviter des complications.

  UBRR0H = 0;

  UBRR0L = 0xCF;

  // permettre la réception et la transmission par le UART0

  UCSR0A = (1 << RXC0) | (1 << TXC0);

  UCSR0B = (1 << RXEN0) | (1 << TXEN0);

  // Format des trames: 8 bits, 1 stop bits, sans parité

  UCSR0C = (1<<UCSZ01)|(1<<UCSZ00);
}

// Du USART vers le PC

void transmissionUART(uint8_t donnee)
{
  /* Wait for empty transmit buffer */
  while (!(UCSR0A & (1 << UDRE0)))
    ;
  /* Put data into buffer, sends the data */
  UDR0 = donnee;
}

int main()
{
  initialisationUART();
  
  DDRA = 0xff; // PORT A est en mode sortie
  DDRB = 0xff; // PORT B est en mode sortie
  DDRC = 0x00; // PORT C est en mode sortie
  DDRD = 0x00; // PORT D est en mode entree
  Memoire24CXXX memoire;
  const uint8_t DELAI_ECRITURE = 100;
  uint8_t longueur = 11; 
  uint8_t message[longueur] = "we cooked\n";
  memoire.ecriture((uint16_t)0, message, longueur);
  _delay_ms(DELAI_ECRITURE);
  uint8_t message2[longueur];
  memoire.lecture((uint16_t)0,message2,longueur);
  
  for(int i = 0; i<longueur;i++)
  {
    transmissionUART(message2[i]);
  }
  return 0;
}

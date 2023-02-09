#define F_CPU 8000000
#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>

/* 
Noms des auteurs: Yassir Marra, Selim Lakehal

Description: Ce code utilise une enum class Etats pour definir les differents etats possibles. Pour cela, on initialise etatCourant a l'etat Eteint.
La fonction verifierBouton sert de debounce, il verifie en premier lieu si le bouton est appuye, puis rajoute un delai de 10 millisecondes et reverifie 
une deuxieme fois si le bouton est allume, il retourne true si oui et retourne false si le bouton n'est pas appuye. 
La fonction changerEtat prend en parametre un etat et permet de changer d'etat.
Dans le main, on utilise un switch case avec l'etat etatCourant en parametre. 
Chaque etat affiche une couleur dans le del et passe au prochain etat en fonction de la pression du bouton

Identifications materielles (Broches I/O) : Un bout sur le connecteur IDC de la section del libre et lautre sur le port A1-2.

Table des etats:
Couleurs: INCOLORE = 00, ROUGE = 01 ,VERT = 10, AMBRE = 11;
+--------------+-------+--------------+----------+
| État présent | Appui | État suivant | Couleur  |
+--------------+-------+--------------+----------+
| Éteint       | 0     | Éteint       | 01       |
+--------------+-------+--------------+----------+
| Éteint       | 1     | Click1       | 01       |
+--------------+-------+--------------+----------+
| Click1       | 1     | Click1       | 11       |
+--------------+-------+--------------+----------+
| Click1       | 0     | Éteint1      | 11       |
+--------------+-------+--------------+----------+
| Éteint1      | 0     | Éteint1      | 10       |
+--------------+-------+--------------+----------+
| Éteint1      | 1     | Click2       | 10       |
+--------------+-------+--------------+----------+
| Click2       | 1     | Click2       | 01       |
+--------------+-------+--------------+----------+
| Click2       | 0     | Éteint2      | 01       |
+--------------+-------+--------------+----------+
| Éteint2      | 0     | Éteint2      | 00       |
+--------------+-------+--------------+----------+
| Éteint2      | 1     | Click3       | 00       |
+--------------+-------+--------------+----------+
| Click3       | 1     | Click3       | 10       |
+--------------+-------+--------------+----------+
| Click3       | 0     | Éteint       | 10       |
+--------------+-------+--------------+----------+


*/




enum class Etats
{
  ETEINT,
  ETEINT1,
  ETEINT2,
  CLICK1,
  CLICK2,
  CLICK3,
};

volatile Etats gEtat = Etats::ETEINT; // selon le nom de votre variable
volatile Etats nextEtat = Etats::CLICK1; // selon le nom de votre variable

// placer le bon type de signal d'interruption
// à prendre en charge en argument

ISR (INT0_vect) {

// laisser un délai avant de confirmer la réponse du
// bouton-poussoir: environ 30 ms (anti-rebond)
_delay_ms (30);

gEtat = nextEtat;

// changements d'état tels que ceux de la
// semaine précédente

// Voir la note plus bas pour comprendre cette instruction et son rôle
EIFR |= (1 << INTF0) ;
}

void initialisation ( void ) {

// cli est une routine qui bloque toutes les interruptions.

// Il serait bien mauvais d'être interrompu alors que

// le microcontrôleur n'est pas prêt...

cli ();


// configurer et choisir les ports pour les entrées

// et les sorties. DDRx... Initialisez bien vos variables

DDRA = 0xff; // PORT A est en mode sortie
DDRD = 0x00; // PORT D est en mode entree


// cette procédure ajuste le registre EIMSK
// de l’ATmega324PA pour permettre les interruptions externes

EIMSK |= (1 << INT0) ;

// il faut sensibiliser les interruptions externes aux
// changements de niveau du bouton-poussoir
// en ajustant le registre EICRA
EICRA |= (1 << ISC00);
// sei permet de recevoir à nouveau des interruptions.
sei ();

}


// Etats changerEtat(Etats etatSuivant)
// {
//   etatCourant = etatSuivant;
//   return etatCourant;
// }

int main()
{
  initialisation();
  const uint8_t INCOLORE = 0x00, ROUGE = 0x01, VERT = 0x02, DELAI_AMBRE = 5;
  while (true)
  {

    switch (gEtat)
    {
        case Etats::ETEINT:
        PORTA = ROUGE & 0x3;
        nextEtat = Etats::CLICK1;
        break;

        case Etats::CLICK1:
        nextEtat  = Etats::ETEINT1;
        PORTA = ROUGE & 0x3;
        _delay_ms(DELAI_AMBRE);  
        PORTA = VERT & 0x3;
        _delay_ms(DELAI_AMBRE);
        break;
        
        case Etats::ETEINT1:
        nextEtat = Etats::CLICK2;
        PORTA = VERT & 0x03;
        break;

        case Etats::CLICK2:
        nextEtat = Etats::ETEINT2;
        PORTA = ROUGE & 0x03;
        break;

        case Etats::ETEINT2:
        nextEtat = Etats::CLICK3;
        PORTA = INCOLORE & 0x03;
        break;

        case Etats::CLICK3:
        nextEtat = Etats::ETEINT;
        PORTA = VERT & 0x03;
        break;
    }
    // case Etats::CLICK2:
    // PORTA = ROUGE & 0x03;
    //   if (!verifierBouton())
    //   {
    //     changerEtat(Etats::ETEINT2);
    //   }
    //   break;
    // case Etats::ETEINT2:
    // PORTA = INCOLORE & 0x03;
    //   if (verifierBouton())
    //   {
    //     changerEtat(Etats::CLICK3);
    //   }
    //   break;
    // case Etats::CLICK3:
    // PORTA = VERT & 0x03;
    //   if (!verifierBouton())
    //   {
    //     changerEtat(Etats::ETEINT);
    //   }
    //   break;
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

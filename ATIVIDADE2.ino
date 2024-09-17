#define BOTAO_LIGA (1 << PB0)     // Define o pino PD1 como BOTAO_LIGA
#define BOTAO_DESLIGA (1 << PB1)  // Define o pino PD0 como BOTAO_DESLIGA
#define SENSOR1 (1 << PB2)
#define SENSOR2 (1 << PB3)
#define SENSOR3 (1 << PB4)
#define MOTOR (1 << PD1)   // Define o pino PD7 como MOTOR
#define PULLUP (1 << PD5)  // Define o pino PD5 para pull-up
#define LEDON (1 << PD2)
#define LEDOF (1 << PD3)
#define ALERT (1 << PD4)
#define CH2 (1 << PD6)
#define CH1 (1 << PD7)


int main() {
  // Configura o pino PD7 como saída para o motor
  DDRD |= MOTOR;  // Configura PD7 como saída
  DDRD |= ALERT;
  DDRD |= LEDON;
  DDRD |= LEDOF;


  // Configura o pino PD5 como entrada com pull-up ativado
  DDRD &= ~PULLUP;  // Configura PD5 como entrada
  PORTD |= PULLUP;  // Ativa pull-up em PD5


  for (;;) {
    // Leitura das entradas
    unsigned short int botaoliga = PINB & BOTAO_LIGA;
    unsigned short int botaodesliga = PINB & BOTAO_DESLIGA;
    unsigned short int sensor1 = PIND & SENSOR1;
    unsigned short int sensor2 = PIND & SENSOR2;
    unsigned short int sensor3 = PIND & SENSOR3;
    unsigned short int ch1 = PIND & CH1;
    unsigned short int ch2 = PIND & CH2;




    // Verifica se o botão de ligar está pressionado
    if (botaoliga != 0) {

      PORTD = PORTD | MOTOR;  // Liga o motor
      PORTD &= ~LEDOF;
    }
    // Verifica se o botão de desligar está pressionado
    if (botaodesliga != 0) {
      PORTD &= ~MOTOR;  // Desliga o motor
    }

    switch ((ch1 >> 3) | ((ch2 >> 2) << 1)) {
      case 0b00:
        if (sensor1 != 0) {
          PORTD = PORTD | LEDON;
          PORTD &= ~MOTOR;
        }

        break;
      case 0b01:  // chave1 == 0 e chave2 == 1
        if (sensor2 != 0) {
          PORTD = PORTD | LEDON;
          PORTD &= ~MOTOR;
        }
        break;
      case 0b10:  // chave1 == 1 e chave2 == 0
        if (sensor3 != 0) {
          PORTD = PORTD | LEDON;
          PORTD &= ~MOTOR;
        }
        break;
    }
  }

  return 0;
}

#include <avr/sleep.h>
#include <avr/interrupt.h>



//Prototypen:
void gotoSleep(void);



#define esp_power 2
#define esp_ready 4
#define switch_state 1
#define sensor 3


volatile bool wakeup = false;
bool statusSleep = true;
bool boottime = false;


void setup() {
    pinMode(sensor, INPUT);
    pinMode(esp_ready, INPUT_PULLUP);
    pinMode(esp_power, OUTPUT);
    digitalWrite(esp_power, LOW);
    pinMode(switch_state, OUTPUT);

    ADCSRA &= ~_BV(ADEN); //ADC ausschalten
    //Setzen der Register fuer Pin-Change-Interrupt Pin PB3
    //Loeschen des Global Interrupt Enable Bits (I) im Status Register (SREG)
    SREG &= 0x7F; //entspricht "cli();"
    //Setze des Pin Change Interrupt Enable Bit
    GIMSK |= (1 << PCIE);
    //Setzen des Pin Change Enable Mask Bit 3 (PCINT3)  ==> Pin PB3
    PCMSK |= (1 << PCINT3);
    //Setzen des Global Interrupt Enable Bits (I) im Status Register (SREG)
    SREG |= 0x80; //entspricht "sei();"
}



void loop() {
    if (wakeup)
    {
        
        digitalWrite(switch_state, digitalRead(sensor));
        digitalWrite(esp_power, HIGH);
        
        if (boottime) //ESPzeit geben um esp_ready auf low zu setzen.
        {
            delay(1000);
            boottime = false;
        }

        if (!digitalRead(esp_ready)) //timeout hinzufügen!
        {
            digitalWrite(esp_power, LOW);
            //pinMode(sensor, OUTPUT);
            wakeup = false;
            statusSleep = true;
        }
    }

    if (statusSleep)
    {
        gotoSleep();
        statusSleep = false;
        boottime = true;
    }
}



//Attiny in den Schlafmodus setzen

void gotoSleep()
{
    pinMode(esp_power, INPUT);
    pinMode(switch_state, INPUT);

    //byte adcsra;

    //adcsra = ADCSRA; //ADC Control and Status Register A sichern
    //ADCSRA &= ~_BV(ADEN); //ADC ausschalten

    MCUCR |= (1 << SM1) & ~(1 << SM0); //Sleep Modus = Power Down
    MCUCR |= _BV(SE); //Sleep Enable setzen
    sleep_cpu(); //Schlafe ....
    MCUCR &= ~(1 << SE); //Sleep Disable setzen

    //ADCSRA = adcsra; //ADCSRA-Register rückspeichern

    pinMode(esp_power, OUTPUT);
    pinMode(switch_state, OUTPUT);
    pinMode(sensor, INPUT);
    pinMode(esp_ready, INPUT_PULLUP);
}



//Interrupt Serviceroutine (Pin-Change-Interrupt)
ISR(PCINT0_vect)
{
    wakeup = true;
}

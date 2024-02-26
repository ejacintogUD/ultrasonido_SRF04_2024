/* mbed Microcontroller Library
 * Copyright (c) 2019 ARM Limited
 * SPDX-License-Identifier: Apache-2.0
 */

#include "ThisThread.h"
#include "Thread.h"
#include "UnbufferedSerial.h"
#include "lorawan_data_structures.h"
#include "mbed.h"
#include <cstdio>


// Blink0ing rate in milliseconds
#define BLINKING_RATE     500ms
#define TIEMPO_LECTURA    500ms

UnbufferedSerial pc(USBTX, USBRX);

char men[30];

Thread hilo_leer_dist;
void leer_dist(void);

Timer t;

DigitalOut Trg(D2);
DigitalIn  Echo(D3);

long Distancia;

int main()
{
    // Initialise the digital pin LED1 as an output
    DigitalOut led(LED1);
    sprintf(men, "Arranque del sistema \n\r");
    pc.write(men, sizeof(men));
    hilo_leer_dist.start(leer_dist);

    while (true) {
        led = !led;
        ThisThread::sleep_for(BLINKING_RATE);
    }
}

void leer_dist (void)
{
    while(true)
    {
        
        Trg=1;
        wait_us(10);
        Trg=0;
        while(!Echo){}
        t.reset();
        t.start();
        while(Echo){}
        t.stop();
        Distancia = t.elapsed_time().count() / 58;
        sprintf(men, "La distancia es: %lu cm \n\r", Distancia);
        pc.write(men, sizeof(men));

        ThisThread::sleep_for(TIEMPO_LECTURA);
    }
}




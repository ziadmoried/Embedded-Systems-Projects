/******************************************************************************
 *
 * Module: Ultrasonic
 *
 * File Name: ultrasonic.c
 *
 * Description: Source file for the Ultrasonic (HC-SR04) driver
 *
 *******************************************************************************/

#ifndef F_CPU
#define F_CPU 16000000UL
#endif

#include "ultrasonic.h"
#include "gpio.h"
#include "icu.h"
#include <util/delay.h>
#include <stdint.h>

/* Trigger pin connection */
#define TRIGGER_PORT        PORTD_ID
#define TRIGGER_PIN         7

/* Timer prescaler used by ICU (must match value passed to ICU_init in Ultrasonic_init) */
#define ULTRASONIC_TIMER_PRESCALER  8U

/* Timeout waiting for echo (ms) */
#define ULTRASONIC_TIMEOUT_MS 60U

/* Globals used by ICU ISR callback */
static volatile uint16 g_firstEdge  = 0;
static volatile uint16 g_secondEdge = 0;
static volatile uint8  g_state      = 0; /* 0 = waiting rising, 1 = waiting falling */
static volatile uint8  g_done       = 0;

/* ICU callback (registered with ICU_setCallBack) */
void Ultrasonic_edgeProcessing(void)
{
    if (g_state == 0)
    {
        g_firstEdge = ICU_getInputCaptureValue();
        ICU_setEdgeDetectionType(FALLING);
        g_state = 1;
    }
    else if (g_state == 1)
    {
        g_secondEdge = ICU_getInputCaptureValue();
        ICU_setEdgeDetectionType(RISING); /* prepare for next measurement */
        g_state = 0;
        g_done = 1;
    }
}

/* Initialize ultrasonic + ICU */
void Ultrasonic_init(void)
{
    /* Configure trigger pin as output and keep low */
    GPIO_setupPinDirection(TRIGGER_PORT, TRIGGER_PIN, PIN_OUTPUT);
    GPIO_writePin(TRIGGER_PORT, TRIGGER_PIN, LOGIC_LOW);

    /* Initialize ICU with prescaler F_CPU/8 and rising edge */
    ICU_ConfigType cfg = { F_CPU_8, RISING };
    ICU_init(&cfg);
    ICU_setCallBack(Ultrasonic_edgeProcessing);
}

/* Send trigger pulse (10 us) */
void Ultrasonic_Trigger(void)
{
    GPIO_writePin(TRIGGER_PORT, TRIGGER_PIN, LOGIC_HIGH);
    _delay_us(10);
    GPIO_writePin(TRIGGER_PORT, TRIGGER_PIN, LOGIC_LOW);
}

/* Single raw measurement. Returns 0xFFFF on timeout/error, otherwise distance in cm. */
uint16 Ultrasonic_readDistanceRaw(void)
{
    /* reset flags */
    g_firstEdge = 0;
    g_secondEdge = 0;
    g_state = 0;
    g_done = 0;

    /* clear timer and fire trigger */
    ICU_clearTimerValue();
    Ultrasonic_Trigger();

    /* wait for measurement complete with timeout */
    uint16 waited = 0;
    while (!g_done && (waited < ULTRASONIC_TIMEOUT_MS))
    {
        _delay_ms(1);
        waited++;
    }

    if (!g_done)
    {
        return 0xFFFF; /* timeout => no valid reading */
    }

    /* compute ticks (handle overflow) */
    uint32_t ticks;
    if (g_secondEdge >= g_firstEdge)
    {
        ticks = (uint32_t)g_secondEdge - (uint32_t)g_firstEdge;
    }
    else
    {
        ticks = (uint32_t)65536UL - (uint32_t)g_firstEdge + (uint32_t)g_secondEdge;
    }

    /* Now compute distance in cm using exact integer arithmetic:
       time_us = ticks * prescaler * 1,000,000 / F_CPU
       distance_cm = time_us / 58
       => distance_cm = (ticks * prescaler * 1,000,000) / (F_CPU * 58)
       Use 64-bit math to avoid overflow and round properly.
    */
    uint64_t numerator = (uint64_t)ticks * (uint64_t)ULTRASONIC_TIMER_PRESCALER * 1000000ULL;
    uint64_t denom     = (uint64_t)F_CPU * 58ULL;

    uint16 distance = (uint16)((numerator + (denom / 2ULL)) / denom); /* rounded */

    return distance;
}

/* Averaged measurement (samples >= 1). Returns 0xFFFF if all samples failed. */
uint16 Ultrasonic_readDistanceAvg(uint8 samples)
{
    if (samples == 0) samples = 1;
    uint32_t sum = 0;
    uint8 valid = 0;

    for (uint8 i = 0; i < samples; ++i)
    {
        uint16 d = Ultrasonic_readDistanceRaw();
        if (d != 0xFFFF)
        {
            sum += d;
            valid++;
        }
        _delay_ms(30);
    }

    if (valid == 0) return 0xFFFF;
    return (uint16)((sum + (valid/2U)) / valid); /* rounded average */
}

/************************************************************************************************
Copyright (c) 2024, Karen Zamudio <kzamudioquintero@gmail.com>

Permission is hereby granted, free of charge, to any person obtaining a copy of this software and
associated documentation files (the "Software"), to deal in the Software without restriction,
including without limitation the rights to use, copy, modify, merge, publish, distribute,
sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all copies or substantial
portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT
NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES
OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN
CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.

SPDX-License-Identifier: MIT
*************************************************************************************************/

/** @file leds.c
 ** @brief Capa de abstracción para controlar LEDs (implementación)
 **/

/* === Headers files inclusions =============================================================== */

#include <stddef.h>
#include "leds.h"

/* === Macros definitions ====================================================================== */

/* === Private data type declarations ========================================================== */
/* === Private variable declarations =========================================================== */

static uint16_t * led_port;

/* === Public function implementation ========================================================== */

/**
 * @brief Inicializa el controlador de LEDs.
 *
 * @param port Puntero al puerto de salida de los LEDs.
 * @return 0 en caso de éxito, -1 si el puerto es nulo.
 */
int leds_init(uint16_t * port) {
    // Verifica si el puerto es nulo
    if (port == NULL) {
        return LED_ERROR_NULL_PORT;
    }

    // Almacena el puerto en la variable global
    led_port = port;

    // Apaga todos los LEDs inicialmente
    *led_port = LED_OFF;

    return LED_SUCCESS;
}

/**
 * @brief Detiene y apaga el controlador de LEDs.
 */
void leds_deinit(void) {
    // Apaga todos los LEDs si el puerto no es nulo
    if (led_port != NULL) {
        *led_port = LED_OFF;
        led_port = NULL;
    }
}

/**
 * @brief Enciende un LED individual.
 *
 * @param led Número de LED a encender (1-16).
 * @return 0 en caso de éxito, -2 si el LED está fuera de rango o el puerto es nulo.
 */
int leds_turn_on_single(uint16_t led) {
    // Verifica si el puerto es nulo o el LED está fuera de rango
    if (led_port == NULL || led < 1 || led > LED_COUNT) {
        return LED_ERROR_INVALID_PARAMS;
    }

    // Enciende el LED correspondiente
    *led_port |= (1 << (led - 1));

    return LED_SUCCESS;
}

/**
 * @brief Apaga un LED individual.
 *
 * @param led Número de LED a apagar (1-8).
 * @return 0 en caso de éxito, -2 si el LED está fuera de rango o el puerto es nulo.
 */
int leds_turn_off_single(uint16_t led) {
    // Verifica si el puerto es nulo o el LED está fuera de rango
    if (led_port == NULL || led < 1 || led > LED_COUNT) {
        return LED_ERROR_INVALID_PARAMS;
    }

    // Apaga el LED correspondiente
    *led_port &= ~(1 << (led - 1));

    return LED_SUCCESS;
}

/**
 * @brief Obtiene el estado de un LED individual.
 *
 * @param led Número de LED del que se desea obtener el estado (1-8).
 * @return Estado del LED (1 encendido, 0 apagado) o -2 si el LED está fuera de rango o el puerto es
 * nulo.
 */
int leds_get_status_single(uint16_t led) {
    // Verifica si el puerto es nulo o el LED está fuera de rango
    if (led_port == NULL || led < 1 || led > LED_COUNT) {
        return LED_ERROR_INVALID_PARAMS;
    }

    // Retorna el estado del LED correspondiente
    return (*led_port & (1 << (led - 1))) != 0;
}

/**
 * @brief Enciende todos los LEDs.
 *
 * @return 0 en caso de éxito, -1 si el puerto es nulo.
 */
int leds_turn_on_all(void) {
    // Verifica si el puerto es nulo
    if (led_port == NULL) {
        return LED_ERROR_NULL_PORT;
    }

    // Enciende todos los LEDs
    *led_port = LED_ON;

    return LED_SUCCESS;
}

/**
 * @brief Apaga todos los LEDs.
 *
 * @return 0 en caso de éxito, -1 si el puerto es nulo.
 */
int leds_turn_off_all(void) {
    // Verifica si el puerto es nulo
    if (led_port == NULL) {
        return LED_ERROR_NULL_PORT;
    }

    // Apaga todos los LEDs
    *led_port = LED_OFF;

    return LED_SUCCESS;
}

/**
 * @brief Obtiene el estado de todos los LEDs.
 *
 * @return Estado de todos los LEDs o -1 si el puerto es nulo.
 */
int leds_get_status_all(void) {
    // Verifica si el puerto es nulo
    if (led_port == NULL) {
        return LED_ERROR_NULL_PORT;
    }

    // Retorna el estado de todos los LEDs
    return *led_port;
}

/* === End of documentation ==================================================================== */

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
#ifndef LEDS_H
#define LEDS_H

/** @file leds.h
 ** @brief Capa de abstracción para controlar LEDs
 **/

/* === Headers files inclusions ================================================================ */

#include <stdint.h>

/* === Cabecera C++ ============================================================================ */

/* === Public macros definitions =============================================================== */

#define LED_COUNT                16   /**< Cantidad total de LEDs */
#define LED_OFF                  0x00 /**< Valor para apagar todos los LEDs */
#define LED_ON                   0xFF /**< Valor para encender todos los LEDs */

#define LED_SUCCESS              0  /**< Operación exitosa */
#define LED_ERROR_NULL_PORT      -1 /**< Puerto nulo */
#define LED_ERROR_INVALID_PARAMS -2 /**< Parámetros inválidos */

/* === Public data type declarations =========================================================== */
/* === Public variable declarations ============================================================ */
/* === Public function declarations ============================================================ */

/**
 * @brief Inicializa el controlador de LEDs.
 *
 * Esta función inicializa el controlador de LEDs, configurando el puerto donde están conectados
 * y apagando todos los LEDs.
 *
 * @param port Puntero al puerto de salida donde están conectados los LEDs.
 * @return 0 si la operación es exitosa, -1 si el puerto es nulo.
 */
int leds_init(uint16_t * port);

/**
 * @brief Desinicializa el controlador de LEDs.
 *
 * Esta función desinicializa el controlador de LEDs, apagando todos los LEDs y liberando el
 * puerto.
 */
void leds_deinit(void);

/**
 * @brief Enciende un LED individual.
 *
 * Esta función enciende un LED específico.
 *
 * @param led Número del LED a encender (1 a LED_COUNT).
 * @return 0 si la operación es exitosa, -1 si el puerto es nulo o el LED está fuera de rango.
 */
int leds_turn_on_single(uint16_t led);

/**
 * @brief Apaga un LED individual.
 *
 * Esta función apaga un LED específico.
 *
 * @param led Número del LED a apagar (1 a LED_COUNT).
 * @return 0 si la operación es exitosa, -1 si el puerto es nulo o el LED está fuera de rango.
 */
int leds_turn_off_single(uint16_t led);

/**
 * @brief Obtiene el estado de un LED individual.
 *
 * Esta función obtiene el estado de un LED específico.
 *
 * @param led Número del LED a verificar (1 a LED_COUNT).
 * @return Estado del LED (0 apagado, 1 encendido), -1 si el puerto es nulo o el LED está fuera de
 * rango.
 */
int leds_get_status_single(uint16_t led);

/**
 * @brief Enciende todos los LEDs.
 *
 * Esta función enciende todos los LEDs.
 *
 * @return 0 si la operación es exitosa, -1 si el puerto es nulo.
 */
int leds_turn_on_all(void);

/**
 * @brief Apaga todos los LEDs.
 *
 * Esta función apaga todos los LEDs.
 *
 * @return 0 si la operación es exitosa, -1 si el puerto es nulo.
 */
int leds_turn_off_all(void);

/**
 * @brief Obtiene el estado de todos los LEDs.
 *
 * Esta función obtiene el estado de todos los LEDs.
 *
 * @return Estado de todos los LEDs, -1 si el puerto es nulo.
 */
int leds_get_status_all(void);

#endif /* LEDS_H */

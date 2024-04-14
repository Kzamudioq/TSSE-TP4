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

/** @file test_leds.c
 ** @brief Unit Tests para la API de manejo de LEDs. (ceedling)
 **/

/* === Headers files inclusions ================================================================ */

#include <unity.h>
#include "leds.h"

/* === Macros definitions ====================================================================== */
/* === Private data type declarations ========================================================== */
/* === Private variable declarations =========================================================== */

static uint16_t leds_port = 0xFF;

/* === Private function declarations =========================================================== */

void setUp(void);
void test_initial_state(void);
void test_single_led_on(void);
void test_single_led_off(void);
void test_multiple_leds_on_and_off(void);
void test_single_led_get_status_on(void);
void test_all_leds_turn_on(void);
void test_all_leds_turn_off(void);
void test_uninitialized_led_port(void);
void test_uninitialized_led_port_get_single_value(void);
void test_check_boundary_values(void);
void test_check_forbidden_values_turn_on(void);
void test_check_forbidden_values_turn_off(void);

/* === Public variable definitions ============================================================= */
/* === Private variable definitions ============================================================ */
/* === Private function implementation ========================================================= */
/* === Public function implementation ========================================================== */

void setUp(void) {
    leds_init(&leds_port);
}

/**
 * @brief Verifica que al iniciar el controlador todos los bits de los LEDs queden en cero.
 */
void test_initial_state(void) {
    TEST_ASSERT_EQUAL_INT(LED_SUCCESS, leds_init(&leds_port));
    TEST_ASSERT_EQUAL_UINT16(LED_OFF, leds_port);
}

/**
 * @brief Verifica que al prender un LED individual, el bit correspondiente se establezca en alto.
 */
void test_single_led_on(void) {
    const int LED = 3;

    TEST_ASSERT_EQUAL_INT(LED_SUCCESS, leds_turn_on_single(LED));
    TEST_ASSERT_BIT_HIGH(LED - 1, leds_port);
    TEST_ASSERT_BITS_LOW(~(1 << (LED - 1)), leds_port);
}

/**
 * @brief Verifica que al apagar un LED individual, el bit correspondiente se establezca en bajo.
 */
void test_single_led_off(void) {
    const int LED = 3;

    // Enciende un LED específico antes de apagarlo
    leds_turn_on_single(LED);

    // Apaga un LED específico y verifica que el bit correspondiente se establezca en bajo
    TEST_ASSERT_EQUAL_INT(LED_SUCCESS, leds_turn_off_single(LED));
    TEST_ASSERT_EQUAL_UINT16(LED_OFF, leds_port);
}

/**
 * @brief Verifica el comportamiento al prender y apagar múltiples LEDs.
 */
void test_multiple_leds_on_and_off(void) {
    const int LED1 = 1;
    const int LED3 = 3;
    const int LED5 = 5;

    // Enciende los LEDs 1, 3 y 5
    TEST_ASSERT_EQUAL_INT(LED_SUCCESS, leds_turn_on_single(LED1));
    TEST_ASSERT_EQUAL_INT(LED_SUCCESS, leds_turn_on_single(LED3));
    TEST_ASSERT_EQUAL_INT(LED_SUCCESS, leds_turn_on_single(LED5));

    // Apaga los LEDs 1 y 5
    TEST_ASSERT_EQUAL_INT(LED_SUCCESS, leds_turn_off_single(LED1));
    TEST_ASSERT_EQUAL_INT(LED_SUCCESS, leds_turn_off_single(LED5));

    // Verifica que solo el LED 3 esté encendido después de apagar los LEDs 1 y 5
    TEST_ASSERT_EQUAL_UINT16((1 << (LED3 - 1)), leds_port);
}

/**
 * @brief Verifica que al consultar el estado de un LED individual, el valor retornado sea correcto.
 */
void test_single_led_get_status_on(void) {
    const int LED3 = 3;

    TEST_ASSERT_EQUAL_INT(LED_SUCCESS, leds_turn_on_single(LED3));
    TEST_ASSERT_EQUAL_INT(1, leds_get_status_single(LED3));
}

/**
 * @brief Verifica que al prender todos los LEDs, el estado del puerto sea correcto.
 */
void test_all_leds_turn_on(void) {

    // Enciende todos los LEDs y verifica que todos estén encendidos
    TEST_ASSERT_EQUAL_INT(LED_SUCCESS, leds_turn_on_all());
    TEST_ASSERT_EQUAL_UINT16(LED_ON, leds_get_status_all());
}

/**
 * @brief Verifica que al apagar todos los LEDs, el estado del puerto sea correcto.
 */
void test_all_leds_turn_off(void) {

    // Enciende todos los LEDs antes de apagarlos
    TEST_ASSERT_EQUAL_INT(LED_SUCCESS, leds_turn_on_all());

    // Apaga todos los LEDs y verifica que todos estén apagados
    TEST_ASSERT_EQUAL_INT(LED_SUCCESS, leds_turn_off_all());
    TEST_ASSERT_EQUAL_UINT16(LED_OFF, leds_port);
}

/**
 * @brief Verifica el comportamiento al desinicializar el puerto de los LEDs.
 */
void test_uninitialized_led_port(void) {
    leds_deinit();
    TEST_ASSERT_EQUAL_INT(LED_ERROR_NULL_PORT, leds_turn_on_all());
    TEST_ASSERT_EQUAL_UINT8(LED_OFF, leds_port);
}

/**
 * @brief Verifica el comportamiento al consultar el estado de un LED individual con el puerto
 * desinicializado.
 */
void test_uninitialized_led_port_get_single_value(void) {
    const int LED3 = 3;

    // Desinicializa el puerto de LEDs y verifica que no se pueda consultar el estado de un LED
    leds_deinit();
    TEST_ASSERT_EQUAL_INT(LED_ERROR_INVALID_PARAMS, leds_get_status_single(LED3));
}

/**
 * @brief Verificar valores límite:
 *        Verifica que el primer LED (número de LED 1) se encienda correctamente.
 *        Verifica que el último LED (número de LED 16) se encienda correctamente.
 */
void test_check_boundary_values(void) {

    const int LED1 = 1;
    const int LED16 = 16;

    TEST_ASSERT_EQUAL_INT(LED_SUCCESS, leds_turn_on_single(LED1)); // Enciende el primer LED
    TEST_ASSERT_BIT_HIGH(LED1 - 1, leds_port); // Verifica que el primer LED esté encendido
    TEST_ASSERT_EQUAL_INT(LED_SUCCESS, leds_turn_on_single(LED16)); // Enciende el último LED
    TEST_ASSERT_BIT_HIGH(LED16 - 1, leds_port); // Verifica que el último LED esté encendido
}

/**
 * @brief Verificar valores prohibidos al encender:
 *        Verifica que intentar encender un LED con un número mayor que 16 o menor que 1 no afecte
 * al estado del LED.
 */
void test_check_forbidden_values_turn_on(void) {

    const int LED1 = 1;
    const int LED16 = 16;

    TEST_ASSERT_EQUAL_INT(LED_ERROR_INVALID_PARAMS,
                          leds_turn_on_single(LED1 - 1)); // Intenta encender un LED menor que 1
    TEST_ASSERT_EQUAL_INT(LED_ERROR_INVALID_PARAMS,
                          leds_turn_on_single(LED16 + 1)); // Intenta encender un LED mayor que 16
    TEST_ASSERT_EQUAL_UINT16(LED_OFF, leds_port); // Verifica que todos los LEDs estén apagados
}

/**
 * @brief Verifica valores prohibidos al apagar:
 *        Verifica que intentar apagar un LED con un número mayor que 16 o menor que 1 no afecte al
 * estado del LED.
 */
void test_check_forbidden_values_turn_off(void) {
    const int LED1 = 1;
    const int LED16 = 16;

    leds_turn_on_all(); // Enciende todos los LEDs antes de la prueba

    TEST_ASSERT_EQUAL_INT(LED_ERROR_INVALID_PARAMS,
                          leds_turn_off_single(LED1 - 1)); // Intenta apagar un LED menor que 1
    TEST_ASSERT_EQUAL_INT(LED_ERROR_INVALID_PARAMS,
                          leds_turn_off_single(LED16 + 1)); // Intenta apagar un LED mayor que 16
    TEST_ASSERT_EQUAL_UINT16(LED_ON, leds_port); // Verifica que todos los LEDs estén encendidos
}

/* === End of documentation ==================================================================== */

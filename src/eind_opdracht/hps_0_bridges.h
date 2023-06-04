#ifndef _ALTERA_HPS_0_BRIDGES_H_
#define _ALTERA_HPS_0_BRIDGES_H_

/*
 * This file was automatically generated by the swinfo2header utility.
 * 
 * Created from SOPC Builder system 'eind_opdracht_design' in
 * file './eind_opdracht_design.sopcinfo'.
 */

/*
 * This file contains macros for module 'hps_0_bridges' and devices
 * connected to the following masters:
 *   axi_f2h
 *   h2f_lw
 * 
 * Do not include this header file and another header file created for a
 * different module or master group at the same time.
 * Doing so may result in duplicate macro names.
 * Instead, use the system header file which has macros with unique names.
 */

/*
 * Macros for device 'pio_leds', class 'altera_avalon_pio'
 * The macros are prefixed with 'PIO_LEDS_'.
 * The prefix is the slave descriptor.
 */
#define PIO_LEDS_COMPONENT_TYPE altera_avalon_pio
#define PIO_LEDS_COMPONENT_NAME pio_leds
#define PIO_LEDS_BASE 0x0
#define PIO_LEDS_SPAN 16
#define PIO_LEDS_END 0xf
#define PIO_LEDS_BIT_CLEARING_EDGE_REGISTER 0
#define PIO_LEDS_BIT_MODIFYING_OUTPUT_REGISTER 0
#define PIO_LEDS_CAPTURE 0
#define PIO_LEDS_DATA_WIDTH 8
#define PIO_LEDS_DO_TEST_BENCH_WIRING 0
#define PIO_LEDS_DRIVEN_SIM_VALUE 0
#define PIO_LEDS_EDGE_TYPE NONE
#define PIO_LEDS_FREQ 50000000
#define PIO_LEDS_HAS_IN 0
#define PIO_LEDS_HAS_OUT 1
#define PIO_LEDS_HAS_TRI 0
#define PIO_LEDS_IRQ_TYPE NONE
#define PIO_LEDS_RESET_VALUE 0

/*
 * Macros for device 'pio_hex', class 'altera_avalon_pio'
 * The macros are prefixed with 'PIO_HEX_'.
 * The prefix is the slave descriptor.
 */
#define PIO_HEX_COMPONENT_TYPE altera_avalon_pio
#define PIO_HEX_COMPONENT_NAME pio_hex
#define PIO_HEX_BASE 0x10
#define PIO_HEX_SPAN 16
#define PIO_HEX_END 0x1f
#define PIO_HEX_BIT_CLEARING_EDGE_REGISTER 0
#define PIO_HEX_BIT_MODIFYING_OUTPUT_REGISTER 0
#define PIO_HEX_CAPTURE 0
#define PIO_HEX_DATA_WIDTH 32
#define PIO_HEX_DO_TEST_BENCH_WIRING 0
#define PIO_HEX_DRIVEN_SIM_VALUE 0
#define PIO_HEX_EDGE_TYPE NONE
#define PIO_HEX_FREQ 50000000
#define PIO_HEX_HAS_IN 0
#define PIO_HEX_HAS_OUT 1
#define PIO_HEX_HAS_TRI 0
#define PIO_HEX_IRQ_TYPE NONE
#define PIO_HEX_RESET_VALUE 0

/*
 * Macros for device 'pio_switches', class 'altera_avalon_pio'
 * The macros are prefixed with 'PIO_SWITCHES_'.
 * The prefix is the slave descriptor.
 */
#define PIO_SWITCHES_COMPONENT_TYPE altera_avalon_pio
#define PIO_SWITCHES_COMPONENT_NAME pio_switches
#define PIO_SWITCHES_BASE 0x20
#define PIO_SWITCHES_SPAN 16
#define PIO_SWITCHES_END 0x2f
#define PIO_SWITCHES_BIT_CLEARING_EDGE_REGISTER 1
#define PIO_SWITCHES_BIT_MODIFYING_OUTPUT_REGISTER 0
#define PIO_SWITCHES_CAPTURE 1
#define PIO_SWITCHES_DATA_WIDTH 4
#define PIO_SWITCHES_DO_TEST_BENCH_WIRING 0
#define PIO_SWITCHES_DRIVEN_SIM_VALUE 0
#define PIO_SWITCHES_EDGE_TYPE RISING
#define PIO_SWITCHES_FREQ 50000000
#define PIO_SWITCHES_HAS_IN 1
#define PIO_SWITCHES_HAS_OUT 0
#define PIO_SWITCHES_HAS_TRI 0
#define PIO_SWITCHES_IRQ_TYPE EDGE
#define PIO_SWITCHES_RESET_VALUE 0

/*
 * Macros for device 'pio_keys', class 'altera_avalon_pio'
 * The macros are prefixed with 'PIO_KEYS_'.
 * The prefix is the slave descriptor.
 */
#define PIO_KEYS_COMPONENT_TYPE altera_avalon_pio
#define PIO_KEYS_COMPONENT_NAME pio_keys
#define PIO_KEYS_BASE 0x30
#define PIO_KEYS_SPAN 16
#define PIO_KEYS_END 0x3f
#define PIO_KEYS_BIT_CLEARING_EDGE_REGISTER 1
#define PIO_KEYS_BIT_MODIFYING_OUTPUT_REGISTER 0
#define PIO_KEYS_CAPTURE 1
#define PIO_KEYS_DATA_WIDTH 4
#define PIO_KEYS_DO_TEST_BENCH_WIRING 0
#define PIO_KEYS_DRIVEN_SIM_VALUE 0
#define PIO_KEYS_EDGE_TYPE RISING
#define PIO_KEYS_FREQ 50000000
#define PIO_KEYS_HAS_IN 1
#define PIO_KEYS_HAS_OUT 0
#define PIO_KEYS_HAS_TRI 0
#define PIO_KEYS_IRQ_TYPE EDGE
#define PIO_KEYS_RESET_VALUE 0


#endif /* _ALTERA_HPS_0_BRIDGES_H_ */

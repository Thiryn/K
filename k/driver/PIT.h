#ifndef PIT_H_
# define PIT_H_

#define PIT_INTERNAL_FREQ 1193182 /* see https://k.lse.epita.fr/internals/8259a_controller.html */
#define DESIRED_FREQ 1000 /* Hz */

#define PIT_CR0 0x40 /* PIT Counter Register 0 - Frequency interrupt */
#define PIT_CR1 0x41 /* PIT Counter Register 1 - unused */
#define PIT_CR2 0x42 /* PIT Counter Register 2 - Linked with PC Speaker*/
#define PIT_CMD 0x43 /* PIT Control Register, used for configuration */

/*
 * PIT configuration :
 * see https://k.lse.epita.fr/internals/8254_controller.html for full documentation
 * - Binary Counter
 * - Mode 2
 * - All Register RW
 * - Setting up Counter 0
 */
#define PIT_CONF 0b00110100

/*
 * Initialize the PIT
 * Send the confguration and set the timer's frequency
 */
void init_pit(void);

#endif /* !PIT_H_ */

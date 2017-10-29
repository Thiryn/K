#ifndef PIC_H_
#define PIC_H_

#define PIC_MASTER_A 0x20 /* PIC Master port A */
#define PIC_MASTER_B 0x21 /* PIC Master port B */
#define PIC_SLAVE_A 0xA0 /* PIC Slave port B */
#define PIC_SLAVE_B 0xA1 /* PIC Master port B */


/*
 * For full Initialization Command Words configuration documentation
 * see https://k.lse.epita.fr/internals/8259a_controller.html
 */

/*
 * ICW1 configuration :
 * - ICW4 Present
 * - Cascade mode (with slave)
 * - Level triggered mode, see https://www.quora.com/What-is-the-difference-between-the-edge-trigger-and-the-level-trigger-in-epoll
 */
#define ICW1 0b00010001
#define ICW2_MASTER 32 /* IRQ start index for master */
#define ICW2_SLAVE 40 /* IRQ start index for slave */
#define ICW3_MASTER 0b00000100 /* The slave is connected to the 3rd pin from the end */
#define ICW3_SLAVE 0b00000010 /* The master is connected to the 2nd pin from the end*/
#define ICW4 0x1 /* No special ICW4 mode */
#define OCW1_MASTER 0b11111001 /* No IRQ on 2 and 3 */
#define OCW1_SLAVE 0b11111111 /* All IRQs  ON */

void init_pic(void);

#endif /* !PIC_H_*/

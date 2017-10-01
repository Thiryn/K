#ifndef PIC_H_
#define PIC_H_

#define PIT_INTERNAL_FREQ 1193182
#define DESIRED_FREQ 1000

#define PIC_MASTER_A 0x20
#define PIC_MASTER_B 0x21
#define PIC_SLAVE_A 0xA0
#define PIC_SLAVE_B 0xA1

#define PIT_CR0 0x40
#define PIT_CR1 0x41
#define PIT_CR2 0x42
#define PIT_CMD 0x43
#define PIT_CONF 0b00110100

#define ICW1 0b00010001
#define ICW2_MASTER 32 
#define ICW2_SLAVE 40
#define ICW3_MASTER 0x4 
#define ICW3_SLAVE 0x2
#define ICW4 0x1
#define OCW1_MASTER 0b11111001
#define OCW1_SLAVE 0b11111111

void init_pit(void);
void init_pic(void);
#endif /* !PIC_H_*/

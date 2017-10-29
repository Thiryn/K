#ifndef SYSCALL_H_
#define SYSCALL_H_

void addkey(u8 scancode);
int getkey(void);
unsigned long gettick(void);

#endif /* !SYSCALL_H_ */

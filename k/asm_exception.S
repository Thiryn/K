.extern exception_callback
.global exception_handler

exception_handler:
     pusha
     call exception_callback
     popa
     iret

global outb

outb:
  mov al, [esp + 8]             ; move the data to be sent into the al register
  mov dx, [esp + 4]             ;move the address of the I/O port into the dx register
  out dx, al                    ;send the data ot the I/O Port
  ret                           ; return the calling function

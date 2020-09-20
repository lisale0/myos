#ifndef INCLUDE_IO_H
#define INCLUDE_IO_H
/*
  outb: send the given data to the given IO port.  Defined in io.s

  @param port The I/O port to send the data to
  @param data the data to send the to the I/O port
 */
void outb(unsigned short port, unsigned char data);

#endif /*INCLUDE IO_H*/

#ifndef UART_H
#define	UART_H

void	UART_init(uint32_t baud_rate);
void	UART_send(byte c);
size_t	UART_available(void);
bool	UART_read(byte *b);
void	UART_wait_response(size_t sz);

#endif	/* UART_H */
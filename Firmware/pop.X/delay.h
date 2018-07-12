#ifndef DELAY_H
#define	DELAY_H

#define PR_MS	(SYSCLOCK / 8000) - 1
#define PR_US	(SYSCLOCK / 800000) - 1

extern uint16_t slp;
void			delay_ms(uint32_t ms);
void			delay_us(uint32_t us);
void			delay_init();
void            delay_async_ms(uint32_t ms);
uint32_t        delay_async_status(void);

#endif	/* DELAY_H */


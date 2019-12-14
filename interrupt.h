/*
 * interrupt.h
 *
 *  Created on: Dec 9, 2019
 *      Author: ahmed
 */

#ifndef INTERRUPT_H_
#define INTERRUPT_H_


#define ISR(vector, ...)            \
    void vector (void) __attribute__ ((signal,used, externally_visible)) __VA_ARGS__; \
    void vector (void)

#define _VECTOR(N) 		__vector_ ## N

#define INT0_vect 		_VECTOR(1)

#define INT1_vect 		_VECTOR(2)

#define INT2_vect 		_VECTOR(3)

#define TIMER2_COMP_vect 	_VECTOR(4)

#define TIMER2_OVF_vect 	_VECTOR(5)

#define TIMER1_CAPT_vect 	_VECTOR(6)

#define TIMER1_COMPA_vect 	_VECTOR(7)

#define TIMER1_COMPB_vect 	_VECTOR(8)

#define TIMER1_OVF_vect 	_VECTOR(9)

#define TIMER0_COMP_vect 	_VECTOR(10)

#define TIMER0_OVF_vect 	_VECTOR(11)

#define SPI_STC_vect		_VECTOR(12)

#define USART_RXC_vect 		_VECTOR(13)

#define USART_UDRE_vect 	_VECTOR(14)

#define SIG_USART_TRANS		_VECTOR(15)

#define ADC_vect 		_VECTOR(16)

#define EE_RDY_vect	 	_VECTOR(17)

#define ANA_COMP_vect	 	_VECTOR(18)

#define TWI_vect	 	_VECTOR(19)

#define SPM_RDY_vect		_VECTOR(20)


# define sei()  __asm__ __volatile__ ("sei" :::"memory")

# define cli()  __asm__ __volatile__ ("cli" :::"memory")


#endif /* INTERRUPT_H_ */

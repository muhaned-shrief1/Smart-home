/*
 * DIO.h
 *
 *  Created on: Oct 10, 2016
 *      Author: ahmed
 */

#ifndef DIO_H_
#define DIO_H_

typedef enum Dio_state{
	LOW,
	HIGH
}Dio_state_t;

#define SET_BIT(Register,Pin)       (Register |=(1<<Pin))
#define CLEAR_BIT(Register,Pin)     (Register &=~(1<<Pin))
#define TOGGLE_BIT(Register,Pin)	(Register ^=(1<<Pin))
#define BIT_SET(Register,Pin)       (Register &(1<<Pin))
#define BIT_CLEARED(Register,Pin)   (!(Register &(1<<Pin)))
#define READ_BIT(_REG,PIN)     ((_REG>>PIN)  & 1)
#define CHECK_BIT(REG , PIN)	(REG>>PIN)& 1

#endif /* DIO_H_ */

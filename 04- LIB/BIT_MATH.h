#ifndef _BIT_MATH_H_
#define _BIT_MATH_H_

#define SET_BIT(reg,bit)    	(reg |= (1 << bit))

#define CLEAR_BIT(reg,bit)   	(reg &=~(1 << bit))
							
#define TOGGLE_BIT(reg,bit)    	(reg ^= (1 << bit))

#define TOGGLE_PORT(reg)    	(reg ^= reg)
							
#define GET_BIT(reg,bit)		((reg >> bit)&0x01)

#define SET_REG(reg)			(reg = 0xFF)

#define CLEAR_REG(reg)			(reg = 0)

#define SET_REG_VAL(reg,val)    (reg = val)

#endif

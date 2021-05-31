#include "STD_TYPES.h"
#include "BIT_MATH.h"
#include "DIO_PRIVATE.h"
#include "DIO_INTERFACE.h"
#include "assert.h"

static void pinCehck(u8 pin){
	//assert(pin < 8 && pin >= 0);
	;
}
static void portCehck(u8 port){
	//assert(port < 5 && port > 0);
	;
}

void DIO_VoidSetPinDirection(u8 PORT,u8 PIN,u8 DIRECTION){
	pinCehck(PIN);
	portCehck(PORT);
	switch(PORT){
	case PORT_A:
		if(DIRECTION == OUTPUT){
			SET_BIT(DDRA,PIN);			}
		else if(DIRECTION == INPUT){
			CLEAR_BIT(DDRA,PIN);		}
		break;

	case PORT_B:
		if(DIRECTION == OUTPUT){
			SET_BIT(DDRB,PIN);}
		else if(DIRECTION == INPUT){
			CLEAR_BIT(DDRB,PIN);		}
		break;

	case PORT_C:

		if(DIRECTION == OUTPUT){
			SET_BIT(DDRC,PIN);}
		else if(DIRECTION == INPUT){
			CLEAR_BIT(DDRC,PIN);		}
		break;

	case PORT_D:
		if(DIRECTION == OUTPUT){
			SET_BIT(DDRD,PIN);}
		else if(DIRECTION == INPUT){
			CLEAR_BIT(DDRD,PIN);		}
		break;
	default:
		break;
	}
}

void DIO_VoidSetPORTDirection(u8 PORT,u8 DIRECTION){
	portCehck(PORT);
	switch(PORT){
	case PORT_A:
		SET_REG_VAL(DDRA,DIRECTION);
		break;

	case PORT_B:
		SET_REG_VAL(DDRB,DIRECTION);
		break;

	case PORT_C:
		SET_REG_VAL(DDRC,DIRECTION);
		break;
	case PORT_D:
		SET_REG_VAL(DDRD,DIRECTION);
		break;
	default:
		break;
	}
}

void DIO_VoidSetPinValue(u8 PORT,u8 PIN,u8 VALUE){
	pinCehck(PIN);
	portCehck(PORT);
	switch(PORT){
		case PORT_A:
			if(VALUE == OUTPUT){
				SET_BIT(PORTA,PIN);}
			else if(VALUE == INPUT){
				CLEAR_BIT(PORTA,PIN);		}
			break;
		case PORT_B:
			if(VALUE == OUTPUT){
				SET_BIT(PORTB,PIN);}
			else if(VALUE == INPUT){
				CLEAR_BIT(PORTB,PIN);		}
			break;
		case PORT_C:
			if(VALUE == OUTPUT){
				SET_BIT(PORTC,PIN);}
			else if(VALUE == INPUT){
				CLEAR_BIT(PORTC,PIN);		}
			break;
		case PORT_D:
			if(VALUE == OUTPUT){
				SET_BIT(PORTD,PIN);}
			else if(VALUE){
				CLEAR_BIT(PORTD,PIN);		}
			break;
		default:
			break;
		}
}

void DIO_VoidSetPortValue(u8 PORT,u8 VALUE){
	portCehck(PORT);
	switch(PORT)
		{
			case PORT_A: SET_REG_VAL(PORTA,VALUE);
						break;
			case PORT_B: SET_REG_VAL(PORTB,VALUE);
						break;
			case PORT_C: SET_REG_VAL(PORTC,VALUE);
						break;
			case PORT_D: SET_REG_VAL(PORTD,VALUE);
						break;
			default:	break;
		}
}

void DIO_VoidTogglePin(u8 PORT,u8 PIN){
	pinCehck(PIN);
	portCehck(PORT);
}

void DIO_VoidTogglePort(u8 PORT){
	portCehck(PORT);
	switch(PORT)
		{
			case PORT_A: TOGGLE_PORT(PORTA);
						break;
			case PORT_B: TOGGLE_PORT(PORTB);
						break;
			case PORT_C: TOGGLE_PORT(PORTC);
						break;
			case PORT_D: TOGGLE_PORT(PORTD);
						break;
			default:	break;
		}

}

u8	DIO_U8GetPinValue(u8 PORT,u8 PIN){
	pinCehck(PIN);
	portCehck(PORT);
	u8 pinvalue;
	switch(PORT)
		{
			case PORT_A: pinvalue = GET_BIT(PINA,PIN);
						break;
			case PORT_B: pinvalue = GET_BIT(PINB,PIN);
						break;
			case PORT_C: pinvalue = GET_BIT(PINC,PIN);
						break;
			case PORT_D: pinvalue = GET_BIT(PIND,PIN);
						break;
			default:	break;
		}
		return pinvalue;
}

u8  DIO_U8GetPortValue(u8 PORT){
	 u8 data;
	 portCehck(PORT);
	 switch(PORT){
			case PORT_A:
					data = PINA;
							break;
				case PORT_B:
					data = PINB;
							break;
				case PORT_C:
					data = PINC;
							break;
				case PORT_D:
					data = PIND;
							break;
				default:	break;
	 }
	return data;
}

void DIO_VoidSetPullUp(u8 PORT, u8 PIN){
	pinCehck(PIN);
	portCehck(PORT);
		switch(PORT){
			case PORT_A:
					SET_BIT(PORTA,PIN);
				break;
			case PORT_B:
					SET_BIT(PORTB,PIN);
				break;
			case PORT_C:
					SET_BIT(PORTC,PIN);
				break;
			case PORT_D:
					SET_BIT(PORTD,PIN);
				break;
			default:
				break;
			}
}

void DIO_VoidFloating(u8 PORT, u8 PIN){
	pinCehck(PIN);
	portCehck(PORT);
		switch(PORT){
			case PORT_A:
				CLEAR_BIT(PORTA,PIN);
				break;
			case PORT_B:
				CLEAR_BIT(PORTB,PIN);
				break;
			case PORT_C:
				CLEAR_BIT(PORTC,PIN);
				break;
			case PORT_D:
				CLEAR_BIT(PORTD,PIN);
				break;
			default:
				break;
			}
}

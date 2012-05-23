#include "Print.h"

void Print::print(const char *s)	//uart_puts
{
    int n;
    for (n = 0; *s; s++, n++) {
        write(*s);
    }
    //return n;
    return;
}

void Print::print(int val, RADIX_FORMAT format)
{
	if(format == BYTE)
	{
		write((char)(val & 0xff));
		return;
	}
	char s[33];
	int i,j;
	i=j=0; // header of strings
	if (val<0)
	{ //minus value
		s[i]='-';
		val=~val+1;
		i++;
		j++;
	}
	switch(format)
	{
	case BIN:
		while (val>0)
		{ // do until zero
			s[i++]=radix_bin[val%format];
			val/=format;
		}
		break;

	case OCT:
		while (val>0)
		{ // do until zero
			s[i++]=radix_oct[val%format];
			val/=format;
		}
		break;

	case DEC:	//RADIX = Decimal
		while (val>0)
		{ // do until zero
			s[i++]=radix_dec[val%format];
			val/=format;
		}
		break;

	case HEX:	//RADIX = Hexadecimal
		while (val>0)
		{ // do until zero
			s[i++]=radix_hex[val%format];
			val/=format;
		}
		break;
	default:
		break;
	}
	s[i--]='\0'; // EOF
	while (j<i)
	{ // reverse strings array
	char t;
	t=s[j]; s[j]=s[i]; s[i]=t;
	j++; i--;
	}
	print(s);

	return ;
}

void Print::write(const char *s, int length)
{
	int n;
	for(n=0;n<length;s++,n++)
	{
		write(*s);
	}
	return;
}

void Print::println(const char *s)
{
	print(s);
	println();
	return;
}


void Print::println(int val, RADIX_FORMAT format)
{
	print(val,format);
	println();
	return;
}

void Print::println(void)
{
	write ('\r');
	write ('\n');
	return;
}

void Print::print(const char c)
{
	write(c);
	return;
}

void Print::println(const char c)
{
	write(c);
	println();
	return;
}




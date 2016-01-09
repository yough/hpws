#include"common.h"
void print(const char *fmt, ...)
{
	int debug=1;
	if(debug==0) return;

	va_list ap;
	const char *p;
	int i, d;
	double f;
	char *s;

	p=fmt;
	va_start(ap, fmt);
	for(i=0; *(p+i); i++)
	{
		if(*(p+i)!='%')
		{
			putchar(*(p+i));
			continue;
		}
		i++;	
		switch(*(p+i))
		{
			i++;
			case 'd':
				d=va_arg(ap, int);
				printf("%d", d);
				break;
			case 'f':
				f=va_arg(ap, double);
				printf("%f", f);
				break;
			case 's':
				s=va_arg(ap, char *); 
				printf("%s", s);
			default:
				break;
		}
	}
	va_end(ap);
}

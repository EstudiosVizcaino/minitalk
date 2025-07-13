#include "ft_printf.h"
#include <stdio.h>

#define	INT_MAX 2147483647
#define INT_MIN -2147483647
#define UINT_MAX 4294967295


int	main(void)
{
	char	*s = ":)";
	int		charcount1;
	int		charcount2;

	charcount1 = ft_printf("%%s: %s Consecutivos %%c: %c%c Consecutivos %%i: %i, %i" 
		"\n%%x: %x | %%X: %X Pointer: %p - UwU-: %u UwU+: %u - %%d: %d", s, 'x', 'D', INT_MIN, -69, 0, 69, NULL, -2342, 2342, -42);
	write(1, "\n\n", 2);
	charcount2 = printf("%%s: %s Consecutivos %%c: %c%c Consecutivos %%i: %i, %i"
		"\n%%x: %x | %%X: %X Pointer: %p - UwU-: %u UwU+: %u - %%d: %d", s, 'x', 'D', INT_MIN, -69, 0, 69, NULL, -2342, 2342, -42);

	printf("\n\nft_printf charcount: %i\nprintf charcount: %i", charcount1, charcount2);
	return (0);
}


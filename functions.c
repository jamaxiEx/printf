#include "main.h"

/************************* PRINT CHAR *************************/

/**
 * print_char - Prints a character
 * @types: List number of arguments
 * @buffer: Array Buffer to handle print
 * @flag:  Calculates the number of active flags
 * @width: Width
 * @precision: Precision specification
 * @bulk: Size specifier
 * Return: Number of characters to printed
 */
int print_char(va_list types, char buffer[],
	int flag, int width, int precision, int bulk)
{
	char c = va_arg(types, int);

	return (handle_write_char(c, buffer, flag, width, precision, bulk));
}
/************************* PRINT A STRING *************************/
/**
 * print_string - Prints string
 * @types: List number of arguments
 * @buffer: Array Buffer to handle print
 * @flags:  Calculates the number of active flags
 * @width: get width.
 * @precision: Precision specification
 * @bulk: Size specifier
 * Return: Number of characters to printed
 */
int print_string(va_list types, char buffer[],
	int flag, int width, int precision, int bulk)
{
	int length = 0, b;
	char *str = va_arg(types, char *);

	UNUSED(buffer);
	UNUSED(flag);
	UNUSED(width);
	UNUSED(precision);
	UNUSED(bulk);
	if (str == NULL)
	{
		str = "(null)";
		if (precision >= 6)
			str = "      ";
	}

	while (str[length] != '\0')
		length++;

	if (precision >= 0 && precision < length)
		length = precision;

	if (width > length)
	{
		if (flag & F_MINUS)
		{
			write(1, &str[0], length);
			for (b = width - length; b > 0; b--)
				write(1, " ", 1);
			return (width);
		}
		else
		{
			for (b = width - length; b > 0; b--)
				write(1, " ", 1);
			write(1, &str[0], length);
			return (width);
		}
	}

	return (write(1, str, length));
}
/************************* PRINT PERCENT SIGN *************************/
/**
 * print_percent - Prints percent sign
 * @types: Lista of arguments and types
 * @buffer: array buffer to handle print
 * @flag:  Calculates the number of active flags
 * @width: get width.
 * @precision: Precision specification
 * @bulk: Size specifier
 * Return: Number of characters to print
 */
int print_percent(va_list types, char buffer[],
	int flag, int width, int precision, int bulk)
{
	UNUSED(types);
	UNUSED(buffer);
	UNUSED(flag);
	UNUSED(width);
	UNUSED(precision);
	UNUSED(bulk);
	return (write(1, "%%", 1));
}

/************************* PRINT INT *************************/
/**
 * print_int - Print integers
 * @types: List of arguments
 * @buffer: Array buffer to handle print
 * @flags:  Calculates active flags
 * @width: get width.
 * @precision: Precision specification
 * @bulk: Size specifier
 * Return: Number of chars printed
 */
int print_int(va_list types, char buffer[],
	int flags, int width, int precision, int bulk)
{
	int b = BUFF_SIZE - 2;
	int is_negative = 0;
	long int n = va_arg(types, long int);
	unsigned long int num;

	n = convert_size_number(n, bulk);

	if (n == 0)
		buffer[b--] = '0';

	buffer[BUFF_SIZE - 1] = '\0';
	num = (unsigned long int)n;

	if (n < 0)
	{
		num = (unsigned long int)((-1) * n);
		is_negative = 1;
	}

	while (num > 0)
	{
		buffer[b--] = (num % 10) + '0';
		num /= 10;
	}

	b++;

	return (write_number(is_negative, b, buffer, flag, width, precision, bulk));
}

/************************* PRINT BINARY *************************/
/**
 * print_binary - Prints an unsigned number
 * @types: List of arguments
 * @buffer: array buffer to handle print
 * @flag:  Calculates  number active flags
 * @width: get width.
 * @precision: Precision specification
 * @bulk: Size specifier
 * Return: Numbers of characters printed.
 */
int print_binary(va_list types, char buffer[],
	int flag, int width, int precision, int bulk)
{
	unsigned int n, m, b, sum;
	unsigned int a[32];
	int count;

	UNUSED(buffer);
	UNUSED(flag);
	UNUSED(width);
	UNUSED(precision);
	UNUSED(bulk);

	n = va_arg(types, unsigned int);
	m = 2147483648; /* (2 ^ 31) */
	a[0] = n / m;
	for (b = 1; b < 32; b++)
	{
		m /= 2;
		a[b] = (n / m) % 2;
	}
	for (b = 0, sum = 0, count = 0; b < 32; b++)
	{
		sum += a[b];
		if (sum || b == 31)
		{
			char z = '0' + a[b];

			write(1, &z, 1);
			count++;
		}
	}
	return (count);
}


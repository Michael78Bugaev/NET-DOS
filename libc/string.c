#include <string.h>
#include <stdint.h>

void	memcpy(uint8_t *src, uint8_t *dest, uint32_t bytes)
{
	uint32_t i;

	i = 0;
	while (i < bytes)
	{
		dest[i] = src[i];
		i++;
	}
}
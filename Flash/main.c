#include "stm32f10x.h"                  // Device header
#include "stm32f10x_flash.h"            // Device:StdPeriph Drivers:Flash
//#define LENGTH_BUFFER 8U
typedef enum {
    FLASH_ERRORS = 0U,
    FLASH_NO_ERROR
} FlashStatus;

#define address_store  0x0800A000
void Flash_unlock(void);
void Flash_erase(volatile uint32_t u32addr);
FlagStatus Flash_Write(volatile uint32_t u32addr,uint16_t u16BufferWrite, uint32_t u32Legth);
FlagStatus Flash_Read(volatile uint32_t u32addr,uint16_t u16BufferRead, uint32_t u32Legth);

int aDataWrite = 11000;

int main(void)
{
//    uint16_t aDataBuffer[LENGTH_BUFFER] = {0};
    
    Flash_erase(address_store);
    if (FLASH_NO_ERROR != Flash_Write(address_store, aDataWrite, 4)) {
			/* error occured */
        while (1);
    }
    
    if(Flash_Read(address_store, aDataWrite,2 ))
		{
			/* error occured */
				while (1);
    }
		Flash_erase(address_store);
		return 0;
}
void Flash_unlock(void)
{
	FLASH->KEYR = 0x45670123;
	FLASH->KEYR = 0xCDEF89AB;
}
void Flash_erase(volatile uint32_t u32addr)
{
//	Check that no Flash memory operation is ongoing by checking the BSY bit in the FLASH_CR register
	while((FLASH->SR&FLASH_SR_BSY) == FLASH_SR_BSY)
	{
//		wait for BST bit
	}
	if ((FLASH->CR&FLASH_CR_LOCK) == FLASH_CR_LOCK)
	{
		Flash_unlock();
	}
	FLASH->CR |= FLASH_CR_PER;
	FLASH->AR |= u32addr;
	FLASH->CR |= FLASH_CR_STRT;
	while((FLASH->SR&FLASH_SR_BSY) == FLASH_SR_BSY)
	{
//		wait for BST bit
	}
	FLASH->CR &= ~FLASH_CR_PER;
	FLASH->CR &= ~FLASH_CR_STRT;
}
FlagStatus Flash_Write(volatile uint32_t u32addr,uint16_t u16BufferWrite, uint32_t u32Legth)
{
	uint32_t u32count = 0U;
	// check input 
	if ((u16BufferWrite == 0x00U) || (u32Legth == 0U) || (u32Legth%2U != 0U))
	{
		return FLASH_ERRORS	;
	}
	//	Check that no Flash memory operation is ongoing by checking the BSY bit in the FLASH_CR register
	while((FLASH->SR&FLASH_SR_BSY) == FLASH_SR_BSY)
	{
//		wait for BST bit
	}
	// check unlock sequence
	if ((FLASH->CR&FLASH_CR_LOCK) == FLASH_CR_LOCK)
	{
		Flash_unlock();
	}
	FLASH->CR |= FLASH_CR_PG;
	//Perform half-word write at the desired address
	for (u32count = 0U; u32count < (u32Legth/2);u32count++)
	{
		*(uint16_t *)(u32addr + u32count*2U) = *(uint16_t *)(u16BufferWrite + u32count*2U);
	}
	//	Check that no Flash memory operation is ongoing by checking the BSY bit in the FLASH_CR register
	while((FLASH->SR&FLASH_SR_BSY) == FLASH_SR_BSY)
	{
//		wait for BST bit
	}
	FLASH->CR &= ~FLASH_CR_PG;
	return FLASH_NO_ERROR;
}
FlagStatus Flash_Read(volatile uint32_t u32addr,uint16_t u16BufferRead, uint32_t u32Legth)
{
	uint32_t u32count = 0U;
		// check input 
	if ((u16BufferRead == 0x00U) || (u32Legth == 0U))
	{
		return FLASH_ERRORS;
	}
	// read data buffer
	for (u32count = 0U; u32count < (u32Legth);u32count++)
	{
		*(uint16_t *)(u16BufferRead + u32count) = *(uint16_t *)(u32addr + u32count);
	}
	return FLASH_NO_ERROR;
}

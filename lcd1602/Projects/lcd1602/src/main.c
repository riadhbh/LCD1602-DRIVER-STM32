#include "LCD1602.h"
#include "stm32l1xx.h"
#include "discover_board.h"
#include<stdlib.h>
void main(){
LCD1602_Init();
LCD1602_Clear();
u_c*sentence=strcat("The scrolling ","sentence");
u_c*str1=Number_to_str(-990098.99000001,8);//Number to String
u_c*str2=str_dec_to_base(48801,16);//decimal to Hexa(16)
u_c*str3=str_dec_to_base(-48801,16);//decimal to Hexa(16)
while(1){
LCD1602_ScrollSentence(sentence,1,300);
LCD1602_Blink(4,"Message1",4,"Message2",3,300);
LCD1602_Write_String(0,0,str1);
LCD1602_Write_String(0,1,str2);
LCD1602_Write_String(5,1,str3);
DelayMs(150);
}
}

#ifdef  USE_FULL_ASSERT

/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t* file, uint32_t line)
{ 
  /* User can add his own implementation to report the file name and line number,
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* Infinite loop */
  while (1);
}

#endif

/******************* (C) COPYRIGHT 2011 STMicroelectronics *****END OF FILE****/

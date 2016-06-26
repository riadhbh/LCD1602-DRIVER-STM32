This project contains LCD 16X2 Drivers with some Functions:
LCD1602_ScrollSentence(...) : this function scroll a sentence with maximum length 24 character  in double sens 
							  (top and bottom simultaneously) else the sentence will be scrolled in one direction.
							  
LCD1602_Blink(...) : 	this Function blink 1 or 2 Messages, the frist message in the top (first line) and the second
						message in the bottom (2nd line), the length of any message to blink + display index must be 
						less than 40 otherwise the message will be ignored, because the two messages might overlap.
						
Number_To_Str(...) : 	this function converts any number(float or int ...) to a String, this function is useful for 
						displaying Numbers values, because the lcd display functions must take the String format on input,
						The maximum digits after the '.' is 8 because the Error of miscalculation in STM32 is about 10^-9,
						The user can specify the number of digits after the point in the second parameter of the function.
						
str_dec_to_base(...) :	This Function Converts any number(int, long int) negative or positive to any base, and returns the 
						result into a String.
strcat(...) 		:   This function concatenates two Strings, it might be useful to display chiffers with unity 
						like 64°F or 21°C, By calling strcat(Number_To_Str("64"),"°F"), the display will be easier...
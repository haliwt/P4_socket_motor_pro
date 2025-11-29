#include "bsp.h"

uint8_t k,counter,value;
uint8_t read_key_value;

uint8_t key_scan(void)
{

   if(KEY_VALUE() == 0 && value != 0x81){
       counter=0;
       if(k< 200 ){
         k++;
         if(k>100){
            k=220;
			value = 0x81;
			buzzer_sound();
		    return value; //long key 
		 }
	   }

   }

   if(KEY_VALUE()==1){//bounce key 
      if(value ==0x81){
         value =0;
		 k=0;
	     return 0;
	  }
      counter ++;
	  if(counter < 2) return 0;

      counter = 0;

	  if(k > 20 && k<200){
          k=0;
          value =1;
	      return 1; 
	  }


	}

}


void key_parse_value(uint8_t keyvalue)
{
   switch(keyvalue){

      case 0:
	  	  read_key_value = 0;
      break;

	  case 0x01://key short
          read_key_value = 0x01;
	  break;

	  case 0x81://long key .
           read_key_value = 0x81;
	  break;

	  default:
	  
	  break;

   }

}

uint8_t get_key_value(void)
{
    return read_key_value ;

}





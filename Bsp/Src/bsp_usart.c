#include "bsp.h"

volatile uint8_t rx_step_counter;

void usart1_callback_isr(uint8_t rx_data)
{
 //  printf("rx_data = %d \r\n",rx_data);
   if(gpro_t.gpower_flag == power_on){
  

   if(gpro_t.rx_index < 48 &&  hlw8032_rx_tc_flag==0){
        
		hlw8032_rxbuf[gpro_t.rx_index++]= rx_data;

        
	   

    }
    else if(gpro_t.rx_index >47 && hlw8032_rx_tc_flag==0){

	   hlw8032_rx_tc_flag=1;

	}
   }
}

//   }
 
//   if(rx_data==0x55 &&  rx_step_counter==0){
   
//		hlw8032_rxbuf[0]= 0x55;
//		 gpro_t.rx_index=1;
//		 rx_step_counter=1;
//    }
//	else if(rx_step_counter==1){

//	   if(rx_data==0xAA){
//	   hlw8032_rxbuf[gpro_t.rx_index]= rx_data;
//	   rx_step_counter=2;
//	    gpro_t.rx_index++;
	 
//	   }
//	   else{
//	   gpro_t.rx_index=0;
//	   rx_step_counter=0;

//	   }

//	}
//	else if(rx_step_counter==2 && hlw8032_rx_tc_flag==0){
	
//	       hlw8032_rxbuf[gpro_t.rx_index]= rx_data;
//           gpro_t.rx_index++;
//		 if(gpro_t.rx_index >=24){
//			rx_step_counter=0;
//			hlw8032_rx_tc_flag=1;
//		 }

//	}
	
//}
  #if 0
   switch(rx_step_counter){

	case 0:
			
		    gpro_t.rx_index=0;
           
            if(rx_data==0x55){
				hlw8032_rxbuf[gpro_t.rx_index]= 0x55;
				gpro_t.rx_index++;
				rx_step_counter=1;
            }
			else{
			  rx_step_counter=0;


			}

		   

		break;

		case 1:
			
		  
		  if(rx_data == 0xAA){
		  	hlw8032_rxbuf[gpro_t.rx_index]=rx_data;
		  	gpro_t.rx_index++;
		  	rx_step_counter=2;

		  }
		  else{ 

		    rx_step_counter=0;
		  	gpro_t.rx_index=0;

		  	}
		  

		break;

		case 2:
            
		     hlw8032_rxbuf[gpro_t.rx_index] = rx_data;	  // 存入缓冲区
		     gpro_t.rx_index++;
			 if(gpro_t.rx_index >= HLW8032_FRAME_SIZE) {
				   gpro_t.rx_index = 0; // 循环缓冲
				   hlw8032_rx_tc_flag=1;
			       	rx_step_counter=0;
			   }

		break;
        }
   #endif 


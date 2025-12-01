#include "bsp.h"




typedef struct process_run_t{

 uint8_t pro_read_key;
 uint8_t power_onoff_flag;
 uint8_t motor_dir_flag;
 uint8_t motor_dir_init_falg;
 uint8_t motor_step_flag ;

}process_main_t;

process_main_t glpro_t;




/*
	*@brief: 
	*@note:
	*@param:
	*@return:
*/

void main_process_handler(void)
{

 

  if(gpro_t.gpower_flag == power_on){



    glpro_t.motor_step_flag = motor_run_state_ref();

    switch(glpro_t.motor_step_flag){

       case 0:

	    motor_stop();

	   break;

	   case motor_run_is_up:
	        motor_run_up();

	   break;

	   case motor_run_is_down:
	   	    motor_run_down();

	   break;

	   case motor_run_is_pause:
	   	    motor_pause();

	   break;
	   
	    default:

	   break;


	}


	  works_disp_hanlder();




  


  } 
  else{ //power off 
   
    smg_power_off_ref();
	motor_pause();
	TM1639_donotDisplay();
	LED_KEY_OFF() ;
   
  

  }

}
/*
	*@brief: 
	*@note:
	*@param:
	*@return:
*/



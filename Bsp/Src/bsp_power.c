#include "bsp.h"




typedef struct process_run_t{

 uint8_t pro_read_key;
 uint8_t power_onoff_flag;
 uint8_t motor_dir_flag;
 uint8_t motor_dir_init_falg;
 uint8_t motor_step_flag ;
 uint8_t main_run_step;

}process_main_t;

process_main_t glpro_t;


static void mainboard_control_handler(void);

static void motor_main_run_process_handler(void);

/*
	*@brief: 
	*@note:
	*@param:
	*@return:
*/

void main_process_handler(void)
{

 if(gpro_t.gpower_flag == power_on){


 
     mainboard_control_handler();

	 motor_main_run_process_handler();

      works_disp_hanlder();

	 hlw8032_run_process_handler();
	


  } 
  else{ //power off 
    glpro_t.main_run_step=0;
    RELAY_CTL_OFF();
    smg_power_off_ref();
	motor_pause();
	TM1639_donotDisplay();
	LED_KEY_OFF() ;
	USB_POWER_DISABLE();
   
  

  }

}
/*
	*@brief: 
	*@note:
	*@param:
	*@return:
*/
static void motor_main_run_process_handler(void)
{

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


}

/*
	*@brief: 
	*@note:
	*@param:
	*@return:
*/
static void mainboard_control_handler(void)
{
     switch(glpro_t.main_run_step){


	 case 0:
         RELAY_CTL_ON();
	     glpro_t.main_run_step = 1;
	 break;

	 case 1:

	 break;



    }


}



#include "bsp.h"




typedef struct process_run_t{

 uint8_t pro_read_key;
 uint8_t power_onoff_flag;
 uint8_t motor_dir_flag;
 uint8_t motor_dir_init_falg;
 

}process_main_t;

process_main_t glpro_t;

static void works_motor_run_handler(void);


/*
	*@brief: 
	*@note:
	*@param:
	*@return:
*/

void main_process_handler(void)
{

   static uint8_t motor_up_n,motor_down_n;
   glpro_t.pro_read_key = get_key_value();

   switch(glpro_t.pro_read_key){


    case 0x01: //short key 
       if(glpro_t.power_onoff_flag == power_on){

            if(MOTOR_POS_UP_VALUE()==0 || WIRELESS_CHARGING_VALUE() == 0 || MOTOR_PINCH_VALUE()==0){
			    glpro_t.motor_dir_flag = charging_state;

			}
			else{
				if(glpro_t.motor_dir_init_falg ==0){
					glpro_t.motor_dir_init_falg ++;
	                glpro_t.motor_dir_flag = motor_id_up;
		        }
				else if(glpro_t.motor_dir_flag == motor_id_up){

				    glpro_t.motor_dir_flag = motor_id_stop;
			    }
				else if(glpro_t.motor_dir_flag == motor_id_down){
				
				      glpro_t.motor_dir_flag = motor_id_stop;
					
                }
				else if(glpro_t.motor_dir_flag == motor_id_stop){
                      
                     if(glpro_t.motor_dir_flag == motor_id_up){

					      glpro_t.motor_dir_flag = motor_id_down;

					 }
					 else{

					      glpro_t.motor_dir_flag = motor_id_up;

					 }

				}
			}
            
	   }
    break;


	case 0x81: //long key 
	    if(glpro_t.power_onoff_flag == power_off){
           glpro_t.power_onoff_flag = power_on;
		   LED_KEY_ON() ;
		   TM1639_Init();
		   
		   
	    }
		else{
		    glpro_t.power_onoff_flag = power_off;
			motor_stop();
			TM1639_donotDisplay();
		    LED_KEY_OFF() ;
		

		}
	break;

	default:

	break;



   }
   
   if(glpro_t.power_onoff_flag == power_on){
      works_motor_run_handler();
	  works_disp_hanlder();

   }

}
/*
	*@brief: 
	*@note:
	*@param:
	*@return:
*/
static void works_motor_run_handler(void)
{
    //handler motor 
    switch(glpro_t.motor_dir_flag){

      case motor_id_up:
         if(MOTOR_POS_UP_VALUE()==0 || WIRELESS_CHARGING_VALUE() == 0 || MOTOR_PINCH_VALUE()==0){
		     motor_stop();
			 glpro_t.motor_dir_flag= motor_id_stop;

		 }
		 else
	       motor_run_up();

	  break;

	  case motor_id_down:
		if(MOTOR_POS_DOWN_VALUE()==0 || WIRELESS_CHARGING_VALUE() == 0 || MOTOR_PINCH_VALUE()==0){
			motor_stop();
			glpro_t.motor_dir_flag= motor_id_stop;
		 
		}
		else
	       motor_run_down();

	  break;

	  case motor_id_stop:
           motor_stop();
	  break;

	  case charging_state:
            motor_stop();
	  break;


	  	

	}
	//hanlder disply power meter
	

}


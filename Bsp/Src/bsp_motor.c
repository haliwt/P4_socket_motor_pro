#include "bsp.h"


typedef struct{

  uint8_t motor_run_flag;
  uint8_t motor_pos_flag;
  uint8_t motor_direction;

}motor_run_state_t;

motor_run_state_t glmotor_t;

/**
 * @brief  :  
 * @note   :  
 * @param   None
 * @retval  None
 */
void motor_run_up(void)
{
   if(WIRELESS_CHARGING_VALUE() ==0 || MOTOR_PINCH_VALUE()==0 || MOTOR_POS_UP_VALUE()==0){
      motor_pause();

   }
   else{
	   MOTOR_RUN_UP_SetHigh();
	   MOTOR_RUN_DOWN_SetLow();
   }

}
/**
 * @brief  :  
 * @note   :  
 * @param   None
 * @retval  None
 */
void motor_run_down(void)
{
   if(WIRELESS_CHARGING_VALUE() ==0 || MOTOR_PINCH_VALUE()==0 || MOTOR_POS_DOWN_VALUE()==0){
      motor_pause();

   }
   else{
	MOTOR_RUN_DOWN_SetHigh();
	MOTOR_RUN_UP_SetLow();
   }

}
/**
 * @brief  :  
 * @note   :  
 * @param   None
 * @retval  None
 */
void motor_stop(void)
{
   MOTOR_RUN_UP_SetLow();
   MOTOR_RUN_DOWN_SetLow();

}

/**
 * @brief  :  
 * @note   :  
 * @param   None
 * @retval  None
 */
void motor_run_state(void)
{
   static uint8_t motor_init;

   if(motor_init==0){
       motor_init++;
	   glmotor_t.motor_direction = motor_run_is_up;
       glmotor_t.motor_run_flag = motor_run_is_up;
	   motor_run_up();
   }
   else{

      if(glmotor_t.motor_direction == motor_run_is_up){

	     glmotor_t.motor_direction = motor_run_is_down;
         glmotor_t.motor_run_flag = motor_run_is_down;
	     motor_run_down();
	  }
	  else if(glmotor_t.motor_direction == motor_run_is_pause){

         if(glmotor_t.motor_direction == motor_run_is_up){
			glmotor_t.motor_direction = motor_run_is_down;
            glmotor_t.motor_run_flag = motor_run_is_down;   
		    motor_run_down();
		 }
		 else{
		    glmotor_t.motor_direction = motor_run_is_up;
		    glmotor_t.motor_run_flag = motor_run_is_up;
		   motor_run_up();
         }

	  }
	  else if(glmotor_t.motor_direction == motor_run_is_down){

	     glmotor_t.motor_direction = motor_run_is_up;
         glmotor_t.motor_run_flag = motor_run_is_up; 
	    
	     motor_run_up();
	  }

   }
}
/**
 * @brief  :  
 * @note   :  
 * @param   None
 * @retval  None
 */
void motor_pause(void)
{

   glmotor_t.motor_direction = motor_run_is_pause;
   
    motor_stop();
}
/**
 * @brief  :  
 * @note   :  
 * @param   None
 * @retval  None
 */
uint8_t motor_run_state_ref(void)
{
   
    return glmotor_t.motor_run_flag;
   
   

}
/**
 * @brief  :  
 * @note   :  
 * @param   None
 * @retval  None
 */
void motor_detect_pinch(void)
{
  if(WIRELESS_CHARGING_VALUE() ==0 || MOTOR_PINCH_VALUE()==0 || MOTOR_POS_DOWN_VALUE()==0){
		 motor_pause();
	
	}

}


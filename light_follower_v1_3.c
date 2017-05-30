 /* LIGHT FOLLOWING
 BRIAN DAY
 JOHN KAHLA
 2/15
 */
 
 
//prototypes 
int constrain_velocity ( int vel) ;
void goto_light(int l_vel, int r_vel, int forward_speed);
void obstacle_avoid();
//int move_bumper( int l_vel, int r_vel, int duration );
 
int main() 
{
    //left motor 1  full power turns right
    //right motor 0 full power turns left
    
    int l_vel = 600 ;
	int r_vel = 600 ;
    int forward_speed = 600;
    int stop = 1; 
    while(1) 
    {
		//r_vel = 400;
		//l_vel = 400;
		//mav(0, r_vel);
		//mav(1, l_vel);
		obstacle_avoid(l_vel, r_vel, forward_speed);
        goto_light(l_vel, r_vel, forward_speed);
    }
}
 
int constrain_velocity ( int vel)
{
    vel = vel > 1000 ? 1000 : ( vel < -1000 ? -1000 : vel) ; //if > 1000 constrain to to 1000, less then -1000 constrain to -1000
    return vel;
}

void obstacle_avoid(l_vel, r_vel, forward_speed)
{
	int right_bumper_pressed = 0 ;
	int left_bumper_pressed = 0 ;
	
	while (digital(8) || digital(9))
	{
		//check to see if sensor has been triggered 
		if(digital(8))
		{	
			right_bumper_pressed = 1 ;
		}
		if(digital(9))
		{
			left_bumper_pressed = 1 ;
		}
		
		mav(0, l_vel * -1); //reverse
		mav(1, r_vel * -1);
		msleep(1200) ;
		
		if( right_bumper_pressed )//object to right of robot
		{
			mav(0, l_vel * -1);//turn left
			mav(1, r_vel * 1);
			msleep(1100);
			if(digital(8) || digital(9))
			{ break;}
			mav(0, l_vel * 1); //forward 2x the amount it backsup
			mav(1, r_vel * 1);
			msleep(2000);
			if(digital(8) || digital(9))
			{ break;}
			mav(0, l_vel * 1);//turn right
			mav(1, r_vel * -1);
			msleep(1000);
			//move_bumper( l_vel*-1, r_vel, 100 );//turn left
			//move_bumper( l_vel, r_vel, 100 );//go straight
			//move_bumper( l_vel, r_vel*-1, 100 );//turn right
			
			right_bumper_pressed = 0;
		}
		
		if( left_bumper_pressed )
		{
			mav(0, l_vel * 1);//turn right
			mav(1, r_vel * -1);
			msleep(1100);
			if(digital(8) || digital(9))
			{ break;}
			mav(0, l_vel * 1); //forward 2x the amount it backsup
			mav(1, r_vel * 1);
			msleep(2000);
			if(digital(8) || digital(9))
			{ break;}
			mav(0, l_vel * -1);//turn left
			mav(1, r_vel * 1);
			msleep(1000);
			left_bumper_pressed = 0;
		}
		
		//move right or left?
		
		
	}
}

void goto_light (l_vel, r_vel, forward_speed )
{
	int dark_cutoff = 500 ;
    int sensor_threshold = 5 ;
	int light_sensor_dif =  0 ;  //find the difference between 2 sensors
	
	if( analog10(0) >= dark_cutoff && analog10(1) >= dark_cutoff )
        {
            l_vel = forward_speed ;
            r_vel = forward_speed * -1 ;
            mav(0, l_vel) ;
            mav(1, r_vel) ;
        }
        //if the difference between the sensor is greater then threshold turn towards lower of the value
        //modulate the velocity so the larger the diference then the quicker the turn
        else
        {
			//light following
			light_sensor_dif = analog10(0) - analog10(1) ; //analog10() range 0-1023
			
			//start going straight
			r_vel = forward_speed ;
			
            
			//move left, right motor > left motor
			if( light_sensor_dif > sensor_threshold ) //positive difference
			{
				if(light_sensor_dif > 40 && analog10(1) < 100 )
			   {
					printf("turn left hard %d\n", light_sensor_dif);
					mav(0, r_vel) ;
					mav(1, l_vel - (light_sensor_dif * 20) );
				}
				else
				{
					printf("turn left %d\n", light_sensor_dif);
					mav(0, r_vel) ;
					mav(1, l_vel - (light_sensor_dif * 8) );
				}
			}
		 
			//turn right, left motor > right motor
			if( light_sensor_dif < (0 - sensor_threshold) )//negative difference
			{
				if(light_sensor_dif < -40 && analog10(0) < 100)
			   {
				   printf("turn right hard %d\n", light_sensor_dif);
					mav(0, r_vel + (light_sensor_dif * 20) ) ;
					mav(1, l_vel);
				}
				else
				{
					printf("turn right %d\n", light_sensor_dif);
					mav(0, r_vel - (light_sensor_dif * 8) ) ;
					mav(1, l_vel);
				}
			}
            else //in threshold
            {
				printf("straight %d\n", light_sensor_dif);
                mav(0, constrain_velocity( forward_speed * 2 )) ;
                mav(1, constrain_velocity( forward_speed * 2 ) ) ;
            }
        }       
}
    
/*int move_bumper(l_vel, r_vel, duration)
{
	int backup = 0;
	int t = 0;
	int exit_bump = 1;
	for( t; t < duration ; t++)
	{
		if(digital(8) || digital(9))
		{ exit_bump = 0 ;
			break; 
		}
		mav(0, l_vel);
		mav(1, r_vel);
		
	}
}
*/

 
//prototypes 
int constrain_velocity ( int vel) ;
void rotateLeft();
void rotateRight();
void moveBack();
void moveForward();
int obstacle_avoid( int dir );
 
int main() 
{
    //left motor 1  full power turns right
    //right motor 0 full power turns left
    int light_sensor_dif =  0 ;  //find the difference between 2 sensors
    int l_vel , r_vel = 0 ;
    int dark_cutoff = 500 ;
    int sensor_threshold = 5 ;
	int forward_speed = 500;
     
    while(1) 
    {
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
}
 
int constrain_velocity ( int vel)
{
    vel = vel > 1000 ? 1000 : ( vel < -1000 ? -1000 : vel) ; //if > 1000 constrain to to 1000, less then -1000 constrain to -1000
     
    /*if ( vel > 1000)
    {
        vel = 1000;
    }
    if ( vel < -1000)
    {
        vel = -1000;
    }
    */
    return vel;
}

void goto_light ( )
{
    

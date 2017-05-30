int vel = 600;

int constrain_velocity ( int vel)
{
    vel = vel > 1000 ? 1000 : ( vel < -1000 ? -1000 : vel) ; //if > 1000 constrain to to 1000, less then -1000 constrain to -1000
    return vel;
}

int mod_vel(int dif)
{
	return abs(dif*6);

}

int main() 
{
	int sensor_dif = 0;
	set_each_analog_state(0,0,1,1,0,0,0,0); //disable internal pulldown resistor
	sleep(0.02);
	
	while(1)
	{
		sensor_dif = analog10(3) - analog10(2); //if a neg number then front sensor is farther from wall
		printf("sensor dif %d\n", sensor_dif);
		
		//too far from wall find parallel with wall and  then get closer
		if ( analog10(2) <= 100 ) //rear sensor > 12" from wall
		{
			//make sure front sensor is about same distance from wall
			if ( sensor_dif <=  abs(50)  ) //parallel to wall
			{
				//turn and move toward wall
				printf("turning 90* right\n");
				mav( 0 , vel *-1 ); //right motor
				mav( 1 , vel ) ;// full forward to turn in place right
				sleep ( 1.4 ); //turn long enough to get 90 degrees
				
				//move forward
				printf("straight toward wall\n");
				mav( 0 , vel  ); //right motor
				mav( 1 , vel  ) ;// full forward to turn in place right
				
				sleep ( 2.0 - (analog10(3)/33) ); //modified by estimated distance to wall, needs to be adjusted depending on velocity
				
				//turn back to be about parallel to wall
				printf("turn back parallel to wall\n");
				mav( 0 , vel  ); //right motor
				mav( 1 , vel *-1  ) ;// full forward to turn in place right
				sleep ( 1.5 ); //should be modified by calulated distance to wall
				
				//go straight
				mav( 0 , vel  ) ; 
				mav( 1 , vel  ) ;		
			}
			
			//far from wall but not parallel with it 
			else if (sensor_dif < -50)//turn right if front sensor further away
			{ 
				printf( "far-slight right\n" );
				mav( 0 , constrain_velocity( vel - mod_vel( sensor_dif ) ));
				mav( 1 , constrain_velocity( vel + mod_vel( sensor_dif ) ));
			}
			else if (sensor_dif > 50)//turn left if front sensor is  closer
			{ 
				
				printf( "far-slight left\n" );
				mav( 1 , constrain_velocity( vel - mod_vel( sensor_dif ) * 2 ));
				mav( 0 , constrain_velocity( vel + mod_vel( sensor_dif ) * 4 )) ;
			}
			else
			{
				beep();
			}
		}
		
		else//rear sensor within 12" of wall
		{
			printf("Close to wall, adjust to stay close\n");
			if ( sensor_dif <= -60 ) //wall is curving to right or veering to right too much
			{
				//check to see if the front sensor is starting to get too far from wall
				if(analog10(3) < 512 )  //too far from wall turn harder right
				{
					printf("hard right dif:%d f %d, r %d\n", sensor_dif , analog10(3), analog10(2));
					mav( 0 , constrain_velocity( vel - mod_vel( sensor_dif ) * 5 ));
					mav( 1 , constrain_velocity( vel + mod_vel( sensor_dif ) * 3 ));
				}
				else //modulate speed based on dif between sensors
				{
					mav( 0 , constrain_velocity( vel - mod_vel( sensor_dif ) ));
					mav( 1 , constrain_velocity( vel + mod_vel( sensor_dif ) ));
					printf( "slight right\n" );
				}
			}
		
			else if ( sensor_dif >= 60 ) //wall is curving to left or robot is veering to right too much
			{
				printf( "slight left\n") ;
				mav( 1 , constrain_velocity( vel - mod_vel( sensor_dif )  ));
				mav( 0 , constrain_velocity( vel + mod_vel( sensor_dif )  )) ;
			}
			else 
			{ //shouldnt get here
				printf("should be going straight\n");
				//beep();
				mav( 0, constrain_velocity( vel * 4 )) ;
				mav( 3, constrain_velocity( vel * 4 )) ;
			}
		}
	}
	return 0;
}


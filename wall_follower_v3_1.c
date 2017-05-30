int l_vel = 440;
int r_vel = 600;

int constrain_velocity ( int vel )
{
    vel = vel > 1000 ? 1000 : ( vel < -1000 ? -1000 : vel) ; //if > 1000 constrain to to 1000, less then -1000 constrain to -1000
    return vel;
}

int mod_vel(int dif)
{
	return abs(dif)*6;

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
		
		if( abs(sensor_dif) <= 100 ) //parallel to a wall or greater then 30" from a wall
		{
			if(analog10(2) < 512 )//too far from wall turn right
			{
				printf("too far from wall, searching\n");
				mav( 0 , constrain_velocity (r_vel - mod_vel( sensor_dif ) ) );
				mav( 1 , constrain_velocity (l_vel + mod_vel( sensor_dif ) ) ) ;
			}
			else
			{
				printf( "straight\n" );
				mav( 0 , r_vel ); //right motor
				mav( 1 , l_vel ); //left motor
			}
		}
		
		else if ( sensor_dif < -400 ) //corner of wall 
		{	//hard turn
			
			//sleep(0.2); // mov forward a bit then hard turn
			mav( 0 , r_vel *-1); 
			mav( 1 , l_vel ) ;
		}
		
		else if ( sensor_dif < -50 ) //wall is curving to right or veering to right too much
		{
			if(analog10(3) < 512 )  //too far from wall turn harder right
			{
				printf("too far from wall dif:%d f %d, r %d\n", sensor_dif , analog10(3), analog10(2));
				mav( 0 , constrain_velocity (r_vel - mod_vel( sensor_dif) * 5)  );
				mav( 1 , constrain_velocity (l_vel + mod_vel( sensor_dif) * 4)  ) ;
			}
			
				mav( 0 , constrain_velocity (r_vel - mod_vel( sensor_dif)) * 3 );
				mav( 1 , constrain_velocity (l_vel + mod_vel( sensor_dif)) * 3 ) ;
				printf("turning right\n");
			}
		
		else if ( sensor_dif > 50 ) //wall is curving to left or robot is veering to right too much
		{
			
				mav( 1 , constrain_velocity (r_vel - mod_vel( sensor_dif))  );
				mav( 0 , constrain_velocity (l_vel + mod_vel( sensor_dif))  ) ;
		}
		
	}
	return 0;
}


int vel = 600;

int mod_vel(int dif)
{
	int val = 0;
	val = vel - (abs(dif));
	return val;
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
		
		if( abs(sensor_dif) <= 50 ) //parallel to a wall or greater then 30" from a wall
		{
			mav( 0 , vel ); //right motor
			mav( 1 , vel ); //left motor
		}
		if ( sensor_dif < -400 && analog10(3) > 100) //corner of wall 
		{	//hard turn
			
			//sleep(0.2); // mov forward a bit then hard turn
			mav( 0 , vel *-1); 
			mav( 1 , vel ) ;
		}
		else if ( sensor_dif < -50 ) //wall is curving to right or veering to right too much
		{
			mav( 0 , mod_vel( sensor_dif  ) );
			mav( 1 , vel ) ;
		}
		
		else if ( sensor_dif > 50 ) //wall is curving to left or robot is veering to right too much
		{
			mav( 1 , mod_vel( sensor_dif  ) );
			mav( 0 , vel ) ;
		}
		
	}
	return 0;
}


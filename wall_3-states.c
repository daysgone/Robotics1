//motors
int r_motor = 1 ;
int l_motor = 2 ;
//set default motor speed
int r_vel = 900; 
int l_vel = 500;


int constrain_velocity ( int vel )
{
    vel = vel > 1000 ? 1000 : ( vel < -1000 ? -1000 : vel) ; //if > 1000 constrain to to 1000, less then -1000 constrain to -1000
    return vel;
}

int main() 
{
	int sensor_dif = 0 ;
	int c_msg = 0 ;
	int f_msg = 0 ;
	int s_msg = 0 ;
	
	set_each_analog_state(0,0,1,1,0,0,0,0); //disable internal pulldown resistor
	sleep(0.02);
	
	//start robot moving forward
	mav( r_motor, r_vel );
	mav( l_motor, l_vel );
	
	while(1) //three states too close, too far, good range
	{
		
		//too far from wall, turn toward wall
		if (analog10(2) < 360)
		{ 
			if( !f_msg ){ printf("too far from wall\n"); f_msg = 1; c_msg = 0; s_msg = 0; }
			mav( r_motor, constrain_velocity( r_vel - 250));
			mav( l_motor, constrain_velocity( l_vel + 280 )); //not same as too close to wall since l motor seems faster
		}
		
		//too close to wall, turn away from wall
		else if (analog10(2) > 480)
		{
			if( !c_msg ){ printf("too close from wall\n"); c_msg = 1; f_msg = 0; s_msg = 0; }
			mav( r_motor, constrain_velocity( r_vel + 100 ));
			mav( l_motor, constrain_velocity( l_vel  ));
		}
		
		else //sensor readings between 450-600
		{ 	//move straight
			if( !s_msg ){ printf("straight\n"); c_msg = 0; f_msg = 0; s_msg = 1;}
			mav( 0, r_vel +10 );
			mav( 1, l_vel );
			//msleep( 50 ); //move a bit forward before checking wall distance again to make it go quicker
		}
		
	}
	return 0;
}


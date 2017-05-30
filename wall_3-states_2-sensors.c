#define PI 3.14159265  // cant get pi to work with including math.h
//motors
int r_motor = 1 ;
int l_motor = 2 ;
//set default motor speed
int r_vel = 900; 
int l_vel = 900;


int cons_vel ( int vel )
{
    vel = vel > 1000 ? 1000 : ( vel < -1000 ? -1000 : vel) ; //if > 1000 constrain to to 1000, less then -1000 constrain to -1000
    return vel;
}
int dist_from_wall()
{
	//SOH-CAH-TOA
	//value from sensor is hyp, angle should be 45degree or pi/4
	return ((analog(3) * cos(PI/4))*2 ) ; //adjustment by *2 makes sensor return same value
}
void set_motor_vel ( int vel)
{

	printf("r_motor:%d : l_motor:%d \n" , cons_vel(r_vel-vel) ,cons_vel(l_vel+vel) );
	
		mav( r_motor, cons_vel( r_vel - vel )) ;
		mav( l_motor, cons_vel( l_vel + vel )) ;
	
}

int main() 
{
	int sensor_dif = 0 ;
	
	int forward_vel = 0; //0 means straight, larger neg values harder left turn, larger values harder right turn
	//int reverse = 0;
	
	//used to not spam screen with msgs if state has not changed
	int c_msg = 0 ;
	int f_msg = 0 ;
	int s_msg = 0 ;
	
	set_each_analog_state(0,0,1,1,0,0,0,0); //disable internal pulldown resistor
	sleep(0.02);
	
	//start robot moving forward
	set_motor_vel( forward_vel ); //should go straight
	
	while(1) //three states too close, too far, good range
	{
		set_motor_vel( forward_vel );
		//test sensors
		//printf("front sensor %d \n front sensor to side wall %d \n rear sensor %d  \n" , analog(3) , dist_from_wall(), analog(2) );
		//sleep(5.0);
		
		//if front sensor is greater then 100 must have come to a wall
		if (analog10(3) >=500)
		{
			printf( "possible obstacle. trying to avoid\n");
			forward_vel = -10000; //make sure its a hard turn left
			
		}
		else if ( analog10(3) <=200 )
		{//possible hard turn/curve to right
			forward_vel = forward_vel + 1000; 
		}
		
		if (analog10(2) <= 350)
		{
			printf("too far from wall");
			
			printf(" slight right\n");
			forward_vel = forward_vel + 20;
			
		}
		else if (analog10(2) > 540)
		{
			printf("too close to wall");
			
			printf(" slight left\n");
			forward_vel = forward_vel - 20;
			
		}
		else
		{
			printf("going straight\n");
			if (forward_vel < -100){forward_vel = forward_vel + 20;}//trying to get back to 0
			else if (forward_vel > 100){forward_vel = forward_vel - 20;}
			else{forward_vel = 0 ;}
			
		}
		
	}
	return 0;
}


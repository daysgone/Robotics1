#define PI 3.14159265  // cant get pi to work with including math.h
//motors
int r_motor = 1 ;
int l_motor = 2 ;

//set default motor speed
int r_vel = 800; 
int l_vel = 800;

int forward_vel = 0; //0 means straight, larger neg values harder left turn, larger values harder right turn


int cons_vel ( int vel )
{
    vel = vel > 900 ? 900 : ( vel < -900 ? -900 : vel) ; //if > 900 constrain to to 900, less then -900 constrain to -900
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
	//printf("r_motor:%d : l_motor:%d \n" , cons_vel(r_vel-vel) ,cons_vel(l_vel+vel) );
	mav( r_motor, cons_vel( r_vel - vel )) ;
	mav( l_motor, cons_vel( l_vel + vel )) ;
}

int main() 
{
	int sensor_dif = 0 ; //difference between both sensors, used to see if robot angled toward or away from wall
	int state = 0 ; //what was previous state
	int t = 0 ; //time spent turning, when in ok range area, try and compensate for incoming angle
	
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
		
		//if front sensor is greater then 600 must have come to a wall
		/*if (analog10(3) > 600)
		{
			if ( state !=10) { printf( "possible obstacle. trying to avoid\n"); }
			state = 10;
			forward_vel =  -10000; //make sure its a hard turn left
		}
		
		else if ( analog10(3) < 400 )
		{//possible hard turn/curve to right
			forward_vel = forward_vel + 50; 
		}
		*/
		
		if (analog10(2) <= 440)
		{
			if ( state != 1) { printf("too far from wall: slight right\n"); }
			state = 1;
			forward_vel = forward_vel + 1;
			t++ ; //increment time spent turning
		}
		
		else if (analog10(2) > 540)
		{
			if ( state != -1 ) { printf("too close to wall: slight left\n"); }
			state = -1;
			forward_vel = forward_vel - 1;
			t++ ; //increment time spent turning
		}
		
		else
		{
			if ( state != 0 ) { printf("straight\n"); }
			else if ( state = -1 )//just came from the right
			{
				//lessen incoming angle
				printf( "compensating left" ) ;
				if( forward_vel >= 5) { forward_vel = forward_vel - 5; }
				
			}
			else if ( state = 1 ) //just came from the left
			{
				printf( "compensating right" ) ;
				if( forward_vel <= -5) {forward_vel = forward_vel + 5; }
			}
			t = 0 ; //reset timer
			
			if (forward_vel > 20) { forward_vel = forward_vel - 20; }
			else if (forward_vel < -20) { forward_vel = forward_vel + 20; }
			else { forward_vel = 0;}
		}
		
	}
	return 0;
}


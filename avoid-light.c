 /* LIGHT AVOIDANCE
 BRIAN DAY
 JOHN KAHLA
 2/15
 */
 
 
//prototypes 
int constrain( int val) ;
void avoid_light(int l_vel, int r_vel, int forward_speed);
void rotateLeft();
void rotateRight();


int main() 
{
    //left motor 1  full power turns right
    //right motor 0 full power turns left
    
    int l_vel = 450 ;
	int r_vel = 450 ;
    int forward_speed = 800;
    int stop = 1; 
    while(1) 
    {
		avoid_light(l_vel, r_vel, forward_speed);
    }
}
 
int constrain_velocity ( int vel)
{
    vel = vel > 1000 ? 1000 : ( vel < -1000 ? -1000 : vel) ; //if > 1000 constrain to to 1000, less then -1000 constrain to -1000
    return vel;
}

void avoid_light (l_vel, r_vel, forward_speed )
{
	int light_cutoff = 200 ;
    int sensor_threshold = 5 ;
	int light_direct = 75                                ;
	int light_sensor_dif =  0 ;  //find the difference between 2 sensors
	
	if( analog10(0) > light_cutoff && analog10(1) > light_cutoff )
        {
            l_vel = forward_speed ;//move forward
            r_vel = forward_speed ;
            mav(0, l_vel) ;
            mav(1, r_vel) ;
        }
      else if(analog10(0) < light_direct && analog10(1) < light_direct)
	  {
		 if(analog10(0) > analog10(1))
			 run_for(1, rotateRight);
		 else
			 run_for(1, rotateLeft);
	  } 
	else
        {
			printf(	"Right Sensor: %d \n", analog10(0) );
			mav(0, constrain(analog10(0))* 1.5 ); //motor 0 turns faster the higher the value obtained from the right sensor
			printf(	"\tLeft Sensor: %d ", analog10(1) );
			mav(1, constrain(analog10(1))* 1.5); 
		}
}

int constrain ( int val)
{
    return val < 30 ? 0 : val ; //if > 1000 constrain to 0, else keep same passed in value
}
      
void rotateLeft()
{
	fd(0);
	bk(1);
}

void rotateRight()
{
	fd(1);
	bk(0);
}

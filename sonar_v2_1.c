// Created on Tue Mar 3 2015
void get_sonar_readings(int *sonar_val, int sonar_size)
{
	int i = 0 ;
	//check sonar distance
		for ( i = 0 ; i < sonar_size ; ++i)
		{
			set_servo_position( 0, (i*45)/0.09 );
			msleep(400);//takes 50ms to ping sonar
			sonar_val[i] = analog(0) ;
			printf( "sonar %d has a value of %d\n", i, sonar_val[i]);
		}
		
		set_servo_position( 0, 950 ); //center servor
}
void find_max( int *sonar_val, int sonar_size, int *max , int *location )
{
	printf("array size %d\n", sonar_size);
	int j = 0;
	for (j = 0; j < sonar_size ; j++)
	{
		printf("%d,",j);
		if ( sonar_val[j] > *max)
		{
			*max = sonar_val[j] ;
			*location = j;
			printf( "new max of %d @ %d\n" ,*max ,*location);
		}
			
		else if ( sonar_val[j] == *max )
		{
			if( (2 - *location) > (2 - j) )
			{
				*location = j;
				printf( "new location %d \n" ,*location );
			}
		else{ printf( "kept old location %d\n" ,*location ); }
		}	
	}
	printf("Max value found of %d, of location %d\n" , *max , *location);
	
	if( *max < 10) //cannot find a good way to turn
	{ *location = -1 ;}
}

int cons_vel ( int vel )
{
    vel = vel > 1000 ? 1000 : ( vel < -1000 ? -1000 : vel) ; //if > 900 constrain to to 900, less then -900 constrain to -900
    return vel;
}


int main() 
{
	//declare motors
	int fb_motor = 0 ;
	int t_motor = 3 ;
	
	int sonar_val[5] = {0}; //values to store for each sonar position
	int sonar_size = sizeof(sonar_val)/sizeof(sonar_val[0]) ; //need this to pass array by reference and loop through it
	
	//direction to go toward
	int max = 0;
	int location = 0;
	int t_vel = 0; //-1000 turn hard left  <-> 0 straight  <-> 1000 turn hard right, 
	int f_vel = 600;// forward 1000 <-> backward -1000
	
	//setup
	enable_servos();
	set_each_analog_state(1,0,0,0,0,0,0,0); //turn off internal pulldown resistor
	sleep(0.02);// have to wait for the sonar to calibrate itself ( must have nothing within 17" )
	
	
	
	
	while(1){
		get_sonar_readings(sonar_val, sonar_size) ;
		/*
		for(i = 0; i < sizeof(sonar_val)/sizeof(sonar_val[0]) ; i++)
		{
			printf( "sonar %d has a value of %d\n", i, sonar_val[i]);
		}
		*/
		
		//reset max distance to 0
		max = sonar_val[0];
		location = 0;
		//find actual max distance
		find_max( sonar_val, sonar_size, &max , &location );
		/*
		//override max value if going to run into something
		if( sonar_val[2] <= 8)// || sonar_val[1] < 10 || sonar_val[3] < 10) 
		{
			printf("\t something too close\n");
			ao(); //deadstop
			if( location < 2 ) {location == 0;} //turn hard right
			else if (location > 2){ location == 5; } //turn hard left
			else{ location = -1; } //backup
		}
		*/
		// turn to correct direction
		switch (location)
		{
			case 0 : // 90* right
				printf("hard right\n");
				mav( fb_motor , f_vel/4 ) ; //kill forward movement
				mrp( t_motor , 800 , 777 );
				sleep(0.6); 
				break;
			
			case 1 : // 45* right
				printf("slight right\n");
				//keep speed forward same but turn on other motor to arc to the right
				t_vel = t_vel + 100 ;
				break;
			case 2 : // straight
				printf("go straight\n");
				//move forward
				t_vel = 0; //make sure turning motor is zero'd
				mav(t_motor , t_vel) ; 
				break;
			
			case 3 : // 45* left
				printf("slight left\n");
				//keep speed forward same but turn on other motor to arc to the right
				t_vel = t_vel -100 ;
				break;
			case 4 : // 90* left
				printf("hard left\n");
				mav( fb_motor , f_vel/4) ; //kill forward movement
				mrp( t_motor , -800 , -777);
				sleep(0.6);
				break;
			default:
				printf("BACKUP\n");
				t_vel = 0; //make sure turning motor is zero'd
				mav( t_motor , t_vel) ; 
				f_vel = -800 ;
				mav( fb_motor, f_vel ) ;
				
				sleep(2.5);
				break;
		}
		 
		msleep(300); //pause to give servo to reset
		mav(fb_motor , f_vel) ; 
		t_vel = cons_vel(t_vel); //make sure not out of range
		mav(t_motor , t_vel) ; 
		t_vel = 0; //make sure turning motor is zero'd
		f_vel = 600 ; //default back to forward
		
	}
}

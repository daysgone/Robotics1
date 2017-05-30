// Created on Tue Mar 3 2015

int main() 
{
	int fb_motor = 0 ;
	int t_motor = 3 ;
	int max = 0;
	int location = 0;
	int j = 0;
	int sonar_val[5] = {0}; //values to store for each sonar position
	
	
	enable_servos();
	set_each_analog_state(1,0,0,0,0,0,0,0);
	sleep(0.02);
	
	
	while(1){
		ao(); //stop motors
		
		//check sonar distance
		for ( j = 0 ; j < sizeof(sonar_val)/sizeof(sonar_val[0]) ; ++j)
		{
			set_servo_position( 0, (j*45)/0.094 );
			sleep(1.0);
			sonar_val[j] = analog(0) ;
			
		}
		
		set_servo_position( 0, 957 ); //center servor
		for(j = 0; j < sizeof(sonar_val)/sizeof(sonar_val[0]) ; j++)
		{
			printf( "sonar %d has a value of %d\n", j, sonar_val[j]);
		}
		
		//find max distance
		max = sonar_val[0];
		location = 0;
 
		for (j = 0; j < sizeof(sonar_val)/sizeof(sonar_val[0]) ; j++)
		{
			if ( sonar_val[j] > max)
			{
				max = sonar_val[j];
				location = j;
			}
				
			else if ( sonar_val[j] == max )
			{
				if( (2 - location) > (2 - j) )
				{
					max = sonar_val[j];
					location = j;
				}
			}	
		}
		printf("Max value found of %d, of location %d \n" , max , location);
		
		if( max < 10) //cannot find a good way to turn
		{ location = -1 ;}
		
		// turn to correct direction
		switch (location)
		{
			case 0 : // 90* right
				printf("hard right\n");
				mrp( t_motor , 600 , 800);
				sleep(1.0);
				//move forward
				mav(fb_motor, 1000);
				sleep(3.0);
				break;
			case 1 : // 45* right
				printf("slight right\n");
				mrp( t_motor , 600 , 400);
				sleep(1.0);
				//move forward
				mav(fb_motor, 1000);
				sleep(3.0);
				break;
			case 2 : // straight
				printf("go straight\n");
				//move forward
				mav(fb_motor, 1000);
				sleep(3.0);
				break;
			case 3 : // 45* left
				printf("slight left\n");
				mrp( t_motor , -600 , -400);
				sleep(1.0);
				//move forward
				mav(fb_motor, 1000);
				sleep(3.0);
				break;
			case 4 : // 90* left
				printf("hard left\n");
				mrp( t_motor , -600 , -800);
				sleep(1.0);
				//move forward
				mav(fb_motor, 1000);
				sleep(3.0);
				break;
			default:
				printf("BACKUP\n");
				mav( fb_motor, -800);
				sleep(3.0);
				break;
		}
		
		
		
		
	}
}

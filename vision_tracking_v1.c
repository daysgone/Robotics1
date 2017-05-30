void turn(int x)
{
	if(x < 60){
		mav(3, 100);
		printf("turning right\n");
	}
	else if(x < 100)
	{
		mav(3, 0);
		printf("going straight\n");
	}
	else
	{
		mav(3, -100);
		printf("turning left\n");
	}
}

int main()
{
	int x,y;
	int fb_vel = 800;
	
	while(black_button() == 0){
		track_update(); //get most recent camera image and process it
		x =  track_x(0,0);
		y = track_y(0,0);
		printf("size of blob %d\n", track_size(0, 0));
		
		//there are blobs found 
		if(track_count(0) > 0 )
		{	
			if(track_size(0,0) > 20 && track_size(0,0) < 4000) //foudn a large enough blob
			{
				//adjusting turning speed bassed off distance away
				if( y > 40 )//far
				{ 	
					printf("far\n");
					mav(0, fb_vel);
					turn(x);
				}
				else if ( y > 10 ) //closer
				{
					printf("closer\n");
					mav(0, fb_vel/2);
					turn(x);
				}
				else //close 
				{
					printf("close\n");
					mav(0, fb_vel/4);
					turn(x);
				} 
			}	
			else if (track_size(0,0) >= 4000)
			{
				//RIGHT IN FRONT OF CAMERA
				//start to find place to put ball
				printf("have ball \n");
				mav(3,0);
				mav(0, 500);//needs to slow increase speed so it doesnt bump it out of the way
			}
				
			else
			{
				printf("blob found, too small \n");
				mav(3, 500);
			}
		}
		else
		{
			printf("no blobs found \n");
			mav(3, 500);
		}
        
	}
	return 0;
}

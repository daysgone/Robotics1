void turn(int x)//determine direction to move depending on the blobs center x location
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
	int fb_vel = 800; //general forward direction
	int done = 0;
	int current_color = 0; //default to track red channel


	while(black_button() == 0 || done == 0){
		track_update(); //get most recent camera image and process it

		x = track_x(current_color,0); //current color is red if has not picked up ball yet
		y = track_y(current_color,0); //blue if carrying a ball

		printf("size of blob %d\n", track_size(0, 0));

		//there are blobs found
		if(track_count(0) > 0 )
		{
			if(track_size(0,0) > 20 && track_size(0,0) < 4000) //found a large enough blob
			{
				//adjusting turning speed based off distance away
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
				else //real close
				{
					printf("real close\n");
					mav(0, fb_vel/4);
					turn(x);
				}
			}
			else if (track_size(0,0) >= 4000)
			{
				//RIGHT IN FRONT OF CAMERA
				if( current_color == 3 )
				{
					printf("dropping off ball\n");
					ao();
					//open up gripper
					//mav(1,-200);
					//msleep(200);//allow time to fully open
					mav(0, -100); //back-away from ball
					msleep(100);
					current_color = 0;

					done = 1; //stop code

				}
				else
				{
					printf("have ball \n");
					ao(); //stop to grab ball

					//use gripper to grab ball
					//mav(1,200);
					//msleep(200);//allow time to fully close

					printf("switching to blue\n");
					current_color = 3;
					mav(3,500); //turn to find place to drop off ball

				}

			}

			else // keep searching for a viable blob
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

int main()
{
	int x;
	while(1){
	track_update(); //get most recent camera image and process it
	x = track_x(0,0);
	if(track_count(0) > 0){
		mav(0, 400);
		if(x < 60){
			mav(3, -100);
			printf("turning left\n");
		}
		else if(x < 100){
			mav(3, 0);
			printf("going straight\n");
		}
		else{
			mav(3,100);
			printf("turning right\n");
		}
		
	}
	else{
		mav(3, 500);
	}
			
	}
	return 0;
}

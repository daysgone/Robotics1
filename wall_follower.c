//wall follower
int modulate_speed()
{
	if(analog10(2) < 50)
		return 360;
	else if(analog10(2) < 100)
		return 365;
	else if(analog10(2) < 150)
		return 370;
	else if(analog10(2) < 200)
		return 375;
	else if(analog10(2) < 250)
		return 380;
	else if(analog10(2) < 300)
		return 385;
	else if(analog10(2) < 350)
		return 390;

}



int main() 
{
	set_each_analog_state(0,0,1,1,0,0,0,0); //disable internal pulldown resistor
	sleep(0.02);
	while(1)
	{
		if(analog10(2) < 350) //turn toward wall
		{
			mav(1, 400);
			mav(0, modulate_speed());
		}
		else if(analog10(2) < 400)//go straight
		{
			mav(1, 800);
			mav(0, 800);
		}
		else //turn away from wayy
		{
			mav(0, 800);
			mav(1, modulate_speed());
		}
	}
	return 0;
}


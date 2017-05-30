// Created on Wed Feb 18 2015
int constrain (int val);
int main() 
{
	while(1)
	{
		printf(	"Right Sensor: %d \n", analog10(0) );
		mav(1, constrain(500 - analog10(0)) * 1.5 ); //motor 1 turns faster the lower the value obtained from the right sensor
		printf(	"\tLeft Sensor: %d ", analog10(1) );
		mav(0, constrain(500 - analog10(1)) * 1.5 ); //motor 0 turns faster the lower the value obtained from the right sensor
	}
	return 0;
}

int constrain ( int val)
{
    return val < 0 ? 0 : val ; //if > 1000 constrain to 0, else keep same passed in value
}

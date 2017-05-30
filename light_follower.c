void rotateLeft()
{
	fd(0);
	bk(3);
}

void rotateRight()
{
	fd(3);
	bk(0);
}

void moveBack()
{
	bk(0);
	bk(3);
}

void moveForward()
{
	fd(0);
	fd(3);
}

void search()
{
	mav(0, 600);
	mav(3, -600);
}

int main() 
{
	while(1)
	{
		if(analog10(0) > 750 && analog10(1) > 750)
			search();
		sleep(0.5);
	
		while(analog10(0) > analog10(1) && analog10)
			rotateRight();
		while(analog10(0) < analog10(1))
			rotateLeft();
		
			
	}
}


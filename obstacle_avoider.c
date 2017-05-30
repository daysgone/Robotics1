// Created on Thu Feb 5 2015
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

int main() 
{
	while(1)
	{
		int m1, m2 = 0;
		fd(0);
		fd(3);
		while(digital(8) || digital(9))
		{
			while(digital(8))
		{
			run_for(1.5 , moveBack);
			m1 = 1;
		}
		if(m1)
		{
			run_for(0.7, rotateLeft);
			m1 = 0;
		}
		
		while(digital(9))
		{
			run_for(1.5, moveBack);
			m2 = 1;
		}
		if(m2)
		{
			run_for(0.7, rotateRight);
			m2 = 0;
		}
		}
		
	}
}

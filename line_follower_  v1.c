/* 
This program runs
*/

int main()
{
	while (1)
    {
        mav(0, 1000);
        mav(3, 1000);
        
		while(analog10(0) < 128)
        {
            mav(0, 1000);
            mav(3, -600);
        }
        while(analog10(1) < 128)
        {
            mav(3, 1000);
            mav(0, -600);	
        }
    }
}

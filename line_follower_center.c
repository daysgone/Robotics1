
int main()
{
    while (1)
    {
		if(analog10(2) > 128)
        {
            mav(0, -400);
            mav(3, 1000);
        }
        if(analog10(2) <= 128)
        {
            mav(3, -400);
            mav(0, 1000);	
        }
    }
}

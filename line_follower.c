
int main()
{
    while (1)
    {
        mav(0, 600);
        mav(3, 600);
        
		while(analog10(0) < 128)
        {
            mav(0, 950);
            mav(3, -350);
        }
        while(analog10(1) < 128)
        {
            mav(3, 950);
            mav(0, -350);	
        }
    }
}

#include<iostream>
#include<time.h>
#include<stdlib.h>
#include<windows.h>
using namespace std;
int main()
{
    srand((unsigned int)time(0));
	LARGE_INTEGER t1, t2, tc;
	QueryPerformanceFrequency(&tc);
    int n,m;
    for(n=1000;n<8001;n+=1000)
    {
        for(m=10;m<31;m+=10)
        {
            int rem=n;
            QueryPerformanceCounter(&t1);
            for(int i=0;i<1000;i++)
            {
                rem=n;
                while(true)
                {
                    rem-=(rem%(1+m));
                    if(rem==0) break;
                    rem-=(rand()%m+1);
                }
            }

            QueryPerformanceCounter(&t2);
            cout<<"n="<<n<<" m="<<m<<endl<<"time="<<(t2.QuadPart - t1.QuadPart) * 1000.0 / tc.QuadPart<<"Î¢Ãë"<<endl;
        }
        cout<<endl;
    }
    return 0;
}

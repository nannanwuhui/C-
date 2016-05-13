#include <stdio.h>
#include <time.h>
void foo( int& year, int& month, int& day )
{
    year = 1900;
    month = 1;
    day += 0;
    for(int n; n=(((year%4==0 && year%100!=0)||(year%400==0))?366:365), day>=n; day-=n, ++year );
    static int m[12] = { 31,0,31,30,31,30,31,31,30,31,30,31 };
    m[1] = ( ((year%4==0 && year%100!=0)||(year%400==0)) ? 29 : 28 );
    for( int i=0; day>=m[i]; day-=m[i], ++i, ++month );
    ++day;
}
int main()
{
    for( int i=25567; i<=38555; ++i ) // 从1970/01/01测试到2005/07/24
    {
        int year;
        int month;
        int day = i;
        foo( year, month, day );
        printf( "%04d/%02d/%02d --- ", year, month, day );
        time_t t1 = (i-25567)*24*3600;
        tm* t2 = gmtime( &t1 );
        printf( "%04d/%02d/%02d\n", t2->tm_year+1900, t2->tm_mon+1, t2->tm_mday );
        if( year!=t2->tm_year+1900 || month!=t2->tm_mon+1 || day!=t2->tm_mday )
        {
            printf( "ERR: %d\n", i );
            getchar();
        }
    }
    return 0;
}

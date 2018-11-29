#include <stdio.h>
#include <stdlib.h>

int is_leap(int year);
int yearFirstDay_weekday(int year);
int monthFirstDay_weekday(int year, int month);
void printCalendar(int year, int month);

void printCalendarWholeYear(int year);

char monthNames[12][4] = { "Jan", "Feb", "Mar", "Apr", "May", "Jun", "Jul", "Aug", "Sep", "Oct", "Dec", "Nov" };
int monthDaysLeap[12] = { 31, 29, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };
int monthDaysNotLeap[12] = { 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };
char weekdays[7][4] = { "Sun", "Mon", "Tue", "Wed", "Thu", "Fri", "Sat" };

int main(void)
{
	int year, month;
	printf("Please input a year: ");
	while (scanf("%d", &year) != EOF)
	{
		printCalendarWholeYear(year);
		printf("Please input a year: ");
	}
	return 0;
}

int is_leap(int year)  // 判断该年是否是闰年
{
	if ((year % 4 == 0 && year % 100 != 0) || year % 400 == 0) {
		return 1;
	}
	return 0;
}

// * 按照规定的0001年 1月 1日开始
// * 计算从 0001年 1月 1日开始到规定年份有多少天
// * 先假设没有闰年，所以加365x（year - 1）
// * 然后补充闰年数
int yearFirstDay(int year)
{
	int n = 0, i;

	n += (year - 1) * 365; //假设该年之前没有闰年，计算从0001年开始有几天
	for (i = 1; i < year; i++)
	{
		n += is_leap(i);    // 计算从0001年到该年闰年没有加的天数
	}

	return n;
}

int monthFirstDay_weekday(int year, int month)  // 计算该年该月第一天是从0001年算起的第几天，并换算成星期几
{
	int day = yearFirstDay(year), i;          // 先算出该年1月1日是第几天

	if (is_leap(year))
	{
		for (i = 0; i < month - 1; i++)
		{
			day += monthDaysLeap[i];          // 闰年情况下，计算该月之前有几天
		}
	}
	else
	{
		for (i = 0; i < month - 1; i++)
		{
			day += monthDaysNotLeap[i];    //非闰年
		}
	}
	
	return day % 7 + 1;            // 换算成星期几
}

void printCalendar(int year, int month)
{
	int i, j, day = 1;
	
	
	for (i = 0; i < 7; i++)
	{
		printf("%5s", weekdays[i]);  //打印表头
	}
	putchar('\n');
	
	for (i = 1; i <= monthFirstDay_weekday(year, month); i++) //该循环用于输出第一个星期的空格
	{
		printf("     ");
	}
	for (j = monthFirstDay_weekday(year, month); j <= 6; j++)  // 该循环补充出第一个星期的剩余天数
	{
		printf("%5d", day++);
	}
	putchar('\n');



	// * 除去第一个星期，剩余天数不超过 30 天
	// * 所以外层循环控制打印 5 行
	// * 内层循环控制每行打印 7 个数字
	// * 如果天数已经到达该月总天数，则跳出循环
	// *
	if (is_leap(year))                                
	{
		for (i = 1; i <= 5; i++) {
			for (j = 1; j <= 7; j++) {
				if (day == monthDaysLeap[month - 1] + 1) {
					break;
				}
				else {
					printf("%5d", day++);
				}
			}
			putchar('\n');
		}
	}
	else
	{
		for (i = 1; i <= 5; i++) {
			for (j = 1; j <= 7; j++) {
				if (day == monthDaysNotLeap[month - 1] + 1) {
					break;
				}
				else {
					printf("%5d", day++);
				}
			}
			putchar('\n');
		}
	}
}

void printCalendarWholeYear(int year)
{
	int m = 1, i;

	printf("Year %d: \n", year);
	for (m = 1; m <= 12; m++)
	{
		for (i = 0; i < 7; i++)
		{
			printf("=+=+=");
		}
		putchar('\n');
		printf("%s: \n\n", monthNames[m - 1]);
		printCalendar(year, m);
	}
}
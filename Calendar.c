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

int is_leap(int year)  // �жϸ����Ƿ�������
{
	if ((year % 4 == 0 && year % 100 != 0) || year % 400 == 0) {
		return 1;
	}
	return 0;
}

// * ���չ涨��0001�� 1�� 1�տ�ʼ
// * ����� 0001�� 1�� 1�տ�ʼ���涨����ж�����
// * �ȼ���û�����꣬���Լ�365x��year - 1��
// * Ȼ�󲹳�������
int yearFirstDay(int year)
{
	int n = 0, i;

	n += (year - 1) * 365; //�������֮ǰû�����꣬�����0001�꿪ʼ�м���
	for (i = 1; i < year; i++)
	{
		n += is_leap(i);    // �����0001�굽��������û�мӵ�����
	}

	return n;
}

int monthFirstDay_weekday(int year, int month)  // ���������µ�һ���Ǵ�0001������ĵڼ��죬����������ڼ�
{
	int day = yearFirstDay(year), i;          // ���������1��1���ǵڼ���

	if (is_leap(year))
	{
		for (i = 0; i < month - 1; i++)
		{
			day += monthDaysLeap[i];          // ��������£��������֮ǰ�м���
		}
	}
	else
	{
		for (i = 0; i < month - 1; i++)
		{
			day += monthDaysNotLeap[i];    //������
		}
	}
	
	return day % 7 + 1;            // ��������ڼ�
}

void printCalendar(int year, int month)
{
	int i, j, day = 1;
	
	
	for (i = 0; i < 7; i++)
	{
		printf("%5s", weekdays[i]);  //��ӡ��ͷ
	}
	putchar('\n');
	
	for (i = 1; i <= monthFirstDay_weekday(year, month); i++) //��ѭ�����������һ�����ڵĿո�
	{
		printf("     ");
	}
	for (j = monthFirstDay_weekday(year, month); j <= 6; j++)  // ��ѭ���������һ�����ڵ�ʣ������
	{
		printf("%5d", day++);
	}
	putchar('\n');



	// * ��ȥ��һ�����ڣ�ʣ������������ 30 ��
	// * �������ѭ�����ƴ�ӡ 5 ��
	// * �ڲ�ѭ������ÿ�д�ӡ 7 ������
	// * ��������Ѿ����������������������ѭ��
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
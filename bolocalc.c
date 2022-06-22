#include <time.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int main(void)
{
	struct tm str_time;
	int tmp_year,tmp_month; 
	int ref_obrt, bolo_obrt[4];
	time_t ref_time, bolo_time[4];
	char * bolo_time_string[4];
	char * ref_time_string;

	int i = 0;
	char * m[4];
	m[0] = "Insert the 1st inibition time [YYYY-MM-DD hh:mm:ss]:\n";
	m[1] = "Insert the 1st cross-over time [YYYY-MM-DD hh:mm:ss]:\n";
	m[2] = "Insert the 2nd inibition time [YYYY-MM-DD hh:mm:ss]:\n";
	m[3] = "Insert the 2nd cross-over time [YYYY-MM-DD hh:mm:ss]:\n";

	char * b[4];
	b[0] = "INIBITION 1";
	b[1] = "CROSS-OVER 1";
	b[2] = "INIBITION 2";
	b[3] = "CROSS-OVER 2";

	/* Startup screen  */
	system("clear");
	printf("############################################################################\n");
	printf("Bolometers Inibition Management Tool\n");
	printf("----------------------------------------------------------------------------\n");
	printf("Developed by Giovanni Pecoraro <giovanni1.pecoraro@protonmail.com>\n");
	printf("----------------------------------------------------------------------------\n\n");

	/* Reference time */
	printf("Insert the reference time [YYYY-MM-DD hh:mm:ss]:\n");
	scanf("%d-%d-%d %d:%d:%d",&tmp_year,&tmp_month,&str_time.tm_mday,&str_time.tm_hour,&str_time.tm_min,&str_time.tm_sec);
	str_time.tm_year = tmp_year-1900;
	str_time.tm_mon = tmp_month-1;	
	str_time.tm_isdst = 0;
	ref_time = mktime(&str_time);
	ref_time_string   = (char*)calloc(255, sizeof(char));
	sprintf(ref_time_string,"%04d-%02d-%02d %02d:%02d:%02d",tmp_year,tmp_month,str_time.tm_mday,str_time.tm_hour,str_time.tm_min,str_time.tm_sec);

	/* Reference OBRT */
	printf("Insert the reference OBRT:\n");
	scanf("%d",&ref_obrt);

	for (i=0; i<4; i++) 
	{
		/* Bolometer inibition time */	
		printf("%s", m[i]);

		scanf("%04d-%02d-%02d %02d:%02d:%02d",&tmp_year,&tmp_month,&str_time.tm_mday,&str_time.tm_hour,&str_time.tm_min,&str_time.tm_sec);	
		str_time.tm_year = tmp_year-1900;
		str_time.tm_mon = tmp_month-1;	
		str_time.tm_isdst = 0;
		bolo_time[i] = mktime(&str_time);
		bolo_time_string[i]   = (char*)calloc(255, sizeof(char));
		sprintf(bolo_time_string[i],"%04d-%02d-%02d %02d:%02d:%02d",tmp_year,tmp_month,str_time.tm_mday,str_time.tm_hour,str_time.tm_min,str_time.tm_sec);

		/* Bolometer inibition OBRT */
		bolo_obrt[i] = ref_obrt + difftime(bolo_time[i],ref_time);
	}

	/* Summary */
	system("clear");
	printf("############################################################################\n");
	printf("SUMMARY\n");
	printf("############################################################################\n");
	printf("Reference time: %s\n", ref_time_string);
	printf("Reference OBRT: %d\n", ref_obrt);	
	printf("----------------------------------------------------------------------------\n");
	printf("\t\tINIBITION TIME\t\t-->\tINIBITION OBRT\n");
	printf("----------------------------------------------------------------------------\n");
	for (i=0; i<4; i++) 
	{
		printf("%s\t%s\t-->\t%d\n",b[i],bolo_time_string[i],bolo_obrt[i]);
		printf("----------------------------------------------------------------------------\n");
		free(bolo_time_string[i]);

	}
	printf("############################################################################\n");

	free(ref_time_string);

	return 0;
	
}

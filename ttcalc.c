#include <time.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int main(void)
{
	struct tm str_time;
	int tmp_year,tmp_month; 
	int ref_obrt, tt_obrt;
	time_t ref_time, tt_time;
	char * obrt_hex;
	char * tt_time_string;
	char * ref_time_string;

	char obrt_hex_3byte[7]; 
	int obrt_int_3byte = 0;
	char obrt_hex_2byte[5]; 
	int obrt_int_2byte = 0;
	
	FILE * outfile;
	char * filename;
	char * file_string;
	
	char c;

	/* Startup screen  */
	system("clear");
	printf("############################################################################\n");
	printf("Time-tagged Telecommands Management Tool\n");
	printf("----------------------------------------------------------------------------\n");
	printf("Developed by Giovanni Pecoraro <giovanni1.pecoraro@protonmail.com>\n");
	printf("----------------------------------------------------------------------------\n\n");

	/* Reference time */
	printf("Insert the reference time [YYYY-MM-DD hh:mm:ss]:\n");
	scanf("%d-%d-%d %d:%d:%d",&tmp_year,&tmp_month,&str_time.tm_mday,&str_time.tm_hour,&str_time.tm_min,&str_time.tm_sec);
	str_time.tm_year = tmp_year-1900;
	str_time.tm_mon = tmp_month-1;	
	str_time.tm_isdst = 0;
	ref_time = mktime(&str_time); // gmtime
	ref_time_string   = (char*)calloc(255, sizeof(char));
	sprintf(ref_time_string,"%04d-%02d-%02d %02d:%02d:%02d",tmp_year,tmp_month,str_time.tm_mday,str_time.tm_hour,str_time.tm_min,str_time.tm_sec);

	/* Reference OBRT */
	printf("Insert the reference OBRT:\n");
	scanf("%d",&ref_obrt);

	do {
		/* Telecommand execution time */	
		printf("Insert telecommand execution time [YYYY-MM-DD hh:mm:ss]:\n");
		scanf("%04d-%02d-%02d %02d:%02d:%02d",&tmp_year,&tmp_month,&str_time.tm_mday,&str_time.tm_hour,&str_time.tm_min,&str_time.tm_sec);	
		str_time.tm_year = tmp_year-1900;
		str_time.tm_mon = tmp_month-1;	
		str_time.tm_isdst = 0;
		tt_time = mktime(&str_time); // gmtime
		tt_time_string = (char*)calloc(255, sizeof(char));
		sprintf(tt_time_string,"%04d-%02d-%02d %02d:%02d:%02d",tmp_year,tmp_month,str_time.tm_mday,str_time.tm_hour,str_time.tm_min,str_time.tm_sec);

		/* Telecommnad execution OBRT */
		tt_obrt = ref_obrt + difftime(tt_time,ref_time);

		/* OBRT in HEX format  */
		obrt_hex   = (char*)calloc(255, sizeof(char));
		sprintf(obrt_hex,"%08x00", tt_obrt);
		/* printf("%s\n",obrt_hex); */

		/* 3 bytes OBRT */
		memcpy(obrt_hex_3byte,&obrt_hex[0],6); obrt_hex_3byte[6] = '\0';
		obrt_int_3byte = (int)strtol(obrt_hex_3byte, NULL, 16);
		/* printf("%d\n",obrt_int_3byte);

		/* 2 bytes OBRT */
		memcpy(obrt_hex_2byte,&obrt_hex[6],4); obrt_hex_2byte[4] = '\0';
		obrt_int_2byte = (int)strtol(obrt_hex_2byte, NULL, 16);
		/* printf("%d\n",obrt_int_2byte); */

		/* Output to file  */
		filename = (char*)calloc(255, sizeof(char));
      	sprintf(filename, "timetagged.txt");
		outfile = fopen(filename,"w");

		file_string = (char*)calloc(255, sizeof(char));
		sprintf(file_string,"%04d-%02d-%02d_%02d:%02d:%02d %d %d",tmp_year,tmp_month,str_time.tm_mday,str_time.tm_hour,str_time.tm_min,str_time.tm_sec,obrt_int_3byte,obrt_int_2byte);
		/* printf("%s\n",file_string); */			
		fwrite(file_string,strlen(file_string),1,outfile);
      	fclose(outfile);

		/* Summary */
		system("clear");
		printf("############################################################################\n");
		printf("SUMMARY\n");
		printf("############################################################################\n");
		printf("Reference time: %s\n", ref_time_string);
		printf("Reference OBRT: %d\n", ref_obrt);	
		printf("----------------------------------------------------------------------------\n");
		printf("Execution time: %s\n", tt_time_string);
		printf("Execution OBRT (4 byte) [int]: %d\n", tt_obrt);
		printf("Execution OBRT (5 byte) [hex]: %s\n", obrt_hex);
		printf("Execution OBRT (3 byte) [hex-int]: %s---->%d\n", obrt_hex_3byte, obrt_int_3byte);
		printf("Execution OBRT (2 byte) [hex-int]: %s---->%d\n", obrt_hex_2byte, obrt_int_2byte);
		printf("----------------------------------------------------------------------------\n");
		printf("############################################################################\n");
		printf("############################################################################\n");

		/* Output file for STORM */
		printf("Time Tagged file\n");
	   	system("cat timetagged.txt");
		printf("\n############################################################################\n");

		/* Additional telecommands? */
		printf("\nDo you want to send additional time-tagged telecommands? [y/n]");
		scanf(" %c",&c);
	} while ((c == 'y') || (c == 'Y'));

	free(ref_time_string);
	free(tt_time_string);
	free(obrt_hex);
	free(filename);
	free(file_string);

	return 0;	
}

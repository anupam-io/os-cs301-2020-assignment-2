#include<stdio.h>
#include<stdlib.h>

int main(){
	FILE* data_out = fopen("_csv.csv","w");
	fprintf(data_out, "123,\n");
	fprintf(data_out, "123,\n");
	fprintf(data_out, "123,\n");
	fclose(data_out);

	return 0;
}
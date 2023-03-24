// Javorina Nikola, EE171/2013

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main()
{
	FILE* fp1;		// ledovke
	FILE* fp2;		// switchevi
	FILE* fp3;		// dugmici
	char  t0,t1,t2,t3;	// dugmici
	char  sw1, sw0;		// switchevi 
	char  *str1;		// dugmici
	char  *str2;		// switch
	size_t num_of_bytes=6;
	char *stanje[]={"0b0001","0b0010","0b0100","0b1000"};  
	int prethodni;
	int taster=0;
	int pritisnuto=0;
	int s=0;
	int m=0;
	int i=0;

		fp1 = fopen("/dev/led", "w");
		if(fp1 == NULL)
		{
			printf("Problem pri otvaranju /dev/led\n");
			return -1;
		}
		fputs(stanje[0],fp1);
		if(fclose(fp1))
		{
			printf("Problem pri zatvaranju /dev/led\n");
			return -1;
		}

	while(1) 
	{	

		//Switchevi	
		fp2 = fopen ("/dev/switch", "r");
		if(fp2==NULL)
		{
			puts("Problem pri otvaranju /dev/switch");
			return -1;
		}


		str2 = (char *)malloc(num_of_bytes+1); 
		getline(&str2, &num_of_bytes, fp2); 

		if(fclose(fp2))
		{
			puts("Problem pri zatvaranju /dev/switch");
			return -1;
		}

				
		sw1 = str2[4] - 48;
		sw0 = str2[5] - 48;
		free(str2);

			
		if (sw0==0 && sw1==0) {
			m=0;
		}
		
		else if (sw0==1 && sw1==0) {
			m=1;
		}

		else if (sw0==0 && sw1==1) {
			m=2;
		}
		else if (sw0==1 && sw1==1) {
			m=3;
		}

		
		

		//Dugmici
		fp3 = fopen ("/dev/button", "r");
		if(fp3==NULL)
		{
			puts("Problem pri otvaranju /dev/button");
			return -1;
		}


		str1 = (char *)malloc(num_of_bytes+1); 
		getline(&str1, &num_of_bytes, fp3); 

		if(fclose(fp3))
		{
			puts("Problem pri zatvaranju /dev/button");
			return -1;
		}

		t3 = str1[2] - 48;
		t2 = str1[3] - 48;	
		t1 = str1[4] - 48;	
		t0 = str1[5] - 48;	
		
		
		if (t3==1) 
			pritisnuto=2;
		
		else if (t2==1) 
			pritisnuto=3;
		
		else if (t1==1) 
			pritisnuto=4;
		
		else if (t0==1) 
			pritisnuto=5;
		free(str1);


			
		prethodni=taster;
		taster=pritisnuto;
		
		if (taster!=prethodni) {			
		if (t0==1) {
			s=0;
		}

		else if (t1==1) {
			for (i=0; i<m; i++) {
				s--;
			if (s<0){
				s=3;
				}
			}
		}	

		else if (t2==1) {
			for (i=0; i<m; i++) {
				s++;
			if (s>3){
				s=0;
				}
			}
		}
		
		else if (t3==1) {
			s=3;
			}
		}
		pritisnuto=0;

		
		// Upali diode
		fp1 = fopen("/dev/led", "w");
		if(fp1 == NULL)
		{
			printf("Problem pri otvaranju /dev/led\n");
			return -1;
		}
		fputs(stanje[s], fp1);
		if(fclose(fp1))
		{
			printf("Problem pri zatvaranju /dev/led\n");
			return -1;
		}
	}
	return 0;
}

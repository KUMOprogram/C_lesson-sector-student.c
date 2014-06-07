#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

struct lesson
{
	int lessonid;
	char lessonname[40];
	int weekhours;
	int lessonabs;
	int semester;
	char semestername[20];
};
	
struct sector
{
 	int sectorid;
   	char sectorname[50];
   	struct lesson lessor[5];
};

struct studentprogress
{
	int lessonid;
	int grade;
	int absence;
};

struct student
{
	int studentid;
	char studentFname[30];
	char studentLname[30];
	int sectorid;
	struct studentprogress progress[5];
};

int print_lessons (int j)
{
			FILE *less;
			int i,something;
			struct lesson lessram;
			
			less=fopen("data/lessons.dat","r"); //open to less
     		for (i=0; i<j; i++)
         	{
               something=fread(&lessram,sizeof(struct lesson),1,less);
               printf(" ID ma8hmatos %i: %i\n", i+1, lessram.lessonid);
               printf(" onoma ma8hmatos %i: %s\n", i+1, lessram.lessonname);
               printf(" wres ma8hmatos %i: %i\n", i+1, lessram.weekhours);
               printf(" apousies ma8hmatos %i: %i\n", i+1, lessram.lessonabs);
               printf(" e3amhno ma8hmatos %i: %i\n", i+1, lessram.semester);
               printf(" e3amhno ma8hmatos %i: %s\n", i+1, lessram.semestername);
               printf(" ------------------------------------------------------\n");
         	}
     		fclose(less);
			return 0;
}

int print_sectors (int jj)
{
            FILE *sexor;
			int i,n,something;
			struct sector sectram;

    		sexor=fopen("data/sectors.dat","r");
			for (i=0; i<jj; i++)
			{
				something=fread(&sectram,sizeof(struct sector),1,sexor);
				 printf(" ID tmhmatos: %i\n", sectram.sectorid);
				 printf(" onoma tmhmatos: %s\n\n", sectram.sectorname);
				 for (n=0; n<5; n++)
       			 {
					if (sectram.lessor[n].lessonid!=0)
					{
               			printf(" * ID ma8hmatos: %i\n", sectram.lessor[n].lessonid);
               			printf(" * onoma ma8hmatos: %s\n", sectram.lessor[n].lessonname);
               			printf(" * wres ma8hmatos: %i\n", sectram.lessor[n].weekhours);
               			printf(" * apousies ma8hmatos: %i\n", sectram.lessor[n].lessonabs);
               			printf(" * e3amhno ma8hmatos: %i\n", sectram.lessor[n].semester);
               			printf(" * e3amhno ma8hmatos: %s\n\n", sectram.lessor[n].semestername);
					}
		 		}
		 		printf(" ------------------------------------------------------\n");
			}
			fclose(sexor);
    		return 0;
}

int print_students (int jjj)
{
    		FILE *stud;
			int i,n,something;
			struct student studram;
			
            stud=fopen("data/students.dat","r"); //open to stud
     		for (i=0; i<jjj; i++)
         	{
               something=fread(&studram,sizeof(struct student),1,stud);
               printf(" ID ma8hth %i: %i\n", i+1, studram.studentid);
               printf(" onoma ma8hth %i: %s\n", i+1, studram.studentFname);
               printf(" eponymo ma8hth %i: %s\n", i+1, studram.studentLname);
               if (studram.sectorid!=0)
               {
					printf(" ID tomea ma8hth %i: %i\n\n", i+1, studram.sectorid);
               }else{
					printf(" DEN exei oristei ID tomea ma8hth %i\n\n", i+1);
               }
               for (n=0; n<5; n++)
       		   {
					if (studram.progress[n].lessonid!=0 && studram.sectorid!=0)
					{
               			printf(" * ID ma8hmatos: %i\n", studram.progress[n].lessonid);
               			printf(" * ba8mos ma8hmatos: %i\n", studram.progress[n].grade);
               			printf(" * apousies ma8hmatos: %i\n\n", studram.progress[n].absence);
					}
		 	   }
               printf(" ------------------------------------------------------\n");
         	}
     		fclose(stud);
    		return 0;
}

int replace_sectors (int sit)
{
    int i,j,jj,something,g;

	FILE *less;
	FILE *sexor;

	FILE *counter_less;
	FILE *counter_sexor;

    struct lesson lessram;
    struct sector sectram;

            counter_less=fopen("data/counter_lessons.txt","r");
        		fscanf(counter_less,"%i",&j); //counter_lesson
     		fclose(counter_less);

     		counter_sexor=fopen("data/counter_sectors.txt","r");
        		fscanf(counter_sexor,"%i",&jj); //counter_sexor
     		fclose(counter_sexor);

			struct sector sec[jj];
     		struct lesson les[j];

     		sexor=fopen("data/sectors.dat","r"); //open to sexor
      		if (sexor!=NULL)
      		{
         		for (i=0; i<jj; i++)
         		{
               		something=fread(&sectram,sizeof(struct sector),1,sexor);
               		sec[i]=sectram;
         		}
      		}
     		fclose(sexor);

     		less=fopen("data/lessons.dat","r"); //open to less
      		if (less!=NULL)
      		{
         		for (i=0; i<j; i++)
         		{
               		something=fread(&lessram,sizeof(struct lesson),1,less);
               		les[i]=lessram;
        		}
      		}
     		fclose(less);
     	  	
       for (g=0; g<jj; g++)
       {
     		for (i=0; i<5; i++)
     		{
                if (sec[g].lessor[i].lessonid==les[sit].lessonid)
                {
                   strcpy(sec[g].lessor[i].lessonname,les[sit].lessonname);
                   sec[g].lessor[i].weekhours=les[sit].weekhours;
                   sec[g].lessor[i].lessonabs=les[sit].lessonabs;
                   sec[g].lessor[i].semester=les[sit].semester;
                   strcpy(sec[g].lessor[i].semestername,les[sit].semestername);
                }
            }
       }
                
       sexor=fopen("data/sectors.dat","w");
       for (i=0; i<jj; i++)
       {
           fwrite(&sec[i],sizeof(struct sector),1,sexor);
       }
       fclose(sexor);
       print_sectors(jj);
       printf("\n Apo8hkeuthke h allagh kai sto data/sectors.dat\n");
       printf(" ------------------------------------------------------\n");
     			
       return 0;	
}

int delete_from_sectors (int deleta)
{
    int i,jj,something,g;

	FILE *sexor;
	
	FILE *counter_sexor;

    struct sector sectram;

     		counter_sexor=fopen("data/counter_sectors.txt","r");
        		fscanf(counter_sexor,"%i",&jj); //counter_sexor
     		fclose(counter_sexor);

			struct sector sec[jj];

     		sexor=fopen("data/sectors.dat","r"); //open to sexor
      		if (sexor!=NULL)
      		{
         		for (i=0; i<jj; i++)
         		{
               		something=fread(&sectram,sizeof(struct sector),1,sexor);
               		sec[i]=sectram;
         		}
      		}
     		fclose(sexor);

       for (g=0; g<jj; g++)
       {
     		for (i=0; i<5; i++)
     		{
                if (sec[g].lessor[i].lessonid==deleta)
                {
                    sec[g].lessor[i].lessonid=0;
                }
            }
       }

       sexor=fopen("data/sectors.dat","w");
       for (i=0; i<jj; i++)
       {
           fwrite(&sec[i],sizeof(struct sector),1,sexor);
       }
       fclose(sexor);
       print_sectors(jj);
       printf("\n Apo8hkeuthke h antistoixh diagrafh kai sto data/sectors.dat\n");
	   printf(" ---------------------------------------------------------------\n");

       return 0;
}

int main (void)
{
system("md data");

	int i,j,jj,jjj,something,b,n,sit;

	FILE *less;
	FILE *stud;
	FILE *sexor;

	FILE *counter_less;
    FILE *counter_stud;
	FILE *counter_sexor;

    struct lesson lessram;
	struct student studram;
    struct sector sectram;
    
	_Bool flagaros;
	flagaros=1;
	while (flagaros)
	{
	system("cls");
	system("color f1");

   	 	printf("*******************************************************************************\n\n");
   		printf("              create/reset sector files ----------------- 1\n");
   		printf("              create/reset lesson files ----------------- 2\n");
   		printf("              create/reset student files ---------------- 3\n");
    	printf("              add new sector ---------------------------- 4\n");
        printf("              add new lesson ---------------------------- 5\n");
        printf("              add new student --------------------------- 6\n");
    	printf("              print in screen sectors ------------------- 7\n");
    	printf("              print in screen lessons ------------------- 8\n");
    	printf("              print in screen students ------------------ 9\n");
    	printf("              change something in sector ---------------- 10\n");
    	printf("              change something in lesson ---------------- 11\n");
    	printf("              change something in student --------------- 12\n");
    	printf("              delete sector ----------------------------- 13\n");
    	printf("              delete lesson ----------------------------- 14\n");
    	printf("              delete student ---------------------------- 15\n");
    	printf("              end program ------------------------------- 0\n\n");
    	printf("*******************************************************************************\n");
    	printf("                                Choice: ");
    	scanf("%i",&b);
    	printf("*******************************************************************************\n");

        if (b==1)
		{
   			sexor=fopen("data/sectors.dat","w");
			fclose(sexor);
    		counter_sexor=fopen("data/counter_sectors.txt","w");
    		fprintf(counter_sexor,"%i",0);
			fclose(counter_sexor);

			printf("                       (RE)CREATED data/sectors.dat\n");
		}
		
		if (b==2)
		{
   			less=fopen("data/lessons.dat","w");
			fclose(less);
    		counter_less=fopen("data/counter_lessons.txt","w");
    		fprintf(counter_less,"%i",0);
			fclose(counter_less);

			printf("                       (RE)CREATED data/lessons.dat\n");
		}

		if (b==3)
		{
   			stud=fopen("data/students.dat","w");
			fclose(stud);
    		counter_stud=fopen("data/counter_students.txt","w");
    		fprintf(counter_stud,"%i",0);
			fclose(counter_stud);

			printf("                       (RE)CREATED data/students.dat\n");
		}
		
		if (b==4)
		{
            counter_less=fopen("data/counter_lessons.txt","r");
        		fscanf(counter_less,"%i",&j);     //counter_less
     		fclose(counter_less);
     		
     		if (j!=0)
     		{
                counter_sexor=fopen("data/counter_sectors.txt","r");
					fscanf(counter_sexor,"%i%",&jj);  //counter_sexor
				fclose(counter_sexor);

				struct sector sec[jj];

				sexor=fopen("data/sectors.dat","r");
					for (i=0; i<jj; i++)
                	{
						something=fread(&sectram,sizeof(struct sector),1,sexor);
						sec[i]=sectram;
                	}
				fclose(sexor);
				
				int search;
            	printf(" dwse ID tomea %i: ", jj+1); //read apo xrhsth gia euresh
       			scanf("%i", &search);
				
				_Bool flagizard=1;    //elenxos an uparxei
				for (i=0; i<jj; i++)
				{
					if (sec[i].sectorid==search)
					{
						flagizard=0;
					}
				}

				if (flagizard==1)
				{
					sectram.sectorid=search;  //add twn stoixeiwn efoson den pro-uparxei
        			printf(" dwse onoma tomea: ");
					scanf("%s", sectram.sectorname);
					while (strlen(sectram.sectorname)<49)
					{
						strcat(sectram.sectorname," ");
					}
					sectram.sectorname[49]='\0';
					printf(" ------------------------------------------------------\n");

					int z;
					for (z=0; z<5; z++)
					{
                        	sectram.lessor[z].lessonid=0;
					}

    	 			z=0;  //o metrhths ths neas mas eggrafhs
    	 			_Bool flaganistan=1;
    	 			while (flaganistan && z<5)
    	 			{
							system("cls");
							print_lessons (j);
    			 			int lsd;
    			 			printf(" ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^\n");
    			 			printf(" Gia na proxwrhseis se epilogh ID ----------------- 1\n");
    			 			printf(" Gia na stamathseis kai na apo8hkeuseis ----------- 2\n\n");
    			 			printf("*******************************************************************************\n");
    			 			printf(" Choice: ");
				 			scanf("%i", &lsd);
				 			printf("*******************************************************************************\n");

    						if (lsd==1)
    						{
								_Bool flagobios=1;
								int epil;
								while (flagobios)
								{
									flagobios=0;
    								printf(" Choose ID: ");
    								scanf("%i", &epil);
    								for (i=0; i<z; i++)
    								{
										if (epil==sectram.lessor[i].lessonid)
										{
											printf(" to ID tomea uparxei hdh. Dwste ena allo.\n");
											printf(" ------------------------------------------------------\n");
											flagobios=1;
										}
    								}
								}

								_Bool flagafla=1;
    							int i=0;     //ergaleio epanalhpshs gia lessram, asxeto me ton pinaka sectram.lessor[] pou xrhsimopoiw to z
    							less=fopen("data/lessons.dat","r");
    			  				while (i<j && flagafla)
   				  				{
									something=fread(&lessram,sizeof(struct lesson),1,less);
									if (epil==lessram.lessonid)
									{
										sectram.lessor[z].lessonid=lessram.lessonid;   //me z gia na arxisei apo thn arxh pali mias kai einai NEA eggrafh kai oxi antikatastash palias
                     					strcpy(sectram.lessor[z].lessonname,lessram.lessonname);
                    					sectram.lessor[z].weekhours=lessram.weekhours;
                    					sectram.lessor[z].lessonabs=lessram.lessonabs;
                    					sectram.lessor[z].semester=lessram.semester;
                   						strcpy(sectram.lessor[z].semestername,lessram.semestername);
										flagafla=0;
										z++;
										printf("%io ma8hma sthn lista tou tomea.\n",z);
									}
		 		  				i++;
		 		 	 			}
								fclose(less);

								if (flagafla==1)
								{
									printf("\n DEN UPARXEI TO ID POU DWSATE\n");
									printf(" DEN EGINE KATAXWRHSH\n\n");
								}
    						}

							if(lsd==2)
							{
								flaganistan=0;
							}

							if(lsd!=1 && lsd!=2)
							{
								printf(" @@@ WRONG CHOICE @@@\n");
     							printf(" put 1 2\n\n");
							}
							system ("pause");
						}

       					sexor=fopen("data/sectors.dat","a"); //save
           					fwrite(&sectram,sizeof(struct sector),1,sexor);
       					fclose(sexor);

     					jj++;
     					counter_sexor=fopen("data/counter_sectors.txt","w"); //counter+1
        					fprintf(counter_sexor,"%i",jj);
     					fclose(counter_sexor);

						printf("\n APO8HKEYTHKE ME EPITUXIA sto data/sectors.dat\n");
				}else{
					printf("\n UPARXEI HDH AUTO TO ID TOMEA\n");
				}
			}else{
				printf("\n DEN UPARXOUN MA8HMATA DIA8ESIMA WSTE NA PROXWRHSEI H TOMAIOPOIHSH\n");
			}
		}
		
		if (b==5)
     	{
     		counter_less=fopen("data/counter_lessons.txt","r");
        		fscanf(counter_less,"%i",&j); //counter_less
     		fclose(counter_less);

			struct lesson les[j];

            less=fopen("data/lessons.dat","r");
                for (i=0; i<j; i++)
                {
					something=fread(&lessram,sizeof(struct lesson),1,less);
					les[i]=lessram;
                }
			fclose(less);

			int search;
            printf(" dwse ID ma8hmatos %i: ", j+1); //read apo xrhsth gia euresh
       		scanf("%i", &search);

			_Bool flagizard=1;    //elenxos an uparxei
			for (i=0; i<j; i++)
			{
				if (les[i].lessonid==search)
				{
					flagizard=0;
				}
			}

			if (flagizard==1)
			{
				lessram.lessonid=search;  //add twn stoixeiwn efoson den pro-uparxei
       			printf(" dwse onoma ma8hmatos %i: ", j+1);
       			scanf("%s", lessram.lessonname);
       			while (strlen(lessram.lessonname)<39)
				{
					strcat(lessram.lessonname," ");
				}
				lessram.lessonname[39]='\0';
       			printf(" dwse wres ma8hmatos %i: ", j+1);
       			scanf("%i", &lessram.weekhours);
       			printf(" dwse apousies ma8hmatos %i: ", j+1);
       			scanf("%i", &lessram.lessonabs);
       			printf(" dwse e3amino ma8hmatos (ari8mhtika) %i: ", j+1);
       			scanf("%i", &lessram.semester);
       			printf(" dwse e3amhno ma8hmatos (earino/xeimerino) %i: ", j+1);
       			scanf("%s", lessram.semestername);
       			while (strlen(lessram.semestername)<19)
				{
					strcat(lessram.semestername," ");
				}
				lessram.semestername[19]='\0';

       			less=fopen("data/lessons.dat","a"); //save
           			fwrite(&lessram,sizeof(struct lesson),1,less);
       			fclose(less);

     			j++;
     			counter_less=fopen("data/counter_lessons.txt","w"); //counter+1
        			fprintf(counter_less,"%i",j);
     			fclose(counter_less);

				printf("\n APO8HKEYTHKE ME EPITUXIA sto data/lessons.dat\n");
			}else{
				printf("\n UPARXEI HDH AUTO TO ID MA8HMATOS\n");
			}
     	}
		
		if (b==6)
     	{
            counter_sexor=fopen("data/counter_sectors.txt","r");
				fscanf(counter_sexor,"%i%",&jj);
			fclose(counter_sexor);
			
			if (jj!=0)
			{
     			counter_stud=fopen("data/counter_students.txt","r");
        			fscanf(counter_stud,"%i",&jjj); //counter_stud
     			fclose(counter_stud);

				struct student stu[jjj];

           	 	stud=fopen("data/students.dat","r");
               	 	for (i=0; i<jjj; i++)
                	{
						something=fread(&studram,sizeof(struct student),1,stud);
						stu[i]=studram;
                	}
				fclose(stud);

				int search;
    	        printf(" dwse ID ma8hth %i: ", jjj+1); //read apo xrhsth gia euresh
	       		scanf("%i", &search);

				_Bool flagizard=1;    //elenxos an uparxei
				for (i=0; i<jjj; i++)
				{
					if (stu[i].studentid==search)
					{
						flagizard=0;
					}
				}

				if (flagizard==1)
				{
					studram.studentid=search;  //add twn stoixeiwn efoson den pro-uparxei
       				printf(" dwse onoma ma8hth %i: ", jjj+1);
       				scanf("%s", studram.studentFname);
       				while (strlen(studram.studentFname)<29)
					{
						strcat(studram.studentFname," ");
					}
					studram.studentFname[29]='\0';
       				printf(" dwse eponymo ma8hth %i: ", jjj+1);
       				scanf("%s", studram.studentLname);
       				while (strlen(studram.studentLname)<29)
					{
						strcat(studram.studentLname," ");
					}
					studram.studentLname[29]='\0';
       				printf(" ------------------------------------------------------\n");

					print_sectors (jj);

    	 			_Bool flaganistan=1;  //mia epanalhpsh wste na anagkastei o xrhsths na dwsei swsto ID
    	 			while (flaganistan)
    	 			{
						int epil;
    					printf(" Diale3e ID tomea: ");
    					scanf("%i", &epil);

						_Bool flagafla=1;
    					int i=0;     //ergaleio epanalhpshs gia sectram
    					sexor=fopen("data/sectors.dat","r");
    			  		while (i<jj && flagafla)
   				  		{
							something=fread(&sectram,sizeof(struct sector),1,sexor);
							if (epil==sectram.sectorid)
							{
								studram.sectorid=sectram.sectorid;
								int z;
								for (z=0; z<5; z++)
								{
									studram.progress[z].lessonid=sectram.lessor[z].lessonid;
									if (studram.progress[z].lessonid!=0)
									{
										printf("\n Ma8hma me ID %i\n", studram.progress[z].lessonid);
										printf(" ==============================\n");
										printf(" dwse ba8mo: ");
										scanf("%i", &studram.progress[z].grade);
										printf(" dwse apousies: ");
										scanf("%i", &studram.progress[z].absence);
										printf(" ------------------------------------------------------\n\n");
									}
								}
								flagafla=0;
								flaganistan=0;
							}
		 			  	i++;
		 			 	}
						fclose(sexor);

						if (flagafla==1)
						{
							printf("\n DEN UPARXEI TO ID POU DWSATE\n");
							printf(" DEN EGINE KATAXWRHSH\n");
							printf(" ------------------------------------------------------\n");
						}
					}

       				stud=fopen("data/students.dat","a"); //save
           				fwrite(&studram,sizeof(struct student),1,stud);
       				fclose(stud);

     				jjj++;
     				counter_stud=fopen("data/counter_students.txt","w"); //counter+1
        				fprintf(counter_stud,"%i",jjj);
     				fclose(counter_stud);

					printf("\n APO8HKEYTHKE ME EPITUXIA sto data/students.dat\n");
				}else{
					printf("\n UPARXEI HDH AUTO TO ID MA8HTH\n");
				}
			}else{
				printf("\n DEN UPARXOUN TOMEIS GIA NA ENTAXTEI");
			}
     	}
		
		if (b==7)
		{
			counter_sexor=fopen("data/counter_sectors.txt","r");
				fscanf(counter_sexor,"%i%",&jj);
			fclose(counter_sexor);

            if (jj!=0)
            {
               print_sectors (jj);
            }
		}
		
		if (b==8)
    	{
     		counter_less=fopen("data/counter_lessons.txt","r");
       			fscanf(counter_less,"%i",&j); //counter_less
     		fclose(counter_less);

            if (j!=0)
            {
     		   print_lessons(j);
            }
     	}

        if (b==9)
    	{
     		counter_stud=fopen("data/counter_students.txt","r");
       			fscanf(counter_stud,"%i",&jjj); //counter_stud
     		fclose(counter_stud);

            if (jjj!=0)
            {
     		   print_students (jjj);
            }   
     	}

		if (b==10)
		{
     		counter_less=fopen("data/counter_lessons.txt","r");
       			fscanf(counter_less,"%i",&j); //counter_less
     		fclose(counter_less);

     		counter_sexor=fopen("data/counter_sectors.txt","r");
				fscanf(counter_sexor,"%i%",&jj);
			fclose(counter_sexor);

			if (j!=0 && jj!=0)
			{
     			struct sector sec[jj];
				struct lesson les[j];

				print_sectors(jj);

	 			sexor=fopen("data/sectors.dat","r"); //open to sectors
      			for (i=0; i<jj; i++)
         		{
               			something=fread(&sectram,sizeof(struct sector),1,sexor);
               			sec[i]=sectram;
         		}
          		fclose(sexor);
          		
          		less=fopen("data/lessons.dat","r");
                for (i=0; i<j; i++)
                {
						something=fread(&lessram,sizeof(struct lesson),1,less);
						les[i]=lessram;
                }
				fclose(less);

                _Bool flagobios=1;
				int epil;
				while (flagobios)
				{
    				printf(" Diale3te ID pou 8elete na alla3ei: ");
    				scanf("%i", &epil);
    				for (i=0; i<jj; i++)
    				{
						if (epil==sec[i].sectorid)
						{
							flagobios=0;
							sit=i;   //sit einai ena int p dinei thn 8esh p brisketai ston pinaka sec[] auto p allazw
						}
					}
					if (flagobios==1)
					{
							printf("\n To ID tomea pou plhktrologisate den uparxei.\n");
							printf(" ------------------------------------------------------\n");
					}
				}

				_Bool flagerstein=1;
				int a;
     			while (flagerstein)
     			{
					system("color f5");
   	 				printf("*******************************************************************************\n\n");
   					printf("              change sector name ------------------------ 1\n");
   					printf("              change sector lessons --------------------- 2\n");
    				printf("              return to main menu ----------------------- 0\n\n");
    				printf("*******************************************************************************\n");
    				printf("                                Choice: ");
    				scanf("%i",&a);
    				printf("*******************************************************************************\n");

					if (a==1)
					{
                        printf(" dwse onoma tmhmatos: ");
     		    		scanf("%s", sec[sit].sectorname);
     		    		while (strlen(sec[sit].sectorname)<49)
						{
							strcat(sec[sit].sectorname," ");
						}
						sec[sit].sectorname[49]='\0';
     		    		printf(" 8a apo8hkeutei h allagh otan epistrepsete sto menou\n");
						printf("\n ------------------------------------------------------\n");
					}

					if (a==2)
					{
				 		for (i=0; i<5; i++)
       			 		{
							printf(" %ih eggrafh\n", i+1);
							_Bool flagamama=1;
							if (sec[sit].lessor[i].lessonid!=0)
							{
               					printf(" * ID ma8hmatos: %i\n", sec[sit].lessor[i].lessonid);
               					printf(" * onoma ma8hmatos: %s\n", sec[sit].lessor[i].lessonname);
               					printf(" * wres ma8hmatos: %i\n", sec[sit].lessor[i].weekhours);
               					printf(" * apousies ma8hmatos: %i\n", sec[sit].lessor[i].lessonabs);
               					printf(" * e3amhno ma8hmatos: %i\n", sec[sit].lessor[i].semester);
               					printf(" * e3amhno ma8hmatos: %s\n\n", sec[sit].lessor[i].semestername);
							    flagamama=0;
                            }
                            if (flagamama)
                            {
								printf(" * kenh eggrafh\n\n");
							}
		 					printf(" ------------------------------------------------------\n");
						}

							printf(" poia eggrafh 8es na alla3eis (1 2 3 4 5)? ");
							scanf("%i",&n);

						if (n>0 && n<6)
						{
							printf("\n PI8ANA MA8HMATA\n ================\n\n");
							print_lessons(j);

                            _Bool flagin=1;
							while (flagin)
							{
								int search;
                        		printf(" dwse ID ma8hmatos: ");
                        		scanf("%i", &search);
                        		_Bool flagon=1;    //elenxos an uparxei
								for (i=0; i<5; i++)
								{
									if (sec[sit].lessor[i].lessonid==search) //n-1 gt to n pernei apo 1 ws 5 kai meis 8eloume apo 0 ws 4
									{
										flagon=0;
									}
								}

								if (flagon)
								{
                                    sec[sit].lessor[n-1].lessonid=search;
									for (i=0; i<j; i++)
									{
										if (sec[sit].lessor[n-1].lessonid==les[i].lessonid)
										{
											strcpy(sec[sit].lessor[n-1].lessonname,les[i].lessonname);
               								sec[sit].lessor[n-1].weekhours=les[i].weekhours;
            	   							sec[sit].lessor[n-1].lessonabs=les[i].lessonabs;
        	       							sec[sit].lessor[n-1].semester=les[i].semester;
		               						strcpy(sec[sit].lessor[n-1].semestername,les[i].semestername);
	    	           						flagin=0;
										}
									}
									printf(" 8a apo8hkeutei h allagh otan epistrepsete sto menou\n");
									printf("\n ------------------------------------------------------\n");
								}
								if (flagin==1)
								{
									printf(" la8os ID ma8hmatos h' xrhsimopoieitai hdh\n");
									printf("\n ------------------------------------------------------\n");
								}
							}
						}else{
							printf("@@@ la8os epilogh @@@\n");
							printf("\n ------------------------------------------------------\n");
						}
					}

					if (a==0)
					{
						flagerstein=0;
					}

					if (a!=1 && a!=2 && a!=0)
					{
						printf("                            @@@ WRONG CHOICE @@@\n");
						printf("                            viable choices: 0 1 2\n");
					}
				}
				
				counter_sexor=fopen("data/counter_sectors.txt","r"); //anoigoume to counter_sexor gt mporei kapoios allos xrhsths na ekane "add" kati opote to jj na phge+
					fscanf(counter_sexor,"%i%",&jj);
				fclose(counter_sexor);
				
				struct sector isec[jj]; //3anadhlwnetai o pinakas gt mporei kapoios allos xrhsths na ekane "add" kati opote to jj na phge+
				
				sexor=fopen("data/sectors.dat","r"); //kanoume enan pinaka pali sec[] ws isec[] ektws thn 8esh SIT pou htan auth p kaname allagh
      			for (i=0; i<jj; i++)
         		{
               		something=fread(&sectram,sizeof(struct sector),1,sexor);
               		if (i!=sit)
               		{
						isec[i]=sectram;
					}else{
						isec[i]=sec[sit];
					}
         		}
          		fclose(sexor);
				
				sexor=fopen("data/sectors.dat","w"); //en telh 3anagrafoume olo to arxeio me thn nea allagh tou pinaka isec[]
				for (i=0; i<jj; i++)
				{
					fwrite(&isec[i],sizeof(struct sector),1,sexor);
				}
     			fclose(sexor);
     			print_sectors(jj);
     			printf("\n Apo8hkeuthke me epituxia sto data/sectors.dat\n");
     			
			}else{
				printf(" DEN uparxoun apo8hkeumena tmhmata\n\n");
			}
		}

		if (b==11)
		{
     		counter_less=fopen("data/counter_lessons.txt","r");
       			fscanf(counter_less,"%i",&j); //counter_less
     		fclose(counter_less);

			if (j!=0)
			{
				struct lesson les[j];

				print_lessons(j);

          		less=fopen("data/lessons.dat","r");
                for (i=0; i<j; i++)
                {
						something=fread(&lessram,sizeof(struct lesson),1,less);
						les[i]=lessram;
                }
				fclose(less);

                _Bool flagobios=1;
				int epil;
				while (flagobios)
				{
    				printf(" Diale3te ID pou 8elete na alla3ei: ");
    				scanf("%i", &epil);
    				for (i=0; i<j; i++)
    				{
						if (epil==les[i].lessonid)
						{
							flagobios=0;
							sit=i;   //sit einai ena int p dinei thn 8esh p brisketai ston pinaka les[] auto p allazw
						}
					}
					if (flagobios==1)
					{
							printf("\n To ID ma8hmatos pou plhktrologisate den uparxei.\n");
							printf(" ------------------------------------------------------\n");
					}
				}

				_Bool flagerstein=1;
				int a;
     			while (flagerstein)
     			{
					system("color f5");
   	 				printf("*******************************************************************************\n\n");
   					printf("              change lesson name ------------------------ 1\n");
   					printf("              change lesson weekhours ------------------- 2\n");
   					printf("              change lesson absences -------------------- 3\n");
   					printf("              change lesson semester (number)------------ 4\n");
   					printf("              change lesson semester (word) ------------- 5\n");
    				printf("              return to main menu ----------------------- 0\n\n");
    				printf("*******************************************************************************\n");
    				printf("                                Choice: ");
    				scanf("%i",&a);
    				printf("*******************************************************************************\n");
					
					if (a==1)
					{
        				printf(" dwse onoma ma8hmatos: ");
        				scanf("%s", les[sit].lessonname);
        				while (strlen(les[sit].lessonname)<39)
						{
							strcat(les[sit].lessonname," ");
						}
						les[sit].lessonname[39]='\0';
        				printf(" 8a apo8hkeutei h allagh otan epistrepsete sto menou\n");
						printf("\n ------------------------------------------------------\n");
					}

					if (a==2)
					{
						printf(" dwse wres ma8hmatos: ");
        				scanf("%i", &les[sit].weekhours);
        				printf(" 8a apo8hkeutei h allagh otan epistrepsete sto menou\n");
						printf("\n ------------------------------------------------------\n");
					}

					if (a==3)
					{
						printf(" dwse apousies ma8hmatos: ");
        				scanf("%i", &les[sit].lessonabs);
        				printf(" 8a apo8hkeutei h allagh otan epistrepsete sto menou\n");
						printf("\n ------------------------------------------------------\n");
					}
					
					if (a==4)
					{
						printf(" dwse e3amino ma8hmatos (ari8mhtika): ");
        				scanf("%i", &les[sit].semester);
        				printf(" 8a apo8hkeutei h allagh otan epistrepsete sto menou\n");
						printf("\n ------------------------------------------------------\n");
					}
					
					if (a==5)
					{
						printf(" dwse e3amhno ma8hmatos (earino/xeimerino): ");
        				scanf("%s", les[sit].semestername);
        				while (strlen(les[sit].semestername)<19)
						{
							strcat(les[sit].semestername," ");
						}
						les[sit].semestername[19]='\0';
        				printf(" 8a apo8hkeutei h allagh otan epistrepsete sto menou\n");
						printf("\n ------------------------------------------------------\n");
					}
					
					if (a==0)
					{
						flagerstein=0;
					}

					if (a!=1 && a!=2 && a!=3 && a!=4 && a!=5 && a!=0)
					{
						printf("                            @@@ WRONG CHOICE @@@\n");
						printf("                        viable choices: 0 1 2 3 4 5\n");
					}
				}
     			
     			counter_less=fopen("data/counter_lessons.txt","r"); //anoigoume to counter_lessons gt mporei kapoios allos xrhsths na ekane "add" kati opote to j na phge+
					fscanf(counter_less,"%i%",&j);
				fclose(counter_less);

				struct lesson iles[j]; //3anadhlwnetai o pinakas gt mporei kapoios allos xrhsths na ekane "add" kati opote to j na phge+

				less=fopen("data/lessons.dat","r"); //kanoume enan pinaka pali les[] ws iles[] ektws thn 8esh SIT pou htan auth p kaname allagh
      			for (i=0; i<j; i++)
         		{
               		something=fread(&lessram,sizeof(struct lesson),1,less);
               		if (i!=sit)
               		{
						iles[i]=lessram;
					}else{
						iles[i]=les[sit];
					}
         		}
          		fclose(less);
     			
     			less=fopen("data/lessons.dat","w");
				for (i=0; i<j; i++)
				{
					fwrite(&iles[i],sizeof(struct lesson),1,less);
				}
     			fclose(less);
     			print_lessons(j);
     			printf("\n Apo8hkeuthke me epituxia sto data/lessons.dat\n");
     			printf(" ------------------------------------------------------\n");
     			
     			replace_sectors (sit);
     			
			}else{
				printf("DEN uparxoun apo8hkeumena ma8hmata\n\n");
			}
		}

		if (b==12)
		{
            counter_stud=fopen("data/counter_students.txt","r");
        		fscanf(counter_stud,"%i",&jjj); //counter_stud
     		fclose(counter_stud);

            counter_less=fopen("data/counter_lessons.txt","r");
        		fscanf(counter_less,"%i",&j); //counter_lesson
     		fclose(counter_less);

     		counter_sexor=fopen("data/counter_sectors.txt","r");
        		fscanf(counter_sexor,"%i",&jj); //counter_sexor
     		fclose(counter_sexor);

     		struct student stu[jjj];
			struct sector sec[jj];

     		sexor=fopen("data/sectors.dat","r"); //open to sexor
      		if (sexor!=NULL)
      		{
         		for (i=0; i<jj; i++)
         		{
               		something=fread(&sectram,sizeof(struct sector),1,sexor);
               		sec[i]=sectram;
         		}
      		}
     		fclose(sexor);

     		stud=fopen("data/students.dat","r"); //open to stud
      		if (stud!=NULL)
      		{
         		for (i=0; i<jjj; i++)
         		{
               		something=fread(&studram,sizeof(struct student),1,stud);
               		stu[i]=studram;
         		}
      		}
     		fclose(stud);
     		
     		if (j!=0 && jj!=0 && jjj!=0)
     		{
            	print_students (jjj);
            	
            	_Bool flagobios=1;
				int epil;
				while (flagobios)
				{
    				printf(" Diale3te ID pou 8elete na alla3ei: ");
    				scanf("%i", &epil);
    				for (i=0; i<jjj; i++)
    				{
						if (epil==stu[i].studentid)
						{
							flagobios=0;
							sit=i;   //sit einai ena int p dinei thn 8esh p brisketai ston pinaka stu[] auto p allazw
						}
					}
					if (flagobios==1)
					{
							printf("\n To ID ma8hth pou plhktrologisate den uparxei.\n");
							printf(" ------------------------------------------------------\n");
					}
				}
				
				_Bool flagerstein=1;
				int a;
     			while (flagerstein)
     			{
					system("color f5");
   	 				printf("*******************************************************************************\n\n");
   					printf("              change student onoma ---------------------- 1\n");
   					printf("              change student eponymo -------------------- 2\n");
   					printf("              change student sector ID ------------------ 3\n");
	   				printf("              change student grade to a lesson ---------- 4\n");
   					printf("              change student absences to a lesson ------- 5\n");
    				printf("              return to main menu ----------------------- 0\n\n");
    				printf("*******************************************************************************\n");
    				printf("                                Choice: ");
	    			scanf("%i",&a);
    				printf("*******************************************************************************\n");
				    
				    if (a==1)
				    {
                        printf(" dwse onoma ma8hth: ");
        				scanf("%s", stu[sit].studentFname);
        				while (strlen(stu[sit].studentFname)<29)
						{
							strcat(stu[sit].studentFname," ");
						}
						stu[sit].studentFname[29]='\0';
        				printf(" 8a apo8hkeutei h allagh otan epistrepsete sto menou\n");
						printf("\n ------------------------------------------------------\n");
				    }
				    
				    if (a==2)
				    {
                        printf(" dwse eponymo ma8hth: ");
        				scanf("%s", stu[sit].studentLname);
        				while (strlen(stu[sit].studentLname)<29)
						{
							strcat(stu[sit].studentLname," ");
						}
						stu[sit].studentLname[29]='\0';
        				printf(" 8a apo8hkeutei h allagh otan epistrepsete sto menou\n");
						printf("\n ------------------------------------------------------\n");
				    }
				    
				    if (a==3)
				    {
						print_sectors(jj);
						
						_Bool flagizard=1;
						int search;
						while (flagizard)
						{
							printf(" dwse ID tomea: ");
        					scanf("%i", &search);
							for (i=0; i<jj; i++)
							{
								if (sec[i].sectorid==search)
								{
									flagizard=0;
									stu[sit].sectorid=sec[i].sectorid;
								}
							}
							if (flagizard==1)
							{
								printf(" To ID den antistoixei se tomea.\n\n");
								printf(" ------------------------------------------------------\n");
							}
							if (flagizard==0)
							{
								int z;
                                for (z=0; z<5; z++)
								{
									if (stu[sit].progress[z].lessonid!=0)
									{
										printf("\n Ma8hma me ID %i\n", studram.progress[z].lessonid);
										printf(" ==============================\n");
										printf(" dwse ba8mo: ");
										scanf("%i", &stu[sit].progress[z].grade);
										printf(" dwse apousies: ");
										scanf("%i", &stu[sit].progress[z].absence);
										printf(" ------------------------------------------------------\n\n");
									}
								}
                                printf(" 8a apo8hkeutei h allagh otan epistrepsete sto menou\n");
								printf("\n ------------------------------------------------------\n");
							}
						}
				    }
				    
				    if (a==4)
				    {
						something=0;
                        for (i=0; i<5; i++)
       		   			{
							if (stu[sit].progress[i].lessonid!=0 && stu[sit].sectorid!=0)
							{
                                printf(" %ih eggrafh\n", something+1);
               					printf(" * ID ma8hmatos: %i\n", stu[sit].progress[i].lessonid);
               					printf(" * ba8mos ma8hmatos: %i\n", stu[sit].progress[i].grade);
               					something++;
                                printf(" ------------------------------------------------------\n");
							}
						}
						printf("poias eggrafhs ba8mo 8es na alla3eis? ");
						scanf("%i",&n);

						if (n>0 && n<=something)
						{
                            printf(" dwse ba8mo: ");
                            scanf("%i",&stu[sit].progress[n-1].grade); //n-1 gt to n pernei apo 1 ws 5 kai meis 8eloume apo 0 ws 4
                            printf(" 8a apo8hkeutei h allagh otan epistrepsete sto menou\n");
							printf("\n ------------------------------------------------------\n");
						}else{
							printf(" @@@ la8os epilogh @@@\n");
							printf("\n ------------------------------------------------------\n");
						}
					}
				    
				    if (a==5)
				    {
                        something=0;
                        for (i=0; i<5; i++)
       		   			{
							if (stu[sit].progress[i].lessonid!=0 && stu[sit].sectorid!=0)
							{
                                printf(" %ih eggrafh\n", something+1);
               					printf(" * ID ma8hmatos: %i\n", stu[sit].progress[i].lessonid);
               					printf(" * apousies ma8hmatos: %i\n\n", stu[sit].progress[i].absence);
               					something++;
                            	printf(" ------------------------------------------------------\n");
							}
						}
						printf(" poias eggrafhs apousies 8es na alla3eis? ");
						scanf("%i",&n);

						if (n>0 && n<=something)
						{
                            printf(" dwse apousies: ");
                            scanf("%i",&stu[sit].progress[n-1].absence); //n-1 gt to n pernei apo 1 ws 5 kai meis 8eloume apo 0 ws 4
						}else{
							printf(" @@@ la8os epilogh @@@\n");
						}
				    }
				
					if (a==0)
					{
						flagerstein=0;
					}

					if (a!=1 && a!=2 && a!=3 && a!=4 && a!=5 && a!=0)
					{
						printf("                            @@@ WRONG CHOICE @@@\n");
						printf("                        viable choices: 0 1 2 3 4 5\n");
					}
				}
				
				counter_stud=fopen("data/counter_students.txt","r"); //anoigoume to counter_stud gt mporei kapoios allos xrhsths na ekane "add" kati opote to jjj na phge+
					fscanf(counter_stud,"%i%",&jjj);
				fclose(counter_stud);

				struct student istu[jjj]; //3anadhlwnetai o pinakas gt mporei kapoios allos xrhsths na ekane "add" kati opote to jjj na phge+

				stud=fopen("data/students.dat","r"); //kanoume enan pinaka pali stu[] ws istu[] ektws thn 8esh SIT pou htan auth p kaname allagh
      			for (i=0; i<jjj; i++)
         		{
               		something=fread(&studram,sizeof(struct student),1,stud);
               		if (i!=sit)
               		{
						istu[i]=studram;
					}else{
						istu[i]=stu[sit];
					}
         		}
          		fclose(stud);

				stud=fopen("data/students.dat","w");
				for (i=0; i<jjj; i++)
				{
					fwrite(&istu[i],sizeof(struct student),1,stud);
				}
     			fclose(stud);
     			print_students(jjj);
     			printf("\n Apo8hkeuthke me epituxia sto data/students.dat\n");

			}else{
				printf(" DEN uparxoun apo8hkeumenoi ma8htes\n\n");
			}
		}

		if (b==13)
     	{
            counter_stud=fopen("data/counter_students.txt","r");
        		fscanf(counter_stud,"%i",&jjj); //counter_stud
     		fclose(counter_stud);

            counter_less=fopen("data/counter_lessons.txt","r");
        		fscanf(counter_less,"%i",&j); //counter_lesson
     		fclose(counter_less);

     		counter_sexor=fopen("data/counter_sectors.txt","r");
        		fscanf(counter_sexor,"%i",&jj); //counter_sexor
     		fclose(counter_sexor);

     		struct student stu[jjj];
			struct sector sec[jj];
     		struct lesson les[j];

     		sexor=fopen("data/sectors.dat","r"); //open to sexor
      		if (sexor!=NULL)
      		{
         		for (i=0; i<jj; i++)
         		{
               		something=fread(&sectram,sizeof(struct sector),1,sexor);
               		sec[i]=sectram;
         		}
      		}
     		fclose(sexor);

     		stud=fopen("data/students.dat","r"); //open to stud
      		if (stud!=NULL)
      		{
         		for (i=0; i<jjj; i++)
         		{
               		something=fread(&studram,sizeof(struct student),1,stud);
               		stu[i]=studram;
         		}
      		}
     		fclose(stud);

     		less=fopen("data/lessons.dat","r"); //open to less
      		if (less!=NULL)
      		{
         		for (i=0; i<j; i++)
         		{
               		something=fread(&lessram,sizeof(struct lesson),1,less);
               		les[i]=lessram;
        		}
      		}
     		fclose(less);

        	if (j!=0 && jj!=0 && jjj!=0)
			{

 	           print_sectors (jj);

				int deleta;
     			printf("                      poio ID 8es na diagrapseis: "); //&deleta
				scanf("%i", &deleta);

	            _Bool flaganxos=1;
    	        for (i=0; i<jjj; i++)
        	    {
            	        if (deleta==stu[i].sectorid)
                	    {
                           flaganxos=0;                                   
                    	}
	            }
            
    	        if (flaganxos)
        	    {
            	    _Bool flagerstein=1;
					int k=0;
					i=0;
					while (i<jj)
					{
						something=fread(&sec[i],sizeof(struct sector),1,sexor);
						if (deleta==sec[i].sectorid) //ama uparxei to deleta apla agnww thn eggrafh k paw -1 wste na thn pathsw
						{
							flagerstein=0;
						}else{
							sec[k]=sec[i];
							k++;
						}
					i++;
					}

					if (flagerstein==1)
					{
						printf("                            @@@ LA8OS ID @@@\n");
					}

					if (flagerstein==0)
					{
						jj--;
		 				counter_sexor=fopen("data/counter_sectors.txt","w");
         				fprintf(counter_sexor,"%i",jj); //counter jj meiwmeno kata 1 AMA uphrxe to ID
	    	 			fclose(counter_sexor);
	    		 		printf("             DIAGRADHKE ME EPITUXIA apo to data/sectors.dat\n");

						sexor=fopen("data/sectors.dat","w");
						for (i=0; i<jj; i++) //anoigw me "w" to .dat kai grafw ta panta PRIN autou pou afairesa
						{
							fwrite(&sec[i],sizeof(struct sector),1,sexor);
						}
	 		  			fclose(sexor);
    			
						printf("\n APEMEINAN\n =================\n");
						print_sectors (jj);
					}
 	           }else{
    	             printf("\n AUTO TO SECTOR XRHSIMOPOIEITAI APO MA8HTH DEN MPOREI NA DIAGRAFEI\n");
        	   }
            }else{
				printf("\n                       Den uparxei tpt na diagrafei.\n");
			}
   		}

        if (b==14)
     	{
            counter_stud=fopen("data/counter_students.txt","r");
        		fscanf(counter_stud,"%i",&jjj); //counter_stud
     		fclose(counter_stud);

            counter_less=fopen("data/counter_lessons.txt","r");
        		fscanf(counter_less,"%i",&j); //counter_lesson
     		fclose(counter_less);

     		counter_sexor=fopen("data/counter_sectors.txt","r");
        		fscanf(counter_sexor,"%i",&jj); //counter_sexor
     		fclose(counter_sexor);

     		struct student stu[jjj];
			struct sector sec[jj];
     		struct lesson les[j];

     		sexor=fopen("data/sectors.dat","r"); //open to sexor
      		if (sexor!=NULL)
      		{
         		for (i=0; i<jj; i++)
         		{
               		something=fread(&sectram,sizeof(struct sector),1,sexor);
               		sec[i]=sectram;
         		}
      		}
     		fclose(sexor);

     		stud=fopen("data/students.dat","r"); //open to stud
      		if (stud!=NULL)
      		{
         		for (i=0; i<jjj; i++)
         		{
               		something=fread(&studram,sizeof(struct student),1,stud);
               		stu[i]=studram;
         		}
      		}
     		fclose(stud);

     		less=fopen("data/lessons.dat","r"); //open to less
      		if (less!=NULL)
      		{
    	    	for (i=0; i<j; i++)
	        	{
            		something=fread(&lessram,sizeof(struct lesson),1,less);
            		les[i]=lessram;
        		}
      		}
    	 	fclose(less);

			if (j!=0 && jj!=0 && jjj!=0)
			{
 	           print_lessons (j);

				int deleta;
     			printf("                      poio ID 8es na diagrapseis: "); //&deleta
				scanf("%i", &deleta);

				_Bool flaganxos=1;
            	for (i=0; i<jjj; i++)
        	    {
    	            for (n=0; n<5; n++)
 	               {
                    	if (deleta==stu[i].progress[n].lessonid)
                	    {
            	               flaganxos=0;
        	            }
    	            }
	            }

            	if (flaganxos)
            	{
        	        _Bool flagerstein=1;
    	            int k=0;
				    i=0;
			    	while (i<j)
				    {
    					something=fread(&les[i],sizeof(struct lesson),1,less);
	    				if (deleta==les[i].lessonid) //ama uparxei to deleta apla agnww thn eggrafh k paw -1 wste na thn pathsw
			    		{
				    		flagerstein=0;
					    }else{
    						les[k]=les[i];
	    					k++;
		    			}
				    i++;
    				}

		    		if (flagerstein==1)
		    		{
				    	printf("                            @@@ LA8OS ID @@@\n");
    				}
    
		    		if (flagerstein==0)
		    		{
  				    	j--;
					    counter_less=fopen("data/counter_lessons.txt","w");
    	         		fprintf(counter_less,"%i",j); //counter j meiwmeno kata 1 AMA uphrxe to ID
	        	 		fclose(counter_less);
    	     			printf("             DIAGRADHKE ME EPITUXIA apo to data/lessons.dat\n");

			    		less=fopen("data/lessons.dat","w");
					    for (i=0; i<j; i++) //anoigw me "w" to .dat kai grafw ta panta PRIN autou pou afairesa
					    {
				    		fwrite(&les[i],sizeof(struct lesson),1,less);
				    	}
    		    		fclose(less);

			    		printf("\n APEMEINAN\n =================\n");
			    		print_lessons (j);
			    		printf("\n ------------------------------------------------------\n\n");
			    		
			    		delete_from_sectors (deleta);
		    		}
       		    }else{
       	       	   	printf("\n AUTO TO MA8HMA XRHSIMOPOIEITAI KAI DEN MPOREI NA DIAGRAFEI\n");
            	}
            }else{
				printf("\n                       Den uparxei tpt na diagrafei.\n");
			}
    	}

     	if (b==15)
     	{
     		counter_stud=fopen("data/counter_students.txt","r");
        		fscanf(counter_stud,"%i",&jjj); //icounter
     		fclose(counter_stud);

			if (jjj!=0)
			{
 	    		struct student stu[jjj];

	            print_students (jjj);

	     		stud=fopen("data/students.dat","r"); //open to sexor
    	  		if (stud!=NULL)
      			{
         			for (i=0; i<jjj; i++)
         			{
	               		something=fread(&studram,sizeof(struct student),1,stud);
    	           		stu[i]=studram;
        	 		}
      			}
  		   		fclose(stud);

				int deleta;
     			printf("                      poio ID 8es na diagrapseis: "); //&deleta
				scanf("%i", &deleta);
				_Bool flagerstein=1;

				int k=0;
				i=0;
				while (i<jjj)
				{
					something=fread(&stu[i],sizeof(struct student),1,stud);
					if (deleta==stu[i].studentid) //ama uparxei to deleta apla agnww thn eggrafh k paw -1 wste na thn pathsw
					{
						flagerstein=0;
					}else{
						stu[k]=stu[i];
						k++;
					}
				i++;
				}

				if (flagerstein==1)
				{
					printf("                            @@@ LA8OS ID @@@\n");
				}

				if (flagerstein==0)
				{
  	 	 		jjj--;
		 			counter_stud=fopen("data/counter_students.txt","w");
         			fprintf(counter_stud,"%i",jjj); //counter jj meiwmeno kata 1 AMA uphrxe to ID
    		 		fclose(counter_stud);
    		 		printf("             DIAGRADHKE ME EPITUXIA apo to data/students.dat\n");

					stud=fopen("data/students.dat","w");
					for (i=0; i<jjj; i++) //anoigw me "w" to .dat kai grafw ta panta PRIN autou pou afairesa
					{
						fwrite(&stu[i],sizeof(struct student),1,stud);
					}
    				fclose(stud);

					printf("\n APEMEINAN\n =================\n");
					print_students (jjj);
				}
			}else{
				printf("\n                       Den uparxei tpt na diagrafei.\n");
			}
   		}

		if (b==0)
		{
			flagaros=0;
			printf("                       Program Ended Successfully!\n");
		}

		if (b!=0 && b!=1 && b!=2 && b!=3 && b!=4 && b!=5 && b!=6 && b!=7 && b!=8 && b!=9 && b!=10 && b!=11 && b!=12 && b!=13 && b!=14 && b!=15)
		{
			printf("                            @@@ WRONG CHOICE @@@\n");
			printf("        viable choices: 0 1 2 3 4 5 6 7 8 9 10 11 12 13 14 15\n");
		}

	system("pause");
	}
return 0;
}

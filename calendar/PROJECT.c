#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<time.h>
int month(int,int,int);
int leap_year(int);
int age_calculator();
int fest_previousday(int,int,int);
int next_month(int,int,int);
int next_day(int,int,int,int);
int previous_day(int,int,int,int);
int fdays,fday;
int l1=0;
int leap_year(int pyear){
	if(pyear%400==0){
		return 0;
	}
	else if(pyear%100==0){
		return 1;
	}
	else if(pyear%4==0){
		return 0;
	}
	else{
		return 1;
	}
}
int display_date(){
	time_t currentTime;
	time(&currentTime);
	struct tm *mytime=localtime(&currentTime);
	month(mytime->tm_mday,mytime->tm_mon+1,mytime->tm_year+1900);
}
struct reminder{ 
    int dd;
    int mm;
    int yy;
    char text[50];
};
struct reminder r;
int adding_reminder(){
    char text[50];
    char ch[]="yes";
    FILE *fp;
    fp=fopen("Reminder.txt","a"); //Opening of the file Reminder.txt in append mode.
    if(fp==NULL){
        printf("Error opening the file");
        exit(0);
    }
    while(1){
    	if(strcmp(ch,"yes")==0){ //checking whether user wants to add another reminder or not.
    		printf("Enter the date(dd,mm,yy) and Note(50 character max): "); //Taking input of date and text.
    		scanf("%d %d %d %[^\n]",&r.dd,&r.mm,&r.yy,r.text);
			fprintf(fp,"%d %d %d %s\n",r.dd,r.mm,r.yy,r.text);
        	printf("You want to add another reminder(yes or no):");   //Asking user whether wants to add another reminder or not.
        	scanf("%s",ch);
		}
		else{
			break;
		}
    }
	fclose(fp); //closing the file
}
int modifying_reminder(){
    char text[50];
    FILE *fp1;
    fp1=fopen("temp.txt","w");
    FILE *fp;
    int c=0;
    int dd,mm,yy;
    printf("Enter the date(dd,mm,yy):"); 
    scanf("%d %d %d",&dd,&mm,&yy);
    fp=fopen("Reminder.txt","r");  
    if(fp==NULL){
        printf("Error opening the file");
    }
    while(fscanf(fp,"%d %d %d %[^\n]s",&r.dd,&r.mm,&r.yy,r.text)!=EOF){ 
    	if((r.dd == dd) && (r.mm == mm) && (r.yy == yy)){
    		c++;
    	}
    	if((r.dd != dd) || (r.mm != mm) || (r.yy != yy)){
    		fprintf(fp1,"%d %d %d %s\n",r.dd,r.mm,r.yy,r.text);
		}
	}
	if(c==1){
		printf("Enter the date(dd,mm,yy) and text:");
		scanf("%d %d %d %[^\n]s",&r.dd,&r.mm,&r.yy,r.text);
		fprintf(fp1,"%d %d %d %s\n",r.dd,r.mm,r.yy,r.text);
	}
	else if(c==0){
		printf("DATE NOT FOUND!!\n");
	}
	fclose(fp);
	fclose(fp1);
	remove("Reminder.txt");
	rename("temp.txt","Reminder.txt");
}
int deleting_reminder(){
	FILE *ptr1,*ptr2;
	int dd,mm,yy;
	int c=0;
	printf("Enter the date(dd,mm,yy) to delete the reminder:");
	scanf("%d %d %d",&dd,&mm,&yy);
    ptr1=fopen("Reminder.txt","r");
	ptr2=fopen("temp.txt","w");
	rewind(ptr1);
	while(fscanf(ptr1,"%d %d %d %[^\n]s",&r.dd,&r.mm,&r.yy,r.text)!=EOF){
		if((r.dd == dd) && (r.mm == mm) && (r.yy == yy)){
    		c++;
    	}
		if(r.dd !=dd || r.mm!=mm || r.yy!=yy){
			fprintf(ptr2,"%d %d %d %s\n",r.dd,r.mm,r.yy,r.text);
		}
	}
	if(c==0){
		printf("DATE NOT FOUND\n");
	}
    fclose(ptr1);
    fclose(ptr2);
    remove("Reminder.txt");
    rename("temp.txt","Reminder.txt");
}
int add_reminder(){
	int choice;
	while(1){
		printf("1->To add reminder\n2->To modify the reminder\n3->To delete the reminder\n4->To go back\n5->To main menu\nENTER YOUR CHOICE:");
    	scanf("%d",&choice);
		system("clear");
		if(choice==1){
			system("clear");
			adding_reminder();	
		}
		else if(choice==2){
			system("clear");
			modifying_reminder();
		}
		else if(choice==3){
			system("clear");
			deleting_reminder();
		}
		else if(choice==4){
			add_reminder();
			break;
		}
		else if(choice==5){
			break;
		}
	}
}
int get_reminder(){
    FILE *fp;
    int c=0;
    int dd,mm,yy;
    printf("Enter the date to see reminder if any on that date(dd,mm,yy):"); //Taking date as input from user to see reminders if any on that date.
    scanf("%d %d %d",&dd,&mm,&yy);
    month(dd,mm,yy);
    fp=fopen("Reminder.txt","r");  //opening file Reminder.txt in read mode.
    if(fp==NULL){
        printf("Error opening the file");
    }
    while(fscanf(fp,"%d %d %d %[^\n]s",&r.dd,&r.mm,&r.yy,r.text)!=EOF){ //reading the data type specified from file till end of the file.
    	if((r.dd == dd) && (r.mm == mm) && (r.yy == yy)){
    		c++;
    		printf("\n	HERE IS YOUR REMINDER ->%s\n",r.text);  //printing of reminder if present.
			printf("=======================================================\n");
		}
    }
    if(c==0){
    	printf("\n	No reminder today!!.\n");  //no reminder on that date.
		printf("=======================================================\n");
	}
    fclose(fp);
    printf("\n");
}
int reminder(){
	int choice;
	while(1){
		printf("\n1->For adding remider\n2->For getting reminder\n3->To go back\n4->To main menu\nENTER YOUR CHOICE:");
    	scanf("%d",&choice);
		system("clear");
		if(choice==1){
			system("clear");
			add_reminder();	
		}
		else if(choice==2){
			system("clear");
			get_reminder();
		}
		else if(choice==3){
			reminder();
			break;
		}
		else if(choice==4){
			break;
		}
	}
}
int festival_day(){
	struct reminder{ //defining a struct reminder data containing day month and special day text.
    	int dd;
    	int mm;
    	char text[50];
	}r;
	FILE *fp;
	int c=0,dd,mm,yy;
	printf("Enter the date(dd,mm,yy):"); //Taking day, month and year as input from user.
	scanf("%d %d %d",&dd,&mm,&yy);
	month(dd,mm,yy);
	printf("\n");
    fp=fopen("Festivals.txt","r");   //Opening the file Festivals.txt in read mode.
    
    //Note:The file Festivals.txt already contained the data like day month and the special day.
    
    if(fp==NULL){
        printf("Error opening the file");
    }
    while((fscanf(fp,"%d %d %[^\n]s",&r.dd,&r.mm,r.text))!=EOF){ //Reading the specified data type line by line from the file.
    	if(r.dd==dd && r.mm==mm){  //Checking the day and month in file.
    		c++;
    		printf("	SPECIAL DAY IS:%s\n",r.text);  //If day and month are present in the file printing the special day on that date.
			printf("=======================================================\n");		
		}
    }
    if(c==0){
    	printf("	NOTHING SPECIAL TODAY :(\n"); //If not found printing the message that there is no special day on the date given.
		printf("=======================================================\n");
	}
	fclose(fp);
    printf("\n");
}
int fest_week_day(int day,int month,int year){
	struct reminder{ 
    	int dd;
    	int mm;
    	char text[50];
	}r;
	FILE *fp;
	int c=0;
    fp=fopen("Festivals.txt","r");
    if(fp==NULL){
        printf("Error opening the file");
    }
    while((fscanf(fp,"%d %d %[^\n]s",&r.dd,&r.mm,r.text))!=EOF){ 
    	if(r.dd==day && r.mm==month){
    		c++;
    		printf("Today is a special day %d and it is:%s\n",r.dd,r.text);	
		}
    }
	fclose(fp);
}
int festival_week(){
	int dd,mm,yy,f2,fcs,l2=0,l1=0;
	printf("Enter the date(dd,mm,yy):");
	scanf("%d %d %d",&dd,&mm,&yy);
	int f1[]={1,4,4,0,2,5,0,3,6,1,4,6};
	for(int i=0;i<12;i++){
		if(mm==i+1){
			f2=f1[i];
		}
	}
	int fcen=yy/100;
	int fcsum[]={6,4,2,0,6,4,2,0,6,4,2,0,6,4,2,0,6,4,2,0,6,4,2,0};
	for(int j=0;j<23;j++){
		if(fcen==j){
			fcs=fcsum[j];
		}
	}
	int fysum=(yy-(fcen*100));
	int sum=0;
	sum+=dd+f2+fcs+fysum+(fysum/4);
	int day=sum%7;
	int fweek[]={1,2,3,4,5,6,0};
	for(int i=0;i<7;i++){
		if(day==fweek[i]){
			fday=i;
		}
	}
	if(mm<1 || mm>12 ){
		l2+=1;
	}
	if(mm==4 || mm==6 || mm==9 || mm==11){
		fdays=30;
		if(dd>30){
			l2+=1;
		}
	}
	else if((mm==2) || (mm==1)){
		int res=leap_year(yy);
		if(res==0){
			if(mm==2){
				fdays=29;
			}
			else{
				fdays=31;
			}
			l1+=1;
		}
		else if(res==1){
			if(mm==2){
				fdays=28;
			}
			else{
				fdays=31;
			}
			if(mm==2 && dd>=29){
				l2+=1;
			}
		}
	}
	else if(mm==3 || mm==5 || mm==7 || mm==8 || mm==10 || mm==12){
		fdays=31;
	}
	if(l1==1){
		if(fday==0){
			fday=6;
		}
		else{
			fday-=1;
		}
	}
	if(l2!=1){
		if(fday==0){
			fest_week_day(dd,mm,yy);
			next_day(0,dd,mm,yy);
		}
		else if(fday==1){
			previous_day(0,dd,mm,yy);
			fest_week_day(dd,mm,yy);
			next_day(1,dd,mm,yy);
		}
		else if(fday==2){
			previous_day(-1,dd,mm,yy);
			fest_week_day(dd,mm,yy);
			next_day(2,dd,mm,yy);
		}
		else if(fday==3){
			previous_day(-2,dd,mm,yy);
			fest_week_day(dd,mm,yy);
			next_day(3,dd,mm,yy);
		}
		else if(fday==4){
			previous_day(-3,dd,mm,yy);
			fest_week_day(dd,mm,yy);
			next_day(4,dd,mm,yy);
		}
		else if(fday==5){
			previous_day(-4,dd,mm,yy);
			fest_week_day(dd,mm,yy);
			next_day(5,dd,mm,yy);
		}
		else if(fday==6){
			previous_day(-5,dd,mm,yy);
			fest_week_day(dd,mm,yy);
		}
	}
	else{
		printf("You've entered wrong date.");
	}
}
int next_day(int count,int dd,int mm,int yy){
	do{
		count++;
		if(mm==2){
			if(((dd<28)&&(l1==1)) || ((dd<29)&&(l1==0))){
				dd+=1;
			}
			else if(((dd==28)&&(l1==1)) || ((dd==29) && (l1==0))){
				dd=1;
				mm=3;
			}
		}
		else if(fdays==30){
			if(dd<30){
				dd+=1;
			}
			else if(dd==30){
				dd=1;
				mm+=1;
			}
		}
		else if(fdays==31){
			if(fday<31){
				dd+=1;
			}
			else if(dd==31 && mm!=12){
				dd=1;
				mm+=1;
			}
			else if(dd==31 && mm==12){
				dd=1;
				mm=1;
				yy+=1;
			}
		}
	fest_week_day(dd,mm,yy);
	}while(count<6);
}
int previous_day(int i,int dd,int mm,int yy){
	do{
		i++;
		int leap=leap_year(yy);
		if(leap==0){
			if(mm==2 && dd<=29){
				dd-=1;
			}
			if(mm==3 && dd==1){
				dd=29;
				mm-=1;
			}
		}
		else if(leap==1){
			if(mm==2 && dd<=28){
				dd-=1;
			}
			if(mm==3){
				if(dd==1){
					dd=28;
					mm-=1;
				}
				else if(dd<=31){
					dd-=1;
				}
			}
		}
		if(mm==1){
			if(dd==1){
				dd=31;
				mm=12;
				yy-=1;
			}
			else if(dd<31){
				dd-=1;
			}
		}
		else if(mm==4 || mm==6 || mm==9 || mm==11){
			if(dd==1){
				dd=31;
				mm-=1;
			}
			else if(dd<=30){
				dd-=1;
			}
		}
		else if(mm==5 || mm==7 || mm==10 || mm==12){
			if(dd==1){
				dd=30;
				mm-=1;
			}
			else if(dd<=31){
				dd-=1;
			}
		}
		else if(mm==8){
			if(dd==1){
				dd=31;
				mm-=1;
			}
			else if(dd<=31){
				dd-=1;
			}
		}
	fest_week_day(dd,mm,yy);
	}while(i<=0);
}
int festival_month(){
    FILE *fp1;
	int c1=0,mm1;
	printf("Enter the month to see festivals in that month(mm):"); //Taking input of month from the user.
	scanf("%d",&mm1);
    fp1=fopen("Festivals.txt","r");   //Opening the file in read mode.
    if(fp1==NULL){
        printf("Error opening the file");
    }
    printf("\n");
    while((fscanf(fp1,"%d %d %[^\n]s",&r.dd,&r.mm,r.text))!=EOF){
    	if(r.mm==mm1){       //If month is there are not in the file
    		c1++;
    		printf("Today is a special day %d and it is:%s\n",r.dd,r.text);   //If month is found printing the special day in that month.	
		}
    }
    if(c1==0){
    	printf("No special days.\n");  //If month not found printing a message of no special days in the month given.
	}
    fclose(fp1);
    printf("\n");
}
int festival(){
	int choice;
	while(1){
		printf("\n1->For special day\n2->For special days in a week\n3->For special days in a month\n4->To go back\n5->To main menu\nENTER YOUR CHOICE:");
    	scanf("%d",&choice);
		system("clear");
		if(choice==1){
			system("clear");
			festival_day();	
		}
		else if(choice==2){
			system("clear");
			festival_week();
		}
		else if(choice==3){
			system("clear");
			festival_month();
		}
		else if(choice==4){
			festival();
			break;
		}
		else if(choice==5){
			break;
		}
	}
}
int calculating_age(){
	int choice;
	while(1){
		printf("\n1->For calculating age\n2->To main menu\nENTER YOUR CHOICE:");
		scanf("%d",&choice);
		system("clear");
		if(choice==1){
			system("clear");
			age_calculator();
		}
		else if(choice==2){
			break;
		}
	}	
}
int age_calculator(){
	int pday,pmonth,pyear,days;
	printf("Enter the present date format-DD-MM-YY :"); 
	scanf("%d %d %d",&pday,&pmonth,&pyear);
	int day,month,year;
	printf("Enter the date of birth format-DD-MM-YY:"); 
	scanf("%d %d %d",&day,&month,&year);
	int l2=0;
	if(pmonth<1 || pmonth>12 || month<1 || month>12){ 
		l2+=1;
	}
	if(pmonth==4 || pmonth==6 || pmonth==9 || pmonth==11){ 
		if(pday>30){  
			l2+=1;
		}
		days=30;
	}
	else if((pmonth==2) || (month==2)){    
		if((pyear%400==0) || (year%400==0)){
			days=29;
		}
		else if((pyear%100==0) || (year%100==0)){
			days=28;
			if(pday>=29 || day>=29){ 
				l2+=1;
			}
		}
		else if((pyear%4==0) || (year%4==0)){
			days=29;
		}
		else{
			days=28;
			if((pday>=29) || (day>=29)){ 
				l2+=1;
			}
		}
	}
	else{
		days=31;
	}
	if(pyear<year){
		printf("Cant find the age.\n");
	}
	else if(l2!=1){
		if(((pmonth<month) && (pday<day)) || ((pmonth==month) && (pday<day))){
			pyear-=1;
			pday+=31;
			pmonth+=11;
			printf("You are %d years %d months %d days old.\n",(pyear-year),(pmonth-month),(pday-day));
		}
		else if((pmonth<month)&&(pday>=day)){
			pmonth+=12;
			pyear-=1;
			printf("You are %d years %d months %d days old.\n",(pyear-year),(pmonth-month),(pday-day));
		}
		else if(((pmonth==month)&&(pday>=day)) || ((pmonth>month) && (pday>=day))){
			printf("You are %d years %d months %d days old.\n",(pyear-year),(pmonth-month),(pday-day));	
		}
		else if((pmonth>month)&&(pday<day)){
			pday+=days;
			pmonth-=1;
			printf("You are %d years %d months %d days old.\n",(pyear-year),(pmonth-month),(pday-day));
		}
	}
	else{
		printf("You've entered wrong date\n");
	}
}
int nextbirthday(){
	int bpday,bpmonth,pyear,days;
	printf("Enter the present date format-DD-MM-YY :"); 
	scanf("%d %d %d",&bpday,&bpmonth,&pyear);
	int bday,bmonth,year;
	printf("Enter the date of birth format-DD-MM-YY:"); 
	scanf("%d %d %d",&bday,&bmonth,&year);
	printf("\n");
	int l2=0;
	if(bpmonth<1 || bpmonth>12 || bmonth<1 || bmonth>12){ 
		l2+=1;
	}
	if(bpmonth==4 || bpmonth==6 || bpmonth==9 || bpmonth==11){ 
		if(bpday>30){  
			l2+=1;
		}
		days=30;
	}
	else if((bpmonth==2) || (bmonth==2)){    
		if((pyear%400==0) || (year%400==0)){
			days=29;
		}
		else if((pyear%100==0) || (year%100==0)){
			days=28;
			if(bpday>=29 || bday>=29){ 
				l2+=1;
			}
		}
		else if((pyear%4==0) || (year%4==0)){
			days=29;
		}
		else{
			days=28;
			if((bpday>=29) || (bday>=29)){ 
				l2+=1;
			}
		}
	}
	else{
		days=31;
	}
	year=pyear+1;
	if(l2!=1){
		if(((bpmonth>bmonth) && (bpday>bday)) || ((bmonth==bpmonth) && (bpday>bday))){
			bday+=31;
			bmonth+=11;
			printf("Next birthday is in  %d months %d days\n",(bmonth-bpmonth),(bday-bpday));
		}
		else if((bpmonth>bmonth)&&(bpday<=bday)){
			bmonth+=12;
			printf("Next birthday is in  %d months %d days\n",(bmonth-bpmonth),(bday-bpday));
		}
		else if(((bpmonth==bmonth)&&(bpday<bday)) || ((bpmonth<bmonth) && (bpday<=bday))){
			printf("Next birthday is in  %d months %d days\n",(bmonth-bpmonth),(bday-bpday));	
		}
		else if((bpmonth<bmonth)&&(bpday>bday)){
			bday+=days;
			bmonth-=1;
			printf("Next birthday is in  %d months %d days\n",(bmonth-bpmonth),(bday-bpday));
		}
		else if(((bmonth-bpmonth)==0)&&((bday-bpday)==0)){
			printf("Next birthday is in  1 year.\n");
		}
	}
	else{
		printf("can't find next birthday\n");
	}
	printf("\n");
}
int next_birthday(){
	int choice;
	while(1){
		printf("\n1->For next birthday calculator\n2->To main menu\nENTER YOUR CHOICE:");
		scanf("%d",&choice);
		system("clear");
		if(choice==1){
			system("clear");
			nextbirthday();
		}
		else if(choice==2){
			break;
		}
	}	
}
int pday,pmonth,pyear,prevmonth,prevday,prevyear,nextday,nextmonth,nextyear;
int previous_month(int prevday,int prevmonth,int prevyear){
	if(pmonth==1){
		pmonth=12;
		pyear-=1;
	}
	else{
		pmonth-=1;
	}
	int leap=leap_year(pyear);
	if(leap==0){
		if(pmonth==2){
			pday=29;
		}
	}
	else if(leap==1){
		if(pmonth==2){
			pday=28;
		}
	}
	if(pmonth==4 || pmonth==6 || pmonth==9 || pmonth==11){
		pday=30;
	}
	else if(pmonth==3 || pmonth==5 || pmonth==7 || pmonth==8 || pmonth==10 || pmonth==12){
		pday=31;
	}
	prevday=pday;
	prevmonth=pmonth;
	prevyear=pyear;
	month(prevday,prevmonth,prevyear);
	return 0;
}
int next_month(int nextday,int nextmonth,int nextyear){
	if(pmonth==12){
		pmonth=1;
		pyear+=1;
	}
	else{
		pmonth+=1;
	}
	int leap1=leap_year(pyear);
	if(leap1==0){
		if(pmonth==2){
			pday=29;
		}
	}
	else if(leap1==1){
		if(pmonth==2){
			pday=28;
		}
	}
	if(pmonth==4 || pmonth==6 || pmonth==9 || pmonth==11){
		pday=30;
	}
	else if(pmonth==3 || pmonth==5 || pmonth==7 || pmonth==8 || pmonth==10 || pmonth==12){
		pday=31;
	}
	nextday=pday;
	nextmonth=pmonth;
	nextyear=pyear;
	month(nextday,nextmonth,nextyear);
	return 0;
}
int month(int pday,int pmonth,int pyear){
	int l2=0,c1=0,l1=0,m2,days,day1,c;
	int p1day=1;
	int m1[]={1,4,4,0,2,5,0,3,6,1,4,6};
	for(int i=0;i<12;i++){
		if(pmonth==i+1){
			m2=m1[i];
		}
	}
	int cen=pyear/100;
	int cs;
	int csum[]={6,4,2,0,6,4,2,0,6,4,2,0,6,4,2,0,6,4,2,0,6,4,2,0};
	for(int j=0;j<23;j++){
		if(cen==j){
			cs=csum[j];
		}
	}
	int ysum=(pyear-(cen*100));
	int sum=0;
	sum+=p1day+m2+cs+ysum+(ysum/4);
	int day=sum%7;
	if(pmonth<1 || pmonth>12 ){
		l2+=1;
	}
	if(pmonth==4 || pmonth==6 || pmonth==9 || pmonth==11){
		days=30;
		if(pday>30){
			l2+=1;
		}
	}
	else if((pmonth==2) || (pmonth==1)){
		int res=leap_year(pyear);
		if(res==0){
			if(pmonth==2){
				days=29;
			}
			else{
				days=31;
			}
			l1+=1;
		}
		else if(res==1){
			if(pmonth==2){
				days=28;
			}
			else{
				days=31;
			}
			if(pmonth==2 && pday>=29){
				l2+=1;
			}
		}
	}
	else if(pmonth==3 || pmonth==5 || pmonth==7 || pmonth==8 || pmonth==10 || pmonth==12){
		days=31;
	}
	if(l1==1){
		if(day==0){
			day=6;
		}
		else{
			day-=1;
		}
	}
	int c3;
	int week[]={1,2,3,4,5,6,0};
	for(int i=0;i<7;i++){
		if(day==week[i]){
			c3=i;
			c=7-i;
		}
	}
	int c2=c;
	int week1[]={1,2,3,4,5,6,0};
	if(day==0){
		day1=7;
	}
	else{
		day1=day;
	}
	if(l2!=1){
		printf("=======================================================\n");
	switch(pmonth){
        case 1: printf("			January,%d				\n",pyear);
		 break;
        case 2: printf("			February,%d				\n",pyear);
		 break;
        case 3: printf("			March,%d				\n",pyear);
		 break;
        case 4: printf("			April,%d				\n",pyear);
		 break;
        case 5: printf("			May,%d				\n",pyear); 
		break;
        case 6: printf("			June,%d				\n",pyear);
		 break;
        case 7: printf("			July,%d				\n",pyear);
		 break;
        case 8: printf("			August,%d				\n",pyear);
		 break;
        case 9: printf("			September,%d				\n",pyear);
		 break;
        case 10: printf("			October,%d				\n",pyear);
		 break;
        case 11: printf("			November,%d				\n",pyear);
		 break;
        case 12: printf("			December,%d				\n",pyear); 
		break;
    }
    printf("=======================================================\n");
		printf("sun	mon	tue	wed	thu	fri	sat\n");
		for(int j=1;j<day1;j++){
			printf("	");
		}
		for(int i=1;i<=days;i++){
			c1++;
			if(i==pday){
				printf("<%d>	",i);
			}
			else if(i!=pday){
				printf("%d	",i);
			}
			if(((c1==c))||((i-c2)==7)){
				c2=i;
				printf("\n");
			}
		}
		printf("\n=======================================================\n");
		printf("=======================================================");
	}
	else{
		printf("You've entered wrong date\n");
		printf("=======================================================\n");
	}
}
int jump_to_date(){
	printf("Enter the  date you want to get format(DD-MM-YY):");
	scanf("%d %d %d",&pday,&pmonth,&pyear);
	printf("\n");
	month(pday,pmonth,pyear);
	int choice;
	while(1){
		printf("\n1->For previous month\n2->For next month\n3->To quit\nENTER YOUR CHOICE:");
    	scanf("%d",&choice);
		system("clear");
		if(choice==1){
			system("clear");
			previous_month(pday,pmonth,pyear);	
		}
		else if(choice==2){
			system("clear");
			next_month(pday,pmonth,pyear);	
		}
		else if(choice==3){
			break;
		}
	}
}
int main(){
    while(1){
    	display_date();
    	int choice;
       	printf("\n1)JUMP TO DATE\n2)FOR ADDING/ACCESSING REMINDER\n3)FOR FESTIVALS\n4)FOR AGE CALCULATOR\n5)FOR NEXT BIRTHDAY CALCULATOR\n6)To exit\nEnter your choice:");
        scanf("%d",&choice);
        switch(choice){
        case 1:
        	system("clear");
        	jump_to_date();
        	break;
        case 2:
        	system("clear");
        	reminder();
        	break;
        case 3:
        	system("clear");
        	festival();
        	break;
       	case 4:
       		system("clear");
       		calculating_age();
       		break;
       	case 5:
       		system("clear");
       		next_birthday();
       		break;
       	case 6:
       		exit(0);
       	default:
       		printf("Please enter valid choice.\n");
        }
    }
}

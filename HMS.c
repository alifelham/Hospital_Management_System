/*
  Hospital Management System 1.0
  Created by:Alif Elham Khan
  Feel free to use and share. Together we can beat Covid-19.*/

#include<stdio.h>
#include<string.h>
#include<windows.h>
#include<conio.h>
#include<ctype.h>
#include<time.h>

struct patient
{
    int id;
    int doc;
    char name[20];
    char cell[20];
};

struct emergency
{
    int id;
    char name[20];
    char cell[20];
};

struct admin
{
    int id;
    char name[20];
    char password[20];
    int status;
};

struct doctor
{
    int id;
    char name[20];
    int serial;
    char field[20];
    char cell[20];
};

struct Medicine  ///Apurbo
{
    int id,price,quantity;
    char medicneName[100],Company[100],Mfg_Date[11],Exp_Date[11],info[5000];
} m[100];
void PurchaseMedicine(int number);
void EnterInfoAboutMedicine(int number);
void StockOfMedicine(int number);
void KnowInfoAboutMedicine(int number);
void AddMedicineinStore(int number,struct Medicine m[]);
void DeleteMedicineStore(int number);
void ChangeMedicineDetails(int number);  ///Apurbo

struct emergency emg[30];
struct patient pat[30];
struct doctor doc[30];
struct admin ad[30];

int user,current_id=-1;
FILE *rPat,*wPat, *rDoc,*wDoc,*rAdm,*wAdm,*rEmg,*wEmg,*aRec;
char name[20], pass[20];

void Load(int a)
{
    if(a == 1)
    {
        int i, lines = count(a);
        rEmg = fopen("emergency.txt","r");

        for(i=1; i<=lines; i++)
        {
            fscanf(rEmg,"%d %s %s",&emg[i].id,&emg[i].name,&emg[i].cell);
        }
        //printf("\nUpdated!\n\n");
        fclose(rEmg);
    }

    if(a == 2)
    {
        int i, lines = count(a);
        rPat = fopen("appointment.txt","r");

        for(i=1; i<=lines; i++)
        {
            fscanf(rPat,"%d %s %s %d",&pat[i].id,&pat[i].name,&pat[i].cell,&pat[i].doc);
        }
        //printf("\nUpdated!\n\n");
        fclose(rPat);
    }

    else if(a == 3)
    {
        int i, lines = count(a);
        rAdm = fopen("admin.txt","r");

        for(i=1; i<=lines; i++)
        {
            fscanf(rAdm,"%d %s %s %d",&ad[i].id, &ad[i].name, &ad[i].password, &ad[i].status);
        }
        //printf("\nUpdated!\n\n");
        fclose(rAdm);
    }

    else if(a == 4)
    {
        int i, lines = count(a);
        rDoc = fopen("doctors.txt","r");

        for(i=1; i<=lines; i++)
        {
            fscanf(rDoc,"%d %s %s %s",&doc[i].id,&doc[i].name,&doc[i].cell,&doc[i].field);
        }
        //printf("\nUpdated!\n\n");
        fclose(rDoc);
    }
}

void Registration(int a)
{
    int ser, dctr, zr = 0;
    if(a == 1)
    {
        wEmg = fopen("emergency.txt","a");

        user = count(a)+1;

        printf("Enter Username: ");
        scanf("%s",emg[user].name);

        printf("Enter Contact Number: ");
        scanf("%s",emg[user].cell);


        emg[user].id = user;

        fprintf(wEmg,"%d %s %s\n",user,emg[user].name,emg[user].cell);
        printf("\nDear %s, Thank you for the information! Your serial: %d\n\n",emg[user].name,user);

        fclose(wEmg);
        Load(a);
    }

    else if(a == 2)
    {
        wPat = fopen("appointment.txt","a");

        user = count(a)+1;

        printf("Enter Username: ");
        scanf("%s",pat[user].name);

        printf("Enter Contact Number: ");
        scanf("%s",pat[user].cell);

        printf("Doctor of choice: ");
        scanf("%d",&pat[user].doc);
        dctr = pat[user].doc;
        ser = serial(dctr);
        doc[dctr].serial = ser;

        pat[user].id = user;

        fprintf(wPat,"%d %s %s %d\n",user,pat[user].name,pat[user].cell, pat[user].doc);
        printf("\nDear %s, Thank you for the information! Your serial: %d\n\n",pat[user].name,ser+1);

        fclose(wPat);
        Load(a);
    }

    else if(a == 3)
    {
        wAdm = fopen("admin.txt","a");

        user = count(a)+1;

        printf("Enter Name: ");
        scanf("%s", ad[user].name);

        printf("Enter Password: ");
        scanf("%s",ad[user].password);


        ad[user].id = user;

        fprintf(wAdm,"%d %s %s %d\n",user, ad[user].name, ad[user].password, zr);
        printf("\nPending Approval\n\n");

        fclose(wAdm);
        Load(a);
    }

    else if(a == 4)
    {
        wDoc = fopen("doctors.txt","a");

        user = count(a)+1;

        printf("Enter Doctor's Name: ");
        scanf("%s", doc[user].name);

        printf("Enter Contact Number: ");
        scanf("%s",doc[user].cell);

        printf("Field: ");
        scanf("%s",doc[user].field);

        //ser = serial(user);
        //doc[user].serial = ser;

        doc[user].id = user;

        fprintf(wDoc,"%d %s %s %s\n",user, doc[user].name, doc[user].cell, doc[user].field);
        printf("\nThank you for the information! Dr. %s registered!\n\n",doc[user].name);

        fclose(wDoc);
        Load(a);
    }
}


void show(int a)
{
    Load(a);

    int i;
    int total = count(a);
    if(a == 1) //for displaying emergency.txt
    {
        printf("\n\nID\tName\tContact No.\n");
        for(i=1; i<=total; i++)
        {
            printf("%d\t%s\t%s\n",emg[i].id, emg[i].name, emg[i].cell);
        }
    }
    if(a == 2) //for displaying appointment.txt
    {
        printf("\n\nID\tName\tContact\t\tDoctor Requested\n");
        for(i=1; i<=total; i++)
        {
            printf("%d\t%s\t%s\t%d\n",pat[i].id,pat[i].name,pat[i].cell,pat[i].doc);
        }
    }
    if(a == 4) //for displaying doctors.txt
    {
        printf("\n\nID\tName\tContact\t\tField\tSerial\n");
        for(i=1; i<=total; i++)
        {
            doc[i].serial = serial(i);
            printf("%d\t%s\t%s\t%s\t%d\n",doc[i].id,doc[i].name,doc[i].cell,doc[i].field,doc[i].serial);
        }
    }
}

int serial(int a)
{
    int i, lines = count(2), cnt = 0;
    //lines variable set to number of lines counted from patients' appointment.txt file

    rPat = fopen("appointment.txt","r");

    for(i=1; i<=lines; i++) //loop runs for all of the pending patients of every doctor
    {
        //the patients' list is read and values are passed to structure objects
        fscanf(rPat,"%d %s %s %d",&pat[i].id,&pat[i].name,&pat[i].cell,&pat[i].doc);
        if(pat[i].doc == a) ++cnt; //if requested doctor matches with request of others then cnt is incremented
    }

    return cnt;
}

void copyFile()
{
   char ch, source_file[20], target_file[20];

   rPat = fopen("appointment.txt", "r");
   aRec = fopen("record.txt", "a");

   time_t t;
   time(&t);
   fprintf(aRec,"\n Recorded: %s \n", ctime(&t));
   fprintf(aRec,"------------------------------\n");
   while( ( ch = fgetc(rPat) ) != EOF )
      fputc(ch, aRec);

   printf("\nRecord updated successfully!");

   fclose(rPat);
   fclose(aRec);
}

int Login()
{
    int i, total = count(3), c=1, end;

    //user inputs name and password
    printf("Enter Username: ");
    scanf("%s",name);

    printf("Enter Password: ");
    scanf("%s",pass);

    Load(3);

    //checks name of each ID and if it matches then that ID is set as current ID
    for(i=1; i<=total; i++)
    {
        if(strcmp(ad[i].name, name)==0)
        {
            current_id = ad[i].id;
            break;
        }
    }

    //checks if name of current ID exactly matches entered name
    if(strcmp(ad[current_id].name,name)==0)
    {
        //checks if password of current ID exactly matches entered password
        if(strcmp(ad[current_id].password,pass)==0)
        {
            //checks if status of current ID is 1 (Approved) or 0 (Pending Approval)
            if(ad[current_id].status == 1) //status has been set to 1
            {
                printf("\n\nWelcome %s, Login successful!\n\n",name);
            }
            else //status is still 0
            {
                printf("\n\nRegistration Pending Approval..\n\n");
                c = 0;
            }
        }
        else //password does not match
        {
            printf("\nWrong Password! Try Again!\n\n");
            Login();
        }
    }
    else //name does not match with an approved name
    {
        printf("\nUser does not exist\n\n");
        printf("press #0 to Exit\n");
        printf("press #1 to register\n");
        printf("press #2 to Try Again\n");

        c = 0;
        scanf("%d", &end); //return menu/ exit screen
        while(end!=0 && end!=1 && end!=2)
        {
            printf("Please enter a valid option\n");
            scanf("%d", &end);
        }
        if(end == 0) return c; //exits login
        else if(end == 1) Registration(3); //prompts admin registration session
        else Login(); //prompts another login session

    }
    return c;
}

int count(int a) //counts number of user entries
{
    if(a == 1) //for emergency patients
    {
        char ch;
        int lines = 0;
        rEmg = fopen("emergency.txt","r"); //opens txt file in read mode
        while(!feof(rEmg)) //loop runs till end of file
        {
            ch = fgetc(rEmg);
            if(ch == '\n') //for every new line found the line variable increments
            {
                ++lines;
            }
        }
        fclose(rEmg);
        return lines;
    }

    else if(a == 2) //for patients' appointment list
    {
        char ch;
        int lines = 0;
        rPat = fopen("appointment.txt","r");
        while(!feof(rPat)) //loop runs till end of file
        {
            ch = fgetc(rPat);
            if(ch == '\n') //for every new line found the line variable increments
            {
                ++lines;
            }
        }
        fclose(rPat);
        return lines;
    }

    else if(a == 3) //for admin list
    {
        char ch;
        int lines = 0;
        rAdm = fopen("admin.txt","r");
        while(!feof(rAdm)) //loop runs till end of file
        {
            ch = fgetc(rAdm);
            if(ch == '\n') //for every new line found the line variable increments
            {
                ++lines;
            }
        }
        fclose(rAdm);
        return lines;
    }

    else if(a == 4) //for doctors' list
    {
        char ch;
        int lines = 0;
        rDoc = fopen("doctors.txt","r");
        while(!feof(rDoc)) //loop runs till end of file
        {
            ch = fgetc(rDoc);
            if(ch == '\n') //for every new line found the line variable increments
            {
                ++lines;
            }
        }
        fclose(rDoc);
        return lines;
    }
}

int main()
{
    printf("................................\n");
    printf("** Welcome to HMS Version 1.0  **\n");
    printf("** Released on June, 2020      **\n");
    printf("** Created by: Alif Elham Khan **\n");
    printf("................................\n");

    system("color 74"); //cmd bg color set to gray and text to red
    while(1)
    {
        int n=-1,p=-1,emg=-1, end=-1, app=-1, cov=-1, logst=-1, admi=-1, ad=-1, con=-1;

        //Initial option screen
        time_t t;
        time(&t);
        printf("\n\n%s", ctime(&t));
        printf("-------------------------");
        printf("\n\nPress the desired option:\n");
        printf("-------------------------\n");
        printf(" #1 Patient's Corner\n");
        printf(" #2 Admin Panel\n");
        printf(" #3 Contact Us\n");
        //printf(" #4 Pharmacy\n");
        printf(" #4 Clear Screen\n");
        printf(" #0 Exit\n");

        scanf("%d", &n);
        while(n!=0 && n!=1 && n!=2 && n!=3 && n!=4 && n!=5)
        {
            printf("[!]Please enter a valid option\n");
            scanf("%d", &n);
        }

        if( n == 4)
        {
        system("cls");
        }
        if(n == 0)
        {
            printf(" ----------------------------------\n");
            printf("| Thank you for using my software! |\n| Regards, Alif Elham\t\t   |\n");
            printf(" ----------------------------------\n");
            break;
        }
        //Patient's Corner
        if(n == 1)
        {
            printf("\n\nPress the desired option:\n");
            printf("-------------------------\n");
            printf(" #1 Emergency\n");
            printf(" #2 Covid-19\n");
            printf(" #3 Doctor's Appointment\n");
            //printf(" #4 Admit Patient\n");

            scanf("%d", &p);
            while(p!=1 && p!=2 && p!=3 && p!=4)
            {
                printf("[!]Please enter a valid option\n");
                scanf("%d", &p);
            }

            switch(p)
            {
            case 1:
            {
                printf("\n\n--- Emergency Unit! ---\n");
                printf("------------------------\n\n");
                printf("Press the desired option:\n");
                printf("-------------------------\n");
                printf(" #1 Request Ambulance\n");
                printf(" #2 Emergency Visit\n");

                scanf("%d", &emg);
                while(emg!=1 && emg!=2)
                {
                    printf("[!]Please enter a valid option\n");
                    scanf("%d", &emg);
                }

                if(emg==1) //call an ambulance
                {
                    printf("\n\n-- Ambulance Service --\n");
                    printf("------------------------\n\n");
                    printf(" Contact Hotline-1: 1234\n");
                    printf(" Contact Hotline-2: 1256\n");
                    printf(" Contact Hotline-3: 1278\n");

                    //prompt exit / return menu
                    printf("\n\n Press #0 to Exit program\n");
                    printf(" Press #1 to return to Main Menu\n");
                    scanf("%d", &end);
                    while(end!=0 && end!=1)
                    {
                        printf("Please enter a valid option\n");
                        scanf("%d", &end);
                    }
                    if(end == 0)
                    {
                        printf(" ----------------------------------\n");
                        printf("| Thank you for using my software! |\n| Regards, Alif Elham\t\t   |\n");
                        printf(" ----------------------------------\n");
                        return 0;
                    }
                    else continue;
                }

                else
                {
                    printf("\n\nGet an emergency serial:\n");
                    printf("------------------------\n\n");
                    Registration(1);

                    //prompt exit / return menu
                    printf("\n\nPress #0 to Exit program\n");
                    printf("Press #1 to return to Main Menu\n");
                    scanf("%d", &end);
                    while(end!=0 && end!=1)
                    {
                        printf("[!]Please enter a valid option\n");
                        scanf("%d", &end);
                    }
                    if(end == 0)
                    {
                        printf(" ----------------------------------\n");
                        printf("| Thank you for using my software! |\n| Regards, Alif Elham\t\t   |\n");
                        printf(" ----------------------------------\n");
                        return 0;
                    }
                    else continue;
                }

            }

            case 2:
            {
                printf("\n\n---Covid-19---\n\n");
                printf("Press the desired option:\n");
                printf("-------------------------\n");
                printf(" #1 Get latest updates\n");
                printf(" #2 Get tested near you\n");

                scanf("%d", &cov);
                while(cov!=1 && cov!=2)
                {
                    printf("[!]Please enter a valid option\n");
                    scanf("%d", &cov);
                }

                if(cov == 1)
                {
                    //opens worldometer's website
                    system("explorer https://www.worldometers.info/coronavirus/country/bangladesh/");
                    printf("\n Launched in your browser!\n");
                }
                else if(cov == 2)
                {
                    //opens IEDRC's website
                    system("explorer https://www.iedcr.gov.bd/index.php/component/content/article/73-ncov-2019");
                    printf("\n Launched in your browser! \n");
                }

                //prompt exit / return menu
                printf("\n\n Press #0 to Exit program\n");
                printf(" Press #1 to return to Main Menu\n");
                scanf("%d", &end);
                while(end!=0 && end!=1)
                {
                    printf("[!]Please enter a valid option\n");
                    scanf("%d", &end);
                }
                if(end == 0)
                {
                    printf(" ----------------------------------\n");
                    printf("| Thank you for using my software! |\n| Regards, Alif Elham\t\t   |\n");
                    printf(" ----------------------------------\n");
                    return 0;
                }
                else continue;
            }

            case 3: //Book an appointment
            {
                printf("\n\n-- Get Doctor's Appointment --\n");
                printf("-------------------------------\n\n");
                printf("Press the desired option:\n");
                printf("-------------------------\n");
                printf(" #1 Check Available Doctors\n");
                printf(" #2 Book an appointment\n");

                scanf("%d", &app);
                while(app!=1 && app!=2)
                {
                    printf("[!]Please enter a valid option\n");
                    scanf("%d", &app);
                }

                if(app==1)
                {
                    printf("\n\n-- Doctors Available --\n");
                    printf("------------------------");
                    show(4);

                    printf("\n\nDo you want to book an appointment?\n");
                    printf(" Press #0 for No\n");
                    printf(" Press #1 for Yes\n");
                    scanf("%d", &end);
                    while(end!=0 && end!=1)
                    {
                        printf("Please enter a valid option\n");
                        scanf("%d", &end);
                    }
                    if(end == 1) Registration(2);

                    //prompt exit / return menu
                    printf("\n\n Press #0 to Exit program\n");
                    printf(" Press #1 to return to Main Menu\n");
                    scanf("%d", &end);
                    while(end!=0 && end!=1)
                    {
                        printf("[!]Please enter a valid option\n");
                        scanf("%d", &end);
                    }
                    if(end == 0)
                    {
                        printf(" ----------------------------------\n");
                        printf("| Thank you for using my software! |\n| Regards, Alif Elham\t\t   |\n");
                        printf(" ----------------------------------\n");
                        return 0;
                    }

                    else continue;
                }

                else
                {
                    printf("\n\nGet an appointment with a Doctor:\n");
                    printf("--------------------------------------\n");
                    Registration(2);

                    //prompt exit / return menu
                    printf("\n\n Press #0 to Exit program\n");
                    printf(" Press #1 to return to Main Menu\n");
                    scanf("%d", &end);
                    while(end!=0 && end!=1)
                    {
                        printf("[!]Please enter a valid option\n");
                        scanf("%d", &end);
                    }
                    if(end == 0)
                    {
                        printf(" ----------------------------------\n");
                        printf("| Thank you for using my software! |\n| Regards, Alif Elham\t\t   |\n");
                        printf(" ----------------------------------\n");
                        return 0;
                    }
                    else continue;
                }
            }

            }
        }

        //Admin Panel
        if(n == 2)
        {
            printf("Press the desired option:\n");
            printf("-------------------------\n");
            printf(" #1 Login\n");
            printf(" #2 Register\n");

            scanf("%d", &ad);
            while(ad!=1 && ad!=2)
            {
                printf("[!]Please enter a valid option\n");
                scanf("%d", &ad);
            }

            if(ad==1)
            {
                logst = Login();
                if(logst == 1)
                {
                    while(1)
                    {
                        printf("Press the desired option:\n");
                        printf("-------------------------\n");
                        printf(" #1 Register a doctor\n");
                        printf(" #2 Show patients\n");
                        printf(" #3 Show emergency patients\n");
                        printf(" #4 Show doctors\n");
                        printf(" #5 Update patient records\n");
                        printf(" #6 Clear patient serials\n");

                        scanf("%d", &admi);
                        while(admi!=1 && admi!=2 && admi!=3 && admi!=4 && admi!=5 && admi!=6)
                        {
                            printf("[!]Please enter a valid option\n");
                            scanf("%d", &admi);
                        }

                        if(admi==1)
                        {
                            Registration(4);
                        }

                        else if(admi==2)
                        {
                            show(2);
                        }

                        else if(admi==3)
                        {
                            show(1);
                        }

                        else if(admi==4)
                        {
                            show(4);
                        }

                        else if(admi==5)
                        {
                            copyFile();
                        }

                        else if(admi==6)
                        {
                            fclose(fopen("appointment.txt", "w"));
                            printf("\n Patient serials cleared!\n");
                        }

                        //prompt exit / return menu
                        printf("\n\n Press #0 to Exit program\n");
                        printf(" Press #1 to return to Main Menu\n");
                        printf(" Press #2 to return to Admin Panel\n");
                        scanf("%d", &end);
                        while(end!=0 && end!=1 && end!=2)
                        {
                            printf("[!]Please enter a valid option\n");
                            scanf("%d", &end);
                        }
                        if(end == 0)
                        {
                            printf(" ----------------------------------\n");
                            printf("| Thank you for using my software! |\n| Regards, Alif Elham\t\t   |\n");
                            printf(" ----------------------------------\n");
                            return 0;
                        }
                        else if(end == 1) break;
                        else continue;
                    }
                }

                else if(logst == 0 || logst == 2)
                {
                    printf("Try again later");
                }

                else
                {
                    printf("Login Failed!");
                }
            }

            else if(ad==2)
            {
                Registration(3);
            }
        }

        if(n == 3)
        {
            printf("\n\nPress the desired option:\n");
            printf("-------------------------\n");
            printf(" #1 Email Us\n");
            printf(" #2 Call Us\n");
            printf(" #3 Visit Website\n");

            scanf("%d", &con);
            while(con!=1 && con!=2 && con!=3)
            {
                printf("[!]Please enter a valid option\n");
                scanf("%d", &con);
            }


            if(con == 1)
            {
                system("explorer https://www.google.com/gmail/about/#");
                printf("\n Launched in your browser!\n");
            }

            if(con == 2)
            {
                system("explorer https://hangouts.google.com/");
                printf("\n Launched in your browser!\n");
            }

            if(con == 3)
            {
                system("explorer https://github.com/alifelham");
                printf("\n Launched in your browser!\n");
            }
        }
    }
}


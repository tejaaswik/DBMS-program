#include<stdio.h>
#include<stdlib.h>
struct employee
{
 int id;
 char name[20];
 float ranking;
}emp;
                                //    FUNCTION TO INSERT RECORDS TO THE FILE
void insert()
{
 FILE *fp;
 fp = fopen("Record", "a");
 printf("Enter the id   :");
 scanf("%d", &emp.id);
 printf("Enter the Name      :");
 scanf("%s",emp.name);
 printf("Enter the ranking      :");
 scanf("%f", &emp.ranking);
 fwrite(&emp, sizeof(emp), 1, fp);
 fclose(fp);
}
                              //    FUNCTION TO DISPLAY RECORDS
void disp()
{
 FILE *fp1;
 fp1 = fopen("Record", "r");
 printf("\nRoll Number\tName\tranking\n\n");
 while (fread(&emp, sizeof(emp), 1, fp1))
 printf("  %d\t\t%s\t%.2f\n", emp.id, emp.name, emp.ranking);
 fclose(fp1);
}
int roll(int rno)
{
 FILE *fp;
 int c = 0;
 fp = fopen("Record", "r");
 while (!feof(fp))
 {
  fread(&emp, sizeof(emp), 1, fp);

  if (rno == emp.id)
  {
   fclose(fp);
   return 1;
  }
 }
 fclose(fp);
 return 0;
}
                              //    FUNCTION TO SEARCH THE GIVEN RECORD
void search()
{
 FILE *fp2;
 int r, s, temp;
 printf("\nEnter the id you want to search  :");
 scanf("%d", &r);
 temp = roll(r);
 if (temp == 0)
  printf("id %d is not available in the file\n",r);
 else
 {
  fp2 = fopen("Record", "r");
  while (fread(&emp, sizeof(emp), 1, fp2))
  {
   s = emp.id;
   if (s == r)
   {
    printf("\nid = %d", emp.id);
    printf("\nName    = %s", emp.name);
    printf("\nranking    = %.2f\n", emp.ranking);
   }
  }
  fclose(fp2);
 }
}
                             

                                    //    FUNCTION TO DELETE A RECORD

void deletefile()
{
 FILE *fpo;
 FILE *fpt;
 int r, s;
 printf("Enter the id you want to delete :");
 scanf("%d", &r);
 if (roll(r) == 0)
  printf("id %d is not available in the file\n", r);
 else
 {
  fpo = fopen("Record", "r");
  fpt = fopen("TempFile", "w");
  while (fread(&emp, sizeof(emp), 1, fpo))
  {
   s = emp.id;
   if (s != r)
    fwrite(&emp, sizeof(emp), 1, fpt);
  }
  fclose(fpo);
  fclose(fpt);
  fpo = fopen("Record", "w");
  fpt = fopen("TempFile", "r");
  while (fread(&emp, sizeof(emp), 1, fpt))
   fwrite(&emp, sizeof(emp), 1, fpo);
  printf("\nRECORD DELETED\n");
  fclose(fpo);
  fclose(fpt);
 }

}
                              //    FUNCTION TO UPDATE THE RECORD
void update()
{
 int temp;
 FILE *fpt;
 FILE *fpo;
 int s, r, ch;
 printf("Enter roll number to update:");
 scanf("%d", &r);
 temp = roll(r);
 if (temp == 0)
 {
  printf("Roll number %d is not Available in the file", r);
 }
 else
 {
  fpo = fopen("Record", "r");
  fpt = fopen("TempFile", "w");
  while (fread(&emp, sizeof(emp), 1, fpo))
  {
   s = emp.id;
   if (s != r)
    fwrite(&emp, sizeof(emp), 1, fpt);
   else
   {
    printf("\n\t1. Update Name of Roll Number %d", r);
    printf("\n\t2. Update ranking of Roll Number %d", r);
    printf("\n\t3. Update both Name and ranking of Roll Number %d", r);
    printf("\nEnter your choice:");
    scanf("%d", &ch);
    switch (ch)
    {
    case 1:
     printf("Enter Name:");
     scanf("%s",emp.name);
     break;
    case 2:
     printf("Enter ranking : ");
     scanf("%f", &emp.ranking);
     break;
    case 3:
     printf("Enter Name: ");
     scanf("%s",emp.name);
     printf("Enter ranking: ");
     scanf("%f", &emp.ranking);
     break;
    default:
     printf("Invalid Selection");
     break;
    }
    fwrite(&emp, sizeof(emp), 1, fpt);
   }
  }
  fclose(fpo);
  fclose(fpt);
  fpo = fopen("Record", "w");
  fpt = fopen("TempFile", "r");
  while (fread(&emp, sizeof(emp), 1, fpt))
  {
   fwrite(&emp, sizeof(emp), 1, fpo);
  }
  fclose(fpo);
  fclose(fpt);
  printf("RECORD UPDATED");
 }
}

           

                              //FUNCTION TO CHECK THE FILE IS EMPTY OR NOT
int empty()
{
 int c = 0;
 FILE *fp;
 fp = fopen("Record", "r");
 while (fread(&emp, sizeof(emp), 1, fp))
  c = 1;
 fclose(fp);
 return c;
}
                               // MAIN PROGRAM
void main()
{
 int c, emp;
 do
 {
  printf("\n\t---Select your choice---------\n");
  printf("\n\t1. INSERT\n\t2. DISPLAY\n\t3. SEARCH");
  printf("\n\t4. DELETE\n\t5. UPDATE\n\t");
  printf("\n\t6. EXIT");
  printf("\n\n------------------------------------------\n");
  printf("\nEnter your choice:");
  scanf("%d", &c);
  printf("\n");
  switch (c)
  {
  case 1:
   insert();
   break;
  case 2:
   emp = empty();
   if (emp == 0)
    printf("\nThe file is EMPTY\n");
   else
    disp();
   break;
  case 3:
   search();
   break;
  case 4:
   deletefile();
   break;
  case 5:
   update();
   break;
  case 6:
   exit(1);
   break;
  default:
   printf("\nYour choice is wrong\nPlease try again...\n");
   break;

  }
 } while (c != 6);
}

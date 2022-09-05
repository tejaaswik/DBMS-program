#include<stdio.h>
#include<stdlib.h>
struct student
{
 int rollno;
 char name[20];
 float mark;
}std;
                                //    FUNCTION TO INSERT RECORDS TO THE FILE
void insert()
{
 FILE *fp;
 fp = fopen("Record", "a");
 printf("Enter the Roll no   :");
 scanf("%d", &std.rollno);
 printf("Enter the Name      :");
 scanf("%s",std.name);
 printf("Enter the mark      :");
 scanf("%f", &std.mark);
 fwrite(&std, sizeof(std), 1, fp);
 fclose(fp);
}
                              //    FUNCTION TO DISPLAY RECORDS
void disp()
{
 FILE *fp1;
 fp1 = fopen("Record", "r");
 printf("\nRoll Number\tName\tMark\n\n");
 while (fread(&std, sizeof(std), 1, fp1))
 printf("  %d\t\t%s\t%.2f\n", std.rollno, std.name, std.mark);
 fclose(fp1);
}
int roll(int rno)
{
 FILE *fp;
 int c = 0;
 fp = fopen("Record", "r");
 while (!feof(fp))
 {
  fread(&std, sizeof(std), 1, fp);

  if (rno == std.rollno)
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
 printf("\nEnter the Roll no you want to search  :");
 scanf("%d", &r);
 temp = roll(r);
 if (temp == 0)
  printf("Roll No %d is not available in the file\n",r);
 else
 {
  fp2 = fopen("Record", "r");
  while (fread(&std, sizeof(std), 1, fp2))
  {
   s = std.rollno;
   if (s == r)
   {
    printf("\nRoll no = %d", std.rollno);
    printf("\nName    = %s", std.name);
    printf("\nMark    = %.2f\n", std.mark);
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
 printf("Enter the Roll no you want to delete :");
 scanf("%d", &r);
 if (roll(r) == 0)
  printf("Roll no %d is not available in the file\n", r);
 else
 {
  fpo = fopen("Record", "r");
  fpt = fopen("TempFile", "w");
  while (fread(&std, sizeof(std), 1, fpo))
  {
   s = std.rollno;
   if (s != r)
    fwrite(&std, sizeof(std), 1, fpt);
  }
  fclose(fpo);
  fclose(fpt);
  fpo = fopen("Record", "w");
  fpt = fopen("TempFile", "r");
  while (fread(&std, sizeof(std), 1, fpt))
   fwrite(&std, sizeof(std), 1, fpo);
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
  while (fread(&std, sizeof(std), 1, fpo))
  {
   s = std.rollno;
   if (s != r)
    fwrite(&std, sizeof(std), 1, fpt);
   else
   {
    printf("\n\t1. Update Name of Roll Number %d", r);
    printf("\n\t2. Update Mark of Roll Number %d", r);
    printf("\n\t3. Update both Name and Mark of Roll Number %d", r);
    printf("\nEnter your choice:");
    scanf("%d", &ch);
    switch (ch)
    {
    case 1:
     printf("Enter Name:");
     scanf("%s",std.name);
     break;
    case 2:
     printf("Enter Mark : ");
     scanf("%f", &std.mark);
     break;
    case 3:
     printf("Enter Name: ");
     scanf("%s",std.name);
     printf("Enter Mark: ");
     scanf("%f", &std.mark);
     break;
    default:
     printf("Invalid Selection");
     break;
    }
    fwrite(&std, sizeof(std), 1, fpt);
   }
  }
  fclose(fpo);
  fclose(fpt);
  fpo = fopen("Record", "w");
  fpt = fopen("TempFile", "r");
  while (fread(&std, sizeof(std), 1, fpt))
  {
   fwrite(&std, sizeof(std), 1, fpo);
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
 while (fread(&std, sizeof(std), 1, fp))
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


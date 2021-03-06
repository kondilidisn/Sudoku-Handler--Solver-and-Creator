#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

// This function implements "Print Menu" and "Get Valid Answer from User" actions
int show_menu()
 {
     char answer,error=0;
     do
     {
         system("cls");
         if(error)
         {
             printf("Invalid answer, please choose again!\n");
             system("pause");
         }
         error=0;
         printf("1. Load Sudoku\n2. Save Sudoku\n3. Clear Sudoku\n4. Create Sudoku\n5. Create Sudoku Automatically\n6. Modify Sudoku\n7. Solve Sudoku (By the user)\n8. Solve Sudoku Automatically\n9. Exit\n");
         fflush(stdin);
         scanf("%c",&answer);
         if(answer!='1' && answer!='2' && answer!='3' && answer!='4' && answer!='5' && answer!='6' &&answer!='7' && answer!='8' && answer!='9')
         {
             error=1;
         }
     }while(error);
     return answer;
 }


// This function implements a copy of "strcpy" function
 void copy_Sudoku(char to_Sudoku[], char from_Sudoku[])
 {
     char i;
     for(i=0;i<90;i++)
     {
         to_Sudoku[i]=from_Sudoku[i];
     }
 }

// This function checks if a specific cell violates any of Sudoku Rules
 int box_has_error(char Sudoku[], int position)
 {
     if(Sudoku[position]=='0')
     {
         return 0;
     }
     int i,j,col,raw;
     col=position%10;
     raw=position/10;
     // Singularity in raw
     for(i=0;i<9;i++)
     {
         if(col!=i && Sudoku[raw*10 + i]==Sudoku[position])
         {
             return 1;
         }
     }
     // Singularity in column
     for(i=0;i<9;i++)
     {
         if(raw!=i && Sudoku[i*10 + col]==Sudoku[position])
         {
             return 1;
         }
     }
     // Singularity in 3x3 block
     // Let in be noted that my block is in (raw-raw%3) raw of blocks and (col - col%3) column of blocks
     // for every raw in the block
     for(i=0;i<3;i++)
     {
         // for every column in the block
         for(j=0;j<3;j++)
         {
             // checking all 9 cells of the block
             // Let it also be noted that the first cell of the block can be found in the position Sudoku[(raw -raw%3)*10 + col -col%3]
             // and that the rest of the cells can be found in : Sudoku[(raw - raw%3 + i)*10 + col -col%3 + j]
             if((raw!=(raw -raw%3 + i)) && (col!=(col - col%3 + j)) && (Sudoku[position]==Sudoku[(raw -raw%3 + i)*10 + col - col%3 + j]))
             {
                 return 1;
             }
         }
     }
     return 0;
 }

// This function print Sudoku table in a better interface using ASCII characters
void print_Sudoku(char Sudoku[])
{
    char i,j;
    printf("%c%c%c%c%c%c%c%c%c%c%c%c%c\n",218,196,196,196,194,196,196,196,194,196,196,196,191);//prwth seira sxediaframatos pinaka
    for(i=0;i<9;i++)
    {
        if(i!=0 && i%3==0)
        {
            printf("%c%c%c%c%c%c%c%c%c%c%c%c%c\n",195,196,196,196,197,196,196,196,197,196,196,196,180);
        }
        for(j=0;j<10;j++)
        {
            if(j%3==0)
            {
                printf("%c",179);
            }
            // If my cell is '0' then I print ' ' (space)
            if(Sudoku[i*10+j]!='0')
            {
                printf("%c",Sudoku[i*10+j]);
            }
            else
            {
                printf(" ");
            }
        }
    }
    printf("%c%c%c%c%c%c%c%c%c%c%c%c%c\n",192,196,196,196,193,196,196,196,193,196,196,196,217);
}

// This function implements load sudoku from file function
void load_Sudoku(char Sudoku[])
{
    char answer;
    char filename[22],fullname[40];
    char i;
    FILE *file;
    do{
        strcpy(fullname,"sudoku_samples/");
        system("cls");
        fflush(stdin);
        printf("Please give the name of the file you want to load\nwhich can be found in 'sudoku_samples' folder, next to this program.\nDo not insert file extension ('.sud') !\n");
        scanf("%s",&filename);
        strcat(fullname,filename);
        strcat(fullname,".sud");
        file=fopen(fullname,"r+"); //  "r+" is used so that it will not be created in case it won't be found
        if(file==NULL)
        {
            printf("The file %s could not be found in 'sudoku_samples' folder.\nPlease insert filename again.\n",filename);
            system("pause");
        }
    }while(file==NULL);
    for(i=0;i<90;i++)
    {
        fscanf(file,"%c",&Sudoku[i]);
    }
    fclose(file);
    printf("The file : %s has been loaded succesfully!\n",filename);
    system("pause");
    system("cls");
}

// This function implements "Save Sudoku to file" function
 void save_Sudoku(char Sudoku[])
 {
    char filename[22],fullname[40];
    char i;
    char answer;
    char flag;
    FILE *file;

    //creating folder in order to be sure that exists
    #ifdef __linux__
        mkdir("sudoku_samples", 777);
    #else
        _mkdir("sudoku_samples");
    #endif


    do{
        flag=0;
        strcpy(fullname,"sudoku_samples/");
        system("cls");
        fflush(stdin);
        printf("Please insert the filename in which you want to store\ncurrent Sudoku.\nIt will be created in 'Sudoku_samples' folder.\nDo not add the file extension ('.sud') !\n");
        scanf("%s",&filename);
        strcat(fullname,filename);
        strcat(fullname,".sud");
        file=fopen(fullname,"r"); //checking if file already exists
        if(file!=NULL)
        {
            fclose(file);
            printf("File %s already exists, do you want to replace it?\nIf so, press 'y' or 'Y', in any other case, you will be asced for a new name.\n",filename);
            fflush(stdin);
            scanf("%c",&answer);
            if(answer!='y' && answer!='Y')
            {
                flag=1;
            }
        }
    }while(flag); // loopipng until user chooses to overide file or to give a new name
    file=fopen(fullname,"w+");
    for(i=0;i<90;i++)
    {
        fprintf(file,"%c",Sudoku[i]);
    }
    fclose(file);
    printf("Current Sudoku has been saved to file by the name %s succesfully\n",filename);
    system("pause");
    system("cls");
 }

// This Function clears current sudoku
 void erase_Sudoku(char Sudoku[])
 {
     int i,j;
     for(i=0;i<9;i++)
     {
         for(j=0;j<9;j++)
         {
             Sudoku[i*10+j]='0';
         }
         Sudoku[i*10+j]='\n';
     }
 }

// This function implements lets the user to give a Sudoku table by command line
 void hand_create_Sudoku(char Sudoku[])
 {
     int i,j;
     char line[20];  // temporary table that stores raws given by user
     char error;
     erase_Sudoku(Sudoku); // To begin with I clear my Sudoku table
     for(i=0;i<9;i++)
     {
         error=0;
         do
         {
             // In case of Sudoku rule violation, I clear the raw
             for(j=0;j<9;j++)
             {
                 Sudoku[i*10 + j]='0';
             }
             system("cls");
             print_Sudoku(Sudoku);
             if(error)
             {
                 printf("There was a Sudoku violation in the last raw that was inserted.\n");
             }
             error=0;
             printf("Please insert again the %dth raw, the numbers sould be inserted continuously.\nNote that 0 represents ' ' (Space).",i+1);
             fflush(stdin);
             scanf("%s",&line);
             //checking the total nuber of given digits
             if(strlen(line)!=9)
             {
                 error=1;
             }
             //checking if any character was given
             j=0;
             while(j<9 && !error)
             {
                 if(line[j]>'9' || line[j]<'0')
                 {
                     error=1;
                 }
                 j++;
             }
             //checking all non-empty cells for Sudoku violations
             j=0;
             while(j<9 && !error)
             {
                 if(line[j]!='0')
                 {
                     Sudoku[i*10+j]=line[j];
                     if(box_has_error(Sudoku,i*10+j))
                     {
                         error=1;
                     }
                 }
                 j++;
             }
         }while(error);
     }
     printf("Sudoku was succesfully inserted.\nIt will be now used as current.\n");
     system("pause");
     system("cls");
 }

// This function implements "Modify Sudoku" function
 void handle_Sudoku(char Sudoku[])
 {
     char col,raw,num,i,j,error1,error2,answer;
     char temp_Sudoku[91];
     copy_Sudoku(temp_Sudoku,Sudoku);
     //while user chooses to modify another cell :
     do
     {
         error1=0;
         //checking for valid insertion
         do
         {
             system("cls");
             print_Sudoku(temp_Sudoku);
             if(error1)
             {
                 printf("The parameters you enter are invalid, please insert again.\nRaws and Columns between (1-9), but Numbers between (0-9)\n");
             }
             error1=0;
             fflush(stdin);
             printf("Please insert specify the cell you want to modify.\nGive the number of raw, the number of column and the number to be inserted IN THAT ORDER\nFor example insert: '9 8 1'\nif you want to enter number 1 in the 9th raw and 8th column.\n");
             scanf("%d %d %c",&raw,&col,&num);
             if(raw>9 || raw<1 || col>9 || col<1 || num>'9' || num<'0')
             {
                 error1=1;
             }
         }while(error1);
      temp_Sudoku[(raw-1)*10+col-1]=num;
      system("cls");
      print_Sudoku(temp_Sudoku);
      printf("Do you want to modify another cell?\nPress 'y' or 'Y' if so.\n");
      fflush(stdin);
      scanf("%c",&answer);
     }while(answer=='y' || answer=='Y');
     // After that I check for Sudoku violation in the whole Sudoku table
     error1=0;
     i=0;
     do
     {
         j=0;
         while(j<9 && !error1)
         {
             if(box_has_error(temp_Sudoku, i*10 +j))
             {
                 error1=1;
                 raw=i+1;
                 col=j+1;
             }
             j++;
         }
         i++;
     }while(i<9 && !error1);
     // If there is an error or more, I ask the user whether he/she wants to keep the initial Sudoku table
     answer='o';
     if(error1)
     {
         print_Sudoku(temp_Sudoku);
         printf("Current Sudoku has at least one error in the cell with coordinates:\nraw:%d\ncolumn:%d\nDo you want to keep the Sudoku as it was before the modifications?\nPress 'y' h 'Y' to keep the old one or anything else to keep current.\n",raw,col);
         fflush(stdin);
         scanf("%c",&answer);
     }
     if(answer!='y' && answer!='Y')
     {
         copy_Sudoku(Sudoku,temp_Sudoku);
         printf("You succesfully replaced the old Sudoku.\n");
     }
     else
     {
         printf("You chose to keep the old Sudoku.\n");
     }
 }

// This function implements the "Solve Sudoku (By the user)" function
 void hand_solve_Sudoku(char Sudoku[])
 {
     char col=0,raw=0,num,answerc,error1,error2,num_of_0;
     num_of_0=0;
     //checking if table is full
     do
     {
         do
         {
             if(Sudoku[raw*10 + col]=='0')
             {
                 num_of_0++;
             }
             col++;
         }while(col<9 && num_of_0==0);
         raw++;
     }while(raw<9 && num_of_0==0);
     //If it is not full
     if(num_of_0!=0)
     {
         do
         {
             error1=0;
             error2=0;
             //checking whether the user tries to alter already filled cell
             do
             {
                 system("cls");
                 if(error2)
                 {
                     printf("To pedio pou dialeksate den einai adeio...\nParakalw ksanadialekste pedio\n");
                 }
                 error2=0;
                 //checking for correct input
                 do
                 {
                     system("cls");
                     print_Sudoku(Sudoku);
                     if(error1)
                     {
                         printf("The parameters you inserted are invalid, please insert again raw or column (1-9).\n");
                     }
                     error1=0;
                     printf("Please insert raw and column number");
                     fflush(stdin);
                     scanf("%d %d",&raw,&col);
                     if(raw>9 || raw<1 || col>9 || col<1)
                     {
                         error1=1;
                     }
                 }while(error1);
                 error1=0;
                 if(Sudoku[(raw-1)*10 + col -1]!='0')
                 {
                     error2=1;
                 }
             }while(error2);
             //now that the cell is specified he can make as many changes as he/she wants
             do
             {
                 error2=0;
                 do
                 {
                     system("cls");
                     print_Sudoku(Sudoku);
                     if(error2)
                     {
                         printf("Please insert a number between 0 and 9!\n");
                     }
                     error2=0;
                     fflush(stdin);
                     printf("Please insert the number to be inserted in the cell with coordinates:%d,%d\n",raw,col);
                     scanf("%c",&num);
                     system("pause");
                     system("cls");
                     if(num>'9' || num<'0')
                     {
                         error2=1;
                     }
                 }while(error2);
             Sudoku[(raw-1)*10 +col-1]=num;
             print_Sudoku(Sudoku);
             printf("Are you pleased with the number you inerted in the raw:%d and column:%d\nor you want to change it?\nPress 'y' or 'Y' if it is ok, or anything else to modify it.\n",raw,col);
             fflush(stdin);
             scanf("%c",&answerc);
             }while(answerc!='y' && answerc!='Y');
             num_of_0=0;
             raw=0;
             do
             {
                 col=0;
                 do
                 {
                     if(Sudoku[raw*10 + col]=='0')
                     {
                         num_of_0++;
                     }
                     col++;
                 }while(col<9 && num_of_0==0);
                 raw++;
             }while(raw<9 && num_of_0==0);
             //num_of_0 is a counter of empty cells
             system("cls");
             answerc='o';
             //In case there are empty cells left, I ask the user if he wants to insert another digit
             if(num_of_0!=0)
             {
                 fflush(stdin);
                 print_Sudoku(Sudoku);
                 printf("Do you want to insert another digit?\nPress 'y' or 'Y' if so, or anything else to stop.\n");
                 scanf("%c",&answerc);
             }
         }while(num_of_0!=0 && answerc!='y' && answerc!='Y');
     }
     //If there are no other cells
     if(num_of_0==0)
     {
         error1=1;
         //error1 will remain true as long as there are no errors in the table
         raw=0;
         while(raw<9 && error1)
         {
             col=0;
             while(col<9 && error1)
             {
                 if(box_has_error(Sudoku,raw*10 +col))
                 {
                     error1=0;
                 }
                 col++;
             }
             raw++;
         }
     }
     //If at this point error1 is true, then there are no errors in the table
     print_Sudoku(Sudoku);
     if(num_of_0==0 && error1)
     {
         printf("Congratulations !! You solved the SUDOKU !!! \n");
     }
     else
     {
         if(num_of_0==0 && !error1)
         {
             printf("Though the table contains no empty cells, there are errors.\nIn order to modify the table, go to option 6. of the menu.\n");
         }
     }
     system("pause");
     system("cls");
 }

// This function implements the Automatic creation of a Sudoku table
 void auto_create_Sudoku(char Sudoku[])
 {
     char counter=0,num,i,j,sum,error=0;
     //I ask the user the number of digits he wants to be given, until I get a valid answer
     do
     {
        system("cls");
        if(error)
        {
            printf("You inserted invalid answer.\n");
        }
        error=0;
        printf("Insert the number of digits you want to be ginen? (0-81)\n");
        fflush(stdin);
        scanf("%d",&sum);
        if(sum>81 || sum<0)
        {
            error=1;
        }
     }while(error);
     //I clear current Sudoku and I create a new one
     erase_Sudoku(Sudoku);
     srand(time(NULL) + rand());
     //I create randomly the first raw.
     do
     {
         num=rand() %9 + 49;
         Sudoku[counter]=num;
         if(!box_has_error(Sudoku,counter))
         {
             counter++;
         }
     }while(counter<9);
     // the next raws are formen by transpositioning the first raw
     for(i=1;i<9;i++)
     {
         switch (i)
         {
             case 1:
             {
                 num=3;
                 break;
             }
             case 2:
             {
                 num=6;
                 break;
             }
             case 3:
             {
                 num=1;
                 break;
             }
             case 4:
             {
                 num=4;
                 break;
             }
             case 5:
             {
                 num=7;
                 break;
             }
             case 6:
             {
                 num=2;
                 break;
             }
             case 7:
             {
                 num=5;
                 break;
             }
             case 8:
             {
                 num=8;
                 break;
             }
         }
         // Filling next raw by transpositioning first raw digits by "num" cells
         for(j=0;j<9;j++)
         {
             Sudoku[i*10 + (j+num)%9]=Sudoku[j];
         }
     }
     // I erase cells until the number of cells filled is equal to the number asked by the user
     counter=0;
     while(81-sum>counter)
     {
         // num represents the number of cell, out of 81 (total cells) , i-> raw , j -> col .
         num=rand()%81;
         i=num/9;
         j=num%9;
         if(Sudoku[i*10 + j]!='0')
         {
             Sudoku[i*10 + j]='0';
             counter++;
         }
     }
     printf("The Sudoku has been created :\n");
     print_Sudoku(Sudoku);
     system("pause");
     system("cls");
 }

 char solve(char Sudoku[],char temp_Sudoku[], char solved_Sudoku[], char position) //This recursive function assists auto_solve function
{
    // We check if we can try values to a cell, if it is empty on the initial table, which is Sudoku array.
    // We do not change this array at any point
    // All attempts are made on temp_Sudoku array
    // If Sudoku is solved the solution is stored in array solved_Solved

  // logic of this function:
      //- while a cell can take only one specific digit (due to Sudoku rules) I put the digit and check again for more cells
      //- if there are no cell that can take only one digit, the we start making assumptions and we continue by them recursively
      //- if a cell can not take any digit, then we return.
    char num,counter1,counter2,i,temp_num;
    // if the pointer position is equal to 89 then the final cell has been reached
    if(position==89)
    {
         copy_Sudoku(solved_Sudoku,temp_Sudoku);
         return 0;
    }
    // if the pointer position shows on a '\n' character the I continue recursivly with the next position of the table
    if(position%10==9)
    {
         return solve(Sudoku, temp_Sudoku, solved_Sudoku, position + 1);
    }
    else
    {
        // counter1 shows the number of cells that can take only one digit
        do
        {
            counter1=0;
            for(i=position;i<89;i++)
            {
                counter2=0;
                if(i%10==9)
                {
                    i++;
                }
                // for every cell I havn't entered any digit, I check if the cell can take only one digit
                if(temp_Sudoku[i]=='0')
                {
                    num='1';
                    do
                    {
                        temp_Sudoku[i]=num;
                        if(!box_has_error(temp_Sudoku,i))
                        {
                            counter2++;
                            temp_num=num;
                        }
                        num++;
                    }while(num<='9' && counter2<2);
                 // if only one digit can be inserted then I insert it
                    if(counter2==1)
                    {
                        temp_Sudoku[i]=temp_num;
                        counter1++;
                    }
                    else
                    {
                        //In case the cell cannot take any digits, I return to the previous assamption, reversing any inbetween changes
                        if(counter2==0)
                        {
                            for(i=position;i<89;i++)
                            {
                                temp_Sudoku[i]=Sudoku[i];
                            }
                            return 1;
                        }
                        // In case there can be inserted many values, I leave it empty for now
                        temp_Sudoku[i]='0';
                    }
                }
            }
        }while(counter1!=0);
        // when counter1 is equal to 0, we have to make an assumption to move on
        // checking initial Sudoku table in order to make sure that I can modify the cell's value
        if(Sudoku[position]=='0')
        {
            for (num = '1'; num <= '9'; num++)
            {
                 temp_Sudoku[position] = num;
                 if (!box_has_error(temp_Sudoku,position))
                 {
                     // making assumptions recursively
                     solve(Sudoku, temp_Sudoku, solved_Sudoku, position + 1);
                 }
                 //At this point, either all assumptions that have been made, for this position, are wrong, or the sudoku has been solved
                 // One way or another, I revert all changes l have made after this position
            }
            for(i=position;i<89;i++)
            {
                temp_Sudoku[i]=Sudoku[i];
            }
            return 1;
        }
        else
        {
            // At this point, this cell already has value so I continue to next position
            solve(Sudoku, temp_Sudoku, solved_Sudoku, position + 1);
            // At this point, the above assumption has failed so I revert all changes after this position
            for(i=position;i<89;i++)
            {
                temp_Sudoku[i]=Sudoku[i];
            }
            return 0;
        }
    }
}

 // This function implements Automatic Sudoku Solving
 void auto_solve_Sudoku(char Sudoku[])
 {
     // assisting variables
     char temp_Sudoku[91],solved_Sudoku[91];
     char error;

    erase_Sudoku(solved_Sudoku);
    copy_Sudoku(temp_Sudoku,Sudoku);
    printf("Please wait while the program is solving the Sudoku .\nThis may take a few minutes...\n");
    solve(Sudoku,temp_Sudoku,solved_Sudoku,0);
    error=0;
    //
    // Checking if there are empty cells
    if(solved_Sudoku[0]=='0')
    {
        error=1;
    }
    // printing update messages
    if(error)
    {
        printf("The loaded Sudoku cannot be solved...\nPlease load another and continue or modify.\n");
    }
    else
    {
        copy_Sudoku(Sudoku,solved_Sudoku);
        print_Sudoku(Sudoku);
        printf("Solved Sudoku is now Loaded!.\n");
    }
    system("pause");
 }

int main()
{
    char Sudoku[91]; // Sudoku array
    char answer,is_saved=1,is_empty=1;
    do
    {
        answer=show_menu();
        switch (answer)
        {
            case '1':
            {
                if(!is_saved)
                {
                    printf("There is a loaded Sudoku.\nDo you want to replace it?.\nInsert 'y' or 'Y' for yes and anything else for no.\n");
                    fflush(stdin);
                    scanf("%c",&answer);
                    if(answer=='y' || answer=='Y')
                    {
                        printf("Loaded Sudoku will be deleted");
                        load_Sudoku(Sudoku);
                        is_saved=1;
                        is_empty=0;
                    }
                    answer='1';
                }
                else
                {
                    load_Sudoku(Sudoku);
                    is_saved=1;
                    is_empty=0;
                }
                break;
            }
            case '2':
            {
                if(is_empty)
                {
                    printf("There is no loaded Sudoku\nTry to load a Sudoku in order to save it later\n");
                    system("pause");
                    system("cls");
                }
                else
                {
                    save_Sudoku(Sudoku);
                    is_saved=1;
                }
                break;
            }
            case '3':
            {
                if(is_saved)
                {
                    erase_Sudoku(Sudoku);
                    is_empty=1;
                    is_saved=1;
                }
                else
                {
                    printf("Loaded Sudoku is not saved!.\nDo you want to replace it?.\nInsert 'y' or 'Y' for yes and anything else for no.\n");
                    fflush(stdin);
                    scanf("%c",&answer);
                    if(answer=='y' || answer=='Y')
                    {
                        printf("You chose to delete the loaded Sudoku!.\n");
                        erase_Sudoku(Sudoku);
                        is_empty=1;
                        is_saved=1;
                    }
                    else
                    {
                        printf("You have chosen not to delete loaded Sudoku.");
                    }
                    answer='3';
                }
                break;
            }
            case '4':
            {
                if(!is_saved)
                {
                    printf("There is a loaded Sudoku.\nDo you want to replace it?.\nInsert 'y' or 'Y' for yes and anything else for no.\n");
                    fflush(stdin);
                    scanf("%c",&answer);
                    if(answer=='y' || answer=='Y')
                    {
                        printf("You have chosen to delete the loaded Sudoku.\n");
                        system("pause");
                        hand_create_Sudoku(Sudoku);
                        is_empty=0;
                    }
                    else
                    {
                        printf("You chose not to delete the loaded Sudoku.\n");
                        system("pause");
                    }
                    answer='4';
                }
                else
                {
                    hand_create_Sudoku(Sudoku);
                    is_saved=1;
                }
                break;
            }
            case '5':
            {
                if(!is_saved)
                {
                    printf("There is a loaded Sudoku.\nDo you want to replace it?.\nInsert 'y' or 'Y' for yes and anything else for no.\n");
                    fflush(stdin);
                    scanf("%c",&answer);
                    if(answer=='y' || answer=='Y')
                    {
                        printf("You have chosen to delete the loaded Sudoku.\n");
                        system("pause");
                        system("cls");
                        auto_create_Sudoku(Sudoku);
                        is_empty=0;
                    }
                    else
                    {
                        printf("You chose not to delete the loaded Sudoku.\n");
                        system("pause");
                    }
                    answer='5';
                }
                else
                {
                    auto_create_Sudoku(Sudoku);
                    is_empty=0;
                }
                break;
            }
            case '6':
            {
                if(is_empty)
                {
                    printf("There is no loaded Sudoku, please load a Sudoku first in order to handle it.\n");
                    system("pause");
                    system("cls");
                }
                else
                {
                    handle_Sudoku(Sudoku);
                    is_empty=0;
                    is_saved=0;
                }
                break;
            }
            case '7':
            {
                if(is_empty)
                {
                    printf("There is no loaded Sudoku, please load a Sudoku first in order to solve it.\n");
                    system("pause");
                    system("cls");
                }
                else
                {
                    hand_solve_Sudoku(Sudoku);
                    is_saved=0;
                }
                break;
            }
            case '8':
            {
                 if(is_empty)
                 {
                     printf("There is no loaded Sudoku, please load a Sudoku first in order to automatically solve it.");
                     system("pause");
                     system("cls");
                 }
                 else
                 {
                     auto_solve_Sudoku(Sudoku);
                     is_saved=0;
                     is_empty=0;
                 }
                 break;
            }
            case '9':
            {
                if(is_saved)
                {
                    printf("The program will shutdown as soon as you press any key\n");
                    system("pause");
                }
                else
                {
                    printf("The loaded Sudoku has not been saved.\nDo you want to continue exiting?\nPress 'y' or 'Y' to exit the program\nor anything else not to.\n");
                    fflush(stdin);
                    scanf("%c",&answer);
                    if(answer=='y' || answer=='Y')
                    {
                        answer='9';
                    }
                }
                break;
            }
        }
    }while(answer!='9');
    return 0;
}

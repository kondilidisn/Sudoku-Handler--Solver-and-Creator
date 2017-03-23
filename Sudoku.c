#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

// This function implements "Print Menu" and "Get Valid Answer from User" actions
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
    printf("The file : %s was loaded succesfully\n",filename);
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
            printf("File %s already exists, do you want to replace it?\nIf so, press 'N', in any other case, you will be asced for a new name.\n",filename);
            fflush(stdin);
            scanf("%c",&answer);
            if(answer!='n' && answer!='N')
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
             // In case of Sudoku rule violation I clear the raw
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
     printf("To Sudoku dhmiourgh8hke epituxws kai einai twra fortwmeno.\n");
     system("pause");
     system("cls");
 }

 void handle_Sudoku(char Sudoku[]) // Ayth h synarthsh ylopoiei th leitourgia "Tropopoihsh Sudoku".
 {
     char col,raw,num,i,j,error1,error2,answer;
     char temp_Sudoku[91];
     copy_Sudoku(temp_Sudoku,Sudoku);
     //oso o xrhsths epilegei na allaksei kai allo koutaki
     do
     {
         error1=0;
         //elegxos gia egkurh eisagwgh dedomenwn
         do
         {
             system("cls");
             print_Sudoku(temp_Sudoku);
             if(error1)
             {
                 printf("Ta dedomena pou dwsate den htan egkura, parakalw ksanadwste ta dedomena\nSteiles kai grammes (1-9) kai numera (0-9)\n");
             }
             error1=0;
             fflush(stdin);
             printf("Parakalw eisagetai me th seira: th grammh , th sthlh kai sto telos to numero\n gia paradeigma pathste : '9 8 1'\nTo opoio einai: sthn 9h grammh kai 8h sthlh vale to 1.\n");
             scanf("%d %d %c",&raw,&col,&num);
             if(raw>9 || raw<1 || col>9 || col<1 || num>'9' || num<'0')
             {
                 error1=1;
             }
         }while(error1);
      temp_Sudoku[(raw-1)*10+col-1]=num;
      system("cls");
      print_Sudoku(temp_Sudoku);
      printf("8elete na allaksete kai allo koutaki?\nPathste 'n' h 'N' gia nai alliws otidhpote allo\n");
      fflush(stdin);
      scanf("%c",&answer);
     }while(answer=='n' || answer=='N');
     // meta elenxw ama uparxoun ston teliko pinaka Sudoku provlhmata (se opoiodhpote keli tou)
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
     // Ama uaprxei estw kai ena provlhma, dinw ston Xrhsth thn eukairia na krathsei fortwmeno ton arxiko pinaka Sudoku pou eixe
     answer='o';
     if(error1)
     {
         print_Sudoku(temp_Sudoku);
         printf("To Sudoku opws to exete epireasei exei toulaxiston 1 provlhma\nsto shmeio me suntetagmenes:\ngrammh:%d\nsthlh:%d\n8elete na krathsetai to palio h oxi?\nPathste 'n' h 'N' gia na krathsete to palio \nh otidhpote allo gia na sunexisete me auto fortwmeno.\n",raw,col);
         fflush(stdin);
         scanf("%c",&answer);
     }
     if(answer!='n' && answer!='N')
     {
         copy_Sudoku(Sudoku,temp_Sudoku);
         printf("Antikatasthsate to palio me epituxia.\n");
     }
     else
     {
         printf("Epileksate na krathsete to palio Sudoku anepireasto.\n");
     }
 }

 void hand_solve_Sudoku(char Sudoku[])// Ayth h synarthsh ylopoiei th leitourgia "Xeirokinhth epilush Sudoku"
 {
     char col=0,raw=0,num,answerc,error1,error2,num_of_0;
     num_of_0=0;
     //elenxw ama o pinakas einai gematos
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
     //Ama den einai gematos
     if(num_of_0!=0)
     {
         do
         {
             error1=0;
             error2=0;
             //elegxos eisodou kenou keliou
             do
             {
                 system("cls");
                 if(error2)
                 {
                     printf("To pedio pou dialeksate den einai adeio...\nParakalw ksanadialekste pedio\n");
                 }
                 error2=0;
                 //elegxos gia egkurh eisagwgh dedomenwn
                 do
                 {
                     system("cls");
                     print_Sudoku(Sudoku);
                     if(error1)
                     {
                         printf("Ta dedomena pou dwsate den htan egkura, parakalw ksanadwste ta dedomena\nGrammh h sthlh (1-9).\n");
                     }
                     error1=0;
                     printf("Parakalw eisagete me th seira: th grammh kai th sthlh\n");
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
             //twra pou katastalaksame se pedio mporei na to alaksei oses fores 8elei
             do
             {
                 error2=0;
                 do
                 {
                     system("cls");
                     print_Sudoku(Sudoku);
                     if(error2)
                     {
                         printf("Paraklaw plhktrologhste enan ari8mo anamesa sto 0 kai to 9\n");
                     }
                     error2=0;
                     fflush(stdin);
                     printf("Parakalw pathste to numero pou 8elete na eisagete sto pedio:%d,%d\n",raw,col);
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
             printf("To numero pou molis valate sthn grammh:%d kai sthlh:%d einai entaksei h 8elete na to allaksete?\nPathste 'n' h 'N' ama einai entaksei kai o,tidhpote allo gia na to allaksete\n",raw,col);
             fflush(stdin);
             scanf("%c",&answerc);
             }while(answerc!='n' && answerc!='N');
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
             //ama einai gemato to sudoku to num_of_0 8a teleiwsei tis epanalhpseis me timh 0
             system("cls");
             answerc='o';
             //ama den einai gemato rwtaw ton Xrhsth ama 8elei na valei kai allo koutaki
             if(num_of_0!=0)
             {
                 fflush(stdin);
                 print_Sudoku(Sudoku);
                 printf("8elete na eisagete allo numero?\nPathste 'n' h 'N' gia na eisagetai kai allo numero kai o,tidhpote allo gia na stamathsete\n");
                 scanf("%c",&answerc);
             }
         }while(num_of_0!=0 && answerc!='n' && answerc!='N');
     }
     //ama einai gemato
     if(num_of_0==0)
     {
         error1=1;
         //to error1 8a krathsei alh8h timh oso den uparxei la8os sto Sudoku
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
     //ara edw to error1 einai alh8es ama to Sudoku den exei la8h
     print_Sudoku(Sudoku);
     if(num_of_0==0 && error1)
     {
         printf("Sugxarhthria !!! Lusate to Sudoku !!! \n");
     }
     else
     {
         if(num_of_0==0 && !error1)
         {
             printf("To Sudoku einai gemato alla periexei la8h!!!\nGia na dior8wsete ena la8os prepei na pate sth leitourgia '6' tou menu\npou grafei 'Tropopoihsh Sudoku' kai na to allaksete apo ekei.\n");
         }
     }
     system("pause");
     system("cls");
 }

 void auto_create_Sudoku(char Sudoku[])// Ayth h synarthsh ylopoiei th leitourgia aytomaths dhmiourgias Sudoku
 {
     char counter=0,num,i,j,sum,error=0;
     //rwtaw to xrhsth posa koutakia 8elei na dinontai, mexri na parw egkuro ari8mo
     do
     {
        system("cls");
        if(error)
        {
            printf("Dwsate ari8mo ektos pediou.\n");
        }
        error=0;
        printf("Dwste ton ari8mo twn keliwn pou 8a dinontai (0-81)\n");
        fflush(stdin);
        scanf("%d",&sum);
        if(sum>81 || sum<0)
        {
            error=1;
        }
     }while(error);
     //meta ka8arizw - arxikopoiw to Sudoku kai sth 8esh tou dhmiourgw kainourgio.
     erase_Sudoku(Sudoku);
     srand(time(NULL) + rand());
     //sxediazw thn prwth grammh kai meta se sxesh me ayth sxediazw tis alles
     do
     {
         num=rand() %9 + 49;
         Sudoku[counter]=num;
         if(!box_has_error(Sudoku,counter))
         {
             counter++;
         }
     }while(counter<9);
     //twra se sxesh me auth 8a sxediasw tis alles, h num pleon 8a deixnei poses 8eseis 8a metatopistei h prwth seira wste na dhmiourghsei tis alles
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
         //vazw thn prwth seira metatopismenh (peristrofika) kata "num"
         for(j=0;j<9;j++)
         {
             Sudoku[i*10 + (j+num)%9]=Sudoku[j];
         }
     }
     // epeita kruvw arketa koutakia mexri na fainontai mono osa epelekse o xrhsths
     counter=0;
     while(81-sum>counter)
     {
         // to num edw antiprosopeuei th 8esh ston pinaka se sxesh me tis 81 sunlonika , i-> raw , j -> col .
         num=rand()%81;
         i=num/9;
         j=num%9;
         if(Sudoku[i*10 + j]!='0')
         {
             Sudoku[i*10 + j]='0';
             counter++;
         }
     }
     printf("To Sudoku pou molis dhmiourgh8hke einai fortwmeno kai einai auto:\n");
     print_Sudoku(Sudoku);
     system("pause");
     system("cls");
 }

 char solve(char Sudoku[],char temp_Sudoku[], char solved_Sudoku[], char position) //Ayth h anadromikh sunarthsh einai boh8htikh ths auto_solve
{
    // O pinakas Sudoku den allazei pou8ena, alla mesw autou elenxwoume an mporoume na peiraksoume ena koutaki ston temp_Sudoku.
    // O temp_Sudoku krataei oles tis dokimes pou kanoume (dhladh panw se auton prospa8oume na lusoume to Sudoku)
    // O ston pinaka solved_Solved antigrafetai olos o temp_Sudoku otan exei katalhksei se lush.
    // h logikh auth ths sunarthshs einai : oso uparxoun koutakia pou mporoun na paroun mono 1 numero valto kai ksanaelenkse an uparxoun kai alla.
    // alliws den uparxoun koutakia me monadikh pi8anh timh.
    // opote kanoume mia upo8esh (estw oti edw einai to "tuxaio numero" kai sunexizoume thn epilush me vash auth thn upo8esh.
    // h ulopoihsh auth ths logikhs ths upo8eshs ginetai mesw ths anadromhs (otan teleiwsoun oi ekteleseis twn YPO-kaloumenwn anadromwn tote h upo8esh einai atoph)
    // ama katalhksei se atopo gurname mia anadromh pisw (giati exoun teleiwsei oi dunates time pou mporei na parei auto to koutaki).
    char num,counter1,counter2,i,temp_num;
    //ama exei ftaseis to koutaki 89 tote exei teleiwsei th diasxush tou Sudoku.
    if(position==89)
    {
         copy_Sudoku(solved_Sudoku,temp_Sudoku);
         return 0;
    }
    // ama exei pesei panw se '\n' giati ta exw mesa ston pinaka sthn 10h 8esh ka8e seiras , na proxwrhsei koutaki.
    if(position%10==9)
    {
         return solve(Sudoku, temp_Sudoku, solved_Sudoku, position + 1);
    }
    else
    {
        // oso to counter den menei 0 paei na pei oti uparxoun koutakia pou mporoun na paroun monadikh timh
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
                //gia ka8e koutaki pou mporw na peiraksw kai den tou exw dwsei hdh timh elenxw an mporei na parei monadikh timh
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
                    if(counter2==1) // ama mporei na parei monadikh timh tou thn dinw
                    {
                        temp_Sudoku[i]=temp_num;
                        counter1++;
                    }
                    else
                    {
                        //alliws ama den mporei na parei kamia timh tote dior8wnw o,ti exw allaksei me vash ton arxiko pinaka Sudoku kai epistrefw apo thn teleutaia upo8esh
                        if(counter2==0)
                        {
                            for(i=position;i<89;i++)
                            {
                                temp_Sudoku[i]=Sudoku[i];
                            }
                            return 1;
                        }
                        //ama omws mporei apla na parei polles times to afhnw mhden kai synexizw gia na kanw mia upo8esh
                        temp_Sudoku[i]='0';
                    }
                }
            }
        }while(counter1!=0);
        // ama to counter ginei 0 tote prepei na kanoume mia upo8esh gia na sunexisoume
        // elenxw an ama mporw na peiraksw to koutaki opote to elenxw me to arxiko
        if(Sudoku[position]=='0')
        {
            for (num = '1'; num <= '9'; num++)
            {
                 temp_Sudoku[position] = num;
                 if (!box_has_error(temp_Sudoku,position))
                 {
                     //ama exw mpei edw tote dokimazw poio numero mporei na parei auto to koutaki kai gia ka8e pi8ano numero arxizw tis upo8eseis.
                     solve(Sudoku, temp_Sudoku, solved_Sudoku, position + 1);
                 }
                 //ama bgw apo edw h exoun ginei oles oi upo8esei la8os h to sudoku exei lu8ei kai apla gunraw sthn arxikh mou anadromh.
                 //outws h allws, allazw o,ti allages exw kanei ston temp_Sudoku apo to position kai pera gia na eimai kalumenos sthn periptwsh la8ous kai epistrefw.
            }
            for(i=position;i<89;i++)
            {
                temp_Sudoku[i]=Sudoku[i];
            }
            return 1;
        }
        else
        {
            //ama eimai egw tote to koutaki den einai '0' ston arxiko pinaka Sudoku kai tote apla proxwraw
            solve(Sudoku, temp_Sudoku, solved_Sudoku, position + 1);
            //ama gurnaei kai apo autes tis periptwseis pali allazw o,ti exei ginei apo to position kai pera
            for(i=position;i<89;i++)
            {
                temp_Sudoku[i]=Sudoku[i];
            }
            return 0;
        }
    }
}

 void auto_solve_Sudoku(char Sudoku[]) // Ayth h synarthsh ylopoiei thn leitourgia ths automaths epilushs
 {
     char temp_Sudoku[91],solved_Sudoku[91];//voh8htikoi pinakes gia thn lush kai thn apo8hkeush tou lumenou Sudoku
     char error;

    erase_Sudoku(solved_Sudoku);
    copy_Sudoku(temp_Sudoku,Sudoku);
    printf("Parakalw perimenete oso to programma epiluei to Sudoku.\nAuto mporei na parei liga lepta...\n");
    solve(Sudoku,temp_Sudoku,solved_Sudoku,0);
    error=0;
    // o idios elenxos me to an o pinakas solved_Sudoku exei meinei adeios, ara den lu8hke to Sudoku.
    if(solved_Sudoku[0]=='0')
    {
        error=1;
    }
    // epeita apla tupwnw mhnymata enhmerwshs.
    if(error)
    {
        printf("To Sudoku pou htan fortwmeno den einai epilusimo...\nParakalw fortwste kai sunexiste me allo h elenkste to xeirokinhta.\n");
    }
    else
    {
        copy_Sudoku(Sudoku,solved_Sudoku);
        print_Sudoku(Sudoku);
        printf("To lumeno Sudoku einai twra fortwmeno.\nDhladh 8a xeirizeste auto mexri na fortwsete allo apo to menu.\n");
    }
    system("pause");
 }

int main()
{
    char Sudoku[91]; // pinakas pou antiprosopeuei to sudoku
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
                    printf("Yparxei kapoio fortwmeno Sudoku.\n8elete na to svhsete kai na fortwsetai allo?.\nPathste 'n' h 'N' gia nai kai o,tidhpote allo gia oxi\n");
                    fflush(stdin);
                    scanf("%c",&answer);
                    if(answer=='n' || answer=='N')
                    {
                        printf("Auto pou htan fortwmeno 8a svhstei kai 8a fortw8ei allo");
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
                    printf("Den uparxei kapoio fortwmeno Sudoku.\nParakalw fortwste ena prwta kai meta apo8hkeuste to.\n");
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
                    printf("To Sudoku pou einai fortwmeno den einai apo8hkeuumeno.\nPathste 'n' h 'N' gia na to svhsete kai otidhpote allo\ngia na to akurwsete.\n");
                    fflush(stdin);
                    scanf("%c",&answer);
                    if(answer=='n' || answer=='n')
                    {
                        printf("Epileksate na svhsete to Sudoku.\n");
                        erase_Sudoku(Sudoku);
                        is_empty=1;
                        is_saved=1;
                    }
                    else
                    {
                        printf("Epileksate na mh svhsete to Sudoku");
                    }
                    answer='3';
                }
                break;
            }
            case '4':
            {
                if(!is_saved)
                {
                    printf("Yparxei fortwmeno Sudoku pou den exei apo8hkeutei.\n8elete na to antikatasthete kai na dhmiourghhsetai allo?\nAn 8elete na to antikatasthsetai pathste 'n' h 'N' kai otidhpote allo gia oxi.\n");
                    fflush(stdin);
                    scanf("%c",&answer);
                    if(answer=='n' || answer=='N')
                    {
                        printf("Epileksate na svhsetai to palio kai na valetai sthn 8esh tou kainourgio.\n");
                        system("pause");
                        hand_create_Sudoku(Sudoku);
                        is_empty=0;
                    }
                    else
                    {
                        printf("Epileksate na mh svhsete to palio.\n");
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
                    printf("Yparxei fortwmeno Sudoku pou den exei apo8hkeutei.\n8elete na to antikatasthete kai na dhmiourghhsetai allo?\nAn 8elete na to antikatasthsetai pathste 'n' h 'N' kai otidhpote allo gia oxi.\n");
                    fflush(stdin);
                    scanf("%c",&answer);
                    if(answer=='n' || answer=='N')
                    {
                        printf("Epileksate na svhhstei to palio fortwmeno Sudoku\n;");
                        system("pause");
                        system("cls");
                        auto_create_Sudoku(Sudoku);
                        is_empty=0;
                    }
                    else
                    {
                        printf("Epileksate na mh svhsete to palio.\n");
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
                    printf("Den uparxei kapoio fortwmeno Sudoku.\nParakalw fortwste ena prwta kai meta tropopoihste to.\n");
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
                    printf("Den uparxei kapoio fortwmeno Sudoku.\nParakalw fortwste ena prwta kai meta prospa8hste na to lusete.\n");
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
                     printf("To fortwmeno Sudoku einai adeio.\nParakalw fortwste ena Sudoku prwta kai meta epilekste thn automath apilush\n");
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
                    printf("Epileksate thn eksodo, to programma 8a termatistei molis pathsete kati\n");
                    system("pause");
                }
                else
                {
                    printf("To Sudoku pou einai fortwmeno den exei apo8hkeutei.\n8elete na sunexisete me ton termatismo?\nPathste 'n' h 'N' gia na termatisei to programma\nkai otidhpote allo gia na mh termathsei\n");
                    fflush(stdin);
                    scanf("%c",&answer);
                    if(answer=='n' || answer=='N')
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

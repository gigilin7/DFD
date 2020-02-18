#include <stdio.h>
#include <string.h>
#include <stdbool.h>
enum Choice {ENTER_RECORD=1,VIEW_DAY,VIEW_WEEK,MODIFY,DELETE,SEARCH,QUIT};
enum WWWW {WHEN=1,WHO,WHERE,WHAT}; //4 個 W 


typedef struct Record 
{
	char date[5];
	char name[21];
	char location[31];
	char thing[81];
	
}record;

int enterchoice()
{
	printf("Enter a number.\nWhich service you want??\n");
	printf("1-Enter the who/when/what/where information.\n");
	printf("2-View a day.\n");
	printf("3-View a week.\n");
	printf("4-Modify a record.\n");
	printf("5-Delete a record.\n");
	printf("6-Search a record by one of when/what/who/where.\n");
	printf("7-Quit after save the record or discard.\n --> ");
	
	int choice;
	scanf("%d",&choice);
	return choice;
};

record InitialRecord(record initial)
{
	
	strcpy( initial.date , "0" );
	strcpy( initial.location , "Null" );
	strcpy( initial.name , "Null" );
	strcpy( initial.thing , "Null" );
	return initial;
}

record EnterRecord(record newrecord[],int i) //要有warn if 輸入的time存在
{
	int j;
	bool flag=true;
	do
	{
		setbuf(stdin, NULL);  //清空buffer裡的 \n 使得[^\n]正常運作 
		printf("Enter date (1~31): ");
		scanf("%[^\n]",&newrecord[i].date);
		for(j=0;j<i;j++)
		{
			if(atoi(newrecord[i].date)==atoi(newrecord[j].date))
			{
				printf(" the date exist. \n" );
				flag=false;
			}
			else
			{
				flag=true;
			}
		}	
	}while( atoi(newrecord[i].date)>31 || atoi(newrecord[i].date)<=0 || flag==false );
	
	setbuf(stdin, NULL);  //清空buffer裡的 \n 使得[^\n]正常運作 
	printf("Enter name : ");
	scanf("%[^\n]",&newrecord[i].name);
	
	setbuf(stdin, NULL);  //清空buffer裡的 \n 使得[^\n]正常運作 
	printf("Enter location : ");
	scanf("%[^\n]",&newrecord[i].location);
	
	setbuf(stdin, NULL);  //清空buffer裡的 \n 使得[^\n]正常運作 
	printf("Enter thing : ");
	scanf("%[^\n]",&newrecord[i].thing);

	return *newrecord;
};
void ViewDay(record viewrecord[],int n)
{
	//最底下有直接讀取檔案輸出的方式 
	int i,temp;
	for(i=0;i<10;i++)
	{
		temp=atoi(viewrecord[i].date);
		if(temp==n)
		{
			printf("-> Date: %s \t-> Name: %-20s\n",viewrecord[i].date,viewrecord[i].name);
			printf("-> Location: %-30s\n",viewrecord[i].location);
			printf("-> Thing: %-80s\n",viewrecord[i].thing);
			printf("-----------------------\n");
			break;;
		}
	}
};

void ViewWeek(record viewrecord[],int n)
{
	//最底下有直接讀取檔案輸出的方式
	int i,j,temp;
	for(j=n;j<n+7;j++)
	{
		bool flag=false;  //若找到對應date的record flag設為true 
		
		for(i=0;i<10;i++)  //找找有沒有對應的record 
		{
			temp=atoi(viewrecord[i].date);
		
			if( temp== j ) //找到就印出來 
			{
				printf("-> Date: %s \t-> Name: %-20s\n",viewrecord[i].date,viewrecord[i].name);
				printf("-> Location: %-30s\n",viewrecord[i].location);
				printf("-> Thing: %-80s\n",viewrecord[i].thing);
				printf("-----------------------\n");
				flag=true;
			}
		}	
		if(!flag) //沒有找到 flag 為 false ， !flag 為 true 
		{
			printf("-> Date: %-2d \t-> Name: Null\n",j);
			printf("-> Location: Null\n");
			printf("-> Thing: Null\n");	
			printf("-----------------------\n");
		}
	}	
};//modify沒寫好 
record Modify(record modifyrecord[],int n)
{
	int i,j=0,temp;
	record temprecord[10];
	bool flag=false;
	for(i=0;i<10;i++)
		InitialRecord(temprecord[i]);
	
	for(i=0;i<10;i++)
	{
		if(atoi(modifyrecord[i].date)==n)
		{
			flag=true;
			break;
		}
	}
	if(!flag)
	{
		printf("\n----------the date record can not found !!-----------\n\n ");
		return *modifyrecord;;
	}
	printf("\nEnter a number.\nWhich choice you want??\n");
	printf("1-Modify when.\n");
	printf("2-Modify who.\n");
	printf("3-Modify where.\n");
	printf("4-Modify what.\n");
	
	int modify_choice;
	scanf("%d",&modify_choice);

	switch( modify_choice )
	{	
		case WHEN:
		{
			int date;
			do
			{
				printf("Enter a new date number : ");
				scanf("%d",&date);
			}while(date>31 || date<=0);
			sprintf(modifyrecord[i].date,"%d",date);
		
			break;
		}
		case WHAT:
		{
			char thing[81];
			setbuf(stdin, NULL);  //清空buffer裡的 \n 使得[^\n]正常運作 
			printf("Enter a new thing (len<=80): ");
			scanf("%[^\n]",thing);
			
			strcpy(modifyrecord[i].thing,thing);
			
			break;
		}
		case WHERE:
		{
			char location[31];
			setbuf(stdin, NULL);  //清空buffer裡的 \n 使得[^\n]正常運作 
			printf("Enter a new location (len<=30): ");
			scanf("%[^\n]",location);
		
			strcpy(modifyrecord[i].location,location);
		
			break;
		}
		case WHO:
		{
			char name[21];
			setbuf(stdin, NULL);  //清空buffer裡的 \n 使得[^\n]正常運作 
			printf("Enter a new name (<=20): ");
			scanf("%[^\n]",name);
		
			strcpy(modifyrecord[i].name,name);
			break;
		}	
		default:	//若輸入錯誤直接離開 
			printf("Incorrect choice\n");
	}
	printf("\n----------modify success------------\n\n");
		
	return *modifyrecord;
};

record Delete(record deleterecord[],int n)
{
	int i,j=0,temp;
	bool flag=0;
	record temprecord[10];
	for(i=0;i<10;i++)
		InitialRecord(temprecord[i]);
	
	for(i=0;i<10;i++)
	{
		temp=atoi(deleterecord[i].date); //等等比對有沒有目標資料 
		if(temp==n)
		{
			temp=i;  //將日期符合需求的第 i 筆資料的 i 記錄下來 
			flag=true;  //表示有找到 
			break;
		}
	}

	// 重點執行 delete的部分 除了欲刪除的項目外，其他record要存到temprecord裡
	// temprecord則成為刪除成功的record 
	for(i=0;i<10;i++)
	{
		if(i!=temp)
		{
			temprecord[j]=deleterecord[i];
			j++;	
		}
		InitialRecord(deleterecord[i]);
		
	}
	// 將temprecord 傳回給原來的位置	
	for(i=0;i<10;i++)
	{
		deleterecord[i]=temprecord[i];
	}
	
	// 若有找到 flag 在前面被設為 true 
	if(flag)
		printf("\n----------delete success------------\n\n");
	else
		printf("\n--the date can not found at the record--\n\n");
		
	return *deleterecord;
};
void Search(record newrecord[])
{
	int i;
	bool flag=false;
	printf("\nEnter a number.\nWhich choice you want??\n");
	printf("1-Search when.\n");
	printf("2-Search who.\n");
	printf("3-Search where.\n");
	printf("4-Search what.\n");

	int search_choice;
	scanf("%d",&search_choice);

	switch( search_choice )
	{	
		case WHEN:
		{
			int n;
			do
			{
				printf("Enter the date number : ");
				scanf("%d",&n);
			}while(n>31 || n<=0);
			
			ViewDay(newrecord,n);
			break;
		}
		case WHAT:
		{
			char thing[81];
			setbuf(stdin, NULL);  //清空buffer裡的 \n 使得[^\n]正常運作 
			printf("Enter the thing (len<=80): ");
			scanf("%[^\n]",thing);
			system("pause");
			for(i=0;i<10;i++)	//搜尋是否有符合的資料 
			{
				if(strcmp(newrecord[i].thing,thing)==0)
				{
					ViewDay(newrecord,atoi(newrecord[i].date));
					flag=true;	//表示找到過資料 
				}	
			}
			if(!flag)
				printf("\nthe record can not found by \"%s\"\n\n",thing); 
			break;
		}
		case WHERE:
		{
			char location[31];
			setbuf(stdin, NULL);  //清空buffer裡的 \n 使得[^\n]正常運作 
			printf("Enter the location (len<=30): ");
			scanf("%[^\n]",location);
			for(i=0;i<10;i++)	//搜尋是否有符合的資料
			{
				if(strcmp(newrecord[i].location,location)==0)
				{
					ViewDay(newrecord,atoi(newrecord[i].date));	
					flag=true;	//表示找到過資料 
				}	
			}
			if(!flag)
				printf("\nthe record can not found by \"%s\"\n\n",location); 
			break;
		}
		case WHO:
		{
			char name[21];
			setbuf(stdin, NULL);  //清空buffer裡的 \n 使得[^\n]正常運作 
			printf("Enter the name (<=20): ");
			scanf("%[^\n]",name);
			for(i=0;i<10;i++)	//搜尋是否有符合的資料
			{
				if(strcmp(newrecord[i].name,name)==0)
				{
					ViewDay(newrecord,atoi(newrecord[i].date));
					flag=true;	//表示找到過資料 
				}	
			}
			if(!flag)
				printf("\nthe record can not found by \"%s\"\n\n",name); 
			break;
		}	
		default:	//若輸入錯誤直接離開 
			printf("Incorrect choice\n");
	}
	
};//儲存此次執行所有編輯的紀錄or丟棄 
void Quit(record newrecord[],int i) 
{	//i是有i筆的意思，若S則儲存至file，D則直接丟棄 
	char c[1];
	int j=0;
	do
	{
		printf("Do you want to save or discard the record?? (S/D) : ");
		scanf("%s",c);
		
		if(c[0]=='S')	//save 更新file內全部的資料 
		{
			FILE *fout;
			fout=fopen("Appointment_Book.dat","r+b");
			
			fprintf(fout,"%s   %-21s%-31s%-80s\r","date","name","locatoin","thing"); //放標題 
			fseek(fout,sizeof(record)+4,SEEK_SET); //尋找位置 		
			
			fclose(fout);
			for(;j<10;j++)		//輸出先前編輯的record 
			{
				fout=fopen("Appointment_Book.dat","r+b");
			
				fseek(fout,sizeof(record)*(j+1)+4,SEEK_SET); //尋找位置 				
/*/測試用
				printf("-> Date: +%s+\t-> Name: +%s+\n",newrecord[j].date,newrecord[j].name);
				printf("-> Location: +%s+\n",newrecord[j].location);
				printf("-> Thing: +%s+\n",newrecord[j].thing);
				printf("-----------------------\n");
*/
				fwrite( &newrecord[j],sizeof(record),1,fout);

//測試用		printf("\n+%d+\n",ftell(fout));
				
				fclose(fout);
			}
			printf("\n-----------the record saved!!---------\n\n");
		}
		else if(c[0]=='D')
		{
			printf("\n-----------the record discard!!---------\n\n");
			break;
		}
	}while( c[0] != 'S' && c[0] != 'D' );	
};

//	initial the file 
void InitialFile(record Empty)
{
	int i;
	do		
	{
		printf("Do you want initial the record file? (Y/N) : ");
		char c;
		scanf("%c",&c);
		setbuf(stdin, NULL);  //清空buffer裡的 \n 使得[^\n]正常運作 
		if(c=='Y' || c=='y')
		{
			FILE *fout;
			fout=fopen("Appointment_Book.dat","wb");
			fprintf(fout,"%s   %-21s%-31s%-80s","date","name","locatoin","thing"); //放標題 
			fwrite( "\n",sizeof(char),1,fout);
			
			fclose(fout);
			
//測試用	printf("%d+",ftell(fout));
			
			for(i=1;i<=10;i++)	//開始初始化 
			{	
				fout=fopen("Appointment_Book.dat","r+b");
				fseek(fout,sizeof(record),SEEK_SET);
				if(i==1)
					fseek(fout,2,SEEK_CUR); //尋找位置
				else
					fseek(fout,2+sizeof(record)*(i-1),SEEK_CUR); //尋找位置
						
				fwrite( " ",sizeof(char),2,fout);				
				fwrite( &Empty,sizeof(record)-3,1,fout);
				fwrite( "\n",sizeof(char),1,fout);		
				
				fclose(fout);
			}
			printf("initial success!!\n\n");
			break;
		}
		else if(c=='N' || c=='n')
		{
			break;
		}
	}while(1);
};
//判斷是否為Null record
bool NullCompare(record A,record Empty) 
{
	/*因為strcmp無法考慮長度不同的問題，因此重寫一個比較string的
	以element一個一個比對*/ 
	//return true 代表 是null 也就是沒有資料的
	//return false 代表 該位置有資料 
	int i;
	
	for(i=0;i<strlen(Empty.date);i++)	//檢查date 
		if(A.date[i]!=Empty.date[i]) 
			return false;
			
	for(i=0;i<strlen(Empty.location);i++)	//檢查location 
	{
		if( A.location[i] != Empty.location[i] )
			return false;
	}
	
	for(i=0;i<strlen(Empty.name);i++)	//檢查name 
	{
		if( A.name[i] != Empty.name[i] )
			return false;
	}
	
	for(i=0;i<strlen(Empty.thing);i++)	//檢查thing 
	{
		if( A.thing[i] != Empty.thing[i] )
			return false;
	}
	
	return true;
}
int main()
{
	FILE *fout;
	fout=fopen("Appointment_Book.dat","r+b"); 
	static struct Record Empty;
	record newrecord[10];	//存放file裡的十筆資料的 
	int i=0;
	
	//判斷檔案是否存在 
	if( fout==NULL || fout==NULL )   
	{
		printf("Fail to open Appointment_Book.dat!!\n");
		printf("\n->Appointment_Book.dat established\n\n");
		printf("->please execute again...");
		FILE *f=fopen("Appointment_Book.dat","w");	//fail是因為沒有該檔案 ， 重新創該檔名的檔案 
		fclose(f);		//再重開有了 
		return;
	}
	
	// 將newrecord清空 
	strcpy( Empty.date , "0" );
	strcpy( Empty.location , "Null" );
	strcpy( Empty.name , "Null" );
	strcpy( Empty.thing , "Null" );
	for(i=0;i<10;i++)
		newrecord[i]=Empty;		
	
	//	是否初始化Appointment_Book.dat的格式 
	InitialFile(Empty);


	//讀取file裡的record資料 
	fseek(fout,sizeof(record)+4,SEEK_SET); //尋找第一筆資料的位置 
	for(i=0;i<10;i++)
	{
//測試用		printf("%d+",ftell(fout));
		fread(newrecord[i].date,4,1,fout); 
		fseek(fout,1,SEEK_CUR); 
		
		fread(newrecord[i].name,20,1,fout); //從file讀取一行資料到newrecord[i].name裡 
		fseek(fout,1,SEEK_CUR); 

		fread(newrecord[i].location,30,1,fout); //從file讀取一行資料到newrecord[i].location裡 
		fseek(fout,1,SEEK_CUR);  

		fread(newrecord[i].thing,80,1,fout); //從file讀取一行資料到newrecord[i].thing裡 
		fseek(fout,1,SEEK_CUR);					
	}
	
/*/	測試上面是否成功讀取
	for(i=0;i<10;i++)
	{
		printf("-> Date: +%-s+\t-> Name: +%-s+\n",newrecord[i].date,newrecord[i].name);
		printf("-> Location: +%-s+\n",newrecord[i].location);
		printf("-> Thing: +%-s+\n",newrecord[i].thing);
		printf("-----------------------\n");	
		
	}
*/
	// record最多10筆若要新增要從第i筆開始 ，因此尋找那個 i 
	for(i=0;i<10;i++)
	{
		if( NullCompare(newrecord[i],Empty) )
			break;	
/*測試用 
		printf("%s+\n->",newrecord[i].location);
		printf("%d=\n\n",strcmp(newrecord[i].location, Empty.location));			
*/ 		
	}
//測試用*/	printf("%d+",i);
	
	

	//選擇使用哪個service 
	int choice,n;   
	
 	while( ( choice = enterchoice() ) != QUIT  ) 
	{
		switch( choice )
		{	//新增整理date的排序 由小到大 
			case ENTER_RECORD:	//新增record 
			{
				if( i < 10 )
					EnterRecord( newrecord , i );
				i++;
				break;
			}
			case VIEW_DAY:	//看某天的record 
			{
				do
				{
					printf( "Enter the date number : " );
					scanf( "%d" , &n );
				}while( n > 31 || n <= 0 );
				ViewDay( newrecord , n );
				break;
			}
			case VIEW_WEEK:	//看某天開始的七天的record 
			{
				do
				{
					printf( "Enter the date number : " );
					scanf( "%d" , &n );
				}while( n > 31 || n <= 0 );
				
				ViewWeek( newrecord , n ); //輸出接下來七天 
				break;
			}
			case MODIFY:	//更改資料 
			{
				for(n=0;n<i;n++)
				{
					printf("-> Date: %-s\t-> Name: %-s\n",newrecord[n].date,newrecord[n].name);
					printf("-> Location: %-s\n",newrecord[n].location);
					printf("-> Thing: %-s\n",newrecord[n].thing);
					printf("-----------------------\n");
				}
				do
				{
					printf( "Enter the date number which you want modify : " );
					scanf( "%d" , &n );
				}while( n > 31 || n <= 0 );
				Modify( newrecord , n); 
				break;
			}
			case DELETE:	//刪除某行 
			{
			 	for(n=0;n<i;n++)
				{
					printf("-> Date: %-s\t-> Name: %-s\n",newrecord[n].date,newrecord[n].name);
					printf("-> Location: %-s\n",newrecord[n].location);
					printf("-> Thing: %-s\n",newrecord[n].thing);
					printf("-----------------------\n");
				}

				do
				{
					printf( "Enter the date number which you want delete : " );
					scanf( "%d" , &n );
				}while( n > 31 || n <= 0 );
				Delete( newrecord , n );
				i--;
				break;
			}
			case SEARCH:
				Search( newrecord );
				break;
			default:
				printf( "Incorrect service\n\n" );
		}
		setbuf( stdin, NULL );  //清空buffer裡的內容使得 enterchoice 正常運作 
	
	}
	//choice to save or discard
	Quit( newrecord , i );
	fclose( fout );
	
	
	return 0;
}

#include <stdio.h>
#include <string.h>
#include <stdbool.h>
enum Choice {ENTER_RECORD=1,VIEW_DAY,VIEW_WEEK,MODIFY,DELETE,SEARCH,QUIT};
enum WWWW {WHEN=1,WHO,WHERE,WHAT}; //4 個 W 

/*提供部分程式碼參考，其餘省略*/

typedef struct Record 
{
	char date[5];
	char name[21];
	char location[31];
	char thing[81];
	
}record;

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
		fread(newrecord[i].date,4,1,fout); 
		fseek(fout,1,SEEK_CUR); 
		
		fread(newrecord[i].name,20,1,fout); //從file讀取一行資料到newrecord[i].name裡 
		fseek(fout,1,SEEK_CUR); 

		fread(newrecord[i].location,30,1,fout); //從file讀取一行資料到newrecord[i].location裡 
		fseek(fout,1,SEEK_CUR);  

		fread(newrecord[i].thing,80,1,fout); //從file讀取一行資料到newrecord[i].thing裡 
		fseek(fout,1,SEEK_CUR);					
	}

	for(i=0;i<10;i++)
	{
		if( NullCompare(newrecord[i],Empty) )
			break;	
		
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

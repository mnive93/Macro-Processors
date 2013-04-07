#include<stdio.h>
#include<stdlib.h>
#include<ctype.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<unistd.h>
#include<string.h>
#include<fcntl.h>

int number=0;
int arg=0;
int nam=0;
struct deftab
{
char data[100];
}d[10];
struct nametab
{
char mac[100];
int start;
int end;
}n[10];
struct argtab
{
char value[10][10];
int count;
}a[50];
int search(char str[100])
{
	int i=0;

for(i=0;i<nam-1;i++)
	{

	if(strstr(str,n[i].mac)!=0)
		{
		return i;
		}
	}
return -1;
}
void populate()
{
	FILE  *fp,*fp1;
char line[100];

	fp=fopen("deftab.txt","r");
	fp1=fopen("namtab.txt","r");
	while(fgets ( line, sizeof(line), fp ) != NULL)
	{
	//printf("heree..\n");
		strcpy(d[number].data,line);
		number+=1;	
	}
	while(!feof(fp1))
	{
	fscanf(fp1,"%s %d %d",n[nam].mac,&n[nam].start,&n[nam].end);
	nam+=1;
	}
}
int separate(char operand[100])
{
int num;
num=atoi(&operand[1]);	
return num;
}
void macro_expand()
{
	int i,j=0;
	char line[100];
	FILE *fp;
	char buf='.';
	int pos1,num;
	int st,ed;
		int pos2=0;
	char name1[100],val[100],*temp;
	fp=fopen("macro.txt","r");		
	while(fgets ( line, sizeof(line), fp ) != NULL)
		{
			
			if(strstr(line,"MACRO")!=0)
				{
					do
					{
					
					fgets ( line, sizeof(line), fp );
					}while(strstr(line,"MEND")==0);
	
					}
else
{
		pos1=search(line);
			
			if(pos1!=-1)
			{
				printf(".%s\n",line);
				sscanf(line,"%s%s",name1,val);
				temp=strtok(val,",");
				while(temp!=NULL)				
				{
					
					strcpy(a[arg].value[a[arg].count],temp);
					a[arg].count+=1;
					temp=strtok(NULL,",");
				}
				
				
				st=n[pos1].start;
				ed=n[pos1].end;
				for(i=st+1;i<=ed;i++)
					{
						if(strstr(d[i].data,"?")!=0)
							{
								sscanf(d[i].data,"%s %s",name1,val);
							num=separate(val);
							strcpy(val,a[arg].value[num-1]);
							sprintf(line,"%s %s",name1,val);
							printf("%s\n",line);	
							}
					}
			arg+=1;		
			}
else
printf("%s\n",line);
		}	
		}	
			
}
int main()
{
char buf,macro[100][100];
int i=0,j=0;
populate();
macro_expand();
return 0;
}


#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<dirent.h>
#include<sys/stat.h>
#include<fcntl.h>
#include<sys/types.h>
#include<string.h>

struct FileInfo
{
	char Fname[256];
	int Fsize;
};

int main(int argc,char* argv[])
{
	DIR * dp=NULL;
	struct dirent *dip=NULL;
	struct stat sobj;
	int ret=0,fddest=0,fdsrc=0;
	char name[300]={'\0'};
	struct FileInfo fobj;
	char Buffer[1024];
	
	dp = opendir(argv[1]);
	if(dp==NULL)
	{
		printf("Unable to open directory\n");
		return -1;
	}
	
	fddest=creat(argv[2],0777);
	if(fddest==-1)
	{
		printf("Unable to create new file\n");
		closedir(dp);
		return -1;
	}
	
	printf("Files are : \n");
	while((dip=readdir(dp))!=NULL)
	{
		sprintf(name,"%s/%s",argv[1],dip->d_name);
		ret=stat(name,&sobj);
		if(S_ISREG(sobj.st_mode))
		{
			strcpy(fobj.Fname,dip->d_name);
			fobj.Fsize=sobj.st_size;
			
			write(fddest,&fobj,sizeof(fobj));
			
			memset(&fobj,0,sizeof(fobj));
			fdsrc=open(name,O_RDONLY);
			while((ret=read(fdsrc,&Buffer,sizeof(Buffer)))!=0)
			{
				write(fddest,&Buffer,ret);
			}
			memset(Buffer,0,sizeof(Buffer));
			close(fdsrc);
			
			printf("%s : ",dip->d_name);
			printf("%ld\n",sobj.st_size);
		}
	}
	closedir(dp);
	return 0;
}

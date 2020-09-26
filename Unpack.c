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
	int ret=0,fddest=0,fdsrc=0,size=0;
	char name[300]={'\0'};
	struct FileInfo fobj;
	char *Buffer=NULL;

	fdsrc=open(argv[1],O_RDONLY);
	if(fdsrc==-1)
	{
		printf("Unable to open file/n");
		return -1;
	}
	
	while((ret=read(fdsrc,&fobj,sizeof(fobj)))!=0)
	{
		printf("File name is %s Size is : %d\n",fobj.Fname,fobj.Fsize);
		fddest=creat(fobj.Fname,0777);
		if(fddest==-1)
		{
			printf("Unable to create file\n");
			return -1;
		}
		Buffer=(char*)malloc(fobj.Fsize);
		
		read(fdsrc,Buffer,fobj.Fsize);
		write(fddest,Buffer,fobj.Fsize);
		
		free(Buffer);
		close(fddest);
	}
	close(fdsrc);	
	return 0;
}

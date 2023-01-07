
#include <winbgim.h>
#include <time.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct regNodo
{
   void *imagen;
   int corX, corY;
   struct regNodo *ant,*sig,*arriba, *abajo;
}*NODO_MALLA;

typedef struct
{
  NODO_MALLA pri, ult;
  int nRen, nCol;
}MALLA;

void inicializaMalla( MALLA * );
int creaNodo(NODO_MALLA*, void *, int, int);
void creaMalla( MALLA *);
void imprimeMalla( MALLA );
void eliminaMalla( MALLA * );
int imprimeMenu();
void dibujaMenu();
void malla();
void dibujaLinea( int x1, int y1, int x2, int y2, int color );
void leerTexto(int ,int , char * );
void retraso(int );
void leerDimensiones( MALLA *);
void *abrirImagen( char * );

int main()
{
    initwindow( 1358, 700 ); //open a 400x300 graphics window
    
    dibujaMenu();
    malla();
    
    getch();
    closegraph();        //close graphics window
}

void malla()
{
    MALLA malla;
    int corX,corY,color,tamX,tamY,x1,y1,x2,y2;
    x2 = y2 = 0;
    char name[20];
    
    x1 = 175;
    y1 = 25;
    x2 = 278;
    y2 = 52;
    
    inicializaMalla( &malla );
    
    do
    {
       dibujaMenu();
       
       corX = mousex();
       corY = mousey();
       
      
       if( corX > x1 && corX < x2 && corY > y1 && corY < y2 ){  //nuevo          
             dibujaLinea( x1 , y2 + 4, x2 , y2 + 4 , YELLOW );
             
             if( ismouseclick( WM_LBUTTONDOWN )){
                    eliminaMalla( &malla );
                    leerDimensiones( &malla );
                    creaMalla( &malla );
             }
       }else{
               dibujaLinea( x1 ,  y2 + 4, x2 , y2 + 4 , BLACK);
               
               if( corX > x2 + 15 && corX < x2 + 95  && corY > y1 && corY < y2  ){  //Abrir
                     dibujaLinea( x2+15,y2+4, x2 + 130 , y2+4, YELLOW );
                       
                         if( ismouseclick(WM_LBUTTONDOWN ) ){
                            imprimeMalla(malla);
                                 
                         }
                   //    printf( " name : %s\n", name );*/        
                }else 
                       dibujaLinea( x2+15, y2+4 , x2 + 130 , y2 + 4, BLACK );         
                        
                  
                }  
             
           clearmouseclick(WM_LBUTTONDOWN );
       
       }while(!kbhit());
}

void inicializaMalla( MALLA *m )
{
   m -> pri = NULL;
   m -> ult = NULL;
}

void eliminaMalla( MALLA *m )
{
  NODO_MALLA aux;
  int i, j;
  
  if( m -> pri )
  {
     m -> ult = m -> pri;

     for( i = 1; i <= m -> nRen; i++ )
     {
         aux = m -> pri;
         m -> pri = m -> pri -> abajo;
    
        for( j = 1; j <= m -> nCol; j++ )
        {
            aux -> arriba = NULL;
            aux -> abajo = NULL;
            
            free( aux );
            
            if( !j == m -> nCol )
            {
               aux = aux -> sig;
               aux -> ant -> sig = NULL;
               aux -> ant = NULL;
            }   
        }
     }
   }
}

void creaMalla( MALLA *m)
{
   int i,j, x, y;
   NODO_MALLA aux, antRen,nuevo;
   
   void *imagen;
   y = 100;
   
   //printf( "\n x: %d y :%d " ,nR, nC );
   //printf( "\n  m : %p\n "  , m );
   
   srand( time(NULL ) );
   
 
   for( i = 1; i <= m -> nRen; i++, y += 36  )
   {
        x = 50;
     for( j = 1; j <= m -> nCol; j++ ,x += 90)
     {
       switch(j)
       {
         case 1:  imagen = abrirImagen( "robot" );
                  break;
         case 2:  imagen = abrirImagen( "robotCd" );
                  break;
         case 3:  imagen = abrirImagen( "robotCd2" );
                  break;
       }  
        
        if( creaNodo( &nuevo, imagen , x , y ) )
          { 
               if( i == 1 )
               {
                    if( !m -> pri ){
                         m -> pri = nuevo;  
                         aux = m -> pri;
                    } else
                        {
                           m -> ult -> sig= nuevo;
                           nuevo -> ant = m -> ult;
                        } 
                      
                      m -> ult = nuevo;
                      m -> ult -> sig = m -> pri;
               }else
                   {
                     if( !antRen -> abajo )
                     {
                        antRen -> abajo = nuevo;
                        nuevo -> arriba = antRen;
                        aux = antRen -> abajo;
                     }else
                        {
                           
                           antRen -> abajo -> sig = nuevo;
                           antRen -> sig -> abajo = nuevo;
                           nuevo -> ant = antRen -> abajo;
                           nuevo -> arriba = antRen -> sig;
                           
                           antRen = antRen -> sig;
                                                   
                         }
                  }
              }
            
           }       
           antRen = aux;
     }
}

void *abrirImagen( char * name )
{
    FILE *ptrArch;
    void *imagen;
    long tamImagen;
    int x1I, y1I, x2I, y2I, tamPixel,;
    
    
    if( ptrArch = fopen( name , "rb" ) )
    {
        fread(&tamPixel, sizeof( int ), 1 , ptrArch );
        fread( &x1I, sizeof( int ), 1 , ptrArch );
        fread( &y1I, sizeof( int ), 1 , ptrArch );
        fread( &x2I, sizeof( int ), 1 , ptrArch );
        fread( &y2I, sizeof( int ), 1 , ptrArch );
        
      
        fread( &tamImagen, sizeof( long ), 1 , ptrArch );
        printf( " x1: %d y1 : %d", x1I, y1I );
        printf( " tamImagen: %ld", tamImagen);
       
        imagen = malloc( tamImagen );
      
        fread( imagen, tamImagen, 1 , ptrArch );
       
        //putimage(x1I,y1I, imagen ,COPY_PUT );   
        
       //free( imagen );
       fclose( ptrArch );
    }else 
        {
           outtextxy( 260, 275, " No se encontro el archivo imagen               " );
           retraso( 1000 );
        }
   
    return( imagen );    
}  


int creaNodo( NODO_MALLA  *m, void *img, int x, int y )
{
  
  int ret = 0;
  
  *m = ( NODO_MALLA )malloc( sizeof( struct regNodo ) );
   
   if( *m )
   {
     (*m) -> imagen = img;
     (*m) -> corX = x;
     (*m) -> corY = y;
     (*m) -> ant = NULL;
     (*m) -> sig = NULL;
     (*m) -> arriba = NULL;
     (*m) -> abajo = NULL;
     
     ret = 1;
  }
  
  return( ret );
}

void imprimeMalla( MALLA m )
{
  NODO_MALLA aux,ant;
  int i , j, cont = 0;
//  char cad[10];
  
  if( m.pri )
  {
     aux = m.pri;
     
     for( i = 1; i <= m.nRen; i++ , aux = aux -> abajo )
     {
       ant = aux;
       
       for( j = 1; j <= m.nCol; j++, aux = aux -> sig )
       {
         putimage( aux -> corX , aux -> corY , aux -> imagen ,COPY_PUT );
          /*setcolor( 1+  rand()% + 11  );
          circle( aux -> corX, aux -> corY , 15 );
            */  
         /* setcolor( WHITE );
          sprintf( cad, " %d ", aux -> info);
          settextstyle( 11, 0 , 2 );
          outtextxy( aux -> corX -7, aux -> corY - 7, cad );
     
       */}
       
       aux = ant;
     }
  }else
     {
        outtextxy( 200, 200, " No se a creado ninguna malla " );
        retraso( 600 );
        cleardevice();
     }

}


void dibujaLinea( int x1, int y1, int x2, int y2, int color )
{
    setcolor( color );
    setlinestyle( SOLID_LINE, 0 , 6 );
    line( x1 , y1, x2 , y2 );
} 

void dibujaMenu()
{
    int x1, y1, x2, y2, z ;
    
    x1 = 180;
    y1 = 18;
    x2 = x1 + 80;
    y2 = y1 + 50;
    z = 10;
    
    setcolor( 7 );
    setlinestyle( SOLID_LINE, 0 , 4 );
    
    setcolor( WHITE );
    settextstyle( 4, 0 , 2 );
     
    outtextxy( x1, y1 + z, "Nuevo" );
    outtextxy( x2 + 40 , y1 + z, "Imprime" );
}

void leerDimensiones( MALLA *m )
{
   int x1, y1, x2, y2 ;
   char cad[50];
   
   x1 = 300;
   y1 = 330;
   x2 = 650;
   y2 = 420;
   
   setcolor( YELLOW );
   rectangle( x1 , y1, x2, y2 );
   setfillstyle(SOLID_FILL, BLACK);
   floodfill( x1 + 10, y1 + 10 , YELLOW);
   
   setbkcolor( BLACK );
   setcolor( WHITE );  
   settextstyle( 9, 0 , 1 );
   
   outtextxy( x1 + 20, y1 + 30, " No de reglones : " );
   leerTexto( x1 + 240, y1 + 30, cad );
   
   m -> nRen = atoi( cad );
   
    outtextxy( x1 + 20, y1 + 30, " No. de columnas :" );
    leerTexto( x1 + 240, y1 + 30, cad );
   
   m -> nCol = atoi( cad );
   
   setbkcolor( BLACK );
   cleardevice();
}


void leerTexto(int x,int y, char cadena[])
{
 char tecla, var;     
 int contador=0;
 cadena[0]='\0';
 
 do{
      //Si no se presiona una tecla, se imprimira un guion definidamente
      do{  //párpadeo
			 setcolor(15);
			 outtextxy(x+textwidth(cadena),y,"_       ");
			 retraso(50);
			 setcolor(0);
			 outtextxy(x+textwidth(cadena),y,"_       ");
			 retraso(50);
			 setcolor(15);
      }while(!kbhit());
     
      tecla = getch();
     
      if(tecla==0)  // si es código extendido
         tecla=getch();
        if(tecla==8 && contador > 0)  // se presion¢ <backspace>
			{
				 setcolor(BLACK);
				 outtextxy(x,y,cadena);  // se borra en la pantalla
				 cadena[--contador]='\0';  //se borr¢ £ltimo caracter del arreglo
				 setcolor( WHITE );
				 outtextxy(x,y,cadena);
			}
		 else
			{  
              if(tecla!=13)
              {  
				 cadena[contador++]=tecla;
				 cadena[contador]='\0';
				 outtextxy(x,y,cadena);
              }
            }    
  }while(tecla!=13); 
}

void retraso(int ms)
{
  clock_t i,j;
 
  i=clock();
 
  do
  {
    j=clock();
  }while((j-i) < ms);  
}




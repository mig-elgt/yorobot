
/*

 Universidad Autonoma de San Luis Potosi
 Facultad de Ingenieria
 
 Materia: Estructuras de Datos y Algoritmos B
 Prof. M.C De la Cruz Lopez Miguel Angel
 
 Alumno: Galicia Torrez Miguel Angel
 Carrera: Ing. En Informatica
 
 Programa: Simulacion de un juego con la implentacion de estructuras dinamica( LISTAS ) y  
           funciones graficas de Borland
 
 15/12/2010
*/

#include <winbgim.h>
#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <string.h>

#define TAM_IMG 13
#define TALLA 26
#define TALLA_A 20
#define REN_M 1200
#define COL_M 118

typedef struct
{
  int puntos;
  char name[20];
}RECORDS;

typedef struct regBalas
{
  int corX, corY;
  struct regBalas *sig;
}*BALAS;

typedef struct regImg
{
  void *img;
  struct regImg *sigImg;
}*IMAGEN;

typedef struct regNodo
{
   char name[10];
   void *imagen;
   int existencia, corX, corY,dir;
   struct regNodo *ant,*sig,*arriba, *abajo;
}*NODO_MALLA;

typedef struct regA
{
   NODO_MALLA ptrM;
   struct regA *sigA;
}*ARO;

typedef struct
{
   int nElem;
   ARO arrayA[TALLA_A];
}VA;

typedef struct
{
   int nVidas;
   NODO_MALLA ptrM;
   BALAS ptrB;
}RE;

typedef struct 
{
  int nElem;
  RE robotEn[5];
}RBT_ENE;

typedef struct
{
  int dirBloque;
  NODO_MALLA posBloque[10];
  NODO_MALLA ptrBloque;
}VECTOR_B;

typedef struct
{
  NODO_MALLA pri, ult;
  int nRen, nCol;
}MALLA;

void menu( RECORDS * );
void leerArchivoText( char *, int , int  , int);
int leerNombre( RECORDS * );
void imprimeTiempo( time_t tS, int *seg , time_t tM, int *min);
void lee_texto(int ,int , char *);
void guardaRecords( RECORDS );
void iniMalla( MALLA * );
void iniArrayIMG( IMAGEN * );
int creaNodo(NODO_MALLA*, int, int);
void creaMalla( MALLA *);
void retraso(int );
void iniciaJuego(RECORDS *);
void cargarIMG(IMAGEN * );
void *abrirImagen( char * );
void insIMG( IMAGEN *, void *);
int creaNodoIMG( IMAGEN *, void * );
void escenario( IMAGEN *, MALLA, RECORDS * );
void camina( IMAGEN *, NODO_MALLA *, NODO_MALLA *, char, IMAGEN *);
void dibujaEscenario(IMAGEN, IMAGEN , NODO_MALLA, IMAGEN, NODO_MALLA *);
void iniEscenario( MALLA , IMAGEN *, NODO_MALLA *, NODO_MALLA *, VECTOR_B *,NODO_MALLA *,NODO_MALLA *, VA * );
void cambiaDirBloques( VECTOR_B * );
void mueveBloques( VECTOR_B *, void *, RBT_ENE *);
void brincaRobot( NODO_MALLA *,NODO_MALLA *, IMAGEN *imgP, int *cont, char *dir, int *band,IMAGEN *);
void estadisticas( void *, void* ,char *);
void determinaEstado( NODO_MALLA *, NODO_MALLA *, int *, char , int *, IMAGEN, IMAGEN * , RBT_ENE, VECTOR_B *);
void dibujaEscenario( NODO_MALLA , IMAGEN, VECTOR_B * ,void *, NODO_MALLA, void *, NODO_MALLA, void *);
void mueveEscenario( VECTOR_B *,NODO_MALLA *, NODO_MALLA *, NODO_MALLA *, NODO_MALLA *, VA *);
void iniBalas( BALAS *);
int creaBala( BALAS *, int , int  );
void insBala( BALAS * , int, int );
void eliminaBala( RBT_ENE *, BALAS *, NODO_MALLA );
void dibujaBalas( RBT_ENE, BALAS);
void insRobotEne( RBT_ENE *, NODO_MALLA  );
int creaRE( RBT_ENE *, NODO_MALLA  );
void activaBloque( VECTOR_B * , int);
void eliminaRobotEne( RBT_ENE * );
void iniRE( RBT_ENE * );
void insBalasRE( RBT_ENE *, int, int* );
int creaAro(ARO*, NODO_MALLA );
void insAro( ARO *, NODO_MALLA );
void dibujaAro( VA );
void iniAro( VA * );
void generaAros( NODO_MALLA *, VA *, int, int);
void eliminaAros(VA *, NODO_MALLA , NODO_MALLA);
void ordenaBurbuja( RECORDS *, int );
void leerRecords();
int nJugadores();
void imprimeRecords( RECORDS *a, int nJ );
int reloj(time_t,time_t);
void mensaje(RECORDS , void * );
void eliminaMalla( MALLA * );
void limpiaPantalla();
void dibujaLinea( int , int , int , int , int  );
void liberaArrayImg( IMAGEN * );


//Variables globales
int cuentaSal = 0;
int c2 = 0;
int vidas = 10;
int balas = 50;
int bandVH = 1;
int bandVE = 1;
int bandAux = 1;
int mueve = 0;
int xB = 5;
int escen = 1;
int puntos = 0;
int final = 0;

int main()
{
  initwindow( 1000, 700 ); 
  RECORDS rec;
  
  strcpy( rec.name, "" );
  rec.puntos = 0;
  
  menu( &rec );
 // iniciaJuego( &rec );
  delay(500); 
  closegraph();
}

/* Esta funcion es la del menu del juego, reciibe como parametro la estructura records por referencia, los unicos campos
 de insteres son el nombre y los puntos por acumulador el jugador durante el juego */
void menu(RECORDS *rec)
{
  
  int corX, corY, x1, y1, x2, y2, z , y, band = 0;
  int bandAux;
  
  x1 = 100;
  y1 = 18;
  x2 = x1 + 80;
  y2 = y1 + 50;
  y = 150;
 
  leerArchivoText( "acercaDe.txt", 250, 140 , 1); 
   
  do
  {
    setlinestyle( SOLID_LINE, 0 ,  2);
    
    setcolor( WHITE );
    settextstyle( 4, 0 , 2 );
     
    outtextxy( x1, y1 , "Jugar" );
    outtextxy( x2 + 65 , y1 , "Records" );
    outtextxy( x2 + 245, y1 , "Ayuda" );
    outtextxy( x2 + 390 , y1 , "Acerca de" );
    outtextxy( x2 + 590, y1 , "Salir" );
    
    setcolor( LIGHTBLUE );
    rectangle( 5, 2, 985, y1 + 50 );
    rectangle(5, y1 + 55, 985, 687 );
    
    corX = mousex();
    corY = mousey();
    
    if( corX > x1 && corX < x2 && corY > y1 && corY < y2 )
    {          
         dibujaLinea( x1 , y1+26 , x2 , y1 + 26, YELLOW );
          
         if( ismouseclick( WM_LBUTTONDOWN) )
         { 
             if(  bandAux = leerNombre( rec ) == 1 ) 
             {
                   iniciaJuego( rec );
                   guardaRecords( *rec );
             }
             
             leerArchivoText( "acercaDe.txt", 250, 140 , 1);
                
         }
    }else{
              dibujaLinea( x1 ,  y1 + 26, x2 , y1 + 26, BLACK);
               
               // Opcion de records
               if( corX > x2 + 65 && corX < x2 + 185  && corY > y1 && corY < y2  ){  //Abrir
                     dibujaLinea( x2+65,y1 + 26, x2 + 185 , y1 + 26, YELLOW );
                        
                         if( ismouseclick(WM_LBUTTONDOWN ) )
                                leerRecords();
                }else{   
                         dibujaLinea( x2+65, y1 + 26 , x2 + 185 ,y1 + 26, BLACK );         
                 
                           if( corX > x2+(390-x2)+ 33 && corX < x2+(516-x2)-2  && corY > y1 && corY < y2  ){  //Guardar
                              dibujaLinea( x2+(390-x2) +33, y1 + 26, x2+(516-x2) -2 ,y1 + 26, YELLOW );
                              
                                 if( ismouseclick( WM_LBUTTONDOWN ) ) 
                                        leerArchivoText( "ayuda.txt", 250, 140 , 1);
                                       
                           }else{
                                   dibujaLinea( x2+(390-x2) + 33, y1 + 26, x2+(516-x2) -2 ,y1 + 26, BLACK );         
                                 
                                  if( corX > x2+(540-x2)+30 && corX < x2+(755-x2)-41  && corY > y1 && corY < y2  ){  //Guaradar como 
                                        dibujaLinea( x2+(540-x2)+30, y1 + 26, x2+(755-x2)-41,y1 + 26,YELLOW );
                                        
                                        if( ismouseclick( WM_LBUTTONDOWN ) ) 
                                              leerArchivoText( "acercaDe.txt", 250, 140 , 1);
                                      
                                  }else
                                    {
                                       dibujaLinea( x2+(540-x2)+30, y1 + 26, x2+(755-x2) - 41,y1 + 26 ,BLACK );
                                      
                                       
                                       if( corX > x2+(775-x2)-2 && corX < x2+(880-x2) -50 && corY > y1 && corY < y2  ){  //Salir 
                                            dibujaLinea( x2+(775-x2)-2, y1 + 26, x2+(880-x2)-50, y1 + 26,YELLOW );
                                             
                                              if( ismouseclick( WM_LBUTTONDOWN ) )
                                                       band= 1;
                                         }else  
                                                dibujaLinea( x2+(775-x2)-2, y1 + 26, x2+(880-x2)-50,y1 + 26,BLACK );
                                                    
                                    }
                                 }
                             }
                }
          clearmouseclick(WM_LBUTTONDOWN );
     
     delay(1);  
    }while ( !band);   
}

/*
 Esta funcion se encarga de dibujar una linea abajo de alguna opcion del menu
 recibe como parametros, las coordenas de la opcion del menu y el color que se dibujara*/
void dibujaLinea( int x1, int y1, int x2, int y2, int color )
{
    setcolor( color );
    setlinestyle( SOLID_LINE, 0 , 6 );
    line( x1 , y1, x2 , y2 );
} 

/* Se hace lectura de un archivo binario donde se guardo la informacion del usuario 
   guardandola en un arreglo de tipo Records  y posteriormente ordenar el arreglo*/
void leerRecords()
{
  RECORDS recAux;
  RECORDS *arrayRec;
  int  nJug, i  = 0;
  FILE *ptrArch;
  
  
  if( nJug = nJugadores() )// Se determina el numero de jugadores existentes en el archivo
  { 
      //Reservacion de espacio de memoria para el arreglo de tipo Records
      arrayRec = ( RECORDS*)malloc( sizeof( RECORDS ) * nJug -1 ); 
      ptrArch = fopen( "records.dat", "rb+" );
      
      // Se almacenan los datos del jugador en el arreglo de tipo Records arrayRec
      if( ptrArch != NULL )
      {
        while( !feof( ptrArch ))
        {      
         fread( &recAux, sizeof( RECORDS ), 1, ptrArch );
         
         strcpy( arrayRec[i].name , recAux.name );
         arrayRec[i].puntos = recAux.puntos;
         
         i++;
        }
      }else
         printf( "Error no se puede leer el archivo " );
  
      fclose( ptrArch );
      ordenaBurbuja( arrayRec , nJug -1 );// una ves que se capturarn los jugadores,se ordenan decrecientemente
   }
   
   imprimeRecords( arrayRec , nJug -1 );
   
   if( nJug )
       free( arrayRec );// Liberacion de memoria
}
/*
  Para saber el numero de jugadores, se abre un archivo binario ( records.dat )
  y se retorna los N jugadores, este valor retornado por la fucnion nos sera util para el monebto de 
  imprimir el puntaje de los jugadores en la ventana de records*/
int nJugadores( )
{

   int nJugAux = 0;
   
   RECORDS recAux;
   FILE *ptrArch;
   
   if(( ptrArch = fopen( "records.dat", "rb" ) ) != NULL  )
       while( !feof( ptrArch ))
       { 
          fread( &recAux, sizeof( RECORDS ), 1, ptrArch );
          nJugAux++;
       }
   else
         printf( "Error no se puede leer el archivo " );
        
    fclose( ptrArch );
   
   return ( nJugAux );
   
}

// Esta funcion se encarga de limpiar la pantalla del menu, cada ves que se seleciona una opcion se ejecuta
void  limpiaPantalla()
{
   setfillstyle(SOLID_FILL, BLACK);
   floodfill( 300,200, LIGHTBLUE);
}
/*
 Esta funcion es para imprimir los records en la opcion del menu, recibe como parametros, un arreglo de tipo
 estructura RECORDS y el numero de jugadores */
void imprimeRecords( RECORDS *a, int nJ )
{
  
  limpiaPantalla();
  
  int x1,j, x2, y1, y2,x,y, corX,corY, bandera = -1;
  char cad[10];
  
  y = 150; 
  x = 250;
  
  setlinestyle( SOLID_LINE,0, 1);
  setcolor( YELLOW);
  rectangle( 230, y, 770, y + 470 );
  line(260, y + 90 , 740, y + 90 );
  
  setcolor( WHITE );
  settextstyle( 4, 0 , 3 );
  outtextxy( x + 30 , y + 30 , " Nombre             Puntos" );
  setcolor( YELLOW);
  line(500, y + 30 , 500, y + 430);
  setcolor( WHITE);
  
  // Imprime el nombre y los puntos de cada jugador
  for( j = 0; j < nJ ; j++, y += 30  )
  {
    settextstyle( 4, 0 , 1 );
    outtextxy( x + 60 , y + 70 + 50  , a[j].name);
    
    sprintf(cad, "%d", a[j].puntos );
    
    if( a[j].puntos < 100 && a[j].puntos > 0)
         outtextxy( x + 335 , y + 70 + 50 , cad);
    else
        if( a[j].puntos == 0 )
             outtextxy( x + 351 , y + 70 +50 , cad);
        else
             outtextxy( x + 320 , y + 70 +50 , cad);
   }
  
}

/*
 La funcion se encarga de guardar la estructura Records en un archivo de tipo binario para posteriormente leerla y 
 vislumbrar el puntaje almacenado en el archivo, recibe como parametro la estructura Records */
void guardaRecords( RECORDS rec )
{
  FILE *ptrArch;
  
  ptrArch = fopen( "records.dat", "ab" );
  
  if( ptrArch != NULL )
      fwrite( &rec, sizeof( RECORDS ), 1 , ptrArch );
  else
      printf(" Error no se pudo guardar eñ archivo" );
  
  fclose( ptrArch );

}
/*Esta funcion es para ordenar el puntaje de los jugadores, se opera en el momento de imprimir los records
  recibe como parametros la estructura y el nuemro de jugadores */
void ordenaBurbuja( RECORDS *a , int nJ )
{
  int i , pas, bandera = 1;
  RECORDS aux;

  for( pas = 1; pas < nJ  && bandera == 1  ; pas ++ )
  { 
     bandera  = 0; 
      
    for( i = nJ -1; i > 0 ; i-- )
         if( a[ i ].puntos > a[ i - 1 ].puntos )
         { 
           aux.puntos  = a[ i ].puntos;
           a[ i ].puntos = a[ i - 1 ].puntos;
           a[ i - 1 ].puntos = aux.puntos;
           
           strcpy( aux.name ,  a[ i ].name );
           strcpy( a[ i ].name ,  a[ i - 1].name );
           strcpy( a[ i - 1].name ,  aux.name );
           
           bandera = 1;
         } 
  }
}

/* Esta funcion es  para capturar el nombre del jugador, al terminar de escribir apareceran dos botones de continuar 
   o cancelar, recibe como parametro la estructura RECORDS por referencia, la funcion returna un 1 si se escogio 
   ir al juego 0 un 2 si fue cancelar*/
int leerNombre(RECORDS *r )
{
  limpiaPantalla();
  setlinestyle( SOLID_LINE,0, 2);
  char cadena[50];
  int y;
  int corX, corY, bandera = -1;
  int band = 0;
  
  y = 200;
  setcolor( YELLOW);
  rectangle( 230, y , 770, y + 340 );
  
  setcolor ( WHITE );
  outtextxy( 330, y + 50 , " Introduzca su nombre " );
  
  rectangle( 320, y + 100 , 670, y + 160 );
  lee_texto( 345 ,y + 120, cadena );
  
  settextstyle( 11 , 0 , 1 );
  
  rectangle( 290, y + 210 , 440, y + 270 );
  outtextxy( 310, y + 230 , " I R  A L   J U E G O" );
  
  rectangle( 560, y + 210 , 710, y + 270 );
  outtextxy( 585, y + 230 , " C A N C E L A R " );
  
  do
  {
    corX = mousex();
    corY = mousey();
    
    if( corX > 290 && corX < 440 && corY > y + 210 && corY < y + 270 )
    {   
        setcolor( YELLOW );
        setlinestyle( 0, 0, 6 );       
        rectangle( 290, y + 210 , 440, y + 270 );
          
         if( ismouseclick( WM_LBUTTONDOWN) )
             band = 1;
     }else
       {
          setcolor( BLACK );
          setlinestyle( 0, 0, 6 );       
          rectangle( 290, y + 210 , 440, y + 270 );   
          
          setlinestyle( 0, 0, 2 );  
          setcolor( WHITE );       
          rectangle( 290, y + 210 , 440, y + 270 );
          
          if( corX > 560 && corX < 710 && corY > y + 210 && corY < y + 270 )
          {   
               setcolor( YELLOW );       
               setlinestyle( 0, 0, 6 ); 
               rectangle( 560, y + 210 , 710, y + 270 );
          
              if( ismouseclick( WM_LBUTTONDOWN) )
                   band = 2;
          }else
              {  
                 setcolor( BLACK );
                 setlinestyle( 0, 0, 6 );  
                 rectangle( 560, y + 210 , 710, y + 270 );
                  
                 setcolor( WHITE );       
                 setlinestyle( 0, 0, 2 );
                 rectangle( 560, y + 210 , 710, y + 270 );
              }
           }
  
   clearmouseclick(WM_LBUTTONDOWN );
   delay(1);  
  
  }while ( band != 1 && band != 2 ); 
  
  if( band == 1 )
  {
     strcpy( r -> name , cadena ); 
     retraso( 1000 );
     limpiaPantalla();
  }
  return( band );
}

/*Esta funcion es para leer texto en modo grafico, recibe dos parametros de tipo entero, que indican las coordenadas
 en donde el cursos inicara el comienzo de la escritura y una cadena de caracteres, como auxiliar dentro de la funcion*/
void lee_texto(int x,int y, char cadena[])
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

/* Esta funcion es para leer un archivo en modo texto, estos archivos son leeidos para utilizarlos en las opciones del menu
 de ayuda y acerca de, reciben como parametros, una cadena de caracteres que representa el nombre que sera leido, dos datos de
 tipo entero que representan las coordenas en donde se iniciara la impresion del archivo y por elultimo un nuemro que
 indica el tipo de archivo por abrir */ 
void leerArchivoText( char *name, int x, int y , int num)
{
  
  limpiaPantalla();
  
  FILE *ptrA;
  char cadena[900];
  int x1, y1, x2, y2 ;
  
  x1 = 250;
  y1 = 570;
  x2 = 300;
  y2 = 600;
  
  setcolor(WHITE ); 
  
  setlinestyle( SOLID_LINE,0, 1);
  setcolor( YELLOW);
  rectangle( 200, y +10, 800, y + 490 );
  
  ptrA = fopen(  name , "r" );
  
  if( ptrA != NULL )
  {
     while( !feof( ptrA ) )
     {
        fgets( cadena, 900 , ptrA );
         
        cadena[ strlen( cadena )  ] = '\0' ;
        setcolor( WHITE );
     
        settextstyle( 11 , 0 , 1 );
        outtextxy( x-10 , y + 40 , cadena );
        y += 16;
            
     } 
     fclose( ptrA );
  }else
       outtextxy( 300, 400, "Error" );
}

/* La funcion iniciaJuego es la encargada de llevar a cabo todos los procesos principales del juego, recibe como parametro
  la estructura records por referencia */
void iniciaJuego( RECORDS *rec)
{
  MALLA malla;
  IMAGEN arrayImg[TAM_IMG];
  
  iniArrayIMG( arrayImg );
  iniMalla( &malla );
  creaMalla( &malla );
  cargarIMG( arrayImg );
  escenario( arrayImg, malla, rec ); 
}

/* Esta funcion es la esencial del juego ya que lleva toda la logica del juego, recibe como parametros un arreglo de 
  apuntadores a la estructura IMAGEN, esta estructura representa un nodo para almacenar cualquier imagen, todas las imagenes 
  del juego fueron capturadas en el este arreglo, el arreglo almacena un conjunto de lista circulares, que daran
  la secuencia de las imagenes, tambien recibe otra estructura de tipo MALLA , esta es la estructura del 
  juego, y por ultimo recibe la estructura RECORDS para el contro de puntos*/
  
void escenario( IMAGEN *aImg, MALLA malla , RECORDS *rec)
{
    NODO_MALLA aux, auxC, auxD, auxE, robotIzq, robotDer,bloqueBase,bloqueBase2, robotIzqAux, robotDerAux,chip, bandera;
    IMAGEN nodoImg, aux1, aux2, aux3, robot;
    VECTOR_B arrayBloques[TALLA];
    BALAS balasE, balasH, auxB;
    RBT_ENE robotEne;
    VA aros;
    ARO auxF;
    
    int arrayCorY[3], tiempo, ret, bandM ,i, band4, minutos, page, xBaux, band,band2, u, contM, bandBal, band3, cont = 1;
    time_t tA, tB ,t1 , t2, t3, t4; 
    void *imgAux;
    char dir;
    
    rec -> puntos = 0;
    tA = time( NULL );
    
    arrayCorY[0] = 700;// Este arreglo controla el nuemro de robot enemigos existen en el juego, los arreglos son tipo 
    arrayCorY[1] = 700;
    arrayCorY[2] = 700;
    balasH = NULL;
    page = band = bandM = band4 = 1;
    band2= band3 = bandBal = contM = 0;
    ret = 20;
    xBaux = xB;
    
    robot = aImg[0];
    aux1 = aImg[1];
    aux2 = aImg[2];
    aux3 = aImg[3];
    
    // SE realizan las inicializaciones de todas las instantancia creadas
    iniAro( &aros );
    iniRE( &robotEne );
    iniBalas( &balasE ); 
    iniEscenario( malla, aImg, &robotIzq, &robotDer, arrayBloques, &chip, &bandera, &aros);
    
    robotIzqAux = robotIzq;
    robotDerAux = robotDer;
   
    // Con este ciclo se posiona el bloque base debajo del robot 
    bloqueBase = robotIzq;
    for(u  = 1; u < 12; u++, bloqueBase = bloqueBase -> abajo );
    
    bloqueBase2 = bloqueBase -> sig -> sig -> sig -> sig -> sig -> sig -> sig;
    
    do
    {
    
      do 
      {
       t1 = time ( NULL );
       tB = time( NULL ); 
        
       if( page == 1) 
           page = 0;
       else
         page = 1;
      
      setactivepage(page);
      cleardevice();
      estadisticas( aImg[0] -> img, aImg[10] -> img , rec -> name);
      cambiaDirBloques( arrayBloques );
      mueveBloques( arrayBloques , aImg[6] -> img, &robotEne );
      brincaRobot( &robotIzq, &robotDer, &aux3, &cont, &dir, &band, &robot); 
      determinaEstado( &robotIzq, &robotDer, &cont, dir, &band2, aImg[0], &robot, robotEne, arrayBloques );
      
      /* Se verifica si e robot a pasado a otro escenario,por si es asi, mover todo el escenario hacienod las configuracione 
        de apuntadores adecuada */
        
      if( mueve && bandM )
      {
        contM++;
        
        mueveEscenario( arrayBloques, &robotIzq, &robotDer , &chip, &bandera, &aros);
        
        if( contM == 100 )
         {
           contM = 0;
           mueve = 0;
           arrayCorY[0] = 700;
           arrayCorY[1] = 700;
           arrayCorY[2] = 700;
           xB += 5;
           xBaux = xB;
           bandAux = 1;
           band4 = 0;
         }
      }   
      retraso( ret );
      
      minutos = reloj( tA, tB );
     
     // Se checa si el robot llego a la cima y esta con el chip     
     if( ( (robotIzq -> corX < chip -> corX + 30 && robotDer -> corX > chip -> corX + 30) || (robotIzq -> corX < chip -> corX && robotDer -> corX > chip -> corX ) ) && robotIzq -> corY   < chip -> corY )
     {
           robot =  aImg[12];
           final = 1;
     }
     
    
     for( i = 0; i < escen; i++)
       switch( i )
           {
             case 0: if( arrayCorY[i] != 5 && arrayCorY[i] < 700 )
                        putimage(700, arrayCorY[i], aImg[7] -> img,2 );break;
             
             case 1: if( arrayCorY[i] != 100 && arrayCorY[i] < 700)
                            putimage(50, arrayCorY[i], aImg[7] -> img,2 );break;
             
             case 2: if( arrayCorY[i] != 200 && arrayCorY[i] < 700 )
                         putimage(350, arrayCorY[i], aImg[7] -> img,2 );break;
           } 
    
          
    if( escen < 4 ) 
      if( cuentaSal == 1 && !band3)
            band3 = 1;
      
      /* Se checa si algun robot enemigo ya llego al bloque para asi llevar acabo la operacion de insercion en el 
        arreglo de robot enemigo previamente ya declarado*/
      if( band3 )
        for( i = 0; i < escen; i++)
          switch( i )
          {
             case 0: if(  arrayCorY[i] == 5 )
                     {   
                       for( u = escen; u > 0; xBaux--, u--)
                       {
                         insRobotEne( &robotEne, arrayBloques[ xBaux ].ptrBloque);
                         activaBloque( arrayBloques , xBaux);
                       
                       }
                      
                       band3 = cuentaSal = 0;
                    
                     }else
                         arrayCorY[i] -= 5;
                    
                     break;
             
             case 1:  if(  arrayCorY[i] == 100 )
                          putimage(50, arrayCorY[i], aImg[7] -> img,2 );
                      else
                         arrayCorY[i] -= 5;
                      
                      break;
             
             case 2: if(  arrayCorY[i] == 200 )
                       putimage(350, arrayCorY[i], aImg[7] -> img,2 );
                     else
                         arrayCorY[i] -= 5; 
          }
        
        for( int w = 0; w < robotEne.nElem; w++ )
           if( robotEne.robotEn[w].nVidas )
             if( bandVE )
                putimage( robotEne.robotEn[w].ptrM -> corX, robotEne.robotEn[w].ptrM -> corY - 57, aImg[7] -> img, 0  ); 
              else
              {
                 putimage( robotEne.robotEn[w].ptrM -> corX, robotEne.robotEn[w].ptrM -> corY - 57, aImg[7] -> img, 1); 
                 retraso( 50 );
                 bandVE = 1;
               }
      
      eliminaRobotEne( &robotEne );
      
      // Se insertan las balas del robot heroe una ves que ya este en el bloque moviendose
      if( robotEne.nElem &&(t2 = time( NULL ) - t1 ) == 1)         
            for( i = 0; i < robotEne.nElem; insBalasRE( &robotEne , i, arrayCorY ), i++ ); 
           
       /* Esta condiciones es para posicionar al robot en el inicio e el momento de caer del bloque 
          siempre y cuando este en el primer escenario*/
       if(  robotDer-> corY == 750 )
       {
          if( escen == 1 )
          {
             robotIzq = robotIzqAux;
             robotDer = robotDerAux;
             
            
          }else
              {  /* Si el robot esta en otra escenario que no sea el primero, al momento de caer aparecera
                    en el primer bloque del escenario*/ 
               robotIzq = arrayBloques[ xB - 6].ptrBloque;
               for( i = 1; i <=11; i++, robotIzq = robotIzq -> arriba);
              
               robotDer = robotIzq;
              
               for( i = 1; i <=11; i++, robotDer = robotDer -> abajo);
               for( i = 1; i <=7; i++, robotDer = robotDer -> sig);
              
              }
           dir = -1;
           cont = 0;
           robot = aImg[0];
           retraso( 200 ); 
           vidas--;
       }
       
      if( escen == 1 )
      {
        putimage( bloqueBase -> corX, bloqueBase -> corY, aImg[5] -> img,COPY_PUT  );
        putimage( bloqueBase2 -> corX, bloqueBase2 -> corY, aImg[5] -> sigImg -> img,COPY_PUT  );
      }else
        if( !band4 )
          {
             for(u = 0; u < 20; strcpy( bloqueBase -> name, " "), bloqueBase = bloqueBase -> sig,u++ );
             band4 = 1;
          }
     
     dibujaEscenario( robotIzq, robot, arrayBloques , aImg[6] -> img, chip, aImg[9] -> img,bandera, aImg[11] -> img  );
     dibujaAro( aros );
     dibujaBalas( robotEne, balasH ); 
     eliminaBala( &robotEne, &balasH , robotIzq );
     eliminaAros( &aros, robotIzq, robotDer );
     setvisualpage( page );
    
    }while( !kbhit() && vidas > 0 && !final && minutos != 10) ;
    
    if( vidas > 0 && !final && minutos !=10)
     {
      
       if( !robotIzq -> ant-> ant-> ant-> ant-> ant-> ant ->ant -> ant  )   
        {
            robotIzq = robotIzq -> sig;
            robotDer = robotDer -> sig;
        }else
           if( !robotDer -> sig )
           {
              robotIzq = robotIzq -> ant;
              robotDer = robotDer -> ant;
           }
      
       if( !contM  ) 
       {
         dir = getch();
        
         switch(dir)
         {
                   
          case 110: camina( &aux1, &robotIzq, &robotDer, dir, &robot); break;
          case 118: camina( &aux2, &robotIzq, &robotDer, dir, &robot); break;
          case 98: robot = aImg[8];
                   
                   if( balas != 0 )
                    {
                      insBala( &balasH, robotIzq -> corX + 70, robotIzq -> corY ); 
                       bandBal = 1;
                       balas--;
                    }
                   break;
           case 102: if( balas == 0 )
                     balas = 50;
                    break;
         }
        }
      }
       
    }while( vidas > 0 && !final && minutos != 10);
    
    rec -> puntos = puntos;
    
    retraso( 2000 );
    mensaje( *rec, aImg[0] -> img );
    
    eliminaMalla( &malla );// Libera de memoria la malla
    
    //Se libera de memoria el arreglo de aros
    for( i = 0; i < aros.nElem; i++ );    
     { 
         auxF = aros.arrayA[i];
         for( ; auxF; free( auxF ), auxF = auxF -> sigA );
     }
     
    // Libera el arreglo de las imagenes
     liberaArrayImg( aImg );
     
     cuentaSal = c2 = mueve = puntos = final = 0;
     bandVH = bandVE = bandAux = escen = 1;
     vidas = 10;
     balas = 50;
     xB = 5;
     
     cleardevice();
}

/* Esta funció es para libera la memoria que se reservo en la captura de las imagenes del juego
   recibe como parametro el arreglo de imagenes */
void liberaArrayImg( IMAGEN *aI )
{
  IMAGEN aux, nodoF;
  int i;
  
  for( i = 0; i < TAM_IMG; i++)
  {
     aux = aI[i];
     
     while( aux )
     {
       if( aux -> sigImg == aI[i] )
          aI[i] = NULL;
       else
          {
            nodoF = aux;
            
            for(; nodoF -> sigImg != aI[i]; nodoF = nodoF -> sigImg );
            
            aI[i] = aux -> sigImg;
            nodoF -> sigImg = aI[i];
          }
     
       free( aux -> img );
       free( aux );
       
       aux = aI[i];
     }
  }
}

/* Esta funion es para mostrar un mensaje al jugador de si gano o perdio la partida, recibe la estructura de records y la imagen del
 robot para imprimirla junto los records de los jugadores */
void mensaje( RECORDS rec, void * robot )
{
   int x, y;
   char tecla, cad[10];
   
   x = 155;
   y = 150;
 do
 {
     setcolor( LIGHTBLUE );
     setfillstyle(SOLID_FILL, BLACK);
     rectangle( x, y, 640, 517 );
     floodfill(x+100,y+100, LIGHTBLUE); 
   
     setcolor( WHITE );
     settextstyle( 4, 0 , 4 );
     outtextxy( x + 80, y + 40, " Fin del juego " );
   
     setcolor( YELLOW );
     settextstyle( 1 , 0 , 4 );
     
     if( final )
        outtextxy( x + 70, y + 100, " GANASTE!!!! " );
     else
        outtextxy( x + 70, y + 100, " PERDISTE!!!! " );
   
     setcolor(WHITE );
     settextstyle( 4, 0 , 2 );
     putimage( x +  30, y + 200, robot, 0 );    
     outtextxy( x + 130, y + 200, " Nombre : " );
     outtextxy( x + 280, y + 200, rec.name );
     outtextxy( x + 130, y + 250, " Puntos : " );
   
     itoa( rec.puntos, cad, 10 ); 
     outtextxy( x + 280, y + 250, cad);
   
      settextstyle( 11 , 0 , 1 );
      setcolor( YELLOW );
      outtextxy( x + 40,  y + 320, " Presione esc para ir a menu..." );
    
    tecla = getch(); 
  }while( tecla != 27 );
}

/* Esta funcion esta calculando el tiempo actual del sistema, el timpo retornado le sirve al sistema para verificar
 si el jugador esta fuera de este limite, recibe como parametros dos varibles de tipo time_h */
int reloj(time_t tini,time_t tact)
{
   int seg,min,hrs,t;
   char tiempo[9],aux[3];
   
   setfillstyle(1,0);
   settextstyle(1,0,1);
   setcolor(WHITE );
   
   seg = tact-tini;
   hrs = seg/3600;
   seg = seg%3600;
   min = seg/60;
   seg = seg%60;
   
   itoa(hrs,aux,10);
   t = strlen(aux);
   
   if(t==1)
   {
    strcpy(tiempo,"0");
    strcat(tiempo,aux);
   }
   else
      strcpy(tiempo,aux);
  
   strcat(tiempo,":");
   itoa(min,aux,10);
   t = strlen(aux);
  
   if(t==1)
   {
     strcat(tiempo,"0");
     strcat(tiempo,aux);
   }
   else
      strcat(tiempo,aux);
   
   strcat(tiempo,":");
   itoa(seg,aux,10);
   t = strlen(aux);
   
   if(t==1)
   {
     strcat(tiempo,"0");
     strcat(tiempo,aux);
   }
   else 
      strcat(tiempo,aux);   
  
   outtextxy(830,610,tiempo);
  
  return(min);
}

/* Esata funcion se encarga de inicializar un arreglo que contiene los aros de todo el juego, recibe como
 parametro el arreglo de tipo estrutura VA( Vector de Aros)*/
void iniAro( VA *vA )
{
  int i;
  
  for( i = 0; i < TALLA_A; i++ )
      vA -> arrayA[i] = NULL;
  
  vA -> nElem = 0;
}

/* Esta funcion es para crear un nodo de tipo ARO recibe como  parametro, el propio arreglo de ARO y un apuntador a
 un nodo de la malla, este arreglo tendra solamente un conjunto de direcciones*/
int creaAro( ARO *a, NODO_MALLA nM )
{
  int res = 0;
  
  if( *a = ( ARO )malloc( sizeof( struct regA ) ) )
  {
    (*a) -> ptrM = nM;
    (*a) -> sigA = NULL;
    res = 1;
  }
  
  return( res );
}

/* Esta funciones para insertar un aro en alguna de las lista del arreglo aro, recibe como parametro el arreglo y 
  el apuntador , con el que cada cabecera de las lista haga referencia */
void insAro( ARO *lA, NODO_MALLA nM )
{
  ARO nueva;
  
  if( creaAro( &nueva, nM ) )
  {
    nueva->sigA = *lA;
    *lA = nueva;
  }
 
}

//Esta funcion es para inicializar la estrucura RBT_ENE
void iniRE( RBT_ENE *rE )
{
  int i;
  
  for(i = 0; i < 5; i++ )
  {
    rE -> robotEn[i].nVidas = 0;
    rE -> robotEn[i].ptrM = NULL;
    rE -> robotEn[i].ptrB = NULL;
  }
  
  rE -> nElem = 0;
  
}
/* Esta funcion es para eliminar algun robot enemigo del arreglo , la eliminacion del robot
 solo se llevara a cabo simpre y cuando el robot sea liquidado por las balas del robot heroe,la funcion recibe como parametro una
 lista, esta lista es la cabecerade uno de los elementos de l arreglo */
void eliminaRobotEne( RBT_ENE *rE)
{
  BALAS aux;
  int i;
  
  if( rE -> nElem ) 
     for( i = 0; i < rE -> nElem; i++ )
      if( !rE -> robotEn[i].nVidas )
       {
         for(; rE -> robotEn[i].ptrB; free(rE -> robotEn[i].ptrB), rE -> robotEn[i].ptrB = rE -> robotEn[i].ptrB -> sig ); 
         
         if( i != rE -> nElem - 1 )
         {
           rE -> robotEn[i].nVidas = rE -> robotEn[i + 1].nVidas;
           rE -> robotEn[i].ptrM = rE -> robotEn[i + 1].ptrM;
         }
         
         bandAux = 0;
         rE -> nElem--;
       } 
} 
 
/* La funcion activa bloque, se encarga de cambiar la direccion del bloque, cuando se inicializa el escenario, algunos
  bloques se les da la direccion -1, este digito indica en alguna parte del programa que no se podra mover, el resto 
  de digitos tiene un 1(mueve derecha) y 0( mueve izquierda), la funcion es llamada cuando en cada escenario
  aparecezca algun robot enemigo, una ves que se posiona el robot encima  del bloque, este es activado y se pone en
  movimiento constante, la funcion recibe como parametro un arreglo de tipo VECTOR, en esa estructura se encuentra el arreglo
  y un dato de tipo entero, que representa el bloque que activara*/
void activaBloque( VECTOR_B aB[],int bloque )
{
 
 NODO_MALLA auxB;
  
 (aB + bloque ) -> dirBloque = 1;
 
 auxB = aB[bloque].ptrBloque;
  
 for(int z = 0; z < 8; z++, auxB = auxB -> sig )
      (aB + bloque ) -> posBloque[ z ] -> dir = 1;
   
}

/* Esta funcion es para crear un robot enemigo, no se necesita reservacion de memoria, ya que lo unico
  que se requiere es tener una referencia a algun nodo de la malla,la funcio  recibe como parametro el arreglo 
  de tipo estructura RBT_ENE, y un apuntador que indicara el apuntador al cual tendra que hacer referencia. */
void insRobotEne( RBT_ENE *rE, NODO_MALLA ptrB )
{
  rE -> robotEn[rE -> nElem].ptrM = ptrB;
  rE -> robotEn[rE -> nElem].nVidas = 20;
  rE -> nElem ++; 
}

// Se inicializa la lista de balas
void iniBalas( BALAS *bE )
{
  *bE = NULL;
}

/* Esta funcion es para crear un nodo bala, cada ves que el robot heroe o robot(s) enemigo(s) dispare(n)
  se ejecuta la esta funcion, reservando memoria para dicho nodo, lo unico que necesita el nodo son 
  las coordenadas en donde se imprimira la bala una ves que haya sido disparada, recibe como parametro
  una lista de BALAS y las coordenadas atuales en del robot heroe o robot enemigo(s).*/
int creaBala( BALAS *lB, int x, int y )
{
  int res = 0;
  
  if( *lB = ( BALAS )malloc( sizeof( struct regBalas ) ) )
  {
    ( *lB ) -> corX = x;
    ( *lB ) -> corY = y;
    ( *lB ) -> sig = NULL;
    
    res = 1;
  }     
  
  return ( res );
}

/* Esta funcion es para controlar las balas del enemigo(s), lo que realiza es llevar el contro de en que
  momento ir insertando las balas, segun la posicion del bloque en donde esta ubicado, recibe como parametro el arreglo de
  robots enemigos RBT_ENE, el tipo de robot, esto es que robot y un arreglo de coordendas, que determina en que escenario se 
  encuentra el robot heroe , son tres escenarios y segun sea el escenario sera la cantidad de robots en activar*/
void insBalasRE( RBT_ENE *rE, int tipoE, int *arrayCor )
{
  int i;
  
  switch( tipoE )
  {
    case 0:  if( arrayCor[tipoE] == 5 )
                 insBala( &rE->robotEn[tipoE].ptrB, rE -> robotEn[tipoE].ptrM -> corX + 40, rE -> robotEn[tipoE].ptrM -> corY  );
             break;
    case 1:  if( arrayCor[tipoE] == 100 )
                 insBala( &rE->robotEn[tipoE].ptrB, rE -> robotEn[tipoE].ptrM -> corX + 40, rE -> robotEn[tipoE].ptrM -> corY  );
             break;
    case 2:  if( arrayCor[tipoE] == 200 )
                 insBala( &rE->robotEn[tipoE].ptrB, rE -> robotEn[tipoE].ptrM -> corX + 40, rE -> robotEn[tipoE].ptrM -> corY  );
             break;
  }
}
/* Esta funciones para insertar una bala en la lista BALAS, esa lista es exclusiva del robot heroe, la funcion insBala
   recibe como parametro la lista y las coordendas en donde se guardara la bala */
void insBala( BALAS *lB , int x, int y)
{
  BALAS  nueva;
  
  if( creaBala( &nueva, x, y ) )
  {
    nueva -> sig = *lB;
    *lB = nueva;
  }
}

/* Esta funcion se encarga de eliminar todo aro que haga contacto con el robot heroe y su ves todo aro que salga del escenario
   esto ocurrira en el momento de ir ascendiendo por los bloques recibe como parametro el Areglo de aros, y dos apuntadores 
   a un nodo malla, uno apunta a la parte izquierda del robot heroe y el otro a la parte derecha, por medio de los apuntadores
   se hace referencia  a las coordendas de que tienen dicho nodo y asi evaluarlas con el robot*/
void eliminaAros( VA *aros, NODO_MALLA robotIzq, NODO_MALLA robotDer )
{
  ARO aux, ant;
  int i,j, band = 0;
  int cont = 0;
  
  for( i = 0;  i < aros -> nElem && !band ; i++)
  {
    aux = aros -> arrayA[i];
    
    while( !band && aux  )
    {
      if( aux -> ptrM -> corY < 690 )
      {
         if(  aux -> ptrM -> corY + 10 == robotIzq -> corY  || aux -> ptrM -> corY - 10 == robotIzq -> corY + 45 || aux -> ptrM -> corY > robotIzq -> corY + 10 && aux -> ptrM -> corY < robotIzq -> corY + 20 ||aux -> ptrM -> corY > robotIzq -> corY + 10 && aux -> ptrM -> corY < robotIzq -> corY + 45)
            if( robotDer -> corX > aux ->ptrM -> corX - 7 && robotIzq -> corX < aux -> ptrM -> corX + 7 ) 
            { 
               if( aux == aros -> arrayA[i] )
                     aros -> arrayA[i] = aux -> sigA;
                else
                    ant -> sigA = aux -> sigA;
               
               band = 1;
            }
      }else
          {
              if( aux == aros -> arrayA[i] )
                     aros -> arrayA[i] = aux -> sigA;
                else
                    ant -> sigA = aux -> sigA;
               
               band = 1; 
          } 
      if( band )
       {
         free( aux );
         puntos+=10;
      }else
       {
          ant = aux;
          aux = aux -> sigA;
          
       }
     }
    
    //Se checa si alguna cabezara del arreglo esta vacia y si es asi los elemntos del arreglo s e recorren
    if( aux ) 
    if( !aros -> arrayA[i] )
    {
         for(j = i; j < aros->nElem - 1; j++)
            aros -> arrayA[j] = aros -> arrayA[j+1];
         
         aros -> nElem --;
    }
  }  
}
/* Esta funcion es para eliminar toda la malla, una ves que haya termina el juego, se libera toda la memoria reservada
 la funcion recibe como parametro( por referencia) la estructura malla*/
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

/* Esta funcion es para eliminar las balas de los dos robots, si alguna hace contacto con un de ellos o alguna
 sale disparada fuera del escenario, se recibe como parametro el arreglo de los robot enemigo, la lista 
 las balas del robot heroey un apuntador a nodo, este  es para hacer referencia al robot */
void eliminaBala( RBT_ENE *rE, BALAS *bH, NODO_MALLA robotIzq )
{
  BALAS ant, aux;
  NODO_MALLA auxB;
  int band = 0;
  
  if( rE -> nElem )
   {
     
     for(int i = 0; i < rE ->nElem; i++ ) 
     {
       // printf(" vidas robotE: %d", rE -> robotEn[i].nVidas  );
     
        auxB = rE -> robotEn[i].ptrM;
        
        for(aux = *bH; aux && !band; ant = aux , aux = aux -> sig )
           if( aux -> corX > auxB -> corX && aux -> corX < auxB -> corX + 60 && aux -> corY < auxB -> corY )
           {
             if( aux == *bH )
                *bH = aux -> sig;
             else
               ant -> sig = aux -> sig; 
         
             free( aux );
             band = 1;
             rE -> robotEn[i].nVidas -- ;
              bandVE = 0;
           }
     }
  }
  
  for(aux = *bH; aux && aux -> sig; ant = aux , aux = aux -> sig );
  
  if( aux )
  {
     if( aux -> corY == 0 || aux -> corY == -5 )
     {
         if( aux == *bH )
             *bH = NULL;
         else
             ant -> sig = aux -> sig;
         
         free( aux );
        // puts( " Bala eliminada " );
     }
  }
  
  // Se elimina una bala de la lista del robot enemigo al hacer contacto con el robot heroe
 
 for( int i = 0; i <  rE -> nElem; i++) 
  {
    for(aux = rE -> robotEn[i].ptrB; aux && !band; ant = aux , aux = aux -> sig )
       if( aux -> corX > robotIzq -> corX && aux -> corX < robotIzq -> corX + 55 && aux -> corY > robotIzq -> corY && aux -> corY < robotIzq -> corY + 50)
       {
          if( aux == rE -> robotEn[i].ptrB )
             rE -> robotEn[i].ptrB = aux -> sig;
           else
             ant -> sig = aux -> sig; 
         
           free( aux );
           band = 1;
           vidas--;
           bandVH = 0;
        //   puts( " Robot disparado " );
       }
  
     // Se elimina de la lista toda bala que haya llegado al vacio
    for(aux = rE -> robotEn[i].ptrB; aux && aux -> sig; ant = aux , aux = aux -> sig );
    
    if( aux )
      if( aux -> corY == 700 )
      {
         if( aux == rE -> robotEn[i].ptrB )
             rE -> robotEn[i].ptrB = NULL;
         else
             ant -> sig = aux -> sig;
         
         free( aux );
      //   puts( " Bala eliminada " );
      }
    }   
}

/* La funcion dibuja balas se encarga de ir imprimiendo todas las balas generadas en la insercion,tanto para el robot heroe
 como el enemigo, necesita como parametro la estructura del robot enemigos y una lista de bala del heroe, 
 para cada robot, se hace un recorrido por sus lista y se analiza si hay alguna creada si es asi se imprime la bala en las
 coordendas que almacena alguno de sus nodos, para las balas del robot heroe se hace lo mismo*/
void dibujaBalas( RBT_ENE rE, BALAS bH )
{
  setlinestyle(0,0,3);
  BALAS aux;
  int i;
  
  if( bH ) 
  {  
    // puts( "H:lista llena" );
      
     while( bH )
     {
       // printf( " B :%d ",  bH -> corY );
        setfillstyle(SOLID_FILL,WHITE); 
        
        setcolor( BLUE );
        fillellipse( bH -> corX, bH -> corY , 6, 12 ); 
        floodfill(bH -> corX,bH -> corY , BLUE);
        bH -> corY -= 10;
        bH = bH -> sig;
      }
   }/*else
      puts( " H:lista vacia" );
  */
  if( rE.nElem ) 
  {  
    // puts( " \t\tE :lista llena" );
   for(i=0; i < rE.nElem; i++)     
   {
     aux =  rE.robotEn[i].ptrB;      
     while( aux )
     {
       // printf( " B :%d ",  aux -> corY );
        setfillstyle(SOLID_FILL,WHITE); 
        
        setcolor( RED);
        fillellipse( aux -> corX, aux -> corY , 6, 12 ); 
        floodfill(aux -> corX, aux -> corY ,RED);
        aux -> corY += 5;
        aux = aux -> sig;
      }
    
    }
  }/*else
      puts( " E:lista vacia" );*/
}

/* Esta funcion se encarga de mover todo el escenario, esto es cambiar unas posisicones a todo aquel apuntador que este haciendo 
  referencia a algun nodo de la malla, para hacer eso lo unico que se hace es cambiar las direcciones de cada apuntador
  y pasar toda sus informacion a dicha posicion, recibe como parametro el vector de bloques, y los apuntadores que tienen 
  la direccion del robot, el chip y la bandera */
void mueveEscenario( VECTOR_B *aB, NODO_MALLA *rI, NODO_MALLA *rD ,NODO_MALLA *chip,NODO_MALLA *bandera,VA *aros)
{
   NODO_MALLA aux;
   ARO auxB;
   int i, j; 
   
   *rI = (*rI) -> abajo;
   *rD = (*rD) -> abajo;
   *chip = (*chip) -> abajo;
   *bandera = (*bandera) -> abajo;
  
   for( i = 0; i < aros -> nElem; i++)
   {
      auxB = aros ->arrayA[i];
      
      while( auxB )
      {
         auxB -> ptrM = auxB -> ptrM -> abajo;
         auxB = auxB -> sigA;
      }
  }
   
   for( i = 0; i < TALLA; i++ )
   {
     ( aB + i ) -> ptrBloque = (aB + i) -> ptrBloque -> abajo;
      aux = ( aB + i ) -> ptrBloque;
     
     for( j = 0; j < 8; j++ )
     {
       strcpy( aux -> name, aB[i].posBloque[j] -> name );
        strcpy( aB[i].posBloque[j] -> name, "" );
        
       aux -> dir = aB[i].posBloque[j] -> dir;
       aB[i].posBloque[j] = aux;
       
       aux = aux -> sig; 
     }
   }
   
   retraso( 10 );
}

/* Esta funcion imprime todos los aros que existan en el juego, se hace un recorrido por el arreglo VA y asu ves
  por cada una de sus listas,simpre y cuando existan , recibe como parametro un instancia de de tipo VA */
void dibujaAro( VA vA )
{
 ARO aux;
 int i;
 int cont = 0;
 
 setcolor( YELLOW );
 setlinestyle(1,1,2);
 
 for( i = 0; i< vA.nElem; i++)
 {   
    aux = vA.arrayA[i];
     
     while( aux )
     { 
        if( aux -> ptrM -> corY > 0 && aux -> ptrM -> corY < 700 )
           circle( aux ->ptrM ->corX, aux -> ptrM -> corY, 10 ); 
       
        aux = aux -> sigA;
     }
  }
}

/* La  funcion dibuja escenario, se encarga de dibujar toda ocurrencia en el programa,  esto es los bloques, el robot, la bandera
  el chip y todo loq ue ste en la interface del juego */
void dibujaEscenario( NODO_MALLA robotIzq, IMAGEN robot, VECTOR_B aB[], void *imgBloque, NODO_MALLA chip , void *imgChip, NODO_MALLA bandera, void *imgBand)
{
  int cont = 0;
  
  if( chip -> corY > 0 &&  bandera -> corY > 0)
  {
     if( !final )
         putimage( chip -> corX, chip -> corY, imgChip, 2 );
     else
         putimage(robotIzq -> corX, robotIzq -> corY - 10, robot -> img, 2 );
     
     putimage( bandera -> corX + 10, bandera -> corY - 55, imgBand, 2 );
  }  
          
  
  for( int d = 0; d < TALLA; d++ )
   if(  aB[d].ptrBloque -> corY > 0 && aB[d].ptrBloque -> corY < 700)
    {
        // printf(" corY: %d \n", aB[d].ptrBloque -> corY );
         putimage( aB[d].ptrBloque -> corX, aB[d].ptrBloque -> corY, imgBloque, 2 );
         cont ++;
    }   
 
 if( !final )    
   if( bandVH )
     putimage(robotIzq -> corX, robotIzq -> corY, robot -> img, 2 );
   else
     {
       putimage(robotIzq -> corX, robotIzq -> corY, robot -> img, 1);
       retraso( 100 );
       bandVH = 1;
     }
} 

/* La funcion camina se encarga de ajustar los apuntadores del robot, tanto el izquierda como el derecha segun sea
  la direccion del robot, recibe como parametro una lista de imagenes que es la secuencia de los camina, una dato de tipo
  entero que representa la direccion en que se movio el robot y sus apuntadores que hacen referencia a la posicion actual del robot
  tanto el izquierda como el derecha*/
void camina( IMAGEN  *ptrImg, NODO_MALLA *robIzq,NODO_MALLA *robDer, char dir, IMAGEN *robot )
{
  if( dir == 110 )
  {
     *robIzq = (*robIzq) -> sig;
     *robDer = (*robDer) -> sig;
  }else
      {
       *robIzq = (*robIzq) -> ant;
       *robDer = (*robDer) -> ant;
      }
  
   *ptrImg = (*ptrImg) -> sigImg; 
   *robot = *ptrImg;
}

/* Esta funcion se encarga de definir la posicon actual del robot,esto es si esta encima de algun bloque, si es asi,quedarse encima de
 el y si esta en movimiento sincronizar al robot con el bloque, recibe como parametros, los apuntadores que hacen referencia al robot, el arreglo
 de bloques, la direccion del robot, asi como la imagen del robot y el arreglo del robot enemigo*/ 
void determinaEstado(NODO_MALLA *robotIzq, NODO_MALLA *robotDer, int *cont, char dir, int *band2, IMAGEN imgRobot, IMAGEN *robot, RBT_ENE rE, VECTOR_B *aB )
{
   NODO_MALLA aux;
    /* Se verifica que el robot pase encima de algun bloque, y asi posicionarse en el, cuando el contador es mayor a 25
         esto indica que el robot viene cayendo */ 
    
    aux = (*robotIzq) -> abajo -> abajo -> abajo ->abajo ->abajo ->abajo ->abajo ->abajo ->abajo ->abajo ->abajo;
    
    if( *cont > 25 )
       if( !strcmp( (*robotDer) -> name , "bloque" ) || !strcmp( aux -> name , "bloque" ) || !strcmp( (*robotDer) -> name , "bloqueB" ) || !strcmp( aux -> name , "bloqueB" ) ) 
           { 
                *cont = 181; 
                *band2 = 1;
                *robot = imgRobot;
                
                if( !rE.nElem && bandAux)
                    cuentaSal ++;
               
                  if( (*robotDer) -> corY == aB[ xB ].ptrBloque -> corY && !rE.nElem && escen < 4 )
                  {
                     mueve = 1; 
                     escen ++; 
                  }else
                      puts( " robotP " );
          }
  
   if( *cont == 1 )
        if(  strcmp(aux -> name , "bloqueB" ) && strcmp( (*robotDer) -> name , "bloque") && strcmp(aux -> name , "bloque" ) )
         {
            (*robotIzq) = (*robotIzq) -> abajo;  
            (*robotDer) = (*robotDer)-> abajo; 
         }else
               *band2 = 1;
      
    if( ( *band2 && !dir ) || escen <4 )
    {
       if( (*robotIzq) -> ant-> ant-> ant-> ant-> ant-> ant ->ant -> ant )
       {
          if( !strcmp( aux -> name , "bloque" ) ||  !strcmp( (*robotDer) -> name , "bloque" ) )
          { 
            if( aux -> dir != -1 && (*robotDer) -> dir != -1 )  
              if( aux -> dir ) 
              {
                 (*robotIzq) =  (*robotIzq) -> sig;
                 (*robotDer) =  (*robotDer) -> sig;
               }else
                   {
                    (*robotIzq) =  (*robotIzq) -> ant;
                    (*robotDer) =  (*robotDer) -> ant;
                   }
          }else
              *band2 = 0;
       }else
           {
             (*robotIzq) = (*robotIzq) -> sig;
             (*robotDer) = (*robotDer) -> sig;
           }
       
       if( !(*robotDer) -> sig )
       {
           (*robotIzq)  = (*robotIzq) -> ant;
           (*robotDer) = (*robotDer) -> ant;
        }
    }
}

/* En esta funcion  imprime el estado del robot, en relacion al puntaje, sus vidas , el tiempo que lleva en el juego, asi
 como el conteo de las balas, solo  recibe dos imagenes una de ellas es la del robot y la otra la de la bala, tambien recibe
 el nombre del usuario */
void estadisticas( void *imgR, void *bala , char *name)
{
   char cad[10];
   
   itoa(vidas, cad, 10 );
   
   setcolor( WHITE );
   setlinestyle(0,0,0);
   outtextxy( 810, 450, " Puntos " );
   
   settextstyle(1,0,1);
   outtextxy( 820, 200, "Vidas" );
   outtextxy( 920, 200, cad );
   
   itoa( balas, cad, 10 );
   outtextxy( 920, 330, cad );
   
   itoa( puntos, cad, 10 );
   outtextxy( 910, 500, cad );
   
   putimage( 850, 30, imgR, COPY_PUT);
   outtextxy( 810, 100, name );
   
   putimage( 820,330 , bala, COPY_PUT);
   
   setcolor( 7 );
   rectangle( 5,0, 790, 687 );
   
   setcolor( YELLOW);
   rectangle( 795,0, 987, 687 );
   line( 795, 140 , 987, 140 );
   line( 795, 280 , 987, 280 ); 
   line( 795, 420 , 987, 420 );
   line( 795, 560 , 987, 560 );
   
   setcolor( YELLOW );
   setlinestyle(1,1,2);
   circle(  860, 510, 10 );
   
}

/* Esta función es para controlar el brinco del robot,  se hace uso de un contador para ir delimitando el brinco, sí
  el contodor es mayor a 25 las direcciones del robot ahora cambiarán hacia abajo, esto para simular el descenso del robot,
  recibe como parametro los apuntadores que hacen referencia al robot ( izq y der), una lista de imagenes, para 
  controlar la secuencia de los saltos, un contador de tipo entero por referencia para determina el momento de la caida, una bandera que 
  indica en que momento  ha completado todo el salto, y un apuntado del robot, que es donde se guarda las secuencias de las
  imagenes */
void brincaRobot( NODO_MALLA *robIzq, NODO_MALLA *robDer, IMAGEN *imgP, int *cont, char *dir, int *band, IMAGEN *robot )
{
  if( *cont <= 180 && *dir == 106 )
  {
      *band = 0;
      
      if( *cont > 25 )
      {
          *robIzq = (*robIzq) -> abajo;
          *robDer = (*robDer) -> abajo;
      }else
         {
            *robIzq = (*robIzq) -> arriba;
            *robDer = (*robDer) -> arriba;
          }
   
      *imgP = (*imgP) -> sigImg;
      *cont += 1;
      *robot = *imgP;
  }else
      {
         *cont = 1;
         *dir = 0;   
         *band = 1;
      }  
}

/* Esta función es para cambiar  la dirección de todos los bloques de la malla,
  una ves que alguno de ellos esté en algun extremo de la malla su dirección se invierte,
  recibe como parametro un arreglo de tipo estructura VECTOR_B */
void cambiaDirBloques( VECTOR_B *aB )
{
  int i,j;
  NODO_MALLA aux;
  
  for( i = 0; i < TALLA; i++ )
     if( !(aB + i ) -> ptrBloque -> sig ->sig -> sig -> sig ->sig -> sig-> sig-> sig-> sig-> sig )
         ( aB + i ) -> dirBloque = 0;
     else
       if( !(aB + i ) -> ptrBloque -> ant-> ant-> ant-> ant-> ant-> ant ->ant )    
            ( aB + i ) -> dirBloque = 1;
}

/* Esta función sirve para mover una posición siguiente a todos los bloques del juego,
 para ello se evalua la direcciín de cada uno de ellos, si su direccion es 0 el bloque se
 mueve a la izquierda si no se moverá a la derecha, la dirección se modifica antes del
 llamado de esta función.
 Recibe como parametros un arreglo de tipo estructura denominada VECTOR_B en donde sus campos contiene
 la dirección y un apuntador que hace referencia a un bloque de la malla.
 EL otro parametro es un la imagen del bloque que se utiliza en el momento que se hacen cambios de 
 posición del bloque */
void mueveBloques( VECTOR_B *aB , void * imgBloque, RBT_ENE *rE)
{
  int i,j, k ,z;
  NODO_MALLA aux, aux2;
  
  for( i = 0; i < TALLA; i++ )
  {
    if(  ( aB + i ) -> dirBloque   != -1 )
       if( ( aB + i ) -> dirBloque )
       {
        
        ( aB + i ) -> ptrBloque = ( aB + i ) -> ptrBloque -> sig; // El bloque se mueve hacia la derecha
      
         j = 0;
         strcpy( ( aB + i ) -> posBloque[j] -> name, " " );
      
         for(; j < 8; j++ )
          ( aB + i ) -> posBloque[j] = ( aB + i ) -> posBloque[j] -> sig;
      
         strcpy( ( aB + i ) -> posBloque[j -1 ] -> name, "bloque" );
      
         for(j = 0; j < 8; j++ )
          ( aB + i ) -> posBloque[j] -> dir = 1; 
    
       }else
          {
           
           ( aB + i ) -> ptrBloque = ( aB + i ) -> ptrBloque -> ant;// El bloque se mueve hacia la izquierda
         
            j = 0;
            strcpy( ( aB + i ) -> posBloque[j] -> ant -> name, "bloque" );
         
            for(; j < 8; j++ )
             ( aB + i ) -> posBloque[j] = ( aB + i ) -> posBloque[j] -> ant;
         
            strcpy( ( aB + i ) -> posBloque[j -1] -> sig -> name, " " );
         
            for(j = 0; j < 8; j++ )
             ( aB + i ) -> posBloque[j] -> dir = 0;  
           }
  }

  if( rE -> nElem )
    for( i = 0; i < rE -> nElem; i++) 
      if( rE -> robotEn[i].ptrM -> sig -> dir )
          rE -> robotEn[i].ptrM = rE -> robotEn[i].ptrM -> sig;
      else
         rE -> robotEn[i].ptrM = rE -> robotEn[i].ptrM -> ant;
}

/* Esta función se encarga de inicializar todo el escenario del juego, ubicar los bloques en la posición
  correspondiente, ubicar al robot asi como los aros en toda la malla, todas estas asignaciones se van dando en el momento en que se le da 
  al robot heroe su posicion en la malla, recibe como parametro la malla, el arreglo de imagenes, los aputadores( izq y der) que hacen referencia al robot
  el apuntador del chip, el de los aros, y una estructura de los aros */
void iniEscenario( MALLA m, IMAGEN *aImg, NODO_MALLA *robIzq, NODO_MALLA *robDer, VECTOR_B *aB, NODO_MALLA *chip,NODO_MALLA *bandera, VA *aros )
{
  NODO_MALLA auxA,auxB, auxC,auxD, auxF, auxT, aux = m.pri;
  int i,j, w,z;
  
  for( i = 1; i <543;i++, aux = aux -> abajo);// Posiciona al robot 542
  for( i = 1; i <=7;i++, aux = aux -> sig);// Posiciona al robot
  
  *robDer = aux;
 
  for( i = 1; i <=11; i++, *robDer = (*robDer) -> abajo);// Posiciona al robot
  for( i = 1; i <=7; i++, *robDer = (*robDer) -> sig);// Posiciona al robot
 
  auxA = auxC = auxB = auxD = aux;
  
  for( i = 1; i < 12; i++, aux = aux -> abajo );// Posiciona al bloque base
  for( i = 1; i <= 20; i++, aux = aux -> sig )
      strcpy( aux -> name, "bloqueB" );
 
  // Inisialización de los bloques
   for( i = 1; i <= 10; auxC = auxC -> abajo, i++ );// Altura del apuntador del robot al primer bloque
   
   for( i = 0; i < TALLA; i++ )
   {
     if( i < 20 )
        for( int j = 1; j <= 20; auxC = auxC -> arriba, j++ );// Altura del apuntador del robot al primer bloque
     
     (aB + i ) -> dirBloque = 1;
     
     // Se determina la dirección del los bloques y a su ves se generan los aros con las direcciones de los bloques
     switch( i )
     {
        case 0: for( w = 0 ,auxD = auxC;  w < 0; auxD = auxD -> sig, w++);
                auxT = auxD -> sig -> sig -> sig -> sig -> arriba -> arriba -> arriba;
                generaAros( &auxT, aros, 6, i);
                break; 
        
        case 1: for( w = 0, auxD = auxC; w < 100; auxD = auxD -> sig, w++);break; 
        case 2: for( w = 0, auxD = auxC; w < 50; auxD = auxD -> sig, w++);
                (aB + i ) -> dirBloque = -1; 
                auxT = auxD -> sig -> sig -> sig -> sig -> sig -> arriba -> arriba -> arriba;
                generaAros( &auxT, aros, 3 ,i);
                break; 
        case 3: for( w = 0, auxD = auxC; w < 90; w++, auxD = auxD -> sig );
                auxT = auxD -> sig -> sig -> sig -> sig -> arriba -> arriba -> arriba;
                generaAros( &auxT, aros, 3 ,i);
                break; 
        case 4:for( w = 0, auxD = auxC; w < 5; w++, auxD = auxD -> sig ); 
                auxT = auxD -> sig -> sig -> sig -> sig -> arriba -> arriba -> arriba;
                generaAros( &auxT, aros, 6 ,i);
                break;
        case 5:for( w = 0, auxD = auxC; w < 100; w++, auxD = auxD -> sig );(aB + i ) -> dirBloque = -1;break; 
        case 6:for( w = 0, auxD = auxC; w < 90; auxD = auxD -> sig, w++);
                auxT = auxD -> sig -> sig -> sig -> sig -> arriba -> arriba -> arriba;
                generaAros( &auxT, aros, 3 ,i);
               break; 
        case 7:for( w = 0, auxD = auxC; w < 40; w++, auxD = auxD -> sig );
               auxT = auxD -> sig -> sig -> sig -> sig -> arriba -> arriba -> arriba;
               generaAros( &auxT, aros, 8, i ); 
               break; 
        case 8:for( w = 0, auxD = auxC; w <5; w++, auxD = auxD -> sig );
               auxT = auxD -> sig -> sig -> sig -> sig -> arriba -> arriba -> arriba;
               generaAros( &auxT, aros, 3, i ); 
               break; 
        case 9: for( w = 0, auxD = auxC; w < 5; w++, auxD = auxD -> sig );
                (aB + i ) -> dirBloque = -1;
                auxT = auxD -> sig -> sig -> sig -> sig -> arriba -> arriba -> arriba;
                generaAros( &auxT, aros, 3, i); 
                break; 
        case 10:for( w = 0 ,auxD = auxC;  w < 100; auxD = auxD -> sig, w++);
                (aB + i ) -> dirBloque = -1;
                auxT = auxD -> sig-> sig-> sig -> arriba -> arriba -> arriba;
                generaAros( &auxT, aros, 2, i); 
                break; 
        case 11: for( w = 0, auxD = auxC; w < 5; auxD = auxD -> sig, w++);
                 auxT = auxD -> sig -> sig -> sig -> sig -> arriba -> arriba -> arriba;
                 generaAros( &auxT, aros, 8, i); 
                break; 
        case 12: for( w = 0, auxD = auxC; w < 90; auxD = auxD -> sig, w++);
                 auxT = auxD -> sig -> sig -> sig -> sig -> arriba -> arriba -> arriba;
                 generaAros( &auxT, aros, 3, i);
                 break; 
        case 13:for( w = 0, auxD = auxC; w < 50; w++, auxD = auxD -> sig );
                (aB + i ) -> dirBloque = -1;
                auxT = auxD -> sig -> sig -> sig -> sig ->sig -> arriba -> arriba -> arriba;
                generaAros( &auxT, aros, 3, i);
                break; 
        case 14:for( w = 0, auxD = auxC; w < 5; w++, auxD = auxD -> sig );
                (aB + i ) -> dirBloque = -1;
                auxT = auxD -> sig -> arriba -> arriba -> arriba;
                generaAros( &auxT, aros, 3, i);
                break; 
        case 15:for( w = 0, auxD = auxC; w < 100; w++, auxD = auxD -> sig );
                (aB + i ) -> dirBloque = -1;
                auxT = auxD -> sig -> sig -> sig -> sig ->sig -> arriba -> arriba -> arriba;
                generaAros( &auxT, aros, 1, i);
                break;
        case 16: for( w = 0, auxD = auxC; w < 10; auxD = auxD -> sig, w++);
                 auxT = auxD -> sig -> sig -> sig -> sig -> arriba -> arriba -> arriba;
                 generaAros( &auxT, aros, 3,i); 
                 break; 
        case 17:for( w = 0, auxD = auxC; w < 50; w++, auxD = auxD -> sig );
                 auxT = auxD -> sig -> sig -> sig -> sig -> arriba -> arriba -> arriba;
                generaAros( &auxT, aros, 3,i); 
                break; 
        case 18:for( w = 0, auxD = auxC; w < 80; w++, auxD = auxD -> sig );break; 
        case 19:for( w = 0, auxD = auxC; w < 21; w++, auxD = auxD -> sig );(aB + i ) -> dirBloque = -1;break; 
        case 20:for( w = 0, auxD = auxC; w < 31; w++, auxD = auxD -> sig );(aB + i ) -> dirBloque = -1;break; 
        case 21:for( w = 0, auxD = auxC; w < 41; w++, auxD = auxD -> sig );
                    (aB + i ) -> dirBloque = -1;
                    auxT = auxD -> sig -> sig-> arriba -> arriba -> arriba;
                    generaAros( &auxT, aros, 12,i);
                    break; 
        case 22:for( w = 0, auxD = auxC; w < 51; w++, auxD = auxD -> sig );(aB + i ) -> dirBloque = -1;break; 
        case 23:for( w = 0, auxD = auxC; w < 61; w++, auxD = auxD -> sig );(aB + i ) -> dirBloque = -1;break; 
        case 24:for( w = 0, auxD = auxC; w < 71; w++, auxD = auxD -> sig );(aB + i ) -> dirBloque = -1;break; 
        case 25:for( w = 0, auxD = auxC; w < 81; w++, auxD = auxD -> sig );(aB + i ) -> dirBloque = -1;break; 
      
     }
     
     (aB + i ) -> ptrBloque = auxD;
     
     if( i == 20 )
        *chip = auxD -> arriba-> arriba-> arriba-> arriba-> arriba-> arriba-> arriba-> arriba-> arriba;
     if( i == 19 )
        *bandera =auxD -> arriba-> arriba-> arriba-> arriba-> arriba-> arriba-> arriba-> arriba-> arriba;

         
    // Se ajustan los bloques que no se van a mover
     
     for( z = 0, auxB = auxD; z < 8; z++, auxB = auxB -> sig )
     {
       (aB + i ) -> posBloque[ z ] = auxB;
        
        switch( i )
        {
          case 2:(aB + i ) -> posBloque[ z ] -> dir = -1;break;
          case 5:(aB + i ) -> posBloque[ z ] -> dir = -1;break;
          case 9:(aB + i ) -> posBloque[ z ] -> dir = -1;break;
          case 10:(aB + i ) -> posBloque[ z ] -> dir = -1;break;
          case 13:(aB + i ) -> posBloque[ z ] -> dir = -1;break;
          case 14:(aB + i ) -> posBloque[ z ] -> dir = -1;break;
          case 15:(aB + i ) -> posBloque[ z ] -> dir = -1;break;
          case 19:(aB + i ) -> posBloque[ z ] -> dir = -1;break;
          case 20:(aB + i ) -> posBloque[ z ] -> dir = -1;break;
          case 21:(aB + i ) -> posBloque[ z ] -> dir = -1;break;
          case 22:(aB + i ) -> posBloque[ z ] -> dir = -1;break;
          case 23:(aB + i ) -> posBloque[ z ] -> dir = -1;break;
          case 24:(aB + i ) -> posBloque[ z ] -> dir = -1;break;
          case 25:(aB + i ) -> posBloque[ z ] -> dir = -1;break;
          default: ( aB + i ) -> posBloque[ z ] -> dir = 1;
        }
       strcpy(  (aB + i ) -> posBloque[ z ]-> name, "bloque" );
     }
  }
  
  *robIzq = auxA;
}

/* Esta función se encarga de insertar los aros en el arreglo de los aros, recibe como parametro un apuntador a un nodo de la malla,
 este apuntador se tomó como referencia para la inserción de los demas aros, ya que solo almacenan direcciones recibe el 
 vetor de aros, un  variable que representa la cantidad de aros se genera en la lista y por ultimo una variable que
 indica aquellos aros que se posicionaran en forma horizontal */ 
void generaAros( NODO_MALLA *pM, VA *aros, int nA, int i )
{
    for(int j = 0; j < nA; j++ )
    {
       insAro(  &aros ->arrayA[aros -> nElem], *pM );
       
       switch( i )
       {
         case 4: *pM = (*pM )-> sig -> sig-> sig-> sig;break;
         case 7: *pM = (*pM )-> sig -> sig-> sig-> sig;break;
         case 10: *pM = (*pM )-> sig -> sig-> sig-> sig;break;
         case 11: *pM = (*pM )-> sig -> sig-> sig-> sig;break;
         case 14: *pM = (*pM )-> sig -> sig-> sig-> sig;break;
         case 21: *pM = (*pM )-> sig -> sig-> sig-> sig;break;
         default:   *pM = (*pM )-> arriba -> arriba-> arriba-> arriba-> arriba;
       }
    
    }
    aros -> nElem++;
}

void iniArrayIMG( IMAGEN *a )
{
  for( int i = 0; i < TAM_IMG; i++ )
      a[i] = NULL;
}

/*Funcion: Carga imagenes
  Parametros: Un arreglo de tipo apuntador IMAGEN
  Proceso:
           Se leen todas la imagenes utilizadas en el programa, desde una archivo binario
           guardandolas en un arreglo semidinamico. */

void cargarIMG( IMAGEN *a )
{
  int i;
  void *imgAux;
  
  printf("%p", a[i] );
  
  for( i = 0; i < TAM_IMG; i++ )
  {
     switch( i )
     {
       case 0: imgAux = abrirImagen("heroe");
               insIMG( &a[i], imgAux ); 
               break;
      
       case 1: imgAux = abrirImagen("camDer");
               insIMG( &a[i], imgAux ); 
               imgAux = abrirImagen("camDer2");
               insIMG( &a[i], imgAux ); 
               break;
       
       case 2: imgAux = abrirImagen("camIzq");
               insIMG( &a[i], imgAux ); 
               imgAux = abrirImagen("camIzq2");
               insIMG( &a[i], imgAux ); 
               break;
       
       case 3: imgAux = abrirImagen("brinca");
               insIMG( &a[i], imgAux );
               imgAux = abrirImagen("brinca2");
               insIMG( &a[i], imgAux );
               imgAux = abrirImagen("brinca3");
               insIMG( &a[i], imgAux );
               break;
       
       case 4: 
               imgAux = abrirImagen("brincaD");
               insIMG( &a[i], imgAux );
               imgAux = abrirImagen("brincaD2");
               insIMG( &a[i], imgAux );
               imgAux = abrirImagen("brincaD3");
               insIMG( &a[i], imgAux );
               imgAux = abrirImagen("brincaD4");
               insIMG( &a[i], imgAux );
               break;
       
       case 5: imgAux = abrirImagen("bloqueB2");
               insIMG( &a[i], imgAux );
               imgAux = abrirImagen("bloqueB");
               insIMG( &a[i], imgAux );
               break;
      
       case 6: imgAux = abrirImagen("bloque");
               insIMG( &a[i], imgAux );
               break;
       case 7: imgAux = abrirImagen("robotE");
               insIMG( &a[i], imgAux );
               break;
      case 8: imgAux = abrirImagen("robotDis");
              insIMG( &a[i], imgAux );
              break;
      case 9: imgAux = abrirImagen("chip");
              insIMG( &a[i], imgAux );
              break;
      case 10: imgAux = abrirImagen("bala");
              insIMG( &a[i], imgAux );
              break;
      case 11: imgAux = abrirImagen("bandera");
              insIMG( &a[i], imgAux );
              break;
      case 12: imgAux = abrirImagen("heroe2");
              insIMG( &a[i], imgAux );
              break;
      }
   }
}

/*  Esta función es para abrir alguna imagen del archivo, solo recibe como parametro el nombre de la imagen que
  se abrira, la funcion retorna la imagen */
void * abrirImagen( char * name )
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
    
    imagen = malloc( tamImagen );
    
    fread( imagen, tamImagen, 1 , ptrArch );
  
    fclose( ptrArch );
  }else 
      {
        outtextxy( 260, 275, " No se encontro el archivo imagen               " );
        retraso( 1000 );
      }
 
  return( imagen );    
}  

/* Esta función es para ir insertando las imagenes en una lista circular que esta integrada en el arreglo de 
  imagenes, recibe como parametro el arreglo de imagenes y la dicha imagen que sera inserata */
void insIMG( IMAGEN *ptrImg, void *imagen )
{
  IMAGEN nuevo, aux;
  
  if( creaNodoIMG( &nuevo, imagen ) )
  {
     for(aux = *ptrImg; aux && aux -> sigImg != *ptrImg; aux = aux -> sigImg );
        
     if( !*ptrImg )
        *ptrImg = nuevo;
     else
        aux -> sigImg = nuevo;
    
     nuevo -> sigImg = *ptrImg;
  }
}

/* Esta función crea un nodo con la imagen que posteriormente sera insertada en el arreglo de imagenes, recibe como parametro
 uns lista de tipo IMAGEN y la imagen a insertar */
int creaNodoIMG( IMAGEN *ptrNew, void *imagen )
{
  int res = 0;
  
  if( *ptrNew = ( IMAGEN )malloc( sizeof( struct regImg ) ) )
  {
    (*ptrNew) -> img = imagen;
    (*ptrNew) -> sigImg = NULL;
    res = 1;
  }
  
  return( res );
}

// Se inicializa la estructura de la malla
void iniMalla( MALLA *m )
{
   m -> pri = NULL;
   m -> ult = NULL;
}

/* Se crea la malla, con los renglones y columnas indicados en las constantes simbolicas, recibe como parametro( por referencia )
  la estructura malla */
void creaMalla( MALLA *m)
{
   int i,j, x, y;
   NODO_MALLA aux, antRen,nuevo;
   
   y = -2100; // -2100
   
   m -> nRen = REN_M;
   m -> nCol = COL_M;
   
  for( i = 1; i <= m -> nRen; i++, y += 5)
   {
      x = -42;
     for( j = 1; j <= m -> nCol; j++ , x += 7 )
          if( creaNodo( &nuevo, x , y ) )
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
               
           antRen = aux;
     }
}

// Esta función crea un nodo de la malla, recibe un apuntador, y las cordenadas de la malla(por valor)
int creaNodo( NODO_MALLA  *m, int x, int y )
{
  int ret = 0;
  
  *m = ( NODO_MALLA )malloc( sizeof( struct regNodo ) );
   
   if( *m )
   {
     (*m) -> corX = x;
     (*m) -> corY = y;
     (*m) -> existencia = 0;
     (*m) -> ant = NULL;
     (*m) -> sig = NULL;
     (*m) -> arriba = NULL;
     (*m) -> abajo = NULL;
     (*m) -> imagen = NULL;
     (*m) -> name[0] = '\n';
     (*m) -> dir = 1;
      
      ret = 1;
  }
  
  return( ret );
}

// Se hace uso de esta funcion en lugar del delay para tener el sistema
void retraso(int ms)
{
  clock_t i,j;
 
  i=clock();
 
  do
  {
    j=clock();
  }while((j-i) < ms);  
}

 

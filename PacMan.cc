#include <esat/window.h>
#include <esat/draw.h>
#include <esat/sprite.h>
#include <esat/input.h>
#include <esat/time.h>
#include <stdio.h>


#include <esat_extra/soloud/soloud.h>
#include <esat_extra/soloud/soloud_wav.h>

 SoLoud::Soloud canal;
 //Declaración variables canal audio.
 SoLoud::Wav ejemplo1,ejemplo2;
 
 esat::SpriteHandle SpriteSheet;
 esat::SpriteHandle Mapa;
 esat::SpriteHandle PacMan[12];
 esat::SpriteHandle Dot[2];

 int auxanim=0;
 int AnimPacMan[4][4]={	0,1,2,1,
 						0,3,4,3,
 						0,5,6,5,
 						0,7,8,7	};
 int w=672/28;
 int h=744/31;


 int estados[31][14]={	1,1,1,1,1,1,1,1,1,1,1,1,1,1,
 						1,2,2,2,2,2,2,2,2,2,2,2,2,1,
 						1,2,1,1,1,1,2,1,1,1,1,1,2,1,
 						1,3,1,1,1,1,2,1,1,1,1,1,2,1,
 						1,2,1,1,1,1,2,1,1,1,1,1,2,1,
 						1,2,2,2,2,2,2,2,2,2,2,2,2,2,
 						1,2,1,1,1,1,2,1,1,2,1,1,1,1,
 						1,2,1,1,1,1,2,1,1,2,1,1,1,1,
 						1,2,2,2,2,2,2,1,1,2,2,2,2,1,
 						1,1,1,1,1,1,2,1,1,1,1,1,0,1,
 						1,1,1,1,1,1,2,1,1,1,1,1,0,1,
 						1,1,1,1,1,1,2,1,1,0,0,0,0,0,
 						1,1,1,1,1,1,2,1,1,0,1,1,1,1,
 						1,1,1,1,1,1,2,1,1,0,1,1,1,1,
 						0,0,0,0,0,0,2,0,0,0,1,1,0,0,
 						1,1,1,1,1,1,2,1,1,0,1,1,1,1,
 						1,1,1,1,1,1,2,1,1,0,1,1,1,1,
 						1,1,1,1,1,1,2,1,1,0,0,0,0,0,
 						1,1,1,1,1,1,2,1,1,0,1,1,1,1,
 						1,1,1,1,1,1,2,1,1,0,1,1,1,1,
 						1,2,2,2,2,2,2,2,2,2,2,2,2,1,
 						1,2,1,1,1,1,2,1,1,1,1,1,2,1,
 						1,2,1,1,1,1,2,1,1,1,1,1,2,1,
 						1,3,2,2,1,1,2,2,2,2,2,2,2,2,
 						1,1,1,2,1,1,2,1,1,2,1,1,1,1,
 						1,1,1,2,1,1,2,1,1,2,1,1,1,1,
 						1,2,2,2,2,2,2,1,1,2,2,2,2,1,
 						1,2,1,1,1,1,1,1,1,1,1,1,2,1,
 						1,2,1,1,1,1,1,1,1,1,1,1,2,1,
 						1,2,2,2,2,2,2,2,2,2,2,2,2,2,
 						1,1,1,1,1,1,1,1,1,1,1,1,1,1
 					};
 
 struct casillas{
	int ax,ay,bx,by;
	int tipo;
	esat::SpriteHandle sprite;
}casilla[31][28]; 

struct PacMan{
	int x,y;
	int cx1,cy1,cx2,cy2;
	int d=1;
	int v=1;
	int casillaX,casillaY;
	int anim=1;
	bool stuck=false;
	esat::SpriteHandle sprite;
}pacman;                      
 
 void InitPacMan(){
	 pacman.casillaX = 13;
	 pacman.casillaY = 17;
	 pacman.cx1 = pacman.casillaX*w + 12;
	 pacman.cy1 = pacman.casillaY*h;
	 pacman.cx2 = pacman.cx1 + 24;
	 pacman.cy2 = pacman.cy1 + 24;
	 pacman.x = pacman.cx1 - 12;
	 pacman.y = pacman.cy1 - 10;
	 
 }
 

 void DrawPacManCol(){
	 
	 esat::DrawLine(pacman.cx1,pacman.cy1,pacman.cx2,pacman.cy2);
	 
 }
 
void CargaSprites(){
	
	SpriteSheet = esat::SpriteFromFile("./Recursos/Imagenes/PacMan.png");
	
	Mapa = esat::SubSprite(SpriteSheet,0,0,672,744);
	
	for(int i=0;i<9;i++){
		PacMan[i] = esat::SubSprite(SpriteSheet,682+i*44,0,42,42);
	}

	Dot[0] = esat::SubSprite(SpriteSheet,682,364,24,24);
	Dot[1] = esat::SubSprite(SpriteSheet,709,364,24,24);
}

void InitPos(){
	
	for(int i=0;i<31;i++){
		for(int j=0;j<28;j++){
			casilla[i][j].ax=w*j;
			casilla[i][j].ay=h*i;
			casilla[i][j].bx=w*j + w;
			casilla[i][j].by=h*i + h;
		}
	}
}

void DrawMatriz(){

	for(int j=0;j<28;j++){
		esat::DrawLine(j*w,0,j*w,744);
	}
	for(int i=0;i<31;i++){
		esat::DrawLine(0,i*h,672,i*h);
	}
	
}

void InitCasillas(){

	for(int i=0;i<31;i++){
		for(int j=0;j<14;j++){
			casilla[i][j].tipo=estados[i][j];
			casilla[i][27-j].tipo=estados[i][j];
			
			if(estados[i][j]==2){
				printf("hola2");
				casilla[i][j].sprite=Dot[0];
				casilla[i][27-j].sprite=Dot[0];
			}else if(estados[i][j]==3){
				printf("hola3");
				casilla[i][j].sprite=Dot[1];
				casilla[i][27-j].sprite=Dot[1];
			
			}
		}
	}
}

void PacManInput(){
	
	if(esat::IsSpecialKeyDown(esat::kSpecialKey_Right))
		pacman.d = 1;
	else if(esat::IsSpecialKeyDown(esat::kSpecialKey_Left))
		pacman.d = 2;
	else if(esat::IsSpecialKeyDown(esat::kSpecialKey_Up))
		pacman.d = 3;
	else if(esat::IsSpecialKeyDown(esat::kSpecialKey_Down))
		pacman.d = 4;

}

void UpdatePacManCasilla(){
	
	pacman.casillaX = (pacman.cx1+w/2)/w;
	pacman.casillaY = (pacman.cy1+h/2)/h;
	printf("%d, %d\n",pacman.casillaX,pacman.casillaY);
	
}

 bool Col(int a1x, int a1y, int a2x, int a2y, int b1x, int b1y, int b2x, int b2y){

	if(a2x < b1x || a1x > b2x)
		return false;
	else if(a2y < b1y || a1y > b2y)
		return false;
	else{
		printf("col \n");
		return true;
	}
		 
}
 

void PacManMov(){

	switch (pacman.d){
		
		case 1:
		printf("(%d,%d),(%d,%d)\n",pacman.cx1+pacman.v,pacman.cy1,pacman.cx2+pacman.v,pacman.cy2);
		printf("(%d,%d)->(%d,%d),(%d,%d)\n", pacman.casillaX+1, pacman.casillaY, casilla[pacman.casillaX+1][pacman.casillaY].ax,casilla[pacman.casillaX+1][pacman.casillaY].ay,
			casilla[pacman.casillaX+1][pacman.casillaY].bx,casilla[pacman.casillaX+1][pacman.casillaY].by);
			if(Col(pacman.cx1+pacman.v,pacman.cy1,pacman.cx2+pacman.v,pacman.cy2,
			casilla[pacman.casillaX+1][pacman.casillaY].ax,casilla[pacman.casillaX+1][pacman.casillaY].ay,
			casilla[pacman.casillaX+1][pacman.casillaY].bx,casilla[pacman.casillaX+1][pacman.casillaY].by) 
			&& casilla[pacman.casillaX+1][pacman.casillaY].tipo==1){
				pacman.stuck=true;
			}else{
				pacman.x+=pacman.v;
				pacman.cx1+=pacman.v;
				pacman.cx2+=pacman.v;
			}
			break;
		case 2:
			printf("(%d,%d),(%d,%d)\n",pacman.cx1-pacman.v,pacman.cy1,pacman.cx2-pacman.v,pacman.cy2);
		printf("(%d,%d)->(%d,%d),(%d,%d)\n", pacman.casillaX-1, pacman.casillaY, casilla[pacman.casillaX-1][pacman.casillaY].ax,casilla[pacman.casillaX-1][pacman.casillaY].ay,
			casilla[pacman.casillaX-1][pacman.casillaY].ax,casilla[pacman.casillaX-1][pacman.casillaY].ay);
			if(Col(pacman.cx1-pacman.v,pacman.cy1,pacman.cx2-pacman.v,pacman.cy2,
			casilla[pacman.casillaX-1][pacman.casillaY].ax,casilla[pacman.casillaX-1][pacman.casillaY].ay,
			casilla[pacman.casillaX-1][pacman.casillaY].ax,casilla[pacman.casillaX-1][pacman.casillaY].ay) 
			&& casilla[pacman.casillaX-1][pacman.casillaY].tipo==1){
				pacman.stuck=true;
			}else{
				pacman.x-=pacman.v;
				pacman.cx1-=pacman.v;
				pacman.cx2-=pacman.v;
			}
			break;
		case 3:
		printf("(%d,%d),(%d,%d)\n",pacman.cx1,pacman.cy1-pacman.v,pacman.cx2,pacman.cy2-pacman.v);
		printf("(%d,%d)->(%d,%d),(%d,%d)\n", pacman.casillaX, pacman.casillaY-1, casilla[pacman.casillaX][pacman.casillaY-1].ax,casilla[pacman.casillaX][pacman.casillaY-1].ay,
			casilla[pacman.casillaX][pacman.casillaY-1].ax,casilla[pacman.casillaX][pacman.casillaY-1].ay);
			if(Col(pacman.cx1,pacman.cy1-pacman.v,pacman.cx2,pacman.cy2-pacman.v,
			casilla[pacman.casillaX][pacman.casillaY-1].ax,casilla[pacman.casillaX][pacman.casillaY-1].ay,
			casilla[pacman.casillaX][pacman.casillaY-1].ax,casilla[pacman.casillaX][pacman.casillaY-1].ay) 
			&& casilla[pacman.casillaX][pacman.casillaY-1].tipo==1){
				pacman.stuck=true;
			}else{
				pacman.y-=pacman.v;
				pacman.cy1-=pacman.v;
				pacman.cy2-=pacman.v;
			}
			break;
		case 4:
		printf("(%d,%d),(%d,%d)\n",pacman.cx1,pacman.cy1+pacman.v,pacman.cx2,pacman.cy2+pacman.v);
		printf("(%d,%d)->(%d,%d),(%d,%d)\n",pacman.casillaX, pacman.casillaY+1, casilla[pacman.casillaX][pacman.casillaY+1].ax,casilla[pacman.casillaX][pacman.casillaY+1].ay,
			casilla[pacman.casillaX][pacman.casillaY+1].ax,casilla[pacman.casillaX][pacman.casillaY+1].ay);
			if(Col(pacman.cx1,pacman.cy1+pacman.v,pacman.cx2,pacman.cy2+pacman.v,
			casilla[pacman.casillaX][pacman.casillaY+1].ax,casilla[pacman.casillaX][pacman.casillaY+1].ay,
			casilla[pacman.casillaX][pacman.casillaY+1].ax,casilla[pacman.casillaX][pacman.casillaY+1].ay) 
			&& casilla[pacman.casillaX][pacman.casillaY+1].tipo==1){
				pacman.stuck=true;
			}else{
				pacman.y+=pacman.v;
				pacman.cy1+=pacman.v;
				pacman.cy2+=pacman.v;
			}
			break;
	}
}

void PacManAnim(){

	if(auxanim==4)
		auxanim=0;
	else
		pacman.sprite=PacMan[AnimPacMan[pacman.d-1][auxanim]];

	auxanim++;
}

void DrawDots(){

	for(int i=0;i<31;i++){
		for(int j=0;j<28;j++){
			if(casilla[i][j].tipo == 2 || casilla[i][j].tipo == 3)
				esat::DrawSprite(casilla[i][j].sprite,casilla[i][j].ax,casilla[i][j].ay);
		}
	}
}

void MuestraPacMan(){

	esat::DrawSprite(pacman.sprite,pacman.x,pacman.y);
	DrawDots();

}



/*void ColMuros(){
	if(Col(pacman.cx1,pacman.cy1,))
}*/

int esat::main(int argc, char **argv) {
 
  double current_time,last_time;
  unsigned char fps=30;

  int pacmananim=1;



  //Inicialicización sistema audio.
  canal.init();
  //Carga audio en cada variable canal audio.
  ejemplo1.load("./Recursos/Audio/ogg/dp_frogger_extra.ogg");
  ejemplo2.load("./Recursos/Audio/ogg/dp_frogger_start.ogg");
 
  esat::WindowInit(672,744);
  WindowSetMouseVisibility(true);
  CargaSprites();
  pacman.sprite = PacMan[1];
  InitPacMan();
  InitPos();
  InitCasillas();
  
  for(int i=0;i<31;i++){
	for(int j=0;j<28;j++){
		printf("%02d", casilla[i][j].tipo);		
	}
	printf("\n");
  }
  

  while(esat::WindowIsOpened() && !esat::IsSpecialKeyDown(esat::kSpecialKey_Escape)) {
	last_time = esat::Time();
	
	esat::DrawBegin();
    esat::DrawClear(0,0,0);
	
	PacManAnim();
    PacManInput();
	UpdatePacManCasilla();
    PacManMov();
	

	esat::DrawSprite(Mapa,0,0);
	esat::DrawSetStrokeColor(255,255,255);
	DrawMatriz();
	MuestraPacMan();
	DrawPacManCol();

	
    



    /*if(esat::IsSpecialKeyPressed(esat::kSpecialKey_Left)){
      canal.play(ejemplo1); //Inicia reproducción canal
    }
    if(esat::IsSpecialKeyPressed(esat::kSpecialKey_Right)){
      ejemplo1.stop(); //Finaliza reproducción canal
    }
    if(esat::IsSpecialKeyPressed(esat::kSpecialKey_Up)){
      canal.play(ejemplo2);
    }
    if(esat::IsSpecialKeyPressed(esat::kSpecialKey_Down)){
      ejemplo2.stop();
    }*/
    
    esat::DrawEnd();
	
	do{
    current_time = esat::Time();
    }while((current_time-last_time)<=1000.0/fps);
    esat::WindowFrame();
  }
  
  esat::WindowDestroy();
   //Finalización sitema audio.
  canal.deinit();
  return 0;
}
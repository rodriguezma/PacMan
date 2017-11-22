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
	int x=312,y=399;
	int cx,cy;
	int d=1;
	int v=3;
	int anim=1;
	esat::SpriteHandle sprite;
}pacman;                      
 
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
				casilla[i][j].sprite = arrayspritesderecha[casilla[i][j].tipomuro];
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

void PacManMov(){

	switch (pacman.d){
		
		case 1:
			pacman.x+=pacman.v;
			break;
		case 2:
			pacman.x-=pacman.v;
			break;
		case 3:
			pacman.y-=pacman.v;
			break;
		case 4:
			pacman.y+=pacman.v;
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

bool Col(int x, int y, int ax, int ay, int bx, int by){

	if(x < ax || x > bx)
		return false;
	else if(y < ay || y > by)
		return false;
	else
		return true; 
}

void ColMuros(){

}

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
  InitPos();
  InitCasillas();
  

  while(esat::WindowIsOpened() && !esat::IsSpecialKeyDown(esat::kSpecialKey_Escape)) {
	last_time = esat::Time();
	
	esat::DrawBegin();
    esat::DrawClear(0,0,0);
	
	PacManAnim();
    PacManInput();
    PacManMov();

	esat::DrawSprite(Mapa,0,0);
	esat::DrawSetStrokeColor(255,255,255);
	DrawMatriz();
	MuestraPacMan();

	
    



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
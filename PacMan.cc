


#include <esat/window.h>
#include <esat/draw.h>
#include <esat/sprite.h>
#include <esat/input.h>
#include <esat/time.h>


#include <esat_extra/soloud/soloud.h>
#include <esat_extra/soloud/soloud_wav.h>

 SoLoud::Soloud canal;
 //Declaración variables canal audio.
 SoLoud::Wav ejemplo1,ejemplo2;
 
 esat::SpriteHandle SpriteSheet;
 esat::SpriteHandle Mapa;
 esat::SpriteHandle PacMan[4][3];

 int auxanim=0;
 int AnimPacMan[]={0,1,2,1};
 int w=672/28;
 int h=744/31;

 int estados[31][14]={	1,1,1,1,1,1,1,1,1,1,1,1,1,1,
 						1,0,0,0,0,0,0,0,0,0,0,0,0,1,
 						1,0,1,1,1,1,0,1,1,1,1,1,0,1,
 						1,0,1,1,1,1,0,1,1,1,1,1,0,1,
 						1,0,1,1,1,1,0,1,1,1,1,1,0,1,
 						1,0,0,0,0,0,0,0,0,0,0,0,0,0,
 						1,0,1,1,1,1,0,1,1,0,1,1,1,1,
 						1,0,1,1,1,1,0,1,1,0,1,1,1,1,
 						1,0,0,0,0,0,0,1,1,0,0,0,0,1,
 						1,1,1,1,1,1,0,1,1,1,1,1,0,1,
 						1,1,1,1,1,1,0,1,1,1,1,1,0,1,
 						1,1,1,1,1,1,0,1,1,0,0,0,0,0,
 						1,1,1,1,1,1,0,1,1,0,1,1,1,1,
 						1,1,1,1,1,1,0,1,1,0,1,1,1,1,
 						0,0,0,0,0,0,0,0,0,0,1,1,0,0,
 						1,1,1,1,1,1,0,1,1,0,1,1,1,1,
 						1,1,1,1,1,1,0,1,1,0,1,1,1,1,
 						1,1,1,1,1,1,0,1,1,0,0,0,0,0,
 						1,1,1,1,1,1,0,1,1,0,1,1,1,1,
 						1,1,1,1,1,1,0,1,1,0,1,1,1,1,
 						1,0,0,0,0,0,0,0,0,0,0,0,0,1,
 						1,0,1,1,1,1,0,1,1,1,1,1,0,1,
 						1,0,1,1,1,1,0,1,1,1,1,1,0,1,
 						1,0,0,0,1,1,0,0,0,0,0,0,0,0,
 						1,1,1,0,1,1,0,1,1,0,1,1,1,1,
 						1,1,1,0,1,1,0,1,1,0,1,1,1,1,
 						1,0,0,0,0,0,0,1,1,0,0,0,0,1,
 						1,0,1,1,1,1,1,1,1,1,1,1,0,1,
 						1,0,1,1,1,1,1,1,1,1,1,1,0,1,
 						1,0,0,0,0,0,0,0,0,0,0,0,0,0,
 						1,1,1,1,1,1,1,1,1,1,1,1,1,1
 					};
 
 struct casillas{
	int ax,ay,bx,by;
	bool muro;
}casilla[31][28]; 

struct PacMan{
	int x,y;
	int cx,cy;
	int d=1;
	int v=3;
	int anim=1;
	esat::SpriteHandle sprite;
}pacman;                      
 
void CargaSprites(){
	
	SpriteSheet = esat::SpriteFromFile("./Recursos/Imagenes/SpriteNuevo.png");
	
	Mapa = esat::SubSprite(SpriteSheet,0,371,672,744);
	
	PacMan[0][0] = esat::SubSprite(SpriteSheet,742,310,39,39);
	PacMan[0][1] = esat::SubSprite(SpriteSheet,684,310,39,39);
  	PacMan[0][2] = esat::SubSprite(SpriteSheet,623,310,39,39);
  	PacMan[1][0] = esat::SubSprite(SpriteSheet,565,192,39,39);
	PacMan[1][1] = esat::SubSprite(SpriteSheet,515,192,39,39);
  	PacMan[1][2] = esat::SubSprite(SpriteSheet,623,310,39,39);
  	PacMan[2][0] = esat::SubSprite(SpriteSheet,562,298,39,39);
	PacMan[2][1] = esat::SubSprite(SpriteSheet,406,188,39,39);
  	PacMan[2][2] = esat::SubSprite(SpriteSheet,623,310,39,39);
  	PacMan[3][0] = esat::SubSprite(SpriteSheet,345,192,39,39);
	PacMan[3][1] = esat::SubSprite(SpriteSheet,284,192,39,39);
  	PacMan[3][2] = esat::SubSprite(SpriteSheet,623,310,39,39);
	  	
}

void InitPos(){
	
	for(int i=0;i<31;i++){
		for(int j=0;j<28;j++){
			casilla[i][j].ax=w*i;
			casilla[i][j].ay=h*j;
			casilla[i][j].bx=w*i + w;
			casilla[i][j].by=h*j + h;
		}
	}
}

void InitMuros(){

	for(int i=0;i<31;i++){
		for(int j=0;j<14;j++){
			casilla[i][j].muro=estados[i][j];
			casilla[i][28-j].muro=estados[i][j];
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

	pacman.sprite = PacMan[pacman.d-1][AnimPacMan[auxanim%4]];
	auxanim++;

}

void MuestraPacMan(){

	esat::DrawSprite(pacman.sprite,pacman.x,pacman.y);
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
  unsigned char fps=20;

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
  

  while(esat::WindowIsOpened() && !esat::IsSpecialKeyDown(esat::kSpecialKey_Escape)) {
	last_time = esat::Time();
	
	esat::DrawBegin();
    esat::DrawClear(0,0,0);
	
	PacManAnim();
    PacManInput();
    PacManMov();

	esat::DrawSprite(Mapa,0,0);
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



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
 
 struct casillas{
	int x,y;
	bool muro;
}casilla[28][31];                       
 
void CargaSprites(){
	
	SpriteSheet = esat::SpriteFromFile("./Recursos/Imagenes/sprite.png");
	Mapa = esat::SubSprite(SpriteSheet,0,0,448,492);
	
}

void InitTablero(){
	
	int a=448/28;
	int b=492/31;
	
	for(int i=0;i<28;i++){
		for(int j=0;j<31;j++){
			casilla[i][j].x=a*i;
			casilla[i][j].y=b*j;
		}
	}

}


int esat::main(int argc, char **argv) {
 
  double current_time,last_time;
  unsigned char fps=25;

  //Inicialicización sistema audio.
  canal.init();
  //Carga audio en cada variable canal audio.
  ejemplo1.load("./Recursos/Audio/ogg/dp_frogger_extra.ogg");
  ejemplo2.load("./Recursos/Audio/ogg/dp_frogger_start.ogg");
 
  esat::WindowInit(448,492);
  WindowSetMouseVisibility(true);
  
  CargaSprites();
  

  while(esat::WindowIsOpened() && !esat::IsSpecialKeyDown(esat::kSpecialKey_Escape)) {
	last_time = esat::Time();
	
	esat::DrawBegin();
    esat::DrawClear(0,0,0);
	
	esat::DrawSprite(Mapa,0,0);
	
    if(esat::IsSpecialKeyPressed(esat::kSpecialKey_Left)){
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
    }
    
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
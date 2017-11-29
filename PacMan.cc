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
 esat::SpriteHandle PacMan[9];
 esat::SpriteHandle Dot[2];
 esat::SpriteHandle	Fantasmas[4][8];

 //int auxanim=0;
 int AnimPacMan[4][4]={	0,1,2,1,
 						0,3,4,3,
 						0,5,6,5,
 						0,7,8,7	};
 int w=672/28;
 int h=744/31;

 int frames=0;
 int framesAnim=0;



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
 						1,1,1,1,1,1,2,1,1,0,1,1,1,4,
 						1,1,1,1,1,1,2,1,1,0,1,0,0,0,
 						0,0,0,0,0,0,2,0,0,0,1,0,0,0,
 						1,1,1,1,1,1,2,1,1,0,1,0,0,0,
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
	int casillaF,casillaC;
	int anim=0;
	bool stuck=false;
	esat::SpriteHandle sprite;
}pacman;  

struct Fantasmas{
	int x,y;
	int cx1,cy1,cx2,cy2;
	int d=1;
	int v=1;
	int casillaF,casillaC;
	int anim=0;
	bool stuck=false;
	esat::SpriteHandle sprite;
	bool vivo=true;
}fantasma[4];   

                 
 
 void InitPacMan(){
	 pacman.casillaC = 13;
	 pacman.casillaF = 17;
	 pacman.cx1 = pacman.casillaC*w;
	 pacman.cy1 = pacman.casillaF*h;
	 pacman.cx2 = pacman.cx1 + w;
	 pacman.cy2 = pacman.cy1 + h;
	 pacman.x = pacman.cx1 - 10;
	 pacman.y = pacman.cy1 - 10;
	 
 }
 
 void InitFantasmas(){
	 
	 fantasma[0].cx1 = 278;
	 fantasma[0].cy1 = 336;
	
	 fantasma[1].cx1 = 370;
	 fantasma[1].cy1 = 336;
	
	 fantasma[2].cx1 = 312;
	 fantasma[2].cy1 = 312;
	 fantasma[2].d = 3;
	
	 fantasma[3].cx1 = 324;
	 fantasma[3].cy1 = 264;


	 for(int i=0;i<4;i++){
	 	fantasma[i].x = fantasma[i].cx1-10;
	 	fantasma[i].y = fantasma[i].cy1-10;
	 	fantasma[i].cx2 = fantasma[i].cx1+24;
	 	fantasma[i].cy2 = fantasma[i].cy1+24;
	 }
	 
	 fantasma[0].sprite = Fantasmas[0][0];
	 fantasma[1].sprite = Fantasmas[1][0];
	 fantasma[2].sprite = Fantasmas[2][0];
	 fantasma[3].sprite = Fantasmas[3][0];
	 
}


 void MostrarFantasmas(){
 	for(int i=0;i<4;i++){
 		if(fantasma[i].vivo)
 			esat::DrawSprite(fantasma[i].sprite,fantasma[i].x,fantasma[i].y);
 	}
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

	for(int i=0;i<4;i++){
		for(int j=0;j<8;j++){
			Fantasmas[i][j] = esat::SubSprite(SpriteSheet,682+j*51,104+i*54,42,42);		
		}
	}
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
				
				casilla[i][j].sprite=Dot[0];
				casilla[i][27-j].sprite=Dot[0];
			}else if(estados[i][j]==3){
				
				casilla[i][j].sprite=Dot[1];
				casilla[i][27-j].sprite=Dot[1];
			
			}
		}
	}
}

void PacManInput(){
	
	if(esat::IsSpecialKeyPressed(esat::kSpecialKey_Right)){
		if(pacman.cy1==casilla[pacman.casillaF][pacman.casillaC+1].ay)
			pacman.d = 1;
	}
	else if(esat::IsSpecialKeyPressed(esat::kSpecialKey_Left)){
		printf("izquierda: %d , %d\n",pacman.cy1,casilla[pacman.casillaF][pacman.casillaC-1].ay);
		if(pacman.cy1==casilla[pacman.casillaF][pacman.casillaC-1].ay)
			pacman.d = 2;
	}
	else if(esat::IsSpecialKeyPressed(esat::kSpecialKey_Up)){
		printf("arriba: %d , %d\n",pacman.cx1,casilla[pacman.casillaF+1][pacman.casillaC].ax);
		if(pacman.cx1==casilla[pacman.casillaF+1][pacman.casillaC].ax)
			pacman.d = 3;
	}
	else if(esat::IsSpecialKeyPressed(esat::kSpecialKey_Down)){
		printf("abajo: %d , %d\n",pacman.cx1,casilla[pacman.casillaF-1][pacman.casillaC].ax);
		if(pacman.cx1==casilla[pacman.casillaF-1][pacman.casillaC].ax)
			pacman.d = 4;
	}
}

void UpdatePacManCasilla(){
	
	pacman.casillaC = (pacman.cx1+w/2)/w;
	pacman.casillaF = (pacman.cy1+h/2)/h;
	printf("%d, %d\n",pacman.casillaF,pacman.casillaC);
	
}

void UpdateFantasmasCasilla(){
	for(int i=0;i<4;i++){
			fantasma[i].casillaC = (fantasma[i].cx1+w/2)/w;	
			fantasma[i].casillaF = (fantasma[i].cy1+h/2)/h;
		}
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

bool ColSwitch(int d){
	switch (d){
		case 1:
			if(Col(pacman.cx1, pacman.cy1, pacman.cx2, pacman.cy2, 
				casilla[pacman.casillaF][pacman.casillaC+1].ax, casilla[pacman.casillaF][pacman.casillaC+1].ay, 
				casilla[pacman.casillaF][pacman.casillaC+1].bx, casilla[pacman.casillaF][pacman.casillaC+1].by)){
					return true;
			}else{
				return false;
			}
			break;
		case 2:
			if(Col(pacman.cx1, pacman.cy1, pacman.cx2, pacman.cy2, 
				casilla[pacman.casillaF][pacman.casillaC-1].ax, casilla[pacman.casillaF][pacman.casillaC-1].ay, 
				casilla[pacman.casillaF][pacman.casillaC-1].bx, casilla[pacman.casillaF][pacman.casillaC-1].by)){
					return true;
			}else{
				return false;
			}
			break;
		case 3:
			if(Col(pacman.cx1, pacman.cy1, pacman.cx2, pacman.cy2, 
				casilla[pacman.casillaF-1][pacman.casillaC].ax, casilla[pacman.casillaF-1][pacman.casillaC].ay, 
				casilla[pacman.casillaF-1][pacman.casillaC].bx, casilla[pacman.casillaF-1][pacman.casillaC].by)){
					return true;
			}else{
				return false;
			}
			break;
		case 4:
			if(Col(pacman.cx1, pacman.cy1, pacman.cx2, pacman.cy2, 
				casilla[pacman.casillaF+1][pacman.casillaC].ax, casilla[pacman.casillaF+1][pacman.casillaC].ay, 
				casilla[pacman.casillaF+1][pacman.casillaC].bx, casilla[pacman.casillaF+1][pacman.casillaC].by)){
					return true;
			}else{
				return false;
			}
		break;
	}
}

void ColPacManFantasmas(){

	for(int i=0;i<4;i++){

		if(Col(fantasma[i].cx1, fantasma[i].cy1, fantasma[i].cx2, fantasma[i].cy2,
			pacman.cx1, pacman.cy1, pacman.cx2, pacman.cy2))

			fantasma[i].vivo=false;


	}

}

bool ColSwitchFantasma(int i, int d){
	switch (d){
		case 1:
			if(Col(fantasma[i].cx1, fantasma[i].cy1, fantasma[i].cx2, fantasma[i].cy2, 
				casilla[fantasma[i].casillaF][fantasma[i].casillaC+1].ax, casilla[fantasma[i].casillaF][fantasma[i].casillaC+1].ay, 
				casilla[fantasma[i].casillaF][fantasma[i].casillaC+1].bx, casilla[fantasma[i].casillaF][fantasma[i].casillaC+1].by)){
					return true;
			}else{
				return false;
			}
			break;
		case 2:
			if(Col(fantasma[i].cx1, fantasma[i].cy1, fantasma[i].cx2, fantasma[i].cy2, 
				casilla[fantasma[i].casillaF][fantasma[i].casillaC-1].ax, casilla[fantasma[i].casillaF][fantasma[i].casillaC-1].ay, 
				casilla[fantasma[i].casillaF][fantasma[i].casillaC-1].bx, casilla[fantasma[i].casillaF][fantasma[i].casillaC-1].by)){
					return true;
			}else{
				return false;
			}
			break;
		case 3:
			if(Col(fantasma[i].cx1, fantasma[i].cy1, fantasma[i].cx2, fantasma[i].cy2, 
				casilla[fantasma[i].casillaF-1][fantasma[i].casillaC].ax, casilla[fantasma[i].casillaF-1][fantasma[i].casillaC].ay, 
				casilla[fantasma[i].casillaF-1][fantasma[i].casillaC].bx, casilla[fantasma[i].casillaF-1][fantasma[i].casillaC].by)){
					return true;
			}else{
				return false;
			}
			break;
		case 4:
			if(Col(fantasma[i].cx1, fantasma[i].cy1, fantasma[i].cx2, fantasma[i].cy2, 
				casilla[fantasma[i].casillaF+1][fantasma[i].casillaC].ax, casilla[fantasma[i].casillaF+1][fantasma[i].casillaC].ay, 
				casilla[fantasma[i].casillaF+1][fantasma[i].casillaC].bx, casilla[fantasma[i].casillaF+1][fantasma[i].casillaC].by)){
					return true;
			}else{
				return false;
			}
		break;
	}
}

bool ColSwitch(int d, int a){
	switch (d){
		case 1:
			if(Col(pacman.cx1 + a, pacman.cy1 + a, pacman.cx2 - a, pacman.cy2 - a, 
				casilla[pacman.casillaF][pacman.casillaC+1].ax, casilla[pacman.casillaF][pacman.casillaC+1].ay, 
				casilla[pacman.casillaF][pacman.casillaC+1].bx, casilla[pacman.casillaF][pacman.casillaC+1].by)){
					return true;
			}else{
				return false;
			}
			break;
		case 2:
			if(Col(pacman.cx1 + a, pacman.cy1 + a, pacman.cx2 - a, pacman.cy2 - a, 
				casilla[pacman.casillaF][pacman.casillaC-1].ax, casilla[pacman.casillaF][pacman.casillaC-1].ay, 
				casilla[pacman.casillaF][pacman.casillaC-1].bx, casilla[pacman.casillaF][pacman.casillaC-1].by)){
					return true;
			}else{
				return false;
			}
			break;
		case 3:
			if(Col(pacman.cx1 + a, pacman.cy1 + a, pacman.cx2 - a, pacman.cy2 - a, 
				casilla[pacman.casillaF-1][pacman.casillaC].ax, casilla[pacman.casillaF-1][pacman.casillaC].ay, 
				casilla[pacman.casillaF-1][pacman.casillaC].bx, casilla[pacman.casillaF-1][pacman.casillaC].by)){
					return true;
			}else{
				return false;
			}
			break;
		case 4:
			if(Col(pacman.cx1 + a, pacman.cy1 + a, pacman.cx2 - a, pacman.cy2 - a, 
				casilla[pacman.casillaF+1][pacman.casillaC].ax, casilla[pacman.casillaF+1][pacman.casillaC].ay, 
				casilla[pacman.casillaF+1][pacman.casillaC].bx, casilla[pacman.casillaF+1][pacman.casillaC].by)){
					return true;
			}else{
				return false;
			}
		break;
	}
}

void PacManMov(){

	switch (pacman.d){
		
		case 1:
			if(ColSwitch(pacman.d) && (casilla[pacman.casillaF][pacman.casillaC+1].tipo==1 || casilla[pacman.casillaF][pacman.casillaC+1].tipo==4)){
			
			}else{
				pacman.x+=pacman.v;
				pacman.cx1+=pacman.v;
				pacman.cx2+=pacman.v;
			}
			break;
		case 2:
			if(ColSwitch(pacman.d) && (casilla[pacman.casillaF][pacman.casillaC-1].tipo==1 || casilla[pacman.casillaF][pacman.casillaC-1].tipo==4)){
				
			}else{
				pacman.x-=pacman.v;
				pacman.cx1-=pacman.v;
				pacman.cx2-=pacman.v;
			}
			break;
		case 3:
			if(ColSwitch(pacman.d) && (casilla[pacman.casillaF-1][pacman.casillaC].tipo==1 || casilla[pacman.casillaF-1][pacman.casillaC].tipo==4)){
				
			}else{
				pacman.y-=pacman.v;
				pacman.cy1-=pacman.v;
				pacman.cy2-=pacman.v;
			}
			break;
		case 4:
			if(ColSwitch(pacman.d) && (casilla[pacman.casillaF+1][pacman.casillaC].tipo==1 || casilla[pacman.casillaF+1][pacman.casillaC].tipo==4)){
				
			}else{
				pacman.y+=pacman.v;
				pacman.cy1+=pacman.v;
				pacman.cy2+=pacman.v;
			}
		
			break;
	}
}
 

void FantasmasMov(){
	for(int i=0;i<4;i++){
		switch (fantasma[i].d){
		
			case 1:
				if(ColSwitchFantasma(i,fantasma[i].d) && casilla[fantasma[i].casillaF][fantasma[i].casillaC+1].tipo==1){
					fantasma[i].stuck=true;		
				}else{
				
				fantasma[i].x+=fantasma[i].v;
				fantasma[i].cx1+=fantasma[i].v;
				fantasma[i].cx2+=fantasma[i].v;
			}
			break;
		case 2:
			if(ColSwitchFantasma(i,fantasma[i].d) && casilla[fantasma[i].casillaF][fantasma[i].casillaC-1].tipo==1){
				fantasma[i].stuck=true;	
			}else{
				fantasma[i].x-=fantasma[i].v;
				fantasma[i].cx1-=fantasma[i].v;
				fantasma[i].cx2-=fantasma[i].v;
			}
			break;
		case 3:
			if(ColSwitchFantasma(i,fantasma[i].d) && casilla[fantasma[i].casillaF-1][fantasma[i].casillaC].tipo==1){
				fantasma[i].stuck=true;	
			}else{
				fantasma[i].y-=fantasma[i].v;
				fantasma[i].cy1-=fantasma[i].v;
				fantasma[i].cy2-=fantasma[i].v;
			}
			break;
		case 4:
			if(ColSwitchFantasma(i,fantasma[i].d) && casilla[fantasma[i].casillaF+1][fantasma[i].casillaC].tipo==1){
				fantasma[i].stuck=true;	
			}else{
				fantasma[i].y+=fantasma[i].v;
				fantasma[i].cy1+=fantasma[i].v;
				fantasma[i].cy2+=fantasma[i].v;
			}
		
			break;
		}
	}
}

void FantasmasDir(){
	for(int i=0;i<4;i++){
		if(rand()%1000<50 || fantasma[i].stuck){
			if( fantasma[i].cx1==casilla[fantasma[i].casillaF][fantasma[i].casillaC].ax && fantasma[i].cy1==casilla[fantasma[i].casillaF][fantasma[i].casillaC].ay){
 			
 			bool Update=false;

 			do{
 				int aux=fantasma[i].d;
				fantasma[i].d=rand()%4+1;	
				
					switch (fantasma[i].d){
		
					case 1:
						if(casilla[fantasma[i].casillaF][fantasma[i].casillaC+1].tipo!=1)
							Update=true;		
						break;
					case 2:
						if(casilla[fantasma[i].casillaF][fantasma[i].casillaC-1].tipo!=1)
							Update=true;
						break;
					case 3:
						if(casilla[fantasma[i].casillaF-1][fantasma[i].casillaC].tipo!=1)
							Update=true;
						break;
					case 4:
						if(casilla[fantasma[i].casillaF+1][fantasma[i].casillaC].tipo!=1)
							Update=true;
						break;
					}
				if(aux==fantasma[i].d)
					Update=false;	
		}while(Update==false);

	}
}
	fantasma[i].stuck=false;
}
}

void PacManDots(){

		switch (pacman.d){
		
		case 1:
			if(ColSwitch(pacman.d,12) && (casilla[pacman.casillaF][pacman.casillaC+1].tipo==2 || casilla[pacman.casillaF][pacman.casillaC+1].tipo==3))
					casilla[pacman.casillaF][pacman.casillaC+1].tipo=0;
			break;
		case 2:
			if(ColSwitch(pacman.d,12) && (casilla[pacman.casillaF][pacman.casillaC-1].tipo==2 || casilla[pacman.casillaF][pacman.casillaC-1].tipo==3))
					casilla[pacman.casillaF][pacman.casillaC-1].tipo=0;
			
			break;
		case 3:
			if(ColSwitch(pacman.d,12) && (casilla[pacman.casillaF-1][pacman.casillaC].tipo==2 || casilla[pacman.casillaF-1][pacman.casillaC].tipo==3))
					casilla[pacman.casillaF-1][pacman.casillaC].tipo=0;
			break;
		case 4:
			if(ColSwitch(pacman.d,12) && (casilla[pacman.casillaF+1][pacman.casillaC].tipo==2 || casilla[pacman.casillaF+1][pacman.casillaC].tipo==3))
					casilla[pacman.casillaF+1][pacman.casillaC].tipo=0;
			}
}

void PacManAnim(){

		pacman.anim	=framesAnim%4;
		pacman.sprite=PacMan[AnimPacMan[pacman.d-1][pacman.anim]];


}

void AnimFantasmas(){

	for(int i=0;i<4;i++){
		fantasma[i].anim=framesAnim%2;
		fantasma[i].sprite=Fantasmas[i][fantasma[i].anim + (fantasma[i].d-1)*2];
	}	

}

void Anim(){
		if(frames%5 == 0){
			PacManAnim();
			AnimFantasmas();
			framesAnim++;	
		}
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

	DrawDots();
	esat::DrawSprite(pacman.sprite,pacman.x,pacman.y);
	

}

void DrawWalls(){
	for(int i=0;i<31;i++){
		for(int j=0;j<28;j++){
			if(casilla[i][j].tipo==1)
				esat::DrawLine(casilla[i][j].ax,casilla[i][j].ay,casilla[i][j].bx,casilla[i][j].by);
		}
	}
}



/*void ColMuros(){
	if(Col(pacman.cx1,pacman.cy1,))
}*/

int esat::main(int argc, char **argv) {
 
  double current_time,last_time;
  unsigned char fps=60;

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
  InitFantasmas();
  InitPos();
  InitCasillas();
  
  for(int i=0;i<31;i++){
	for(int j=0;j<28;j++){
		printf("%d", casilla[i][j].tipo);		
	}
	printf("\n");
  }
  

  while(esat::WindowIsOpened() && !esat::IsSpecialKeyDown(esat::kSpecialKey_Escape)) {
	last_time = esat::Time();
	
	esat::DrawBegin();
    esat::DrawClear(0,0,0);
	
	Anim();
    PacManInput();
	UpdatePacManCasilla();
	UpdateFantasmasCasilla();
	PacManMov();
	FantasmasDir();	
	FantasmasMov();	

	ColPacManFantasmas();

	esat::DrawSprite(Mapa,0,0);
	esat::DrawSetStrokeColor(255,255,255);
	DrawMatriz();
	MuestraPacMan();
	MostrarFantasmas();
	DrawPacManCol();
	PacManDots();


	DrawWalls();

	printf("(%d,%d)\n",pacman.cx1,pacman.cy1);
	
    



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

    frames++;

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
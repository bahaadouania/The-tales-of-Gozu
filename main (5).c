#include "SDL/SDL_image.h"
#include <stdio.h>
#include <stdlib.h>
#include "SDL/SDL.h"
#include <SDL/SDL_mixer.h>
#include <SDL/SDL_ttf.h>
#include "fonction.h"


int main(void)
{

SDL_Surface *screen = NULL;
SDL_Surface *image = NULL;
SDL_Surface *texte = NULL ;
SDL_Surface *play1 = NULL;
SDL_Surface *play2 = NULL;
SDL_Surface *settings1 = NULL;
SDL_Surface *settings2 = NULL;
SDL_Surface *exit1 = NULL;
SDL_Surface *exit2 = NULL;
SDL_Surface *background2 = NULL;
SDL_Surface *loading = NULL;
SDL_Surface *barre = NULL;
SDL_Surface *mute = NULL ;
SDL_Surface *bird=NULL;
TTF_Font *police = NULL;
TTF_Font *police1 =NULL;
//background b;
int b1 = 0,b2 = 0,b3=0,m=0,p=0,b=0,curframe=0,maxframe=4,num=0,i=0;
float v=64;
int etat =0;
// variable texte 
char text[256]="birdspritesheet.png";
SDL_Color couleurNoire = {0,0,0};
SDL_Rect posframe,frame,positionecran,positionbarre,positiontxt,positionplay,positionsettings,positionexit;
char ch[256];
// audio 
if(Mix_OpenAudio(44100,MIX_DEFAULT_FORMAT,MIX_DEFAULT_CHANNELS,1024)==-1)
{printf("%s",Mix_GetError());}
Mix_VolumeMusic(v);
Mix_Music *music;
music= Mix_LoadMUS("naruto.mp3");
Mix_PlayMusic(music,-1);
Mix_AllocateChannels(2);
Mix_Volume(0,MIX_MAX_VOLUME );
Mix_Chunk *son;
son= Mix_LoadWAV("son.wav");


TTF_Init();
police= TTF_OpenFont("angelina.TTF",42);
texte=TTF_RenderText_Blended(police,"commencer la partie",couleurNoire);
play1=IMG_Load("play1.png");
play2=IMG_Load("play2.png");
settings1=IMG_Load("settings1.png");
settings2=IMG_Load("settings2.png");
exit1=IMG_Load("exit1.png");
exit2=IMG_Load("exit2.png");
background2=IMG_Load("background2.png");
barre=IMG_Load("barre.png");
mute=IMG_Load("mute.png");
loading=IMG_Load("loading.png");
bird= IMG_Load(text);


// inisialitation erreur 
if (SDL_Init(SDL_INIT_VIDEO)!=0)
{
printf("unable to set Initialize SDL : %s/n",SDL_GetError());
return 1;
}
// largeur , hauteur , resolution         
screen = SDL_SetVideoMode(700,394,32,SDL_HWSURFACE | SDL_DOUBLEBUF);

if (screen==NULL)
{
printf("unable to set  video mode : %s/n",SDL_GetError());
return 1;
}
image=IMG_Load("background.png");

if (image==NULL)
{
printf("unable to load  bitmap : %s/n",SDL_GetError());
return 1;
}
// inisialitation position
positionplay.x=519;
positionplay.y=130;
positionsettings.x=519;
positionsettings.y=190;
positionexit.x=519;
positionexit.y=250;
positiontxt.x=50;
positiontxt.y=280;
positionbarre.x=350;
positionbarre.y=301;
// position oiseau (frame)
frame.x=0;
frame.y=0;
frame.w=128;
frame.h=130;
posframe.x=0;
posframe.y=0;
// transparence ( qualite image )
SDL_FillRect(screen,NULL,SDL_MapRGB(screen->format,255,255,0));
int done = 1 ;
SDL_Event event;

while(done)
 {

if(etat==0)
{
SDL_BlitSurface(image,NULL,screen,&positionecran);
SDL_BlitSurface(bird,&frame,screen,&posframe);
curframe+=1;
if (curframe > maxframe)
curframe=0;
frame.x= curframe * frame.w;
posframe.x+=5;
if (posframe.x>700)
posframe.x=0;


if((b1==0)&&(b!=1))

{SDL_BlitSurface(play1,NULL,screen,&positionplay);



}
else
// boutton yecheel w taamel son bref
{Mix_PlayChannel(0,son,0);
SDL_BlitSurface(play2,NULL,screen,&positionplay);




SDL_BlitSurface(texte,NULL,screen,&positiontxt);


}
if((b2==0)&&(b!=2))
{
SDL_BlitSurface(settings1,NULL,screen,&positionsettings);


}
else
{Mix_PlayChannel(0,son,0);
SDL_BlitSurface(settings2,NULL,screen,&positionsettings);


}
if((b3==0)&&(b!=3))
{
SDL_BlitSurface(exit1,NULL,screen,&positionexit);


}
else
{Mix_PlayChannel(0,son,0);
SDL_BlitSurface(exit2,NULL,screen,&positionexit);


}


}
else if (etat==1)
// affichage taswira 
{SDL_BlitSurface(background2,NULL,screen,NULL);


 SDL_BlitSurface(barre,NULL,screen,&positionbarre);

 
if ( m==1)
SDL_BlitSurface(mute,NULL,screen,NULL);


}
else if(etat==2)
{
 SDL_BlitSurface(loading,NULL,screen,NULL);
}
SDL_Flip(screen);



SDL_PollEvent(&event);
 switch(event.type)
{case SDL_QUIT:
done=0;
break;
case SDL_KEYDOWN:
if ((event.key.keysym.sym == SDLK_DOWN)&&(b<3)&&(etat==0))
{b++;
SDL_Delay(150);}//rafraichissement ken matkhalihech ybeugi en millisec
if ((event.key.keysym.sym == SDLK_UP)&&(b>1)&&(etat==0))
{b--;
SDL_Delay(150);}
if(event.key.keysym.sym == SDLK_RETURN)
{if (b==1)
etat =2;
else if (b==2)
etat=1;
else done=0;
}

break;
case SDL_MOUSEBUTTONUP:
if (event.button.button == SDL_BUTTON_LEFT)
// nazlet souris axe
{ 
// nzelt exit 
if((event.button.x > 519)&&(event.button.x <  616)&&(event.button.y > 250)&&(event.button.y <   293)&&(etat==0))
{done=0;}
// nzelt setting
if((event.button.x > 519)&&(event.button.x < 616)&&(event.button.y > 190)&&(event.button.y < 233)&&(etat==0))
{  etat=1;       }
// nzelt play 
if ((event.button.x > 519)&&(event.button.x < 616)&&(event.button.y > 130)&&(event.button.y < 173)&&(etat==0))
etat=2;

}
break;
case SDL_MOUSEBUTTONDOWN :
if (event.button.button == SDL_BUTTON_LEFT)
{
// pos settings nzelt tkawi volume
if((event.button.x > 510) && (event.button.x < 550) && (event.button.y > 308 ) &&(event.button.y < 350) && (v < 128)  && (etat==1) && (positionbarre.x<483))
// augmentation
{m=0;
v+=12.8;
positionbarre.x+=27;
Mix_VolumeMusic(v);
SDL_Delay(150);}
// diminution
if((event.button.x > 150) && (event.button.x < 190) && (event.button.y > 308 ) &&(event.button.y < 350) && ( v >=12.8) && (etat==1) && (positionbarre.x >= 217))

{v-=12.8;
positionbarre.x-=27;
Mix_VolumeMusic(v);
SDL_Delay(150);
}
// mute 
if((event.button.x > 620) && (event.button.x < 665) && (event.button.y > 308 ) &&(event.button.y < 350) && ( v >=0) && (etat==1) )
{if(m==0)
{v=0;
Mix_VolumeMusic(v);
positionbarre.x=217;
m=1;}
else
{v=64;
Mix_VolumeMusic(v);
positionbarre.x=350;
m=0;

}
}
// boutton return
if((event.button.x > 25) && (event.button.x < 90) && (event.button.y > 20 ) &&(event.button.y < 89) &&(etat==1))
etat=0;


// plein ecran
if((event.button.x > 550) && (event.button.x < 610) && (event.button.y > 169 ) &&(event.button.y < 229) && (etat==1)&&(p==0))
{screen = SDL_SetVideoMode(700,394,32,SDL_HWSURFACE | SDL_DOUBLEBUF | SDL_FULLSCREEN);
p=1;}
else if((event.button.x > 550) && (event.button.x < 610) && (event.button.y > 169 ) &&(event.button.y < 229) && (etat==1)&&(p==1))
{ screen = SDL_SetVideoMode(700,394,32,SDL_HWSURFACE | SDL_DOUBLEBUF );
p=0;}


}
break;
case SDL_MOUSEMOTION :
// taa lmenu lowel mtaa souris
if ((event.motion.x > 519)&&(event.motion.x < 616)&&(event.motion.y > 130)&&(event.motion.y < 173))
b1=1;
else
b1=0;


if((event.motion.x > 519)&&(event.motion.x < 616)&&(event.motion.y > 190)&&(event.motion.y < 233))
b2=2;
else
b2=0;
if((event.motion.x > 519)&&(event.motion.x < 616)&&(event.motion.y > 250)&&(event.motion.y < 293))
b3=3;
else
b3=0;

break;


}

}
for (i=0;i<12;i++)
SDL_FreeSurface(loading);
SDL_FreeSurface(background2);
SDL_FreeSurface(exit2);
SDL_FreeSurface(exit1);
SDL_FreeSurface(settings1);
SDL_FreeSurface(settings2);
SDL_FreeSurface(play2);
SDL_FreeSurface(play1);
SDL_FreeSurface(barre);
SDL_FreeSurface(image);
SDL_FreeSurface(mute);
Mix_FreeMusic(music);
TTF_CloseFont(police);
SDL_FreeSurface(texte);

return 0;
}

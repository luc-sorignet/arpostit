#include "Menu.h"

Menu::Menu(){
    menu=1;
    network.loadImage("img/network.png");
    network_dis.loadImage("img/network_dis.png");
    camera.loadImage("img/camera.png");
    camera_dis.loadImage("img/camera_dis.png");
    postit.loadImage("img/postit.png");
    postit_dis.loadImage("img/postit_dis.png");
}
 int Menu::getMenu(){
    return menu;
 }
  void Menu::draw(){
  switch(menu){
  case 0:
      /* NETWORK */
      ofSetHexColor(0xffffff);
      network.draw(0,0);
      camera_dis.draw(0,164);
      postit_dis.draw(0,337);
      break;
  case 1:
       /* CAMERA */
      ofSetHexColor(0xffffff);
      network_dis.draw(0,0);
      camera.draw(0,164);
      postit_dis.draw(0,337);
      break;
  case 2:
       /* POSTIT */
      ofSetHexColor(0xffffff);
      network_dis.draw(0,0);
      camera_dis.draw(0,164);
      postit.draw(0,337);
       break;

  }


  }
void Menu::mouseAction(int x, int y ){
   if(x>=0&&x<=40){
            if(y>=0&&y<=163){
                    menu=0;

            }else if(y>=164&&y<=336){
                    menu=1;

            }else if(y>=337&&y<=520){
                    menu=2;
            }
   }

}
Menu::~Menu(){}

using namespace std;
#include "input.hpp"
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "texture_packs/textures.dat"
#include <unistd.h>
#include "source/rooms.dat"
#include "updateLog.dat"
#include "graphics_s.hpp"
#include <SDL2/SDL.h>
#include <cmath>

#define WINDOW_WIDTH 1080
#define WINDOW_HEIGHT 600

//                 Y,X
int bossSpawn[] = {0,0};
int effect[3] = {0,0,0};
float Health = 40.00;
void applyEffects (void) {
  if (effect[0] == 1) {
    if (effect[1] < 1) {
      effect[0] = 0;
    }
    else {
      Health = Health + effect[2];
      effect[1] = effect[1] - 1;
    }
  }
}
int veiwRange = 7;
int itemGetIndex = 1;
int minDamage = 1;
int maxDamage = 3;
char tempInput1 = 0;
int itemSelected = 0;
int inventorySlot = 1;
int inventoryList[] = {2,0,0,0,0,0,0,0,0};
int inventoryIndex = (0);
void showInventory() {
  system("clear");
  inventoryIndex = (0);
  while (inventoryIndex < 9) {
    printf("\n");
    if (inventoryIndex == itemSelected) {
      printf("•");
    }
    else {
      printf(" ");
    }
    if (inventoryList[inventoryIndex] == 0) {
      //0 code
    }
    if (inventoryList[inventoryIndex] == 1) {
      printf("Gp");
    }
    if (inventoryList[inventoryIndex] == 2) {
      printf("Charm of Sight");
    }
    if (inventoryList[inventoryIndex] == 3) {
      printf("Apple");
    }
    inventoryIndex = (inventoryIndex + 1);
  }
  tempInput1 = getch();
  if (tempInput1 == 27) {
    return;
  }
  if (tempInput1 == 113) {
    if (inventoryList[itemSelected] != 0) {
      inventoryList[itemSelected] = 0;
    }
  }
  if (tempInput1 == 'z') {
    if (inventoryList[itemSelected] == 3) {
      int effect[3] = {1,3,1};
      inventoryList[itemSelected] = 0;
    }
  }
  else {
    itemSelected = tempInput1 - 49;
    showInventory();
  }
  
}

int rand_num = 0;
void generate_random(int l, int r, int count) {
   int i;
   for (i = 0; i < count; i++) {
      rand_num = (rand() % (r - l + 1)) + l;
      
   }
}
//26 pc
//3 watch

int mapSize = 26;

float map[150][300] = {};

float mapPlan[15][15] = {
  {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
  {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
  {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
  {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
  {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
  {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
  {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
  {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
  {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
  {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
  {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
  {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
  {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
  {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
  {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0}
};


int mapUnitMax = 15;
int countX = (0);
int countY = (0);
int playerX = (110);
int playerY = (55);
int index2 = 0;
int mapUnitX = 3;
int mapUnitY = 3;

int level = 0;

void genMap() {
  int mapPlanIndex = 0;
  usleep(100);
  int randMapDir = 0;
  int mapGenPos[] = {0,0};

  while (mapGenPos[1] < 15) {
    mapGenPos[0] = 0;
    while (mapGenPos[0] < 15) {
      generate_random(1,23,1);
      if (rand_num == 0) {
        generate_random(1,23,1);
      }
      if (rand_num == 3) {
        generate_random(0,level,1);
        if (rand_num == 0) {
          generate_random(1,23,1);
        }
        else{
          rand_num = 3;
        }
      }
      if (rand_num == 4) {
        generate_random(0,level,1);
        if (rand_num == 0) {
          generate_random(1,23,1);
        }
        else{
          rand_num = 4;
        }
      }
      if (rand_num == 10) {
        generate_random(0,level,1);
        if (rand_num == 0) {
          generate_random(1,23,1);
        }
        else{
          rand_num = 10;
        }
      }

      if (rand_num == 12) {
        generate_random(1,23,1);
        if (rand_num == 12) {
          mapPlan[mapGenPos[0] - 1][mapGenPos[1] - 1] = 12.25;
          mapPlan[mapGenPos[0] - 1][mapGenPos[1]] = 12.5;
          mapPlan[mapGenPos[0]][mapGenPos[1] - 1] = 12.75;
        }
      }

      if (rand_num == 15) {
        rand_num = 1;
      }
      if (rand_num == 16) {
        rand_num = 1;
      }
      if (rand_num == 17) {
        rand_num = 1;
      }
      
      mapPlan[mapGenPos[0]][mapGenPos[1]] = rand_num;
      mapGenPos[0] = mapGenPos[0] + 1;
    }
    mapGenPos[1] = mapGenPos[1] + 1;
  } 
  mapPlan[0][0] = 0;
  mapPlan[1][0] = 0;
  mapPlan[2][0] = 0;
  mapPlan[3][0] = 0;
  mapPlan[4][0] = 0;
  mapPlan[5][0] = 0;
  mapPlan[6][0] = 0;
  mapPlan[7][0] = 0;
  mapPlan[8][0] = 0;
  mapPlan[9][0] = 0;
  mapPlan[10][0] = 0;
  mapPlan[11][0] = 0;
  mapPlan[12][0] = 0;
  mapPlan[13][0] = 0;
  mapPlan[14][0] = 0;
  mapPlan[0][14] = 0;
  mapPlan[1][14] = 0;
  mapPlan[2][14] = 0;
  mapPlan[3][14] = 0;
  mapPlan[4][14] = 0;
  mapPlan[5][14] = 0;
  mapPlan[6][14] = 0;
  mapPlan[7][14] = 0;
  mapPlan[8][14] = 0;
  mapPlan[9][14] = 0;
  mapPlan[10][14] = 0;
  mapPlan[11][14] = 0;
  mapPlan[12][14] = 0;
  mapPlan[13][14] = 0;
  mapPlan[14][14] = 0;
  mapPlan[0][1] = 0;
  mapPlan[0][2] = 0;
  mapPlan[0][3] = 0;
  mapPlan[0][4] = 0;
  mapPlan[0][5] = 0;
  mapPlan[0][6] = 0;
  mapPlan[0][7] = 0;
  mapPlan[0][8] = 0;
  mapPlan[0][9] = 0;
  mapPlan[0][10] = 0;
  mapPlan[0][11] = 0;
  mapPlan[0][12] = 0;
  mapPlan[0][13] = 0;
  mapPlan[0][14] = 0;
  mapPlan[0][0] = 0;
  mapPlan[14][1] = 0;
  mapPlan[14][2] = 0;
  mapPlan[14][3] = 0;
  mapPlan[14][4] = 0;
  mapPlan[14][5] = 0;
  mapPlan[14][6] = 0;
  mapPlan[14][7] = 0;
  mapPlan[14][8] = 0;
  mapPlan[14][9] = 0;
  mapPlan[14][10] = 0;
  mapPlan[14][11] = 0;
  mapPlan[14][12] = 0;
  mapPlan[14][13] = 0;
  mapPlan[14][14] = 0;
  mapPlan[14][0] = 0;
  mapPlan[5][5] = 1;
  generate_random(2,12,1);
  int tempRandY = rand_num;
  generate_random(2,12,1);
  mapPlan[tempRandY][rand_num] = -1;
  mapPlan[tempRandY][rand_num - 1] = 15;
  mapPlan[tempRandY][rand_num + 1] = 16;
  mapPlan[tempRandY - 1][rand_num + 1] = 12;
  mapPlan[tempRandY - 1][rand_num - 1] = 12.75;
  mapPlan[tempRandY - 2][rand_num - 1] = 12.25;
  mapPlan[tempRandY - 2][rand_num + 1] = 12.5;
  mapPlan[tempRandY - 1][rand_num] = -2;
  mapPlan[tempRandY - 2][rand_num] = -3;
  return;
}

int distance(float x1,float y1,float x2,float y2) {
  int Xdist = abs(x1 - x2);
  int Ydist = abs(y1 - y2);
  int dist = abs((Ydist / 2) + (Xdist / 2));
  return dist;
}

int playerTouch(int pTItem) {
  int pTouching = map[playerY - 1][playerX];
  if(pTouching == pTItem) {
    return 1;
  }
  else {
    pTouching = map[playerY + 1][playerX];
    if(pTouching == pTItem) {
      return 2;
    }
    else {
      pTouching = map[playerY][playerX - 1];
      if(pTouching == pTItem) {
        return 3;
      }
      else {
        pTouching = map[playerY][playerX + 1];
        if(pTouching == pTItem) {
          return 4;
        }
        else {
          pTouching = 0;
          return 0;
        }
      }
    }
  }
}

#include "source/boss.dat"

void generateMap() {
  countX = 0;
  countY = 0;
  mapUnitX = 0;
  mapUnitY = 0;
  while (mapUnitY < mapUnitMax) {
    mapUnitX = 0;
    while (mapUnitX < mapUnitMax) {
      countY = 0;
      //pre room gen code {

      //}
      generate_random(1,4,1);
      while (countY < 10) {
        countX = 0;
        while (countX < 20) {
          //pre tile placement code {
            
          //}
          if (mapPlan[mapUnitY][mapUnitX] == 1) {
            map[countY + (mapUnitY * 10)][countX + (mapUnitX  * 20)] = room1[countY][countX];
          }
          if (mapPlan[mapUnitY][mapUnitX] == 2) {
            map[countY + (mapUnitY * 10)][countX + (mapUnitX  * 20)] = room2[countY][countX];
          }
          if (mapPlan[mapUnitY][mapUnitX] == 0) {
            map[countY + (mapUnitY * 10)][countX + (mapUnitX  * 20)] = room0[countY][countX];
          }
          if (mapPlan[mapUnitY][mapUnitX] == 3) {
            map[countY + (mapUnitY * 10)][countX + (mapUnitX  * 20)] = room3[countY][countX];
          }
          if (mapPlan[mapUnitY][mapUnitX] == 4) {
            if (rand_num == 1) {
              map[countY + (mapUnitY * 10)][countX + (mapUnitX  * 20)] = room4a[countY][countX];
            }
            if (rand_num == 2) {
              map[countY + (mapUnitY * 10)][countX + (mapUnitX  * 20)] = room4b[countY][countX];
            }
            if (rand_num == 3) {
              map[countY + (mapUnitY * 10)][countX + (mapUnitX  * 20)] = room4c[countY][countX];
            }
            if (rand_num == 4) {
              map[countY + (mapUnitY * 10)][countX + (mapUnitX  * 20)] = room4d[countY][countX];
            }
          }
          if (mapPlan[mapUnitY][mapUnitX] == 5) {
            map[countY + (mapUnitY * 10)][countX + (mapUnitX  * 20)] = room5[countY][countX];
          }
          if (mapPlan[mapUnitY][mapUnitX] == 6) {
            map[countY + (mapUnitY * 10)][countX + (mapUnitX  * 20)] = room6[countY][countX];
          }
          if (mapPlan[mapUnitY][mapUnitX] == 7) {
            map[countY + (mapUnitY * 10)][countX + (mapUnitX  * 20)] = room7[countY][countX];
          }
          if (mapPlan[mapUnitY][mapUnitX] == 8) {
            map[countY + (mapUnitY * 10)][countX + (mapUnitX  * 20)] = room8[countY][countX];
          }
          if (mapPlan[mapUnitY][mapUnitX] == 9) {
            map[countY + (mapUnitY * 10)][countX + (mapUnitX  * 20)] = room9[countY][countX];
          }
          if (mapPlan[mapUnitY][mapUnitX] == 10) {
            if (rand_num == 1) {
              map[countY + (mapUnitY * 10)][countX + (mapUnitX  * 20)] = room10a[countY][countX];
            }
            if (rand_num == 2) {
              map[countY + (mapUnitY * 10)][countX + (mapUnitX  * 20)] = room10b[countY][countX];
            }
            if (rand_num == 3) {
              map[countY + (mapUnitY * 10)][countX + (mapUnitX  * 20)] = room10c[countY][countX];
            }
            if (rand_num == 4) {
              map[countY + (mapUnitY * 10)][countX + (mapUnitX  * 20)] = room10d[countY][countX];
            }
          }
          if (mapPlan[mapUnitY][mapUnitX] == 11) {
            map[countY + (mapUnitY * 10)][countX + (mapUnitX  * 20)] = room11[countY][countX];
          }
          if (mapPlan[mapUnitY][mapUnitX] == 12) {
            map[countY + (mapUnitY * 10)][countX + (mapUnitX  * 20)] = room12c[countY][countX];
          }
          if (mapPlan[mapUnitY][mapUnitX] == 12.25) {
            map[countY + (mapUnitY * 10)][countX + (mapUnitX  * 20)] = room12a[countY][countX];
          }
          if (mapPlan[mapUnitY][mapUnitX] == 12.5) {
            map[countY + (mapUnitY * 10)][countX + (mapUnitX  * 20)] = room12b[countY][countX];
          }
          if (mapPlan[mapUnitY][mapUnitX] == 12.75) {
            map[countY + (mapUnitY * 10)][countX + (mapUnitX  * 20)] = room12d[countY][countX];
          }
          if (mapPlan[mapUnitY][mapUnitX] == 13) {
            map[countY + (mapUnitY * 10)][countX + (mapUnitX  * 20)] = room13[countY][countX];
          }
          if (mapPlan[mapUnitY][mapUnitX] == 14) {
            if(rand_num == 1) {
              map[countY + (mapUnitY * 10)][countX + (mapUnitX  * 20)] = room14a[countY][countX];
            }
            if(rand_num == 2) {
              map[countY + (mapUnitY * 10)][countX + (mapUnitX  * 20)] = room14b[countY][countX];
            }
            if(rand_num == 3) {
              map[countY + (mapUnitY * 10)][countX + (mapUnitX  * 20)] = room14c[countY][countX];
            }
            if(rand_num == 4) {
              map[countY + (mapUnitY * 10)][countX + (mapUnitX  * 20)] = room14d[countY][countX];
            }
          }
          if (mapPlan[mapUnitY][mapUnitX] == 15) {
            map[countY + (mapUnitY * 10)][countX + (mapUnitX  * 20)] = room15[countY][countX];
          }
          if (mapPlan[mapUnitY][mapUnitX] == 16) {
            map[countY + (mapUnitY * 10)][countX + (mapUnitX  * 20)] = room16[countY][countX];
          }
          if (mapPlan[mapUnitY][mapUnitX] == 17) {
            map[countY + (mapUnitY * 10)][countX + (mapUnitX  * 20)] = room17[countY][countX];
          }
          if (mapPlan[mapUnitY][mapUnitX] == 18) {
            map[countY + (mapUnitY * 10)][countX + (mapUnitX  * 20)] = room18[countY][countX];
          }
          if (mapPlan[mapUnitY][mapUnitX] == 19) {
            map[countY + (mapUnitY * 10)][countX + (mapUnitX  * 20)] = room19[countY][countX];
          }
          if (mapPlan[mapUnitY][mapUnitX] == 20) {
            map[countY + (mapUnitY * 10)][countX + (mapUnitX  * 20)] = room20[countY][countX];
          }
          if (mapPlan[mapUnitY][mapUnitX] == 21) {
            map[countY + (mapUnitY * 10)][countX + (mapUnitX  * 20)] = room21[countY][countX];
          }
          if (mapPlan[mapUnitY][mapUnitX] == -1) {
            map[countY + (mapUnitY * 10)][countX + (mapUnitX  * 20)] = roomExit[countY][countX];
            bossSpawn[0] = (mapUnitY * 10) - 10;
            bossSpawn[1] = 10 + (mapUnitX  * 20);
            createBoss(1,bossSpawn[0],bossSpawn[1]);
          }
          if (mapPlan[mapUnitY][mapUnitX] == -2) {
            map[countY + (mapUnitY * 10)][countX + (mapUnitX  * 20)] = room12f[countY][countX];
          }
          if (mapPlan[mapUnitY][mapUnitX] == -3) {
            map[countY + (mapUnitY * 10)][countX + (mapUnitX  * 20)] = room12e[countY][countX];
          }
          if (mapPlan[mapUnitY][mapUnitX] == 22) {
            map[countY + (mapUnitY * 10)][countX + (mapUnitX  * 20)] = room22[countY][countX];
          }
          if (mapPlan[mapUnitY][mapUnitX] == 23) {
            map[countY + (mapUnitY * 10)][countX + (mapUnitX  * 20)] = room23[countY][countX];
          }
          countX = countX + 1;
        }
        countY = countY + 1;
      }

      mapUnitX = mapUnitX + 1;
    }
    mapUnitY = mapUnitY + 1;
  }
  return;
}
char startK;

#include "source/enemy.dat"

void type_text(char *s, float ms_delay)
{
   float usecs = ms_delay * 1000; /* 1000 microseconds per ms */

   for (; *s; s++) {
      putchar(*s);
      fflush(stdout); /* alternatively, do once: setbuf(stdout, NULL); */
      usleep(usecs);
   }
}

int barCount = 0;

void displayPlayerStats() {
  barCount = 0;
  printf("[");
  while (barCount < (Health)) {
    printf("|");
    barCount = barCount + 1;
  }
  barCount = 0;
  while (barCount < (40 - Health)) {
    printf("");
    barCount = barCount + 1;
  }
  printf("]");
}

void playerUpdate() {
  map[playerY][playerX] = (0);
}
int tempRand = 0;

struct vector {
  float x;
  float y;
};
vector vector2d(float x, float y){
  vector v;
  v.x = x;
  v.y = y;
}

vector get_movement(float v, float d) {
  vector m = vector2d(sin(d)*v,cos(d)*v);
  return m;
}

void loadMap(SDL_Renderer *renderer){
	//SDL_SetRenderDrawColor(renderer, 10, 10, 10, 255);
    //SDL_RenderClear(renderer);
    for (int y = 0; y < 16; ++y) {
        for (int x = 0; x < 32; ++x) {
			int render_tile = map[(playerY - 8) + y][(playerX - 16) + x];
			switch( render_tile ) {
				case 0:
          draw_model(floor1,floor1,x*32,y*32,renderer);
					break;
				case 1:
					draw_model(player,player,x*32,y*32,renderer);
					break;
				case 2:
					draw_model(wall,wall,x*32,y*32,renderer);
					break;
				case 3:
					draw_model(enemy,enemy,x*32,y*32,renderer);
					break;
				case 4:
					if(map[(playerY - 8) + y][(playerX - 16) + x + 1] == 7){
						draw_model(glory_door,glory_door,x*32,y*32,renderer);
					}
					else {
						draw_model(arcane_door,arcane_door,x*32,y*32,renderer);
					}
					break;
				case 6:
					draw_model(fence,fence,x*32,y*32,renderer);
					break;
				case 7:
					draw_model(glory_wall,glory_wall,x*32,y*32,renderer);
					break;
				case 8:
					draw_model(wall,wall,x*32,y*32,renderer);
					break;
				case 9:
					draw_model(chest,chest,x*32,y*32,renderer);
					break;
				case 10:
					draw_model(gp,gp,x*32,y*32,renderer);
					break;
				case 11:
					draw_model(hard_fence,hard_fence,x*32,y*32,renderer);
					break;
				case 12:
					draw_model(arcane_tile,arcane_tile,x*32,y*32,renderer);
					break;
				default:
					draw_model(ph,ph,x*32,y*32,renderer);
			}
        }
    }
    SDL_RenderPresent(renderer);
}

void nextFloor(SDL_Renderer *renderer) {
  level = level + 1;
  createRats();
  char levelChar = char(level);
  std::cout << (char(level + 48));
  printf("\n");
  genMap();
  generateMap();
  playerX = (110);
  playerY = (55);
  sleep(1);
  loadMap(renderer);
}

int loop(SDL_Renderer *renderer) {
  applyEffects();
  index2 = 0;
  map[playerY][playerX] = (1);

  renderRats();
  renderBoss();

  if (inventoryList[0] == 2) {
    veiwRange = 26; 
  }
  else {
    veiwRange = 7;
  }

  loadMap(renderer);
  char key;
  SDL_Event keyevent;
    bool keyPress = false;
    while(!keyPress){
    while (SDL_PollEvent(&keyevent))
    {
	   if(keyevent.type == SDL_KEYDOWN)
	   {
            if(keyevent.key.keysym.sym == SDLK_a){
	              key = 'a';
                keyPress = true;
            }
            if(keyevent.key.keysym.sym == SDLK_d){
	              key = 'd';
                keyPress = true;
            }
            if(keyevent.key.keysym.sym == SDLK_w){
	              key = 'w';
                keyPress = true;
            }
            if(keyevent.key.keysym.sym == SDLK_s){
	              key = 's';
                keyPress = true;
            }
            if(keyevent.key.keysym.sym == SDLK_z){
	              key = 'z';
                keyPress = true;
            }
            if(keyevent.key.keysym.sym == SDLK_e){
	              key = 'e';
                keyPress = true;
            }
            if(keyevent.key.keysym.sym == SDLK_ESCAPE){
                key = 27;
                keyPress = true;
            }
	   }
	   else if(keyevent.type == SDL_QUIT){
      exit(0);
	   }
    }
  }
  if(key == 27){
    //none
  }
  if (key == 'w') {
    playerUpdate();
    if ((map[playerY - 1][playerX]) == (0)) {
      playerY = playerY - 1;   
    }
    if ((map[playerY - 1][playerX]) == (4)) {
      playerY = playerY - 1;
    }
    if ((map[playerY - 1][playerX]) == (8)) {
      playerY = playerY - 1;
    }
    if ((map[playerY - 1][playerX]) == (9)) {
      map[playerY - 1][playerX] = (10);
    }
  }
  
  if (key == 's') {
    playerUpdate();
    if ((map[playerY + 1][playerX]) == (0)) {
      playerY = playerY + 1;   
    }
    if ((map[playerY + 1][playerX]) == (4)) {
      playerY = playerY + 1;
    }
    if ((map[playerY + 1][playerX]) == (8)) {
      playerY = playerY + 1;
    }
  }

    if (key == 'a') {
      playerUpdate();
      if ((map[playerY][playerX - 1]) == (0)) {
        playerX = playerX - 1;   
      }
      if ((map[playerY][playerX - 1]) == (4)) {
        playerX = playerX - 1;
      }
      if ((map[playerY][playerX - 1]) == (8)) {
        playerX = playerX - 1;
      }
    }

    if (key == 'd') {
      playerUpdate();
      if ((map[playerY][playerX + 1]) == (0)) {
        playerX = playerX + 1;   
      }
      if ((map[playerY][playerX + 1]) == (4)) {
        playerX = playerX + 1;
      }
      if ((map[playerY][playerX + 1]) == (8)) {
        playerX = playerX + 1;
      }
    }
    if (key == 'e') {
      showInventory();
    }

    if (key == 'z') {
      generate_random(minDamage,maxDamage,1);
      damageCloseRat(rand_num);
      damageCloseBoss(rand_num);
      if ((playerTouch(10)) == (1)) {
        map[playerY - 1][playerX] = (0);
        inventoryList[itemGetIndex] = 1;
        itemGetIndex = itemGetIndex + 1;
      }
      if ((playerTouch(10)) == (2)) {
        map[playerY + 1][playerX] = (0);
        inventoryList[itemGetIndex] = 1;
        itemGetIndex = itemGetIndex + 1;
      }
      if ((playerTouch(10)) == (3)) {
        map[playerY][playerX - 1] = (0);
        inventoryList[itemGetIndex] = 1;
        itemGetIndex = itemGetIndex + 1;
      }
      if ((playerTouch(10)) == (4)) {
        map[playerY][playerX + 1] = (0);
        inventoryList[itemGetIndex] = 1;
        itemGetIndex = itemGetIndex + 1;
      }
      if ((playerTouch(9)) == (1)) {
        generate_random(1,2,1);
        if(rand_num == 1) {
          map[playerY - 1][playerX] = (10);
        }
        else {
          map[playerY - 1][playerX] = (16);
        }
      }
      if ((playerTouch(9)) == (2)) {
        generate_random(1,2,1);
        if(rand_num == 1) {
          map[playerY + 1][playerX] = (10);
        }
        else {
          map[playerY + 1][playerX] = (16);
        }
      }
      if ((playerTouch(9)) == (3)) {
        generate_random(1,2,1);
        if(rand_num == 1) {
          map[playerY][playerX - 1] = (10);
        }
        else {
          map[playerY][playerX - 1] = (16);
        }
      }
      if ((playerTouch(9)) == (4)) {
        generate_random(1,2,1);
        if(rand_num == 1) {
          map[playerY][playerX + 1] = (10);
        }
        else {
          map[playerY][playerX + 1] = (16);
        }
      }
      if ((playerTouch(4)) == (1)) {
        if (bossHP < 1) {
          nextFloor(renderer);
        }
      }
      if ((playerTouch(4)) == (2)) {
        if (bossHP < 1) {
          nextFloor(renderer);
        }
      }
      if ((playerTouch(4)) == (3)) {
        if (bossHP < 1) {
          nextFloor(renderer);
        }
      }
      if ((playerTouch(4)) == (4)) {
        if (bossHP < 1) {
          nextFloor(renderer);
        }
      }
      if ((playerTouch(16)) == (1)) {
        map[playerY - 1][playerX] = (0);
        inventoryList[itemGetIndex] = 3;
        itemGetIndex = itemGetIndex + 1;
      }
      if ((playerTouch(16)) == (2)) {
        map[playerY + 1][playerX] = (0);
        inventoryList[itemGetIndex] = 3;
        itemGetIndex = itemGetIndex + 1;
      }
      if ((playerTouch(16)) == (3)) {
        map[playerY][playerX - 1] = (0);
        inventoryList[itemGetIndex] = 3;
        itemGetIndex = itemGetIndex + 1;
      }
      if ((playerTouch(16)) == (4)) {
        map[playerY][playerX + 1] = (0);
        inventoryList[itemGetIndex] = 3;
        itemGetIndex = itemGetIndex + 1;
      }
    }
  if (Health <= 0) {
    system("clear");
    printf("Y O U   D I E D . . .");
    printf("\nPress enter to restart\n");
    scanf("%c", &startK);
    level = 0;
    Health = 40.0;
    srand ( time(NULL) );
    genMap();
    generateMap();
    createRats();
    system("clear"); 
    nextFloor(renderer);
  }
  else {
  }
  return 0;
  
}

int main(void){
  SDL_Renderer *renderer;
  SDL_Window *window;
  SDL_Init(SDL_INIT_VIDEO);
  SDL_CreateWindowAndRenderer(WINDOW_WIDTH, WINDOW_HEIGHT, 0, &window, &renderer);
  SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
  SDL_RenderClear(renderer);
  SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
      SDL_RenderPresent(renderer);
  SDL_SetWindowTitle(window,"Dungeon Game");
  SDL_Surface *icon = SDL_LoadBMP("icon.bmp");
  SDL_SetWindowIcon(window, icon);
  mapSize = 26;
  srand ( time(NULL) );
  genMap();
  generateMap();
  createRats();
  int mainCount = 0;
  nextFloor(renderer);
  bool exit_1 = true;
  while(exit_1){
    loop(renderer);
    SDL_Event exit_event;
    while(SDL_PollEvent(&exit_event)){
		exit_1 = !(exit_event.type == SDL_QUIT);
		if(!exit_1){
			break;
		}
	}
  }
}

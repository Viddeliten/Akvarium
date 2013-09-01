#define S_W 1024
#define S_H 600
#define DEPTH 3

#define ANT_JORD 20
#define ANT_PLANT s_w/10
#define ANT_PL_EATER 5
#define ANT_EATER ANT_PL_EATER
#define ANT_ASEATER 5

#define SIGHT 10
#define ACCX fdx
#define ACCY fdy
#define HACCX (SIGHT)/fdx
#define HACCY (SIGHT)/fdy

#define SOL_E 30 //65
#define STILL_E 5
#define MOVE_E 10

#define POO ENERGY_TO_MAKE_PLANT*50 //*50 //Hur mycket bajs man har innan man gör ifrån sig
#define POO_PERCENT 15

#define PLANT_DIVIDER 400 // 400

#define MIN_WEIGHT 500 //Hur mycket man måste väga för att få ta energi från sin vikt
#define MIN_WEIGHT_A MIN_WEIGHT/10 //Hur mycket man måste väga för att få ta energi från sin vikt

#define MAX_AGE_H s_w*10
#define MAX_AGE_C MAX_AGE_H
#define MAX_AGE_A s_h*3
#define MAX_AGE_EGG_A 500 //2000
#define MAX_AGE_EGG_H 2000 //2000

#define START_WEIGHT s_w+rand()%s_w
#define START_ENERGY s_w*MOVE_E+rand()%s_w*MOVE_E
#define START_ENERGY_PLANT START_ENERGY*2
#define START_ENERGY_H START_ENERGY
#define START_ENERGY_AS START_ENERGY*3

#define ENERGY_LOSS 1

#define PLANT_COST PLANT_DIVIDER/2 //400

#define ENERGY_TO_MAKE_H 200000 //455000 //Hur mycket energi som krävs för att saken ska bli "rastlös"
#define ENERGY_TO_MAKE_C ENERGY_TO_MAKE_H //Hur mycket energi som krävs för att saken ska bli "rastlös"
#define ENERGY_TO_MAKE_A 100000 //Hur mycket energi som krävs för att saken ska bli "rastlös"
#define ENERGY_TO_MAKE_PLANT SOL_E*170 //134
#define ENERGY_TO_MAKE_ROOT ENERGY_TO_MAKE_PLANT
#define MIN_ENERGY ENERGY_TO_MAKE_PLANT //Hur mycket energi en växt måste ha för att inte suga från omgivningen
#define WEIGHT_TO_ENERGY 3/ENERGY_LOSS

extern PALETTE pal;
extern BITMAP *bmp;
extern int s_w, s_h;
extern float wind;

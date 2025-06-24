#include "iGraphics.h"
#include "iSound.h"
#include <iostream>
using namespace std;
/*
function iDraw() is called again and again by the system.
*/
int ch=-1;
int click;
int screenCount = 0,screen=1;
int volume = 1;
int music_vol = 0, musicPlaying=-1;
int width = 500, height = 650;
int ball_radius = 10;
int ball_diameter = 2*ball_radius;
int name_taken = 0;

typedef struct{
    int red,green,blue;
    int exist;
    int x,y;
}staticBall;

//number of static balls = 500 / (10 * 2) * 3(rows);
staticBall all_static_balls[31][25];


void draw_a_static_ball(staticBall aBall){


    iSetColor(aBall.red,aBall.green,aBall.blue);
    iFilledCircle(aBall.x,aBall.y,ball_radius);
}

void draw_all_static_ball()
{
    for(int i=0; i<30; i++){

        for(int j=0;j<25;j++){
            if(all_static_balls[i][j].exist)
                draw_a_static_ball(all_static_balls[i][j]);
        }
    }
}
//-------ball er co ordinate draw a static ball e thakbe-----------
staticBall emptyBall;
void set_coordinates(){
    for(int i = 0;i<31;i++){
        for(int j=0;j<25;j++){

            all_static_balls[i][j].x = (2*j+1)*ball_radius;
            all_static_balls[i][j].y = height - (2*i+1)*ball_radius;

        }
    }
}
void set_static_ball(int red,int green,int blue,int i,int j){
    all_static_balls[i][j].exist = 1;
    all_static_balls[i][j].red = red;
    all_static_balls[i][j].green = green;
    all_static_balls[i][j].blue = blue;
    all_static_balls[i][j].x = (2*j+1)*ball_radius;
    all_static_balls[i][j].y = height - (2*i+1)*ball_radius;
}

void fillwithballs(){

    for(int i=0;i<5;i++){
        int c = 0;
        for(int j =0;j<25;j++){
            staticBall tempBall;
            tempBall.exist =1;
            switch(c%3){
                case 0:tempBall.red =255;tempBall.blue =0;tempBall.green =0;break;
                case 1:tempBall.green =255;tempBall.red =0;tempBall.blue =0;break;
                case 2:tempBall.blue =255;tempBall.red =0;tempBall.green =0;break;
            }
            all_static_balls[i][j] = tempBall;
            c++;
        }
    }

    for(int i = 5;i<31;i++){
        for(int j=0;j<25;j++){
            all_static_balls[i][j] = emptyBall;
        }
    }
    set_coordinates();
    set_static_ball(255,255,255,20,20);
}
//void loweringstaticball(){ball.x;ball.y++} --------time mode er gameplay er jonno-----------

void noballs()
{
    for(int i = 0;i<30;i++){
        for(int j=0;j<25;j++){
            all_static_balls[i][j] = emptyBall;
        }
    }
}
void drawAxis()
{
    iSetColor(255, 255, 255);
    iLine(0, 50, width, 50);
}


double angle = 0;


double ball_x = 250;
double ball_y = 50;
int throw_ball = 0;
double dx;
double dy;
double velocity = 3;
int color_counter = 0;
int r = 255;
int g = 0;
int b = 0;
void setBall()
{
    throw_ball = 1;
    dx = velocity*sin(angle * 3.1416/180);
    dy = velocity*cos(angle * 3.1416/180);
}

void resetBall()
{
    throw_ball = 0;
    ball_x = 250;
    ball_y = 50;
    color_counter++;
    switch(color_counter%3){
        case 1: r = 0; g = 255; b = 0;break;
        case 2: r = 0; g = 0; b = 255;break;
        case 0: r = 255; g = 0; b = 0;break;
    }
}


void drawCannon() //---------------------working alright-------------------------------
{
    double cannon_x = 30*sin(angle * 3.1416/180);
    double cannon_y = 30*cos(angle * 3.1416/180);
    iSetLineWidth(2);
    iSetColor(255,255,255);
    iLine(250-10,50,250+cannon_x-10,50+cannon_y);
    iLine(250+10,50,250+cannon_x+10,50+cannon_y);
    iSetLineWidth(1);
    iSetColor(r,g,b);
    iLine(250,50,250+5*cannon_x,50+5*cannon_y);
    if(throw_ball==0){
        iSetColor(r,g,b);
        iFilledCircle(250,40, ball_radius);
    }
}
int combo = 0;
void check_neighbour(int i,int j){
    combo++;
    all_static_balls[i][j].exist=0;
    if (i!=0 && all_static_balls[i-1][j].exist){
        if (r==all_static_balls[i-1][j].red && g==all_static_balls[i-1][j].green && b==all_static_balls[i-1][j].blue){
        check_neighbour(i-1,j);
        }
    }
    if (all_static_balls[i+1][j].exist){
        if (r==all_static_balls[i+1][j].red && g==all_static_balls[i+1][j].green && b==all_static_balls[i+1][j].blue){
        check_neighbour(i+1,j);
        }
    }
    if (j!=0 && all_static_balls[i][j-1].exist){
        if (r==all_static_balls[i][j-1].red && g==all_static_balls[i][j-1].green && b==all_static_balls[i][j-1].blue){
        check_neighbour(i,j-1);
        }
    }
    if (j!=24 && all_static_balls[i][j+1].exist){
        if (r==all_static_balls[i][j+1].red && g==all_static_balls[i][j+1].green && b==all_static_balls[i][j+1].blue){
        check_neighbour(i,j+1);
        }
    }
}

void check_collision(int i, int j){
    int startchecking = 0;
    if (all_static_balls[i][j].exist){
        if(all_static_balls[i+1][j].exist==0){
            i = i+1;
            j = j;
        }
        else if(dx>0){
            if(all_static_balls[i][j-1].exist==0){
                i = i;
                j = j-1;
            }
            else{
                i = i+1;
                j = j-1;
            }

        }
        else if(dx<0){
            if(all_static_balls[i][j-1].exist==0){
                i = i;
                j = j+1;
            }
            else{
                i = i+1;
                j = j-1;
            }
        }
        startchecking = 1;
    }
    if(ball_y + ball_radius > height) startchecking = 1;
    //checking around i,j
    if(startchecking){
    if (i!=0 && all_static_balls[i-1][j].exist){
        if (r==all_static_balls[i-1][j].red && g==all_static_balls[i-1][j].green && b==all_static_balls[i-1][j].blue){
        combo++;
        check_neighbour(i-1,j);
        all_static_balls[i-1][j].exist=1;
        }
    }
    if (i!=29 && all_static_balls[i+1][j].exist){
        if (r==all_static_balls[i+1][j].red && g==all_static_balls[i+1][j].green && b==all_static_balls[i+1][j].blue){
        combo++;
        check_neighbour(i+1,j);
        all_static_balls[i+1][j].exist=1;
        }
    }
    if (j!=0 && all_static_balls[i][j-1].exist){
        if (r==all_static_balls[i][j-1].red && g==all_static_balls[i][j-1].green && b==all_static_balls[i][j-1].blue){
        combo++;
        check_neighbour(i,j-1);
        all_static_balls[i][j-1].exist=1;
        }
    }
    if (j!=24 && all_static_balls[i][j+1].exist){
        if (r==all_static_balls[i][j+1].red && g==all_static_balls[i][j+1].green && b==all_static_balls[i][j+1].blue){
        combo++;
        check_neighbour(i,j+1);
        all_static_balls[i][j+1].exist=1;
        }
    }

    if(combo<=2){
        all_static_balls[i][j].exist=1;
        all_static_balls[i][j].red=r;
        all_static_balls[i][j].green=g;
        all_static_balls[i][j].blue=b;
    }
    else{
        if (all_static_balls[i-1][j].exist){
            if (r==all_static_balls[i-1][j].red && g==all_static_balls[i-1][j].green && b==all_static_balls[i-1][j].blue){
                all_static_balls[i-1][j].exist=0;
            }
        }
        if (all_static_balls[i+1][j].exist){
            if (r==all_static_balls[i+1][j].red && g==all_static_balls[i+1][j].green && b==all_static_balls[i+1][j].blue){
                all_static_balls[i+1][j].exist=0;

            }
        }
        if (j!=0 && all_static_balls[i][j-1].exist){
            if (r==all_static_balls[i][j-1].red && g==all_static_balls[i][j-1].green && b==all_static_balls[i][j-1].blue){
                all_static_balls[i][j-1].exist=0;
            }
        }
        if (j!=24 && all_static_balls[i][j+1].exist){
            if (r==all_static_balls[i][j+1].red && g==all_static_balls[i][j+1].green && b==all_static_balls[i][j+1].blue){
                all_static_balls[i][j+1].exist=0;
            }
        }
    }
    resetBall();
    }


}

void drawBall()
{

    iSetColor(r,g,b);
    iFilledCircle(ball_x,ball_y, ball_radius);

    if(ball_x - ball_radius<0 || ball_x + ball_radius > width)
        dx = -dx;

        ball_x+=dx;
        ball_y+=dy;
    /*if(ball_y - ball_radius<0){
        resetBall();
    }*/

}
//----------------------game over function --------------------------------------
void gameover(){
    for(int j = 0;j<25;j++){
        if(all_static_balls[30][j].exist){
            exit(0);
        }
    }
}

void curv(int x, int y, int w, int h, int r){
        iFilledRectangle(x + r, y, w - 2*r, h); 
        iFilledRectangle(x, y + r, r, h - 2*r); 
        iFilledRectangle(x + w - r, y + r, r, h - 2*r); 
        iFilledCircle(x + r, y + r, r); 
        iFilledCircle(x + w - r, y + r, r); 
        iFilledCircle(x + r, y + h - r, r); 
        iFilledCircle(x + w - r, y + h - r, r); 
}
void curv_border(int x, int y, int w, int h, int r){
        iRectangle(x + r-.3, y-.3, w - 2*r+.6, h+.6); 
        iRectangle(x-.3, y + r-.3, r+.6, h - 2*r+.6); 
        iRectangle(x + w - r-.3, y + r-.3, r+.6, h - 2*r+.6); 
        iFilledCircle(x + r, y + r, r+.3); 
        iFilledCircle(x + w - r, y + r, r+.3); 
        iFilledCircle(x + r, y + h - r, r+.3); 
        iFilledCircle(x + w - r, y + h - r, r+.3); 
}
void iDraw()
{
    // place your drawing codes here
    if(screenCount == 0)
    {
        iClear();
        iSetColor(147, 213, 230); 
        iFilledRectangle(0, 0, 500, 650); 
        iShowImage(-50, -30, "assets/images/bg_0.png"); 
        iSetColor(42, 54, 53);
        iTextBold(185, 428, "Play  Game", GLUT_BITMAP_TIMES_ROMAN_24);
        iSetColor(42, 54, 53);
        iTextBold(185, 358, "High-scores", GLUT_BITMAP_TIMES_ROMAN_24); 
        iSetColor(42, 54, 53);
        iTextBold(206, 290, "Settings", GLUT_BITMAP_TIMES_ROMAN_24); 
        iSetColor(42, 54, 53);
        iTextBold(220, 218, "Exit", GLUT_BITMAP_TIMES_ROMAN_24); 
        iSetColor(232, 167, 160);
        iFilledCircle(25, 25, 17);
        iSetColor(255, 0, 0);
        iFilledCircle(25, 25, 15);
        iSetColor(0,0,0);
        iTextBold(20,17,"?", GLUT_BITMAP_TIMES_ROMAN_24); 
        int x2=420, y2=10, w2=70, h2=20, r2=10;
        iSetColor(232, 167, 160);
        curv_border(x2, y2, w2, h2, r2); 
        iSetColor(24, 66, 35);
        curv(x2, y2, w2, h2, r2);
        iSetColor(255, 255, 255);
        iTextBold(429, 15, "About Us", GLUT_BITMAP_HELVETICA_12);
    }
    else if(screenCount == 1)
    {
        // Code for the second screen, new game screen
        iClear();
        
        if(screen == 1)
        {
														iShowImage(-100, -80, "assets/images/new_game_1.jpeg");
            iSetColor(77, 34, 29);
            iFilledCircle(396, 460, 16);
            iSetColor(255, 0, 0);
            iFilledCircle(396, 460, 15);
            iSetColor(255, 255, 255);
            iTextBold(390, 455, "X", GLUT_BITMAP_HELVETICA_18);
            iSetColor(255, 255, 255);
        }
        else if(screen == 2)
        {
            /*-------------for debug purpose---------------
            char details[100];
            int j = ball_x / ball_diameter;
            int i = (height - ball_y) / ball_diameter;
            sprintf(details, "%lf %lf %i %i",ball_x,ball_y,i,j);
            iText(200, 200, details);*/
            int j = ball_x / ball_diameter;
            int i = (height - ball_y) / ball_diameter;
    
            iSetLineWidth(3);
            drawAxis();
        
            draw_all_static_ball();
            drawCannon();
            check_collision(i,j);
        
            gameover();
    
            if(throw_ball)
                drawBall();
        
            char cmb[12];
            sprintf(cmb,"COMBO: %i",(combo>=2)?combo:0);
            iSetColor(255,255,255);
            iText(200, 300, "Hello World");
            iText(10, 25, cmb);
        }
    }
    else if(screenCount == 2)
    {
        // Code for the third screen,  high-score screen
    }
    else if(screenCount == 3)
    {
        // Code for the fourth screen,  settings screen
        iClear();
        iShowImage(-50, -30, "assets/images/bg_3.png");
        iSetColor(77, 34, 29);
        iFilledCircle(406, 435, 16);
        iSetColor(255, 0, 0);
        iFilledCircle(406, 435, 15);
        iSetColor(255, 255, 255);
        iTextBold(400, 429, "X", GLUT_BITMAP_HELVETICA_18); 
        iSetColor(55, 74, 66);
        curv_border(232, 357, 166, 40, 14);
        iSetColor(154, 204, 237);
        curv(232, 357, 166, 40, 14); 
        if(volume == 1){
            iSetColor(42, 54, 53);
            iTextBold(239, 370, "Low", GLUT_BITMAP_HELVETICA_18); 
            iSetColor(255, 255, 255);
            curv_border(288, 356, 55, 40, 13); 
            iSetColor(42, 54, 53);
            curv(288, 356, 55, 40, 13); 
            iSetColor(220, 247, 235);
            iTextBold(298, 370, "Mid", GLUT_BITMAP_HELVETICA_18);
            iSetColor(42, 54, 53);
            iTextBold(352, 370, "High", GLUT_BITMAP_HELVETICA_18); 
        }
        else if(volume == 0)
        {
            iSetColor(220, 247, 235);
            curv_border(232, 356, 55, 40, 13); 
            iSetColor(42, 54, 53);
            curv(232, 356, 55, 40, 13); 
            iSetColor(203, 242, 234);
            iTextBold(242, 370, "Low", GLUT_BITMAP_HELVETICA_18); 
            iSetColor(42, 54, 53);
            iTextBold(298, 370, "Mid", GLUT_BITMAP_HELVETICA_18); 
            iSetColor(42, 54, 53);
            iTextBold(352, 370, "High", GLUT_BITMAP_HELVETICA_18); 
        }
        else if(volume == 2)
        {
            iSetColor(42, 54, 53);
            iTextBold(239, 370, "Low", GLUT_BITMAP_HELVETICA_18); 
            iSetColor(42, 54, 53);
            iTextBold(298, 370, "Mid", GLUT_BITMAP_HELVETICA_18); 
            iSetColor(220, 247, 235);
            curv_border(344, 356, 55, 40, 13);
            iSetColor(42, 54, 53);
            curv(344, 356, 55, 40, 13); 
            iSetColor(203, 242, 234);
            iTextBold(355, 370, "High", GLUT_BITMAP_HELVETICA_18); 
        }        
        iSetColor(55, 74, 66);
        curv_border(232, 285, 168, 40, 13); 
        iSetColor(154, 204, 237);
        curv(232, 285, 168, 40, 13); 

        if(music_vol==0)
        {          
            iSetColor(42, 54, 53);
            iTextBold(260, 299, "On", GLUT_BITMAP_HELVETICA_18); 
            iSetColor(220, 247, 235);
            curv_border(314, 285, 84, 40, 13); // 
            iSetColor(42, 54, 53);
            curv(314, 285, 84, 40, 13); // 
            iSetColor(203, 242, 234);
            iTextBold(339, 299, "Off", GLUT_BITMAP_HELVETICA_18); 
            // PlaySound(0,0,0); 
        }
        else if(music_vol==1)
        {
            iSetColor(220, 247, 235);
            curv_border(232, 285, 84, 40, 13); 
            iSetColor(42, 54, 53);
            curv(232, 285, 84, 40, 13); 
            iSetColor(203, 242, 234);
            iTextBold(260, 299, "On", GLUT_BITMAP_HELVETICA_18); 
            iSetColor(42, 54, 53);
            iTextBold(339, 299, "Off", GLUT_BITMAP_HELVETICA_18); 
        }
    }
    else if(screenCount == 4)
    {
        // Code for the fifth screen,  exit confirmation screen
        iClear();
        iShowImage(-50, -30, "assets/images/bg_4.png");
        iSetColor(147, 213, 230);
        iFilledCircle(404, 400, 19);
        iSetColor(255, 0, 0);
        iFilledCircle(404, 400, 17.5);
        iSetColor(255, 255, 255);
        iTextBold(398, 395.2, "X", GLUT_BITMAP_HELVETICA_18);
    }
    else if(screenCount == 5)
    {
        // Code for the sixth screen,  game over screen
    }
    else if(screenCount == 6)
    {
        // Code for the seventh screen,  victory screen
    }
    else if(screenCount == 7)
    {
        // Code for the eighth screen,  help screen
        iClear();
        iShowImage(-50, -30, "assets/images/bg_7.png");
        iSetTransparentColor(147, 213, 230, 0.5);
        iFilledRectangle(0, 0, 500, 650); 
        iSetColor(204, 163, 131);
        curv_border(30, 205, 433, 281, 10); 
        iSetColor(168, 108, 77);
        curv(30, 205, 433, 281, 10); 
        iSetColor(77, 34, 29);
        iFilledCircle(460, 484, 16); 
        iSetColor(255, 0, 0);
        iFilledCircle(460, 484, 15);
        iSetColor(255, 255, 255);
        iTextBold(453.8, 478, "X", GLUT_BITMAP_HELVETICA_18);
        iSetColor(157, 177, 224);
        curv_border(41, 219.5, 412, 201, 10);
        iSetColor(23, 35, 64);
        curv(41, 219.5, 412, 201, 10); 
        iSetColor(157, 177, 224);
        iFilledEllipse(235, 449, 100, 20); 
        iSetColor(23, 35, 64);
        iFilledEllipse(234, 450, 100, 20); 
        iSetColor(255, 255, 255);
        iText(170, 442, "How To Play", GLUT_BITMAP_TIMES_ROMAN_24);       
        iText(50, 399.3, "1. Click on 'New Game' to start a new game.", GLUT_BITMAP_HELVETICA_18);
        iText(50, 369.3, "2. Click on 'Load Game' to load a saved game.", GLUT_BITMAP_HELVETICA_18);
        iText(50, 339.3, "3. Click on 'Settings' to change game settings.", GLUT_BITMAP_HELVETICA_18);
        iText(50, 309.3, "4. Click on 'Exit' to close the game.", GLUT_BITMAP_HELVETICA_18);
        iText(50, 279.3, "5. Click on '?' for help or instructions.", GLUT_BITMAP_HELVETICA_18);
        iText(50, 249.3, "6. Click on 'About Us' to know about the", GLUT_BITMAP_HELVETICA_18);
        iText(50, 223.9, "    game developers.", GLUT_BITMAP_HELVETICA_18);
    }
    else if(screenCount==8){
        iClear();
        iShowImage(-50, -30, "assets/images/bg_7.png");
        iSetTransparentColor(147, 213, 230, 0.5);
        iFilledRectangle(0, 0, 500, 650); 
        iSetColor(32, 59, 97);
        curv_border(30, 185, 433, 321, 10);
        iSetColor(139, 190, 232);
        curv(30, 185, 433, 321, 10);
        iSetColor(77, 34, 29);
        iFilledCircle(460, 504, 16);
        iSetColor(255, 0, 0);
        iFilledCircle(460, 504, 15);
        iSetColor(255, 255, 255);
        iTextBold(453.8, 498, "X", GLUT_BITMAP_HELVETICA_18);
        iSetColor(245, 207, 169);
        curv_border(182, 490, 130, 40, 10);
        iSetColor(133, 98, 80);
        curv(182, 490, 130, 40, 10);
        iSetColor(230, 207, 195);
        iTextBold(200, 500, "About Us", GLUT_BITMAP_TIMES_ROMAN_24);
        iSetColor(39, 68, 87);
        iTextBold(50, 450, "Version 1.0.0", GLUT_BITMAP_HELVETICA_18);
        iTextBold(50, 420, "Developed by:", GLUT_BITMAP_HELVETICA_18);
        iTextBold(50, 380, "1. Siam Rafsan Prionto (BUET CSE-24)", GLUT_BITMAP_HELVETICA_18);
        iTextBold(50, 350, "2. Kazi FAhin Abraz (BUET CSE-24)", GLUT_BITMAP_HELVETICA_18);
        iTextBold(50, 310, "This is still a work in progress", GLUT_BITMAP_HELVETICA_18);
        iTextBold(50, 280, "and more features will be added over the years.", GLUT_BITMAP_HELVETICA_18);
        iTextBold(50, 240, "Thank you for trying it out!", GLUT_BITMAP_HELVETICA_18);
        iSetColor(255, 255, 255);
        iCircle(53, 206, 6);
        iSetColor(39, 68, 87);
        iTextBold(50, 203, "c", GLUT_BITMAP_HELVETICA_12); 
        iTextBold(62, 200, "Copyright to the owners", GLUT_BITMAP_HELVETICA_18);
    }
}

/*
function iMouseMove() is called when the user moves the mouse.
(mx, my) is the position where the mouse pointer is.
*/
void iMouseMove(int mx, int my)
{
    // place your codes here
}

/*
function iMouseDrag() is called when the user presses and drags the mouse.
(mx, my) is the position where the mouse pointer is.
*/
void iMouseDrag(int mx, int my)
{
    // place your codes here
}

/*
function iMouse() is called when the user presses/releases the mouse.
(mx, my) is the position where the mouse pointer is.
*/
void iMouse(int button, int state, int mx, int my)
{
    if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
    {
        // place your codes here
        cout<<mx<<my<<screenCount<<endl;
        
        if(screenCount==0)
        {
            if((mx-25)*(mx-25)+(my-25)*(my-25)<=289) 
            {
                screenCount = 7; 
            }
            else if(mx >= 155 && mx <= 333 && my >= 417 && my <= 457) 
            {
                screenCount = 1; 
            }
            else if(mx >= 155 && mx <= 333 && my >= 346 && my <= 391) 
            {
                screenCount = 2; 
            }
            else if(mx >= 155 && mx <= 333 && my >= 274 && my <= 318) 
            {
                screenCount = 3; 
            }
            else if(mx >= 155 && mx <= 333 && my >= 203 && my <= 251) 
            {
                screenCount = 4; 
            }
            else if(mx >= 420 && mx <= 490 && my >= 10 && my <= 30) 
            {
                screenCount = 8;
            }
        }
        else if(screenCount==1)
        {
            // Code for play game screen
            if(!name_taken)
            {
                if(screen=1){
                    if((mx-396)*(mx-396)+(my-460)*(my-460)<=256) 
                    {
                        screenCount = 0; 
                    }
                    else if(mx>=109 && mx<=245 && my>=276 && my<=304) 
                    {
                        screen=2;
                    }
                    else if(mx>=245 && mx<=381 && my>=276 && my<=304) 
                    {
                        screen=3; 
                    }
                }
            }
            
        }
        else if(screenCount==2)
        {
            // Code for high-score screen
        }
        else if(screenCount==5)
        {
            // Code for game over screen
        }
        else if(screenCount==6)
        {
            // Code for victory screen
        }
        else if(screenCount==4)
        {
            if((mx-404)*(mx-404)+(my-400)*(my-400)<=289) 
            {
                screenCount = 0; 
            }
            else if(mx >= 103 && mx <= 245 && my >= 206 && my <= 242) 
            {
                exit(0); 
            }
            else if(mx >= 257 && mx <= 391 && my >= 204 && my <= 242) 
            {
                screenCount = 0; 
            }
        }
        else if(screenCount==7) 
        {
            if((mx-460)*(mx-460)+(my-484)*(my-484)<=225) 
            {
                screenCount = 0; 
            }
        }
        else if (screenCount == 3) 
        {
            if ((mx - 406)*(mx - 406) + (my - 435)*(my - 435) <= 225)
            {
                screenCount = 0;
            }
            else if (mx >= 236 && mx <= 312 && my >= 290 && my <= 325)
            {
                music_vol = 1;
                if (ch == -1) {
                    ch = iPlaySound("assets/sounds/music_mid.wav", true, 50);
                    iSetVolume(ch, (volume == 0) ? 20 : (volume == 2) ? 70 : 40);
                }
                else {
                    iResumeSound(ch);
                }
            }
            else if (mx >= 313 && mx <= 400 && my >= 288 && my <= 331)
            {
                music_vol = 0;
                if (ch != -1) iPauseSound(ch);
            }
            else if (mx >= 232 && mx <= 287 && my >= 356 && my <= 396)
            {
                volume = 0;
                if (music_vol == 1 && ch != -1)
                    iSetVolume(ch, 20);
            }
            else if (mx >= 288 && mx <= 343 && my >= 356 && my <= 396)
            {
                volume = 1;
                if (music_vol == 1 && ch != -1)
                    iSetVolume(ch, 40);
            }
            else if (mx >= 346 && mx <= 401 && my >= 356 && my <= 396)
            {
                volume = 2;
                if (music_vol == 1 && ch != -1)
                    iSetVolume(ch, 70); 
            }
        }
        else if(screenCount == 8)
        {
            if((mx-460)*(mx-460)+(my-504)*(my-504)<=225) 
            {
                screenCount = 0; 
            }
        }
        if(mx>=0 && mx<=500 && my>=0 && my<=650)
        {
            iPlaySound("assets/sounds/click.wav", false, 50);
        }
    }
}

/*
function iMouseWheel() is called when the user scrolls the mouse wheel.
dir = 1 for up, -1 for down.
*/
void iMouseWheel(int dir, int mx, int my)
{
    // place your code here
}

/*
function iKeyboard() is called whenever the user hits a key in keyboard.
key- holds the ASCII value of the key pressed.
*/
void iKeyboard(unsigned char key)
{
    if(screenCount == 1){
    switch (key)
    {
    case 'q':
        // do something with 'q'
        screenCount=0;
        break;
    case 'a':
        if(angle>-80)
            angle-=2.5;
        break;
    case 'd':
        if(angle<80)
            angle+=2.5;
        break;
    case 'w':
        if(throw_ball==0)
            combo=0;
            setBall();
        break;
    case 'f':
        fillwithballs();
        break;
    case 'r':
        noballs();
        break;

    // place your codes for other keys here
    default:
        break;
    }
}
}

/*
function iSpecialKeyboard() is called whenver user hits special keys likefunction
keys, home, end, pg up, pg down, arraows etc. you have to use
appropriate constants to detect them. A list is:
GLUT_KEY_F1, GLUT_KEY_F2, GLUT_KEY_F3, GLUT_KEY_F4, GLUT_KEY_F5, GLUT_KEY_F6,
GLUT_KEY_F7, GLUT_KEY_F8, GLUT_KEY_F9, GLUT_KEY_F10, GLUT_KEY_F11,
GLUT_KEY_F12, GLUT_KEY_LEFT, GLUT_KEY_UP, GLUT_KEY_RIGHT, GLUT_KEY_DOWN,
GLUT_KEY_PAGE_UP, GLUT_KEY_PAGE_DOWN, GLUT_KEY_HOME, GLUT_KEY_END,
GLUT_KEY_INSERT */
void iSpecialKeyboard(unsigned char key)
{
    switch (key)
    {
    case GLUT_KEY_END:
        // do something
        break;
    // place your codes for other keys here
    default:
        break;
    }
}

int main(int argc, char *argv[])
{
    glutInit(&argc, argv);
    // place your own initialization codes here.
    iInitializeSound();

    iInitialize(500, 650, "Bouncy Bonanza");
    return 0;
}

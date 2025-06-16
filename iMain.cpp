#include "iGraphics.h"
#include <iostream>
using namespace std;
/*
function iDraw() is called again and again by the system.
*/
int screenCount = 0;
int volume = 1;
int music_vol = 0, musicPlaying=-1;

void curv(int x, int y, int w, int h, int r){
        iFilledRectangle(x + r, y, w - 2*r, h); // center body
        iFilledRectangle(x, y + r, r, h - 2*r); // left side
        iFilledRectangle(x + w - r, y + r, r, h - 2*r); // right side
        iFilledCircle(x + r, y + r, r); // bottom-left
        iFilledCircle(x + w - r, y + r, r); // bottom-right
        iFilledCircle(x + r, y + h - r, r); // top-left
        iFilledCircle(x + w - r, y + h - r, r); // top-right
}
void curv_border(int x, int y, int w, int h, int r){
        iRectangle(x + r-.3, y-.3, w - 2*r+.6, h+.6); // center body
        iRectangle(x-.3, y + r-.3, r+.6, h - 2*r+.6); // left side
        iRectangle(x + w - r-.3, y + r-.3, r+.6, h - 2*r+.6); // right side
        iFilledCircle(x + r, y + r, r+.3); // bottom-left
        iFilledCircle(x + w - r, y + r, r+.3); // bottom-right
        iFilledCircle(x + r, y + h - r, r+.3); // top-left
        iFilledCircle(x + w - r, y + h - r, r+.3); // top-right
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
    iTextBold(185, 428, "New  Game", GLUT_BITMAP_TIMES_ROMAN_24);
    iSetColor(42, 54, 53);
    iTextBold(185, 358, "High-scores", GLUT_BITMAP_TIMES_ROMAN_24); // Second button text
    iSetColor(42, 54, 53);
    iTextBold(206, 290, "Settings", GLUT_BITMAP_TIMES_ROMAN_24); // Third button text
    iSetColor(42, 54, 53);
    iTextBold(220, 218, "Exit", GLUT_BITMAP_TIMES_ROMAN_24); // Fourth button text
    iSetColor(232, 167, 160);
    iFilledCircle(25, 25, 17);
    iSetColor(255, 0, 0);
    iFilledCircle(25, 25, 15);
    iSetColor(0,0,0);
    iTextBold(20,17,"?", GLUT_BITMAP_TIMES_ROMAN_24); // Center circle text
    int x2=420, y2=10, w2=70, h2=20, r2=10;
    iSetColor(232, 167, 160);
    curv_border(x2, y2, w2, h2, r2); 
    iSetColor(24, 66, 35);
    curv(x2, y2, w2, h2, r2);
    iSetColor(255, 255, 255);
    iTextBold(429, 15, "About Us", GLUT_BITMAP_HELVETICA_12); // Close button text
    }
    else if(screenCount == 1)
    {
        // Code for the second screen, e.g., game screen
    }
    else if(screenCount == 2)
    {
        // Code for the third screen, e.g., load game screen
    }
    else if(screenCount == 3)
    {
        // Code for the fourth screen, e.g., settings screen
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
            iTextBold(239, 370, "Low", GLUT_BITMAP_HELVETICA_18); // Volume button text
            iSetColor(255, 255, 255);
            curv_border(288, 356, 55, 40, 13); 
            iSetColor(42, 54, 53);
            curv(288, 356, 55, 40, 13); 
            iSetColor(220, 247, 235);
            iTextBold(298, 370, "Mid", GLUT_BITMAP_HELVETICA_18);
            iSetColor(42, 54, 53);
            iTextBold(352, 370, "High", GLUT_BITMAP_HELVETICA_18); // Volume button text
        }
        else if(volume == 0)
        {
            iSetColor(220, 247, 235);
            curv_border(232, 356, 55, 40, 13); 
            iSetColor(42, 54, 53);
            curv(232, 356, 55, 40, 13); 
            iSetColor(203, 242, 234);
            iTextBold(242, 370, "Low", GLUT_BITMAP_HELVETICA_18); // Volume button text
            iSetColor(42, 54, 53);
            iTextBold(298, 370, "Mid", GLUT_BITMAP_HELVETICA_18); // Volume button text
            iSetColor(42, 54, 53);
            iTextBold(352, 370, "High", GLUT_BITMAP_HELVETICA_18); // Volume button text
        }
        else if(volume == 2)
        {
            iSetColor(42, 54, 53);
            iTextBold(239, 370, "Low", GLUT_BITMAP_HELVETICA_18); // Volume button text
            iSetColor(42, 54, 53);
            iTextBold(298, 370, "Mid", GLUT_BITMAP_HELVETICA_18); // Volume button text
            iSetColor(220, 247, 235);
            curv_border(344, 356, 55, 40, 13);
            iSetColor(42, 54, 53);
            curv(344, 356, 55, 40, 13); // Volume button border
            iSetColor(203, 242, 234);
            iTextBold(355, 370, "High", GLUT_BITMAP_HELVETICA_18); // Volume button text
        }        
        iSetColor(55, 74, 66);
        curv_border(232, 285, 168, 40, 13); 
        iSetColor(154, 204, 237);
        curv(232, 285, 168, 40, 13); // 

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
        // Code for the fifth screen, e.g., exit confirmation screen
        iClear();
        iShowImage(-50, -30, "assets/images/bg_4.png");
        iSetColor(147, 213, 230);
        iFilledCircle(404, 400, 19);
        iSetColor(255, 0, 0);
        iFilledCircle(404, 400, 17.5);
        iSetColor(255, 255, 255);
        iTextBold(398, 395.2, "X", GLUT_BITMAP_HELVETICA_18); // Close button text
    }
    else if(screenCount == 5)
    {
        // Code for the sixth screen, e.g., game over screen
    }
    else if(screenCount == 6)
    {
        // Code for the seventh screen, e.g., victory screen
    }
    else if(screenCount == 7)
    {
        // Code for the eighth screen, e.g., help screen
        iClear();
        iShowImage(-50, -30, "assets/images/bg_7.png");
        iSetTransparentColor(147, 213, 230, 0.5);
        iFilledRectangle(0, 0, 500, 650); // Background
        iSetColor(204, 163, 131);
        curv_border(30, 205, 433, 281, 10); 
        iSetColor(168, 108, 77);
        curv(30, 205, 433, 281, 10); 
        iSetColor(77, 34, 29);
        iFilledCircle(460, 484, 16); // Center circle border
        iSetColor(255, 0, 0);
        iFilledCircle(460, 484, 15); // Center circle
        iSetColor(255, 255, 255);
        iTextBold(453.8, 478, "X", GLUT_BITMAP_HELVETICA_18); // Close button text
        iSetColor(157, 177, 224);
        curv_border(41, 219.5, 412, 201, 10);
        iSetColor(23, 35, 64);
        curv(41, 219.5, 412, 201, 10); // Help instructions box
        iSetColor(157, 177, 224);
        iFilledEllipse(235, 449, 100, 20); // Help icon background
        iSetColor(23, 35, 64);
        iFilledEllipse(234, 450, 100, 20); // Help icon
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
        iFilledRectangle(0, 0, 500, 650); // Background
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
                screenCount = 8; // About Us screen
            }
        }
        else if(screenCount==1)
        {
            // Code for the second screen, e.g., game screen
        }
        else if(screenCount==2)
        {
            // Code for the third screen, e.g., load game screen
        }
        else if(screenCount==5)
        {
            // Code for the sixth screen, e.g., game over screen
        }
        else if(screenCount==6)
        {
            // Code for the seventh screen, e.g., victory screen
        }
        else if(screenCount==4)
        {
            if((mx-404)*(mx-404)+(my-400)*(my-400)<=289) // Close button in exit confirmation screen
            {
                screenCount = 0; // Go back to main menu
            }
            else if(mx >= 103 && mx <= 245 && my >= 206 && my <= 242) // Yes button
            {
                exit(0); // Exit the game
            }
            else if(mx >= 257 && mx <= 391 && my >= 204 && my <= 242) // No button
            {
                screenCount = 0; // Go back to main menu
            }
        }
        else if(screenCount==7) // Help button
        {
            if((mx-460)*(mx-460)+(my-484)*(my-484)<=225) // Close button in help screen
            {
                screenCount = 0; // Go back to main menu
            }
        }
        else if(screenCount==3) 
        {
            if ((mx - 406) * (mx - 406) + (my - 435) * (my - 435) <= 225)
            {
                screenCount = 0;
            }
            else if (mx >= 236 && mx <= 312 && my >= 290 && my <= 325)
            {
                music_vol = 1;
                PlaySound(0, 0, 0);
                if (volume == 0)
                    PlaySound("assets/sounds/music_low.wav", NULL, SND_ASYNC | SND_LOOP);
                else if (volume == 1)
                    PlaySound("assets/sounds/music_mid.wav", NULL, SND_ASYNC | SND_LOOP);
                else if (volume == 2)
                    PlaySound("assets/sounds/music_high.wav", NULL, SND_ASYNC | SND_LOOP);

                musicPlaying = volume + 1;
            }
            else if (mx >= 313 && mx <= 400 && my >= 288 && my <= 331)
            {
                music_vol = 0;
                PlaySound(0, 0, 0);
                musicPlaying = 0;
            }
            else if (mx >= 232 && mx <= 287 && my >= 356 && my <= 396)
            {
                volume = 0;
                if (music_vol == 1)
                {
                    PlaySound(0, 0, 0);
                    PlaySound("assets/sounds/music_low.wav", NULL, SND_ASYNC | SND_LOOP);
                    musicPlaying = volume + 1;
                }
            }
            else if (mx >= 288 && mx <= 343 && my >= 356 && my <= 396)
            {
                volume = 1;
                if (music_vol == 1)
                {
                    PlaySound(0, 0, 0);
                    PlaySound("assets/sounds/music_mid.wav", NULL, SND_ASYNC | SND_LOOP);
                    musicPlaying = volume + 1;
                }
            }
            else if (mx >= 346 && mx <= 401 && my >= 356 && my <= 396)
            {
                volume = 2;
                if (music_vol == 1)
                {
                    PlaySound(0, 0, 0);
                    PlaySound("assets/sounds/music_high.wav", NULL, SND_ASYNC | SND_LOOP);
                    musicPlaying = volume + 1;
                }
            }
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
    switch (key)
    {
    case 'q':
        // do something with 'q'
        break;
    // place your codes for other keys here
    default:
        break;
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
    iInitialize(500, 650, "Bouncy Bonanza");
    return 0;
}
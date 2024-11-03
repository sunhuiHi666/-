#include<stdio.h>
#include<windows.h>
#include<mmsystem.h>
#include<conio.h>
#pragma comment(lib,"winmm.lib")
// -------------------------------- 数   据   设   计    ---------------------------------------
/*
    棋盘:
        map[i][j]表示坐标(i,j)的值
        0表示空地
        1表示黑子
        2表示白子
    如: map[3][6] = 1  表示(3,6)的位置是黑子
*/
//用两个数组，一个记录真实棋盘，一个记录连成五子的坐标
int map[15][15];
int map3[15][15];
//mapColor表示地图颜色
//borderColor表示边框提示颜色
int mapColor = 4;
int borderColor = 4;
//flag表示当前回合数  偶数表示黑棋落子  奇数表示白棋落子
//如: flag = 20 表示当前是第[20]次落子  由黑方落子
int flag;
//sum1表示黑子胜利次数
//sum2表示白子胜利次数
int sum1;
int sum2;
//难度选择   简单 1   普通 2   困难 3
int count = 2;
int s = 0;
int f = 0;//开关音乐
//--------------------------------------- 数   据   设   计----------------------------------------
// 
// ---------------------------------------  s e r v i c e -----------------------------------------
/*
    负责人:坦诚
    功能:初始化游戏数据
        将棋盘的值初始化为0   map  map3
        当前回合设为黑棋(flag设为0)
         sum1,sum2 为0
        count默认难度
        mapColor默认地图颜色
        borderColor默认边框提示颜色
    参数: void
    返回值: void
*/
void init();

/*
负责人:大智
功能:
悔棋
输入r将上一颗下的棋子撤销
并给与上一回合玩家重新下子的机会
参数：x,y;
返回值: void
*/
void  regret();

/*
    *难点1
    负责人:坦诚
    功能: 根据传入的坐标(map对应位置)和flag值 判断落点后是否获胜（每次获胜或者是最后谁胜利）
    相应sum进行加一 消去连成的五子
    参数:
        x: 当前回合落子的x坐标
        y: 当前回合落子的y坐标
  
*/
void isWin(int x, int y);

/*
    负责人:我心飞翔
    功能:在指定位置落子
    消去符合条件的棋子
        如果map[x][y]是空地 则修改map[x][y]的值:改为相应颜色(flag对应颜色)
        否则不操作
    参数:
        x: 当前回合落子的x坐标
        y: 当前回合落子的y坐标
    返回值:
        0表示落子失败 (棋盘已经有子)
        1表示落子成功
*/
int playerMove(int x, int y);

/*
    负责人:坦诚
    功能：停止播放所有音乐
    参数: void
    返回值: void
*/
void stopMusic();
// ------------------------------------------- s e r v i c e --------------------------------------------



// --------------------------------------------- v i e w ------------------------------------------------
/*  负责人:坚持
    功能:游戏主菜单
    游戏名
    展示选项  根据wsad移动光标，回车选择
    开始游戏: 调用游戏界面函数gameView();
    游戏设置: 调用游戏设置界面函数game_settings();
    开发人员: 调用开发人员界面函数developer();
    玩法介绍: 调用玩法介绍界面函数playing_method();
    退出游戏: 调用exit(0);
    参数: void
    返回值: void
*/
void menuView();

/*
    负责人:坦诚/大智
    功能:游戏界面
    根据产品原型图 打印游戏棋盘
    参数: void
    返回值: void
*/
void gameView_ShowMap();

/*
    负责人:叶何
    功能:游戏设置
    展示选项 根据wsad移动光标，回车选择
    游戏内BGM:调用游戏音乐界面函数game_music();
    颜色选择:调用颜色选择界面函数
    返回:回到主菜单
    参数: void
    返回值: void
*/
void game_settings();

/*
    负责人:坦诚
    功能:根据产品原型图 打印出音乐选择界面
    根据wsad移动光标，回车选择
    根据选择更改游戏内音乐
    返回:返回游戏设置
    参数: void
    返回值: void
*/
void game_music();

/*
    负责人:叶何
    功能:根据产品原型图 打印出颜色选择界面
    根据wsad移动光标，回车选择
    地图颜色选择
    边框颜色选择
    返回:返回游戏设置
    参数: void
    返回值: void
*/
void game_color();

/*
  负责人:叶何
  功能：实现地图颜色选择
 switch 语句
    case 0:  红色
    case 1:  蓝色
    case 2:  绿色
    case 3:  黄色
    case 4:  白色
    参数: void
    返回值: void
*/
void setmapColor(int color);

/*
   负责人:叶何
   功能：实现边框颜色选择
    switch 语句
    case 0:  红色
    case 1:  紫色
    case 2:  绿色
    case 3:  黄色
    case 4:  白色
    参数: void
    返回值: void
*/
void setborderColor(int color);

/*
    负责人:兔子
    功能:开发人员
    根据产品原型图 打印开发人员界面
    根据回车选择
    返回:返回主菜单
    参数: void
    返回值: void
*/
void developer();

/*
    负责人:赫木
    功能:玩法介绍
    根据产品原型图 打印玩法介绍界面
    根据回车选择
    返回:返回主菜单
    参数: void
    返回值: void
*/
void playing_method();

/*
    负责人:AURORA
    功能：彩蛋
    输出彩蛋界面，可选择返回游戏
参数:void
返回值:void
*/
void SurpriseEgg(int x, int y);

/*
    负责人:乞骸骨
    功能: 打印结算界面  用户可以选择再来一局或回到主菜单
    再来一局:
    回到主菜单:
    退出游戏:
    参数: void
    返回值: void
*/
void winView();

/*
    *难点2
    负责人:YOOU/坦诚/大智
    功能: 游戏界面整合
        初始化游戏数据(调用函数init())
        while(1){
            打印游戏界面(调用函数gameView_ShowMap())
            接收玩家输入,坐标输入
            悔棋
            落子(调用落子函数playerMove())
                (如果落子失败 重新开始循环)

            判断游戏回合是否结束(调用胜利判断函数isWin())
           (如果游戏胜利并且没达到次数 调用初始化函数进行下一局，然后结束当前界面，相应sum进行加一)
            切换玩家(修改flag值)

           判断游戏是否结束（调用函数Win())
           （看sum1/sum2是否达到相应次数）
           跳转到结算界面
        }
    参数: void
    返回值: void
*/
void gameView(); 

/*
  负责人:大智
    功能: 悔棋后的重新落子
           map[x][y] = (flag % 2 == 0) ? 1 : 2;
           根据局合数判断落子数
     参数: int
    返回值: void
*/
void replayerMove(int x, int y);

/*
    负责人:叶何/坦诚
    int userChoose = 0;//0为简单，1为普通，2为困难
    system("cls")
    while (1) {
    三种难度：简单，普通，困难
    利用switch语句}
    参数: void
    返回值: void
*/
void DifficultyChoice();
// --------------------------------------------- v i e w ------------------------------------------------


// 传入坐标, 将光标移动到指定坐标
void gotoXY(int x, int y)
{
    COORD c;
    c.X = x - 1;
    c.Y = y - 1;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), c);
}

//固定区域清屏
void clear(int x, int y, int w, int h)
{
    for (int i = 0; i < h; i++) {
        gotoXY(x, y + i);
        for (int j = 0; j < w; j++) putchar(' ');
    }
}

//使用不同颜色
void setPrintColor(int color) {

    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);

}

//重置不同颜色
void resetPrintColor(int color) {

    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);

}



//游戏初始化
void init() {
    for (int i = 0; i < 15; i++) {
        for (int j = 0; j < 15; j++) {
            map[i][j] = 0;
            map3[i][j] = 0;

        }
    }
    flag = 0;
    sum1 = 0;
    sum2 = 0;
}

//菜单界面
void menuView() {
    
   
    int userChoose = 0;
    while (1)
    {
        if (f)
        {
            mciSendString("stop bgm0", NULL, 0, NULL);
        }
        //播放bgm
        else {
            mciSendString("open 卡农(经典钢琴版).mp3 alias bgm0", NULL, 0, NULL);
            mciSendString("play bgm0  repeat", NULL, 0, NULL);
            mciSendString("setaudio bgm0 volume to 200", NULL, 0, NULL);
        }
        setPrintColor(0x0f);
        gotoXY(52, 3);
        printf("五  子  消  消  乐");

        setPrintColor(userChoose == 0 ? 0x6f : 0x0f);
        gotoXY(57, 9);
        printf("开始游戏");

        setPrintColor(userChoose == 1 ? 0x6f : 0x0f);
        gotoXY(57, 13);
        printf("游戏设置");

        setPrintColor(userChoose == 2 ? 0x6f : 0x0f);
        gotoXY(57, 17);
        printf("开发人员");

        setPrintColor(userChoose == 3 ? 0x6f : 0x0f);
        gotoXY(57, 21);
        printf("玩法介绍");

        setPrintColor(userChoose == 4 ? 0x6f : 0x0f);
        gotoXY(57, 25);
        printf("退出游戏");
        setPrintColor(0x0f);


        char input = _getch();//接收

        switch (input) {
        case 'w':
            userChoose -= 1;
            if (userChoose == -1) {
                userChoose = 4;
            }
            break;

        case 's':
            userChoose += 1;
            if (userChoose == 5) {
                userChoose = 0;
            }
            break;

        case '\r':
            switch (userChoose) {
            case 0:
                system("cls");
                //进入游戏界面
                gameView();

            case 1:
                system("cls");
                //进入设置界面
                game_settings();

            case 2:
                system("cls");
                //进入开发人员界面
                developer();

            case 3:
                system("cls");
                //进入游戏玩法界面
                playing_method();

            case 4:
                system("pause");
                //退出游戏
                exit(0);
            }
            break;
        }
    }


}

//游戏设置界面
void game_settings() {

    int userChoose = 0;

    system("cls");

    while (1) {



        resetPrintColor(0x0f); // 默认颜色  
        gotoXY(57, 3);
        printf(" 设  置 ");

        setPrintColor(userChoose == 0 ? 0x6f : 0x0f);
        gotoXY(55, 9);
        printf("游戏内bgm设置");

        setPrintColor(userChoose == 1 ? 0x6f : 0x0f);
        gotoXY(57, 15);
        printf("颜色选择");

        setPrintColor(userChoose == 2 ? 0x6f : 0x0f);
        gotoXY(57, 21);
        printf("难度选择");

        setPrintColor(userChoose == 3? 0x6f : 0x0f);
        gotoXY(59, 27);
        printf("返回");
        resetPrintColor(0x0f);

        char input = _getch();//接收输入


        switch (input) {
        case 'w':
            userChoose = (userChoose - 1 + 4) % 4; // 循环选择  
            break;
        case 's':
            userChoose = (userChoose + 1) % 4;
            break;
        case '\r':
            switch (userChoose) {
            case 0:
                system("cls");
                //进入音乐选择界面
                game_music();
                break;
            case 1:
                system("cls");
                //进入颜色选择界面
                game_color();
                break;
            case 2:
                system("cls");
                //进入难度选择界面
                DifficultyChoice();
            case 3:
                system("cls");
                //进入菜单界面
                menuView();
            }
            break;
        }


    }


}

//游戏玩法界面
void playing_method()
{
    int userChoose = 0;
    while (1)
    {
        //打印界面
        setPrintColor(0x0f);
        gotoXY(54, 3);
        printf("玩 法 介 绍");

        gotoXY(47, 8);
        printf("输入坐标，棋子出现在指定位置");

        gotoXY(44, 11);
        printf("相同颜色的棋子五子连珠判定一次小胜利");

        gotoXY(47, 14);
        printf("五子连珠后此五颗棋子会被消掉");

        gotoXY(41, 17);
        printf("消去棋子达到具体数量判定完全胜利（游戏结束）");

        gotoXY(29, 20);
        printf("输入特定坐标，会跳转至文字彩蛋页面，出现一段文字，后跳转至游戏页面");

        gotoXY(38, 23);
        printf("悔棋提示：输入坐标后，按j键悔棋，按Enter键落子");

        setPrintColor(userChoose == 0 ? 0x6f : 0x0f);
        gotoXY(56, 25);
        printf("返回设置");

        setPrintColor(0x0f);

        //接收用户输入
        char input = _getch();

        //判断是否回车
        switch (input) {
        case '\r':
            system("cls");
            switch (userChoose)
            {
            case 0:
                //返回菜单界面
                menuView();
                break;
            }
            break;
        }
    }

}

//游戏开发人员界面
void developer() {

    int userChoose = 0;
    while (1)
    {
        //打印界面
        setPrintColor(0x0f);
        gotoXY(54, 3);
        printf("开  发  人  员");
        gotoXY(56, 7);
        printf("阿天小学长");
        gotoXY(48, 10);
        printf("叶何                 Aurora ");

        gotoXY(48, 12);
        printf("坚持                 兔子大王");

        gotoXY(48, 14);
        printf("大智                 我心飞翔");

        gotoXY(48, 16);
        printf("坦诚                Y U U O ");

        gotoXY(48, 18);
        printf("赫木                乞 骸 骨");

        setPrintColor(userChoose == 0 ? 0x6f : 0x0f);
        gotoXY(56, 25);
        printf("返回设置");

        setPrintColor(0x0f);

        //接收用户输入
        char input = _getch();

        //判断是否回车
        switch (input) {
        case '\r':
            system("cls");
            switch (userChoose)
            {
            case 0:
                //返回菜单界面
                menuView();
                break;
            }
            break;
        }
    }





}

//难度选择界面
void DifficultyChoice() {
    int userChoose = 0;


    system("cls");

    while (1) {



        resetPrintColor(0x0f); // 默认颜色  
        gotoXY(55, 3);
        printf(" 难 度 选 择 ");

        setPrintColor(userChoose == 0 ? 0x6f : 0x0f);
        gotoXY(59, 9);
        printf("简单");

        setPrintColor(userChoose == 1 ? 0x6f : 0x0f);
        gotoXY(59, 14);
        printf("普通");

        setPrintColor(userChoose == 2 ? 0x6f : 0x0f);
        gotoXY(59, 19);
        printf("困难");

        setPrintColor(userChoose == 3 ? 0x6f : 0x0f);
        gotoXY(59, 24);
        printf("返回");

        resetPrintColor(0x0f);



        char input = _getch();


        switch (input) {
        case 'w':
            userChoose = (userChoose - 1 + 4) % 4; // 循环选择  
            break;
        case 's':
            userChoose = (userChoose + 1) % 4;
            break;
        case '\r':
            if (userChoose != 3) {
                gotoXY(54, 22);
                resetPrintColor(0x6);
                printf("!!!选择成功!!!");
            }
            switch (userChoose) {
            case 0:
                count = 1;//简单，消五子胜利
                break;
            case 1:
                count = 2;//普通，消十字胜利
                break;
            case 2:
                count = 3;//困难，消十五子胜利
                break;
            case 3:
                system("cls");
                //返回菜单界面
                game_settings();
            }
            break;
        }


    }


}

//音乐播放选择
int playMusic(int choose) {

    switch (choose) {
    case 0:
        stopMusic();
        mciSendString("open CrazyDave(In-Game).mp3 alias bgm", NULL, 0, NULL);
        mciSendString("play bgm repeat ", NULL, 0, NULL);
        mciSendString("setaudio bgm volume to 200", NULL, 0, NULL);
        f++;
        break;

    case 1:
        stopMusic();
        mciSendString("open Experience.mp3 alias bgm1", NULL, 0, NULL);
        mciSendString("play bgm1 repeat", NULL, 0, NULL);
        mciSendString("setaudio bgm1 volume to 200", NULL, 0, NULL);
        f++;
        break;

    case 2:
        stopMusic();
        mciSendString("open 雑踏、僕らの街.mp3 alias bgm2", NULL, 0, NULL);
        mciSendString("play bgm2 repeat", NULL, 0, NULL);
        mciSendString("setaudio bgm2 volume to 200", NULL, 0, NULL);
        f++;
        break;

    case 3:
        stopMusic();
        mciSendString("open Unwelcomeschool.mp3 alias bgm3", NULL, 0, NULL);
        mciSendString("play bgm3 repeat ", NULL, 0, NULL);
        mciSendString("setaudio bgm3 volume to 200", NULL, 0, NULL);
        f++;

        break;

    case 4:

        stopMusic();
        mciSendString("open 让风告诉你.mp3 alias bgm4", NULL, 0, NULL);
        mciSendString("play bgm4 repeat", NULL, 0, NULL);
        mciSendString("setaudio bgm4 volume to 200", NULL, 0, NULL);
        f++;
        break;

    case 5:
        stopMusic();
        mciSendString("open REDOUT.mp3 alias bgm5", NULL, 0, NULL);
        mciSendString("play bgm5 repeat", NULL, 0, NULL);
        mciSendString("setaudio bgm5 volume to 200", NULL, 0, NULL);
        f++;
        break;

    case 6:
        stopMusic();
        mciSendString("open 三国杀.mp3 alias bgm6", NULL, 0, NULL);
        mciSendString("play bgm6 repeat", NULL, 0, NULL);
        mciSendString("setaudio bgm6 volume to 100", NULL, 0, NULL);/////
        f++;
        break;

    case 7:
        stopMusic();
        mciSendString("open フンフンフンだよ、らきすた.mp3 alias bgm7", NULL, 0, NULL);
        mciSendString("play bgm7 repeat", NULL, 0, NULL);
        mciSendString("setaudio bgm7 volume to 200", NULL, 0, NULL);
        f++;
        break;

    case 8:
        stopMusic();
        mciSendString("open 欢乐斗地主.mp3 alias bgm8", NULL, 0, NULL);
        mciSendString("play bgm8 repeat", NULL, 0, NULL);
        mciSendString("setaudio bgm8 volume to 200", NULL, 0, NULL);
        f++;
        break;

    case 9:
        stopMusic();
        mciSendString("open CornfieldChase.mp3 alias bgm9", NULL, 0, NULL);
        mciSendString("play bgm9 repeat", NULL, 0, NULL);
        mciSendString("setaudio bgm9 volume to 200", NULL, 0, NULL);
        f++;
        break;






        return 0;
    };

}

//音乐选择界面
void game_music() {
    mciSendString("stop bgm0", NULL, 0, NULL);
    int UserChoose = 0;
    system("cls");
    while (1) {
        resetPrintColor(0x0f);
        gotoXY(60, 1);
        printf("BGM设置");


        setPrintColor(UserChoose == 0 ? 0x6f : 0x0f);
        gotoXY(48, 7);
        printf("CrazyDave");

        setPrintColor(UserChoose == 1 ? 0x6f : 0x0f);
        gotoXY(48, 11);
        printf("Experience");

        setPrintColor(UserChoose == 2 ? 0x6f : 0x0f);
        gotoXY(46, 15);
        printf("雑踏、僕らの街");

        setPrintColor(UserChoose == 3 ? 0x6f : 0x0f);
        gotoXY(46, 19);
        printf("Unwelcome school");

        setPrintColor(UserChoose == 4 ? 0x6f : 0x0f);
        gotoXY(48, 23);
        printf("让风告诉你");

        setPrintColor(UserChoose == 5 ? 0x6f : 0x0f);
        gotoXY(68, 7);
        printf("RED OUT");

        setPrintColor(UserChoose == 6 ? 0x6f : 0x0f);
        gotoXY(68, 11);
        printf("三国杀");

        setPrintColor(UserChoose == 7 ? 0x6f : 0x0f);
        gotoXY(68, 15);
        printf("フンフンフンだよ、らきすた");

        setPrintColor(UserChoose == 8 ? 0x6f : 0x0f);
        gotoXY(68, 19);
        printf("欢乐斗地主");

        setPrintColor(UserChoose == 9 ? 0x6f : 0x0f);
        gotoXY(68, 23);
        printf("CornfieldChase");

        setPrintColor(UserChoose == 10 ? 0x6f : 0x0f);
        gotoXY(56, 27);
        printf("停止播放音乐");

        setPrintColor(UserChoose == 11 ? 0x6f : 0x0f);
        gotoXY(60, 30);
        printf("返回");


        char input = _getch();//接收输入

        switch (input) {
        case'w': UserChoose -= 1;
            if (UserChoose == -1) {
                UserChoose = 11;

            }
            break;

        case's': UserChoose += 1;
            if (UserChoose == 12) {
                UserChoose = 0;
            }
            break;

        case'\r':
            if (UserChoose < 10) {
                gotoXY(55, 28);
                resetPrintColor(0x6);
                printf("!!!选择成功!!!");
            }
            
            else {
                gotoXY(55, 28);
                resetPrintColor(0x6);
                printf("   取消选择   ");

            }
            
            switch (UserChoose) {
            case 0:playMusic(0);
                break;

            case 1:playMusic(1);
                break;

            case 2:playMusic(2);
                break;

            case 3:playMusic(3);
                break;

            case 4:playMusic(4);
                break;

            case 5:playMusic(5);
                break;

            case 6:playMusic(6);
                break;

            case 7:playMusic(7);
                break;

            case 8:playMusic(8);
                break;

            case 9:playMusic(9);
                break;

            case 10:
                stopMusic();//停止播放音乐
                break;

            case 11://调用上一级函数;
                setPrintColor(0x0f);
                //回到设置界面
                game_settings();

                break;


            }
            break;


        }


    }








}

// 停止播放指定音乐
void stopMusic() {

    while (1) {
        mciSendString("stop bgm", NULL, 0, NULL);
        mciSendString("stop bgm1", NULL, 0, NULL);
        mciSendString("stop bgm2", NULL, 0, NULL);
        mciSendString("stop bgm3", NULL, 0, NULL);
        mciSendString("stop bgm4", NULL, 0, NULL);
        mciSendString("stop bgm5", NULL, 0, NULL);
        mciSendString("stop bgm6", NULL, 0, NULL);
        mciSendString("stop bgm7", NULL, 0, NULL);
        mciSendString("stop bgm8", NULL, 0, NULL);
        mciSendString("stop bgm9", NULL, 0, NULL);
        break;


    }


}


//选择地图颜色
void setmapColor(int color) {
  
    switch (mapColor) {
    case 0: printf("\033[1;31m"); break; // red
    case 1: printf("\033[1;34m"); break; // Blue
    case 2: printf("\033[1;32m"); break; // Green
    case 3: printf("\033[1;33m"); break; // yellow
    case 4: printf("\033[1;37m"); break; // white
    }


}

//选择边框提示颜色
void setborderColor(int color) {
   
    switch (borderColor) {
    case 0: printf("\033[1;31m"); break; // red
    case 1: printf("\033[1;35m"); break; // purple
    case 2: printf("\033[1;36m"); break; // lightGreen
    case 3: printf("\033[1;33m"); break; // yellow
    case 4: printf("\033[1;37m"); break; // white
    }



}

//颜色选择界面
void game_color() {

    int userChooseSection = 0; // 0: 地图颜色选择 1: 边框颜色选择 2：
    int userChooseColor1 = 0;   // 地图颜色  0：红色 1：蓝色 2：绿色 3：黄色
    int userChooseColor2 = 0;   // 边框颜色  0：红色 1：紫色 2：绿色 3：黄色
    int userChooseColor3 = 0;   // 0:确认 1：重置 2：返回

    system("cls");

    while (1) {

        setPrintColor(0x0f);// 默认颜色  
        gotoXY(55, 3);
        printf("颜 色 选 择");

        setPrintColor(0x0f);
        gotoXY(10, 9);
        printf("地图颜色选择: ");

        setPrintColor(0x0f);
        gotoXY(10, 15);
        printf("边框颜色选择: ");


        // 根据当前选择设置颜色
        for (int i = 0; i < 4; i++) {
            int colorCode = (userChooseSection == 0 && userChooseColor1 == i) ? 0x6f : 0x0f;
            setPrintColor(colorCode);
            gotoXY(38 + i * 20, 9);
            printf("%s", (i == 0) ? "红色" : (i == 1) ? "蓝色" : (i == 2) ? "绿色" : "黄色");

            colorCode = (userChooseSection == 1 && userChooseColor2 == i) ? 0x6f : 0x0f;
            setPrintColor(colorCode);
            gotoXY(38 + i * 20, 15);
            printf("%s", (i == 0) ? "红色" : (i == 1) ? "紫色" : (i == 2) ? "青色" : "黄色");


        }

        for (int i = 0; i < 3; i++) {
            int colorCode = (userChooseSection == 2 && userChooseColor3 == i) ? 0x6f : 0x0f;
            setPrintColor(colorCode);
            gotoXY(41 + i * 20, 25);
            printf("%s", (i == 0) ? "确认" : (i == 1) ? "重置" : "返回");
        }


        // 读取用户输入  
        char input = _getch();

        // 处理输入  
        switch (input) {
        case 'w':
            userChooseSection -= 1;
            if (userChooseSection == -1) {
                userChooseSection = 2;
            }
            break;
        case 's':
            userChooseSection += 1;
            if (userChooseSection == 3) {
                userChooseSection = 0;
            }
            break;
        case 'a':
            if (userChooseSection == 0) {
                userChooseColor1 = (userChooseColor1 - 1 + 4) % 4;
            }

            else if (userChooseSection == 1) {
                userChooseColor2 = (userChooseColor2 - 1 + 4) % 4;
            }

            else if (userChooseSection == 2) {
                userChooseColor3 = (userChooseColor3 - 1 + 3) % 3;
            }
            break;
        case 'd':
            if (userChooseSection == 0) {
                userChooseColor1 = (userChooseColor1 + 1) % 4;
            }
            else if (userChooseSection == 1) {
                userChooseColor2 = (userChooseColor2 + 1) % 4;
            }
            else if (userChooseSection == 2) {
                userChooseColor3 = (userChooseColor3 + 1) % 3;
            }
            break;
        case '\r':
            if (userChooseSection == 0) {//选择地图颜色
                gotoXY(10, 11);
                resetPrintColor(0x6);
                printf("地图颜色已选择: ");
                printf("%s", (userChooseColor1 == 0) ? "红色" : (userChooseColor1 == 1) ? "蓝色" : (userChooseColor1 == 2) ? "绿色" : "黄色");

            }
            else if (userChooseSection == 1) {//选择边框提示颜色
                gotoXY(10, 17);
                resetPrintColor(0x6);
                printf("边框颜色已选择: ");
                printf("%s", (userChooseColor2 == 0) ? "红色" : (userChooseColor2 == 1) ? "紫色" : (userChooseColor2 == 2) ? "青色" : "黄色");

            }
            else if (userChooseSection == 2) {//选择 确认 重置（默认地图边框颜色为白） 返回
                if (userChooseColor3 == 0) {
                    gotoXY(57, 22);
                    resetPrintColor(0x6);
                    printf("!!!选择成功!!!");
                    mapColor = userChooseColor1;
                    borderColor = userChooseColor2;
                }
                else if (userChooseColor3 == 1) {
                    system("cls");
                    //重置初始颜色
                    mapColor = 4;
                    borderColor = 4;

                }
                else if (userChooseColor3 == 2) {
                    setPrintColor(0x0f);
                    //回到设置界面
                    game_settings();
                }


            }
            break;
        default:
            break;
        }



    }


}
//游戏游玩提示语句边框打印
void printBox(int x, int y, int w, int h)
{
    //左竖线
    for (int i = 0; i < h; i++) {
        gotoXY(x, y + i);
        putchar('#');
    }
    //右竖线
    for (int i = 0; i < h; i++) {
        gotoXY(x + w, y + i);
        putchar('#');
    }
    //上横线   
    gotoXY(x, y);
    for (int i = 0; i < w; i++) {
        putchar(' #');
    }
    //下横
    for (int i = 0; i <= w; i++) {
        gotoXY(x + i, y + h);
        putchar(' #');

    }
}
//地图与提示边框打印
void gameView_ShowMap() {
    // 打印提示边框
    setborderColor(borderColor);//应用边框颜色
    printf("               ");
    for (int i = 1; i <= 9; i++)
    {
        printf("%d   ", i);
    }
    for (int i = 10; i <= 15; i++)
    {

        printf("%d  ", i);
    }
    for (int i = 0; i <= 14; i++)
    {

        if (i == 0)
        {
            printf("            \n");
            continue;
        }
        printf("            %d\n\n", i);
    }
    printf("            %d", 15);

    //打印地图
    setmapColor(mapColor);//应用地图颜色
    for (int i = 0; i < 15; i++) {
        setmapColor(mapColor);
        gotoXY(15, 2 + 2 * i);
        for (int j = 0; j < 15; j++) {
            setmapColor(mapColor);
            if (map[i][j] == 0) {
                printf(" 十 ");
            }
            else if (map[i][j] == 1) {
                printf(" \x1b[90;100m〇\x1b[0m ");//黑子
            }
            else if (map[i][j] == 2) {
                printf(" \x1b[97;107m〇\x1b[0m ");//白子

            }
        }
        if (i != 14)
            printf("\n");

    }

}


//游戏界面
void gameView()
{
    init();
    mciSendString("stop bgm0", NULL, 0, NULL);
    while (1) {
        gameView_ShowMap();
        int x = 0, y = 0;

        setPrintColor(0x0f);
        printBox(80, 1, 14, 2);
        gotoXY(83, 2);
        printf("按回车落子\n");

        setPrintColor(0x0f);
        printBox(100, 1, 14, 2);
        gotoXY(103, 2);
        printf("按j键悔棋\n");

        setPrintColor(0x0f);
        printBox(82, 4, 28, 2);
        gotoXY(84, 5);
        printf("输入坐标后按k键返回主菜单\n");

        setPrintColor(0x0f);
        printBox(98, 19,17, 4);
        gotoXY(100, 20);
        printf("黑方胜利次数:%d",sum1);
        gotoXY(100, 22);
        printf("白方胜利次数:%d", sum2);

        setPrintColor(0x0f);
        printBox(98,26,17,4);
        gotoXY(100, 28);
        printf("要求胜利次数:%d", count);


        setPrintColor(0x0f);
        gotoXY(80, 8);
        printf("玩家%s请输入落子坐标：\n", (flag % 2 == 0) ? "一" : "二");
        gotoXY(80, 9);
   
        gotoXY(102, 8);
        int rusult=scanf_s("%d %d", &x, &y);//玩家坐标非数组
 
        while (getchar() != '\n');

        x--;//map坐标
        y--;//map坐标
        if (rusult!=2||x<0||x>=15||y<0||y>=15) {
            gotoXY(80, 14);
            setPrintColor(0x60);
            printf("无效坐标\n");
            gotoXY(80, 16);
            setPrintColor(0x60);
            system("pause");
            setPrintColor(0x0f);
            system("cls");
            continue;
        }

        if (!playerMove(x, y)) {
            gotoXY(80, 14);
            setPrintColor(0x60);
            printf("此位置已被占用\n");
            gotoXY(80, 16);
            setPrintColor(0x60);
            system("pause");
            setPrintColor(0x0f);
            system("cls");
            continue;
        }
        SurpriseEgg(x, y);
        system("cls");
        gameView_ShowMap();
        setPrintColor(0x0f);
        printBox(80, 1, 14, 2);
        gotoXY(83, 2);
        printf("按回车落子\n");

        setPrintColor(0x0f);
        printBox(100, 1, 14, 2);
        gotoXY(103, 2);
        printf("按j键悔棋\n");

        setPrintColor(0x0f);
        printBox(82, 4, 28, 2);
        gotoXY(84, 5);
        printf("输入坐标后按k键返回主菜单\n");

        setPrintColor(0x0f);
        printBox(98, 19, 17, 4);
        gotoXY(100, 20);
        printf("黑方胜利次数:%d", sum1);
        gotoXY(100, 22);
        printf("白方胜利次数:%d", sum2);

        setPrintColor(0x0f);
        printBox(98, 26, 17, 4);
        gotoXY(100, 28);
        printf("要求胜利次数:%d", count);
        setPrintColor(0x0f);
        gotoXY(80, 9);
        printf("除按j，k键任意键开始下一玩家下棋");
        gotoXY(122, 9);
        char input = _getch();
        switch (input)
        {
        case 'j'://悔棋
            map[x][y] = 0;
            regret();
            while (s != 0)
            {
                gameView_ShowMap();
                setPrintColor(0x0f);
                printBox(90, 1, 14, 2);
                gotoXY(93, 2);
                printf("按回车落子\n");
                setPrintColor(0x0f);
                printBox(98, 19, 17, 4);
                gotoXY(100, 20);
                printf("黑方胜利次数:%d", sum1);
                gotoXY(100, 22);
                printf("白方胜利次数:%d", sum2);

                setPrintColor(0x0f);
                printBox(98, 26, 17, 4);
                gotoXY(100, 28);
                printf("要求胜利次数:%d", count);
                regret();
            }
           
            break;
        case 'k':
            system("cls");
            menuView();
        case'\r':
            break;
        default:
            break;
        }


        isWin(x, y);
        if (sum1 == count || sum2 == count)
        {
           system("cls");
           //进入胜利界面
            winView();
            return;
        }

        flag++;
        system("cls");
    }
        
        
      
        
    
}

//落子
int  playerMove(int x, int y) {
    if (map[x][y] == 0)
    {

        if (flag % 2 == 0)
        {
            map[x][y] = 1;//黑子
        }
        else if (flag % 2 == 1)
        {
            map[x][y] = 2;//白子
        }
        return 1;

    }
    return 0;
}

//悔棋
void regret()
{

    int x1, y1;
    gotoXY(80, 10);
    printf("请输入悔棋后的x,y坐标: ");
    gotoXY(102, 10);
    
    int rusult =scanf_s("%d %d", &x1, &y1);

    while (getchar() != '\n');

    x1--; y1--;
    if (rusult != 2 || x1 < 0 || x1 >= 15 || y1 < 0 || y1 >= 15) {
        gotoXY(80, 14);
        setPrintColor(0x60);
        printf("无效坐标\n");
        gotoXY(80, 16);
        setPrintColor(0x60);
        system("pause");
        setPrintColor(0x0f);
        system("cls");
        s = 1;
        return ;
    }

    if (map[x1][y1]!=0&& map[x1][y1] ==((flag-1 )% 2 == 0 ? 1 : 2))
    {
        gotoXY(80, 14);
        setPrintColor(0x60);
        printf("位置已被占用\n");
        gotoXY(80, 16);
        setPrintColor(0x60);
        system("pause");
        setPrintColor(0x0f);
        system("cls");
        s = 1;
        return;

    }
    s = 0;
    replayerMove(x1, y1);
    gameView_ShowMap();
}


//悔棋后重新落子
void replayerMove(int x, int y)
{
    map[x][y] = (flag % 2 == 0) ? 1 : 2;
}

//胜利判断
void isWin(int x, int y) {
    int count1 = 0;
    int color = map[x][y];

    //  横向判断
    for (int i = 0; i < 13; i++) {

        //    越界判断
        if ((y - 6 + i) < 0) {//起点
            continue;//跳过 进行下一次
        }
        else if ((y - 6 + i) > 14) {//终点
            break;//此时继续语句无意义
        }
        if (map[x][y - 6 + i] == color) {
            map3[x][y - 6 + i] = color;
            count1++;
        }
        else {
            for (int i = 0; i < 15; i++) {
                for (int j = 0; j < 15; j++) {
                    map3[i][j] = 0;
                }
            }

            count1 = 0;
        }
        if (count1 == 5 && color == 1) {
            for (int i = 0; i < 15; i++) {
                for (int j = 0; j < 15; j++) {
                    map[i][j] -= map3[i][j];
                }
            }
            for (int i = 0; i < 15; i++) {
                for (int j = 0; j < 15; j++) {
                    map3[i][j] = 0;
                }
            }

            sum1 += 1;

        }
        if (count1 == 5 && color == 2) {
            for (int i = 0; i < 15; i++) {
                for (int j = 0; j < 15; j++) {
                    map[i][j] -= map3[i][j];
                }
            }
            for (int i = 0; i < 15; i++) {
                for (int j = 0; j < 15; j++) {
                    map3[i][j] = 0;
                }
            }


            sum2 += 1;

        }



    }

    // 纵向判断
    for (int i = 0; i < 13; i++) {

        //   越界判断
        if ((x - 6 + i) < 0) {
            continue;//跳过 进行下一次
        }
        else if ((x - 6 + i) > 14) {
            break;//此时继续语句无意义
        }




        if (map[x - 6 + i][y] == color) {
            map3[x - 6 + i][y] = color;
            count1++;
        }
        else {
            for (int i = 0; i < 15; i++) {
                for (int j = 0; j < 15; j++) {
                    map3[i][j] = 0;
                }
            }
            count1 = 0;
        }
        if (count1 == 5 && color == 1) {
            for (int i = 0; i < 15; i++) {
                for (int j = 0; j < 15; j++) {
                    map[i][j] -= map3[i][j];
                }
            }
            for (int i = 0; i < 15; i++) {
                for (int j = 0; j < 15; j++) {
                    map3[i][j] = 0;
                }
            }


            sum1 += 1;

        }
        if (count1 == 5 && color == 2) {
            for (int i = 0; i < 15; i++) {
                for (int j = 0; j < 15; j++) {
                    map[i][j] -= map3[i][j];
                }
            }
            for (int i = 0; i < 15; i++) {
                for (int j = 0; j < 15; j++) {
                    map3[i][j] = 0;
                }
            }


            sum2 += 1;

        }



    }



    //      '/'向判断
    for (int i = 0; i < 13; i++) {

        //           越界判断
        if ((x + 6 - i) > 14 || (y - 6 + i) < 0) {
            continue;//跳过 进行下一次
        }
        else if ((x + 6 - i) < 0 || (y - 6 + i) > 14) {
            break;//此时继续语句无意义
        }




        if (map[x + 6 - i][y - 6 + i] == color) {
            map3[x + 6 - i][y - 6 + i] = color;
            count1++;
        }
        else {
            for (int i = 0; i < 15; i++) {
                for (int j = 0; j < 15; j++) {
                    map3[i][j] = 0;
                }
            }
            count1 = 0;
        }
        if (count1 == 5 && color == 1) {
            for (int i = 0; i < 15; i++) {
                for (int j = 0; j < 15; j++) {
                    map[i][j] -= map3[i][j];
                }
            }
            for (int i = 0; i < 15; i++) {
                for (int j = 0; j < 15; j++) {
                    map3[i][j] = 0;
                }
            }


            sum1 += 1;

        }
        if (count1 == 5 && color == 2) {
            for (int i = 0; i < 15; i++) {
                for (int j = 0; j < 15; j++) {
                    map[i][j] -= map3[i][j];
                }
            }
            for (int i = 0; i < 15; i++) {
                for (int j = 0; j < 15; j++) {
                    map3[i][j] = 0;
                }
            }


            sum2 += 1;

        }



    }

    // '\'向判断
    for (int i = 0; i < 13; i++) {

        //      越界判断
        if ((x - 6 + i) < 0 || (y - 6 + i) < 0) {
            continue;//跳过 进行下一次
        }
        else if ((x - 6 + i) > 14 || (y - 6 + i) > 14) {
            break;//此时继续语句无意义
        }




        if (map[x - 6 + i][y - 6 + i] == color) {
            map3[x - 6 + i][y - 6 + i] = color;
            count1++;
        }
        else {
            for (int i = 0; i < 15; i++) {
                for (int j = 0; j < 15; j++) {
                    map3[i][j] = 0;
                }
            }
            count1 = 0;
        }
        if (count1 == 5 && color == 1) {
            for (int i = 0; i < 15; i++) {
                for (int j = 0; j < 15; j++) {
                    map[i][j] -= map3[i][j];
                }
            }
            for (int i = 0; i < 15; i++) {
                for (int j = 0; j < 15; j++) {
                    map3[i][j] = 0;
                }
            }


            sum1 += 1;

        }
        if (count1 == 5 && color == 2) {
            for (int i = 0; i < 15; i++) {
                for (int j = 0; j < 15; j++) {
                    map[i][j] -= map3[i][j];
                }
            }
            for (int i = 0; i < 15; i++) {
                for (int j = 0; j < 15; j++) {
                    map3[i][j] = 0;
                }
            }


            sum2 += 1;

        }



    }



}


//彩蛋界面
void SurpriseEgg(int x, int y) {
    if (x == 3 && y == 3) {
        system("cls");
        gotoXY(52, 7);
        setPrintColor(0x60);
        printf("！恭喜你触发彩蛋！");
        gotoXY(56, 12);
        setPrintColor(0x0c);
        printf("404 ERROR");
        gotoXY(54, 15);
        system("pause");

    }
    else if (x == 3 && y == 1) {
        system("cls");
        gotoXY(52, 7);
        setPrintColor(0x60);
        printf("！恭喜你触发彩蛋！");
        gotoXY(49, 12);
        setPrintColor(0x0e);
        printf("恭喜你触及宇宙的结局…………");
        gotoXY(53, 15);
        system("pause");
    }
    else if (x == 7 && y == 9) {
        system("cls");
        gotoXY(52, 7);
        setPrintColor(0x60);
        printf("！恭喜你触发彩蛋！");
        setPrintColor(0x0f);
        gotoXY(50, 12);
        printf("我们相信你已经做好了准备");
        gotoXY(56, 14);
        printf("天下如棋局");
        gotoXY(56, 16);
        printf("世人如棋子");
        gotoXY(51, 18);
        printf("愿你成为那执棋之人");
        gotoXY(54, 22);
        system("pause");

    }
    else if (x == 12 && y == 5) {
        system("cls");
        gotoXY(52, 7);
        setPrintColor(0x60);
        printf("！恭喜你触发彩蛋！");
        gotoXY(49, 12);
        setPrintColor(0x0c);
        printf("我会永远盯着你…永远永远…");
        gotoXY(53, 15);
        system("pause");
    }
    else if (x == 2 && y == 9) {
        system("cls");
        gotoXY(52, 7);
        setPrintColor(0x60);
        printf("！恭喜你触发彩蛋！");
        gotoXY(53, 12);
        setPrintColor(0x0e);
        printf("v我50，看你实力");
        gotoXY(53, 16);
        system("pause");
    }
    else if (x == 14 && y == 13) {
        system("cls");
        gotoXY(52, 7);
        setPrintColor(0x60);
        printf("！恭喜你触发彩蛋！");
        gotoXY(54, 12);
        setPrintColor(0x0b);
        printf("What can I say!");
        gotoXY(52, 17);
        system("pause");
    }
    else if (x == 5 && y == 14) {
        system("cls");
        gotoXY(52, 7);
        setPrintColor(0x60);
        printf("！恭喜你触发彩蛋！");
        gotoXY(51, 12);
        setPrintColor(0x09);
        printf("冷知识：科比没有肘击过秦始皇");
        gotoXY(53, 17);
        system("pause");
    }
    else if (x == 14 && y == 2) {
        system("cls");
        gotoXY(52, 7);
        setPrintColor(0x60);
        printf("！恭喜你触发彩蛋！");
        gotoXY(55, 12);
        setPrintColor(0x0a);
        printf("已抢到先机");
        gotoXY(53, 15);
        system("pause");
    }
    else if (x == 9 && y == 9) {
        system("cls");
        gotoXY(52, 7);
        setPrintColor(0x60);
        printf("！恭喜你触发彩蛋！");
        gotoXY(40, 12);
        setPrintColor(0x0d);
        printf("每日一问：你可以在珠穆朗玛峰峰顶煎鸡蛋吗？");
        gotoXY(52, 15);
        system("pause");
    }




}

//胜利界面
void winView() {
    int userChoose = 0;
    while (1) {
        // ----------------- 打印界面 -----------------

        if (sum1 == count)
        {
            gotoXY(52, 3);
            setPrintColor(0x6);
            printf("黑  子  胜  利");
            setPrintColor(0x0f);

        }
        else if (sum2 == count)
        {
            gotoXY(52, 3);
            setPrintColor(0x6);
            printf("白  子  胜  利");
            setPrintColor(0x0f);
        }
        if (userChoose == 0) setPrintColor(0x6f);
        gotoXY(55, 9);
        printf("再来一局");
        if (userChoose == 0) setPrintColor(0x0f);

        if (userChoose == 1) setPrintColor(0x6f);
        gotoXY(54, 15);
        printf("返回主菜单");
        if (userChoose == 1) setPrintColor(0x0f);

        if (userChoose == 2) setPrintColor(0x6f);
        gotoXY(55, 21);
        printf("退出游戏");
        if (userChoose == 2) setPrintColor(0x0f);

        if (userChoose == 3) setPrintColor(0x6f);


        // ---------------- 接收用户输入 --------------
        char input = _getch();

        // -------------判断是方向上下还是回车------------
        switch (input) {
        case 'w':
            userChoose -= 1;
            if (userChoose == -1) {
                userChoose = 2;
            }
            break;
        case 's':

            userChoose = (userChoose + 1) % 3;
            break;
        case '\r':
            system("cls");
            switch (userChoose) {
            case 0:
                //进入游戏界面
                gameView();
                break;
            case 1:
                //停止播放音乐
                // 返回主菜单
                stopMusic();
                f = 0;
                menuView();
                break;
            case 2:
                //退出
                exit(0);;
                break;

            }

            break;
        }
    }

}




//主函数入口
int main() {
    //调用菜单函数
    menuView();
    return 0;
}

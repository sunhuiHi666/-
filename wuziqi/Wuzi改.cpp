#include<stdio.h>
#include<windows.h>
#include<mmsystem.h>
#include<conio.h>
#pragma comment(lib,"winmm.lib")
// -------------------------------- ��   ��   ��   ��    ---------------------------------------
/*
    ����:
        map[i][j]��ʾ����(i,j)��ֵ
        0��ʾ�յ�
        1��ʾ����
        2��ʾ����
    ��: map[3][6] = 1  ��ʾ(3,6)��λ���Ǻ���
*/
//���������飬һ����¼��ʵ���̣�һ����¼�������ӵ�����
int map[15][15];
int map3[15][15];
//mapColor��ʾ��ͼ��ɫ
//borderColor��ʾ�߿���ʾ��ɫ
int mapColor = 4;
int borderColor = 4;
//flag��ʾ��ǰ�غ���  ż����ʾ��������  ������ʾ��������
//��: flag = 20 ��ʾ��ǰ�ǵ�[20]������  �ɺڷ�����
int flag;
//sum1��ʾ����ʤ������
//sum2��ʾ����ʤ������
int sum1;
int sum2;
//�Ѷ�ѡ��   �� 1   ��ͨ 2   ���� 3
int count = 2;
int s = 0;
int f = 0;//��������
//--------------------------------------- ��   ��   ��   ��----------------------------------------
// 
// ---------------------------------------  s e r v i c e -----------------------------------------
/*
    ������:̹��
    ����:��ʼ����Ϸ����
        �����̵�ֵ��ʼ��Ϊ0   map  map3
        ��ǰ�غ���Ϊ����(flag��Ϊ0)
         sum1,sum2 Ϊ0
        countĬ���Ѷ�
        mapColorĬ�ϵ�ͼ��ɫ
        borderColorĬ�ϱ߿���ʾ��ɫ
    ����: void
    ����ֵ: void
*/
void init();

/*
������:����
����:
����
����r����һ���µ����ӳ���
��������һ�غ�����������ӵĻ���
������x,y;
����ֵ: void
*/
void  regret();

/*
    *�ѵ�1
    ������:̹��
    ����: ���ݴ��������(map��Ӧλ��)��flagֵ �ж������Ƿ��ʤ��ÿ�λ�ʤ���������˭ʤ����
    ��Ӧsum���м�һ ��ȥ���ɵ�����
    ����:
        x: ��ǰ�غ����ӵ�x����
        y: ��ǰ�غ����ӵ�y����
  
*/
void isWin(int x, int y);

/*
    ������:���ķ���
    ����:��ָ��λ������
    ��ȥ��������������
        ���map[x][y]�ǿյ� ���޸�map[x][y]��ֵ:��Ϊ��Ӧ��ɫ(flag��Ӧ��ɫ)
        ���򲻲���
    ����:
        x: ��ǰ�غ����ӵ�x����
        y: ��ǰ�غ����ӵ�y����
    ����ֵ:
        0��ʾ����ʧ�� (�����Ѿ�����)
        1��ʾ���ӳɹ�
*/
int playerMove(int x, int y);

/*
    ������:̹��
    ���ܣ�ֹͣ������������
    ����: void
    ����ֵ: void
*/
void stopMusic();
// ------------------------------------------- s e r v i c e --------------------------------------------



// --------------------------------------------- v i e w ------------------------------------------------
/*  ������:���
    ����:��Ϸ���˵�
    ��Ϸ��
    չʾѡ��  ����wsad�ƶ���꣬�س�ѡ��
    ��ʼ��Ϸ: ������Ϸ���溯��gameView();
    ��Ϸ����: ������Ϸ���ý��溯��game_settings();
    ������Ա: ���ÿ�����Ա���溯��developer();
    �淨����: �����淨���ܽ��溯��playing_method();
    �˳���Ϸ: ����exit(0);
    ����: void
    ����ֵ: void
*/
void menuView();

/*
    ������:̹��/����
    ����:��Ϸ����
    ���ݲ�Ʒԭ��ͼ ��ӡ��Ϸ����
    ����: void
    ����ֵ: void
*/
void gameView_ShowMap();

/*
    ������:Ҷ��
    ����:��Ϸ����
    չʾѡ�� ����wsad�ƶ���꣬�س�ѡ��
    ��Ϸ��BGM:������Ϸ���ֽ��溯��game_music();
    ��ɫѡ��:������ɫѡ����溯��
    ����:�ص����˵�
    ����: void
    ����ֵ: void
*/
void game_settings();

/*
    ������:̹��
    ����:���ݲ�Ʒԭ��ͼ ��ӡ������ѡ�����
    ����wsad�ƶ���꣬�س�ѡ��
    ����ѡ�������Ϸ������
    ����:������Ϸ����
    ����: void
    ����ֵ: void
*/
void game_music();

/*
    ������:Ҷ��
    ����:���ݲ�Ʒԭ��ͼ ��ӡ����ɫѡ�����
    ����wsad�ƶ���꣬�س�ѡ��
    ��ͼ��ɫѡ��
    �߿���ɫѡ��
    ����:������Ϸ����
    ����: void
    ����ֵ: void
*/
void game_color();

/*
  ������:Ҷ��
  ���ܣ�ʵ�ֵ�ͼ��ɫѡ��
 switch ���
    case 0:  ��ɫ
    case 1:  ��ɫ
    case 2:  ��ɫ
    case 3:  ��ɫ
    case 4:  ��ɫ
    ����: void
    ����ֵ: void
*/
void setmapColor(int color);

/*
   ������:Ҷ��
   ���ܣ�ʵ�ֱ߿���ɫѡ��
    switch ���
    case 0:  ��ɫ
    case 1:  ��ɫ
    case 2:  ��ɫ
    case 3:  ��ɫ
    case 4:  ��ɫ
    ����: void
    ����ֵ: void
*/
void setborderColor(int color);

/*
    ������:����
    ����:������Ա
    ���ݲ�Ʒԭ��ͼ ��ӡ������Ա����
    ���ݻس�ѡ��
    ����:�������˵�
    ����: void
    ����ֵ: void
*/
void developer();

/*
    ������:��ľ
    ����:�淨����
    ���ݲ�Ʒԭ��ͼ ��ӡ�淨���ܽ���
    ���ݻس�ѡ��
    ����:�������˵�
    ����: void
    ����ֵ: void
*/
void playing_method();

/*
    ������:AURORA
    ���ܣ��ʵ�
    ����ʵ����棬��ѡ�񷵻���Ϸ
����:void
����ֵ:void
*/
void SurpriseEgg(int x, int y);

/*
    ������:�򺡹�
    ����: ��ӡ�������  �û�����ѡ������һ�ֻ�ص����˵�
    ����һ��:
    �ص����˵�:
    �˳���Ϸ:
    ����: void
    ����ֵ: void
*/
void winView();

/*
    *�ѵ�2
    ������:YOOU/̹��/����
    ����: ��Ϸ��������
        ��ʼ����Ϸ����(���ú���init())
        while(1){
            ��ӡ��Ϸ����(���ú���gameView_ShowMap())
            �����������,��������
            ����
            ����(�������Ӻ���playerMove())
                (�������ʧ�� ���¿�ʼѭ��)

            �ж���Ϸ�غ��Ƿ����(����ʤ���жϺ���isWin())
           (�����Ϸʤ������û�ﵽ���� ���ó�ʼ������������һ�֣�Ȼ�������ǰ���棬��Ӧsum���м�һ)
            �л����(�޸�flagֵ)

           �ж���Ϸ�Ƿ���������ú���Win())
           ����sum1/sum2�Ƿ�ﵽ��Ӧ������
           ��ת���������
        }
    ����: void
    ����ֵ: void
*/
void gameView(); 

/*
  ������:����
    ����: ��������������
           map[x][y] = (flag % 2 == 0) ? 1 : 2;
           ���ݾֺ����ж�������
     ����: int
    ����ֵ: void
*/
void replayerMove(int x, int y);

/*
    ������:Ҷ��/̹��
    int userChoose = 0;//0Ϊ�򵥣�1Ϊ��ͨ��2Ϊ����
    system("cls")
    while (1) {
    �����Ѷȣ��򵥣���ͨ������
    ����switch���}
    ����: void
    ����ֵ: void
*/
void DifficultyChoice();
// --------------------------------------------- v i e w ------------------------------------------------


// ��������, ������ƶ���ָ������
void gotoXY(int x, int y)
{
    COORD c;
    c.X = x - 1;
    c.Y = y - 1;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), c);
}

//�̶���������
void clear(int x, int y, int w, int h)
{
    for (int i = 0; i < h; i++) {
        gotoXY(x, y + i);
        for (int j = 0; j < w; j++) putchar(' ');
    }
}

//ʹ�ò�ͬ��ɫ
void setPrintColor(int color) {

    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);

}

//���ò�ͬ��ɫ
void resetPrintColor(int color) {

    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);

}



//��Ϸ��ʼ��
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

//�˵�����
void menuView() {
    
   
    int userChoose = 0;
    while (1)
    {
        if (f)
        {
            mciSendString("stop bgm0", NULL, 0, NULL);
        }
        //����bgm
        else {
            mciSendString("open ��ũ(������ٰ�).mp3 alias bgm0", NULL, 0, NULL);
            mciSendString("play bgm0  repeat", NULL, 0, NULL);
            mciSendString("setaudio bgm0 volume to 200", NULL, 0, NULL);
        }
        setPrintColor(0x0f);
        gotoXY(52, 3);
        printf("��  ��  ��  ��  ��");

        setPrintColor(userChoose == 0 ? 0x6f : 0x0f);
        gotoXY(57, 9);
        printf("��ʼ��Ϸ");

        setPrintColor(userChoose == 1 ? 0x6f : 0x0f);
        gotoXY(57, 13);
        printf("��Ϸ����");

        setPrintColor(userChoose == 2 ? 0x6f : 0x0f);
        gotoXY(57, 17);
        printf("������Ա");

        setPrintColor(userChoose == 3 ? 0x6f : 0x0f);
        gotoXY(57, 21);
        printf("�淨����");

        setPrintColor(userChoose == 4 ? 0x6f : 0x0f);
        gotoXY(57, 25);
        printf("�˳���Ϸ");
        setPrintColor(0x0f);


        char input = _getch();//����

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
                //������Ϸ����
                gameView();

            case 1:
                system("cls");
                //�������ý���
                game_settings();

            case 2:
                system("cls");
                //���뿪����Ա����
                developer();

            case 3:
                system("cls");
                //������Ϸ�淨����
                playing_method();

            case 4:
                system("pause");
                //�˳���Ϸ
                exit(0);
            }
            break;
        }
    }


}

//��Ϸ���ý���
void game_settings() {

    int userChoose = 0;

    system("cls");

    while (1) {



        resetPrintColor(0x0f); // Ĭ����ɫ  
        gotoXY(57, 3);
        printf(" ��  �� ");

        setPrintColor(userChoose == 0 ? 0x6f : 0x0f);
        gotoXY(55, 9);
        printf("��Ϸ��bgm����");

        setPrintColor(userChoose == 1 ? 0x6f : 0x0f);
        gotoXY(57, 15);
        printf("��ɫѡ��");

        setPrintColor(userChoose == 2 ? 0x6f : 0x0f);
        gotoXY(57, 21);
        printf("�Ѷ�ѡ��");

        setPrintColor(userChoose == 3? 0x6f : 0x0f);
        gotoXY(59, 27);
        printf("����");
        resetPrintColor(0x0f);

        char input = _getch();//��������


        switch (input) {
        case 'w':
            userChoose = (userChoose - 1 + 4) % 4; // ѭ��ѡ��  
            break;
        case 's':
            userChoose = (userChoose + 1) % 4;
            break;
        case '\r':
            switch (userChoose) {
            case 0:
                system("cls");
                //��������ѡ�����
                game_music();
                break;
            case 1:
                system("cls");
                //������ɫѡ�����
                game_color();
                break;
            case 2:
                system("cls");
                //�����Ѷ�ѡ�����
                DifficultyChoice();
            case 3:
                system("cls");
                //����˵�����
                menuView();
            }
            break;
        }


    }


}

//��Ϸ�淨����
void playing_method()
{
    int userChoose = 0;
    while (1)
    {
        //��ӡ����
        setPrintColor(0x0f);
        gotoXY(54, 3);
        printf("�� �� �� ��");

        gotoXY(47, 8);
        printf("�������꣬���ӳ�����ָ��λ��");

        gotoXY(44, 11);
        printf("��ͬ��ɫ���������������ж�һ��Сʤ��");

        gotoXY(47, 14);
        printf("����������������ӻᱻ����");

        gotoXY(41, 17);
        printf("��ȥ���Ӵﵽ���������ж���ȫʤ������Ϸ������");

        gotoXY(29, 20);
        printf("�����ض����꣬����ת�����ֲʵ�ҳ�棬����һ�����֣�����ת����Ϸҳ��");

        gotoXY(38, 23);
        printf("������ʾ����������󣬰�j�����壬��Enter������");

        setPrintColor(userChoose == 0 ? 0x6f : 0x0f);
        gotoXY(56, 25);
        printf("��������");

        setPrintColor(0x0f);

        //�����û�����
        char input = _getch();

        //�ж��Ƿ�س�
        switch (input) {
        case '\r':
            system("cls");
            switch (userChoose)
            {
            case 0:
                //���ز˵�����
                menuView();
                break;
            }
            break;
        }
    }

}

//��Ϸ������Ա����
void developer() {

    int userChoose = 0;
    while (1)
    {
        //��ӡ����
        setPrintColor(0x0f);
        gotoXY(54, 3);
        printf("��  ��  ��  Ա");
        gotoXY(56, 7);
        printf("����Сѧ��");
        gotoXY(48, 10);
        printf("Ҷ��                 Aurora ");

        gotoXY(48, 12);
        printf("���                 ���Ӵ���");

        gotoXY(48, 14);
        printf("����                 ���ķ���");

        gotoXY(48, 16);
        printf("̹��                Y U U O ");

        gotoXY(48, 18);
        printf("��ľ                �� �� ��");

        setPrintColor(userChoose == 0 ? 0x6f : 0x0f);
        gotoXY(56, 25);
        printf("��������");

        setPrintColor(0x0f);

        //�����û�����
        char input = _getch();

        //�ж��Ƿ�س�
        switch (input) {
        case '\r':
            system("cls");
            switch (userChoose)
            {
            case 0:
                //���ز˵�����
                menuView();
                break;
            }
            break;
        }
    }





}

//�Ѷ�ѡ�����
void DifficultyChoice() {
    int userChoose = 0;


    system("cls");

    while (1) {



        resetPrintColor(0x0f); // Ĭ����ɫ  
        gotoXY(55, 3);
        printf(" �� �� ѡ �� ");

        setPrintColor(userChoose == 0 ? 0x6f : 0x0f);
        gotoXY(59, 9);
        printf("��");

        setPrintColor(userChoose == 1 ? 0x6f : 0x0f);
        gotoXY(59, 14);
        printf("��ͨ");

        setPrintColor(userChoose == 2 ? 0x6f : 0x0f);
        gotoXY(59, 19);
        printf("����");

        setPrintColor(userChoose == 3 ? 0x6f : 0x0f);
        gotoXY(59, 24);
        printf("����");

        resetPrintColor(0x0f);



        char input = _getch();


        switch (input) {
        case 'w':
            userChoose = (userChoose - 1 + 4) % 4; // ѭ��ѡ��  
            break;
        case 's':
            userChoose = (userChoose + 1) % 4;
            break;
        case '\r':
            if (userChoose != 3) {
                gotoXY(54, 22);
                resetPrintColor(0x6);
                printf("!!!ѡ��ɹ�!!!");
            }
            switch (userChoose) {
            case 0:
                count = 1;//�򵥣�������ʤ��
                break;
            case 1:
                count = 2;//��ͨ����ʮ��ʤ��
                break;
            case 2:
                count = 3;//���ѣ���ʮ����ʤ��
                break;
            case 3:
                system("cls");
                //���ز˵�����
                game_settings();
            }
            break;
        }


    }


}

//���ֲ���ѡ��
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
        mciSendString("open �j̤���W��ν�.mp3 alias bgm2", NULL, 0, NULL);
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
        mciSendString("open �÷������.mp3 alias bgm4", NULL, 0, NULL);
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
        mciSendString("open ����ɱ.mp3 alias bgm6", NULL, 0, NULL);
        mciSendString("play bgm6 repeat", NULL, 0, NULL);
        mciSendString("setaudio bgm6 volume to 100", NULL, 0, NULL);/////
        f++;
        break;

    case 7:
        stopMusic();
        mciSendString("open �ե�ե�ե���衢�餭����.mp3 alias bgm7", NULL, 0, NULL);
        mciSendString("play bgm7 repeat", NULL, 0, NULL);
        mciSendString("setaudio bgm7 volume to 200", NULL, 0, NULL);
        f++;
        break;

    case 8:
        stopMusic();
        mciSendString("open ���ֶ�����.mp3 alias bgm8", NULL, 0, NULL);
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

//����ѡ�����
void game_music() {
    mciSendString("stop bgm0", NULL, 0, NULL);
    int UserChoose = 0;
    system("cls");
    while (1) {
        resetPrintColor(0x0f);
        gotoXY(60, 1);
        printf("BGM����");


        setPrintColor(UserChoose == 0 ? 0x6f : 0x0f);
        gotoXY(48, 7);
        printf("CrazyDave");

        setPrintColor(UserChoose == 1 ? 0x6f : 0x0f);
        gotoXY(48, 11);
        printf("Experience");

        setPrintColor(UserChoose == 2 ? 0x6f : 0x0f);
        gotoXY(46, 15);
        printf("�j̤���W��ν�");

        setPrintColor(UserChoose == 3 ? 0x6f : 0x0f);
        gotoXY(46, 19);
        printf("Unwelcome school");

        setPrintColor(UserChoose == 4 ? 0x6f : 0x0f);
        gotoXY(48, 23);
        printf("�÷������");

        setPrintColor(UserChoose == 5 ? 0x6f : 0x0f);
        gotoXY(68, 7);
        printf("RED OUT");

        setPrintColor(UserChoose == 6 ? 0x6f : 0x0f);
        gotoXY(68, 11);
        printf("����ɱ");

        setPrintColor(UserChoose == 7 ? 0x6f : 0x0f);
        gotoXY(68, 15);
        printf("�ե�ե�ե���衢�餭����");

        setPrintColor(UserChoose == 8 ? 0x6f : 0x0f);
        gotoXY(68, 19);
        printf("���ֶ�����");

        setPrintColor(UserChoose == 9 ? 0x6f : 0x0f);
        gotoXY(68, 23);
        printf("CornfieldChase");

        setPrintColor(UserChoose == 10 ? 0x6f : 0x0f);
        gotoXY(56, 27);
        printf("ֹͣ��������");

        setPrintColor(UserChoose == 11 ? 0x6f : 0x0f);
        gotoXY(60, 30);
        printf("����");


        char input = _getch();//��������

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
                printf("!!!ѡ��ɹ�!!!");
            }
            
            else {
                gotoXY(55, 28);
                resetPrintColor(0x6);
                printf("   ȡ��ѡ��   ");

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
                stopMusic();//ֹͣ��������
                break;

            case 11://������һ������;
                setPrintColor(0x0f);
                //�ص����ý���
                game_settings();

                break;


            }
            break;


        }


    }








}

// ֹͣ����ָ������
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


//ѡ���ͼ��ɫ
void setmapColor(int color) {
  
    switch (mapColor) {
    case 0: printf("\033[1;31m"); break; // red
    case 1: printf("\033[1;34m"); break; // Blue
    case 2: printf("\033[1;32m"); break; // Green
    case 3: printf("\033[1;33m"); break; // yellow
    case 4: printf("\033[1;37m"); break; // white
    }


}

//ѡ��߿���ʾ��ɫ
void setborderColor(int color) {
   
    switch (borderColor) {
    case 0: printf("\033[1;31m"); break; // red
    case 1: printf("\033[1;35m"); break; // purple
    case 2: printf("\033[1;36m"); break; // lightGreen
    case 3: printf("\033[1;33m"); break; // yellow
    case 4: printf("\033[1;37m"); break; // white
    }



}

//��ɫѡ�����
void game_color() {

    int userChooseSection = 0; // 0: ��ͼ��ɫѡ�� 1: �߿���ɫѡ�� 2��
    int userChooseColor1 = 0;   // ��ͼ��ɫ  0����ɫ 1����ɫ 2����ɫ 3����ɫ
    int userChooseColor2 = 0;   // �߿���ɫ  0����ɫ 1����ɫ 2����ɫ 3����ɫ
    int userChooseColor3 = 0;   // 0:ȷ�� 1������ 2������

    system("cls");

    while (1) {

        setPrintColor(0x0f);// Ĭ����ɫ  
        gotoXY(55, 3);
        printf("�� ɫ ѡ ��");

        setPrintColor(0x0f);
        gotoXY(10, 9);
        printf("��ͼ��ɫѡ��: ");

        setPrintColor(0x0f);
        gotoXY(10, 15);
        printf("�߿���ɫѡ��: ");


        // ���ݵ�ǰѡ��������ɫ
        for (int i = 0; i < 4; i++) {
            int colorCode = (userChooseSection == 0 && userChooseColor1 == i) ? 0x6f : 0x0f;
            setPrintColor(colorCode);
            gotoXY(38 + i * 20, 9);
            printf("%s", (i == 0) ? "��ɫ" : (i == 1) ? "��ɫ" : (i == 2) ? "��ɫ" : "��ɫ");

            colorCode = (userChooseSection == 1 && userChooseColor2 == i) ? 0x6f : 0x0f;
            setPrintColor(colorCode);
            gotoXY(38 + i * 20, 15);
            printf("%s", (i == 0) ? "��ɫ" : (i == 1) ? "��ɫ" : (i == 2) ? "��ɫ" : "��ɫ");


        }

        for (int i = 0; i < 3; i++) {
            int colorCode = (userChooseSection == 2 && userChooseColor3 == i) ? 0x6f : 0x0f;
            setPrintColor(colorCode);
            gotoXY(41 + i * 20, 25);
            printf("%s", (i == 0) ? "ȷ��" : (i == 1) ? "����" : "����");
        }


        // ��ȡ�û�����  
        char input = _getch();

        // ��������  
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
            if (userChooseSection == 0) {//ѡ���ͼ��ɫ
                gotoXY(10, 11);
                resetPrintColor(0x6);
                printf("��ͼ��ɫ��ѡ��: ");
                printf("%s", (userChooseColor1 == 0) ? "��ɫ" : (userChooseColor1 == 1) ? "��ɫ" : (userChooseColor1 == 2) ? "��ɫ" : "��ɫ");

            }
            else if (userChooseSection == 1) {//ѡ��߿���ʾ��ɫ
                gotoXY(10, 17);
                resetPrintColor(0x6);
                printf("�߿���ɫ��ѡ��: ");
                printf("%s", (userChooseColor2 == 0) ? "��ɫ" : (userChooseColor2 == 1) ? "��ɫ" : (userChooseColor2 == 2) ? "��ɫ" : "��ɫ");

            }
            else if (userChooseSection == 2) {//ѡ�� ȷ�� ���ã�Ĭ�ϵ�ͼ�߿���ɫΪ�ף� ����
                if (userChooseColor3 == 0) {
                    gotoXY(57, 22);
                    resetPrintColor(0x6);
                    printf("!!!ѡ��ɹ�!!!");
                    mapColor = userChooseColor1;
                    borderColor = userChooseColor2;
                }
                else if (userChooseColor3 == 1) {
                    system("cls");
                    //���ó�ʼ��ɫ
                    mapColor = 4;
                    borderColor = 4;

                }
                else if (userChooseColor3 == 2) {
                    setPrintColor(0x0f);
                    //�ص����ý���
                    game_settings();
                }


            }
            break;
        default:
            break;
        }



    }


}
//��Ϸ������ʾ���߿��ӡ
void printBox(int x, int y, int w, int h)
{
    //������
    for (int i = 0; i < h; i++) {
        gotoXY(x, y + i);
        putchar('#');
    }
    //������
    for (int i = 0; i < h; i++) {
        gotoXY(x + w, y + i);
        putchar('#');
    }
    //�Ϻ���   
    gotoXY(x, y);
    for (int i = 0; i < w; i++) {
        putchar(' #');
    }
    //�º�
    for (int i = 0; i <= w; i++) {
        gotoXY(x + i, y + h);
        putchar(' #');

    }
}
//��ͼ����ʾ�߿��ӡ
void gameView_ShowMap() {
    // ��ӡ��ʾ�߿�
    setborderColor(borderColor);//Ӧ�ñ߿���ɫ
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

    //��ӡ��ͼ
    setmapColor(mapColor);//Ӧ�õ�ͼ��ɫ
    for (int i = 0; i < 15; i++) {
        setmapColor(mapColor);
        gotoXY(15, 2 + 2 * i);
        for (int j = 0; j < 15; j++) {
            setmapColor(mapColor);
            if (map[i][j] == 0) {
                printf(" ʮ ");
            }
            else if (map[i][j] == 1) {
                printf(" \x1b[90;100m��\x1b[0m ");//����
            }
            else if (map[i][j] == 2) {
                printf(" \x1b[97;107m��\x1b[0m ");//����

            }
        }
        if (i != 14)
            printf("\n");

    }

}


//��Ϸ����
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
        printf("���س�����\n");

        setPrintColor(0x0f);
        printBox(100, 1, 14, 2);
        gotoXY(103, 2);
        printf("��j������\n");

        setPrintColor(0x0f);
        printBox(82, 4, 28, 2);
        gotoXY(84, 5);
        printf("���������k���������˵�\n");

        setPrintColor(0x0f);
        printBox(98, 19,17, 4);
        gotoXY(100, 20);
        printf("�ڷ�ʤ������:%d",sum1);
        gotoXY(100, 22);
        printf("�׷�ʤ������:%d", sum2);

        setPrintColor(0x0f);
        printBox(98,26,17,4);
        gotoXY(100, 28);
        printf("Ҫ��ʤ������:%d", count);


        setPrintColor(0x0f);
        gotoXY(80, 8);
        printf("���%s�������������꣺\n", (flag % 2 == 0) ? "һ" : "��");
        gotoXY(80, 9);
   
        gotoXY(102, 8);
        int rusult=scanf_s("%d %d", &x, &y);//������������
 
        while (getchar() != '\n');

        x--;//map����
        y--;//map����
        if (rusult!=2||x<0||x>=15||y<0||y>=15) {
            gotoXY(80, 14);
            setPrintColor(0x60);
            printf("��Ч����\n");
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
            printf("��λ���ѱ�ռ��\n");
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
        printf("���س�����\n");

        setPrintColor(0x0f);
        printBox(100, 1, 14, 2);
        gotoXY(103, 2);
        printf("��j������\n");

        setPrintColor(0x0f);
        printBox(82, 4, 28, 2);
        gotoXY(84, 5);
        printf("���������k���������˵�\n");

        setPrintColor(0x0f);
        printBox(98, 19, 17, 4);
        gotoXY(100, 20);
        printf("�ڷ�ʤ������:%d", sum1);
        gotoXY(100, 22);
        printf("�׷�ʤ������:%d", sum2);

        setPrintColor(0x0f);
        printBox(98, 26, 17, 4);
        gotoXY(100, 28);
        printf("Ҫ��ʤ������:%d", count);
        setPrintColor(0x0f);
        gotoXY(80, 9);
        printf("����j��k���������ʼ��һ�������");
        gotoXY(122, 9);
        char input = _getch();
        switch (input)
        {
        case 'j'://����
            map[x][y] = 0;
            regret();
            while (s != 0)
            {
                gameView_ShowMap();
                setPrintColor(0x0f);
                printBox(90, 1, 14, 2);
                gotoXY(93, 2);
                printf("���س�����\n");
                setPrintColor(0x0f);
                printBox(98, 19, 17, 4);
                gotoXY(100, 20);
                printf("�ڷ�ʤ������:%d", sum1);
                gotoXY(100, 22);
                printf("�׷�ʤ������:%d", sum2);

                setPrintColor(0x0f);
                printBox(98, 26, 17, 4);
                gotoXY(100, 28);
                printf("Ҫ��ʤ������:%d", count);
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
           //����ʤ������
            winView();
            return;
        }

        flag++;
        system("cls");
    }
        
        
      
        
    
}

//����
int  playerMove(int x, int y) {
    if (map[x][y] == 0)
    {

        if (flag % 2 == 0)
        {
            map[x][y] = 1;//����
        }
        else if (flag % 2 == 1)
        {
            map[x][y] = 2;//����
        }
        return 1;

    }
    return 0;
}

//����
void regret()
{

    int x1, y1;
    gotoXY(80, 10);
    printf("�����������x,y����: ");
    gotoXY(102, 10);
    
    int rusult =scanf_s("%d %d", &x1, &y1);

    while (getchar() != '\n');

    x1--; y1--;
    if (rusult != 2 || x1 < 0 || x1 >= 15 || y1 < 0 || y1 >= 15) {
        gotoXY(80, 14);
        setPrintColor(0x60);
        printf("��Ч����\n");
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
        printf("λ���ѱ�ռ��\n");
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


//�������������
void replayerMove(int x, int y)
{
    map[x][y] = (flag % 2 == 0) ? 1 : 2;
}

//ʤ���ж�
void isWin(int x, int y) {
    int count1 = 0;
    int color = map[x][y];

    //  �����ж�
    for (int i = 0; i < 13; i++) {

        //    Խ���ж�
        if ((y - 6 + i) < 0) {//���
            continue;//���� ������һ��
        }
        else if ((y - 6 + i) > 14) {//�յ�
            break;//��ʱ�������������
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

    // �����ж�
    for (int i = 0; i < 13; i++) {

        //   Խ���ж�
        if ((x - 6 + i) < 0) {
            continue;//���� ������һ��
        }
        else if ((x - 6 + i) > 14) {
            break;//��ʱ�������������
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



    //      '/'���ж�
    for (int i = 0; i < 13; i++) {

        //           Խ���ж�
        if ((x + 6 - i) > 14 || (y - 6 + i) < 0) {
            continue;//���� ������һ��
        }
        else if ((x + 6 - i) < 0 || (y - 6 + i) > 14) {
            break;//��ʱ�������������
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

    // '\'���ж�
    for (int i = 0; i < 13; i++) {

        //      Խ���ж�
        if ((x - 6 + i) < 0 || (y - 6 + i) < 0) {
            continue;//���� ������һ��
        }
        else if ((x - 6 + i) > 14 || (y - 6 + i) > 14) {
            break;//��ʱ�������������
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


//�ʵ�����
void SurpriseEgg(int x, int y) {
    if (x == 3 && y == 3) {
        system("cls");
        gotoXY(52, 7);
        setPrintColor(0x60);
        printf("����ϲ�㴥���ʵ���");
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
        printf("����ϲ�㴥���ʵ���");
        gotoXY(49, 12);
        setPrintColor(0x0e);
        printf("��ϲ�㴥������Ľ�֡�������");
        gotoXY(53, 15);
        system("pause");
    }
    else if (x == 7 && y == 9) {
        system("cls");
        gotoXY(52, 7);
        setPrintColor(0x60);
        printf("����ϲ�㴥���ʵ���");
        setPrintColor(0x0f);
        gotoXY(50, 12);
        printf("�����������Ѿ�������׼��");
        gotoXY(56, 14);
        printf("���������");
        gotoXY(56, 16);
        printf("����������");
        gotoXY(51, 18);
        printf("Ը���Ϊ��ִ��֮��");
        gotoXY(54, 22);
        system("pause");

    }
    else if (x == 12 && y == 5) {
        system("cls");
        gotoXY(52, 7);
        setPrintColor(0x60);
        printf("����ϲ�㴥���ʵ���");
        gotoXY(49, 12);
        setPrintColor(0x0c);
        printf("�һ���Զ�����㡭��Զ��Զ��");
        gotoXY(53, 15);
        system("pause");
    }
    else if (x == 2 && y == 9) {
        system("cls");
        gotoXY(52, 7);
        setPrintColor(0x60);
        printf("����ϲ�㴥���ʵ���");
        gotoXY(53, 12);
        setPrintColor(0x0e);
        printf("v��50������ʵ��");
        gotoXY(53, 16);
        system("pause");
    }
    else if (x == 14 && y == 13) {
        system("cls");
        gotoXY(52, 7);
        setPrintColor(0x60);
        printf("����ϲ�㴥���ʵ���");
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
        printf("����ϲ�㴥���ʵ���");
        gotoXY(51, 12);
        setPrintColor(0x09);
        printf("��֪ʶ���Ʊ�û���������ʼ��");
        gotoXY(53, 17);
        system("pause");
    }
    else if (x == 14 && y == 2) {
        system("cls");
        gotoXY(52, 7);
        setPrintColor(0x60);
        printf("����ϲ�㴥���ʵ���");
        gotoXY(55, 12);
        setPrintColor(0x0a);
        printf("�������Ȼ�");
        gotoXY(53, 15);
        system("pause");
    }
    else if (x == 9 && y == 9) {
        system("cls");
        gotoXY(52, 7);
        setPrintColor(0x60);
        printf("����ϲ�㴥���ʵ���");
        gotoXY(40, 12);
        setPrintColor(0x0d);
        printf("ÿ��һ�ʣ�����������������嶥�弦����");
        gotoXY(52, 15);
        system("pause");
    }




}

//ʤ������
void winView() {
    int userChoose = 0;
    while (1) {
        // ----------------- ��ӡ���� -----------------

        if (sum1 == count)
        {
            gotoXY(52, 3);
            setPrintColor(0x6);
            printf("��  ��  ʤ  ��");
            setPrintColor(0x0f);

        }
        else if (sum2 == count)
        {
            gotoXY(52, 3);
            setPrintColor(0x6);
            printf("��  ��  ʤ  ��");
            setPrintColor(0x0f);
        }
        if (userChoose == 0) setPrintColor(0x6f);
        gotoXY(55, 9);
        printf("����һ��");
        if (userChoose == 0) setPrintColor(0x0f);

        if (userChoose == 1) setPrintColor(0x6f);
        gotoXY(54, 15);
        printf("�������˵�");
        if (userChoose == 1) setPrintColor(0x0f);

        if (userChoose == 2) setPrintColor(0x6f);
        gotoXY(55, 21);
        printf("�˳���Ϸ");
        if (userChoose == 2) setPrintColor(0x0f);

        if (userChoose == 3) setPrintColor(0x6f);


        // ---------------- �����û����� --------------
        char input = _getch();

        // -------------�ж��Ƿ������»��ǻس�------------
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
                //������Ϸ����
                gameView();
                break;
            case 1:
                //ֹͣ��������
                // �������˵�
                stopMusic();
                f = 0;
                menuView();
                break;
            case 2:
                //�˳�
                exit(0);;
                break;

            }

            break;
        }
    }

}




//���������
int main() {
    //���ò˵�����
    menuView();
    return 0;
}

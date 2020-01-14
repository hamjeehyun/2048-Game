#include <stdio.h>
#include <time.h>
#include <conio.h>
#include <windows.h>
#include <string.h>

#define LEFT 75
#define RIGHT 77
#define UP 72
#define DOWN 80

#define BLACK   0
#define BLUE1   1//2
#define GREEN1   2//4
#define CYAN1   3//8
#define RED1   4//16
#define MAGENTA1 5//32
#define YELLOW1   6//64
#define GRAY2   8//128
#define WHITE   15//256
#define BLUE2   9//512
#define GREEN2   10//1024
#define CYAN2   11//2048
#define RED2   12//4096
#define MAGENTA2   13//8192
#define YELLOW2   14//16384

#pragma comment (lib,"winmm.lib")

typedef struct Rankk{
   char name[100];
   int score;
}rank;

void textcolor(int color_number);
void ul();
void gotoxy(int x, int y);
void game_start(int map[][17]);
void game_print_1p(int map[][17]);
void game_print_2p(int map[][17]);
void number_print_1p(int arr[][4], int score);
void number_print_2p(int arr[][4], int score, int player);
void create(int arr[][4]);
int create_check_1p(int arr[][4]);
int create_check_2p(int arr[][4],int player) ;
int dmove_1p(int arr[][4], int d, int *score);
int dmove_2p(int arr[][4], int d, int *score1,int *score2,int player);
int *arr_tc_1p(int arr[][4], int i, int j, int d);
int *arr_tc_2p(int arr[][4], int i, int j, int d, int player);
void game_over_1p(int *score);
void game_over_2p(int *score1,int *score2, int player) ;
void RankP();
void Music_opening();
void Music_ending_1p();
void Music_ending_2p();
void Click();
void Bubble(rank *board, rank temp);
void RankRe();
void EndG();

rank Rank[11];
void main() {

   int map[17][17];
   int key;  int select;
   RankRe();
START:
   Music_opening();
   ul();
   gotoxy(9,8);printf("player인원수를 입력하시오(1/2)>>");
   scanf("%d", &select);
   game_start(map);//map초기화
   while (1) {//게임 종료시 다시 시작
      int score0 = 100, score1 = 100,score2 = 100, input;
      int arr0[4][4] = { 0, 2, 2 ,};
      int arr1[4][4] = { 0, 2, 2 ,};
      int arr2[4][4] = { 0, 2, 2 ,};

      system("cls");//map을 새로그림

      switch(select) {
      case 1: {
         game_print_1p(map);//map을 draw함
         while (1) {//조작
            if (kbhit()) {
               Click();//입력버퍼에 값이 있을경우
               if (getch() == 224) {//224: 방향키 아스키코드
                  switch (getch()) {//방향키를 입력받음
                  case LEFT:  input = 1; break;
                  case UP:    input = 2; break;
                  case RIGHT: input = 3; break;
                  case DOWN:  input = 4; break;
                  }
                  //더이상 움직일 수없고 배열이 꽉참 -> 게임 오버 -> 게임 재시작
                  if (dmove_1p(arr0, input, &score0)) break; //방향키 이동
               }
               number_print_1p(arr0, score0);//프린트 갱신
            }
         }
         goto START;
            } break;
      case 2: {
         game_print_2p(map);//map을 draw함
         while (1) {//조작
            if (kbhit()) {  
               Click();//입력버퍼에 값이 있을경우 소리.
               key=getch();
               if (key==224) {//224: 방향키 아스키코드 // 확장키 입력확인
                  key=getch(); // 2바이트니까 한번더
                  switch (key) {//방향키를 입력받음
                  case LEFT:  input = 1; break;
                  case UP:    input = 2; break;
                  case RIGHT: input = 3; break;
                  case DOWN:  input = 4; break;
                  }
                  //더이상 움직일 수없고 배열이 꽉참 -> 게임 오버 -> 게임 재시작
                  if (dmove_2p(arr1, input, &score1,&score2, 1)) break; //방향키 이동
               }
               else {
                  switch(key){
                  case 'a': input = 1; break;
                  case 'w': input = 2; break;
                  case 'd': input = 3; break;
                  case 's': input = 4; break;
                  default:break;
                  }
                  if(dmove_2p(arr2, input, &score2, &score1, 2)) break;
               }
               number_print_2p(arr1, score1, 1);//프린트 갱신
               number_print_2p(arr2, score2, 2);//프린트 갱신
            }

         }
         default:goto START;
            } break;
      }
      
   }
}
void textcolor(int color_number){ //텍스트 칼라 바꿔주는 함수
   SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),color_number);
}
void ul(){
   int i;
   textcolor(GREEN1);
   gotoxy(5,11);printf("⊂ _                     ⊂ _ \n");
   gotoxy(5,12);printf("  ＼＼ Λ＿Λ　　　　  　　＼＼ Λ＿Λ\n");
   gotoxy(5,13);printf("    ＼(‘ㅅ' )       　  　  ＼(‘ㅅ' ) \n");
   gotoxy(5,14);printf("      >　⌒ 、　　　　　　　 　>　⌒ 、\n");
   gotoxy(5,15);printf("     / 　 へ＼　　　　　　　　/ 　 へ＼\n");
   gotoxy(5,16);printf("    /　　/　＼＼　　　　　 　/　　/　＼＼\n");
   gotoxy(5,17);printf("   ｜　ノ　　 ＼_つ　　　   ｜ 　ノ　  ＼_つ\n");
   gotoxy(5,18);printf("   /　/｜　　　　　　　　　 /　/｜\n");
   gotoxy(5,19);printf("  (　(｀　　　　　　　　　 (　(｀\n");
   gotoxy(5,20);printf("  |　|、＼　　　　　　　　 |　|、＼\n");
   gotoxy(5,21);printf("　| 〃 ＼ ⌒)　　　　 　　 | 〃 ＼ ⌒)\n");
   gotoxy(5,22);printf("  | |　　) / 　　　　　　　| |　　) /\n");
   gotoxy(5,23);printf("`ノ )　　L/　　　　　　　`ノ )　　L/\n");
   textcolor(WHITE);
   gotoxy(5,2); printf("--------------------------------------------");
   for(i=3;i<10;i++){
      gotoxy(5,i); printf("-");
      gotoxy(26,i);printf("-");
   }
   gotoxy(5,10);printf("-------------------------------------------");
   textcolor(RED2);
   gotoxy(13, 5); printf("2048 GAME");
   textcolor(YELLOW2);
   gotoxy(10, 6); printf(" 프로그래밍 랩 프로젝트");
   textcolor(WHITE);
   gotoxy(10, 7); printf("  서은정,안지웅,함지현");
}
//프린트할 위치
//x의 좌표범위 0~78, y의 좌표범위 0~23
void gotoxy(int x, int y) {
   COORD Pos = { x * 2, y };
   SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), Pos);
}
//맵을 초기화함
void game_start(int map[][17]) {
   int arr_temp[17][17] = {
      { 11, 1, 1, 1, 22, 1, 1, 1, 22, 1, 1, 1, 22, 1, 1, 1, 12 },
      { 2, 0, 0, 0, 2, 0, 0, 0, 2, 0, 0, 0, 2, 0, 0, 0, 2 },
      { 2, 5, 4, 4, 2, 5, 4, 4, 2, 5, 4, 4, 2, 5, 4, 4, 2 },
      { 2, 0, 0, 0, 2, 0, 0, 0, 2, 0, 0, 0, 2, 0, 0, 0, 2 },
      { 21, 1, 1, 1, 3, 1, 1, 1, 3, 1, 1, 1, 3, 1, 1, 1, 23 },
      { 2, 0, 0, 0, 2, 0, 0, 0, 2, 0, 0, 0, 2, 0, 0, 0, 2 },
      { 2, 5, 4, 4, 2, 5, 4, 4, 2, 5, 4, 4, 2, 5, 4, 4, 2 },
      { 2, 0, 0, 0, 2, 0, 0, 0, 2, 0, 0, 0, 2, 0, 0, 0, 2 },
      { 21, 1, 1, 1, 3, 1, 1, 1, 3, 1, 1, 1, 3, 1, 1, 1, 23 },
      { 2, 0, 0, 0, 2, 0, 0, 0, 2, 0, 0, 0, 2, 0, 0, 0, 2 },
      { 2, 5, 4, 4, 2, 5, 4, 4, 2, 5, 4, 4, 2, 5, 4, 4, 2 },
      { 2, 0, 0, 0, 2, 0, 0, 0, 2, 0, 0, 0, 2, 0, 0, 0, 2 },
      { 21, 1, 1, 1, 3, 1, 1, 1, 3, 1, 1, 1, 3, 1, 1, 1, 23 },
      { 2, 0, 0, 0, 2, 0, 0, 0, 2, 0, 0, 0, 2, 0, 0, 0, 2 },
      { 2, 5, 4, 4, 2, 5, 4, 4, 2, 5, 4, 4, 2, 5, 4, 4, 2 },
      { 2, 0, 0, 0, 2, 0, 0, 0, 2, 0, 0, 0, 2, 0, 0, 0, 2 },
      { 14, 1, 1, 1, 24, 1, 1, 1, 24, 1, 1, 1, 24, 1, 1, 1, 13 }
   };
   int i, j;
   for (i = 0; i < 17; i++)
      for (j = 0; j < 17; j++)
         map[i][j] = arr_temp[i][j];
}
//맵을 프린트함-한명
void game_print_1p(int map[][17]) {
   int i = 0, j = 0;
   //printf(" ");
   if(Rank[0].score!=0){
      gotoxy(1,1);printf("       HighScore : %d by %s",Rank[0].score,Rank[0].name);
   }
   else {
      gotoxy(1,1);printf("       HighScore : 100");
   }
   printf("\n\n      Score : %d\n\n", 100); //점수 현황
   for (i = 0; i < 17; i++){
      printf("      ");
      for ( j = 0; j < 17; j++){//맵 그리기
         switch (map[i][j]) {
         case 0: printf("  "); break;
         case 1: printf("─"); break;
         case 2: printf("│"); break;
         case 3: printf("┼"); break;
         case 5: printf("      ");break;
         case 11: printf("┌"); break;
         case 12: printf("┐"); break;
         case 13: printf("┘"); break;
         case 14: printf("└"); break;
         case 21: printf("├"); break;
         case 22: printf("┬"); break;
         case 23: printf("┤"); break;
         case 24: printf("┴"); break;
         }
      }
      printf("\n");
   }
   gotoxy(30,0);printf("프로그래밍 랩");
   gotoxy(20,5);printf("상하좌우 방향키를 이용해서");
   gotoxy(20,6);printf("숫자를 움직이세요.");
   gotoxy(20,7);printf("");
   gotoxy(20,8);printf("최대한 큰 수를 만들어보세요.");
   gotoxy(25,11);printf("⊂ _                     \n");
   gotoxy(25,12);printf("  ＼＼ Λ＿Λ　　　　  　\n");
   gotoxy(25,13);printf("    ＼(‘ㅅ' )       　 \n");
   gotoxy(25,14);printf("      >　⌒ 、　　　　　\n");
   gotoxy(25,15);printf("     / 　 へ＼　　　　　\n");
   gotoxy(25,16);printf("    /　　/　＼＼　　　　\n");
   gotoxy(25,17);printf("   ｜　ノ　　 ＼_つ　　\n");
   gotoxy(25,18);printf("   /　/｜　　　　　　　　\n");
   gotoxy(25,19);printf("  (　(｀　　　　　　　　\n");
   gotoxy(25,20);printf("  |　|、＼　　　　　　　\n");
   gotoxy(25,21);printf("　| 〃 ＼ ⌒)　　　　 　\n");
   gotoxy(25,22);printf("  | |　　) / 　　　　　\n");
   gotoxy(25,23);printf("`ノ )　　L/　　　　　　\n");
}
//맵프린트-두명
void game_print_2p(int map[][17]){
   int i = 0, j = 0;
      if(Rank[0].score!=0){
      gotoxy(16,0);printf("HighScore : %d by %s",Rank[0].score,Rank[0].name);
   }
   else {
      gotoxy(16,0);printf("HighScore : 100");
   }
   printf("\n        score : %d             score : 100\n\n", 100); //점수 현황
   for (i = 0; i < 17; i++){
      printf("      ");
      for ( j = 0; j < 17; j++){//맵 그리기
         switch (map[i][j]) {
         case 0: printf("  "); break;
         case 1: printf("─"); break;
         case 2: printf("│"); break;
         case 3: printf("┼"); break;
         case 5: printf("      ");break;
         case 11: printf("┌"); break;
         case 12: printf("┐"); break;
         case 13: printf("┘"); break;
         case 14: printf("└"); break;
         case 21: printf("├"); break;
         case 22: printf("┬"); break;
         case 23: printf("┤"); break;
         case 24: printf("┴"); break;
         }
      }
      printf("\n");
   }

   for (i = 0; i < 17; i++){
      printf("      ");
      for ( j = 0; j < 17; j++){//맵 그리기
         switch (map[i][j]) {
         case 0: gotoxy(20+j   ,i+3 );printf("  "); break;
         case 1: gotoxy(20+j  , i+3 );printf("─"); break;
         case 2: gotoxy(20 +j, i+3 );printf("│"); break;
         case 3: gotoxy(20  +j, i+3 );printf("┼"); break;
         case 5: gotoxy(20  +j, i +3);printf("      ");break;
         case 11: gotoxy(20 +j , i +3);printf("┌"); break;
         case 12: gotoxy(20 +j , i+3 );printf("┐"); break;
         case 13: gotoxy(20 +j , i +3);printf("┘"); break;
         case 14: gotoxy(20 +j , i+3 );printf("└"); break;
         case 21: gotoxy(20 +j , i +3);printf("├"); break;
         case 22: gotoxy(20 +j ,i+3);printf("┬"); break;
         case 23: gotoxy(20 +j ,i+3);printf("┤"); break;
         case 24: gotoxy(20 +j ,i+3);printf("┴"); break;
         }
      }
      printf("\n");
   
   }
   gotoxy(5,21);printf("Player 1 (방향키로 이동)");
   gotoxy(23,21);printf("Player 2 (wasd로 이동)");
}
//숫자를 프린트함-한명
void number_print_1p(int arr[][4], int score) {
   int i,j;
   gotoxy(12, 3);
   textcolor(WHITE);
   printf("%d", score);
   for(i=0;i<4;i++){ //4x4의 판에서 숫자가 나타나게 함
      for(j=0;j<4;j++){
         gotoxy(4+j*4, 6+i*4);
         switch(arr[i][j]){
         case 2: textcolor(WHITE);break;
         case 4: textcolor(GREEN1);break;
         case 8: textcolor(CYAN1);break;
         case 16: textcolor(RED1);break;
         case 32: textcolor(MAGENTA1);break;
         case 64: textcolor(YELLOW1);break;
         case 128: textcolor(GRAY2);break;
         case 256: textcolor(WHITE);break;
         case 512: textcolor(BLUE2);break;
         case 1024: textcolor(GREEN2);break;
         case 2048: textcolor(CYAN2);break;
         case 4096: textcolor(RED2);break;
         case 8192: textcolor(MAGENTA2);break;
         case 16384: textcolor(YELLOW2);break;
         }
         if (arr[i][j] != 0) {
            printf("%5d ", arr[i][j]);
         }
         else {
            printf("      ");
         }
      }
   }
}
//숫자 프린트 - 두명
void number_print_2p(int arr[][4], int score, int player) {
   int i,j;
   if(player==1){
      gotoxy(13, 1);
      textcolor(WHITE);
      printf("%d", score);
      for(i=0;i<4;i++){ //4x4의 판에서 숫자가 나타나게 함
         for(j=0;j<4;j++){
            gotoxy(4+j*4, 6+i*4);
            switch(arr[i][j]){ //숫자마다 색이 다르게 해줌
            case 2: textcolor(WHITE);break;
            case 4: textcolor(GREEN1);break;
            case 8: textcolor(CYAN1);break;
            case 16: textcolor(RED1);break;
            case 32: textcolor(MAGENTA1);break;
            case 64: textcolor(YELLOW1);break;
            case 128: textcolor(GRAY2);break;
            case 256: textcolor(WHITE);break;
            case 512: textcolor(BLUE2);break;
            case 1024: textcolor(GREEN2);break;
            case 2048: textcolor(CYAN2);break;
            case 4096: textcolor(RED2);break;
            case 8192: textcolor(MAGENTA2);break;
            case 16384: textcolor(YELLOW2);break;
            }
            if (arr[i][j] != 0) {
               printf("%5d ", arr[i][j]);
            }
            else {
               printf("      ");
            }
         }
      }
   }

   if(player==2){
      gotoxy(26,1);
      textcolor(WHITE);
      printf("score : %d", score);
      for(i=0;i<4;i++){ //4x4의 판에서 숫자가 나타나게 함
         for(j=0;j<4;j++){
            gotoxy(21+j*4,6+i*4);
            switch(arr[i][j]){ //숫자마다 색이 다르게 해줌
            case 2: textcolor(WHITE);break;
            case 4: textcolor(GREEN1);break;
            case 8: textcolor(CYAN1);break;
            case 16: textcolor(RED1);break;
            case 32: textcolor(MAGENTA1);break;
            case 64: textcolor(YELLOW1);break;
            case 128: textcolor(GRAY2);break;
            case 256: textcolor(WHITE);break;
            case 512: textcolor(BLUE2);break;
            case 1024: textcolor(GREEN2);break;
            case 2048: textcolor(CYAN2);break;
            case 4096: textcolor(RED2);break;
            case 8192: textcolor(MAGENTA2);break;
            case 16384: textcolor(YELLOW2);break;
            }
            if (arr[i][j] != 0) {
               printf("%5d ", arr[i][j]);
            }
            else {
               printf("      ");
            }
         }
      }
   }
}
//새로운 숫자 생성
void create(int arr[][4]) {
   int locate, number;
   srand((unsigned)(time(NULL)));//rand함수 랜덤설정
   if (rand() % 10 < 8) number = 2;//80퍼로 2생성
   else number = 4;// 20퍼로 4생성
   do{
      locate = rand() % 16;
   } 
   while (arr[locate / 4][locate % 4] != 0);//빈칸나올때까지 랜덤
   arr[locate / 4][locate % 4] = number;
}
//create가 가능한지 체크-한명
int create_check_1p(int arr[][4]) {
   int i, cnt = 0;
   for (i = 0; i < 16; i++) {
      if (arr[i / 4][i % 4] != 0)
         cnt++;
   }
   if (cnt == 16) return 0;//16칸의 배열이 꽉참 -> create불가
   else return 1;//creeate가능
}
//create가 가능한지 체크-두명
int create_check_2p(int arr[][4],int player) {
   int i, cnt = 0;
   for (i = 0; i < 16; i++) {
      if (arr[i / 4][i % 4] != 0)
         cnt++;
   }
   if (cnt == 16) return 0;//16칸의 배열이 꽉참 -> create불가
   else return 1;//creeate가능
}

//방향키이동-한명
int dmove_1p(int arr[][4], int d, int *score) {
   int i,j, s, check = 0;
   for (i = 0; i < 4; i++) {
      for (j = 0; j < 4; j++) {
         if (*arr_tc_1p(arr, i, j, d) != 0) {
            for (s = j + 1; s < 4; s++) {//뒤와 합치기
               if (*arr_tc_1p(arr, i, j, d) == *arr_tc_1p(arr, i, s, d)) {
                  *arr_tc_1p(arr, i, j, d) *= 2;
                  *arr_tc_1p(arr, i, s, d) = 0;
                  *score += *arr_tc_1p(arr, i, j, d);//점수 추가
                  check++;
                  break; 
               }
               else if (*arr_tc_1p(arr, i, s, d) != 0) break;//뒤에 합치지 못하면 종료
            }


            for (s = j - 1; s >= 0; s--) {//앞에 이동할수 있나 체크
               if (*arr_tc_1p(arr, i, s, d) != 0) {
                  break;
               }
            }
            s++;
            if (j != s) {//앞에 이동할수 있으면 정렬
               *arr_tc_1p(arr, i, s, d) = *arr_tc_1p(arr, i, j, d);
               *arr_tc_1p(arr, i, j, d) = 0;
               check++;
            }
         }

      }
   }
   // check == 0 -> 더 이상 움직일 수 없음 -> create 안함
   if (create_check_1p(arr)) {
      if (check != 0) {
         create(arr);
      }
   }
   else//더이상 create 불가 시
   {
      game_over_1p(score); 
      return 1;//다시시작
   }
   return 0;
}
//방향키이동-두명
int dmove_2p(int arr[][4], int d, int *score1,int *score2,int player) {
   int i,j, s, check = 0;
   for (i = 0; i < 4; i++) {
      for (j = 0; j < 4; j++) {
         if (*arr_tc_2p(arr, i, j, d , player) != 0) {
            for (s = j + 1; s < 4; s++) {//뒤와 합치기
               if (*arr_tc_2p(arr, i, j, d , player) == *arr_tc_2p(arr, i, s, d, player)) {
                  *arr_tc_2p(arr, i, j, d, player) *= 2;
                  *arr_tc_2p(arr, i, s, d, player) = 0;
                  *score1 += *arr_tc_2p(arr, i, j, d, player);//점수 추가
                  check++;
                  break; 
               }
               else if (*arr_tc_2p(arr, i, s, d, player) != 0) break;//뒤에 합치지 못하면 종료
            }


            for (s = j - 1; s >= 0; s--) {//앞에 이동할수 있나 체크
               if (*arr_tc_2p(arr, i, s, d, player) != 0) {
                  break;
               }
            }
            s++;
            if (j != s) {//앞에 이동할수 있으면 정렬
               *arr_tc_2p(arr, i, s, d, player) = *arr_tc_2p(arr, i, j, d, player);
               *arr_tc_2p(arr, i, j, d, player) = 0;
               check++;
            }
         }

      }
   }
   // check == 0 -> 더 이상 움직일 수 없음 -> create 안함
   if (create_check_2p(arr, player)) {
      if (check != 0) {
         create(arr);
      }
   }
   else//더이상 create 불가 시
   {
      game_over_2p(score1,score2,player); 
      return 1;//다시시작
   }
   return 0;
}
//배열을 돌림- 한명  -> 방향키가 달라도 같은 코드로 조작 가능
int *arr_tc_1p(int arr[][4], int i, int j, int d) {
   int ti, tj;
   switch (d) {
   case 1: ti = i; tj = j;   break;
   case 2: ti = j; tj = 3 - i; break;
   case 3: ti = i; tj = 3 - j; break;
   case 4: ti = 3 - j; tj = 3 - i; break;
   }
   return &arr[ti][tj];
}
//배열을 돌림 - 두명
int *arr_tc_2p(int arr[][4], int i, int j, int d, int player) {
   int ti=i, tj=j;
   switch (d) {
   case 1: ti = i; tj = j;   break;
   case 2: ti = j; tj = 3 - i; break;
   case 3: ti = i; tj = 3 - j; break;
   case 4: ti = 3 - j; tj = 3 - i; break;
   }
   return &arr[ti][tj];
}

//게임 오버
void game_over_1p(int *score) {
   char name[100];
   int i;
   rank temp;

   textcolor(WHITE);
   EndG();
   Music_ending_1p();
   system("cls");
   gotoxy(10, 5); printf("Game Over");
   gotoxy(10, 6); printf("Score : %d", *score);
   gotoxy(10, 7); printf("랭킹등록 위해 이름 입력>>");scanf("%s",&name);
   //gotoxy(10, 8); gets(name);
   strcpy(temp.name,name);
   temp.score=*score;
   Bubble(Rank,temp);// 버블
   RankP();
   gotoxy(12, 9); printf("PRESS ANY KEY");
   getch();
   system("cls");
}

void game_over_2p(int *score1,int *score2, int player) {
   char name[100];
   int i;
   rank temp;
   textcolor(WHITE);
   EndG();
   Music_ending_2p();
   system("cls");
   gotoxy(10, 4); printf("player %d 이동불가",player);
   gotoxy(10, 5);if(player==1)printf("2p 승!");else printf("1p 승!");
   gotoxy(10, 6); printf("Game Over");
   gotoxy(10, 7); printf("1p Score : %d", *score1);
   gotoxy(10, 8); printf("2p Score : %d", *score2);
   gotoxy(10, 9); printf("랭킹등록 위해 이름 입력>>");scanf("%s",&name);//scanf("%s",&name);
   strcpy(temp.name,name);
   temp.score=*score1;//if(player==1)temp.score=*score1;else temp.score=*score2;
   Bubble(Rank,temp);// 버블
   RankP();
   gotoxy(12, 10); printf("PRESS ANY KEY");
   getch();
   system("cls");
}

void Bubble(rank *board, rank temp){ // 보드=점수판 임시=입력받은 점수
   int i,j;
   rank swap=temp;
   board[10]=temp;
   
   for(i=0;i<11;i++){
      for(j=0;j<11-i;j++){
          if(board[j].score<board[j+1].score){
            swap=board[j];
            board[j]=board[j+1];
            board[j+1]=swap;
         }
      }
   }
}

void RankP() {
   int i,j;
   gotoxy(7,12);printf("---------------------------------------");
   for(i=0;i<11;i++){
      gotoxy(7,12+i);printf("|");
      gotoxy(26,12+i);printf("|");
   }
   gotoxy(7,23);printf("---------------------------------------");
   for(i=0;i<10;i++){
      gotoxy(10,13+i);printf("이름- %10s || 점수- %d \n",Rank[i].name,Rank[i].score);
   }
}

void RankRe(){
   int i;
   for(i=0;i<11;i++){
      strcpy(Rank[i].name,"이름 없음");
      Rank[i].score=0;
   }
}
void Music_opening() {
   PlaySound(TEXT("an.wav"), //파일 경로
      NULL, SND_ASYNC | SND_FILENAME);
}

void Click() {
   PlaySound(TEXT("click.wav"), //파일 경로
      NULL, SND_ASYNC | SND_FILENAME);
}

void Music_ending_1p() {
   PlaySound(TEXT("seo.wav"), //파일 경로
      NULL, SND_ASYNC | SND_FILENAME);
}

void Music_ending_2p() {
   PlaySound(TEXT("ham.wav"), //파일 경로
      NULL, SND_ASYNC | SND_FILENAME);
}

void EndG() {
   PlaySound(TEXT("dead.wav"), //파일 경로
      NULL, SND_SYNC | SND_FILENAME);
}
/*------------------------------------------------
//  荷物情報分類プログラム
//----------------------------------------------*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>
#include <ctype.h>

/*------------------------------------------------
//  荷物情報構造体
//----------------------------------------------*/
typedef struct {
    int number; /* 荷物番号 */
    char size; /* s -> Sサイズ、m -> Mサイズ、l -> Lサイズ */
    int area; /* 配送エリア番号 */
    char areaString[256]; /* 配送エリア名 */
} packageInfo;

/*------------------------------------------------
//  関数宣言
//----------------------------------------------*/
void packagesInfo (packageInfo []);
int makeRandomNumber (int);

/*------------------------------------------------
//  概　要：指定された荷物サイズと配送エリアの荷物だけ抽出して myPackages に格納する関数
//  引  数：char    荷物サイズ
//       ：int    配送エリア
//       ：packageInfo    荷物情報
//       ：packageInfo    対象となる荷物情報
//----------------------------------------------*/
void classifyPackage (char mySize, int myArea, packageInfo packages[], packageInfo myPackages[])
{
    int i = 0, myPackagesCount=0;

    /* デバッグ用 */
    /* printf("mySize: %c\n", mySize); */
    /* printf("myArea: %d\n", myArea); */

    /*
    // 課題の条件は以下の通り
    //   packageInfo のデータの「荷物サイズ」が同じ、かつ「配送エリア」が同じものを myPackages に格納する
    // ヒント：
    //   areaString の文字列は strcpy を使う
    //   myPackagesCount は myPackages のインデックスとして使う
    */

    for (i=0; i<20; i++) {
        if (packages[i].size == mySize && packages[i].area == myArea) {
            myPackages[myPackagesCount].number = packages[i].number;
            myPackages[myPackagesCount].size = packages[i].size;
            myPackages[myPackagesCount].area = packages[i].area;
            strcpy(myPackages[myPackagesCount].areaString, packages[i].areaString);
            myPackagesCount++;
        }
    }
}

/*------------------------------------------------
//  概　要：システムのエントリーポイント（main関数）
//  引  数：なし
//  戻り値：0: 正常、0以外: 異常
//----------------------------------------------*/
int main()
{
    int i = 0;
    char command[256] = {""}; /* 入力コマンドバッファ */
    char mySize = '\0'; /* 自分のトラックが取り扱える荷物サイズ */
    int myArea = 0; /* 自分のトラックの配送エリア */
    packageInfo packages[20] = {0}; /* 配送したい荷物情報 */
    packageInfo myPackages[20] = {0}; /* 配送したい荷物情報 */

    /* 乱数初期化 */
    srand((unsigned int)time(NULL));

    /* 初期表示メッセージ */
    printf("***** 荷物情報分類プログラム📦📦📦\n");
    printf("***** このプログラムはあなたのトラックで配送できる荷物サイズと配送エリアの荷物情報を取得します💪\n");
    printf("\n");

    for (;;) {
        printf("あなたのトラックが配送できる荷物のサイズを教えてください🚚 [S, M, L]: ");
        scanf("%s", command);

        /* 入力値に Q か q が入力されたら for ループを抜ける */
        if(strcmp(command, "Q") == 0 || strcmp(command, "q") == 0) {
            printf("プログラムを終了します...👋");
            return 0;
        }

        if (strcasecmp(command, "s") != 0 && strcasecmp(command, "m") != 0 && strcasecmp(command, "l") != 0) {
            printf("サイズは S, M, L のいずれかです\n");
            continue;
        }

        /* 自分のトラックが取り扱える荷物サイズを mySize にセット（大文字に強制変換） */
        mySize = toupper(command[0]);
        break;
    }

    for (;;) {
        printf("あなたのトラックが配達できるエリアを教えてください📍\n");
        printf("[1:大田区, 2:品川区, 3:目黒区, 4:世田谷区, 5:渋谷区, 6:港区, 7:千代田区, 8:中央区]: ");
        scanf("%s", command);

        /* 入力値に Q か q が入力されたら for ループを抜ける */
        if(strcmp(command, "Q") == 0 || strcmp(command, "q") == 0) {
            printf("プログラムを終了します...👋");
            return 0;
        }

        if (atoi(command) < 1 || atoi(command) > 8) {
            printf("配送エリア外です\n");
            continue;
        }

        /* 自分のトラックの配送エリアを myArea にセット */
        myArea = atoi(command);
        break;
    }

    /* 現在配送が必要な荷物情報を取得 */
    packagesInfo(packages);

    printf("==> 現在配送が必要な荷物情報：\n");
    for (i=0; i<20; i++) {
        printf("    荷物番号: %03d\n", packages[i].number);
        printf("    サ イ ズ: %c\n", packages[i].size);
        printf("    配送先No: %d\n", packages[i].area);
        printf("    配送先名: %s\n", packages[i].areaString);
    }

    /* 現在配送が必要な荷物情報から、自分が配送できる荷物を抽出 */
    classifyPackage(mySize, myArea, packages, myPackages);

    printf("\n");
    printf("==> あなたに配送を依頼したい荷物情報：\n");
    for (i=0; i<20; i++) {
        /* size == '' -> 分類結果がゼロの場合、その後のデータはないのでループを抜ける */
        if (!myPackages[i].size) {
            /* i == 0 の場合データがゼロなので下記のメッセージを表示する */
            if (i == 0) printf("    配達できる荷物はありません…😭😭😭\n");
            break;
        }
        printf("    荷物番号: %03d\n", myPackages[i].number);
        printf("    サ イ ズ: %c\n", myPackages[i].size);
        printf("    配送先No: %d\n", myPackages[i].area);
        printf("    配送先名: %s\n", myPackages[i].areaString);
    }

    return 0;
}

/*------------------------------------------------
//  概　要：現在配送が必要な荷物情報を返す関数
//  引  数：packageInfo    荷物情報（配列）
//  戻り値：なし
//----------------------------------------------*/
void packagesInfo (packageInfo packages[])
{
    int i = 0;
    int size = 0;

    for (i=0; i<20; i++) {
      packages[i].number = i + 1;
      size = makeRandomNumber(3);
      switch(size)
      {
          case 1: packages[i].size = 'S'; break;
          case 2: packages[i].size = 'M'; break;
          case 3: packages[i].size = 'L'; break;
      }
      packages[i].area = makeRandomNumber(8);
      switch(packages[i].area)
      {
          case 1: strcpy(packages[i].areaString, "大田区"); break;
          case 2: strcpy(packages[i].areaString, "品川区"); break;
          case 3: strcpy(packages[i].areaString, "目黒区"); break;
          case 4: strcpy(packages[i].areaString, "世田谷区"); break;
          case 5: strcpy(packages[i].areaString, "渋谷区"); break;
          case 6: strcpy(packages[i].areaString, "港区"); break;
          case 7: strcpy(packages[i].areaString, "千代田区"); break;
          case 8: strcpy(packages[i].areaString, "中央区"); break;
          default: strcpy(packages[i].areaString, "エリア外");
      }
    }
}

/*------------------------------------------------
//  概　要：乱数最大値で指定された間の乱数を生成する関数
//  引  数：int    乱数最大値
//  戻り値：乱数値
//----------------------------------------------*/
int makeRandomNumber (int randMax)
{
    return (int)(rand() % randMax + 1);
}

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>
#include <string.h>

#define NUM_DIGITS 3

bool isValidGuess(int guess) {
    int digits[10] = {0};

    while (guess > 0) {
        int digit = guess % 10;
        if (digits[digit] > 0) {
            return false;
        }
        digits[digit]++;
        guess /= 10;
    }

    return true;
}

int generateNextGuess(int previousGuess, int bulls, int cows) {
    int nextGuess;
    int digit1, digit2, digit3;

    if (previousGuess == 0) {
        do {
            nextGuess = rand() % 900 + 100;
        } while (!isValidGuess(nextGuess));
        return nextGuess;
    }

    do {
        digit1 = previousGuess / 100;
        digit2 = (previousGuess / 10) % 10;
        digit3 = previousGuess % 10;

        if (bulls == 1 && cows == 1) {
            nextGuess = digit3 * 100 + digit1 * 10 + digit2;
        } else if (bulls == 1 && cows == 0) {
            nextGuess = digit2 * 100 + digit3 * 10 + digit1;
        } else if (bulls == 0 && cows == 1) {
            nextGuess = digit1 * 100 + digit3 * 10 + digit2;
        } else {
            do {
                nextGuess = rand() % 900 + 100;
            } while (!isValidGuess(nextGuess));
        }
    } while (nextGuess == previousGuess);

    return nextGuess;
}

int checkNumber(int x) {
    int d1, d2, d3;
    d1 = x / 100;
    d2 = (x / 10) % 10;
    d3 = x % 10;
    if (x <= 987 && x >= 123) {
        if ((d1 != d2) && (d2 != d3) && (d3 != d1))
            return 1;
        else
            return 0;
    } else
        return 0;
}

int generateNumber() {
    int num;
    do {
        num = rand() % 900 + 100;
    } while (!checkNumber(num));
    return num;
}

int cmpNumber(int x, int y) {
    int g1, g2, g3;
    g1 = y / 100;
    g2 = (y / 10) % 10;
    g3 = y % 10;

    int d1, d2, d3;
    d1 = x / 100;
    d2 = (x / 10) % 10;
    d3 = x % 10;

    int bulls = 0, cows = 0;

    if (g1 == d1) bulls++; else if (g1 == d2 || g1 == d3) cows++;
    if (g2 == d2) bulls++; else if (g2 == d1 || g2 == d3) cows++;
    if (g3 == d3) bulls++; else if (g3 == d1 || g3 == d2) cows++;

    printf("%dA%dB\n", bulls, cows);
    return bulls;
}

int main() {
    int choice;
    char guess_str[10];
    printf("歡迎來玩猜數字遊戲，請選擇一種模式:\n若想玩你猜電腦，請輸入 1\n若想玩電腦猜你，請輸入 2\n");
    scanf("%d", &choice);

    srand(time(NULL));

    if (choice == 1) {
        int secret = generateNumber();
        int guess, bulls;
        int ans;
        printf("歡迎來玩猜數字遊戲\n遊戲規則如下:\n");
        printf("遊戲一開始，電腦會設定三位數，其中三位數之限制如下:\n ①三個數字不得重複\n ②不得以0為開頭，即百位數不得為0\n");
        printf("當你輸入一個三位數，電腦會判斷電腦設定的數字與你所猜測的異同，並給予_A_B的回應\n");
        printf(" A表示數字答對，位置也答對\n B表示數字答對，但位置錯誤\n");
        printf("重複上述之步驟，直到你猜到正確的三位數\n");
        printf("是否觀看範例(是:1 否:2)\n");
        scanf("%d", &ans);
        if(ans==1){
            printf("\n假設電腦設定之數字為 752\n你猜測值為 538，電腦回應0A1B\n你再猜測為 250，電腦回應1A1B\n你再猜測為 452，電腦回應2A0B\n你再猜測為 752，電腦回應3A0B 你猜對了!\n如此程式就結束了\n\n");
        }
        printf("請猜一個三位數的數字:\n");

        do {
            scanf("%s", guess_str);
            if (strcmp(guess_str, "show") == 0) {
                printf("正確答案是：%d\n", secret); 
                 continue;
            }
            guess = atoi(guess_str);
            int trouble=guess/100;
            if((trouble < 1) || (trouble >= 10)){
                printf("格式錯誤,請重新開始遊戲");
                break;
            }
            bulls = cmpNumber(guess, secret);
            if (bulls == NUM_DIGITS) {
                printf("你猜對了！\n");
                break;
            }
        } while (bulls != NUM_DIGITS);
    } else if (choice == 2) {
        int fun;
        printf("**警告**此功能尚未開發完畢，不建議遊玩，輸入1結束遊戲，輸入404繼續遊戲(不建議)\n");//警告
        scanf("%d",&fun);
        if(fun!=404){
             return 0;
        }else{
        int guess = 0, bulls = 0, cows = 0;
        printf("請在心裡想一個三位數的數字，然後讓我來猜。\n");

        do {
            guess = generateNextGuess(guess, bulls, cows);
            printf("我的猜測是: %d\n", guess);
            printf("請回答幾A幾B：");
            scanf("%dA%dB", &bulls, &cows);
            int plus=bulls+cows;
            if ((bulls < 0 || bulls > 3) || (cows < 0 || cows > 3)||(plus>3)) {
                printf("回答格式錯誤,請重新開始遊戲");
                break;
            }
            if (bulls == NUM_DIGITS) {
                printf("我猜對了！\n");
                break;
            }

            printf("Bulls: %d, Cows: %d\n", bulls, cows);
        } while (bulls != NUM_DIGITS);
    } 
    }
    else {
        printf("無效的選擇\n");
    }

    return 0;
}
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

int nochange();
int change();

int main(void)
{
    int mode;

    puts("モード変更ありのものを使用する場合は『1』を、モード変更なしのものを使用する場合は『0』を入力してください");

    scanf("%d", &mode);

    if (mode == 0)
    {
        nochange();
    }
    else if (mode == 1)
    {
        change();
    }

    return 0;
}

int nochange()
{

    FILE *fp;
    time_t timer;
    struct tm *t_st;
    char *wday[] = {"日", "月", "火", "水", "木", "金", "土"};
    char siki[125], kazu_1[125], kazu_2[125];
    char fugo_1[1], fugo_2[1], fugo_1m[1], fugo_2m[1], fugo_11[1], fugo_22[1];
    long double suzi_1, suzi_2, answer;
    int i = 0, j, q;
    char flag = 'f';
    char enzansi;

    printf("--------------------------------------------------------------------\n\
		          関数電卓\n\
\n\
	　　          計算可能な演算\n\
     足し算 -> +  引き算 -> m  掛け算 - > *  割り算 - > /  \n\
\n\
	           　 特殊な符号を使用する際 \n\
       sin -> s  cos -> c  tan -> t ルート  -> l\n\
\n\
		            注意点\n\
	      1.式には空白を入れずに書いてください!\n\
	          ex) 3+30, -3*s30, l4+8\n\
\n\
     2.指定されている文字、または数字以外を書き込まないでください!\n\
\n\
--------------------------------------------------------------------\n\n");

    //math.txtに書き込み開始
    fp = fopen("math.txt", "a");

    if (fp == NULL)
    {
        perror("テキストファイルの読み込みに失敗。\n");
        return 1;
    }

    fprintf(fp, "==============================================================================================\n");

    do
    {
        if (flag == 'c')
        {
            fprintf(fp, "%Lf", answer);
        }

        puts("式を入力してください。");

        if (flag == 'f')
        { //初めてこの処理をする際のみ行いたいため
            scanf("%s", siki);

            //sikiの分解（演算子前）

            if (siki[i] == '-')
            {
                fugo_1m[0] = siki[i];
                i++;
            }

            if (siki[i] == 'l' || siki[i] == 'c' || siki[i] == 's' || siki[i] == 't')
            {
                fugo_1[0] = siki[i];
                i++;
            }

            if (siki[i] == 'l' || siki[i] == 'c' || siki[i] == 's' || siki[i] == 't')
            {
                fugo_11[0] = siki[i];
                i++;
            }

            for (j = 0; siki[i] >= '0' && siki[i] <= '9' || siki[i] == '.'; i++)
            {
                kazu_1[j] = siki[i];
                j++;
            }

            //文字列を計算可能な数字に
            kazu_1[j] = '\n';
            suzi_1 = atof(kazu_1);

            switch (fugo_11[0])
            {
            case 's':
                suzi_1 = sin(suzi_1 * 0.01745);
                break;
            case 'c':
                suzi_1 = cos(suzi_1 * 0.01745);
                break;
            case 't':
                suzi_1 = tan(suzi_1 * 0.01745);
                break;
            case 'l':
                suzi_1 = sqrt(suzi_1);
                break;
            default:
                suzi_1 = suzi_1;
                break;
            }

            switch (fugo_1[0])
            {
            case 's':
                suzi_1 = sin(suzi_1 * 0.01745);
                break;
            case 'c':
                suzi_1 = cos(suzi_1 * 0.01745);
                break;
            case 't':
                suzi_1 = tan(suzi_1 * 0.01745);
                break;
            case 'l':
                suzi_1 = sqrt(suzi_1);
                break;
            default:
                suzi_1 = suzi_1;
                break;
            }

            switch (fugo_1m[0])
            {
            case '-':
                suzi_1 = suzi_1 * -1;
            default:
                suzi_1 = suzi_1;
            }
        }

        else
        { //1周目以降の計算のための初期化

            if (flag == 'b')
            {
                fprintf(fp, "%Lf", answer);
            }
            printf("%Lf", answer);
            scanf("%s", siki);
            suzi_1 = answer;
            suzi_2 = 0;
            fugo_2[0] = '\0';
            fugo_2m[0] = '\0';
        }

        //演算子の読み込み
        enzansi = siki[i];
        i++;

        //sikiの分解（演算子後）
        if (siki[i] == '-')
        {
            fugo_2m[0] = siki[i];
            i++;
        }

        if (siki[i] == 'l' || siki[i] == 'c' || siki[i] == 's' || siki[i] == 't')
        {
            fugo_2[0] = siki[i];
            i++;
        }

        if (siki[i] == 'l' || siki[i] == 'c' || siki[i] == 's' || siki[i] == 't')
        {
            fugo_22[0] = siki[i];
            i++;
        }

        for (j = 0; siki[i] >= '0' && siki[i] <= '9' || siki[i] == '.'; i++)
        {
            kazu_2[j] = siki[i];
            j++;
        }

        //文字列を計算可能な数字に
        kazu_2[j] = '\n';
        suzi_2 = atof(kazu_2);

        switch (fugo_22[0])
        {
        case 's':
            suzi_2 = sin(suzi_2 * 0.01745);
            break;
        case 'c':
            suzi_2 = cos(suzi_2 * 0.01745);
            break;
        case 't':
            suzi_2 = tan(suzi_2 * 0.01745);
            break;
        case 'l':
            suzi_2 = sqrt(suzi_2);
            break;
        default:
            suzi_2 = suzi_2;
            break;
        }

        switch (fugo_2[0])
        {
        case 's':
            suzi_2 = sin(suzi_2 * 0.01745);
            break;
        case 'c':
            suzi_2 = cos(suzi_2 * 0.01745);
            break;
        case 't':
            suzi_2 = tan(suzi_2 * 0.01745);
            break;
        case 'l':
            suzi_2 = sqrt(suzi_2);
            break;
        default:
            suzi_2 = suzi_2;
            break;
        }

        switch (fugo_2m[0])
        {
        case '-':
            suzi_2 = suzi_2 * -1;
        default:
            suzi_2 = suzi_2;
        }

        //数字の計算処理
        switch (enzansi)
        {
        case '+':
            answer = suzi_1 + suzi_2;
            break;
        case '-':
            answer = suzi_1 - suzi_2;
            break;
        case '*':
            answer = suzi_1 * suzi_2;
            break;
        case '/':
            if (suzi_2 != 0)
            {
                answer = suzi_1 / suzi_2;
                break;
            }
            else
            {
                puts("0で割れません");
                break;
            }
        default:
            puts("正しく演算子が入力されなかったので、計算が正常にできませんでした。");
            break;
        }

        //ファイルに書き込み＆答えの表示
        fprintf(fp, "%s = %Lf\n", siki, answer);

        printf("=%Lf\n", answer);

        //続けるか、戻るか、止めるかの処理
        do
        {
            if (flag != 'c' && flag != 'f' && flag != 'b')
            {
                puts("使用できない文字が入力されました。再入力してください。");
            }

            puts("続行の場合「c」を、終了の場合「f」を、1つ戻る場合「b」を入力してください");
            scanf("%s", &flag);
            i = 0;

        } while (flag != 'c' && flag != 'f' && flag != 'b');

        if (flag == 'b')
        {
            answer = suzi_1;
        }

    } while (flag == 'c' || flag == 'b');

    //ファイルに最終的な答えを入力
    fprintf(fp, "\n最終的な答えは[%Lf]になりました。\n", answer);

    //ファイルに実行日の書き込み
    time(&timer);

    t_st = localtime(&timer);

    fprintf(fp, "\n実行日\n西暦%d年%d月%d日%s曜日%d時%d分%d秒\n\n", t_st->tm_year + 1900, t_st->tm_mon + 1, t_st->tm_mday, wday[t_st->tm_wday], t_st->tm_hour, t_st->tm_min, t_st->tm_sec);

    fclose(fp);

    //答えの出力
    printf("最終的な答えは[%Lf]になりました。\n", answer);

    return 0;
}

int change()
{

    FILE *fp;
    time_t timer;
    struct tm *t_st;
    char *wday[] = {"日", "月", "火", "水", "木", "金", "土"};
    char siki[125], kazu_1[125], kazu_2[125];
    char fugo_1[1], fugo_2[1], fugo_1m[1], fugo_2m[1], fugo_11[1], fugo_22[1];
    long double suzi_1, suzi_2, answer;
    int i = 0, j, q;
    char flag = 'f';
    char enzansi;
    char mode;

    printf("--------------------------------------------------------------------\n\
		          関数電卓\n\
\n\
	　　          計算可能な演算\n\
     足し算 -> +  引き算 -> m  掛け算 - > *  割り算 - > /  \n\
\n\
	           　 特殊な符号を使用する際 \n\
       sin -> s  cos -> c  tan -> t ルート  -> l\n\
\n\
		            注意点\n\
	      1.式には空白を入れずに書いてください!\n\
	          ex) 3+30, -3*s30, l4+8\n\
\n\
     2.指定されている文字、または数字以外を書き込まないでください!\n\
\n\
--------------------------------------------------------------------\n\n");

    //suusiki.txtに書き込み開始
    fp = fopen("suusiki.txt", "a");

    if (fp == NULL)
    {
        perror("テキストファイルの読み込みに失敗。\n");
        return 1;
    }

    fprintf(fp, "==============================================================================================\n");

    do
    {
        puts("三角関数を利用する場合『F』を、しない場合は『A』を使用してください");
        mode = '\0';
        scanf("%s", &mode);

        if (flag == 'c')
        {
            fprintf(fp, "%Lf", answer);
        }

        puts("式を入力してください。");

        if (flag == 'f')
        { //初めてこの処理をする際のみ行いたいため
            scanf("%s", siki);

            //sikiの分解（演算子前）

            if (siki[i] == '-')
            {
                fugo_1m[0] = siki[i];
                i++;
            }
            if (mode != 'A')
            {
                if (siki[i] == 'l' || siki[i] == 'c' || siki[i] == 's' || siki[i] == 't')
                {
                    fugo_1[0] = siki[i];
                    i++;
                }

                if (siki[i] == 'l' || siki[i] == 'c' || siki[i] == 's' || siki[i] == 't')
                {
                    fugo_11[0] = siki[i];
                    i++;
                }
            }
            for (j = 0; siki[i] >= '0' && siki[i] <= '9' || siki[i] == '.'; i++)
            {
                kazu_1[j] = siki[i];
                j++;
            }

            //文字列を計算可能な数字に
            kazu_1[j] = '\n';
            suzi_1 = atof(kazu_1);

            if (mode != 'A')
            {
                switch (fugo_11[0])
                {
                case 's':
                    suzi_1 = sin(suzi_1 * 0.01745);
                    break;
                case 'c':
                    suzi_1 = cos(suzi_1 * 0.01745);
                    break;
                case 't':
                    suzi_1 = tan(suzi_1 * 0.01745);
                    break;
                case 'l':
                    suzi_1 = sqrt(suzi_1);
                    break;
                default:
                    suzi_1 = suzi_1;
                    break;
                }

                switch (fugo_1[0])
                {
                case 's':
                    suzi_1 = sin(suzi_1 * 0.01745);
                    break;
                case 'c':
                    suzi_1 = cos(suzi_1 * 0.01745);
                    break;
                case 't':
                    suzi_1 = tan(suzi_1 * 0.01745);
                    break;
                case 'l':
                    suzi_1 = sqrt(suzi_1);
                    break;
                default:
                    suzi_1 = suzi_1;
                    break;
                }
            }
            switch (fugo_1m[0])
            {
            case '-':
                suzi_1 = suzi_1 * -1;
            default:
                suzi_1 = suzi_1;
            }
        }

        else
        { //1周目以降の計算のための初期化

            if (flag == 'b')
            {
                fprintf(fp, "%Lf", answer);
            }
            printf("%Lf", answer);
            scanf("%s", siki);
            suzi_1 = answer;
            suzi_2 = 0;
            fugo_2[0] = '\0';
            fugo_2m[0] = '\0';
        }

        //演算子の読み込み
        enzansi = siki[i];
        i++;

        //sikiの分解（演算子後）
        if (siki[i] == '-')
        {
            fugo_2m[0] = siki[i];
            i++;
        }
        if (mode != 'A')
        {
            if (siki[i] == 'l' || siki[i] == 'c' || siki[i] == 's' || siki[i] == 't')
            {
                fugo_2[0] = siki[i];
                i++;
            }

            if (siki[i] == 'l' || siki[i] == 'c' || siki[i] == 's' || siki[i] == 't')
            {
                fugo_22[0] = siki[i];
                i++;
            }
        }
        for (j = 0; siki[i] >= '0' && siki[i] <= '9' || siki[i] == '.'; i++)
        {
            kazu_2[j] = siki[i];
            j++;
        }

        //文字列を計算可能な数字に
        kazu_2[j] = '\n';
        suzi_2 = atof(kazu_2);
        if (mode != 'A')
        {
            switch (fugo_22[0])
            {
            case 's':
                suzi_2 = sin(suzi_2 * 0.01745);
                break;
            case 'c':
                suzi_2 = cos(suzi_2 * 0.01745);
                break;
            case 't':
                suzi_2 = tan(suzi_2 * 0.01745);
                break;
            case 'l':
                suzi_2 = sqrt(suzi_2);
                break;
            default:
                suzi_2 = suzi_2;
                break;
            }

            switch (fugo_2[0])
            {
            case 's':
                suzi_2 = sin(suzi_2 * 0.01745);
                break;
            case 'c':
                suzi_2 = cos(suzi_2 * 0.01745);
                break;
            case 't':
                suzi_2 = tan(suzi_2 * 0.01745);
                break;
            case 'l':
                suzi_2 = sqrt(suzi_2);
                break;
            default:
                suzi_2 = suzi_2;
                break;
            }
        }
        switch (fugo_2m[0])
        {
        case '-':
            suzi_2 = suzi_2 * -1;
        default:
            suzi_2 = suzi_2;
        }

        //数字の計算処理
        switch (enzansi)
        {
        case '+':
            answer = suzi_1 + suzi_2;
            break;
        case '-':
            answer = suzi_1 - suzi_2;
            break;
        case '*':
            answer = suzi_1 * suzi_2;
            break;
        case '/':
            if (suzi_2 != 0)
            {
                answer = suzi_1 / suzi_2;
                break;
            }
            else
            {
                puts("0で割れません");
                break;
            }
        default:
            puts("正しく演算子が入力されなかったので、計算が正常にできませんでした。");
            break;
        }

        //ファイルに書き込み＆答えの表示
        fprintf(fp, "%s = %Lf\n", siki, answer);

        printf("=%Lf\n", answer);

        //続けるか、戻るか、止めるかの処理
        do
        {
            if (flag != 'c' && flag != 'f' && flag != 'b')
            {
                puts("使用できない文字が入力されました。再入力してください。");
            }

            puts("続行の場合「c」を、終了の場合「f」を、1つ戻る場合「b」を入力してください");
            scanf("%s", &flag);
            i = 0;

        } while (flag != 'c' && flag != 'f' && flag != 'b');

        if (flag == 'b')
        {
            answer = suzi_1;
        }

    } while (flag == 'c' || flag == 'b');

    //ファイルに最終的な答えを入力
    fprintf(fp, "\n最終的な答えは[%Lf]になりました。\n", answer);

    //ファイルに実行日の書き込み
    time(&timer);

    t_st = localtime(&timer);

    fprintf(fp, "\n実行日\n西暦%d年%d月%d日%s曜日%d時%d分%d秒\n\n", t_st->tm_year + 1900, t_st->tm_mon + 1, t_st->tm_mday, wday[t_st->tm_wday], t_st->tm_hour, t_st->tm_min, t_st->tm_sec);

    fclose(fp);

    //答えの出力
    printf("最終的な答えは[%Lf]になりました。\n", answer);

    return 0;
}

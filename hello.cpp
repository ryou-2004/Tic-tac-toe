#include <iostream>
#include <string>
using namespace std;

const int edge = 3;
int bord[edge][edge];
int allLineCount;

void BordLog()
{
    std::system("cls");
    for (int i = 0; i < edge; i++)
    {
        cout << "  " << i + 1 << " ";
    }
    cout << "\n";
    for (int i = 0; i < edge; i++)
    {
        cout << i + 1;
        for (int l = 0; l < edge; l++)
        {
            string value = " ";
            switch (bord[i][l])
            {
            case 1:
                value = "1";
                break;
            case 2:
                value = "2";
                break;
            default:
                break;
            }
            string msg = " " + value + " ";
            cout << msg;
            if (l != edge - 1)
                cout << "|";
        }
        cout << "\n";
        if (i == edge - 1)
        {
            break;
        }
        string line = " ---";
        for (int j = 0; j < edge; j++)
        {
            cout << line;
        }
        cout << "\n";
    }
}
int Input(char c)
{
    int value;
    cout << c << " = ";
    cin >> value;
    return value;
}
void GetAllLine(int allLine[][edge]) //全列取得
{
    int copyIndex = 0;
    //横列取得
    for (int i = 0; i < edge; i++)
    {
        memcpy(allLine[copyIndex], bord[i], sizeof(bord[i]));
        copyIndex++;
    }
    //楯列取得
    for (int i = 0; i < edge; i++)
    {
        int ver[3];
        for (int l = 0; l < edge; l++)
        {
            ver[l] = bord[l][i];
        }
        memcpy(allLine[copyIndex], ver, sizeof(ver));
        copyIndex++;
    }
    //左上から右下に向けての斜め列
    int dia[3];
    for (int i = 0; i < edge; i++)
    {
        dia[i] = bord[i][i];
    }
    memcpy(allLine[copyIndex], dia, sizeof(dia));
    copyIndex++;
    //左下から右上に向けての斜め列
    int j = edge - 1;
    for (int i = 0; i < edge; i++)
    {
        dia[i] = bord[i][j];
        j--;
    }
    memcpy(allLine[copyIndex], dia, sizeof(dia));
}
bool IsContinue(int bord[][edge])
{
    bool isContinue = true;

    int allLine[allLineCount][edge];
    GetAllLine(allLine);
    for (int i = 0; i < allLineCount; i++)
    {
        bool temp = true;
        for (int j = 1; j < edge; j++)
        {
            if (allLine[i][0] != allLine[i][j] || allLine[i][j] == 0)
            {
                temp = false;
                break;
            }
        }
        if (temp)
        {
            isContinue = false;
            break;
        }
    }

    return isContinue; //継続可能だったらtrue
}
bool IsWithinRange(int value, int min, int max)
{
    if (value < min - 1 || max <= value)
        return false;
    else
        return true;
}
bool PlayerTurn(int p_turn)
{
    //入力
    int x = Input('x');
    int y = Input('y');

    //インデックスが合うように変更
    x--;
    y--;

    //入力が範囲内か
    if (IsWithinRange(x, 1, edge) && IsWithinRange(y, 1, edge))
    {
        //入力が反映可能か
        if (bord[y][x] != 0)
        {
            cout << "入力されています\n";
            return false;
        }
    }
    else //範囲外だったら
    {
        cout << "入力の範囲外です\n";
        return false;
    }

    bord[y][x] = p_turn;
    return true;
}
void CpuTurn(int c_turn)
{
    int allLine[allLineCount][edge];
    GetAllLine(allLine);

    int x = 0;
    int y = 0;
    while (true)
    {
        x = rand() % 3;
        y = rand() % 3;
        if (bord[y][x] == 0)
        {
            break;
        }
    }
    bord[y][x] = c_turn;
}
bool TurnEndProcess(int p_turn)
{
    //出力
    BordLog();

    //ゲームが続くか
    if (!IsContinue(bord))
    {
        cout << "GameEnd\n";
        string s[] = {"", "Player", "CPU"};
        cout << "WiN " << s[p_turn] << "\n";
        return false;
    }
    return true;
}
int main()
{
    for (int i = 0; i < edge; i++) //ボードの初期化
    {
        for (int j = 0; j < edge; j++)
        {
            bord[i][j] = 0;
        }
    }
    allLineCount = edge * 2 + 2;

    BordLog(); //ボードの表示
    int id = 0;
    int p_turn = 1;
    int c_turn = 2;
    bool isContinue = true;
    while (true)
    {
        bool isPlayerTurn = PlayerTurn(p_turn); //プレイヤーのターン
        if (!isPlayerTurn)                      //プレイヤーの操作ができていなかったら
            continue;                           //もう一度上から

        isContinue = TurnEndProcess(p_turn); //勝敗が付いたかの確認

        if (!isContinue)
            break;

        CpuTurn(c_turn);
        isContinue = TurnEndProcess(c_turn); //勝敗が付いたかの確認

        if (!isContinue)
            break;
    }
    system("pause");
    return 0;
}
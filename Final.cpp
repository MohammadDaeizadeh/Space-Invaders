#include <iostream>
#include <windows.h>
#include <conio.h>
#include <thread>
#include <cstdlib>
#include <cmath>
#include <fstream>
using namespace std;

struct player
{
    int score;
    char name[30];
};

char box[15][15];
int c = 7, bc, br, loose=0;
bool activebullet = false;
void free_aliens();
void show(int, int, int, int);
void fill_aliens();
void move_alien_right(int &, bool &);
void move_alien_left(int &, bool &);
int counter_right(int);
int counter_left(int);
int counter(int);
void gotofirst();
int move(char, char *,int, int ,int, int);
void alien_shoot();
void enemy_bullet_move(int& );
void barrier();
void put_space_ship(int &j);
void move_space_ship(int &j);
void if_empty(int& );
void start_game(int , int , int ,int ,char*);
bool namecheck(char *);
void game_over(int, int);
void add_score(string);
string namescore_string(char *, int);
int digit_counter(int);
int line_decomposer(const string &, char *);
int which_line(char *);
bool check_lines(int, int);
int number_of_lines();
void swap_lines(int, int);
void show_leaderboard();
int string_to_number(string );
void menu();

int main()
{
    srand(static_cast<unsigned int>(time(nullptr)));
    menu();
}
void free_aliens()
{
    for (int k = 0; k < 15; k++)
    {
        for (int q = 0; q < 15; q++)
        {
            box[k][q] = ' ';
        }
    }
}
void show(int score, int time, int health,int level)
{
    cout << "\033[?25l";
    gotofirst();
    for (int k = 0; k < 15; k++)
    {
        for (int q = 0; q < 15; q++)
        {
            if (box[k][q] != ' ')
                cout << "\033[32m";
            if(box[k][q]=='a')
                cout<<"👦";
            else if(box[k][q]=='r')
                cout<<"🧑‍🏫";
            else if(box[k][q]=='b')
                cout<<"👧";
            else if(box[k][q]=='X')
                cout<<"🖊️";
            else if(box[k][q]=='c')
                cout<<"🧒";
            else if(box[k][q]=='Q')
                cout<<"📚";
            else if(box[k][q]=='s')
                cout<<"🧔🏿";
            else if(box[k][q]=='Y')
                cout<<"📒";
            else if(box[k][q]=='Z')
                cout<<"🎒";
            else if(box[k][q]=='B')
                cout<<"🙭";
            else
            cout << box[k][q] << " ";
            cout << "\033[0m";
        }
        cout << endl;
    }
    cout << "score : " << score << "\n";
    cout << "time : " << time * 0.001 << "\n";
    cout << "health : " << health << "  " << "\n";
    cout << "level : " << level << " " << "\n";
}
void fill_aliens()
{

    box[2][0] = 'a';
    box[2][1] = 'a';
    box[2][2] = 'a';
    box[2][3] = 'a';
    box[2][4] = 'a';
    box[2][5] = 'b';
    box[3][0] = 'b';
    box[3][1] = 'b';
    box[3][2] = 'b';
    box[3][3] = 'b';
    box[3][4] = 'b';
    box[3][5] = 'b';
    box[4][0] = 'b';
    box[4][1] = 'c';
    box[4][2] = 'c';
    box[4][3] = 'c';
    box[4][4] = 'c';
    box[4][5] = 'c';
}
void move_alien_right(int &k, bool &right)
{
    for (int i = 2; i < 5; i++)
    {
        if (k < 14)
        {
            for (int j = 13; j >= 0; j--)
            {
                if (box[i][j] != 'B')
                    box[i][j + 1] = box[i][j];
                else
                    box[i][j + 1] = ' ';
            }
            box[i][0] = ' ';
        }
        else if (k == 14)
        {
            right = false;
            break;
        }
    }
}
void move_alien_left(int &k, bool &right)
{
    for (int i = 2; i < 5; i++)
    {
        if (k > 0)
        {
            for (int j = 0; j < 15; j++)
            {
                if (box[i][j + 1] != 'B')
                    box[i][j] = box[i][j + 1];
                else
                    box[i][j] = ' ';
            }
            box[i][14] = ' ';
        }
        else if (k == 0)
        {
            right = true;
            break;
        }
    }
}
int counter_right(int i)
{
    int e = -1;
    for (int j = 14; j >= 0; j--)
    {
        if (box[i][j] == 'a' || box[i][j] == 'b' || box[i][j] == 'c')
        {
            e = j;
            break;
        }
    }

    if (e == -1)
        return 0;
    else
        return e;
}
int counter_left(int i)
{
    int s = -1;
    for (int j = 0; j < 15; j++)
    {
        if (box[i][j] == 'a' || box[i][j] == 'b' || box[i][j] == 'c')
        {
            s = j;
            break;
        }
    }
    if (s == -1)
        return 0;
    else
        return s;
}
int counter(int i)
{
    return counter_right(i) - counter_left(i) + 1;
}
void gotofirst()
{
    HANDLE consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
    COORD cursorCoord;
    cursorCoord.X = 0;
    cursorCoord.Y = 0;
    SetConsoleCursorPosition(consoleHandle, cursorCoord);
}
int move(char m, char *name,int score, int time, int health, int level)
{

    if (m == 'd')
    {
        box[14][c] = ' ';
        if (c > 13)
            c = 13;
        box[14][++c] = 's';
        return 0;
    }

    else if (m == 'a')
    {
        box[14][c] = ' ';
        if (c < 1)
            c = 1;
        box[14][--c] = 's';
        return 0;
    }
    else if (m == 's' && !activebullet)
    {
        box[13][c] = 'B';
        bc = 13;
        br = c;
        activebullet = true;
        return 0;
    }
    else if (m == 'p')
    {
        DWORD start = GetTickCount();
        system("cls");
        int option;
        cout << "1.continue\n2.save&quit\nchoose your option:";
        cin >> option;
        if (option == 1)
        {
            DWORD end = GetTickCount();
            DWORD duration = end - start;
            return duration;
        }
        else if (option == 2)
        {
            int i = 0;
            for (; i < 30; i++)
            {
                if (name[i] == '\0')
                    break;
            }
            name[i] = '.';
            name[i + 1] = 't';
            name[i + 2] = 'x';
            name[i + 3] = 't';
            name[i + 4] = '\0';
            ofstream file(name);
            file.close();
            fstream saved(name);
            saved<<1<<'\n';
            for (int j = 0; j < 15; j++)
            {
                for (int k = 0; k < 15; k++)
                {
                    if(box[j][k]==' ')
                    saved << '*';
                    else
                    saved << box[j][k];
                }
                saved << '\n';
            }
            saved<<score<<'\n'<<time<<'\n'<<health<<'\n'<<level<<'\n';

            loose=1;
            saved.close();
            name[i] = '\0';
            name[i + 1] = '\0';
            name[i + 2] = '\0';
            name[i + 3] = '\0';
            return time;
        }
    }
}
void alien_shoot()
{
        int num = rand() % max(max(counter(2), counter(3)), counter(4)) + min(min(counter_left(2), counter_left(3)), counter_left(4));

        for (int i = 4; i >= 2; i--)
        {
            if (box[i][num] == 'c')
            {
                box[i + 1][num] = 'X';
                break;
            }
            else if (box[i][num] == 'b')
            {
                box[i + 1][num] = 'Y';
                break;
            }
            else if (box[i][num] == 'a')
            {
                box[i + 1][num] = 'Z';
                break;
            }
        }
}
void enemy_bullet_move(int &health)
{
    for (int i = 14; i >= 0; i--)
    {
        for (int j = 14; j >= 0; j--)
        {
            if (box[i][j] == 'X' || box[i][j] == 'Y' || box[i][j] == 'Z')
            {
                if (i == 14)
                    box[i][j] = ' ';
                else if (box[i + 1][j] == ' ')
                {
                    box[i + 1][j] = box[i][j];
                    box[i][j] = ' ';
                }
                else if (box[i + 1][j] == 's')
                {
                    switch (box[i][j])
                    {
                    case 'X':
                        health -= 10;
                        break;
                    case 'Y':
                        health -= 20;
                        break;
                    case 'Z':
                        health -= 30;
                        break;
                    }
                    box[i][j] = ' ';
                    if (health <= 0)
                    {
                        health = 0;
                        loose = 2;
                    }
                }
                else
                {
                    box[i + 1][j] = ' ';
                    box[i][j] = ' ';
                }
            }
        }
    }
}
void barrier()
{
    for (int i = 10; i <= 12; i++)
    {
        for (int j = 0; j <= 2; j++)
        {
            box[i][j] = 'Q';
        }

        for (int j = 4; j <= 6; j++)
        {
            box[i][j] = 'Q';
        }

        for (int j = 8; j <= 10; j++)
        {
            box[i][j] = 'Q';
        }

        for (int j = 12; j <= 14; j++)
        {
            box[i][j] = 'Q';
        }
    }
}
void put_space_ship(int &j)
{
    box[0][0] = 'r';
    j++;
}
void move_space_ship(int &j)
{
    box[0][j] = box[0][j - 1];
    box[0][j - 1] = ' ';
    if (j < 14)
        j++;
    else
    {
        j = 0;
        box[0][14] = ' ';
    }
}
void if_empty(int& level)
{
    int aliens_counter = 0;
    for (int i = 0; i < 15; i++)
    {
        for (int j = 0; j < 15; j++)
        {
            if ((box[i][j] == 'a') || (box[i][j] == 'b') || (box[i][j] == 'c'))
            {
                aliens_counter++;
            }
        }
    }

    if (aliens_counter == 0)
    {
        fill_aliens();
        level++;
    }
}
void start_game(int health, int timeget , int score,int level, char* name)
{
    player pl1;
    pl1.score = score;
    for(int j=0; j<15; j++)
    {
        if(box[14][j]=='s')
        {
            c=j; 
            break;
        }
        else 
            c=7;
    }
    box[14][c] = 's';
    int j;
    system("cls");
    if(score==0 && timeget==0 && health==100)
    {
        j=0;
        level=1;
        free_aliens();
        barrier();
        fill_aliens();
        while (true)
        {
            for (int i = 0; i < 30; i++)
                pl1.name[i] = '\0';

            cin.getline(pl1.name, 30);
            if (namecheck(pl1.name))
                break;
            cout << "What's your name? ";
        }
    }
    else
    {
        for(int l=0; l<15; l++)
        {
            if(box[0][l]=='r')
                j=l;
        }
        int k=0;
        for(; name[k]!='\0'; k++)
        {
            pl1.name[k]=name[k];
        }
        pl1.name[k]='\0';
        cout<<"Welcome "<<pl1.name;
        getch();
    }

    bool right = true;
    int  time = 0, stoped_time=0;
    DWORD start = GetTickCount();
    while (loose==0)
    {
        DWORD end = GetTickCount() - stoped_time;
        DWORD duration = end - start + timeget;
        if (kbhit() && duration % 10 == 0)
        {
            char m = getch();
            stoped_time=stoped_time + move(m, pl1.name,pl1.score, duration, health, level);
        }
        if (activebullet && (duration) % 20 == 0)
        {
            box[bc][br] = ' ';
            char temp;
            temp = box[bc - 1][br];
            if (bc > 0)
                box[--bc][br] = 'B';
            else if (bc == 0)
                bc = -1;
            if (bc == -1 || temp != ' ')
            {
                activebullet = false;
                box[bc][br] = ' ';
                switch (temp)
                {
                case 'c':
                    pl1.score += 20 + level;
                    break;

                case 'b':

                    pl1.score += 30 + level;
                    break;

                case 'a':
                    pl1.score += 40 + level;
                    break;

                case 'r':
                    pl1.score += 100 + level*level;
                    break;
                }
            }
        }
        if ((duration) % 100 == 0)
        {
            if (right)
            {
                int k = max(max(counter_right(2), counter_right(3)), counter_right(4));
                move_alien_right(k, right);
            }
            else if (!right)
            {
                int k = min(min(counter_left(2), counter_left(3)), counter_left(4));
                move_alien_left(k, right);
            }
        }
        if ((duration) % 17000 == 0 && (duration != 0) && j == 0)
        {
            put_space_ship(j);
        }
        if ((duration) % 40 == 0 && j > 0)
        {
            move_space_ship(j);
        }
        if (duration % 2000/sqrt(level) == 0)
        {
            alien_shoot();
        }
        if (duration % 100 == 0)
        {
            enemy_bullet_move(health);
        }
        if ((duration) % 30 == 0)
        {
            if_empty(level);
        }
        if ((duration) % 10 == 0)
            show(pl1.score, duration, health,level);
        if (loose==2)
        {
            time = duration;
            int i=0;
            for (; i < 30; i++)
            {
                if (pl1.name[i] == '\0')
                    break;
            }
            pl1.name[i] = '.';
            pl1.name[i + 1] = 't';
            pl1.name[i + 2] = 'x';
            pl1.name[i + 3] = 't';
            pl1.name[i + 4] = '\0';
            fstream file(pl1.name);
            if(file.is_open())
            {
                file<<9;
                file.close();
            }
            pl1.name[i] = '\0';
            pl1.name[i + 1] = '\0';
            pl1.name[i + 2] = '\0';
            pl1.name[i + 3] = '\0';
            game_over(pl1.score, time);
        }
    }
    add_score(namescore_string(pl1.name, pl1.score));
}
bool namecheck(char *name)
{
    // this function checks if the name is only made of letters
    for (int i = 0; i < 30; i++)
    {
        // when it reaches the end it breaks
        if (name[i] == '\0' && i != 0)
        {
            system("cls");
            cout << "Welcome " << name << endl;
            break;
        }
        else if (name[i] == '\0' && i == 0)
        {
            return false;
        }
        // intervals of alphabet letters in ASCII table
        if (!(name[i] > 64 && name[i] < 91) && !(name[i] > 96 && name[i] < 123))
        {
            cout << "your name can only contain letters" << endl;
            return false;
        }
    }
    return true;
}
void game_over(int score, int time)
{
    system("cls");
    cout << "You scored " << score << " in " << time / 1000 << "s.";
    getch();
}
string namescore_string(char *name, int score)
{
    // this turns the players name and score into a single string
    char result[60];
    // digit holds the number of score's digits
    // digit_counter counts the digit of an int
    int digit = digit_counter(score);
    // coping the name at the begging of the result string
    strcpy(result, name);
    int i = strlen(name);
    // this loop fills the empty spaces between name and score with '_'
    for (; i < (59 - digit); i++)
    {
        result[i] = '_';
    }
    // the last loop places score at the end of string
    for (; i < 59; i++)
    {
        result[i] = score / (pow(10, 58 - i)) + 48;
        score = score % static_cast<int>(pow(10, 58 - i));
    }
    // adding '\0' for ending the string
    result[59] = '\0';
    // resulting string should be like this
    //  name__________________________________________________1234
    return result;
}
int digit_counter(int num)
{
    // this function counts the digits of a given number
    // counter stores that number
    int counter = 0;
    while (num > 0)
    {
        num /= 10;
        counter++;
    }
    return counter;
}
void add_score(string namescore)
{
    // this function adds the score to the leaderboard
    // opening leaderboard file
    fstream LeaderBoard("LeaderBoard.txt");
    // checking file is open
    if (LeaderBoard.is_open())
    {
        // previous_player checks wether the player is previously on the leader board
        bool previous_player = false;
        // playerscore is used when the player is previously on the leader board and it stores the player's previous record
        string playerscore;
        // name and score are the result of decomposing playerscore
        char name[30];
        int score;
        // line_decomposer is used to split the name and score from the singles string created by namescore_string function
        score = line_decomposer(namescore, name);
        // a temp player for each player on the leaderboard to be compared with current player
        player read;
        // this loop skims through the leaderboard file and coping each line to playerscore. to seek for the player with the same name on leaderboard
        while (getline(LeaderBoard, playerscore))
        {
            // decomposing playerscore
            read.score = line_decomposer(playerscore, read.name);
            // this condition checks if the name of player is on that line int the leaderboard
            if (strcmp(read.name, name) == 0)
            {
                // if the previous score is greater it do nothing just marking that the player exists on leaderboard
                if (read.score > score)
                {
                    previous_player = true;
                    break;
                }
                // if the current score is greater
                else
                {
                    // number of characters in each line of leaderboard
                    int char_in_line = 61;
                    // pos shows where in the file should the text be added
                    // which_line tells in wich line of leaderboard the player has been found
                    int pos = (which_line(name) - 1) * char_in_line;
                    LeaderBoard.seekg(pos);
                    LeaderBoard.seekp(pos);
                    // placing new score in the leaderboard
                    LeaderBoard << namescore_string(name, score);
                    LeaderBoard.close();
                    previous_player = true;
                    // this loop moves the newly added scoer up to the right position in the leader board
                    for (int i = which_line(name); i > 1; i--)
                    {
                        // check lines compare the score of two lines
                        if (check_lines(i, i - 1))
                        {
                            // if the above line is smaller than the following line swap_lines swap their postion
                            swap_lines(i, i - 1);
                        }
                        else
                            break;
                    }
                    break;
                }
                break;
            }
        }
        LeaderBoard.clear();
        // if the player is new and hasn't been on the leader board the following lines adds it
        if (!previous_player)
        {
            // moving the pointer to the end of line
            LeaderBoard.seekg(0, ios::end);
            // adding the score
            LeaderBoard << namescore << '\n';
            LeaderBoard.close();
            // this loops moves up the newly added line to its right position like previous lines
            for (int i = number_of_lines(); i > 1; i--)
            {
                if (check_lines(i, i - 1))
                {
                    swap_lines(i, i - 1);
                }
                else
                    break;
            }
        }
    }
    else
    {
        cout << "unable to open LeaderBoards" << endl;
    }
}
int line_decomposer(const string &row, char *name)
{
    // it decomposes the name and score from the single line
    int score = 0;
    // this loop makes all the characters in name null
    for (int j = 0; j < 30; j++)
        name[j] = '\0';
    // this loop extracts the score from the line
    for (int i = 0; i < 59; i++)
    {
        if (row[i] > 47 && row[i] < 58)
        {
            score += (row[i] - 48) * pow(10, 58 - i);
        }
    }
    // this loop extracts name from the line character by character
    int i = 0;
    while (row[i] != '_')
    {
        name[i] = row[i];
        i++;
    }
    // returning score while the name has been passed by reference
    return score;
}
int which_line(char *name)
{
    // this function tells in which line of leaderboard the name is found
    // opening leaderboard file
    fstream file("LeaderBoard.txt");
    string line;
    int i = 0;
    // reading leaderboard line by line to find the wanted name
    // i shows the current line which is being read
    while (getline(file, line))
    {
        i++;
        char namefind[30];
        // decomposing the reading line
        line_decomposer(line, namefind);
        // checking if the names match
        if (strcmp(namefind, name) == 0)
        {
            file.close();
            return i;
            break;
        }
    }
    file.close();
    return 0;
}
bool check_lines(int firstline, int secondline)
{
    // this function checks scores of two lines in leaderboard
    // if there is only one line there is no checking
    if (number_of_lines() == 1)
        return false;
    // opening leaderboard file
    fstream file("LeaderBoard.txt");
    // two strings for keeping two lines to compare
    string first, second;
    // an unimportant cstring for functions input
    char namebin[30];
    // characters in each line of leaderboard
    int char_in_line = 61;
    // fixing the position of pointer to read the wanted line
    int pos = (firstline - 1) * char_in_line;
    file.seekg(pos);
    file.seekp(pos);
    // reading the line
    getline(file, first);
    // fixing the position of pointer to read the wanted line
    pos = (secondline - 1) * char_in_line;
    file.seekg(pos);
    file.seekp(pos);
    // reading the line
    getline(file, second);
    // two ints for storing and comparing the scores of wanted lines
    int firstscore = line_decomposer(first, namebin);
    int secondscore = line_decomposer(second, namebin);
    getch();
    // closing the file
    file.close();
    // this condition determines if the following line's score is greater than the other's
    if (firstscore > secondscore)
        return true;
    else
        return false;
}
int number_of_lines()
{
    // this function tells the number of lines on the leader board
    fstream file("LeaderBoard.txt");
    int NoL = 0;
    string line;
    // it counts until reaching the end of file
    while (!file.eof())
    {
        getline(file, line);
        NoL++;
    }
    file.close();
    return NoL - 1;
}
void swap_lines(int firstline, int secondline)
{
    // if two lines are in wrong positions it swaps them
    // opening the leaderboard file
    fstream file("LeaderBoard.txt");
    string first, second;
    int char_in_line = 61;
    // fixing the positions for reading the wanted lines and reading them
    int pos = (firstline - 1) * char_in_line;
    file.seekg(pos);
    file.seekp(pos);
    getline(file, first);
    pos = (secondline - 1) * char_in_line;
    file.seekg(pos);
    file.seekp(pos);
    getline(file, second);

    // move the pointer to the begining of file
    file.clear();

    // chaning the position of two lines
    pos = (secondline - 1) * char_in_line;
    file.seekg(pos);
    file.seekp(pos);
    file << first;
    pos = (firstline - 1) * char_in_line;
    file.seekg(pos);
    file.seekp(pos);
    file << second;
    file.close();
}
void show_leaderboard()
{
    system("cls");
    // it show the leader board to the screen
    ifstream LeaderBoard("LeaderBoard.txt");
    string playerscore;
    player pl;
    // this loop decomposes all records on leader board and shows them
    int i = 0;
    cout << "LeaderBoard" << endl;
    cout << "------------------------------------------" << endl;
    while (getline(LeaderBoard, playerscore))
    {
        i++;
        pl.score = line_decomposer(playerscore, pl.name);

        if (i == 1)
            cout << "\033[33m";
        else if (i == 2)
            cout << "\033[32m";
        else
            cout << "\033[0m";
        cout << pl.name << "   " << pl.score << endl;
            cout<< "\033[0m";
    }
    // it shows number of players on the list
    cout << "number of players= " << number_of_lines() << endl;
    LeaderBoard.close();
    cout << "\033[0m";
    cout << "Enter a key to continue: ";
    getch();
}
int string_to_number(string get)
{
    int num=0;
    for(int i=0; get[i]!='\0'; i++)
    {
        num=num*10+(get[i]-48);
    }
    return num;
}
void menu()
{
    char option;
    bool exit = false;
    while (!exit)
    {
        system("cls");

        cout << "SCHOOL INVADERS \n1.start new game\n2.loadgame\n3.leaderboard\n4.credits\n5.exit\nenter your option: ";
        cin >> option;
        switch (option)
        {
        case '1':
        {
            system("cls");
            cout<<"how to play:\n a: move left \n d: move right \n s: shoot \n p: pause game";
            getch();
            loose=0;
            char temp[30];
            start_game(100, 0 , 0, 0, temp);
            break;
        }
        case '2':
        {
            system("cls");
            player pl1;
            while (true)
            {
                for (int i = 0; i < 30; i++)
                    pl1.name[i] = '\0';

                cin.getline(pl1.name, 30);
                if (namecheck(pl1.name))
                    break;
                cout << "What's your name? ";
            }
             int i = 0;
            for (; i < 30; i++)
            {
                if (pl1.name[i] == '\0')
                    break;
            }
            pl1.name[i] = '.';
            pl1.name[i + 1] = 't';
            pl1.name[i + 2] = 'x';
            pl1.name[i + 3] = 't';
            pl1.name[i + 4] = '\0';
            fstream load(pl1.name);
            if(!load.is_open())
            {
                cout<<"File Doesn't exist";
                getch();
            }
            pl1.name[i] = '\0';
            pl1.name[i + 1] = '\0';
            pl1.name[i + 2] = '\0';
            pl1.name[i + 3] = '\0';
            char n;
            load>>n;
            if(n==49)
            {
            for(int j=0; j<15; j++)
            {
                for(int k=0; k<15; k++)
                {
                    load>>box[j][k];
                    if(box[j][k]=='*')
                        box[j][k]=' ';
                }
            }
            int score, time, health, level;
            string get;
            getline(load,get);
            getline(load,get);
            score=string_to_number(get);
            getline(load,get);
            time=string_to_number(get);
            getline(load,get);
            health=string_to_number(get);
            getline(load,get);
            level=string_to_number(get);
            load.close();
            show(score, time, health,level);
            getch();
            loose=0;
            start_game(health, time, score,level, pl1.name);
            }
            else
            {
                cout<<"the game has been ended";
                getch();
            }
            break;
        }
        case '3':
        {
            show_leaderboard();
            break;
        }
        case '4':
        {
            cout<<"created by DR\033[33mY AZ D\033[0mESERT"<<endl;
            cout<<"funded by Mohammad Daezadeh"<<endl;
            cout<<"special thanks to ALLIANCE team (Zahra Forouzesh & Morteza Mahdavi)"<<endl;
            cout<<"thanks to Mehrdad and Amir Hossein for their help\n";
            cout << "Enter a key to continue: ";
            getch();
            break;
        }
        case '5':
        {
            exit = true;
            break;
        }
        default:
        cout<<"wrong character";
        getch();
        }
    }
}
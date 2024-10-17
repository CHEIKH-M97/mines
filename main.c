#include<stdio.h>
#include<time.h> //needed for getting random mines each time.

/*  Help :
The game concept is very simple :

An empty 5x4 grid is displayed. The player chooses the number of mines to be placed by the computer
on the board . Later , each time the player chooses a case ; If its a safe case an X will appear ;
If its a mine the player looses.
X : Safe case
M : Mine
O : Unkown case
*/
/* Functions guide :
print_header : prints a welcome message
get_traps : asks the user for the mines number
init_hidden_array : initializes a hidden 2D array (4x5) containing the specific number of mines and the rest
are free cases. (mines cases are generated randomly)
init_board : initializes a 2D array containing "O" as elements (This is the game board that will be changed
                                                                   r and printed during the game)
print_board : this function takes as argument a 2d array and prints it in the shape of a 4x5 grid.
play : asks the user  to choose a case. If its a mine -->Lose ; If its a safe case then the case will be changed to X
*/

char hidden_array[4][5]; //initializing these arrays globally because they will be modified during the game and idk how to pass arrays though functions.
char board[4][5];
int lost = 0;
void print_header()
{
    printf("***************\nWelcome To Mines\n****************\n");
}
int get_traps()
{
    int traps;
    while (1)
    {
        printf("Choose the number of mines : (1-10)\n-->");
        scanf("%d",&traps);
        if (traps<=10 && traps >= 1)
        {
            return traps;
        }
        else
        {
            printf("\nInvalid Input ! Mines should be (1-10)\n");
        }
    }
}
void init_hidden_array(int traps)
{
    int r,c; //r for rows and c for columns
    for (int i = 0 ; i<4 ;i++)
        {
            for (int j = 0 ; j<5 ; j++)
            {
                hidden_array[i][j] = 'O';
            }
        }

    for (int t = 1 ; t<= traps ; t++)
    {
        while(1)
        {
            r = (rand() % 5);
            c = (rand() % 6);
            if (hidden_array[r][c] == 'O')
            {
                hidden_array[r][c] = 'M';
                break;
            }
        }
    }
}
void init_board()
{
    for (int i = 0 ; i<4 ;i++)
    {
        for (int j = 0 ; j<5 ; j++)
        {
            board[i][j] = 'O';
        }
    }
}
void print_board(char arr[4][5])
{
    printf("                  0               1               2               3              4 \n");
    for (int i = 0 ; i<4 ; i++)
    {
        printf("\n          +--------------+---------------+---------------+---------------+---------------+\n",i);
        printf("     %d    |",i);
        for ( int j =0 ; j<5 ; j++)
        {
            printf("       %c      | ",arr[i][j]);
        }
    }
    printf("\n          +--------------+---------------+---------------+---------------+---------------+\n");
}
void play()
{
    int row,column;
    printf("Press Enter to continue");
    getchar();
    while (1)
    {
        printf("\nChoose your row :\n-->");
        scanf("%d",&row);
        printf("Choose your column :\n-->");
        scanf("%d",&column);
        if (row<=3 && row >=0 && column <= 4 && column>=0 && board[row][column] == 'O')
        {
            break;
        }
        else
        {
            printf("Invalid input ! Try again.");
        }
    }
    if (hidden_array[row][column] == 'M')
    {
        lost = 1;
        board[row][column] = 'M';
        print_board(board);
    }
    else
    {
        board[row][column] = 'X';
    }

}
void main()
{
    srand(time(NULL));
    print_header();
    init_board();
    int traps = get_traps();
    init_hidden_array(traps);
    //print_board(hidden_array); //Uncomment only this for testing (dont cheat)
    int plays = 0,max_plays = 20 - traps;
    while(lost ==0 && plays < max_plays)
    {
        print_board(board);
        play();
        plays ++;
    }
    if (plays = max_plays && lost == 0)
    {
        printf("******************\nCongrats !! You win\n******************");
    }
    else if(lost ==1)
    {
        printf("**************************\nThis is a mine !! You lose\n**************************");
        printf("\n Board Reveal : \n");
        print_board(hidden_array);
    }
    system("pause");

}

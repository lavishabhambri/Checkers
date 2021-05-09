#include "checkers.h"
#include "stack.h"
#include "Que.h"
#include "checkers.h"
#include "checkers.h"
#include "Que.h"

// ************File used to call & run the functions************

int main(void)
{
    checkersGrid CheckerBoard[SIZE][SIZE];
    initBoard(CheckerBoard);
    StackContents stack[10000];
    Queue q = createQueue();
    int count_queue = 0;
    char turn = 'O';
    int input, capture, valid;
    coordinates start, final;
    char temp1, temp2;
    int moves;
    int reply;
    int undo_ans;
    int k;
    int temp;
    int dummy;
    int win = 0;
    introduction();
    if (getchar())
    {
        while (1)
        {
            system("clear");
            printBoard(CheckerBoard);
            printf("\n               ");
            printf(" ************ %c's Turn ************\n", turn);
            scanf("%d", &input);
            while (input < 0 || input > 4)
            {
                printf("                    Invalid Input. Try again!\n");
                scanf("%d", &input);
            }
            if (input == 0)
            {
                printf("                  Thank you for playing the game!\n");
                return 0;
            }
            if (input == 1)
            {
                printf("             ");
                printf("      Enter values of X1 Y1 X2 Y2\n");
                scanf(" %c %d %c %d", &temp1, &start.x, &temp2, &final.x);
                temp1 = toupper(temp1);
                temp2 = toupper(temp2);
                start.y = temp1 - 65;
                final.y = temp2 - 65;
                int capture_possible = if_capture(CheckerBoard, turn);
                int capture = captures(CheckerBoard, turn, start, final);
                if (capture != capture_possible)
                    valid = -1;
                else
                    valid = movements(CheckerBoard, turn, start, final) || capture; //move will be valid if either of capture or movements are true

                printf("\n\n");
                if (win != 0)
                {
                    printf("You cannot input as winner is declared; unless you undo\n");
                }
                if (valid == 0)
                {
                    // Invalid move
                    system("clear");
                    printBoard(CheckerBoard);
                    printf("\n               ");
                    printf(" ************ %c's Turn ************\n", turn);
                    printf("\n                     Invalid Move, Try Again!\n");

                    printf("                    Enter a number to continue\n");
                    scanf("%d", &dummy);
                }
                else if(valid == -1)
                {
                    system("clear");
                    printBoard(CheckerBoard);
                    printf("\n               ");
                    printf(" ************ %c's Turn ************\n", turn);
                    printf("\n           Invalid Move, Try Again! Capture is possible\n");

                    printf("                    Enter a number to continue\n");
                    scanf("%d", &dummy);
                }
                else // Valid move
                {   
                    sound();
                    enQueue(q, start, final, turn);
                    count_queue++;
                    // If Valid move push into stack everytime
                    StackContents StackValues;
                    StackValues.start = start;
                    StackValues.final = final;
                    StackValues.turn = turn;
                    StackValues.cap = capture;
                    if (CheckerBoard[final.x - 1][final.y].checkers.type == KING)
                        StackValues.type = 1;
                    else
                        StackValues.type = 0;
                    push(stack, StackValues);
                    if (ifdouble(CheckerBoard, final, turn) && capture > 0)
                        ;
                    else
                        turn = switchTurn(turn);
                }
                win = winner(CheckerBoard, turn);
                if (win == 1)
                {
                    printf("The winner is O\n");
                }
                else if (win == 2)
                {
                    printf("The winner is X\n");
                }
                if (win != 0)
                {
                    printf("Enter any number to continue\n");
                    scanf("%d", &dummy);
                }
            }
            else if (input == 2)
            {
                printf("           Enter the number of moves you want to undo:\n");
                scanf("%d", &moves);
                printf("         Does player %c accept %c request to undo %d moves?\n          Enter 1 to accept or any other number to deny\n", switchTurn(turn), turn, moves);
                scanf("%d", &reply);
                if (reply == 1)
                {
                    printf("                   The player %c accepts\n", switchTurn(turn));
                    undo_ans = undo(CheckerBoard, stack, moves);
                    if (undo_ans == 1)
                    {
                        if (moves > 0)
                        {
                            win = 0;
                        }
                        for (int i = 0; i < moves; i++)
                        {
                            pull(q);
                            count_queue--;
                        }
                        if (moves % 2 == 1)
                        {                            //turn swicthes if we undo odd number of moves but remains same when we undo even number
                            turn = switchTurn(turn); //toggles turn
                        }
                    }
                    else if (undo_ans == 0)
                    {
                        printf("Enter a number to continue\n");
                        scanf("%d", &dummy);
                    }
                }
                else
                {

                    printf("                     The player %c denies\n", switchTurn(turn));

                    printf("                 Enter a number to continue\n");
                    scanf("%d", &dummy);
                }
            }
            else if (input == 3)
            {
                if (count_queue == 0)
                {
                    printf("Cannot review in the 0th move\n");
                    printf("Enter a number to continue\n");
                    scanf("%d", &dummy);
                }
                else
                    Reviewgame(q, count_queue);
            }
            else if (input == 4)
            {
                printf("                  Enter the number of moves(k):");
                scanf("%d", &k);
                allPossibleMoves(CheckerBoard, turn, k); 
                printf("\n                Enter a number to continue.\n");
                scanf("%d", &temp);
            }
            else
            {
                printf("                    Invalid Input. Try again!\n");
            }
        }
    }
    return 0;
}
#include <stdio.h>

// count of all possible numbers of length n
// in a given numeric keyboard
int get_count(char keypad[][3], int n)
{
    if (keypad == NULL || n <= 0) return 0;
    if (n == 1) return 10;

    // left, up, right, down move from current location
    int row[] = {0, 0, -1, 0, 1};
    int col[] = {0, -1, 0, 1, 0};

    // taking n+1 for simplicity
    // number count starting with digit i and length j
    int count[10][n + 1];
    int i = 0, j = 0, k = 0;
    int move = 0, ro = 0, co = 0, num = 0;
    int next_num = 0, total_count = 0;

    for (i = 0; i <= 9 ; ++i) {
        count[i][0] = 0;
        count[i][1] = 1;
    }

    // bottom up - get number count of length 2, 3, 4, ... , n
    for (k = 2; k <= n; ++k) {
        for (i = 0; i < 4; ++i) { // loop on keypad row
            for (j = 0; j < 3; ++j) { // loop on keypad column
                // process for 0 t0 9 digits
                if (keypad[i][j] != '*' && keypad[i][j] != '#')
                {
                    // counting numbers starting with
                    // digit keypad[i][j] and of length k keypad[i][j]
                    // will become 1st digit, and we need to look for
                    // (k-1) more digits
                    num = keypad[i][j] - '0';
                    count[num][k] = 0;

                    // move left, up, right, down from current location
                    // and if new location is valid, then get number
                    // count of length (k-1) from that new digit and
                    // add in count we found so far
                    for (move = 0; move < 5; ++move) {
                        ro = i + row[move];
                        co = j + col[move];
                        if (ro >= 0 && ro <= 3 && co >= 0 && co <= 2 &&
                            keypad[ro][co] != '*' && keypad[ro][co] != '#')
                        {
                            next_num = keypad[ro][co] - '0';
                            count[num][k] += count[next_num][k - 1];
                        }
                    }
                }
            }
        }
    }

    // get count of all possible numbers of length "n" starting
    // with digit 0, 1, 2, ... , 9
    total_count = 0;
    for (i = 0; i <= 9 ; ++i) {
        total_count += count[i][n];
    }

    return total_count;
}

int main() {
    char keypad[4][3] = {{'1', '2', '3'},
                         {'4', '5', '6'},
                         {'7', '8', '9'},
                         {'*', '0', '#'}};

    printf("Count for numbers of length %d: %d", 4, get_count(keypad, 4));

    return 0;
}

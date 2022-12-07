static void
run(int args, char** argv)
{
    assert(args == 2);
    FILE* file = fopen(argv[1], "r");

    char tower1[9][50] =
    {
        {'S', 'Z', 'P', 'D', 'L', 'B', 'F', 'C'},
        {'N', 'V', 'G', 'P', 'H', 'W', 'B'},
        {'F', 'W', 'B', 'J', 'G'},
        {'G', 'J', 'N', 'F', 'L', 'W', 'C', 'S'},
        {'W', 'J', 'L', 'T', 'P', 'M', 'S', 'H'},
        {'B', 'C', 'W', 'G', 'F', 'S'},
        {'H', 'T', 'P', 'M', 'Q', 'B', 'W'},
        {'F', 'S', 'W', 'T'},
        {'N', 'C', 'R'},
    };

    char tower2[9][50];
    memcpy(tower2, tower1, 9*50);

    u32 h1[9] = {7, 6, 4, 7, 7, 5, 6, 3, 2};
    u32 h2[9] = {7, 6, 4, 7, 7, 5, 6, 3, 2};

    u32 move, from, to;
    while(fscanf(file, " move %d from %d to %d", &move, &from, &to) == 3)
    {
        from -= 1;
        to -= 1;

        h2[to] += move;
        for(u32 i = 0; i < move; i++)
        {
            tower1[to][++h1[to]] = tower1[from][h1[from]--];
            tower2[to][h2[to] - i] = tower2[from][h2[from]--];
        }
    }

    char part1[10] = {};
    char part2[10] = {};
    for(u32 i = 0; i < 9; i++)
    {
        part1[i] = tower1[i][h1[i]];
        part2[i] = tower2[i][h2[i]];
    }
    printf("part 1: %s\n", part1);
    printf("part 2: %s\n", part2);
}
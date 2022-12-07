static u32
get_score_part_1(u32 a, u32 b)
{
    u32 result = b + 1;
    // draw
    if(a == b) result += 3;
    // win
    if(a == 0 && b == 1 ||
       a == 1 && b == 2 ||
       a == 2 && b == 0) result += 6;
    return result;
}

static u32
get_score_part_2(u32 a, u32 b)
{
    u32 rt[3][3] = {
    //   l  d  w
        {3, 1, 2}, // rock
        {1, 2, 3}, // paper
        {2, 3, 1}, // scissor
    };
    u32 result = b * 3 + rt[a][b];
    return result;
}

static void
run(int args, char** argv)
{
    assert(args == 2);
    FILE* file = fopen(argv[1], "r");

    u32 totalp1 = 0;
    u32 totalp2 = 0;
    char p[2];

    while(fscanf(file, " %c %c", p, p+1) == 2)
    {
        u32 scorep1 = get_score_part_1(p[0] - 'A', p[1] - 'X');
        u32 scorep2 = get_score_part_2(p[0] - 'A', p[1] - 'X');
        totalp1 += scorep1;
        totalp2 += scorep2;
    }

    printf("Part 1: %d\n", totalp1);
    printf("Part 2: %d\n", totalp2);
}
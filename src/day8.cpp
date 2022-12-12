static u32 visible = 0;
static u32
get_scene_score(u8* trees, u32 x, u32 y, u32 mx, u32 my)
{
    u32 score[4] = {};
    u32 h = trees[y * mx + x];
    b32 isVisible = false;

    s32 i;
    for(i = x + 1; i < mx; i++)
    {
        score[0]++;
        if(trees[y * mx + i] >= h) break;
    }
    if(i == mx) isVisible = true;

    for(i = x - 1; i >= 0; i--)
    {
        score[1]++;
        if(trees[y * mx + i] >= h) break;
    }
    if(i < 0) isVisible = true;

    for(i = y + 1; i < my; i++)
    {
        score[2]++;
        if(trees[i * mx + x] >= h) break;
    }
    if(i == my) isVisible = true;

    for(i = y - 1; i >= 0; i--)
    {
        score[3]++;
        if(trees[i * mx + x] >= h) break;
    }
    if(i < 0) isVisible = true;
    if(isVisible) visible++;

    return score[0] * score[1] * score[2] * score[3];
}

static void
run(int args, char** argv)
{
    assert(args == 2);
    FILE* file = fopen(argv[1], "r");

    u32 gridX = 0;
    u32 gridY = 0;

    char line[100];
    u8* trees = (u8*)malloc(100 * 100);

    while(fscanf(file, " %s", line) == 1)
    {
        if(gridX == 0) gridX = strlen(line);
        for(u32 x = 0; x < gridX; x++)
        {
            trees[gridY * gridX + x] = line[x] - '0';
        }
        gridY++;
    }

    u32 bestScore = 0;

    for(u32 y = 0; y < gridY; y++)
    {
        for(u32 x = 0; x < gridX; x++)
        {
            u32 score = get_scene_score(trees, x, y, gridX, gridY);
            bestScore = MAX(bestScore, score);
        }
    }

    printf("Part 1: %d\n", visible);
    printf("Part 2: %d\n", bestScore);
}
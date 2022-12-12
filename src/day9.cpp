struct Pos
{
    s32 x, y;
};

static void
run(int args, char** argv)
{
    assert(args == 2);
    FILE* file = fopen(argv[1], "r");

    char dir;
    u32 steps;

    const u32 N = 1000;
    Pos knots[10] = {};
    u8 positions[N][N] = {};
    u32 offset = N/2;

    positions[offset][offset] = 1;
    u32 tailPositionsP1 = 1;
    u32 tailPositionsP2 = 1;

    while(fscanf(file, " %c %d", &dir, &steps) == 2)
    {
        for(u32 step = 0; step < steps; step++)
        {
            // move head
            switch(dir)
            {
                case 'R': knots[0].x++; break;
                case 'L': knots[0].x--; break;
                case 'U': knots[0].y++; break;
                case 'D': knots[0].y--; break;
            }

            for(u32 n = 1; n < 10; n++)
            {
                Pos p1 = knots[n-1];
                Pos p2 = knots[n];
                s32 xDiff = p1.x - p2.x;
                s32 yDiff = p1.y - p2.y;
                s32 xDiffAbs = abs(xDiff);
                s32 yDiffAbs = abs(yDiff);

                if(xDiffAbs > 1 || yDiffAbs > 1)
                {
                    if(xDiffAbs > 0) // this one got me YEP (division by 0)
                        knots[n].x += xDiff / xDiffAbs;
                    if(yDiffAbs > 0)
                        knots[n].y += yDiff / yDiffAbs;

                    // part 1
                    if(n == 1 && (positions[offset + knots[n].y][offset + knots[n].x] & 1) == 0)
                    {
                        positions[offset + knots[n].y][offset + knots[n].x] |= 1;
                        tailPositionsP1++;
                    }
                    // part 2
                    if(n == 9 && (positions[offset + knots[n].y][offset + knots[n].x] & 2) == 0)
                    {
                        positions[offset + knots[n].y][offset + knots[n].x] |= 2;
                        tailPositionsP2++;
                    }
                }
            }
        }
    }

    printf("Part 1: %d\n", tailPositionsP1);
    printf("Part 2: %d\n", tailPositionsP2);
}
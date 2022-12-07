static void
run(int args, char** argv)
{
    assert(args == 2);
    FILE* file = fopen(argv[1], "r");

    s32 total = 0;
    s32 big[3] = {};
    char buffer[20];
    char* res = buffer;
    while(res)
    {
        res = fgets(buffer, 100, file);
        s32 number;
        if(res == 0 || sscanf(buffer, "%d", &number) < 1)
        {
            u32 is = 0;
            for(u32 i = 1; i < 3; i++)
            {
                if(big[is] > big[i]) is = i;
            }
            if(total > big[is]) big[is] = total;
            total = 0;
        }
        else
        {
            total += number;
        }
    }
    printf("Part 1: %d\n", MAX(MAX(big[0], big[1]), big[2]));
    printf("Part 2: %d\n", big[0] + big[1] + big[2]);
}
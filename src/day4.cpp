static u32
test_overlap(u32 s1s, u32 s1e, u32 s2s, u32 s2e)
{
    u32 result = 0;
    if(s1s >= s2s && s1e <= s2e ||
       s2s >= s1s && s2e <= s1e)
        result = 1;
    return result;
}

static u32
test_overlap_full(u32 s1s, u32 s1e, u32 s2s, u32 s2e)
{
    u32 result = 0;
    if(s1s >= s2s && s1s <= s2e ||
       s2s >= s1s && s2s <= s1e)
        result = 1;
    return result;
}

static void
run(int args, char** argv)
{
    assert(args == 2);
    FILE* file = fopen(argv[1], "r");

    u32 s1s, s2s, s1e, s2e;
    u32 overlapTotal = 0;
    u32 overlapFullTotal = 0;

    while(fscanf(file, "%d-%d,%d-%d", &s1s, &s1e, &s2s, &s2e) == 4)
    {
        u32 overlap = test_overlap(s1s, s1e, s2s, s2e);
        u32 overlapFull = test_overlap_full(s1s, s1e, s2s, s2e);
        overlapTotal += overlap;
        overlapFullTotal += overlapFull;
    }

    printf("Part 1: %d\n", overlapTotal);
    printf("Part 2: %d\n", overlapFullTotal);
}
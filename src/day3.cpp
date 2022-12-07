#include "string.h"

static u32
get_prio_single(char* line, u32 len)
{
    u32 result = 0;
    u8 items[52] = {};
    for(u32 i = 0; i < len; i++)
    {
        u8 it = line[i] <= 'Z' ? line[i] - 'A' + 26 : line[i] - 'a';
        if(i < len /2)
            items[it] = 1;
        else if(items[it] == 1)
            result = it + 1;
    }
    return result;
}

static u32
get_prio_group(u8 items[52], u32 count, char* line, u32 len)
{
    u32 result = 0;
    for(u32 i = 0; i < len; i++)
    {
        u8 it = line[i] <= 'Z' ? line[i] - 'A' + 26 : line[i] - 'a';
        if(count == 0)
            items[it] = 1;
        else if (count == 1)
            items[it] |= 2;
        else if(count == 2 && items[it] == 3)
            result = it + 1;
    }
    return result;
}

static void
run(int args, char** argv)
{
    assert(args == 2);
    FILE* file = fopen(argv[1], "r");

    char buffer[100];
    u32 prioSum = 0;
    u32 prioSumGroup = 0;
    u8 itemsGroup[52] = {};
    u32 count = 0;

    while(fscanf(file, "%s", buffer) == 1)
    {
        u32 prio = get_prio_single(buffer, strlen(buffer));
        prioSum += prio;

        u32 prioGroup = get_prio_group(itemsGroup, count, buffer, strlen(buffer));
        count++;
        if(count == 3)
        {
            prioSumGroup += prioGroup;
            count = 0;
            memset(itemsGroup, 0, 52);
        }
    }

    printf("Part 1: %d\n", prioSum);
    printf("Part 2: %d\n", prioSumGroup);
}
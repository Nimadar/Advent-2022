static u32
parse_message(char* data, u32 len, u32 messageLen)
{
    u32 at = 0;
    while(at + messageLen < len)
    {
        b32 isStart = true;
        for(u32 i = at; isStart && i < at + messageLen; i++)
        {
            for(u32 ii = i + 1; ii < at + messageLen; ii++)
            {
                if(data[i] == data[ii])
                {
                    isStart = false;
                    at = i;
                }
            }
        }
        if(isStart) break;
        at++;
    }
    return at + messageLen;
}

static void
run(int args, char** argv)
{
    assert(args == 2);
    FILE* file = fopen(argv[1], "r");

    char* data = (char*)malloc(5000);
    fscanf(file, "%s", data);
    u32 len = strlen(data);

    printf("part 1: %d\n", parse_message(data, len, 4));
    printf("part 2: %d\n", parse_message(data, len, 14));
}
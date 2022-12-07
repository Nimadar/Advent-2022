struct Folder
{
    u32 size;
    u32 count;
    Folder* c[10];
    Folder* p;
};

static u32
traverse_size(Folder* f, u32* sum)
{
    u32 size = f->size;
    for(u32 i = 0; i < f->count; i++)
    {
        size += traverse_size(f->c[i], sum);
    }
    if(size < 100000) *sum += size;
    return size;
}

static u32
traverse_delete(Folder* f, u32 needed, u32* tf)
{
    u32 size = f->size;
    for(u32 i = 0; i < f->count; i++)
    {
        size += traverse_delete(f->c[i], needed, tf);
    }
    u32 diff = size - needed;
    u32 diff1 = *tf - needed;
    if(size >= needed && diff < diff1) *tf = size;
    return size;
}

static void
run(int args, char** argv)
{
    assert(args == 2);
    FILE* file = fopen(argv[1], "r");

    char line[100];
    Folder folders[200] = {};
    u32 used = 0;

    Folder* folder = 0;
    while(fgets(line, 100, file))
    {  
        if(line[0] == '$' && line[2] == 'c')
        {   
            if(line[5] == '.' && line[5] == '.')   
                folder = folder->p;
            else
            {
                Folder* p = folder;
                folder = &folders[used++];
                if(p)
                {
                    p->c[p->count++] = folder;
                    folder->p = p;
                }
            }   
        }
        else if(line[0] == '$' && line[2] == 'l');
        else
        {
            u32 size;
            if(sscanf(line, "%d", &size) == 1)
                folder->size += size;
        }
    }

    u32 part1 = 0;
    u32 part2 = 70000000;
    u32 totalSize = traverse_size(folders, &part1);
    u32 needed = 30000000 - (70000000 - totalSize);
    traverse_delete(folders, needed, &part2);

    printf("Part 1: %d\n", part1);
    printf("Part 2: %d\n", part2);
}
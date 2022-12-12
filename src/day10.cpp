enum Op
{
    OP_NOOP,
    OP_ADDX,
};

struct Instruction
{
    Op op;
    u32 cycles;
    s32 p;
};

struct VM
{
    s32 x;
    Instruction queued;
};

static void
run(int args, char** argv)
{
    assert(args == 2);
    FILE* file = fopen(argv[1], "r");

    Instruction program[200];
    u32 opsCount = 0;

    char opString[10];
    s32 param[1];

    while(fscanf(file, " %s %d", opString, param) >= 1)
    {
        if(opString[0] == 'n') program[opsCount++] = {OP_NOOP, 1, 0};
        if(opString[0] == 'a') program[opsCount++] = {OP_ADDX, 2, param[0]};
    }

    s32 total = 0;
    VM vm = {1, program[0]};
    u32 p = 0;
    
    for(u32 cycle = 1; cycle <= 240; cycle++)
    {
        if(cycle <= 220 && (cycle == 20 || (cycle + 20) % 40 == 0))
        {
            total += cycle * vm.x;
        }
        
        // sprite
        s32 crt = (cycle-1) % 40;
        if(vm.x == crt || vm.x-1 == crt || vm.x+1 == crt)
            printf("#");
        else
            printf(" ");
        if(cycle % 40 == 0) printf("\n");
        
        // step
        if(--vm.queued.cycles == 0)
        {
            switch(vm.queued.op)
            {
                case OP_NOOP: break;
                case OP_ADDX: vm.x += vm.queued.p;
            }
            // increment program pointer
            p = (p + 1) % opsCount;

            Instruction nextInstruction = program[p];
            vm.queued = nextInstruction;
        }
    }

    printf("Part 1: %d\n", total);
}
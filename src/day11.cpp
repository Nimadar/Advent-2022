enum Opcode
{
    OP_ADD,
    OP_MUL
};

enum Register
{
    REG_VAL,
    REG_OLD,
};

struct Operation
{
    Opcode opcode;
    Register regs[2];
    u64 value;
};

struct MonkeyProgram
{
    u64 items[10][30];
    u32 itemCount[10];
    Operation ops[10];
    u64 test[10];
    u64 testLookup[10][2];
    u32 monkeyCount;
    u64 maxValue;
};

static MonkeyProgram
get_test_mp()
{
    MonkeyProgram mp = {
        {
            {79, 98},
            {54, 65, 75, 74},
            {79, 60, 97},
            {74},
        },
        {2, 4, 3, 1},
        {
            {OP_MUL, {REG_OLD, REG_VAL}, 19},
            {OP_ADD, {REG_OLD, REG_VAL}, 6},
            {OP_MUL, {REG_OLD, REG_OLD}, 0},
            {OP_ADD, {REG_OLD, REG_VAL}, 3},
        },
        {23, 19, 13, 17}, // test value
        {
            {2, 3},
            {2, 0},
            {1, 3},
            {0, 1},
        },
        4,  // number of monkeys
        1,  // pervent overflow
    };
    return mp;
};

static MonkeyProgram
get_mp()
{
    MonkeyProgram mp = {
        {
            {56, 52, 58, 96, 70, 75, 72},
            {75, 58, 86, 80, 55, 81},
            {73, 68, 73, 90},
            {72, 89, 55, 51, 59},
            {76, 76, 91},
            {88},
            {64, 63, 56, 50, 77, 55, 55, 86},
            {79, 58},
        },
        {7, 6, 4, 5, 3, 1, 8, 2},
        {
            {OP_MUL, {REG_OLD, REG_VAL}, 17},
            {OP_ADD, {REG_OLD, REG_VAL}, 7},
            {OP_MUL, {REG_OLD, REG_OLD}, 0},
            {OP_ADD, {REG_OLD, REG_VAL}, 1},
            {OP_MUL, {REG_OLD, REG_VAL}, 3},
            {OP_ADD, {REG_OLD, REG_VAL}, 4},
            {OP_ADD, {REG_OLD, REG_VAL}, 8},
            {OP_ADD, {REG_OLD, REG_VAL}, 6},
        },
        {11, 3, 5, 7, 19, 2, 13, 17}, // test value
        {
            {2, 3},
            {6, 5},
            {1, 7},
            {2, 7},
            {0, 3},
            {6, 4},
            {4, 0},
            {1, 5},
        },
        8,  // number of monkeys
        1,  // max value to prevent overflow
    };
    return mp;
};

static void
step_monkeys(MonkeyProgram* mp, u32 inspections[10])
{
    for(u32 im = 0; im < mp->monkeyCount; im++)
    {
        while(mp->itemCount[im] != 0)
        {
            // take the first item
            u64 old = mp->items[im][0];
            for(u32 i = 1; i < mp->itemCount[im]; i++)
            {
                mp->items[im][i-1] = mp->items[im][i];
            }
            mp->itemCount[im]--;
            inspections[im]++;

            u64 worry = 0;
            u64 regs[2] = {mp->ops[im].value, old};
            switch(mp->ops[im].opcode)
            {
                case OP_ADD:
                    {
                        worry = regs[mp->ops[im].regs[0]] + regs[mp->ops[im].regs[1]];
                    } break;
                case OP_MUL:
                    {
                        worry = regs[mp->ops[im].regs[0]] * regs[mp->ops[im].regs[1]];
                    } break;
            }

            u64 div = worry % mp->test[im];
            u32 nextMonkey;
            if(div == 0) nextMonkey = mp->testLookup[im][0];
            else nextMonkey = mp->testLookup[im][1];

            // to prevent numbers to get out of hand they can be modded by the biggest number all of them can reach together
            worry = worry % mp->maxValue;

            mp->items[nextMonkey][mp->itemCount[nextMonkey]++] = worry;
            assert(mp->itemCount[nextMonkey] < 30);
        }
    }
}

static void
run(int args, char** argv)
{
    MonkeyProgram mp = get_mp();
    u32 inspections[10] = {};

    for(u32 i = 0; i < mp.monkeyCount; i++)
        mp.maxValue *= mp.test[i];

    for(u32 step = 0; step < 10000; step++)
        step_monkeys(&mp, inspections);

    u64 mb[2] = {};
    for(u32 i = 0; i < mp.monkeyCount; i++)
    {
        printf("%d\n", inspections[i]);
        if(inspections[i] > mb[0]) mb[0] = inspections[i];
        else if(inspections[i] > mb[1]) mb[1] = inspections[i];
        if(mb[0] > mb[1])
        {
            u32 tmp = mb[0];
            mb[0] = mb[1];
            mb[1] = tmp;
        }
    }

    printf("Part 1: %lld\n", mb[0] * mb[1]);
}
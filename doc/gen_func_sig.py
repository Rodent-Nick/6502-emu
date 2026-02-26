import csv as c
instructions = []

with open('opcodes.txt', 'r') as f:
    lines = f.readlines()
    for i in range(len(lines)):

        if lines[i].strip('\n') == '---':
            continue

        line = lines[i].split(' ')
        print(line)
        instructions.append(['%02X'%(i,), line[0], line[1].strip('\n')])

sig_pat = 'static void Operation%s(Memory &mem, Registers &reg, ALU &alu);\n'
def_pat = """
void Processor::Operation%s(Memory &mem, Registers &reg, ALU &alu)
{
    /// Mnemonics %s (Address mode: %s)
    byte opcode = 0x%s;

    return;
}
"""
bind_pat = 'this->instructions[0x%s] = Operation%s;\n'

with open('output_sig.txt', 'w') as f:
    for inst in instructions:
        f.write(sig_pat%(inst[0]))

with open('output_def.txt', 'w') as f:
    for inst in instructions:
        f.write(def_pat%(inst[0], inst[1], inst[2], inst[0]))

with open('output_bind.txt', 'w') as f:
    for inst in instructions:
        f.write(bind_pat%(inst[0], inst[0]))

import csv as c
instructions = []

with open('opcodes.csv', 'r') as f:
    reader = c.reader(f)
    for line in reader:
        instructions.append(line)

sig_pat = 'static void Operation%s(Memory &mem, Registers &reg, ALU &alu);\n'
def_pat = """
void Processor::Operation%s(Memory &mem, Registers &reg, ALU &alu)
{
    /// Mnemonics %s (Address mode: %s)
    byte opcode = 0x%s;

    return;
}
"""

with open('output_sig.txt', 'w') as f:
    for inst in instructions:
        f.write(sig_pat%(inst[0]))

with open('output_def.txt', 'w') as f:
    for inst in instructions:
        f.write(def_pat%(inst[0], inst[1], inst[2], inst[0]))

instructions = []


with open('oplist.tsv', 'r') as f:
    lines = f.readlines()
    for line in lines:
        params = line.split('\t')
        instruction = {}
        instruction['opcode'] = params[2]
        instruction['mnemonics'] = params[1][:3]
        instruction['address mode'] = params[0]
        instruction['byte length'] = params[3]
        instruction['cycles'] = params[4]
        instructions.append(instruction)

with open('oplist.csv', 'w') as f:
    for instruction in instructions:
        row_pat = '%s,%s,\"%s\",%s,%s'
        f.write(row_pat%(
            instruction['mnemonics'],
            instruction['opcode'],
            instruction['address mode'],
            instruction['byte length'],
            instruction['cycles']
            ))



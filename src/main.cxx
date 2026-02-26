#include <fstream>

#include "mem.hxx"
#include "reg.hxx"
#include "processor.hxx"

static const std::regex hexPattern("^(0x)?[0-9a-fA-F]+$");

void ShowMemory(Memory &mem, word head, byte count = 0xf){

    word real_head = head / 0x10;
    real_head *= 0x10;
    byte offset = head - real_head;
    byte lines = ceil((count + offset) / 16);

    printf("     ");
    for (int i = 0; i < 16; i++)
        printf(" +%X", i);
    printf("\n");

    for (int line = 0; line < lines; line++){
        if (real_head + line * 0x10 > 0xffff)
            break;
        printf("%04X:", real_head + line * 0x10);
        for (int col = 0; col < 16; col++){
            printf(" %02X", mem.PeekByte(real_head + line * 0x10 + col));
        }
        printf("\n");
    }
    
    return;
}

void ShowRegister(Processor &proc){

    printf("A  X  Y  S  P    CZIDB-VN (LE)\n");
    printf("%02x %02x %02x %02x %04x ",
        proc.reg.ac,
        proc.reg.xr,
        proc.reg.yr,
        proc.reg.sp,
        proc.reg.pc
    );
    
    for (int i = 0; i < 8; i++){
        printf("%d", bool(proc.reg.sr[i]));
    }

    printf("\n");

    return;
}

std::vector<std::string> splitInput(const std::string& input) {
    std::vector<std::string> tokens;
    std::istringstream iss(input);
    std::string token;
    while (iss >> token) {
        tokens.push_back(token);
    }
    return tokens;
}

int main(int argc, char** argv){

    Memory mem{};
    Processor proc{mem};
    std::string buf;

    printf("6502 Emulator by @Rodent-Nick\nVersion %s\n", VERSION_STRING);
    printf("------------------------------------------\n");
    printf("https://github.com/Rodent-Nick/6502-emu\n");
    printf("------------------------------------------\n");

    while (true) {

        printf(">");
        std::getline(std::cin, buf);

        auto vec = splitInput(buf);

        if (vec[0] == "stop" || vec[0] == "exit") {
            break;
        }

        if (vec[0] == "load") {
            if (vec.size() < 3) {
                printf("Usage: load <file-addr> <mem-head>\n");
                continue;
            }

            if (!std::filesystem::exists(vec[1])) {
                printf("No such file: %s\n", vec[1].c_str());
                continue;
            }

            if (!std::regex_match(vec[2], hexPattern)) {
                printf("Not a hex value: %s\n", vec[2].c_str());
                continue;
            }

            word offset = std::stoul(vec[2], nullptr, 16);
            
            std::ifstream file(vec[1], std::ios::binary);
            if (!file) {
                std::cerr << "Failed to open file: " << vec[1] << std::endl;
                break;
            }

            // Read the file into a buffer
            std::vector<byte> buffer(
                (std::istreambuf_iterator<char>(file)), 
                std::istreambuf_iterator<char>());
            file.close();
            
            for (auto b : buffer) {
                mem.PutByte(offset++, b);
            }

            printf("Load %d bytes into memory.\n", buffer.size());
            continue;

        }

        if (vec[0] == "setr") {

            if (vec.size() < 3) {
                printf("Usage: setr <register> <value>\n");
                printf("Register can be: a x y s p sr\n");
                continue;
            }

            std::array<std::string, 6> regs = {
                "a", "x", "y", "s", "p", "sr"
            };
            auto res = std::find(regs.begin(), regs.end(), vec[1]);

            if (
                res == regs.end()
            ) {
                printf("No such register.\n");
                printf("Register can be: a x y s p sr\n");
                continue;
            }

            if (!std::regex_match(vec[2], hexPattern)) {
                printf("Not a hex value: %x\n", vec[2].c_str());
                continue;
            }

            if (vec[1] == "a") {
                proc.reg.ac = std::stoul(vec[2], nullptr, 16);
                printf(
                    "Register AC set to %02x\n", 
                    std::stoul(vec[2], nullptr, 16));
                continue;
            }

            if (vec[1] == "x") {
                proc.reg.xr = std::stoul(vec[2], nullptr, 16);
                printf(
                    "Register X set to %02x\n", 
                    std::stoul(vec[2], nullptr, 16));
                continue;
            }

            if (vec[1] == "y") {
                proc.reg.yr = std::stoul(vec[2], nullptr, 16);
                printf(
                    "Register Y set to %02x\n", 
                    std::stoul(vec[2], nullptr, 16));
                continue;
            }

            if (vec[1] == "s") {
                proc.reg.sp = std::stoul(vec[2], nullptr, 16);
                printf(
                    "Register S set to %02x\n", 
                    std::stoul(vec[2], nullptr, 16));
                continue;
            }

            if (vec[1] == "p") {
                proc.reg.pc = std::stoul(vec[2], nullptr, 16);
                printf(
                    "Register PC set to %04x\n", 
                    std::stoul(vec[2], nullptr, 16));
                continue;
            }

            if (vec[1] == "sr") {
                proc.reg.sr = std::stoul(vec[2], nullptr, 16);
                printf(
                    "Register SR set to %02x\n", 
                    std::stoul(vec[2], nullptr, 16));
                continue;
            }

        }

        if (vec[0] == "showm") {

            if (vec.size() < 2) {
                printf("Usage: showm <mem-head> <size>\n");
                continue;
            }

            if (vec.size() == 2) {
                vec.push_back(std::string("10"));
            }

            if (!std::regex_match(vec[1], hexPattern)) {
                printf("Not a hex value: %x\n", vec[1].c_str());
                continue;
            }

            if (!std::regex_match(vec[2], hexPattern)) {
                printf("Not a hex value: %x\n", vec[2].c_str());
                continue;
            }

            ShowMemory(
                mem, 
                std::stoul(vec[1], nullptr, 16), 
                std::stoul(vec[2], nullptr, 16)
            );

            continue;
        }

        if (vec[0] == "showr") {

            ShowRegister(proc);

            continue;
        }

        if (vec[0] == "run") {

            while (proc.NextCycle());

            printf("Execution hit BRK and stopped.\n");
            continue;
        }

        if (vec[0] == "reset") {
            proc.ResetProcessor();
            printf("Emulator reset.\n");
            continue;
        }

        if (vec[0] == "dbg") {
            proc.alu.show_debug = true;
            printf("ALU-level debug enabled.\n");
            continue;
        }

        if (vec[0] == "ndb") {
            proc.alu.show_debug = false;
            printf("ALU-level debug disabled.\n");
            continue;
        }

        if (vec[0] == "help") {
            printf("load <file-addr> <mem-head>\n");
            printf("\tLoad a hex file into memory location <mem-head>.\n");
            printf("\t<mem-head> should be hexidecimal.\n");
            printf("\n");
            printf("setr <register> <value>\n");
            printf("\tSet a register to a certain hexidecimal value.\n");
            printf("\tPossible register: a x y s p sr\n");
            printf("\n");
            printf("showm <mem-head> <size>\n");
            printf("\tShow the selected section of memory.\n");
            printf("\n");
            printf("showr <mem-head> <size>\n");
            printf("\tShow register status.\n");
            printf("\n");
            printf("run\n");
            printf("\tRun until hit a BRK ($00) instruction.\n");
            printf("\n");
            printf("dbg\n");
            printf("\tEnable ALU-level debug and show information each time\n");
            printf("\tA arithmetic/logical/comparison operation is done.\n");
            printf("\n");
            printf("ndb\n");
            printf("\tDisable ALU-level debug.\n");
            printf("\n");
            printf("stop\n");
            printf("\tStop the whole simulator and exit the program.\n");
            printf("\n");
            continue;
        }

        printf(
            "No such command: %s\n Enter \"help\" for help\n", 
            vec[0].c_str());

    }
    
    return EXIT_SUCCESS;
}
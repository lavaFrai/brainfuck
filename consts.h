#pragma once

const char* help = "\nlava brainfuck interpreter help:\n\n"
                   "Run syntax:\tbrainfuck [-ex] [-adv] [-c<cell size>] <path>\n"
                   "\t-stack\t\t\tuse extended stack instructions set\n"
                   "\t-IO\t\t\tuse extended IO registers instructions set\n"
                   "\t-c<cell size>\t\tsize of memory cell in bits [-c8 / -c16]\n"
                   "\t<path>\t\t\tpath to file with brainfuck code\n\n"
                   "Example: brainfuck -stack -c8 main.bf\n";

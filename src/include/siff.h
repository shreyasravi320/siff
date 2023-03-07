#ifndef SIFF_H
#define SIFF_H

#include <string>
#include <fstream>
#include <iostream>
#include "array.h"

class Siff
{
public:
    Siff(std::string file_1, std::string file_2);
    ~Siff();

private:
    struct Line
    {
        std::string data;
        int num;

        Line()
        {
            data = "";
            num = 0;
        }

        Line(std::string s, int n)
        {
            data = std::string(s);
            num = n;
        }

        ~Line() {}
    };

    struct Edit
    {
        enum Type
        {
            INSERT,
            DELETE,
            EQUAL
        };

        Type type;
        std::string old_line, new_line;

        Edit(Type t, std::string o, std::string n)
        {
            type = t;
            old_line = std::string(o);
            new_line = std::string(n);
        }
    };

    void read_lines(array<Line *> &lines, std::string input);
    void backtrack(array<Line *> &lines_1, array<Line *> &lines_2);
    void siff(array<Line *> &lines_1, array<Line *> &lines_2);

    array<array<int>> trace;
    array<Edit> edits;
};

#endif

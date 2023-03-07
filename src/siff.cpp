#include "include/siff.h"

Siff::Siff(std::string file_1, std::string file_2)
{
    array<Line *> lines_1, lines_2;
    read_lines(lines_1, file_1);
    read_lines(lines_2, file_2);

    siff(lines_1, lines_2);

    // std::cout << "\033[1;31mTESTING\033[0m\n";
      // del:     "\e[31m",
      // ins:     "\e[32m",
      // default: "\e[39m"
    for (int i = edits.size() - 1; i >= 0; i--)
    {
        switch (edits[i].type)
        {
            case Edit::Type::INSERT:
            {
                std::cout << "\033[32m+\t" << edits[i].old_line << "\t" << edits[i].new_line << "\033[0m\n";
                break;
            }
            case Edit::Type::DELETE:
            {
                std::cout << "\033[31m-\t" << edits[i].old_line << "\t" << edits[i].new_line << "\033[0m\n";
                break;
            }
            case Edit::Type::EQUAL:
            {
                std::cout << "\033[39m=\t" << edits[i].old_line << "\t" << edits[i].new_line << "\033[0m\n";
                break;
            }
        }
    }

    for (int i = 0; i < lines_1.size(); i++)
    {
        delete lines_1[i];
    }

    for (int i = 0; i < lines_2.size(); i++)
    {
        delete lines_2[i];
    }
}

Siff::~Siff() {}

void Siff::read_lines(array<Line *> &lines, std::string input)
{
    std::ifstream in(input);
    std::string data;
    int num = 0;

    while (getline(in, data))
    {
        if (!in.eof()) lines.pushb(new Line(data, ++num));
    }

    in.close();
}

void Siff::backtrack(array<Line *> &lines_1, array<Line *> &lines_2)
{
    array<int> path;
    int x = lines_1.size(), y = lines_2.size();
    for (int d = trace.size() - 1; d >= 0; d--)
    {
        array<int> v = trace[d];
        int k = x - y;
        int prev_x, prev_y, prev_k;

        if (k == -d || (k != d && v[k - 1] < v[k + 1]))
        {
            prev_k = k + 1;
        }
        else
        {
            prev_k = k - 1;
        }

        prev_x = v[prev_k];
        prev_y = prev_x - prev_k;

        while (x > prev_x && y > prev_y)
        {
            path.pushb(x - 1);
            path.pushb(y - 1);
            path.pushb(x);
            path.pushb(y);

            // std::cout << "(" << x - 1 << ", " << y - 1 << ") -> (" << x << ", " << y << ")\n";
            x--, y--;
        }

        if (d > 0)
        {
            path.pushb(prev_x);
            path.pushb(prev_y);
            path.pushb(x);
            path.pushb(y);

            // std::cout << "(" << prev_x << ", " << prev_y << ") -> (" << x << ", " << y << ")\n";
            x = prev_x, y = prev_y;
        }
    }

    x = 0, y = 0;
    for (int i = 0; i < path.size(); i += 4)
    {
        int prev_x = path[i], prev_y = path[i + 1];
        x = path[i + 2], y = path[i + 3];

        if (x == prev_x)
        {
            edits.pushb(Edit(Edit::Type::INSERT, "", lines_2[prev_y]->data));
        }
        else if (y == prev_y)
        {
            edits.pushb(Edit(Edit::Type::DELETE, lines_1[prev_x]->data, ""));
        }
        else
        {
            edits.pushb(Edit(Edit::Type::EQUAL, lines_1[prev_x]->data, lines_2[prev_y]->data));
        }
    }
}

void Siff::siff(array<Line *> &lines_1, array<Line *> &lines_2)
{
    const int n = lines_1.size(), m = lines_2.size();
    const int max = n + m;

    array<int> v(max * 2 + 1, 0);

    for (int d = 0; d <= max; d++)
    {
        trace.pushb(v);
        for (int k = -d; k <= d; k += 2)
        {
            int x;
            if (k == -d || (k != d && v[k - 1] < v[k + 1]))
            {
                x = v[k + 1];
            }
            else
            {
                x = v[k - 1] + 1;
            }

            int y = x - k;

            while (x < n && y < m && lines_1[x]->data == lines_2[y]->data)
            {
                x++, y++;
            }

            v[k] = x;

            if (x >= n && y >= m)
            {
                std::cout << d << "\n";
                backtrack(lines_1, lines_2);
                return;
            }
        }
    }

    std::cout << 0 << "\n";
}

#undef CURSOR_INVIS

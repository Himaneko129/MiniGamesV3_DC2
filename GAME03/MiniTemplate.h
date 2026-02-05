#pragma once
#include <array>
#include <vector>
#include <utility>

enum DIR { NONE, UP, DOWN, LEFT, RIGHT };

struct MiniTemplate {
    std::array<std::array<int, 3>, 3> cell{};   // 0=“¹, 1=•Ç
    std::vector<std::pair<int, int>> mainPath;  // šin/out•û®‚Å‚Í¶¬‚Éì‚é
    DIR arrow[3][3]{};

    int startX = 0, startY = 0;
    int goalX = 0, goalY = 0;
};

extern const std::vector<MiniTemplate> g_miniTemplates;

void buildArrowFromPath(MiniTemplate& t);

MiniTemplate rotate90(const MiniTemplate& src);
MiniTemplate rotate180(const MiniTemplate& src);
MiniTemplate rotate270(const MiniTemplate& src);
MiniTemplate flipHorizontal(const MiniTemplate& src);
std::vector<MiniTemplate> generateVariants(const MiniTemplate& base);


#include "AppMvc.h"

namespace MVC
{
    Node::Node(short ID, const char *name, int Color, int Icon, float coord[2])
    {
        this->ID = ID;
        strcpy(this->name, name);
        this->Color = Color;
        this->Icon = Icon;
        this->coord[0] = coord[0];
        this->coord[1] = coord[1];
    }
} // namespace mvc

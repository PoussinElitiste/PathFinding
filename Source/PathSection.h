#ifndef PATH_SECTION_H
#define PATH_SECTION_H

//class PathNode;
struct PathSection
{
public:
    PathSection() = delete;
    PathSection(PathNode *node):
        targetNode(node),
        parentSection{},
        totalDistance(std::numeric_limits<double>::max())
    {}

    PathNode *targetNode;
    PathSection *parentSection;
    double totalDistance;
};

#endif // PATH_SECTION_H
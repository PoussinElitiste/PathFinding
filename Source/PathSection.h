#ifndef PATH_SECTION_H
#define PATH_SECTION_H

struct PathSection
{
public:
    PathSection():
        parentSection{},
        totalDistance(std::numeric_limits<double>::max())
    {}

    PathSection *parentSection;
    double totalDistance;
};

#endif // PATH_SECTION_H
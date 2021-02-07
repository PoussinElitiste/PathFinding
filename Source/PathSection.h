#ifndef PATH_SECTION_H
#define PATH_SECTION_H

class PathSection
{
public:
    PathSection(PathNode *n1, PathNode *n2, double iWeight):
        mNode1(n1), mNode2(n2), mWeigt(iWeight)
    {}

private:
    PathNode *mNode1, *mNode2;
    double mWeigt;
};

#endif // PATH_SECTION_H
#ifndef PATH_SECTION_H
#define PATH_SECTION_H

class PathSection
{
public:
    PathSection(PathNode *n1, PathNode *n2):
        mNode1(n1), mNode2(n2), mWeigt(std::numeric_limits<double>::max())
    {
        if (!n1 || !n2)
        {
            printf("[ERROR] invalid node");
            return;
        }
        else
        {
            Vertex distance = n1->GetVertex() - n2->GetVertex();
            mWeigt = distance.length();
        }
    }

private:
    PathNode *mNode1, *mNode2;
    double mWeigt;
};

#endif // PATH_SECTION_H
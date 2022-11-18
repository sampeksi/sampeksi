#include "book.hh"

using namespace std;

Book::Book()
{

}

Book::~Book()
{

}

void Book::addNewChapter(const std::string &id,
                         const std::string &fullName, int length)
{


    Chapter* new_chapter = new Chapter{id, fullName, length, nullptr, {}};

    chapters.push_back(new_chapter);
}

void Book::addRelation(const std::string &subchapter,
                       const std::string &parentChapter)
{
   Chapter* sub = findChapter(subchapter);
   Chapter* parent = findChapter(parentChapter);

   sub->parentChapter_ = parent;
   parent->subchapters_.push_back(sub);

}

void Book::printIds(Params params) const
{

}

Chapter *Book::findChapter(const std::string &id) const
{
    for (auto& chap : chapters) {
        if (chap->id_ == id) {
            return chap;
        }
    }
}




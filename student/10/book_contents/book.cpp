#include "book.hh"
#include <map>

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
   if (parentChapter != EMPTY) {
        Chapter* parent = findChapter(parentChapter);

        sub->parentChapter_ = parent;
        parent->subchapters_.push_back(sub);
   }

}

void Book::printIds(Params params) const
{
    vector<string> irrelevant = params;
    cout << "Book has " << chapters.size() << " chapters:" <<endl;
    map<string,string> ids;

    for (auto& chap : chapters) {
        ids.insert({chap->fullName_, chap->id_});

    }
    for (auto& pair : ids) {
        cout << pair.first << " --- " << pair.second <<endl;
    }
}



void Book::printContents(Params params) const
{
    vector<string> irrelevant = params;
    int count = 1;
    string mark;
    for (auto& chap : chapters) {
        if (chap->parentChapter_ == nullptr) {
            if (!chap->open_) {
                mark = "+";
            }
            else {
                mark = "-";
            }
            cout << mark << " " << count << ". " << chap->fullName_ << " ( " <<
                    chap->length_ << " )" <<endl;
            if (chap->open_) {
            print_subchapters(chap->subchapters_);
            }
            count += 1;
        }
    }
}

void Book::close(Params params) const
{
    for (auto& chap : chapters) {
        if (chap->id_ == params[0]) {
            chap->open_ = false;
            break;
        }
    }
}

void Book::open(Params params) const
{
    for (auto& chap : chapters) {
        if (chap->id_ == params[0]) {
            chap->open_ = true;
            break;
        }
    }
}

void Book::openAll(Params params) const
{
    vector<string> irrelevant = params;

    for (auto& chap : chapters) {
        chap->open_ = true;
    }
}

void Book::print_subchapters(vector<Chapter*> subs,int count,
                             string indent) const
{
    indent += "  ";
    string mark;
    for (auto& sub : subs) {
        if (!sub->open_) {
            mark = "+";
        } else {
            mark ="-";
        }
        cout << mark << " " << indent << count << ". " <<
                sub->fullName_  << " ( " <<
                sub->length_ << " )" <<endl;

        if (sub->subchapters_.size() != 0 && sub->open_) {
            print_subchapters(sub->subchapters_, count, indent);
        } count += 1;
    }
}

Chapter *Book::findChapter(const std::string &id) const
{
    for (auto& chap : chapters) {
        if (chap->id_ == id) {
            return chap;
        }
    } return nullptr;
}




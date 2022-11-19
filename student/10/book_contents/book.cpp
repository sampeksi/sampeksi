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

    if (!does_exist(new_chapter->id_)) {
        chapters.push_back(new_chapter);
    } else {
        cout << "Error: Already exists." <<endl;
    }

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
    if (does_exist(params[0])) {
    for (auto& chap : chapters) {
        if (chap->id_ == params[0]) {
            chap->open_ = false;
            close_subchapters(chap->subchapters_);
            break;
        }
    }
    } else {
        cout << "Error: Not found: " << params[0] <<endl;
    }
}

void Book::open(Params params) const
{
    if (does_exist(params[0])) {
    for (auto& chap : chapters) {
        if (chap->id_ == params[0]) {
            chap->open_ = true;
            break;
        }
    }
    } else {
        cout << "Error: Not found: " << params[0] <<endl;
    }
}

void Book::openAll(Params params) const
{
    vector<string> irrelevant = params;

    for (auto& chap : chapters) {
        chap->open_ = true;
    }
}

void Book::printParentsN(Params params) const
{
    if (does_exist(params[0])) {
        if (stoi(params[1]) < 1) {
            cout << "Error. Level can't be less than 1." <<endl;
        } else {
            Chapter* Chap = findChapter(params[0]);
            Chapter* first_Chap = Chap;
            int count = 0;
            set<string> parents = {};
            while (count < stoi(params[1])) {
                if (Chap->parentChapter_ == nullptr) {
                    break;
                }
                else {
                    Chap = Chap->parentChapter_;
                    parents.insert(Chap->id_);
                    count += 1;
                }
            }
            cout << first_Chap->id_ << " has " << count <<
                    " parent chapters:" <<endl;
            for (auto& parent : parents) {
                cout << parent <<endl;
            }
        }
    } else {
        cout << "Error: Not found: " << params[0] <<endl;
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

void Book::close_subchapters(std::vector<Chapter *> subs) const
{
    for (auto& sub : subs) {
        sub->open_ = false;
        if (sub->subchapters_.size() != 0) {
            close_subchapters(sub->subchapters_);
        }
    }
}

bool Book::does_exist(std::string id) const
{
    for (auto& chap : chapters) {
        if (chap->id_ == id) {
            return true;
        }
    }
    return false;
}

Chapter *Book::findChapter(const std::string &id) const
{
    for (auto& chap : chapters) {
        if (chap->id_ == id) {
            return chap;
        }
    } return nullptr;
}




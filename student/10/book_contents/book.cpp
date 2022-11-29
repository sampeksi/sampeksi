/* COMP.CS.110 Programming 2: Autumn 2022                                    #
 * Project3: Book contents                                                   #
 * Tiedosto: book.hh
 *
 * Moduuli toteuttaa seuraavat Luokan Book metodit:
 *  Uusien Lukujen lisääminen valittuun tietorakenteeseen.
 *  Lukujen välisten relaatioiden luominen.
 *  Kaikkien lukujen tunnusten tulostaminen.
 *  Kirjan sisällysluettelon tulostaminen.
 *  Kirjan määrättyjen lukujen sulkeminen.
 *  Kirjan määrättyjen lukujen avaaminen.
 *  Kaikkien lukujen avaaminen.
 *  Määrätyn luvun yälukujen tulostaminen halutulle tasolle asti.
 *  Määrätyn luvun alilukujen tulostaminen halutulle tasolle asti.
 *  Määrätyn luvun kanssa saman yläluvun omaavien lukujen tulostaminen.
 *  Määrätyn luvun kokonaispituuden tulostaminen.
 *  Pisimmän osaluvun tulostaminen määrätystä luvusta.
 *  Lyhimmän osaluvun tulostaminen määrätystä luvusta.
 *
 * Ohjelman kirjoittaja:
 * Nimi: Sampo Suokuisma
 * Opiskelijanro: 150422473
 * Käyttäjätunnus: ndsasu
 * Email: sampo.suokuisma@tuni.fi
*/

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
    map<string, string> ids;

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

        // Keeps calling the function until chapter has no subs.
        if (sub->subchapters_.size() != 0 && sub->open_) {
            print_subchapters(sub->subchapters_, count, indent);

        } count += 1; // Increase counter by one for each level.
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

void Book::close_subchapters(std::vector<Chapter *> subs) const
{
    for (auto& sub : subs) {
        sub->open_ = false;

        // Same idea used with function print_subchapters.
        if (sub->subchapters_.size() != 0) {
            close_subchapters(sub->subchapters_);
        }
    }
}

void Book::open(Params params) const
{
    if (does_exist(params[0])) {
    for (auto& chap : chapters) {
        if (chap->id_ == params[0]) {
            chap->open_ = true;
            for (auto& sub : chap->subchapters_) {

                // If parent chapter opens and subchapter has no subs
                // itself, it opens too.
                if (sub->subchapters_.size() == 0) {
                    sub->open_ = true;
                }
            }
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
            Chapter* first_Chap = Chap; // Saving param Chapter
                                        // for further use.
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
            if (count != 0) {
            cout << first_Chap->id_ << " has " << count <<
                    " parent chapters:" <<endl;
            for (auto& parent : parents) {
                cout << parent <<endl;
            }
            } else {
                cout << first_Chap->id_ << " has no parent chapters." <<endl;
            }
        }
    } else {
        cout << "Error: Not found: " << params[0] <<endl;
    }
}

void Book::printSubchaptersN(Params params) const
{
    if (does_exist(params[0])) {
        if (stoi(params[1]) < 1) {
            cout << "Error. Level can't be less than 1." <<endl;
        } else {
            Chapter* Chap = findChapter(params[0]);
            
            if (Chap->subchapters_.size() == 0) {
                cout << Chap->id_ << " has no subchapters." <<endl;
            } else {
                int levels = stoi(params[1]);
                int count = 0;

                vector<Chapter*> Chaps = {Chap}; // Insering param Chapter
                // inside vector to be used as parameter for hel funktion.
                vector<string> ids;

                while (count < levels) {
                    ids = subchapters(ids, Chaps);
                    count += 1;
                }
                cout << Chap->id_ << " has " << ids.size() << " subchapters:"
                        <<endl;

                // Alpabetical order.
                sort(ids.begin(), ids.end());

                for (auto& id : ids) {
                    cout << id <<endl;
                }
            }
        }
    } else {
        cout << "Error: Not found: " << params[0] <<endl;
    }
}

std::vector<string> Book::subchapters(std::vector<string> sub_ids,
                                         std::vector<Chapter *> &Chaps) const
{
    vector<Chapter*> newChaps;
    for (auto& Chap : Chaps) {
        for (auto& C : Chap->subchapters_) {
            sub_ids.push_back(C->id_);
            newChaps.push_back(C);
        }
    }
    Chaps = newChaps; // Udpating present Chapters.
    return sub_ids;
}

void Book::printSiblingChapters(Params params) const
{
    if (does_exist(params[0])) {
        Chapter* Chap = findChapter(params[0]);
        set<string> ids; {}

        if (Chap->parentChapter_ != nullptr) {
            Chapter* Parent = Chap->parentChapter_;

            for (auto& sub : Parent->subchapters_) {
                if (sub->id_ != Chap->id_) {
                    ids.insert(sub->id_);
                }
            }
            int size = ids.size();
            cout << Chap->id_ << " has " << size << " sibling chapters:"
                 <<endl;

            for (auto& id : ids) {
                cout << id <<endl;
            }
        } else {
            cout << Chap->id_ << " has no sibling chapters." <<endl;
        }

    } else {
        cout << "Error: Not found: " << params[0] <<endl;
    }
}

void Book::printTotalLength(Params params) const
{
    if (does_exist(params[0])) {
        Chapter* Chap = findChapter(params[0]);
        int length = Chap->length_;
        subchapter_length(Chap->subchapters_, length);

        cout << "Total length of " << Chap->id_ << " is "
             << length << "."<<endl;
    }
    else {
        cout << "Error: Not found: " << params[0] <<endl;
    }
}

void Book::subchapter_length(std::vector<Chapter *> subs, int &length) const
{
    for (auto& sub : subs) {
        length += sub->length_;
        if (sub->subchapters_.size() != 0) {
            subchapter_length(sub->subchapters_, length);
        }
    }
}

void Book::printLongestInHierarchy(Params params) const
{
    if (does_exist(params[0])) {

        Chapter* Chap = findChapter(params[0]);
        vector<Chapter*> Chaps = {Chap};
        vector<string> ids;

        while (Chaps.size() != 0) {
            ids = subchapters(ids, Chaps);
        }
        // Making param Chapter the longest at first
        // so it is taken into account.
        Chapter* Longest = Chap;

        for (auto& id : ids) {

            Chapter* currentChap = findChapter(id);
            if (currentChap->length_ > Longest->length_) {
                Longest = currentChap;
            }
        }
        if (Longest->id_ != Chap->id_) {
        cout << "With the length of " << Longest->length_ << ", " <<
                Longest->id_ << " is the longest chapter in "<< Chap->id_ <<
                "'s hierarchy." <<endl;
        } else {
            cout << "With the length of " << Longest->length_ << ", " <<
                   Longest->id_ << " is the longest chapter in "
                   "their hierarchy." <<endl;
        }
    } else {
        cout << "Error: Not found: " << params[0] <<endl;
    }
}

void Book::printShortestInHierarchy(Params params) const
{
    if (does_exist(params[0])) {

            Chapter* Chap = findChapter(params[0]);
            vector<Chapter*> Chaps = {Chap};
            vector<string> ids;

            while (Chaps.size() != 0) {
                ids = subchapters(ids, Chaps);
            }
            // Same here but now with shortest.
            Chapter* Shortest = Chap;

            for (auto& id : ids) {
                Chapter* currentChap = findChapter(id);
                if (currentChap->length_ < Shortest->length_) {
                    Shortest = currentChap;
                }
            }
            if (Shortest->id_ != Chap->id_) {
            cout << "With the length of " << Shortest->length_ << ", " <<
                    Shortest->id_ << " is the shortest chapter in "<<
                    Chap->id_ << "'s hierarchy." <<endl;
            } else {
                cout << "With the length of " << Shortest->length_ << ", " <<
                       Shortest->id_ << " is the shortest chapter in "
                       "their hierarchy." <<endl;
            }
        } else {
            cout << "Error: Not found: " << params[0] <<endl;
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

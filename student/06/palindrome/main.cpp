#include <iostream>
#include <string>
#ifndef RECURSIVE_FUNC
#define RECURSIVE_FUNC
#endif

using namespace std;

bool palindrome_recursive(std::string s)
{
  RECURSIVE_FUNC
  if (s.length()== 0) {
      return true;
  }
  int last_index = s.length()-1;

  if (s.at(last_index) != s.at(0)) {
      return false;
  } else {
      s.erase(last_index);
      s.erase(0, 1);
      return palindrome_recursive(s);
  }
}
#ifndef UNIT_TESTING
int main()
{
    std::cout << "Enter a word: ";
    std::string word;
    std::cin >> word;

    if(palindrome_recursive(word)){
        std::cout << word << " is a palindrome" << std::endl;
    } else {
        std::cout << word << " is not a palindrome" << std::endl;
    }
}
#endif

#include <algorithm>
#include <cctype>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <string>
#include <vector>

enum OP { ECHO, SET };

// TODO: Implement a match for different data types and operations
// TODO: ????
// TODO: ????
// TODO: Return the final string?

bool extract_word(int &pos, char buf[1024], char out[1024]) {
  int len = strlen(buf);
  int out_i = 0;
  for (; pos < len - 1; pos++) {
    if (buf[pos] == '\r')
      std::cout << "\\r";
    else if (buf[pos] == '\n')
      std::cout << "\\n";
    else
      std::cout << buf[pos];
    std::cout << "\n";
    if (buf[pos] == '\r' && buf[pos + 1] == '\n') {
      out[out_i] = '\0';
      pos += 2;
      return true;
    }
    out[out_i++] = buf[pos];
  }
  return false;
}

std::string executeCommand(std::string operation,
                           std::vector<std::string> opArgs) {

  return "????????????????";
};

const char *parser(char buf[1024]) {
  static char ans[1024];
  int pos = 1;

  switch (buf[0]) {
  case '*': {
    extract_word(pos, buf, ans);
    int nargs = std::stoi(ans);
    std::vector<std::string> arr;
    int nopArg = 0;
    std::string opString;
    std::vector<std::string> opArg;
    // NOTE: the nargs *2 is hardcoded for arrays of bulk strings (length + the
    // actual string)

    for (int i = 1; i <= nargs * 2; i++) {
      std::cout << "pos=" << pos << " first char=" << buf << "\n";
      if (buf[pos] == '\r')
        std::cout << "\\r";
      else if (buf[pos] == '\n')
        std::cout << "\\n";
      else
        std::cout << buf[pos];
      std::cout << "\n";
      extract_word(pos, buf, ans);
      if (i % 2) {
        char *snum = ans + 1;
        int num = std::stoi(snum);
      } else {
        // NOTE: if it's an operation cmd(like Echo) then set opArg to the
        // number of args the operation requires.
        // until the nopArg becomes
        // 0 every non odd argument is passed to an array which should then be
        // passed and executed by the command

        if (nopArg) {
          opArg.push_back(ans);
          nopArg--;
          if(nopArg==0)
              std::cout<<executeCommand(opString, opArg)<<'\n';
          continue;
        }
        std::string lowerString = ans;
        std::transform(lowerString.begin(), lowerString.end(),
                       lowerString.begin(), ::tolower);
        opString=lowerString;


        std::cout << "Mmmmmm " + lowerString << '\n';
      }

      std::cout << "extracted=[" << ans << "]\n";
      arr.push_back(ans);
    }
    for (auto el : arr) {
      std::cout << "-" << el << "-\n";
    }
    return "hey";
    break;
  }
  }

  return nullptr;
}

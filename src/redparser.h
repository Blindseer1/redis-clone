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
    std::cout<<"\n";
    if (buf[pos] == '\r' && buf[pos + 1] == '\n') {
      out[out_i] = '\0';
      pos += 2;
      return true;
    }
    out[out_i++] = buf[pos];
  }
  return false;
}

const char *parser(char buf[1024]) {
  static char ans[1024];
  int pos = 1;

  switch (buf[0]) {
  case '*': {
    extract_word(pos, buf, ans);
    int nargs = std::stoi(ans);
    std::vector<std::string> arr;
    for (int i = 1; i <= nargs; i++) {
      std::cout << "pos=" << pos << " first char=" << buf << "\n";
    if (buf[pos] == '\r')
      std::cout << "\\r";
    else if (buf[pos] == '\n')
      std::cout << "\\n";
    else
      std::cout << buf[pos];
    std::cout<<"\n";
      extract_word(pos, buf, ans);
      std::cout << "extracted=[" << ans << "]\n";
      arr.push_back(ans);
    }
    for (auto el : arr) {
      std::cout << "[" << el << "]\n";
    }
    return "hey";
    break;
  }
  }

  return nullptr;
}


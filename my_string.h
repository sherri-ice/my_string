#ifndef MY_STRING_H_
#define MY_STRING_H_

#include <ostream>

class String {
 public:
  String();
  explicit String(const char* str);
  String(int count, char ch);

  String(const String& rhs);
  String& operator=(const String& rhs);

  String(String&& rhs) noexcept;
  String& operator=(String&& rhs) noexcept;

  ~String();

  int length() const;
  bool empty() const;
  char* c_str() const;

  char& operator[](int index);
  const char& operator[](int index) const;

  char& front();
  char& back();
  const char& front() const;
  const char& back() const;


  void reserve(int new_capacity);
  void push_back(char ch);
  void pop_back();
  void clear();
  void insert(int index, const String& str);
  void insert(int index, const char* str, int count);
  void erase(int index, int count = 1);
  int compare(const String& rhs) const;
  int compare(const char* str) const;

  String operator+(const String& rhs) const;
  String& operator+=(const String& rhs);

  bool operator==(const String& rhs) const;
  bool operator!=(const String& rhs) const;
  bool operator<(const String& rhs) const;
  bool operator>(const String& rhs) const;
  bool operator<=(const String& rhs) const;
  bool operator>=(const String& rhs) const;

  bool operator==(const char* rhs) const;
  bool operator!=(const char* rhs) const;
  bool operator<(const char* rhs) const;
  bool operator>(const char* rhs) const;
  bool operator<=(const char* rhs) const;
  bool operator>=(const char* rhs) const;

  friend bool operator==(const char* lhs, const String& rhs);
  friend bool operator!=(const char* lhs, const String& rhs);
  friend bool operator<(const char* lhs, const String& rhs);
  friend bool operator>(const char* lhs, const String& rhs);
  friend bool operator<=(const char* lhs, const String& rhs);
  friend bool operator>=(const char* lhs, const String& rhs);

  friend void Swap(String& first, String& second);
  friend std::ostream& operator<<(std::ostream& os, String& str);

 private:
  char* string_ = new char[1];
  int size_ = 0;
  int capacity_ = 1;
};

#endif  // MY_STRING_H_


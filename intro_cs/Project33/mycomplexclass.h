#ifndef MyComplexClass_H
#define MyComplexClass_H

#include <iostream>

class MyComplexClass
{
  public:
      MyComplexClass();
      MyComplexClass(float, float);
      MyComplexClass(const MyComplexClass&);
      void SetValues(float, float);
      float GetReal() const;
      float GetIm() const;
      void Display() const;
      bool EqualTo(MyComplexClass);
      bool operator ==(MyComplexClass rhs);
      friend std::ostream& operator <<(std::ostream&, const MyComplexClass&);
      friend std::istream& operator >>(std::istream&, MyComplexClass&);

  private:
      float rePart,
            imPart;
};
#endif

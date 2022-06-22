#ifndef SQUARE_H_
#define SQUARE_H_

//#include <iostream>

enum class Square : char
{
    Empty = '.',
    PlayerA = 'X',
    PlayerB = 'O',
};

//std::ostream& operator << (std::ostream& os, const Square& value)
//{
//    return os << static_cast<char>(value);
//}

#endif // !SQUARE_H_
#include <iostream>
#include <cassert>
using namespace std;

char nibble_to_hex(uint8_t i)
{
    switch(i)
    {
    case 0b0000 :
        return '0';
        break;
    case 0b0001 :
        return '1';
        break;
    case 0b0010 :
        return '2';
        break;
    case 0b0011 :
        return '3';
        break;
    case 0b0100 :
        return '4';
        break;
    case 0b0101 :
        return '5';
        break;
    case 0b0110 :
        return '6';
        break;
    case 0b0111 :
        return '7';
        break;
    case 0b1000 :
        return '8';
        break;
    case 0b1001 :
        return '9';
        break;
    case 0b1010 :
        return 'a';
        break;
    case 0b1011 :
        return 'b';
        break;
    case 0b1100 :
        return 'c';
        break;
    case 0b1101 :
        return 'd';
        break;
    case 0b1110 :
        return 'e';
        break;
    case 0b1111 :
        return 'f';
        break;
    }
}

void print_in_hex(uint8_t byte)
{
    cout << nibble_to_hex(byte >> 4)
         << nibble_to_hex(byte & 0b00001111);
}

void test ()
{
    assert(nibble_to_hex(0x0) == '0');
    assert(nibble_to_hex(0x1) == '1');
    assert(nibble_to_hex(0xa) == 'a');
    assert(nibble_to_hex(0xb) == 'b');
    assert(nibble_to_hex(0xc) == 'c');
    assert(nibble_to_hex(0xd) == 'd');
    assert(nibble_to_hex(0xe) == 'e');
    assert(nibble_to_hex(0xf) == 'f');
}

const uint8_t* as_bytes(const void* data)
{
    return reinterpret_cast<const uint8_t*>(data);
}

void print_in_hex(const void* data, size_t size)
{
    auto bytes = as_bytes(data);
    for (size_t i = 0; i < size; i++)
    {
        print_in_hex(bytes[i]);
        if ((i + 1) % 16 == 0)
        {
            cout << '\n';
        }
        else
        {
            cout << ' ';
        }
    }
}

char bit_digit(uint8_t byte, uint8_t bit)
{
    if (byte & (0x1 << bit))
    {
        return '1';
    }
    return '0';
}

void
print_in_binary(uint8_t byte)
{
    for (uint8_t bit = 7; bit > 0; bit--)
    {
        cout << bit_digit(byte, bit);
    }
    cout << bit_digit(byte, 0);
}

void
print_in_binary(const void* data, size_t size)
{
    const uint8_t* bytes = as_bytes(data);
    for (size_t i = 0; i < size; i++)
    {
        print_in_binary(bytes[i]);

        if ((i + 1) % 4 == 0)
        {
            cout << '\n';
        }
        else
        {
            cout << ' ';
        }
    }
}

void calc(uint16_t figure1,char oper,uint16_t figure2)
{
    if ((oper!='&') and (oper!='|') and (oper!='^'))
        cout << "Oshibka vvoda";
    else
    {
        print_in_hex(&figure1, sizeof(figure1));
        cout << oper;
        print_in_hex(&figure2, sizeof(figure2));
        cout << " = ";
        uint16_t res;
        switch(oper)
        {
        case '&' :
            res = figure1 & figure2;
            break;
        case '|' :
            res = figure1 | figure2;
            break;
        case '^' :
            res = figure1 ^ figure2;
            break;
        }
        print_in_hex(&res,sizeof(res));
        cout << '\n';
        print_in_binary(&figure1, sizeof(figure1));
        cout << oper;
        print_in_binary(&figure2, sizeof(figure2));
        cout << " = ";
        uint16_t res2;
        switch(oper)
        {
        case '&' :
            res2 = figure1 & figure2;
            break;
        case '|' :
            res2 = figure1 | figure2;
            break;
        case '^' :
            res2 = figure1 ^ figure2;
            break;
        }
        print_in_binary(&res2,sizeof(res2));
    }
}

struct Student
{
    char name [17];
    int year;
    float average;
    uint8_t gender :1;
    int courses;
    Student* starosta;
};

int main()
{
    uint8_t u8 = 0x42;
    cout << "u8 bytes: ";
    print_in_hex(&u8, sizeof(u8));
    cout << '\n';

    uint16_t u16 = 0x42;
    cout << "u16 bytes: ";
    print_in_hex(&u16, sizeof(u16));
    cout << '\n';

    uint32_t u32 = 0x42;
    cout << "u32 bytes: ";
    print_in_hex(&u32, sizeof(u32));
    cout << '\n';

    cout << "15: ";
    print_in_binary(15);
    cout << '\n';

    uint32_t u = 42;
    cout << "42: ";
    print_in_binary(&u, sizeof(u));
    cout << '\n';

    calc(1025,'&',127);
    cout << '\n' << '\n';

    Student students[3]= {{"Ann",2000,4,0,1,nullptr},{"Ron",2000,5,1,1,&students[0]},{"Kate",1999,5,0,1,&students[0]}};
    cout << "Address massiva students[3]: " << &students << '\n'
         << "Size massiva students[3]: " << sizeof(students) << '\n';
    for (int i=0; i<3; i++)
    {
        cout << "Address students[" << i << "] = " << &students[i] << "  size: " << sizeof(students[i]) <<'\n';
    }
    cout << '\n';
    cout << "Name address students[" << 1 << "] = " << (void*)(&students[1].name) << " Smesh: " << offsetof(Student,name) << " size: " << sizeof(students[1].name)  << " 16: ";
    print_in_hex(&students[1].name,sizeof(students[1].name));
    cout << " 2: ";
    print_in_binary (&students[1].name,sizeof(students[1].name));
    cout << "Year address students[" << 1 << "] = " << &students[1].year << " Smesh: " << offsetof(Student,year)<< " size: " << sizeof(students[1].year) << " 16: ";
    print_in_hex(&students[1].year,sizeof(students[1].year));
    cout << " 2: ";
    print_in_binary (&students[1].year,sizeof(students[1].year));
    cout << "Average address students[" << 1 << "] = " << &students[1].average << " Smesh: " << offsetof(Student,average) << " size: " << sizeof(students[1].average) << " 16: ";
    print_in_hex(&students[1].average,sizeof(students[1].average));
    cout << " 2: ";
    print_in_binary (&students[1].average,sizeof(students[1].average));
    cout << "Courses address students[" << 1 << "] = " << &students[1].courses << " Smesh: " << offsetof(Student,average) << " size: " << sizeof(students[1].courses) << " 16: ";
    print_in_hex(&students[1].courses,sizeof(students[1].courses));
    cout << " 2: ";
    print_in_binary (&students[1].courses,sizeof(students[1].courses));
    cout << '\n';
    cout << "Massive students[" << 1 << "] in 16:" << '\n';
    print_in_hex(&students[1],sizeof(students[1]));
    return 0;
}

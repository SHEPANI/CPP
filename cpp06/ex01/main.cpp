#include "Serializer.hpp"

int main()
{
    intptr_t raw;
    Data data1;
    Data* data2;

    data1.name = "Ahmed";
    data1.age = 42;

    raw = Serializer::serialize(&data1);
    data2 = Serializer::deserialize(raw);

    if (data2 == &data1)
        std::cout << "The deserialized pointer is the same as the original pointer.\n";

    std::cout << "Original Data: name = " << data1.name << ", age = " << data1.age << "\n";
    std::cout << "Deserialized Data: name = " << data2->name << ", age = " << data2->age << "\n";   
    return 0;
}
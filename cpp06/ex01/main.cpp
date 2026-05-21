#include "Serializer.hpp"

int main()
{
    intptr_t raw;
    Data data1;
    Data data2;

    data1.name = "Ahmed";
    data1.age = 42;

    raw = Sealizer::serialize(&data1);
    data2 = *Sealizer::deserialize(raw);

    if (raw == &data1)
        std::cout << "Serialization successful: raw pointer matches original data pointer.\n";
    else
        std::cout << "Serialization failed: raw pointer does not match original data pointer.\n";

    std::cout << "Original Data: name = " << data1.name << ", age = " << data1.age << "\n";
    std::cout << "Deserialized Data: name = " << data2.name << ", age = " << data2.age << "\n";
}
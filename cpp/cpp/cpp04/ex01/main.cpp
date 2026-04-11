/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lhchiban <lhchiban@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/23 21:06:49 by lhchiban          #+#    #+#             */
/*   Updated: 2026/01/24 05:33:49 by lhchiban         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Animal.hpp"
#include "Cat.hpp"
#include "Dog.hpp"
#include "Brain.hpp"
#include <iostream>

int main()
{
    std::cout << "\n=== Test 2: Array of Animals (half Dog, half Cat) ===" << std::endl;
    {
        int arraySize = 10;
        Animal* animals[arraySize];
        
        std::cout << "\n--- Creating Dogs ---" << std::endl;
        for (int i = 0; i < arraySize / 2; i++)
        {
            animals[i] = new Dog();
        }
        
        std::cout << "\n--- Creating Cats ---" << std::endl;
        for (int i = arraySize / 2; i < arraySize; i++)
        {
            animals[i] = new Cat();
        }
        
        std::cout << "\n--- Making sounds ---" << std::endl;
        for (int i = 0; i < arraySize; i++)
        {
            std::cout << animals[i]->getType() << ": ";
            animals[i]->makeSound();
        }
        
        std::cout << "\n--- Deleting all animals ---" << std::endl;
        for (int i = 0; i < arraySize; i++)
        {
            delete animals[i];
        }
    }

    std::cout << "\n=== Test 3: Deep Copy Test for Dog ===" << std::endl;
    {
        std::cout << "\n--- Creating original Dog ---" << std::endl;
        Dog* originalDog = new Dog();
        
        std::cout << "\n--- Creating copy of Dog ---" << std::endl;
        Dog* copiedDog = new Dog(*originalDog);
        
        std::cout << "\n--- Deleting original Dog ---" << std::endl;
        delete originalDog;
        
        std::cout << "\n--- Copied Dog still exists (proving deep copy) ---" << std::endl;
        copiedDog->makeSound();
        
        std::cout << "\n--- Deleting copied Dog ---" << std::endl;
        delete copiedDog;
    }

    std::cout << "\n=== Test 4: Deep Copy Test for Cat ===" << std::endl;
    {
        std::cout << "\n--- Creating original Cat ---" << std::endl;
        Cat* originalCat = new Cat();
        
        std::cout << "\n--- Creating copy of Cat ---" << std::endl;
        Cat* copiedCat = new Cat(*originalCat);
        
        std::cout << "\n--- Deleting original Cat ---" << std::endl;
        delete originalCat;
        
        std::cout << "\n--- Copied Cat still exists (proving deep copy) ---" << std::endl;
        copiedCat->makeSound();
        
        std::cout << "\n--- Deleting copied Cat ---" << std::endl;
        delete copiedCat;
    }

    std::cout << "\n=== Test 5: Assignment Operator Deep Copy Test ===" << std::endl;
    {
        std::cout << "\n--- Creating Dog1 and Dog2 ---" << std::endl;
        Dog dog1;
        Dog dog2;
        
        std::cout << "\n--- Assigning dog1 to dog2 ---" << std::endl;
        dog2 = dog1;
        
        std::cout << "\n--- Both dogs make sound ---" << std::endl;
        dog1.makeSound();
        dog2.makeSound();
        
        std::cout << "\n--- Dogs going out of scope ---" << std::endl;
    }    
    return 0;
}
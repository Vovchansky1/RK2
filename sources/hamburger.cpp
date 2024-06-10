#include "hamburger_l.cpp"


int main()
{
    HamburgerHouse macdoria(std::make_unique<BeefHamburgerFactory>());

    std::cout << "======== Beef Based Hamburger House ========" << std::endl;
    std::cout << "* Let's make a cheese burger" << std::endl;
    macdoria.MakeCheeseBurger().Print();
    std::cout << "* Let's make a jumbo burger" << std::endl;
    macdoria.MakeJumboBurger().Print();

    macdoria.ChangeFactory(std::make_unique<PorkHamburgerFactory>());
    std::cout << std::endl;
    std::cout << "======== Pork Based Hamburger House ========" << std::endl;
    std::cout << "* Let's make a cheese burger" << std::endl;
    macdoria.MakeCheeseBurger().Print();
    std::cout << "* Let's make a jumbo burger" << std::endl;
    macdoria.MakeJumboBurger().Print();

    return 0;
}
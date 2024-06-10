#include "munition_l.cpp"
int main()
{
    MunitionStore store(std::make_unique<AncientMunitionFactory>());

    std::cout << "======== Ancient Munition Store ========" << std::endl;
    store.Print();

    std::cout << "======== Modern Munition Store ========" << std::endl;
    store.ChangeFactory(std::make_unique<ModernMunitionFactory>());
    store.Print();

    std::cout << "======== Future Munition Store ========" << std::endl;
    store.ChangeFactory(std::make_unique<FutureMunitionFactory>());
    store.Print();
}
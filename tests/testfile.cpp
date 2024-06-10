#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <stdexcept>
#include "hamburger_l.cpp"
#include "munition_l.cpp"

class M_MF : public MunitionFactory {
public:
  MOCK_METHOD(std::unique_ptr<Weapon>, MakeWeapon, (), (const, override));
  MOCK_METHOD(std::unique_ptr<Vehicle>, MakeVehicle, (), (const, override));
};

TEST (Hamburger, functions) {
    HamburgerHouse macdoria(std::make_unique<BeefHamburgerFactory>());
    testing::internal::CaptureStdout();
    macdoria.MakeCheeseBurger().Print();
    macdoria.MakeJumboBurger().Print();
    const std::string output = testing::internal::GetCapturedStdout();
    EXPECT_EQ(output, "----------\nLightBread\nLettuce\nGarlicSauce\nBeefPatty\nMozzarellaCheese\nLightBread\n----------\n----------\nLightBread\nLettuce\nGarlicSauce\nBeefPatty\nMozzarellaCheese\nLightBread\nLettuce\nGarlicSauce\nBeefPatty\nMozzarellaCheese\nLightBread\n----------\n");
}
TEST (Munition, functions) {
    MunitionStore store(std::make_unique<AncientMunitionFactory>());
    testing::internal::CaptureStdout();
    store.Print();
    store.ChangeFactory(std::make_unique<ModernMunitionFactory>());
    store.Print();
    const std::string output = testing::internal::GetCapturedStdout();
    EXPECT_EQ(output, "Weapon  : Knife\nVehicle : Horse\n\nWeapon  : Gun\nVehicle : Tank\n\n");
}

using ::testing::AtLeast;
TEST (Ham_Munition, mock) {
  M_MF t_obj1;
  EXPECT_CALL(t_obj1, MakeWeapon()).Times(AtLeast(1));
  t_obj1.MakeWeapon();
}
#include <iostream>
#include <memory>
#include <string>
#include <vector>

struct HamburgerIngredient { virtual ~HamburgerIngredient() = default; virtual std::string Name() const = 0; };

struct Bread : public HamburgerIngredient { std::string Name() const override { return "Bread"; } };
struct Patty : public HamburgerIngredient { std::string Name() const override { return "Patty"; } };
struct Cheese : public HamburgerIngredient { std::string Name() const override { return "Cheese"; } };
struct Tomato : public HamburgerIngredient { std::string Name() const override { return "Tomato"; } };
struct Lettuce : public HamburgerIngredient { std::string Name() const override { return "Lettuce"; } };
struct Sauce : public HamburgerIngredient { std::string Name() const override { return "Sauce"; } };

struct LightBread : public Bread { std::string Name() const override { return "LightBread"; } };
struct SaltyBread : public Bread { std::string Name() const override { return "SaltyBread"; } };

struct BeefPatty : public Patty { std::string Name() const override { return "BeefPatty"; } };
struct PorkPatty : public Patty { std::string Name() const override { return "PorkPatty"; } };

struct MozzarellaCheese : public Cheese { std::string Name() const override { return "MozzarellaCheese"; } };
struct CheddarCheese : public Cheese { std::string Name() const override { return "CheddarCheese"; } };

struct GarlicSauce : public Sauce { std::string Name() const override { return "GarlicSauce"; } };
struct MustardSauce : public Sauce { std::string Name() const override { return "MustardSauce"; } };

class Hamburger final
{
public:
    explicit Hamburger(std::vector<std::unique_ptr<HamburgerIngredient>>&& ingredientList)
        : ingredientList_(std::move(ingredientList))
    {}

    void Print() const
    {
        std::cout << "----------" << std::endl;
        for (auto const& ingredient : ingredientList_)
            std::cout << ingredient->Name() << std::endl;
        std::cout << "----------" << std::endl;
    }

private:
    std::vector<std::unique_ptr<HamburgerIngredient>> ingredientList_;
};

class HamburgerFactory
{
public:
    virtual ~HamburgerFactory() = default;

    virtual std::unique_ptr<Bread> MakeBread() const = 0;
    virtual std::unique_ptr<Patty> MakePatty() const = 0;
    virtual std::unique_ptr<Cheese> MakeCheese() const = 0;
    virtual std::unique_ptr<Tomato> MakeTomato() const = 0;
    virtual std::unique_ptr<Lettuce> MakeLettuce() const = 0;
    virtual std::unique_ptr<Sauce> MakeSauce() const = 0;
};

class BeefHamburgerFactory : public HamburgerFactory
{
public:
    std::unique_ptr<Bread> MakeBread() const override { return std::make_unique<LightBread>(); }
    std::unique_ptr<Patty> MakePatty() const override { return std::make_unique<BeefPatty>(); };
    std::unique_ptr<Cheese> MakeCheese() const override { return std::make_unique<MozzarellaCheese>(); }
    std::unique_ptr<Tomato> MakeTomato() const override { return std::make_unique<Tomato>(); }
    std::unique_ptr<Lettuce> MakeLettuce() const override { return std::make_unique<Lettuce>(); }
    std::unique_ptr<Sauce> MakeSauce() const override { return std::make_unique<GarlicSauce>(); }
};

class PorkHamburgerFactory : public HamburgerFactory
{
public:
    std::unique_ptr<Bread> MakeBread() const override { return std::make_unique<SaltyBread>(); }
    std::unique_ptr<Patty> MakePatty() const override { return std::make_unique<PorkPatty>(); };
    std::unique_ptr<Cheese> MakeCheese() const override { return std::make_unique<CheddarCheese>(); }
    std::unique_ptr<Tomato> MakeTomato() const override { return std::make_unique<Tomato>(); }
    std::unique_ptr<Lettuce> MakeLettuce() const override { return std::make_unique<Lettuce>(); }
    std::unique_ptr<Sauce> MakeSauce() const override { return std::make_unique<MustardSauce>(); }
};

class HamburgerHouse final
{
public:
    explicit HamburgerHouse(std::unique_ptr<HamburgerFactory>&& factory)
        : factory_(std::move(factory))
    {}

    void ChangeFactory(std::unique_ptr<HamburgerFactory>&& factory) { factory_ = std::move(factory); }

    Hamburger MakeCheeseBurger() const
    {
        std::vector<std::unique_ptr<HamburgerIngredient>> ingredientList;

        ingredientList.push_back(factory_->MakeBread());
        ingredientList.push_back(factory_->MakeLettuce());
        ingredientList.push_back(factory_->MakeSauce());
        ingredientList.push_back(factory_->MakePatty());
        ingredientList.push_back(factory_->MakeCheese());
        ingredientList.push_back(factory_->MakeBread());

        return Hamburger(std::move(ingredientList));
    }

    Hamburger MakeJumboBurger() const
    {
        std::vector<std::unique_ptr<HamburgerIngredient>> ingredientList;

        ingredientList.push_back(factory_->MakeBread());
        ingredientList.push_back(factory_->MakeLettuce());
        ingredientList.push_back(factory_->MakeSauce());
        ingredientList.push_back(factory_->MakePatty());
        ingredientList.push_back(factory_->MakeCheese());
        ingredientList.push_back(factory_->MakeBread());
        ingredientList.push_back(factory_->MakeLettuce());
        ingredientList.push_back(factory_->MakeSauce());
        ingredientList.push_back(factory_->MakePatty());
        ingredientList.push_back(factory_->MakeCheese());
        ingredientList.push_back(factory_->MakeBread());

        return Hamburger(std::move(ingredientList));
    }

private:
    std::unique_ptr<HamburgerFactory> factory_;
};


//
// Created by charl on 2024-02-23.
//

#include "gtest/gtest.h"
#include "Regle.h"
#include "SystemeExpert.h"
#include <string>

using namespace tp1;

TEST(Regle, Constructeur) {
    EXPECT_NO_THROW(Regle());
}

class RegleTest : public ::testing::Test {
public:

    RegleTest(): r1(), r2() {}

protected:

    Regle r1;
    Regle r2;
};


TEST_F(RegleTest, ConstructeurParCopie){
    std::string salut = "salut";
    r2.GetPremisses().push_back(salut);
    Regle r3(r2);
    EXPECT_EQ(r2,r3);
 }

TEST_F(RegleTest, OperateurAssignation)
{
    Regle r3;

    EXPECT_EQ(r2,r3);

    std::string salut = "salut";
    r2.GetPremisses().push_back(salut);
    r3 = r2;

    EXPECT_EQ(r2,r3);
}

TEST_F(RegleTest, OperateurEgalite)
{
    Regle r3;

    EXPECT_TRUE(r2 == r3);

    std::string salut = "salut";
    r2.GetPremisses().push_back(salut);
    r3 = r2;

    EXPECT_TRUE(r2 == r3);
}

//Test pour la classe systeme expert

TEST(SystemeExpert, Constructeur) {
    EXPECT_NO_THROW(SystemeExpert());
}

class SystemeExpertTest : public ::testing::Test {
public:

    SystemeExpertTest(): s1(), s2() {}

protected:

    SystemeExpert s1;
    SystemeExpert s2;
};
/**
TEST_F(SystemeExpertTest, ConstructeurParCopie){
    std::string salut = "salut";
    S2.GetPremisses().push_back(salut);
    Regle S3(S2);
    EXPECT_EQ(S2,S3);
}

TEST_F(SystemeExpertTest, OperateurAssignation)
{
    Regle r3;

    EXPECT_EQ(r2,r3);

    std::string salut = "salut";
    r2.GetPremisses().push_back(salut);
    r3 = r2;

    EXPECT_EQ(r2,r3);
}

TEST_F(SystemeExpertTest, OperateurEgalite)
{
    Regle r3;

    EXPECT_TRUE(r2 == r3);

    std::string salut = "salut";
    r2.GetPremisses().push_back(salut);
    r3 = r2;

    EXPECT_TRUE(r2 == r3);
}
 **/
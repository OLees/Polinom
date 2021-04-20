#include "Polinom.h"
#include <gtest.h>


TEST(TMonom, can_create_empty_monom)
{
	ASSERT_NO_THROW(Monom mon);
}

TEST(TMonom, can_create_monom)
{
	ASSERT_NO_THROW(Monom mon(324, 1));
}

TEST(TMonom, throw_when_incorrect_power)
{
	ASSERT_ANY_THROW(Monom mon(1000, 1));
}

TEST(TMonom, can_create_copy_monom)
{
	Monom mon1(345, 1);
	ASSERT_NO_THROW(Monom mon2(mon1));
}

TEST(TMonom, correct_add_two_monoms)
{
	Monom mon1(123, 2);
	Monom mon2(123, 3);
	Monom mon3(124, 4);
	ASSERT_NO_THROW(mon1 + mon2);
	ASSERT_ANY_THROW(mon1 + mon3);
	EXPECT_EQ((mon1 + mon2).power, 123);
	EXPECT_EQ((mon1 + mon2).coef, 5);
}

TEST(TMonom, can_multiply_two_monoms)
{
	Monom mon1(123, 2);
	Monom mon2(345, 1);
	ASSERT_NO_THROW(mon1 * mon2);
}

TEST(TMonom, correctly_of_multiply_monoms)
{
	Monom mon1(123, 7);
	Monom mon2(354, 2);
	EXPECT_EQ((mon1 * mon2).power, 477);
	EXPECT_EQ((mon1 * mon2).coef, 14);
}

TEST(TMonom, throws_then_incorrect_power_after_multiplication)
{
	Monom mon1(911, -2);
	Monom mon2(245, 3);
	ASSERT_ANY_THROW(mon1 * mon2);
}

TEST(TPolinom, can_create_polinom)
{
	Monom mon;
	Node<Monom>* pol = new Node<Monom>(mon, NULL);
	ASSERT_NO_THROW(Polinom pol1(pol));
}

TEST(TPolinom, can_create_copy_polinom)
{
	Monom mon;
	Node<Monom>* pol = new Node<Monom>(mon, NULL);
	Polinom pol1(pol);
	ASSERT_NO_THROW(Polinom pol2(pol1));
}

TEST(TPolinom, can_multiply_monom_with_polinom)
{
	Monom mon;
	Node<Monom>* p1 = new Node<Monom>(mon, NULL);
	Node<Monom>* p2 = new Node<Monom>(mon, NULL);
	Polinom pol(p1);
	Polinom res(p2);
	Monom mon1(123, 1), mon2(354, 7), mon3(511, 4), mon4(477, 7), mon5(634, 4);
	pol.push_front(mon2);
	pol.push_front(mon3);

	res.push_front(mon4);
	res.push_front(mon5);
	std::cout << "res = " << res << std::endl;
	std::cout << "monom = " << mon1 << std::endl;
	std::cout << "pol = " << pol << std::endl;
	//res = pol * mon1;
	//std::cout << "res = " << res << std::endl;
	EXPECT_EQ(res, pol * mon1);
}

TEST(TPolinom, can_add_two_polinoms)
{
	Monom mon;
	Node<Monom>* p = new Node<Monom>(mon, NULL);
	Polinom pol(p);
	Polinom pol2(pol);
	Polinom res(pol);
	Monom mon1(154, 7), mon2(111, 8), mon3(101, 9);
	pol.push_front(mon1);
	pol2.push_front(mon2);
	pol2.push_front(mon3);
	res.push_front(mon1);
	res.push_front(mon2);
	res.push_front(mon3);
	EXPECT_EQ(pol + pol2, res);
}

TEST(TPolinom, can_add_polinoms_with_equal_powers_of_monoms)
{
	Monom mon;
	Node<Monom>* p = new Node<Monom>(mon, NULL);
	Polinom pol(p);
	Polinom pol2(pol);
	Polinom res(pol);
	
	Monom mon1(123, 1), mon2(123, 2), mon3(123, 3), mon4(789, 7), mon5(789, -3), mon6(789, 4);
	pol.push_front(mon1);
	pol.push_front(mon4);

	pol2.push_front(mon2);
	pol2.push_front(mon5);

	res.push_front(mon3);
	res.push_front(mon6);

	std::cout << "pol = " << pol << std::endl;
	std::cout << "pol2 = " << pol2 << std::endl;
	std::cout << "res = " << res << std::endl;
	EXPECT_EQ(res, pol + pol2);
}

TEST(TPolinom, can_multiply_two_polinoms)
{
	Monom mon;
	Node<Monom>* p = new Node<Monom>(mon, NULL);
	Polinom pol(p);
	Polinom pol2(pol);
	Polinom res(pol);
	Monom mon1(211, 2), mon2(213, 3), mon3(134, 7), mon4(132, 1), mon6(345, 17), mon5(343, 2), mon7(347, 21);
	pol.push_front(mon1);
	pol.push_front(mon2);

	pol2.push_front(mon3);
	pol2.push_front(mon4);

	res.push_front(mon7);
	res.push_front(mon6);
	res.push_front(mon5);
	std::cout << "pol = " << pol << std::endl;
	std::cout << "pol2 = " << pol2 << std::endl;
	std::cout << "res = " << res << std::endl;
	EXPECT_EQ(res, pol * pol2);
}

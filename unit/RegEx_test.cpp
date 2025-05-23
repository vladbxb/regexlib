#include "RegEx.hpp"
#include "StateMapper.hpp"
#include <iostream>

int main()
{
	StateMapper m;
	// Fragment tests
	
	NFAFragment literalFragment1(RegEx::buildFragment(Symbol('a'), m));
	NFA literal1(literalFragment1);
	std::cout << "Literal fragment 1:\n";
	std::cout << literal1;

	NFAFragment literalFragment2(RegEx::buildFragment(Symbol('b'), m));
	NFA literal2(literalFragment2);
	std::cout << "Literal fragment 2:\n";
	std::cout << literal2;

	NFAFragment concatFragment(RegEx::buildFragment(Symbol::concat(), literalFragment1, literalFragment2, m));
	NFA concat(concatFragment);
	std::cout << "Literals concatenated:\n";
	std::cout << concat;

	NFAFragment unionFragment(RegEx::buildFragment(Symbol::_union(), literalFragment1, literalFragment2, m));
	NFA _union(unionFragment);
	std::cout << "Literals united:\n";
	std::cout << _union;


	NFAFragment starFragment(RegEx::buildFragment(Symbol::star(), literalFragment1, m));
	NFA star(starFragment);
	std::cout << "Literal 1 fragment starred:\n";
	std::cout << star;


	RegEx r("aa(a+b)b*", RegExNotation::Infix);
	RegEx conv = r.convertToPostfix();
	std::cout << conv.toString() << '\n';

	NFA n = r.toNFA();
	std::cout << n;
	n.test("aaab");
	n.test("aabbbbbbbbbb");
	n.test("aaabbbbbb");
	n.test("aab");

	n.test("bba");
	n.test("ababbbbb");
	n.test("aaaaaaa");
	n.test("bbbbbbbbbb");

	std::cout << "\n\n";

	DFA d = n.convertToDFA();
	std::cout << d;

	d.test("aaab");
	d.test("aabbbbbbbbbb");
	d.test("aaabbbbbb");
	d.test("aab");

	d.test("bba");
	d.test("ababbbbb");
	d.test("aaaaaaa");
	d.test("bbbbbbbbbb");

	return 0;
}

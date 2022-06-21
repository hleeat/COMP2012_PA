#include <iostream>
#include <string>
#include "smartptr.h"
#include "graph.h"
#include <crtdbg.h>
#define __ALL_TESTS
#ifndef _DEBUG
#define new new(_CLIENT_BLOCK,__FILE__,__LINE)
#endif

using namespace std;

int main(int argc, char** argv) {
    _CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
    cout << boolalpha;
    #ifdef __ALL_TESTS
    for ( int testCase = 1; testCase <= 30; ++testCase )
    #else
    int testCase;
    if ( argc > 1 )
        testCase = stoi(argv[1]);
    else {
        cout << "Select test case: ";
        cin >> testCase;
    }
    #endif
    {
        cout << "Test case " << testCase << ":\n===================================\n";
        if ( testCase == 1 ) {
            SmartPtr<int> sp {42};
            cout << "sp: " << sp << "\n";
        }
        else if ( testCase == 2 ) {
            SmartPtr<double> sp1 {3.14};
            cout << "sp1: " << sp1 << "\n\n";
            SmartPtr<double> sp2 {sp1};
            cout << "sp1: " << sp1 << "\n";
            cout << "sp2: " << sp2 << "\n";
        }
        else if ( testCase == 3 ) {
            SmartPtr<double> sp1 {3.14};
            SmartPtr<double> sp2 {0.};
            cout << "sp1: " << sp1 << "\n";
            cout << "sp2: " << sp2 << "\n\n";
            sp1 = sp2;
            cout << "sp1: " << sp1 << "\n";
            cout << "sp2: " << sp2 << "\n\n";
            sp1 = sp2 = SmartPtr<double>{};
            cout << "sp1: " << sp1 << "\n";
            cout << "sp2: " << sp2 << "\n";
        }
        else if ( testCase == 4 ) {
            SmartPtr<int> sp1;
            SmartPtr<int> sp2 {42};
            SmartPtr<int> sp3 {sp2};
            cout << "sp1: " << sp1 << "\n";
            cout << "sp2: " << sp2 << "\n";
            cout << "sp3: " << sp3 << "\n\n";
            sp1.set(43);
            sp2.set(0);
            cout << "sp1: " << sp1 << "\n";
            cout << "sp2: " << sp2 << "\n";
            cout << "sp3: " << sp3 << "\n";
        }
        else if ( testCase == 5 ) {
            SmartPtr<int> sp1 {42};
            SmartPtr<int> sp2 {sp1};
            cout << "sp1: " << sp1 << "\n";
            cout << "sp2: " << sp2 << "\n\n";
            sp1.unset();
            cout << "sp1: " << sp1 << "\n";
            cout << "sp2: " << sp2 << "\n";
        }
        else if ( testCase == 6 ) {
            SmartPtr<double> sp1;
            cout << "sp1: " << sp1 << "\n";
            cout << "sp1.is_null(): " << sp1.is_null() << "\n\n";
            SmartPtr<double> sp2 {3.14};
            cout << "sp2: " << sp2 << "\n";
            cout << "sp2.is_null(): " << sp2.is_null() << "\n";
        }
        else if ( testCase == 7 ) {
            SmartPtr<string> sp1;
            SmartPtr<string> sp2;
            cout << "sp1: " << sp1 << "\n";
            cout << "sp2: " << sp2 << "\n";
            cout << "sp1 == sp2: " << ( sp1 == sp2 ) << "\n";
            cout << "sp1 != sp2: " << ( sp1 != sp2 ) << "\n\n";
            sp1.set("Hello");
            sp2.set("Hello");
            cout << "sp1: " << sp1 << "\n";
            cout << "sp2: " << sp2 << "\n";
            cout << "sp1 == sp2: " << ( sp1 == sp2 ) << "\n";
            cout << "sp1 != sp2: " << ( sp1 != sp2 ) << "\n\n";
            sp1 = sp2;
            cout << "sp1: " << sp1 << "\n";
            cout << "sp2: " << sp2 << "\n";
            cout << "sp1 == sp2: " << ( sp1 == sp2 ) << "\n";
            cout << "sp1 != sp2: " << ( sp1 != sp2 ) << "\n\n";
            sp2.unset();
            cout << "sp1: " << sp1 << "\n";
            cout << "sp2: " << sp2 << "\n";
            cout << "sp1 == sp2: " << ( sp1 == sp2 ) << "\n";
            cout << "sp1 != sp2: " << ( sp1 != sp2 ) << "\n";
        }
        else if ( testCase == 8 ) {
            SmartPtr<int> sp1 {42};
            SmartPtr<int> sp2 {sp1};
            cout << "sp1: " << sp1 << "\n";
            cout << "sp2: " << sp2 << "\n";
            cout << "*sp1: " << *sp1 << "\n\n";
            *sp1 = 0;
            cout << "sp1: " << sp1 << "\n";
            cout << "sp2: " << sp2 << "\n";
        }
        else if ( testCase == 9 ) {
            SmartPtr<string> sp;
            cout << "sp: " << sp << "\n";
            cout << "sp.operator->(): " << sp.operator->() << "\n\n";
            sp.set("Hello World");
            cout << "sp: " << sp << "\n";
            cout << "sp->size(): " << sp->size() << "\n";
        }
        else if ( testCase == 10 ) {
            SmartPtr<string> sp1 {string("Hello")};
            SmartPtr<double> sp2 {3.14};
            cout << "sp1: " << sp1;
            cout << "\nsp2: " << sp2;
            SmartPtr<string> sp3 {sp1};
            cout << "\n\nsp3: " << sp3;
            cout << "\n";
        }
        else if ( testCase == 11 ) {
            SmartPtr<SmartPtr<double>> sp1 {SmartPtr<double>{3.14}};
            SmartPtr<SmartPtr<double>> sp2 {sp1};
            SmartPtr<double> sp3 {*sp1};
            cout << "sp1: " << sp1 << "\n";
            cout << "sp2: " << sp2 << "\n";
            cout << "sp3: " << sp3 << "\n\n";
            **sp1 = 2.72;
            cout << "sp1: " << sp1 << "\n";
            cout << "sp2: " << sp2 << "\n";
            cout << "sp3: " << sp3 << "\n\n";
            *sp1 = SmartPtr<double>{3.14};
            cout << "sp1: " << sp1 << "\n";
            cout << "sp2: " << sp2 << "\n";
            cout << "sp3: " << sp3 << "\n\n";
            sp2.set(SmartPtr<double>{0.});
            cout << "sp1: " << sp1 << "\n";
            cout << "sp2: " << sp2 << "\n";
            cout << "sp3: " << sp3 << "\n\n";
        }
        else if ( testCase == 12 ) {
            Node<int> n {42};
            cout << "n: " << n << "\n";
        }
        else if ( testCase == 13 ) {
            Node<double> n1 {3.14};
            cout << "n1: " << n1 << "\n";
            Node<double> n2 {n1};
            cout << "n2: " << n2 << "\n";
        }
        else if ( testCase == 14 ) {
            Node<string> n1 {"Hello"};
            const Node<string> n2 {"World"};
            cout << "*n1: " << *n1 << "\n";
            cout << "*n2: " << *n2 << "\n\n";
            *n1 = *n2;
            cout << "*n1: " << *n1 << "\n";
            cout << "*n2: " << *n2 << "\n";
        }
        else if ( testCase == 15 ) {
            Node<int> n {0};
            SmartPtr<Node<int>> np1 {new_node(1)};
            SmartPtr<Node<int>> np2 {new_node(2)};
            SmartPtr<Node<int>> np3 {new_node(3)};
            n.add(np1);
            n.add(np2);
            n.add(np3);
            n.remove(np2);
            cout << "n: " << n << "\n";
            cout << "np1: " << np1 << "\n";
            cout << "np2: " << np2 << "\n";
            cout << "np3: " << np3 << "\n\n";
            cout << "n.degree(): " << n.degree() << "\n";
            cout << "n.size(): " << n.size() << "\n";
        }
        else if ( testCase == 16 ) {
            Node<int> n {0};
            SmartPtr<Node<int>> np1 {new_node(1)};
            SmartPtr<Node<int>> np2 {new_node(2)};
            SmartPtr<Node<int>> np3 {new_node(3)};
            n.add(np1);
            n.add(np2);
            n.add(np3);
            n.remove(np2);
            cout << "n: " << n << "\n";
            cout << "np1: " << np1 << "\n";
            cout << "np2: " << np2 << "\n";
            cout << "np3: " << np3 << "\n\n";
            cout << "n[0]: " << n[0] << "\n";
            cout << "n[1]: " << n[1] << "\n";
            cout << "n[2]: " << n[2] << "\n";
        }
        else if ( testCase == 17 ) {
            SmartPtr<Node<int>> np1 {new_node(1)};
            SmartPtr<Node<int>> np2 {new_node(2)};
            SmartPtr<Node<int>> np3 {new_node(3)};
            {
                Node<int> n {0};
                n.add(np1);
                n.add(np2);
                n.add(np3);
                cout << "n: " << n << "\n";
                cout << "np1: " << np1 << "\n";
                cout << "np2: " << np2 << "\n";
                cout << "np3: " << np3 << "\n\n";
            }
            cout << "np1: " << np1 << "\n";
            cout << "np2: " << np2 << "\n";
            cout << "np3: " << np3 << "\n";
        }
        else if ( testCase == 18 ) {
            Node<int> n {0};
            SmartPtr<Node<int>> np1 {new_node(1)};
            SmartPtr<Node<int>> np2 {new_node(2)};
            SmartPtr<Node<int>> np3 {new_node(3)};
            n.add(np1);
            n.add(np2);
            n.add(np3);
            cout << "n: " << n << "\n";
            cout << "np1: " << np1 << "\n";
            cout << "np2: " << np2 << "\n";
            cout << "np3: " << np3 << "\n\n";
            n.remove(np3);
            cout << "n: " << n << "\n";
            cout << "np1: " << np1 << "\n";
            cout << "np2: " << np2 << "\n";
            cout << "np3: " << np3 << "\n\n";
            n.remove(np3);
            n.remove(SmartPtr<Node<int>>{});
            cout << "n: " << n << "\n";
            cout << "np1: " << np1 << "\n";
            cout << "np2: " << np2 << "\n";
            cout << "np3: " << np3 << "\n";
        }
        else if ( testCase == 19 ) {
            Node<double> n {0.};
            SmartPtr<Node<double>> np1 {new_node(3.14)};
            SmartPtr<Node<double>> np2 {new_node(2.72)};
            n.add(np1);
            cout << "n: " << n << "\n";
            cout << "np1: " << np1 << "\n";
            cout << "np2: " << np2 << "\n";
            cout << "n.exists(np1): " << n.exists(np1) << "\n";
            cout << "n.exists(np2): " << n.exists(np2) << "\n";
        }
        else if ( testCase == 20 ) {
            Node<string> n {string{"Hello"}};
            SmartPtr<Node<string>> np {new_node(string{"World"})};
            n.add(np);
            cout << "n: " << n << "\n";
            cout << "np: " << np << "\n";
            cout << "n.find(\"Hello\"): " << n.find("Hello") << "\n";
            cout << "n.find(\"World\"): " << n.find("World") << "\n";
        }
        else if ( testCase == 21 ) {
            SmartPtr<Node<double>> n {new_node(3.14)};
            cout << "n: " << n << "\n";
            cout << "*n: " << *n << "\n";
        }
        else if ( testCase == 22 ) {
            SmartPtr<Node<int>> n1 {new_node(1)};
            SmartPtr<Node<int>> n2 {new_node(2)};
            SmartPtr<Node<int>> n3 {new_node(3)};
            SmartPtr<Node<int>> n4 {new_node(4)};
            add_edge(n1, n2);
            add_edge(n2, n3);
            add_edge(n3, n4);
            add_edge(n4, n1);
            cout << "n1: " << n1 << "\n";
            cout << "n2: " << n2 << "\n";
            cout << "n3: " << n3 << "\n";
            cout << "n4: " << n4 << "\n\n";
            remove_node(n1);
            cout << "n1: " << n1 << "\n";
            cout << "n2: " << n2 << "\n";
            cout << "n3: " << n3 << "\n";
            cout << "n4: " << n4 << "\n\n";
            remove_node(n2);
            cout << "n1: " << n1 << "\n";
            cout << "n2: " << n2 << "\n";
            cout << "n3: " << n3 << "\n";
            cout << "n4: " << n4 << "\n\n";
            remove_node(n3);
            cout << "n1: " << n1 << "\n";
            cout << "n2: " << n2 << "\n";
            cout << "n3: " << n3 << "\n";
            cout << "n4: " << n4 << "\n\n";
            remove_node(n4);
            cout << "n1: " << n1 << "\n";
            cout << "n2: " << n2 << "\n";
            cout << "n3: " << n3 << "\n";
            cout << "n4: " << n4 << "\n";
        }
        else if ( testCase == 23 ) {
            SmartPtr<Node<int>> n {new_node(0)};
            for ( int i = 1; i <= 5; ++i )
                add_edge(n, new_node(i));
            for ( int i = 0; i < 5; ++i )
                for ( int j = i + 1; j < 5; ++j )
                    add_edge((*n)[i], (*n)[j]);
            cout << "n: " << n << "\n";
            for ( int i = 0; i < 5; ++i )
                cout << "(*n)[" << i << "]: " << (*n)[i] << "\n";
            for ( int i = 0; i < 4; ++i )
                remove_edge((*n)[i], (*n)[4]);
            remove_edge(n, (*n)[4]);
            remove_edge((*n)[3], (*n)[0]);
            cout << "\nn: " << n << "\n";
            for ( int i = 0; i < 4; ++i )
                cout << "(*n)[" << i << "]: " << (*n)[i] << "\n";
            for ( int i = 0; i < 4; ++i )
                remove_node((*n)[i]);
        }
        else if ( testCase == 24 ) {
            SmartPtr<Node<int>> n {new_node(0)};
            for ( int i = 1; i <= 5; ++i )
                add_edge(n, new_node(i));
            for ( int i = 0; i < 5; ++i )
                for ( int j = i + 1; j < 5; ++j )
                    add_edge((*n)[i], (*n)[j]);
            SmartPtr<Node<int>> n2 ((*n)[2]);
            cout << "n: " << n << "\n";
            for ( int i = 0; i < 5; ++i )
                cout << "(*n)[" << i << "]: " << (*n)[i] << "\n";
            remove_graph(n2);
            cout << "\nn: " << n << "\n";
            cout << "n2: " << n2 << "\n";
        }
        else if ( testCase == 25 ) {
            SmartPtr<Node<int>> n {new_node(0)};
            add_edge(n, new_node(1));
            add_edge(n, new_node(2));
            add_edge((*n)[0], new_node(3));
            add_edge((*n)[1], (*(*n)[0])[1]);
            cout << n << "\n";
            cout << (*n)[0] << "\n";
            cout << (*n)[1] << "\n";
            cout << (*(*n)[0])[1] << "\n\n";
            cout << "find(n, 0): " << find(n, 0) << "\n";
            cout << "find(n, 1): " << find(n, 1) << "\n";
            cout << "find(n, 3): " << find(n, 3) << "\n";
            cout << "find(n, 4): " << find(n, 4) << "\n";
            remove_graph(n);
        }
        else if ( testCase == 26 ) {
            SmartPtr<Node<int>> n {new_node(0)};
            SmartPtr<Node<int>> n1 {new_node(1)};
            SmartPtr<Node<int>> n2 {new_node(2)};
            add_edge(n, n1);
            add_edge(n1, n2);
            cout << "n: " << n << "\n";
            cout << "n1: " << n1 << "\n";
            cout << "n2: " << n2 << "\n\n";
            cout << "reachable(n, n1): " << reachable(n, n1) << "\n";
            cout << "reachable(n, n2): " << reachable(n, n2) << "\n\n";
            remove_edge(n1, n2);
            cout << "reachable(n, n2): " << reachable(n, n2) << "\n";
            remove_graph(n);
        }
        else if ( testCase == 27 ) {
            Node<int> n {42};
            Node<int> n1 {1};
            Node<int> n2 {2};
            Node<int> n3 {3};
            Node<int> n4 {4};
            cout << "n: " << n;
            n.add(n1);
            cout << "\n\nn: " << n;
            n.add(n2);
            n.add(n3);
            n.add(n4);
            cout << "\n\nn: " << n;
            cout << "\n";
        }
        else if (testCase == 28) {
            SmartPtr<Node<char>> n0 {new_node('a')};
            SmartPtr<Node<char>> n1 {new_node('b')};
            SmartPtr<Node<char>> n2 {new_node('c')};
            SmartPtr<Node<char>> n3 {new_node('d')};
            SmartPtr<Node<char>> n4 {new_node('e')};
            SmartPtr<Node<char>> n5 {new_node('f')};
            SmartPtr<Node<char>> n6 {new_node('g')};
            SmartPtr<Node<char>> n7 {new_node('h')};
            SmartPtr<Node<char>> n8 {new_node('i')};
            SmartPtr<Node<char>> n9 {new_node('j')};
            SmartPtr<Node<char>> n10 {new_node('k')};
            SmartPtr<Node<char>> n11 {new_node('l')};
            SmartPtr<Node<char>> n12 {new_node('m')};
            SmartPtr<Node<char>> n13 {new_node('n')};
            SmartPtr<Node<char>> n14 {new_node('o')};
            SmartPtr<Node<char>> n15 {new_node('p')};
            SmartPtr<Node<char>> n16 {new_node('q')};
            SmartPtr<Node<char>> n17 {new_node('r')};
            SmartPtr<Node<char>> n18 {new_node('s')};
            SmartPtr<Node<char>> n19 {new_node('t')};
            SmartPtr<Node<char>> n20 {new_node('u')};
            SmartPtr<Node<char>> n21 {new_node('v')};
            SmartPtr<Node<char>> n22 {new_node('w')};
            SmartPtr<Node<char>> n23 {new_node('x')};
            SmartPtr<Node<char>> n24 {new_node('y')};
            SmartPtr<Node<char>> n25 {new_node('z')};
            add_edge(n0, n1);
            add_edge(n1, n7);
            add_edge(n1, n2);
            add_edge(n7, n3);
            add_edge(n2, n14);
            add_edge(n2, n4);
            add_edge(n3, n6);
            add_edge(n4, n5);
            add_edge(n14, n13);
            add_edge(n6, n15);
            add_edge(n6, n11);
            add_edge(n15, n10);
            add_edge(n5, n8);
            add_edge(n13, n9);
            add_edge(n9, n11);
            add_edge(n9, n12);
            add_edge(n10, n11);
            add_edge(n8, n11);
            add_edge(n12, n11);
            add_edge(n12, n16);
            add_edge(n11, n17);
            add_edge(n11, n18);
            add_edge(n11, n19);
            add_edge(n11, n16);
            add_edge(n17, n18);
            // Testing adding same edge two times
            add_edge(n17, n18);
            add_edge(n18, n19);
            add_edge(n16, n19);
            add_edge(n19, n20);
            add_edge(n20, n21); add_edge(n21, n22); add_edge(n22, n23); add_edge(n23, n24); add_edge(n24, n25);

            cout << "find(n, 'z'): " << find(n0, 'z') << "\n";
            remove_graph(n11);
            remove_edge(n8,n5);
            cout << "reachable(n0, n8): " << reachable(n0, n8) << "\n";
        }
        else if (testCase == 29) {
            SmartPtr<Node<char>> n0 {new_node('a')};
            SmartPtr<Node<char>> n1 {new_node('b')};
            SmartPtr<Node<char>> n2 {new_node('c')};
            SmartPtr<Node<char>> n3 {new_node('d')};
            SmartPtr<Node<char>> n4 {new_node('e')};
            SmartPtr<Node<char>> n5 {new_node('f')};
            SmartPtr<Node<char>> n6 {new_node('g')};
            SmartPtr<Node<char>> n7 {new_node('h')};
            SmartPtr<Node<char>> n8 {new_node('i')};
            SmartPtr<Node<char>> n9 {new_node('j')};
            SmartPtr<Node<char>> n10 {new_node('a')};
            SmartPtr<Node<char>> n11 {new_node('a')};
            SmartPtr<Node<char>> n12 {new_node('a')};
            SmartPtr<Node<char>> n13 {new_node('a')};
            SmartPtr<Node<char>> n14 {new_node('a')};
            SmartPtr<Node<char>> n15 {new_node('a')};
            SmartPtr<Node<char>> n16 {new_node('q')};
            SmartPtr<Node<char>> n17 {new_node('r')};
            SmartPtr<Node<char>> n18 {new_node('s')};
            SmartPtr<Node<char>> n19 {new_node('t')};
            SmartPtr<Node<char>> n20 {new_node('u')};
            SmartPtr<Node<char>> n21 {new_node('v')};
            SmartPtr<Node<char>> n22 {new_node('a')};
            SmartPtr<Node<char>> n23 {new_node('a')};
            SmartPtr<Node<char>> n24 {new_node('a')};
            SmartPtr<Node<char>> n25 {new_node('z')};
            /*cout << "n0:\t" << n0.ptr << endl;
            cout << "n1:\t" << n1.ptr << endl;
            cout << "n2:\t" << n2.ptr << endl;
            cout << "n3:\t" << n3.ptr << endl;
            cout << "n4:\t" << n4.ptr << endl;
            cout << "n5:\t" << n5.ptr << endl;
            cout << "n6:\t" << n6.ptr << endl;
            cout << "n7:\t" << n7.ptr << endl;
            cout << "n8:\t" << n8.ptr << endl;
            cout << "n9:\t" << n9.ptr << endl;
            cout << "n10:\t" << n10.ptr << endl;
            cout << "n11:\t" << n11.ptr << endl;
            cout << "n12:\t" << n12.ptr << endl;
            cout << "n13:\t" << n13.ptr << endl;
            cout << "n14:\t" << n14.ptr << endl;
            cout << "n15:\t" << n15.ptr << endl;
            cout << "n16:\t" << n16.ptr << endl;
            cout << "n17:\t" << n17.ptr << endl;
            cout << "n18:\t" << n18.ptr << endl;
            cout << "n19:\t" << n19.ptr << endl;
            cout << "n20:\t" << n20.ptr << endl;
            cout << "n21:\t" << n21.ptr << endl;
            cout << "n22:\t" << n22.ptr << endl;
            cout << "n23:\t" << n23.ptr << endl;
            cout << "n24:\t" << n24.ptr << endl;
            cout << "n25:\t" << n25.ptr << endl;*/
			add_edge(n0, n1);
			add_edge(n1, n7);
			add_edge(n1, n2);
			add_edge(n7, n3);
			add_edge(n2, n14);
			add_edge(n2, n4);
			add_edge(n3, n6);
			add_edge(n4, n5);
			add_edge(n14, n13);
			add_edge(n6, n15);
			add_edge(n6, n11);
			add_edge(n15, n10);
			add_edge(n5, n8);
			add_edge(n13, n9);
			add_edge(n9, n11);
			add_edge(n9, n12);
			add_edge(n10, n11);
			add_edge(n8, n11);
			add_edge(n12, n11);
			add_edge(n12, n16);
			add_edge(n11, n17);
			add_edge(n11, n18);
			add_edge(n11, n19);
			add_edge(n11, n16);
			add_edge(n17, n18);
			// Testing adding same edge two times
			add_edge(n17, n18);
			add_edge(n18, n19);
			add_edge(n16, n19);
			add_edge(n19, n20);
			add_edge(n20, n21); add_edge(n21, n22); add_edge(n22, n23); add_edge(n23, n24); add_edge(n24, n25);
            
            cout << "find(n, 'z'): " << find(n0, 'z') << "\n";
            remove_graph(n11);
            remove_edge(n8,n5);
            cout << "reachable(n0, n8): " << reachable(n0, n8) << "\n";
        }
        else if (testCase == 30) {
            SmartPtr<Node<char>> n0 {new_node('a')};
            SmartPtr<Node<char>> n1 {new_node('b')};
            SmartPtr<Node<char>> n2 {new_node('c')};
            SmartPtr<Node<char>> n3 {new_node('d')};
            SmartPtr<Node<char>> n4 {new_node('e')};
            SmartPtr<Node<char>> n5 {new_node('f')};
            SmartPtr<Node<char>> n6 {new_node('g')};
            SmartPtr<Node<char>> n7 {new_node('h')};
            SmartPtr<Node<char>> n8 {new_node('i')};
            SmartPtr<Node<char>> n9 {new_node('j')};
            SmartPtr<Node<char>> n10 {new_node('k')};
            SmartPtr<Node<char>> n11 {new_node('l')};
            SmartPtr<Node<char>> n12 {new_node('m')};
            SmartPtr<Node<char>> n13 {new_node('n')};
            SmartPtr<Node<char>> n14 {new_node('o')};
            SmartPtr<Node<char>> n15 {new_node('p')};
            SmartPtr<Node<char>> n16 {new_node('q')};
            SmartPtr<Node<char>> n17 {new_node('r')};
            SmartPtr<Node<char>> n18 {new_node('s')};
            SmartPtr<Node<char>> n19 {new_node('t')};
            SmartPtr<Node<char>> n20 {new_node('u')};
            SmartPtr<Node<char>> n21 {new_node('v')};
            SmartPtr<Node<char>> n22 {new_node('w')};
            SmartPtr<Node<char>> n23 {new_node('x')};
            SmartPtr<Node<char>> n24 {new_node('y')};
            SmartPtr<Node<char>> n25 {new_node('z')};
            add_edge(n0, n1);
            add_edge(n1, n7);
            add_edge(n1, n2);
            add_edge(n7, n3);
            add_edge(n2, n14);
            add_edge(n2, n4);
            add_edge(n3, n6);
            add_edge(n4, n5);
            add_edge(n14, n13);
            add_edge(n6, n15);
            add_edge(n6, n11);
            add_edge(n15, n10);
            add_edge(n5, n8);
            add_edge(n13, n9);
            add_edge(n9, n11);
            add_edge(n9, n12);
            add_edge(n10, n11);
            add_edge(n8, n11);
            add_edge(n12, n11);
            add_edge(n12, n16);
            add_edge(n11, n17);
            add_edge(n11, n18);
            add_edge(n11, n19);
            add_edge(n11, n16);
            add_edge(n17, n18);
            add_edge(n18, n19);
            add_edge(n16, n19);
            add_edge(n19, n20);
            add_edge(n20, n21);
            add_edge(n21, n22);
            add_edge(n22, n23);
            add_edge(n23, n24);
            add_edge(n24, n25);
            remove_graph(n25);
            cout << "n0:\t" << n0 << endl;
            cout << "n1:\t" << n1 << endl;
            cout << "n2:\t" << n2 << endl;
            cout << "n3:\t" << n3 << endl;
            cout << "n4:\t" << n4 << endl;
            cout << "n5:\t" << n5 << endl;
            cout << "n6:\t" << n6 << endl;
            cout << "n7:\t" << n7 << endl;
            cout << "n8:\t" << n8 << endl;
            cout << "n9:\t" << n9 << endl;
            cout << "n10:\t" << n10 << endl;
            cout << "n11:\t" << n11 << endl;
            cout << "n12:\t" << n12 << endl;
            cout << "n13:\t" << n13 << endl;
            cout << "n14:\t" << n14 << endl;
            cout << "n15:\t" << n15 << endl;
            cout << "n16:\t" << n16 << endl;
            cout << "n17:\t" << n17 << endl;
            cout << "n18:\t" << n18 << endl;
            cout << "n19:\t" << n19 << endl;
            cout << "n20:\t" << n20 << endl;
            cout << "n21:\t" << n21 << endl;
            cout << "n22:\t" << n22 << endl;
            cout << "n23:\t" << n23 << endl;
            cout << "n24:\t" << n24 << endl;
            cout << "n25:\t" << n25 << endl;
            cout << endl << endl;
        }
        else if (testCase == 31) {
            cout << "WARNNING! This testCase 31 will exploit the hardware a bit!\n";
            cout << "Therefore this process will take time to be done.\n";
            cout << "Although it seems like this testCase uses the CPU too much, but actually it doesn't :\n";
            cout << "If your computer get something wrong after running this program,\n";
            cout << "it must be a proper time to buy a new laptop!\n";
            cout << "Anyway, would you like to Run this testCase 31? (y/n): ";
            char input;
            cin >> input;
            if (input != 'y')
                break;
            for (int i = 0; i < 64; ++i)
                cout << endl;
            cout << "=================================================================================================================================\n\n\n";
            cout << ":::       :::  ::::::::  :::::::::  :::    ::: ::::::::::: ::::    :::  ::::::::            ::::    :::  ::::::::  :::       ::: \n";
            cout << ":+:       :+: :+:    :+: :+:    :+: :+:   :+:      :+:     :+:+:   :+: :+:    :+:           :+:+:   :+: :+:    :+: :+:       :+: \n";
            cout << "+:+       +:+ +:+    +:+ +:+    +:+ +:+  +:+       +:+     :+:+:+  +:+ +:+                  :+:+:+  +:+ +:+    +:+ +:+       +:+ \n";
            cout << "+#+  +:+  +#+ +#+    +:+ +#++:++#:  +#++:++        +#+     +#+ +:+ +#+ :#:                  +#+ +:+ +#+ +#+    +:+ +#+  +:+  +#+\n";
            cout << "+#+ +#+#+ +#+ +#+    +#+ +#+    +#+ +#+  +#+       +#+     +#+  +#+#+# +#+   +#+#           +#+  +#+#+# +#+    +#+ +#+ +#+#+ +#+ \n";
            cout << " #+#+# #+#+#  #+#    #+# #+#    #+# #+#   #+#      #+#     #+#   #+#+# #+#    #+#           #+#   #+#+# #+#    #+#  #+#+# #+#+# \n";
            cout << "  ###   ###    ########  ###    ### ###    ### ########### ###    ####  ######## ########## ###    ####  ########    ###   ###\n\n\n";
            cout << "================================================================================================================================\n\n";



 

 


            Node<int> n {2000303};
            for (int i = 0; i < 165000; ++i) {
                SmartPtr<Node<int>> temp {i};
                n.add(temp);
                if ((i%1000) == 0)
                    cout << '#';
            }
            for (int i = 0; i < 64; ++i)
                cout << endl;
            cout << n.size() << endl;
            if ((n.size() == 165000) && (**n[12389] == 12389)) {
                cout << "================================================================================\n\n\n";
                cout << " ::::::::  :::    :::  ::::::::   ::::::::  :::::::::: ::::::::   ::::::::  ::: \n";
                cout << ":+:    :+: :+:    :+: :+:    :+: :+:    :+: :+:       :+:    :+: :+:    :+: :+: \n";
                cout << "+:+        +:+    +:+ +:+        +:+        +:+       +:+        +:+        +:+ \n";
                cout << "+#++:++#++ +#+    +:+ +#+        +#+        +#++:++#  +#++:++#++ +#++:++#++ +#+ \n";
                cout << "       +#+ +#+    +#+ +#+        +#+        +#+              +#+        +#+ +#+ \n";
                cout << "#+#    #+# #+#    #+# #+#    #+# #+#    #+# #+#       #+#    #+# #+#    #+#  \n";
                cout << " ########   ########   ########   ########  ########## ########   ########  ### \n\n\n";
                cout << "================================================================================\n\n\n\n\n\n";
            }
            else {
                cout << "==============================================================================\n\n\n";
                cout << "::::::::::   :::     ::::::::::: :::        :::::::::: :::::::::              \n";
                cout << "::::::::::   :::     ::::::::::: :::        :::::::::: :::::::::              \n";
                cout << ":+:        :+: :+:       :+:     :+:        :+:        :+:    :+:             \n";
                cout << ":#::+::# +#++:++#++:     +#+     +#+        +#++:++#   +#+    +:+             \n";
                cout << "+#+      +#+     +#+     +#+     +#+        +#+        +#+    +#+             \n";
                cout << "#+#      #+#     #+#     #+#     #+#        #+#        #+#    #+# #+# #+# #+# \n";
                cout << "###      ###     ### ########### ########## ########## #########  ### ### ### \n\n\n";
                cout << "==============================================================================\n\n\n\n\n\n";
            }











   

        }
        
        cout << "\n";
    }
    return 0;
}

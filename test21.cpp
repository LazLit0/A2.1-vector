// Testtreiber für Aufgabe 2.1: my::vector
// Autor: Hartmut Schirmacher

#include <iostream>
#include <cassert>
#include "my_vector.h"
#include "payload.h"
#include "trackmymoves.h"


void test_21()
{
    using my::vector;
    using std::cout;
    using std::endl;

    {
        cout << "construction/destruction, size() ... ";
        vector<Payload> v0;
        v0.reserve(200);
        assert(v0.capacity() == 200);
        assert(v0.size() == 0);
        assert(Payload::count() == 0);

       {
            // are the elements created?
            vector<Payload> v1(3, Payload(-1,-1,-1));
            assert(v1.size() == 3);
            assert(Payload::count() == v1.size());
        }

        // are the elements destroyed?
        assert(Payload::count() == 0);
        cout << " done." << endl;
    }

 
    {
        cout << "push_back(), pop_back(), size(), empty() ... ";
        {
            vector<Payload> v;
            assert(v.size() == 0);
            assert(v.empty());

            v.push_back(Payload(0,0,0));
            v.push_back(Payload(1,1,1));
            v.push_back(Payload(2,2,2));
            assert(v.size() == 3);
            assert(!v.empty());
            std::cout << "PAyload: " << Payload::count() << std::endl;
            assert(Payload::count() == 3);


            assert(v.pop_back() == Payload(2,2,2));
            assert(v.size() == 2);
            assert(Payload::count() == 2);

            assert(v.pop_back() == Payload(1,1,1));
            assert(v.size() == 1);
            assert(Payload::count() == 1);

            assert(v.pop_back() == Payload(0,0,0));
            assert(v.size() == 0);
            assert(v.empty());
            assert(Payload::count() == 0);

        }
        assert(Payload::count() == 0);
        cout << " done." << endl;
    }


    {
        cout << "operator[] ... ";
        {
            vector<Payload> v;
            v.push_back(Payload(1,2,3));
            v.push_back(Payload(7,8,9));
            assert(v.size() == 2);

            // check reading
            assert(v[0] == Payload(1,2,3));
            assert(v[1] == Payload(7,8,9));

            // check writing
            v[1] = Payload(-1,-1,-1);
            assert(v[1] == Payload(-1,-1,-1));
        }
        cout << " done." << endl;
    }

    {
        cout << "at() ... ";
        {
            vector<Payload> v;
            v.push_back(Payload(1,2,3));
            v.push_back(Payload(7,8,9));
            assert(v.size() == 2);

            // check reading
            assert(v.at(0) == Payload(1,2,3));
            assert(v.at(1) == Payload(7,8,9));

            // check writing
            v.at(1) = Payload(-1,-1,-1);
            assert(v.at(1) == Payload(-1,-1,-1));

            // check exception
            try {
                v.at(2) = Payload(0,0,0);
                assert(!"should have thrown exception");
            } catch(std::out_of_range ex) {
                cout << "exception: " << ex.what();
            }
        }
        cout << " done." << endl;
    }

    {
        cout << "constness... ";
        {
            vector<Payload> v;
            v.push_back(Payload(1,2,3));
            v.push_back(Payload(7,8,9));

            // const ref (read-only ref)
            const vector<Payload> &vconst = v;

            // all this must compile without problems, else you are missing const :-)
            assert(!vconst.empty());
            assert(vconst.size() == 2);
            assert(vconst[0] == Payload(1,2,3));
            assert(vconst.at(0) == Payload(1,2,3));
        }
        cout << " done." << endl;
    }

    {
        // kompiliert jetzt
        vector<Payload> v1;
        vector<Payload> v2 = v2;
    }
#if 0
#endif

} // test21()

void test_22()
{
    using my::vector;
    using std::cout;
    using std::endl;

    cout << "-------------------+ test 22 =---------------------------"<< endl;
     {
        cout << "reserve/clearing/shrink to fit... ";
        {
            vector<Payload> v;
            assert(v.capacity() == 0);
            v.reserve(3);
            v.push_back(Payload(1,2,3));
            v.push_back(Payload(7,8,9));

            assert(v.size() == 2);
            assert(v.capacity() == 3);
            assert(Payload::count() == 2);
            assert(!v.empty());

            v.clear();

            assert(v.empty());
            assert(v.capacity() == 3);
            assert(v.size() == 0);
            assert(Payload::count() == 0);

            v.push_back(Payload(1,2,3));
            v.push_back(Payload(7,8,9));
            v.push_back(Payload(1,2,3));
            assert(v.capacity() == 3);

            v.push_back(Payload(7,8,9));
            assert(v.capacity() == 7);
            v.shrink_to_fit();
            assert(v.size() == 4);
            assert(v.capacity() == 4);

            v.clear();

            assert(v.capacity() == 4);
            assert(v.size() == 0);

            // check exception
            try {
                v.pop_back();
                assert(!"should have thrown exception");
            } catch(std::out_of_range ex) {
                cout << "exception: " << ex.what();
            }
        }
        cout << " done." << endl;
    }

    {
        cout << "copy-ctor... ";
        {
            vector<Payload> v;
            v.reserve(20);
            v.push_back(Payload(1,2,3));
            v.push_back(Payload(4,5,6));
            v.push_back(Payload(7,8,9));

            cout << "Das ist der neue Payload: "<< Payload::count() << endl;
            assert(Payload::count() == 3);

            auto vCopy (v);
            // since it is a copy, Payload::count must have been doubled
            assert(Payload::count() == 6);


            assert(vCopy.size() == v.size());
            assert(vCopy.capacity() == v.capacity());
            for(int i = 0; i < v.size(); i++){
                assert(v[i] == vCopy[i]);
            }


            // since its a copy, a change in that copy should not affect the original
            vCopy[1] = Payload(99,99,99);
            vCopy.shrink_to_fit();

            assert(vCopy[1].x != v[1].x);
            assert(vCopy[1] != v[1]);
            assert(vCopy.capacity() != v.capacity());


        }
        cout << " done." << endl;
    }

     {
        cout << "clear()  ... ";
        vector<Payload> v;
        v.push_back(Payload(0,0,0));
        v.push_back(Payload(1,1,1));
        v.push_back(Payload(2,2,2));
        v.clear();
        assert(v.size() == 0);
        assert(Payload::count() == 0);
        cout << "capacity: " << v.capacity() << endl;
        assert(v.capacity() == 3);
        cout << " done." << endl;
    }

    {
        cout << "reserve(), shrink_to_fit()  ... ";
        {
            vector<Payload> v;
            v.push_back(Payload(0,0,0));
            v.reserve(100);
            assert(v.at(0) == Payload(0,0,0));
            assert(v.capacity() == 100);
            // cout << "HIER BI NICH" << endl;
            assert(Payload::count() == 1);

            try {
                v.reserve(-100);
                assert(!"should have thrown exception");
            } catch(std::out_of_range ex) {
                cout << "exception: " << ex.what();
            }
        }
        {
            vector<Payload> v;
            v.reserve(100);
            v.push_back(Payload(0,0,0));
            v.push_back(Payload(1,1,1));
            v.push_back(Payload(2,2,2));
            assert(v.capacity() == 100);
            v.shrink_to_fit();
            assert(v.capacity() == 3);
        }
        cout << " done." << endl;
    }


    #if 0
#endif
}
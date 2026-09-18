#include <iostream>
#include <assert.h>
using namespace std;

#include "TimeCode.h"


void TestComponentsToSeconds(){
	cout << "Testing ComponentsToSeconds" << endl;
	
	// Random but "safe" inputs
	long long unsigned int t = TimeCode::ComponentsToSeconds(2, 71, 234719572143);
	//assert(t == 11862);
	cout << t << endl;
	// More tests go here!
	assert(TimeCode::ComponentsToSeconds(0, 0, 0) == 0);
	assert(TimeCode::ComponentsToSeconds(1, 0, 0) == 3600);
	assert(TimeCode::ComponentsToSeconds(0, 1, 0) == 60);
	assert(TimeCode::ComponentsToSeconds(0, 0, 1) == 1);
	assert(TimeCode::ComponentsToSeconds(1, 30, 45) == 5445);
	cout << "PASSED!" << endl << endl;
}


void TestDefaultConstructor(){
	cout << "Testing Default Constructor" << endl;
	TimeCode tc;
	
	//cout << "Testing ToString()" << endl;
	//cout << "tc: " << tc.ToString() << endl;
	assert(tc.ToString() == "0:0:0");
	
	cout << "PASSED!" << endl << endl;
}


void TestComponentConstructor(){
	cout << "Testing Component Constructor" << endl;
	TimeCode tc = TimeCode(0, 0, 0);
	//cout << "Testing ToString()" << endl;
	//cout << "tc: " << tc.ToString() << endl;
	assert(tc.ToString() == "0:0:0");
	
	// more tests go here!
	
	// Roll-over inputs
	TimeCode tc3 = TimeCode(3, 71, 3801);
	//cout << "tc3: " << tc3.ToString() << endl;
	assert(tc3.ToString() == "5:14:21");
	
	// More tests go here!
	TimeCode tc4 = TimeCode(1, 30, 45);
	assert(tc4.ToString() == "1:30:45");

	TimeCode tc5 = TimeCode(0, 0, 60);
	assert(tc5.ToString() == "0:1:0");

	TimeCode tc6 = TimeCode(0, 60, 0);
	assert(tc6.ToString() == "1:0:0");
	
	cout << "PASSED!" << endl << endl;
}


void TestGetComponents(){
	cout << "Testing GetComponents" << endl;
	
	unsigned int h;
	unsigned int m;
	unsigned int s;
	
	// Regular values
	TimeCode tc = TimeCode(5, 2, 18);
	tc.GetComponents(h, m, s);
	assert(h == 5 && m == 2 && s == 18);
	
	// More tests go here!
	// Zero
	TimeCode tc2 = TimeCode(0, 0, 0);
	tc2.GetComponents(h, m, s);
	assert(h == 0 && m == 0 && s == 0);

	// Exactly one hour
	TimeCode tc3 = TimeCode(1, 0, 0);
	tc3.GetComponents(h, m, s);
	assert(h == 1 && m == 0 && s == 0);

	// Exactly one minute
	TimeCode tc4 = TimeCode(0, 1, 0);
	tc4.GetComponents(h, m, s);
	assert(h == 0 && m == 1 && s == 0);

	// Exactly one second
	TimeCode tc5 = TimeCode(0, 0, 1);
	tc5.GetComponents(h, m, s);
	assert(h == 0 && m == 0 && s == 1);

	// Rollover
	TimeCode tc6 = TimeCode(3, 71, 3801);
	tc6.GetComponents(h, m, s);
	assert(h == 5 && m == 14 && s == 21);
	cout << "PASSED!" << endl << endl;
}


void TestSubtract(){
	cout << "Testing Subtract" << endl;
	TimeCode tc1 = TimeCode(1, 0, 0);
	TimeCode tc2 = TimeCode(0, 50, 0);
	TimeCode tc3 = tc1 - tc2;
	assert(tc3.ToString() == "0:10:0");
	
	
	TimeCode tc4 = TimeCode(1, 15, 45);
	try{
		TimeCode tc5 = tc1 - tc4;
		cout << "tc5: " << tc5.ToString() << endl;
		assert(false);
	}
	catch(const invalid_argument& e){
		// just leave this empty
		// and keep doing more tests
	}

	// more tests
	TimeCode tc6 = TimeCode(1, 0, 0);
	TimeCode tc7 = TimeCode(1, 0, 0);
	TimeCode tc8 = tc6 - tc7;

	assert(tc8.ToString() == "0:0:0");

	// Subtract seconds
	TimeCode tc9 = TimeCode(1, 0, 30);
	TimeCode tc10 = TimeCode(0, 0, 15);
	TimeCode tc11 = tc9 - tc10;

	assert(tc11.ToString() == "1:0:15");
	
	cout << "PASSED!" << endl << endl;
}


void TestSetMinutes()
{
	cout << "Testing SetMinutes" << endl;

	TimeCode tc = TimeCode(8, 5, 9);
	tc.SetMinutes(15); // test valid change
	assert(tc.ToString() == "8:15:9");

	try
	{
		tc.SetMinutes(80);  // test invalid change
		assert(false);
	}
	catch (const invalid_argument &e)
	{
		// cout << e.what() << endl;
	}

	assert(tc.ToString() == "8:15:9");

	cout << "PASSED!" << endl << endl;
}


void TestMultiplication(){
    cout << "Testing operator*" << endl;

    TimeCode t(2, 30, 0);
	TimeCode result;
    try {
        result = t * -2;
        assert(false);
    }
    catch (const invalid_argument& e) {
        cout << e.what() << endl;
    }
}

	
int main(){
	
	TestComponentsToSeconds();
	TestDefaultConstructor();
	TestComponentConstructor();
	TestGetComponents();
	TestMultiplication();
	TestSubtract();
	// Many othere test functions...
	
	cout << "PASSED ALL TESTS!!!" << endl;
	return 0;
}

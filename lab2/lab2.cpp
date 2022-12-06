#include <iostream>
#include <fstream>
#include <vector>
using namespace std;

class PrimeFactorization {
private:
	int num1, num2;
	vector<int> num1_factor, num2_factor;

public:
	PrimeFactorization() {
		this->num1 = num1;
		this->num2 = num2;
		//TO_DO: initial constructor
	}
	PrimeFactorization(int _a, int _b) {
		num1 = _a;
		num2 = _b;
		//TO_DO: _a means the first integer and _b means the second integer
	}
	void Get_Prime_Factorization() {
		int n = 2,ans1=num1,ans2=num2;
		while (ans1!=1) {
			for (int i = 2; i < sqrt(n) && n!=2 ; i++) {
				if (n % 2 == 0) {
					n++;
					break;
				}
			}
			if (ans1 % n != 0) n++;
			if (ans1 % n == 0) {
				num1_factor.push_back(n);
				ans1 = ans1 / n;
			}
			
		}
		n = 2;
		while (ans2 != 1) {
			for (int i = 2; i < sqrt(n) && n != 2; i++) {
				if (n % 2 == 0) {
					n++;
					break;
				}
			}
			if (ans2 % n != 0) n++;
			if (ans2 % n == 0) {
				num2_factor.push_back(n);
				ans2 = ans2 / n;
			}

		}
		
		//TO_DO: Prime factorization num1 and num2, push result to the num1_factor and num2_factor.
	}

	void Print_Prime_Factorization() {
		cout << "num1_prime_factor:";
		for (int i=0; i<num1_factor.size(); i++) cout << num1_factor[i]<<" ";
		cout << endl;
		cout << "num2_prime_factor:";
		for (int i = 0; i < num2_factor.size(); i++) cout << num2_factor[i] << " ";
		cout << endl;
		//TO_DO: Print num1_factor and num2_factor.
	}

	void Print_GCD() {
		cout << "GCD:";
		int i = 0, j = 0,gcd=1;
		while (i < num1_factor.size() && j < num2_factor.size()) {
			if (num1_factor[i] > num2_factor[j]) {
				j++;
			}
			else if (num1_factor[i] < num2_factor[j]) {
				i++;
			}
			else if (num1_factor[i] == num2_factor[j]) {
				gcd = num1_factor[i] * gcd;
				i++;
				j++;
			}
			
		}
		cout << gcd << endl;
		//TO_DO: Use num1_factor and num2_factor to find GCD and print the result.
	}

};

int main() {
	int n;
	cin >> n;

	for (int i = 0; i < n; i++) {
		int a, b;
		cin >> a >> b;

		cout << "num1 = " << a << endl;
		cout << "num2 = " << b << endl;

		PrimeFactorization PF(a, b);

		PF.Get_Prime_Factorization();
		PF.Print_Prime_Factorization();
		PF.Print_GCD();

		cout << endl;

	}

	system("PAUSE");
	return 0;
}
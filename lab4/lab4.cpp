#include <iostream>
#include <vector>
#include <fstream>
#include <cmath>

using namespace std;

class matrix
{
public:
	vector<vector<int> > M;


	matrix()
	{
		
		M.resize(3);
		for (int i = 0; i < 3; i++) {
			M[i].resize(3);
		}

	}

	matrix(vector<vector<int> >& m)
	{
		M = m;
	}

	vector<vector<int>> transfer(vector<vector<int>> a) {
		vector<vector<int>> ans(3);
		for (int i = 0; i < 3; i++) {
			ans[i].resize(3);
		}
		for (int i = 0; i < 3; i++) {
			for (int j = 0; j < 3; j++) {
				ans[i][j] = a[j][i];
			}
		}
		return ans;
	}

	
	vector<vector<int>> mul(vector<vector<int>> a, vector<vector<int>> b) {
		int n=3, m=3, p=3,sum=0;
		vector<vector<int>> matrix(3);
		for (int i = 0; i < 3; i++) {
			matrix[i].resize(3);
		}
		for (int i = 0; i < n; i++) {
			for (int k = 0; k < p; k++) {
				sum = 0;
				for (int j = 0; j < m; j++) {
					sum = sum + a[i][j] * b[j][k];
				}
				matrix[i][k] = sum;
			}
		}
		return matrix;
	}

	
	vector<vector<int>> adj(vector<vector<int>> matrix) {
		vector<vector<int>> ans(3);
		for (int i = 0; i < 3; i++) {
			ans[i].resize(3);
		}
		int tmp[2][2] = { 0 };
		int row = 0, line = 0;
		for (int i = 0; i < 3; i++) {
			for (int j = 0; j < 3; j++) {
				row = 0;
				for (int m = 0; m < 3; m++) {
					int flag = 1;
					line = 0;
					for (int n = 0; n < 3; n++) {
						if (m == i) {
							flag = 0;
							break;
						}
						if (n == j) continue;
						tmp[row][line] = matrix[m][n];
						line++;
					}
					if (flag == 1) row++;
					
				}
				ans[i][j] = pow(-1, i + j ) * (tmp[0][0] * tmp[1][1] - tmp[0][1] * tmp[1][0]);

			}
		}
		return transfer(ans);
		
	}

	
	int determinant(vector<vector<int>> a) {
		vector<vector<int>>ans(3);
		for (int i = 0; i < 3; i++) {
			ans[i].resize(3);
		}
		ans = mul(a, adj(a));
		return ans[0][0];

	}

};

int main()
{
	fstream fin;

	fin.open("testcase.txt", ios::in);
	if (!fin) {
		cout << "not open" << endl;
		exit(0);
	}

	int n;
	fin >> n;

	matrix matrix1;
	

	for (int i = 0; i < n; i++) {
		for (int j = 0; j < 3; j++) {
			for (int k = 0; k < 3; k++) {
				fin >> matrix1.M[j][k];
			}
		}
		cout << "the determinant of the matrix M is:" <<matrix1.determinant(matrix1.M)<<endl;
	}

	return 0;
}

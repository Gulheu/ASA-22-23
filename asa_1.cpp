
#include <stdio.h> 
#include <stdlib.h>
#include <iostream>
#include <array>
#include <vector>
#include <algorithm>
#include <map>
#include <utility>
#include <bits/stdc++.h>
using namespace std;

int linha;
int coluna;
vector<int> coordenadas;

map<vector<int>, long long> Save; 



vector<int> lerInput() {
	int e = 0;
	scanf("%d/n", &linha);
	scanf("%d/n", &coluna);
	

	while(e < linha) {
		int c;
		scanf("%d/n", &c);
		coordenadas.push_back(c);
		e++;
	}
	return coordenadas;
}

int getHigher(vector<int> coordenada) {
	int e;
	int i;
	for (i = coluna; i >= 0; i--) {
		for (e = linha - 1; e >= 0 ; e--)
			if(coordenada[e] == i) {
				return e;
			}
	}
	return 0;
}



int checkPossibilities(vector<int> coordenada, int linha1) {
	int possibilities = 0;
	int e = 0;

	for (e = linha1; e >= 0; e--) {
		if (coordenada[linha1] == coordenada[e]) {
			possibilities += 1;
		}
		else {
			break;
		}
	}  
	possibilities = min(possibilities, coordenada[linha1]);
	return possibilities;
}

vector<int> newCoordenadas(vector<int> coordenada, int linha, int possibilities) {
	int e = 0;
	for(e = linha; e > linha - possibilities; e--) {
		coordenada[e] -= possibilities;
	}

	return coordenada;
}


long long next(vector<int> coordenada){
	int e = 0;
	long long res = 0;
	int linha1 = getHigher(coordenada);

	int possibilities = checkPossibilities(coordenada, linha1);

	if (possibilities == 0) {
		res += 1;
	}

	for(e = 1; e <= possibilities; e++) {
		vector<int> novaCoordenada = newCoordenadas(coordenada,linha1,e);
		if (Save.find(novaCoordenada) != Save.end()) {
			res += Save[novaCoordenada];
		}
		else{
			long long option = next(novaCoordenada);
			res += option;
			Save.insert({novaCoordenada,option});
		}
		
	}
	return res;
}

int main() {
	time_t start, end;
	start = clock();
	ios_base::sync_with_stdio(false);
	vector<int> coordenada = lerInput();
	int i = coordenada.size();
	if(coordenada[i-1] == 0) {
		int Res = 0;
		cout << Res << endl;
		return Res;
	}
	long long Res = next(coordenada);
	end = clock();
	cout << Res << endl;
	double time = double(end-start) / double(CLOCKS_PER_SEC);
	cout << "Time taken is:"<< fixed
		<< time << setprecision(5);
	return 0;
}
#include <iostream>
#include <vector>

using namespace std;

const vector<vector<int>> switches = { //10개의 스위치가 각각 몇 번 시계와 연결되어있는지 나타내는 배열. 문제에서 주어진 고정값임.
	{0, 1, 2}, //#0
	{3, 7, 9, 11}, //#1
	{4, 10, 14, 15}, //#2
	{0, 4, 5, 6, 7}, //#3
	{6, 7, 8, 10, 12}, //#4
	{0, 2, 14, 15}, //#5
	{3, 14, 15}, //#6
	{4, 5, 7, 14, 15}, //#7
	{1, 2, 3, 4, 5}, //#8
	{3, 4, 5, 9, 13}, //#9
};

int difference_clock(vector<int>& clocks, int a, int b) //두 시계 사이의 시간 차이를 계산함
{
	int difference = 0;

	if (clocks[a] > clocks[b])
		return clocks[a] - clocks[b];
	else return clocks[b] - clocks[a];
}

int countswitch(vector<int>& clocks)
{
	int result = 0; // -1이면 달성 불가능
	int select_clock = -1;
	bool finished = true; //눌러야할 횟수가 남았으면 false, 완료하면 true
	vector<int> pressed;
	int cycle[10];

	//완료조건: 시계가 모두 12시면 완료.
	for (int i = 0; i < clocks.size(); ++i)
	{
		if (clocks[i] != 12)
			finished = false;
	}
	if (finished) return result;

	//불가능한 조건
	if (clocks[8] != clocks[12]) //8번 시계와 12번 시계가 서로 다르면 전부 12시로 만들 수 없음
		return -1;

	if (difference_clock(clocks, 9, 13) != difference_clock(clocks, 11, 13))//9 - 13이랑 11 - 13이 같지 않으면 12시로 만들 수 없음
		return -1;

	//불가능한 조건2 : 사이클이 존재하면 불가능함.
	for (int i = 0; i < pressed.size(); ++i) 
	{
		++cycle[pressed[i]];
	}

	for (int i = 0; i < 10; ++i)			//같은 스위치를 4번 이상 누르게 되면 사이클이 존재한다는 뜻
	{
		if (cycle[i] >= 4)
		{
			return -1;
			break;
		}
	}

	//12시로 만들 시계 선택
	for (int i = 0; i < clocks.size(); ++i)
	{
		if (clocks[i] != 12)
			select_clock = i;
	}

	//스위치를 한 번 누르고 난 다음 상태를 재귀 호출
	for (int num_switch = 0; num_switch < 10; ++num_switch)
	{
		for (int i = 0; i < switches[num_switch].size(); ++i)
		{
			if(clocks[switches[num_switch][i]] < 12)
				clocks[switches[num_switch][i]] += 3;
			else clocks[switches[num_switch][i]] = 3;

			result += 1;
		}

		result += countswitch(clocks);
		
	}

	return result;
}



int main()
{
	const int INF = 987654321;
	int num_case, c;
	int answer = -1;

	vector<int> inVector, clocks;

	cin >> num_case;

	while (cin >> c)
	{
		inVector.push_back(c);
	}

	//입력 검증 부분
	/*
	cout << "inVector:";

	for (int i = 0; i < inVector.size(); ++i)
		cout << inVector[i];

	cout << endl << "num_case:" << num_case << endl;
	*/

	for (int i = 0; i < num_case; ++i)
	{
		//cout << "clocks:";
		for (int j = 16 * i; j < 16 * (i + 1); ++j)
		{
			clocks.push_back(inVector[i]);
			//clocks 검증
			//cout << clocks[i];
		}
		//cout << endl;

		answer = countswitch(clocks);
		cout << answer << endl;
	}
	return 0;
}